#pragma once

#include "defs.hpp"
#include "utility.hpp"

namespace velm {

	/**
	 * \fn convert_to
	 * \brief convert from arguments to a type
	 *
	 * This is a customisation point which allows user-provided types to be
	 * converted to from a velm::vector. The user should specialise this to
	 * take any number of parameters, and return the same type as the first
	 * parameter.
	 */
	template <typename T, typename... Ts>
	T convert_to(Ts&&... args) = delete;

	template <typename T, unsigned int N, typename... Ts,
		std::enable_if<(sizeof...(Ts) == N), int> = 0>
	vector<T, N> convert_to(Ts&&... args)
	{
		return vector<T, N>{args...};
	}

	template <typename R, typename F, typename Tup,
		typename = std::enable_if_t<std::is_convertible<
			decltype(apply(std::declval<F>(), std::declval<Tup>())), R
		>::value>>
	std::true_type is_tuple_callable_r_test(R, F, Tup);
	std::false_type is_tuple_callable_r_test(...);

	template <typename T>
	struct generic_convert_to
	{
		template <typename... Ts>
		decltype(auto) operator()(Ts&&... args)
		{
			return convert_to<T>(std::forward<Ts>(args)...);
		}
	};

	template <typename T, typename Tup>
	using is_vector_convertible_to =
		decltype(is_callable_r_test(
			std::declval<T>(),
			generic_convert_to<T>{},
			std::declval<Tup>()
		));

} // namespace velm
