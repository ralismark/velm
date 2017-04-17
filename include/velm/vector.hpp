#pragma once

#include "defs.hpp"
#include "base.hpp"
#include "utility.hpp"
#include "proxy.hpp"
#include "convert.hpp"

namespace velm {

template <typename T, unsigned int N>
struct vector
	: private tied_vector
	, public vec_base<T, N, swizzle_proxy>
{
public: // statics

	static constexpr auto dimensions = N;
	using value_type = T;

	template <typename Tup>
	constexpr static vector<T, N> from_tuple(Tup&& t)
	{
		using tup_size = std::tuple_size<std::decay_t<Tup>>;
		static_assert(tup_size::value == N, "Tuple must have an element for each dimension");

		auto constructor = [] (auto&&... args) {
			return vector<T, N>(std::forward<decltype(args)>(args)...);
		};
		return utility::apply(constructor, std::forward<Tup>(t));
	}

private: // internal methods

	using base_type = vec_base<T, N, swizzle_proxy>;

	constexpr base_type& as_base()
	{
		return static_cast<base_type&>(*this);
	}

	constexpr const base_type& as_base() const
	{
		return static_cast<const base_type&>(*this);
	}

	template <std::size_t... Is>
	constexpr auto tie_impl(std::index_sequence<Is...> /* seq */)
	{
		return std::tie(std::get<Is>(this->as_base().data)...);
	}

	template <std::size_t... Is>
	constexpr auto tie_impl(std::index_sequence<Is...> /* seq */) const
	{
		return std::tie(std::get<Is>(this->as_base().data)...);
	}

	template <std::size_t... Is>
	constexpr auto tie_impl_r(std::index_sequence<Is...> /* seq */) const
	{
		return std::make_tuple(std::get<Is>(this->as_base().data)...);
	}

public: // methods

	constexpr vector()
		: tied_vector()
		, base_type()
	{
	}

	// value constructors
	template <typename U,
	         std::enable_if_t<(!utility::is_tied_vector<std::decay_t<U>>::value), int> = 0>
	constexpr vector(const U& val)
		: vector(from_tuple(utility::make_filled_tuple<N>(val)))
	{
	}

	// vector converters
	template <typename V,
		std::enable_if_t<(utility::is_tied_vector<std::decay_t<V>>::value), int> = 0>
	constexpr vector(const V& vec)
		: vector(from_tuple(vec.tie()))
	{
	}

	// dimension constructors
	template <typename... Ts,
		typename = std::enable_if_t<(sizeof...(Ts) == N && N > 1)>>
	constexpr vector(Ts&&... vals)
		: tied_vector()
		, base_type{{{{static_cast<T>(std::forward<Ts>(vals))...}}}}
	{
	}

	template <typename U,
		std::enable_if_t<is_vector_convertible_to<U, decltype(utility::make_filled_tuple<N>(std::declval<T>()))>::value, int> = 0>
	operator U() const
	{
		return utility::apply(converter_to<U>{}, this->tie());
	}

	template <unsigned int... Is>
	swizzle_proxy<T, Is...>& swizzle() &
	{
		static_assert(utility::tmax<unsigned int, Is...>::value < N, "Indices must be valid");
		return *reinterpret_cast<swizzle_proxy<T, Is...>*>(&this->as_base().data);
	}

	template <unsigned int... Is>
	const swizzle_proxy<T, Is...>& swizzle() const&
	{
		static_assert(utility::tmax<unsigned int, Is...>::value < N, "Indices must be valid");
		return *reinterpret_cast<const swizzle_proxy<T, Is...>*>(&this->as_base().data);
	}

	template <unsigned int... Is>
	vector<T, sizeof...(Is)> swizzle() const&&
	{
		static_assert(utility::tmax<unsigned int, Is...>::value < N, "Indices must be valid");
		return vector<T, sizeof...(Is)>(std::get<Is>(this->as_base().data)...);
	}

	constexpr auto tie() &
	{
		return this->tie_impl(std::make_index_sequence<N>());
	}

	constexpr auto tie() const&
	{
		return this->tie_impl(std::make_index_sequence<N>());
	}

	constexpr auto tie() const&&
	{
		return this->tie_impl_r(std::make_index_sequence<N>());
	}

	constexpr T& operator[](std::size_t idx)
	{
		return this->as_base().data[idx];
	}

	constexpr const T& operator[](std::size_t idx) const
	{
		return this->as_base().data[idx];
	}

};

} // namespace velm
