#pragma once

#include <type_traits>
#include <utility>

namespace velm {

	/**
	 * \fn tie
	 * \brief get tie of type
	 *
	 * This is to allow ADL for ties, e.g. for external types. Overload as
	 * needed.
	 */
	template <typename T>
	constexpr decltype(auto) tie(T&& t)
	{
		return t.tie();
	}

	// tuple types
	template <typename T,
		typename = std::enable_if_t<(std::tuple_size<std::decay_t<T>>::value >= 0)>>
	constexpr decltype(auto) tie(T&& tup)
	{
		return tup;
	}

	/**
	 * \fn adl_tie
	 * \brief ADL helper for tie
	 *
	 * This helps by making it easier to use tie() properly.
	 */
	template <typename T>
	constexpr decltype(auto) adl_tie(T&& t)
	{
		using namespace velm;
		return tie(std::forward<T>(t));
	}

} // namespace velm
