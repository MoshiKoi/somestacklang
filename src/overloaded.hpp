#pragma once
#ifndef OVERLOADED_HPP
#define OVERLOADED_HPP

template <class... Ts>
struct overloaded : Ts... {
	using Ts::operator()...;
};

template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

#endif