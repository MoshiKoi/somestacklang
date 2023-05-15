#pragma once
#ifndef PARSER_HPP
#define PARSER_HPP

#include <format>
#include <stdexcept>
#include <unordered_map>
#include <variant>

#include "machine.hpp"
#include "token_iterator.hpp"

namespace esolang {

ValueList parse(token_iterator iter, token_iterator_sentinal end);

} // namespace esolang

#endif