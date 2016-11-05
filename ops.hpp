#pragma once

#include "base.hpp"

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
