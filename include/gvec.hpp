#pragma once

// --- begin: base.hpp ---

#include <type_traits>

// --- begin: pp_begin.hpp ---

/*
 * Preprocessor definitions (begin section)
 *
 * This file provides _warn_protect_begin_ and _warn_protect_end_. These macros
 * expand to be pragmas which safely hide warnings. In this case, these macros
 * hide anonymous structs [-Wgnu-anonymous-struct].
 *
 * It also provides _vec_base_ops_, which expands to the methods needed for all
 * specialisations of the union.
 *
 * pp_end.hpp must be included after all uses of the macros, as it restores the
 * original definitions for those macros.
 */

// stop existing macros from begin overwritten
#pragma push_macro("_warn_protect_begin_")
#pragma push_macro("_warn_protect_end_")
#pragma push_macro("_vec_base_ops_")

// stop warnings about overriding macros
#ifdef _warn_protect_begin_
#undef _warn_protect_begin_
#endif

#ifdef _warn_protect_end_
#undef _warn_protect_end_
#endif

#ifdef _vec_base_ops_
#undef _vec_base_ops_
#endif

/*
 * Since differnt compilers use different pragmas for temporarily disabling
 * warnings, we need special definitions for each compiler. However, the
 * generally do the same thing (though with different wording)
 */
#if defined(__clang__)

#	define _warn_protect_begin_ \
		_Pragma("clang diagnostic push") \
		_Pragma("clang diagnostic ignored \"-Wgnu-anonymous-struct\"")

#	define _warn_protect_end_ \
		_Pragma("clang diagnostic pop")

#elif defined(__GNUC__)

#	define _warn_protect_begin_ \
		_Pragma("GCC diagnostic push") \
		_Pragma("GCC diagnostic ignored \"-Wpedantic\"")

#	define _warn_protect_end_ \
		_Pragma("GCC diagnostic pop")

#elif defined(_MSC_VER)

#	define _warn_protect_begin_ \
		_Pragma("warning(push)") \
		_Pragma("warning(disable: 4201)")

#	define _warn_protect_end_ \
		_Pragma("warning(pop)")

#else // unknown or non-conventional compiler, keep warnings

#	define _warn_protect_begin_ // blank
#	define _warn_protect_end_ // blank

#endif

/*
 * _vec_base_ops_ - default vector ops
 *
 * Since we're specialising a union, the methods in it will need to be copied
 * for each specialisation. As a result, this macro was created.
 *
 * Expanded, it looks like this:

gvec(T init = T())
{
	for(auto&& it : vals) {
		it = init;
	}
}

template <typename... Args, typename = std::enable_if<(sizeof...(Args) > 1)>>
gvec(Args&&... args)
	: vals{args...}
{ ; }

T& operator[](size_t n)
{
	return vals[n];
}

const T& operator[](size_t n) const
{
	return vals[n];
}

template <typename C>
gvec<C, N> cast() const
{
	gvec<C, N> out;
	for(size_t i = 0; i < N; ++i) {
		out[i] = static_cast<C>(vals[i]);
	}
	return out;
}

 * However, that's quite long, so it's been contracted into 4 lines.
 */


#define _vec_base_ops_(N) \
	gvec(T init = T()) { for(auto&& it : vals) it = init; } \
	template <typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 1)>> gvec(Args&&... args) : vals{args...} { ; } \
	T& operator[](size_t n) { return vals[n]; } \
	const T& operator[](size_t n) const { return vals[n]; } \
	template <typename C> gvec<C, N> cast() const { gvec<C, N> out; for(size_t i = 0; i < N; ++i) out[i] = static_cast<C>(vals[i]); return out; }

// --- end: pp_begin.hpp ---

/*
 * Base union definitions and declarations
 *
 * This file contains the base declarations and definitions for the gvec union,
 * which is specialised for each number of dimensions under 4. Several macros
 * (beginning and ending with an underscore) are used here; See pp_begin.hpp
 * for an explanation.
 *
 * Each union is specialised for the anonymous struct inside, which contains
 * letter accessors for up to the first 4 dimensions of a vector. The letter
 * 'x', 'y', 'z', and 'w' are used (in that order) for these dimensions, if
 * present.
 */

template <typename T, size_t N>
union gvec {
	// do not support N == 0
	static_assert(N > 0, "vector must have at least 1 dimension");
private:
	T vals[N];
public:
_warn_protect_begin_
	struct {
		T x, y, z, w;
	};
_warn_protect_end_

_vec_base_ops_(N)
};

template <typename T>
union gvec<T, 1> {
private:
	T vals[1];
public:
_warn_protect_begin_
	struct {
		T x;
	};
_warn_protect_end_

_vec_base_ops_(1)
};

template <typename T>
union gvec<T, 2> {
private:
	T vals[2];
public:
_warn_protect_begin_
	struct {
		T x, y;
	};
_warn_protect_end_

_vec_base_ops_(2)
};

template <typename T>
union gvec<T, 3> {
private:
	T vals[3];
public:
_warn_protect_begin_
	struct {
		T x, y, z;
	};
_warn_protect_end_

_vec_base_ops_(3)
};

// --- begin: pp_end.hpp ---

/*
 * Preprocessor definitions (end section)
 *
 * This is the file accompanying pp_guard_begin.hpp, which restores the
 * original definitions for __warn_protect_begin and __warn_protect_end.
 *
 * See pp_guard_begin.hpp for more detail.
 */

#pragma pop_macro("_warn_protect_begin_")
#pragma pop_macro("_warn_protect_end_")
#pragma pop_macro("_vec_base_ops_")

// --- end: pp_end.hpp ---

// --- end: base.hpp ---

// --- begin: ops.hpp ---

/*
 * Vector operators
 *
 * The operators for vectors are defined in this file. To avoid a further
 * template specialisation mess, all of them are defined as non-member
 * functions, relying on the subscript operator for access.
 */

template <typename T, size_t N>
gvec<T, N> operator+(const gvec<T, N>& self)
{
	return self;
}

template <typename T, size_t N>
gvec<T, N> operator-(gvec<T, N> cpy)
{
	for(size_t i = 0; i < N; ++i) {
		cpy[i] = -cpy[i];
	}
	return cpy;
}

template <typename T, size_t N>
gvec<T, N>& operator+=(gvec<T, N>& self, const gvec<T, N>& other)
{
	for(size_t i = 0; i < N; ++i) {
		self[i] += other[i];
	}
	return self;
}

template <typename T, size_t N>
gvec<T, N>& operator-=(gvec<T, N>& self, const gvec<T, N>& other)
{
	for(size_t i = 0; i < N; ++i) {
		self[i] -= other[i];
	}
	return self;
}

template <typename T, size_t N>
gvec<T, N>& operator*=(gvec<T, N>& self, const gvec<T, N>& other)
{
	for(size_t i = 0; i < N; ++i) {
		self[i] *= other[i];
	}
	return self;
}

template <typename T, size_t N>
gvec<T, N>& operator/=(gvec<T, N>& self, const gvec<T, N>& other)
{
	for(size_t i = 0; i < N; ++i) {
		self[i] /= other[i];
	}
	return self;
}

template <typename T, size_t N>
gvec<T, N> operator+(gvec<T, N> left, const gvec<T, N>& right)
{
	return left += right;
}

template <typename T, size_t N>
gvec<T, N> operator-(gvec<T, N> left, const gvec<T, N>& right)
{
	return left -= right;
}

template <typename T, size_t N>
gvec<T, N> operator*(gvec<T, N> left, const gvec<T, N>& right)
{
	return left *= right;
}

template <typename T, size_t N>
gvec<T, N> operator/(gvec<T, N> left, const gvec<T, N>& right)
{
	return left /= right;
}

template <typename T, size_t N>
bool operator==(const gvec<T, N>& left, const gvec<T, N>& right)
{
	for(size_t i = 0; i < N; ++i) {
		// using weird != to fit EqualityComparable
		if(!(left[i] == right[i])) {
			return true;
		}
	}
	return false;
}

template <typename T, size_t N>
bool operator!=(const gvec<T, N>& left, const gvec<T, N>& right)
{
	return !(left == right);
}

template <typename T, size_t N>
bool operator<(const gvec<T, N>& left, const gvec<T, N>& right)
{
	for(size_t i = 0; i < N; ++i) {
		// using weird != to fit LessThanComparable
		if(left[i] < right[i] || right[i] < left[i]) {
			return left[i] < right[i];
		}
	}
	return false;
}

template <typename T, size_t N>
bool operator>(const gvec<T, N>& left, const gvec<T, N>& right)
{
	return right < left;
}

template <typename T, size_t N>
bool operator<=(const gvec<T, N>& left, const gvec<T, N>& right)
{
	return !(left > right);
}

template <typename T, size_t N>
bool operator>=(const gvec<T, N>& left, const gvec<T, N>& right)
{
	return !(left < right);
}

// --- end: ops.hpp ---
