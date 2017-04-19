#pragma once

#include <utility>

#include "defs.hpp"
#include "tuple_utils.hpp"

namespace velm { namespace usr {

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

} } // namespace velm::usr

namespace velm {

	template <typename T, typename Tup>
	using is_vector_convertible_to = typename utility::tuple_subtype_apply<Tup,
			utility::prepend<utility::is_callable_r, T, usr::converter_to<T>>::template apply
		>::type;

} // namespace velm
