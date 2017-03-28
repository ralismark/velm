#pragma once

#include <type_traits>

namespace velm {

template <typename T, unsigned int... N>
struct swizzle_proxy;

template <typename T, unsigned int N,
          template <typename, unsigned int...> typename ProxyGen>
struct vec_base;

template <typename T, unsigned int N>
struct vector;

} // namespace velm

namespace std {

	template <typename T1, typename T2, unsigned int N>
	struct common_type<velm::vector<T1, N>, velm::vector<T2, N>>
	{
		using type = velm::vector<typename std::common_type<T1, T2>::type, N>;
	};

	template <typename T1, typename T2, unsigned int N, unsigned int... Is>
	struct common_type<velm::swizzle_proxy<T1, Is...>, velm::vector<T2, N>>
	{
		using type = std::enable_if_t<(N == sizeof...(Is)),
			velm::vector<typename std::common_type<T1, T2>::type, N>>;
	};

	template <typename T1, typename T2, unsigned int N, unsigned int... Is>
	struct common_type<velm::vector<T1, N>, velm::swizzle_proxy<T2, Is...>>
	{
		using type = std::enable_if_t<(N == sizeof...(Is)),
			velm::vector<typename std::common_type<T1, T2>::type, N>>;
	};

	template <typename T1, typename T2, unsigned int... Is1, unsigned int... Is2>
	struct common_type<velm::swizzle_proxy<T1, Is1...>, velm::swizzle_proxy<T2, Is2...>>
	{
		using type = std::enable_if_t<(sizeof...(Is1) == sizeof...(Is2)),
			velm::vector<typename std::common_type<T1, T2>::type, sizeof...(Is1)>>;
	};

} // namespace std
