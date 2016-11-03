#pragma once

#include "gvec.hpp"

template <typename T, size_t N>
gvec<T, N>::gvec(T init)
{
	for(size_t i = 0; i < N; ++i) {
		vals[i] = init;
	}
}

template <typename T, size_t N>
template <typename... Args, typename>
gvec<T, N>::gvec(Args&&... args)
	: vals{args...}
{ ; }

template <typename T, size_t N>
gvec<T, N> gvec<T, N>::operator+() const
{
	return *this;
}

template <typename T, size_t N>
gvec<T, N> gvec<T, N>::operator-() const
{
	auto copy = *this;
	for(size_t i = 0; i < N; ++i) {
		copy.vals[i] = -copy.vals[i];
	}
	return copy;
}

template <typename T, size_t N>
gvec<T, N>& gvec<T, N>::operator+=(const gvec<T, N>& other)
{
	for(size_t i = 0; i < N; ++i) {
		vals[i] += other.vals[i];
	}
	return *this;
}

template <typename T, size_t N>
gvec<T, N>& gvec<T, N>::operator-=(const gvec<T, N>& other)
{
	for(size_t i = 0; i < N; ++i) {
		vals[i] -= other.vals[i];
	}
	return *this;
}

template <typename T, size_t N>
gvec<T, N>& gvec<T, N>::operator*=(const gvec<T, N>& other)
{
	for(size_t i = 0; i < N; ++i) {
		vals[i] *= other.vals[i];
	}
	return *this;
}

template <typename T, size_t N>
gvec<T, N>& gvec<T, N>::operator/=(const gvec<T, N>& other)
{
	for(size_t i = 0; i < N; ++i) {
		vals[i] /= other.vals[i];
	}
	return *this;
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
gvec<T, N>& gvec<T, N>::operator*=(const T& other)
{
	for(size_t i = 0; i < N; ++i) {
		vals[i] *= other;
	}
	return *this;
}

template <typename T, size_t N>
gvec<T, N>& gvec<T, N>::operator/=(const T& other)
{
	for(size_t i = 0; i < N; ++i) {
		vals[i] /= other;
	}
	return *this;
}

template <typename T, size_t N>
gvec<T, N> operator*(gvec<T, N> self, const T& other)
{
	return self *= other;
}

template <typename T, size_t N>
gvec<T, N> operator/(gvec<T, N> self, const T& other)
{
	return self /= other;
}

template <typename T, size_t N>
gvec<T, N> operator*(const T& other, gvec<T, N> self)
{
	return self *= other;
}

template <typename T, size_t N>
bool operator==(const gvec<T, N>& left, const gvec<T, N>& right)
{
	for(size_t i = 0; i < N; ++i) {
		if(left.vals[i] != right.vals[i]) {
			return false;
		}
	}
	return true;
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
		if(left.vals[i] != right.vals[i]) {
			return left.vals[i] < right.vals[i];
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

template <typename T, size_t N>
typename gvec<T, N>::template accessor<T, N>::type* gvec<T, N>::operator->()
{
	return &access;
}

template <typename T, size_t N>
const typename gvec<T, N>::template accessor<T, N>::type* gvec<T, N>::operator->() const
{
	return &access;
}

template <typename T, size_t N>
const T& gvec<T, N>::operator[](size_t n) const
{
	return vals[n];
}

template <typename T, size_t N>
T& gvec<T, N>::operator[](size_t n)
{
	return vals[n];
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const gvec<T, N>& gv)
{
	os << "[ ";
	for(size_t i = 0; i < N; ++i) {
		if(i != 0) {
			os << ", ";
		}
		os << gv[i];
	}
	os << " ]";
	return os;
}

template <typename T, size_t N>
template <typename C, typename>
gvec<C, N> gvec<T, N>::cast() const
{
	gvec<C, N> out;
	for(size_t i = 0; i < N; ++i) {
		out[i] = vals[i];
	}
	return out;
}

template <typename T, size_t N>
template <typename C, typename>
gvec<T, N>::operator gvec<C, N>() const
{
	return this->cast<C>();
}

template <typename O, typename... Args>
gvec<O, sizeof...(Args)> make_vec(Args&&... vals)
{
	gvec<O, sizeof...(T)> gv = {vals...};
	return gv;
}
