#pragma once
#ifndef TOKEN_ITERATOR_HPP
#define TOKEN_ITERATOR_HPP

#include "token.hpp"

namespace esolang {

class token_iterator_sentinal {};

class token_iterator {
	using iter = std::string_view::const_iterator;

	iter _cur;
	iter _end;
	bool _at_end;

	token _cur_token;

	struct proxy {
		token const value;
		token operator*() { return value; }
	};

  public:
	token_iterator(iter begin, iter end) : _cur{begin}, _end{end}, _at_end{false} { ++*this; }
	token_iterator(std::string_view view) : token_iterator{std::begin(view), std::end(view)} {}

	token operator*() const { return _cur_token; }
	token_iterator &operator++();
	proxy operator++(int) {
		proxy const iter{**this};
		++*this;
		return iter;
	}
	bool operator==(token_iterator const &other) const {
		return _cur == other._cur && _end == other._end && _at_end == other._at_end;
	}
	bool operator==(token_iterator_sentinal const &other) const { return _at_end; }

	using difference_type = std::ptrdiff_t;
	using value_type = token;
	using pointer = token *;
	using reference = token &;
	using iterator_category = std::input_iterator_tag;
};

} // namespace esolang

#endif