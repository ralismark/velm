#pragma once

#include <array>
#include <tuple>

#include "defs.hpp"
#include "utility.hpp"

namespace velm {

template <typename T, unsigned int... N>
struct swizzle_proxy
	: private tied_vector
{
public: // statics

	static constexpr auto dimensions = sizeof...(N);
	using value_type = T;

private:

	std::array<T, tmax<unsigned int, N...>::value + 1> underlying; // used to acess swizzles

public:

	constexpr auto tie() &
	{
		return std::tie(std::get<N>(underlying)...);
	}

	constexpr auto tie() const&
	{
		return std::tie(std::get<N>(underlying)...);
	}

	constexpr auto tie() const&&
	{
		return std::make_tuple(std::get<N>(underlying)...);
	}

	template <typename U,
		std::enable_if_t<is_tied_vector<U>::value, int> = 0>
	constexpr swizzle_proxy& operator=(U&& vec)
	{
		static_assert(std::tuple_size<decltype(this->tie())>::value == std::tuple_size<decltype(vec.tie())>::value,
		              "Ties must be the same size");
		this->tie() = vec.tie();
		return *this;
	}

	template <typename U,
		std::enable_if_t<!is_tied_vector<U>::value, int> = 0>
	constexpr swizzle_proxy& operator=(U&& val)
	{
		this->tie() = make_filled_tuple<dimensions>(val);
		return *this;
	}

	constexpr vector<T, dimensions> operator()() const
	{
		return static_cast<vector<T, dimensions>>(*this);
	}

	constexpr operator vector<T, dimensions>() const
	{
		return vector<T, dimensions>::from_tuple(this->tie());
	}
};

}
