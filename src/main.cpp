#include <fstream>
#include <iostream>
#include <ranges>
#include <stdexcept>
#include <string>
#include <variant>

#include "machine.hpp"
#include "overloaded.hpp"
#include "parse.hpp"
#include "token_iterator.hpp"

void
print_token(esolang::token const &token) {
#define X_TOKEN(Name, ...) \
	[](esolang::Name const &token) -> void { std::cout << #Name __VA_OPT__(<< '(' << token.value << ')'); },

	std::visit(overloaded{[](std::monostate) { std::cout << "err"; }, X_TOKENS}, token);

#undef X_TOKEN
}

void
run(std::string_view view) {
	auto ops = esolang::parse(view, {});
	std::stack<Value> stack;
	stack.push(ops);
	machine m{stack};
	m.run();
}

void
repl() {
	std::string line{};
	while (true) {
		std::cout << "\n> " << std::flush;
		std::getline(std::cin, line);
		if (line == "quit") {
			break;
		}

		try {
			run(line);
		} catch (std::runtime_error err) { std::cerr << err.what() << std::endl; }
	}
}

int
main(int argc, char const **argv) {
	if (argc > 1) {
		std::ifstream ifs{argv[1]};
		std::stringstream ss{};
		ss << ifs.rdbuf();
		run(ss.view());
	} else {
		repl();
	}
}