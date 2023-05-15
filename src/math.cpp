#include <stdexcept>

#include "math.hpp"
#include "overloaded.hpp"

Value
operator+(Value const &left, Value const &right) {
	return std::visit(
		overloaded{
			[](double left, double right) -> Value { return left + right; },
			[](auto left, auto right) -> Value { throw std::runtime_error{"Invalid operands {} and {}"}; },
		},
		left, right);
}

Value
operator-(Value const &left, Value const &right) {
	return std::visit(
		overloaded{
			[](double left, double right) -> Value { return left - right; },
			[](auto left, auto right) -> Value { throw std::runtime_error{"Invalid operands {} and {}"}; },
		},
		left, right);
}

Value
operator*(Value const &left, Value const &right) {
	return std::visit(
		overloaded{
			[](double left, double right) -> Value { return left * right; },
			[](auto left, auto right) -> Value { throw std::runtime_error{"Invalid operands {} and {}"}; },
		},
		left, right);
}

Value
operator/(Value const &left, Value const &right) {
	return std::visit(
		overloaded{
			[](double left, double right) -> Value { return left / right; },
			[](auto left, auto right) -> Value { throw std::runtime_error{"Invalid operands {} and {}"}; },
		},
		left, right);
}