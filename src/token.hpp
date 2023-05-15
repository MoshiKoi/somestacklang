#pragma once
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <variant>

#define X_TOKENS \
	X_TOKEN(Number, double) \
	X_TOKEN(String, std::string) \
	X_TOKEN(Identifier, std::string) \
	X_TOKEN(LBracket) \
	X_TOKEN(RBracket)

namespace esolang {
#define X_TOKEN(Name, ...) \
	struct Name { \
		__VA_OPT__(__VA_ARGS__ value;) \
	};

X_TOKENS

#undef X_TOKEN

#define X_TOKEN(Name, ...) , Name

using token = std::variant<std::monostate X_TOKENS>;

#undef X_TOKEN

} // namespace esolang

#endif