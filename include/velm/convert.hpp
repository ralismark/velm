#pragma once

#include <utility>

#include "defs.hpp"

namespace velm {

	/**
	 * \struct converter_to
	 * \brief function object to convert from arguments to a type
	 *
	 * This is a customisation point which allows user-provided types to be
	 * created from a velm::vector. The user should specialise this to take
	 * any number of parameters, and return the same type as the template
	 * parameter.
	 */
	template <typename T>
	struct converter_to
	{
		template <typename... Args>
		T operator()(Args&&...) const = delete;
	};

	template <typename T, unsigned int N>
	struct converter_to<vector<T, N>>
	{
		template <typename... Args,
			std::enable_if_t<(sizeof...(Args) == N), int> = 0>
		vector<T, N> operator()(Args&&... args) const
		{
			return vector<T, N>{args...};
		}
	};

	template <typename R, typename F, typename Tup,
		typename = std::enable_if_t<std::is_convertible<
			decltype(utility::apply(std::declval<F>(), std::declval<Tup>())), R
		>::value>>
	std::true_type is_tuple_callable_r_test(R, F, Tup);
	std::false_type is_tuple_callable_r_test(...);

	template <typename T, typename Tup>
	using is_vector_convertible_to =
		decltype(is_tuple_callable_r_test(
			std::declval<T>(),
			std::declval<converter_to<T>>(),
			std::declval<Tup>()
		));

} // namespace velm
