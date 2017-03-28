#pragma once

#include <type_traits>
#include <tuple>
#include <utility>

namespace velm {

/*
 * \fn tuple_visit
 * \brief Call function on each tuple elements
 *
 * Taking a tuple-like and a function, this calls the given function on each
 * element of the tuple. A tuple with the result of each function call is
 * returned.
 *
 *      // example
 *      int a = 1, b = 2;
 *      auto c = tuple_visit(std::tie(a, b), [] (auto& x) { return x += 1; });
 *      // a = 2, b = 3, c = [2, 3];
 *
 * The passed function must return a value. Return a dummy value (e.g. 0) and
 * ignore the return if it is not needed.
 */

template <typename F, typename T, std::size_t... Is>
constexpr auto tuple_visit(T&& tup, F&& f, std::index_sequence<Is...> /* seq */)
{
	return std::make_tuple(f(std::get<Is>(tup))...);
}

template <typename F, typename T>
constexpr auto tuple_visit(T&& tup, F&& f)
{
	return tuple_visit(std::forward<T>(tup), std::forward<F>(f),
		std::make_index_sequence<std::tuple_size<std::decay_t<T>>::value>());
}


/*
 * \fn transpose_union
 * \brief Create tuple of tuples based on index
 *
 * Takes any number of tuple-likes, and groups them into a tuple of tuples.
 * Each tuple contains all values with the same index.
 *
 *      // example
 *      int a, b; double c, d;
 *      transpose_union(std::tie(a, b), std::tie(c, d))
 *      // returns std::tuple<std::tuple<int&, double&>, std::tuple<int&, double>>({a, c}, {b, c})
 *
 * The type of each value is based on std::tuple_element, and must be
 * convertible from using std::get. For example, the result of
 * std::forward_as_tuple will not work.
 */

template <unsigned int N, typename... Ts>
constexpr auto make_transpose(Ts&&... ts)
{
	using out_type = std::tuple<typename std::tuple_element<N, std::decay_t<Ts>>::type...>;
	return out_type{std::get<N>(std::forward<Ts>(ts))...};
}

template <typename... Ts, std::size_t... Is>
constexpr auto transpose_union(std::index_sequence<Is...> /* seq */, Ts&&... ts)
{
	using out_type = std::tuple<decltype(make_transpose<Is>(ts...))...>;
	return out_type{make_transpose<Is>(std::forward<Ts>(ts)...)...};
}

template <typename... Ts>
constexpr auto transpose_union(Ts&&... ts)
{
	using first_size = std::tuple_size<std::decay_t<typename std::tuple_element<0, std::tuple<Ts...>>::type>>;
	return transpose_union(std::make_index_sequence<first_size::value>(), std::forward<Ts>(ts)...);
}


/*
 * \fn tuple_subtype_apply
 * \brief Use tuple's sub-types as template parameters
 *
 * This takes a tuple-like and a template type taking any number of types. The
 * result is the template type with the tuple's element dimensions as the
 * parameters.
 *
 *      // example
 *      using common = tuple_subtype_apply<std::tuple<int, double>, std::common_type_t>::type;
 *      // common == double
 *
 */


template <typename T, template <typename...> typename F, typename = void>
struct tuple_subtype_apply
{
	using type = typename tuple_subtype_apply<T, F,
		std::make_index_sequence<std::tuple_size<T>::value>>::type;
};

template <typename T, template <typename...> typename F, std::size_t... Is>
struct tuple_subtype_apply<T, F, std::index_sequence<Is...>>
{
	using type = F<typename std::tuple_element<Is, T>::type...>;
};

template <typename T>
struct tuple_traits
{
	static constexpr auto size = std::tuple_size<std::decay_t<T>>::value;

	template <unsigned int N>
	using nth_type = typename std::tuple_element<N, T>::type;

	template <template <typename...> typename F>
	using subtype_apply = typename tuple_subtype_apply<T, F>::type;

	using common_type = subtype_apply<std::common_type_t>;
};

template <typename T, std::size_t>
using idx_dependent = T;

template <typename T, std::size_t... Is>
constexpr auto make_filled_tuple(T& val, std::index_sequence<Is...> /* seq */)
{
	return std::tuple<idx_dependent<T, Is>...>(((void)Is, std::forward<T>(val))...);
}

template <unsigned int Size, typename T>
constexpr auto make_filled_tuple(T&& val)
{
	return make_filled_tuple(std::forward<T>(val), std::make_index_sequence<Size>());
}


}
