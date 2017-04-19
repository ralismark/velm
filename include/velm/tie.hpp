#pragma once

#include <type_traits>
#include <utility>

namespace velm { namespace usr {

	/**
	 * \fn tie
	 * \brief get tie of type
	 *
	 * This is a customisation point to allow external types (ones that you
	 * cannot modify e.g. in other libraries) to be used.
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

} } // namespace velm::usr
