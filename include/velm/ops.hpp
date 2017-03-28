#pragma once

#include "utility.hpp"

// unary plus {{{

template <typename T,
	std::enable_if_t<velm::is_tied_vector<T>::value, int> = 0>
constexpr auto operator+(T&& vec)
{
	return velm::vec_apply(vec.tie(), [] (auto&& x) { return +x; });
}

// }}}
// unary negate {{{

template <typename T,
	std::enable_if_t<velm::is_tied_vector<T>::value, int> = 0>
constexpr auto operator-(T&& vec)
{
	return velm::vec_apply(vec.tie(), [] (auto&& x) { return -x; });
}

// }}}
// arithmetic {{{

template <typename L, typename R, velm::if_appliable<L, R> = 0>
constexpr auto operator+(L&& lhs, R&& rhs)
{
	return velm::binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
		[] (auto&& a, auto&& b) { return a + b; });
}

template <typename L, typename R, velm::if_appliable<L, R> = 0>
constexpr auto operator-(L&& lhs, R&& rhs)
{
	return velm::binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
		[] (auto&& a, auto&& b) { return a - b; });
}

template <typename L, typename R, velm::if_appliable<L, R> = 0>
constexpr auto operator*(L&& lhs, R&& rhs)
{
	return velm::binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
		[] (auto&& a, auto&& b) { return a * b; });
}

template <typename L, typename R, velm::if_appliable<L, R> = 0>
constexpr auto operator/(L&& lhs, R&& rhs)
{
	return velm::binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
		[] (auto&& a, auto&& b) { return a / b; });
}

// }}}
// compound {{{

template <typename L, typename R, velm::if_compound_appliable<L, R> = 0>
constexpr auto& operator+=(L& lhs, R&& rhs)
{
	velm::binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
		[] (auto&& a, auto&& b) { return a += b; });
	return lhs;
}

template <typename L, typename R, velm::if_compound_appliable<L, R> = 0>
constexpr auto& operator-=(L& lhs, R&& rhs)
{
	velm::binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
		[] (auto&& a, auto&& b) { return a -= b; });
	return lhs;
}

template <typename L, typename R, velm::if_compound_appliable<L, R> = 0>
constexpr auto& operator*=(L& lhs, R&& rhs)
{
	velm::binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
		[] (auto&& a, auto&& b) { return a *= b; });
	return lhs;
}

template <typename L, typename R, velm::if_compound_appliable<L, R> = 0>
constexpr auto& operator/=(L& lhs, R&& rhs)
{
	velm::binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
		[] (auto&& a, auto&& b) { return a /= b; });
	return lhs;
}

// }}}
// comparison {{{

template <typename L, typename R, velm::if_appliable<L, R> = 0>
constexpr bool operator==(L& lhs, R&& rhs)
{
	return velm::binary_tuple_apply(lhs, rhs, [] (auto&& a, auto&& b) { return a == b; });
}

template <typename L, typename R, velm::if_appliable<L, R> = 0>
constexpr bool operator!=(L& lhs, R&& rhs)
{
	return velm::binary_tuple_apply(lhs, rhs, [] (auto&& a, auto&& b) { return a != b; });
}

template <typename L, typename R, velm::if_appliable<L, R> = 0>
constexpr bool operator<(L& lhs, R&& rhs)
{
	return velm::binary_tuple_apply(lhs, rhs, [] (auto&& a, auto&& b) { return a < b; });
}

template <typename L, typename R, velm::if_appliable<L, R> = 0>
constexpr bool operator<=(L& lhs, R&& rhs)
{
	return velm::binary_tuple_apply(lhs, rhs, [] (auto&& a, auto&& b) { return a <= b; });
}

template <typename L, typename R, velm::if_appliable<L, R> = 0>
constexpr bool operator>(L& lhs, R&& rhs)
{
	return velm::binary_tuple_apply(lhs, rhs, [] (auto&& a, auto&& b) { return a > b; });
}

template <typename L, typename R, velm::if_appliable<L, R> = 0>
constexpr bool operator>=(L& lhs, R&& rhs)
{
	return velm::binary_tuple_apply(lhs, rhs, [] (auto&& a, auto&& b) { return a >= b; });
}

// }}}
