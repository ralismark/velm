#pragma once

#include <type_traits>
#include <utility>

#include "defs.hpp"
#include "tuple_utils.hpp"
#include "tie.hpp"

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
 * \typedef detect
 * \brief detection idiom
 *
 * This allows the use of the detection idiom, which checks if a template
 * instantiation is valid, and determines what the resulting type is. This can
 * be used to roughly implement concepts, by checking the type of certain
 * expressions.
 *
 * See http://en.cppreference.com/w/cpp/experimental/is_detected for details.
 */
template <typename...>
using void_t = void;

template <typename Void, template <typename...> typename Op, typename... Args>
struct detector
{
	using value_t = std::false_type;
	using type = void;
};

template <template <typename...> typename Op, typename... Args>
struct detector<void_t<Op<Args...>>, Op, Args...>
{
	using value_t = std::true_type;
	using type = Op<Args...>;
};

template <template <typename...> typename Op, typename... Args>
using detect = detector<void, Op, Args...>;

/**
 * \typedef is_callable_r
 * \brief check if a function is callable and return is convertible
 *
 * Similar to std::is_callable_r/std::is_invocable_r, this checks if a given
 * function (Fn) is callable with a given set of arguments, and that the return
 * type is convertible to another given type.
 */
template <typename Fn, typename... Args>
using call_detect = decltype(std::declval<Fn>()(std::declval<Args>()...));

template <typename R, typename Fn, typename... Args>
using is_callable_r = std::is_convertible<typename detect<call_detect, Fn, Args...>::type, R>;

/**
 * \struct prepend
 * \brief prepend arguments to template parameter list
 *
 * This adds any number of types to the front of the argument list. Use the
 * template member apply as the result.
 *
 * Note: remember to use the template keyword in front of fn, since it may be a
 * dependent member
 */
template <template <typename...> typename Fn, typename... Pre>
struct prepend
{
	template <typename... Ts>
	using apply = Fn<Pre..., Ts...>;
};

/**
 * \struct append
 * \brief add arguments to the end of a template parameter list
 *
 * Similar to prepend, but to the back.
 */
template <template <typename...> typename Fn, typename... App>
struct append
{
	template <typename... Ts>
	using apply = Fn<Ts..., App...>;
};

/**
 * \struct is_tied_vector
 * \brief checks if a type is a vector-like
 *
 * This checks if a type fulfils the tied_vector concept. That is,
 * velm::get_tie(a) returns a tuple-like (i.e. tuple, pair, array).
 */
template <typename T>
using tie_detect = decltype(usr::tie<std::decay_t<T>>{}(std::declval<T>()));

template <typename T>
using is_tied_vector = typename detect<tie_detect, T>::value_t;

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
	return f(get_tie(vec1), get_tie(vec2));
}

template <typename T1, typename T2, typename F, std::enable_if_t<
	!is_tied_vector<T1>::value && is_tied_vector<T2>::value
	, int> = 0>
constexpr decltype(auto) binary_tuple_apply(T1&& val1, T2&& vec2, F&& f)
{
	using traits = tuple_traits<decltype(get_tie(vec2))>;
	return f(make_filled_tuple<traits::size>(val1), get_tie(vec2));
}

template <typename T1, typename T2, typename F, std::enable_if_t<
	is_tied_vector<T1>::value && !is_tied_vector<T2>::value
	, int> = 0>
constexpr decltype(auto) binary_tuple_apply(T1&& vec1, T2&& val2, F&& f)
{
	using traits = tuple_traits<decltype(get_tie(vec1))>;
	return f(get_tie(vec1), make_filled_tuple<traits::size>(val2));
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
