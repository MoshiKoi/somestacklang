#pragma once
#ifndef MATH_HPP
#define MATH_HPP

#include "value.hpp"

Value operator+(Value const &left, Value const &right);
Value operator-(Value const &left, Value const &right);
Value operator*(Value const &left, Value const &right);
Value operator/(Value const &left, Value const &right);

#endif