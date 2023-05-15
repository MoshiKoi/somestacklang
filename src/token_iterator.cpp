#include <cctype>
#include <charconv>
#include <sstream>
#include <stdexcept>

#include "token_iterator.hpp"

namespace esolang {

token_iterator &
token_iterator::operator++() {

#ifdef _DEBUG
	if (_at_end) {
		throw std::runtime_error{"Attempted to iterate past end of input"};
	}
#endif

	std::stringstream builder{};
	while (_cur != _end) {
		switch (*_cur) {
		case ' ':
		case '\t':
		case '\n': ++_cur; continue;
		case '[':
			++_cur;
			_cur_token = LBracket{};
			return *this;
		case ']':
			++_cur;
			_cur_token = RBracket{};
			return *this;

		case '0' ... '9': {
			builder.str("");
			while (_cur != _end && '0' <= *_cur && *_cur <= '9') {
				builder.put(*_cur);
				++_cur;
			}

			double result;
			auto const view = builder.view();
			auto const [_, ec] = std::from_chars(view.data(), view.data() + view.size(), result);

			if (ec != std::errc()) {
				throw std::runtime_error{"Invalid number"};
			}

			_cur_token = Number{result};
			return *this;
		}
		case '"': {
			++_cur;
			builder.str("");
			while (_cur != _end && *_cur != '"') {
				builder.put(*_cur);
				++_cur;
			}
			if (_cur != _end) {
				++_cur;
			}
			_cur_token = String{builder.str()};
			return *this;
		}
		}

		if (std::isalpha(*_cur)) {
			builder.str("");
			while (_cur != _end && std::isalpha(*_cur)) {
				builder.put(*_cur);
				++_cur;
			}
			_cur_token = Identifier{builder.str()};
			return *this;
		}

		throw std::runtime_error{"Character not allowed"};
	}

	_at_end = true;
	return *this;
}

} // namespace esolang