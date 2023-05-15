#pragma once
#ifndef VALUE_HPP
#define VALUE_HPP

#include <string>
#include <variant>
#include <vector>

enum class Operation {
	Add,
	Sub,
	Mul,
	Div,
	Dup,
	Associate,
	Read,
	ReadNum,
	Cond,
};

struct ValueList;

using Value = std::variant<ValueList, Operation, double, std::string>;

struct ValueList {
	std::vector<Value> values;
};

#endif