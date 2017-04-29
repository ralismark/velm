#pragma once

#include <type_traits>
#include <utility>

namespace velm { namespace usr {

	/**
	 * \struct tie
	 * \brief function objet to create a tie from a type
	 *
	 * Similar to usr::converter_to, this provides another customisation
	 * point to allow user-provided type to be used in vector operations.
	 *
	 * This should be specialised to take a single argument, which is the
	 * same as (or convertible from) the template type, and return a
	 * tuple-like (i.e. pair, tuple, array).
	 *
	 * Additionally, this detects the member function tie() and is able to
	 * use that without additional overloads.
	 */
	template <typename T, typename = void>
	struct tie
	{
		// void operator()(const T&) const = delete;
	};

	// types with .tie() member function
	template <typename T>
	struct tie<T, typename std::conditional<true, void,
			decltype(std::declval<T&>().tie())
		>::type>
	{
		template <typename U> // allows perfect forwarding, e.g. for rvalue overloads
		decltype(auto) operator()(U&& t)
		{
			return std::forward<U>(t).tie();
		}
	};

	// tuple types
	template <typename T>
	struct tie<T, std::enable_if_t<(
			std::tuple_size<T>::value >= 0
		)>>
	{
		template <typename U>
		decltype(auto) operator()(U&& t)
		{
			return std::forward<U>(t);
		}
	};

} } // namespace velm::usr

namespace velm {

	template <typename T>
	decltype(auto) get_tie(T&& t)
	{
		return usr::tie<std::decay_t<T>>{}(t);
	}

} // namespace velm
