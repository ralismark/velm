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
	operator gvec<C, N>() const;
};

// --- implementation ---

template <typename C, typename... T>
gvec<C, sizeof...(T)> make_vec(T... vals);

template <typename T, size_t N>
gvec<T, N>::gvec(T init)
{
	for(auto&& it : vals) {
		it = init;
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
	for(auto&& it : copy.vals) {
		it = -it;
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
		vals[i] *= other.vals[i];
	}
	return *this;
}

template <typename T, size_t N>
gvec<T, N>& gvec<T, N>::operator/=(const T& other)
{
	for(size_t i = 0; i < N; ++i) {
		vals[i] /= other.vals[i];
	}
	return *this;
}

template <typename T, size_t N>
gvec<T, N> operator*(gvec<T, N> self, const T& other)
{
	return self *= other;
}

template <typename T, size_t N>
gvec<T, N> operator*(const T& other, gvec<T, N> self)
{
	return self *= other;
}

template <typename T, size_t N>
gvec<T, N> operator/(gvec<T, N> self, const T& other)
{
	return self /= other;
}

template <typename T, size_t N>
gvec<T, N> operator/(const T& other, gvec<T, N> self)
{
	for(auto&& it : self.vals) {
		it = other / it;
	}
	return self;
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
	bool first = true;
	for(auto it : gv.vals) {
		os << (first ? "" : ", ") << it;
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
		out[i] = static_cast<C>(vals[i]);
	}
	return out;
}

template <typename T, size_t N>
template <typename C, typename>
gvec<T, N>::operator gvec<C, N>() const
{
	return this->cast<C>();
}

template <typename C, typename... Args>
gvec<C, sizeof...(Args)> make_vec(Args&&... vals)
{
	return gvec<C, sizeof...(T)>(vals...);
}
