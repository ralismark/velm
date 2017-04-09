#pragma once

#include <type_traits>
#include <utility>

#include "defs.hpp"
#include "tuple_utils.hpp"

namespace velm {

/**
 * \struct tied_vector
 * \brief tag for vector-likes
 *
 * Inherit from this class to denote a vector-like type. That type must have
 * the member function tie(), as well as the type value_type.
 */
struct tied_vector
{
	// using T = drived type

	// requires(T a) {
	//      a.tie() -> std::tuple<T::value_type...>
	// }
}; // tag

} // namespace velm

namespace velm { namespace utility {

/**
 * \struct tmax
 * \brief variadic maximal value
 *
 * Calculated the largest value in the provided parameter list.
 */

template <typename T, T v, T...>
struct tmax
	: std::integral_constant<T, v>
{
};

template <typename T, T l, T r, T... vals>
struct tmax<T, l, r, vals...>
	: std::integral_constant<T, tmax<T, (l > r ? l : r), vals...>::value>
{
};

/**
 * \struct is_tied_vector
 * \brief checks if a type is a vector-like
 *
 * This checks if a type inherits from the tied_vector tag.
 */
template <typename T>
using is_tied_vector = std::is_base_of<tied_vector, std::decay_t<T>>;

/**
 * \fn vec_apply
 * \brief call function on every element of a tuple
 *
 * This calls a given function f on every element of a tuple, and constructs a
 * new vector from the returned values. Essentially a wrapper around
 * tuple_visit.
 */
template <typename T, typename F>
constexpr auto vec_apply(T&& vec, F&& f)
{
	using applied_tuple = decltype(tuple_visit(vec, std::forward<F>(f)));
	using traits = tuple_traits<applied_tuple>;
	using ret_vec = vector<typename traits::common_type, traits::size>;

	return ret_vec::from_tuple(tuple_visit(vec, std::forward<F>(f)));
}

/**
 * \fn vec_apply2
 * \brief apply function over 2 tuples
 *
 * Similar to vec_apply, but takes 2 tuples, and calls the given function on
 * each pair of values. This requires that the 2 tuples are of the same size.
 */
template <typename T1, typename T2, typename F>
constexpr auto vec_apply2(T1&& vec1, T2&& vec2, F&& f)
{
	auto apply_wrapper = [&] (auto&& t) -> decltype(auto) {
		return f(std::get<0>(t), std::get<1>(t));
	};

	return vec_apply(transpose_union(vec1, vec2), apply_wrapper);
}

/**
 * \fn binary_tuple_apply
 * \brief Calls function on tuple made with vectos or values
 *
 * Normally, one has to convert a value to a filled tuple to do tuple
 * operations. This function provides overloads for all combinations of vectors
 * and values, reducing the amount of overloads required by the user.
 */
template <typename T1, typename T2, typename F, std::enable_if_t<
	is_tied_vector<T1>::value && is_tied_vector<T2>::value
	, int> = 0>
constexpr decltype(auto) binary_tuple_apply(T1&& vec1, T2&& vec2, F&& f)
{
	return f(vec1.tie(), vec2.tie());
}

template <typename T1, typename T2, typename F, std::enable_if_t<
	!is_tied_vector<T1>::value && is_tied_vector<T2>::value
	, int> = 0>
constexpr decltype(auto) binary_tuple_apply(T1&& val1, T2&& vec2, F&& f)
{
	using traits = tuple_traits<decltype(vec2.tie())>;
	return f(make_filled_tuple<traits::size>(val1), vec2.tie());
}

template <typename T1, typename T2, typename F, std::enable_if_t<
	is_tied_vector<T1>::value && !is_tied_vector<T2>::value
	, int> = 0>
constexpr decltype(auto) binary_tuple_apply(T1&& vec1, T2&& val2, F&& f)
{
	using traits = tuple_traits<decltype(vec1.tie())>;
	return f(vec1.tie(), make_filled_tuple<traits::size>(val2));
}

template <typename T1, typename T2, typename F, std::enable_if_t<
	!is_tied_vector<T1>::value && !is_tied_vector<T2>::value
	, int> = 0>
constexpr decltype(auto) binary_tuple_apply(T1&& vec1, T2&& val2, F&& f) = delete;

/**
 * \fn binary_apply
 * \brief apply function over arguments
 *
 * This combines the functionality of binary_tuple_apply and vec_apply2,
 * calling a function over each pair of values.
 */
template <typename T1, typename T2, typename F>
constexpr decltype(auto) binary_apply(T1&& lhs, T2&& rhs, F&& f)
{
	auto apply_wrapper = [&] (auto&& lhs, auto&& rhs) {
		return vec_apply2(std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<F>(f));
	};
	return binary_tuple_apply(std::forward<T1>(lhs), std::forward<T2>(rhs), apply_wrapper);
}

template <typename T1, typename T2>
using is_appliable = std::integral_constant<bool, is_tied_vector<T1>::value || is_tied_vector<T2>::value>;

template <typename T1, typename T2>
using if_appliable = std::enable_if_t<is_appliable<T1, T2>::value, int>;

template <typename T1, typename T2>
using if_compound_appliable = std::enable_if_t<is_tied_vector<T1>::value, int>;

} } // namespace velm::utility
