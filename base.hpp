#pragma once

#include <type_traits>

#include "pp_begin.hpp"

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

#include "pp_begin.hpp"
