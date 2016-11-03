#pragma once

#include <ostream>
#include <type_traits>

template <typename T, size_t N>
class gvec // Generic vector
{
private: // for operator -> members and static checking
	template <typename T, size_t N>
	struct accessor
	{
		typedef accessor<T, 4> type;
	};

	template <typename T>
	struct accessor<T, 0>
	{
		struct type { };
	};

	template <typename T>
	struct accessor<T, 1>
	{
		struct type { T x; };
	};

	template <typename T>
	struct accessor<T, 2>
	{
		struct type { T x; T y; };
	};

	template <typename T>
	struct accessor<T, 3>
	{
		struct type { T x; T y; T z; };
	};

	template <typename T>
	struct accessor<T, 4>
	{
		struct type { T x; T y; T z; T w; };
	};
private:
	union {
		T vals[N]; // Internal array
		typename accessor<T, N>::type access;
	};
public:
	gvec(T init = T());
	// requires over 1 to stop overriding important functions
	// e.g. copy ctor
	template <typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 1)>>
	gvec(Args&&... args);

	// unary
	gvec<T, N> operator+() const;
	gvec<T, N> operator-() const;

	// binary assignment ops
	gvec<T, N>& operator+=(const gvec<T, N>& other);
	gvec<T, N>& operator-=(const gvec<T, N>& other);
	gvec<T, N>& operator*=(const gvec<T, N>& other);
	gvec<T, N>& operator/=(const gvec<T, N>& other);

	// binary arithmetic ops
	template <typename T, size_t N>
	friend gvec<T, N> operator+(gvec<T, N> left, const gvec<T, N>& right);
	template <typename T, size_t N>
	friend gvec<T, N> operator-(gvec<T, N> self, const gvec<T, N>& other);
	template <typename T, size_t N>
	friend gvec<T, N> operator*(gvec<T, N> left, const gvec<T, N>& right);
	template <typename T, size_t N>
	friend gvec<T, N> operator/(gvec<T, N> self, const gvec<T, N>& other);

	// single value ops
	gvec<T, N>& operator*=(const T& other);
	gvec<T, N>& operator/=(const T& other);

	template <typename T, size_t N>
	friend gvec<T, N> operator*(gvec<T, N> self, const T& other);
	template <typename T, size_t N>
	friend gvec<T, N> operator*(const T& other, gvec<T, N> self);
	template <typename T, size_t N>
	friend gvec<T, N> operator/(gvec<T, N> self, const T& other);
	template <typename T, size_t N>
	friend gvec<T, N> operator/(const T& other, gvec<T, N> self);

	template <typename T, size_t N>
	friend bool operator==(const gvec<T, N>& left, const gvec<T, N>& right);
	template <typename T, size_t N>
	friend bool operator!=(const gvec<T, N>& left, const gvec<T, N>& right);
	template <typename T, size_t N>
	friend bool operator>=(const gvec<T, N>& left, const gvec<T, N>& right);
	template <typename T, size_t N>
	friend bool operator<=(const gvec<T, N>& left, const gvec<T, N>& right);
	template <typename T, size_t N>
	friend bool operator>(const gvec<T, N>& left, const gvec<T, N>& right);
	template <typename T, size_t N>
	friend bool operator<(const gvec<T, N>& left, const gvec<T, N>& right);

	// Access
	typename accessor<T, N>::type* operator->();
	const typename accessor<T, N>::type* operator->() const;

	T& operator[](size_t n);
	const T& operator[](size_t n) const;

	template <typename T, size_t N>
	friend std::ostream& operator<<(std::ostream& os, const gvec<T, N>& gv);

	template <typename C, typename = std::enable_if_t<std::is_convertible<T, C>::value>>
	gvec<C, N> cast() const;

	template <typename C, typename = std::enable_if_t<std::is_convertible<T, C>::value>>
	explicit operator gvec<C, N>() const;
};

template <typename C, typename... Args>
gvec<C, sizeof...(T)> make_vec(Args&&... vals);

#include "gvec.tpp"
