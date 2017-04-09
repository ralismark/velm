#pragma once

#include "utility.hpp"

#include <cmath>

/**
 * \file funcs.hpp
 * \brief named vector/scalar functions
 *
 * Several functions are defined in this file to provide extra functionality.
 * Most of these are equivalent to the GLSL function of the same name, but have
 * better type support (inc. user-defined vectors). At this point, this is
 * incomplete (both in terms of functions and documentation), though many parts
 * are completed.
 *
 * One difference is the negate function, which is equivalent to the GLSL not
 * function. This was named differently as 'not' is a reserved keyword in C++.
 */

namespace velm {

	// logical {{{

	/**
	 * \fn all
	 * \brief check that all elements are true
	 *
	 * This checks that all components of the vector are true.
	 */
	template <typename T, std::enable_if_t<is_tied_vector<T>::value, int> = 0>
	constexpr bool all(T&& vec)
	{
		bool result = true;
		vec_apply(vec.tie(),
			[&] (auto&& x) { return result &= bool(x); });
		return result;
	}

	/**
	 * \fn any
	 * \brief check if any elements are true
	 *
	 * This checks if any component of the vector is true.
	 */
	template <typename T, std::enable_if_t<is_tied_vector<T>::value, int> = 0>
	constexpr bool any(T&& vec)
	{
		bool result = false;
		vec_apply(vec.tie(),
			[&] (auto&& x) { return result |= bool(x); });
		return result;
	}

	/**
	 * \fn none
	 * \brief check that all elements are false
	 *
	 * This checks that all components of the vector are false.
	 */
	template <typename T, std::enable_if_t<is_tied_vector<T>::value, int> = 0>
	constexpr bool none(T&& vec)
	{
		return !any(std::forward<T>(vec));
	}

	/**
	 * \fn negate
	 * \brief returns the component-wise inverse
	 *
	 * This negates (using logical not) each component of the vector, and
	 * returns the result. This is equivalent to the glsl function not, but
	 * 'not' is a reserved keyword in c++.
	 */
	template <typename T, std::enable_if_t<is_tied_vector<T>::value, int> = 0>
	constexpr bool negate(T&& vec)
	{
		return vec_apply(vec.tie(),
			[] (auto&& x) { return !x; });
	}

	// }}}
	// relational {{{

	/**
	 * \fn lessThan
	 * \brief component-wise less than comparison
	 *
	 * Compares the elements of 2 vectors, and creates a boolean vector
	 * where each dimension represents the result of the comparison.
	 * Comparisons between values return a single boolean.
	 */
	template <typename L, typename R, std::enable_if_t<!is_appliable<L, R>::value, int> = 0>
	constexpr bool lessThan(L&& lhs, R&& rhs)
	{
		return lhs < rhs;
	}

	template <typename L, typename R, if_appliable<L, R> = 0>
	constexpr auto lessThan(L&& lhs, R&& rhs)
	{
		return binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
			[] (auto&& a, auto&& b) { return lessThan(a, b); });
	}

	/**
	 * \fn lessThanEqual
	 * \brief component-wise less than or equal comparison
	 *
	 * Compares the elements of 2 vectors, and creates a boolean vector
	 * where each dimension represents the result of the comparison.
	 * Comparisons between values return a single boolean.
	 */
	template <typename L, typename R, std::enable_if_t<!is_appliable<L, R>::value, int> = 0>
	constexpr bool lessThanEqual(L&& lhs, R&& rhs)
	{
		return lhs <= rhs;
	}

	template <typename L, typename R, if_appliable<L, R> = 0>
	constexpr auto lessThanEqual(L&& lhs, R&& rhs)
	{
		return binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
			[] (auto&& a, auto&& b) { return lessThanEqual(a, b); });
	}

	/**
	 * \fn greaterThan
	 * \brief component-wise greater than comparison
	 *
	 * Compares the elements of 2 vectors, and creates a boolean vector
	 * where each dimension represents the result of the comparison.
	 * Comparisons between values return a single boolean.
	 */
	template <typename L, typename R, std::enable_if_t<!is_appliable<L, R>::value, int> = 0>
	constexpr bool greaterThan(L&& lhs, R&& rhs)
	{
		return lhs > rhs;
	}

	template <typename L, typename R, if_appliable<L, R> = 0>
	constexpr auto greaterThan(L&& lhs, R&& rhs)
	{
		return binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
			[] (auto&& a, auto&& b) { return greaterThan(a, b); });
	}

	/**
	 * \fn greaterThanEqual
	 * \brief component-wise greater than or equal comparison
	 *
	 * Compares the elements of 2 vectors, and creates a boolean vector
	 * where each dimension represents the result of the comparison.
	 * Comparisons between values return a single boolean.
	 */
	template <typename L, typename R, std::enable_if_t<!is_appliable<L, R>::value, int> = 0>
	constexpr bool greaterThanEqual(L&& lhs, R&& rhs)
	{
		return lhs >= rhs;
	}

	template <typename L, typename R, if_appliable<L, R> = 0>
	constexpr auto greaterThanEqual(L&& lhs, R&& rhs)
	{
		return binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
			[] (auto&& a, auto&& b) { return greaterThanEqual(a, b); });
	}

	/**
	 * \fn equal
	 * \brief component-wise equality comparison
	 *
	 * Compares the elements of 2 vectors, and creates a boolean vector
	 * where each dimension represents the result of the comparison.
	 * Comparisons between values return a single boolean.
	 */
	template <typename L, typename R, std::enable_if_t<!is_appliable<L, R>::value, int> = 0>
	constexpr bool equal(L&& lhs, R&& rhs)
	{
		return lhs == rhs;
	}

	template <typename L, typename R, if_appliable<L, R> = 0>
	constexpr auto equal(L&& lhs, R&& rhs)
	{
		return binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
			[] (auto&& a, auto&& b) { return equal(a, b); });
	}

	/**
	 * \fn equal
	 * \brief component-wise inequality comparison
	 *
	 * Compares the elements of 2 vectors, and creates a boolean vector
	 * where each dimension represents the result of the comparison.
	 * Comparisons between values return a single boolean.
	 */
	template <typename L, typename R, std::enable_if_t<!is_appliable<L, R>::value, int> = 0>
	constexpr bool notEqual(L&& lhs, R&& rhs)
	{
		return lhs != rhs;
	}

	template <typename L, typename R, if_appliable<L, R> = 0>
	constexpr auto notEqual(L&& lhs, R&& rhs)
	{
		return binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
			[] (auto&& a, auto&& b) { return notEqual(a, b); });
	}


	// }}}
	// geometric {{{

	/**
	 * \fn dot
	 * \brief dot product of 2 vectors
	 *
	 * This calculates the sum of the product of each pair of components,
	 * resulting in the dot product.
	 */
	template <typename L, typename R, if_appliable<L, R> = 0>
	constexpr auto dot(L&& lhs, R&& rhs)
	{
		using out_type = std::common_type_t<typename std::decay_t<L>::value_type, typename std::decay_t<L>::value_type>;
		out_type sum = 0;
		binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
			[&] (auto&& a, auto&& b) { sum += a * b; return 0; });
		return sum;
	}

	template <typename L, typename R, std::enable_if_t<!is_appliable<L, R>::value, int> = 0>
	constexpr auto dot(L&& lhs, R&& rhs)
	{
		return lhs * rhs;
	}

	/**
	 * \fn length
	 * \brief length of a vector
	 *
	 * This finds the length of a vector from the origin. While still
	 * working of vectors, this also works with scalars (where it is
	 * identical to abs).
	 */
	template <typename T>
	auto length(T&& val)
	{
		return std::sqrt(dot(val, val));
	}

	/**
	 * \fn distance
	 * \brief distance between two points
	 *
	 * This returns the distance between 2 point i.e. length(p0 - p1).
	 */
	template <typename L, typename R>
	auto distance(L&& p0, R&& p1)
	{
		return length(p0 - p1);
	}

	/**
	 * \fn normalize
	 * \brief unit vector in the same direction as the original vector
	 *
	 * This returns a vector with the same direction as its parameter,  but
	 * with length 1.
	 */
	template <typename T>
	auto normalize(T&& val)
	{
		return val / length(val);
	}

	/**
	 * \fn faceforward
	 * \brief a vector pointing in the same direction as another
	 *
	 * Orients a vector n to point away from a surface as defined by its
	 * normal (nref).
	 */
	template <typename N, typename I, typename R>
	constexpr auto faceforward(N&& n, I&& i, R&& nref)
	{
		return dot(nref, i) < 0 ? n : -n;
	}

	/**
	 * \fn reflect
	 * \brief calculate the reflection direction for an incident vector
	 *
	 * For a given incident vector i and surface normal n this returns
	 * the reflection direction. n must be normalized for the desired
	 * result.
	 */
	template <typename I, typename N>
	constexpr auto reflect(I&& i, N&& n)
	{
		return i - 2 * dot(n, i) * n;
	}

	// }}}












	/**
	 * \fn abs
	 * \brief get the absolute value
	 *
	 * This gets the absolute value of the parameter. This is
	 * component-wise if the parameter is a vector.
	 */
	template <typename T, std::enable_if_t<!is_tied_vector<T>::value, int> = 0>
	constexpr auto abs(T&& val)
	{
		return val < 0 ? val : -val;
	}

	template <typename T, std::enable_if_t<is_tied_vector<T>::value, int> = 0>
	constexpr auto abs(T&& vec)
	{
		return vec_apply(vec.tie(),
			[] (auto&& x) { return abs(x); });
	}


	/**
	 * \fn min
	 * \brief smallest value of two
	 *
	 * TODO
	 */
	template <typename L, typename R, std::enable_if_t<!is_appliable<L, R>::value, int> = 0>
	constexpr auto min(L&& lhs, R&& rhs)
	{
		return lhs < rhs ? lhs : rhs;
	}

	template <typename L, typename R, if_appliable<L, R> = 0>
	constexpr auto min(L&& lhs, R&& rhs)
	{
		return binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
			[] (auto&& a, auto&& b) { return min(a, b); });
	}

	template <typename L, typename R, std::enable_if_t<!is_appliable<L, R>::value, int> = 0>
	constexpr auto max(L&& lhs, R&& rhs)
	{
		return lhs > rhs ? lhs : rhs;
	}

	template <typename L, typename R, velm::if_appliable<L, R> = 0>
	constexpr auto max(L&& lhs, R&& rhs)
	{
		return binary_apply(std::forward<L>(lhs), std::forward<R>(rhs),
			[] (auto&& a, auto&& b) { return max(a, b); });
	}

	template <typename T, typename L, typename H>
	constexpr auto clamp(T&& val, L&& low, H&& high)
	{
		return min(max(val, low), high);
	}

	template <typename A, typename B, typename WB>
	constexpr auto mix(A&& a, B&& b, WB&& wb)
	{
		return a * (A(1) - wb) + b * wb;
	}

} // namespace velm
