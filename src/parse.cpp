#include "parse.hpp"

namespace esolang {

static std::unordered_map<std::string_view, Operation> const kws{
	{"add", Operation::Add},   {"sub", Operation::Sub},         {"mul", Operation::Mul},
	{"div", Operation::Div},   {"dup", Operation::Dup},         {"commute", Operation::Commute},
	{"read", Operation::Read}, {"readnum", Operation::ReadNum}, {"if", Operation::Cond},
};

ValueList
parse2(token_iterator &iter, token_iterator_sentinal end) {
	ValueList list{};
	while (iter != end) {
		if (std::holds_alternative<RBracket>(*iter)) {
			++iter;
			break;
		}

		list.values.emplace_back(std::visit(
			overloaded{
				[&](Number const &num) -> Value {
					double value = num.value;
					++iter;
					return {value};
				},
				[&](String const &str) -> Value {
					std::string value = str.value;
					++iter;
					return {value};
				},
				[&](Identifier const &ident) -> Value {
					auto const find = kws.find(ident.value);
					if (find != std::end(kws)) {
						++iter;
						return find->second;
					} else {
						throw std::runtime_error{std::format("{} is not a command", ident.value)};
					}
				},
				[&](LBracket const &) -> Value {
					++iter;
					return parse2(iter, end);
				},
				[](auto const &) -> Value { throw std::runtime_error{"Invalid token"}; },
			},
			*iter));
	}
	return list;
}

ValueList
parse(token_iterator iter, token_iterator_sentinal end) {
	return parse2(iter, end);
}

} // namespace esolang