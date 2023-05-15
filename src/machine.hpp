#pragma once
#ifndef MACHINE_HPP
#define MACHINE_HPP

#include <format>
#include <iostream>
#include <memory>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

#include "math.hpp"
#include "overloaded.hpp"
#include "value.hpp"

inline bool
truthy(Value const &value) {
	return std::visit(
		overloaded{
			[](double const &value) { return value != 0; },
			[](std::string const &value) { return !value.empty(); },
			[](auto) -> bool { throw std::runtime_error{"Invalid operand"}; },
		},
		value);
}

class machine {
	std::stack<Value> _stack;

  public:
	machine(std::stack<Value> stack) : _stack{stack} {}

	void run() {
		while (!_stack.empty()) {
			auto const item = _stack.top();
			_stack.pop();

			std::visit(
				overloaded{
					[&](ValueList const &list) {
						for (auto const &item : list.values) {
							_stack.push(item);
						}
					},
					[&](Operation const &op) { execute(op); },
					[&](double value) { std::cout << value; },
					[&](std::string value) { std::cout << value; },
				},
				item);
		}
	}

	void execute(Operation const &operation) {
		switch (operation) {
		case Operation::Add: {
			auto const a = _stack.top();
			_stack.pop();
			auto const b = _stack.top();
			_stack.pop();

			place(b + a);
			break;
		}
		case Operation::Sub: {
			auto const a = _stack.top();
			_stack.pop();
			auto const b = _stack.top();
			_stack.pop();

			place(b - a);
			break;
		}
		case Operation::Mul: {
			auto const a = _stack.top();
			_stack.pop();
			auto const b = _stack.top();
			_stack.pop();

			place(b * a);
			break;
		}
		case Operation::Div: {
			auto const a = _stack.top();
			_stack.pop();
			auto const b = _stack.top();
			_stack.pop();

			place(b / a);
			break;
		}
		case Operation::Dup: {
			_stack.push(_stack.top());
			break;
		}
		case Operation::Associate: {
			auto const value = _stack.top();
			_stack.pop();

			if (_stack.empty()) {
				throw std::runtime_error{"Empty stack"};
			}
			if (auto *list = std::get_if<ValueList>(&_stack.top())) {
				for (auto &item : list->values) {
					if (auto *inner = std::get_if<ValueList>(&item)) {
						inner->values.insert(inner->values.begin(), value);
					}
				}
			} else {
				throw std::runtime_error{"No value list to insert into"};
			}
			break;
		}
		case Operation::Read: {
			std::string str{};
			std::getline(std::cin, str);
			place(str);
			break;
		}
		case Operation::ReadNum: {
			double num;
			std::cin >> num;
			place(num);
			break;
		}
		case Operation::Cond: {
			auto const top = _stack.top();
			_stack.pop();
			auto const when_true = _stack.top();
			_stack.pop();
			auto const when_false = _stack.top();
			_stack.pop();

			if (truthy(top)) {
				place(when_true);
			} else {
				place(when_false);
			}
			break;
		}
		}
	}

	void place(Value value) {
		if (_stack.empty()) {
			throw std::runtime_error{"Empty stack"};
		}
		if (auto *list = std::get_if<ValueList>(&_stack.top())) {
			list->values.insert(list->values.begin(), value);
		} else {
			throw std::runtime_error{"No value list to insert into"};
		}
	}
};

#endif