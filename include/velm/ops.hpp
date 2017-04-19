#pragma once

#include "utility.hpp"

/**
 * \file ops.hpp
 * \brief operator overloads for vectors
 *
 * Several operator overloads are provided for vectors. These are generally
 * component-wise, and can be used for vectors and vectors, or vectors and
 * scalars. Most arithmetic operations are provided, as well as their compound
 * assignment counterparts. Comparison is done lexicographically.
 */

// unary {{{

template <typename T,
	std::enable_if_t<velm::utility::is_tied_vector<T>::value, int> = 0>
constexpr auto operator+(T&& vec)
{
	return velm::utility::vec_apply(velm::get_tie(vec), [] (auto&& x) { return +x; });
}

template <typename T,
	std::enable_if_t<velm::utility::is_tied_vector<T>::value, int> = 0>
constexpr auto operator-(T&& vec)
{
	return velm::utility::vec_apply(velm::get_tie(vec), [] (auto&& x) { return -x; });
}

// }}}
// arithmetic {{{

template <typename L, typename R, velm::utility::if_appliable<L, R> = 0>
constexpr auto operator+(L&& lhs, R&& rhs)
{
	return velm::utility::binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
		[] (auto&& a, auto&& b) { return a + b; });
}

template <typename L, typename R, velm::utility::if_appliable<L, R> = 0>
constexpr auto operator-(L&& lhs, R&& rhs)
{
	return velm::utility::binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
		[] (auto&& a, auto&& b) { return a - b; });
}

template <typename L, typename R, velm::utility::if_appliable<L, R> = 0>
constexpr auto operator*(L&& lhs, R&& rhs)
{
	return velm::utility::binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
		[] (auto&& a, auto&& b) { return a * b; });
}

template <typename L, typename R, velm::utility::if_appliable<L, R> = 0>
constexpr auto operator/(L&& lhs, R&& rhs)
{
	return velm::utility::binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
		[] (auto&& a, auto&& b) { return a / b; });
}

// }}}
// compound {{{

template <typename L, typename R, velm::utility::if_compound_appliable<L, R> = 0>
constexpr auto& operator+=(L& lhs, R&& rhs)
{
	velm::utility::binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
		[] (auto&& a, auto&& b) { return a += b; });
	return lhs;
}

template <typename L, typename R, velm::utility::if_compound_appliable<L, R> = 0>
constexpr auto& operator-=(L& lhs, R&& rhs)
{
	velm::utility::binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
		[] (auto&& a, auto&& b) { return a -= b; });
	return lhs;
}

template <typename L, typename R, velm::utility::if_compound_appliable<L, R> = 0>
constexpr auto& operator*=(L& lhs, R&& rhs)
{
	velm::utility::binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
		[] (auto&& a, auto&& b) { return a *= b; });
	return lhs;
}

template <typename L, typename R, velm::utility::if_compound_appliable<L, R> = 0>
constexpr auto& operator/=(L& lhs, R&& rhs)
{
	velm::utility::binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
		[] (auto&& a, auto&& b) { return a /= b; });
	return lhs;
}

// }}}
// comparison {{{

template <typename L, typename R, velm::utility::if_appliable<L, R> = 0>
constexpr bool operator==(L& lhs, R&& rhs)
{
	return velm::utility::binary_tuple_apply(lhs, rhs, [] (auto&& a, auto&& b) { return a == b; });
}

template <typename L, typename R, velm::utility::if_appliable<L, R> = 0>
constexpr bool operator!=(L& lhs, R&& rhs)
{
	return velm::utility::binary_tuple_apply(lhs, rhs, [] (auto&& a, auto&& b) { return a != b; });
}

template <typename L, typename R, velm::utility::if_appliable<L, R> = 0>
constexpr bool operator<(L& lhs, R&& rhs)
{
	return velm::utility::binary_tuple_apply(lhs, rhs, [] (auto&& a, auto&& b) { return a < b; });
}

template <typename L, typename R, velm::utility::if_appliable<L, R> = 0>
constexpr bool operator<=(L& lhs, R&& rhs)
{
	return velm::utility::binary_tuple_apply(lhs, rhs, [] (auto&& a, auto&& b) { return a <= b; });
}

template <typename L, typename R, velm::utility::if_appliable<L, R> = 0>
constexpr bool operator>(L& lhs, R&& rhs)
{
	return velm::utility::binary_tuple_apply(lhs, rhs, [] (auto&& a, auto&& b) { return a > b; });
}

template <typename L, typename R, velm::utility::if_appliable<L, R> = 0>
constexpr bool operator>=(L& lhs, R&& rhs)
{
	return velm::utility::binary_tuple_apply(lhs, rhs, [] (auto&& a, auto&& b) { return a >= b; });
}

// }}}
