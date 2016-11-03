# gvector
A header-only generic n-dimensional (math) vector.

Similar to `std::valarray`, it allows you to store an array of values of a
specified type, and perform operations with them.

## Install

Copy the files in the `include` directory into you include path. Alternatively,
copy both `gvec.hpp` and `gvec.tpp` into the include path.

`gvec.hpp` contains the definitions, white `gvec.tpp` contains the
implementation. Since it's a template class, `gvec.tpp` is included with
`gvec.hpp`. `include/gvec.hpp` contains these two files effectively
concatenated (though with minor changes).

## Reference

Using `T` as the type and `N` as the size,

### Class functions

 - `gvec(T init = T())` _(constructor)_

     Initialise the value of all dimensions to be `init`.

 - `gvec(Args&&... args)` _(constructor)_

     Initialise the values of dimensions to be the corresponding argument. If the
     number of arguments is less than N, the remaining dimensions are default
     initialised. The number of arguments must be under N.

 - `gvec operator+() const`

     Returns a copy of `this`.

 - `gvec operator-() const`

     Returns a negated copy of `*this`. Requires T to have the negation operator.

 - `gvec& operator+=(const gvec& val)`
 - `gvec& operator-=(const gvec& val)`
 - `gvec& operator*=(const gvec& val)`
 - `gvec& operator/=(const gvec& val)`

     Perform operation on `*this`, modifying it. Requires the corresponding
     compound assignment operator for T.

 - `friend gvec operator+(gvec left, const gvec& right)`
 - `friend gvec operator-(gvec left, const gvec& right)`
 - `friend gvec operator*(gvec left, const gvec& right)`
 - `friend gvec operator/(gvec left, const gvec& right)`

     Perform operation on the two arguments, without modifying either. Requires
     the corresponding compound assignment for T.

 - `gvec& operator*=(const T& val)`
 - `gvec& operator/=(const T& val)`

     Overload for multiplying and dividing by a certain value. Equivalent to the
     compound assignment operator, using `gvec(val)` as the argument.

 - `friend gvec operator*(gvec self, const T& other)`
 - `friend gvec operator*(const T& other, gvec self)`
 - `friend gvec operator/(gvec self, const T& other)`
 - `friend gvec operator/(const T& other, gvec self)`

     Overload for multiplication and division by a certain value. Equivalent to the
     arithmetic operators, with `gvec(other)` instead of `other`.

 - `friend bool operator==(const gvec& left, const gvec& right)`
 - `friend bool operator!=(const gvec& left, const gvec& right)`

     Checks if `left` is equal or not equal to `right`. Short circuited, if
     any dimension differs, the ones numerically after it are not accessed.

 - `friend bool operator>(const gvec& left, const gvec& right)`
 - `friend bool operator<(const gvec& left, const gvec& right)`
 - `friend bool operator>=(const gvec& left, const gvec& right)`
 - `friend bool operator<=(const gvec& left, const gvec& right)`

     Lexicographically compares `left` and `right`, that is, compares the first
     dimension, if they are equal, compares the next, and so on. Short
     circuited, if any dimension differ, the ones after it are not accessed.

 - `accessor* operator->()`
 - `const accessor* operator->() const`

     Returns an object which refers to up to the first 4 dimensions of the
     vector, by the letters `x`, `y`, `z`, `w` (in that order), if available.
     Attempted access to dimensions past `N` will result in a compile-time
     error.

 - `T& operator[](size_t n)`
 - `const T& operator[](size_t n) const`

     Access the `n`'th dimension of the vector.

 - `friend std::ostream& operator<<(std::ostream& os, const gvec& gv)`

     Prints `gv` to `os`. The output contains a left bracket (`[`), followed by
     the dimensions of `gv` (using `operator<<`) separated by a comma, then a
     right bracket (`]`).

 - `template <typename C> gvec<C, N> cast() const`

     Create a copy of the vector with elements instead with type `C`. This is
     done by casting. Requires T to be convertible to C (`std::is_convertible`).

 - `template <typename C> explicit operator gvec<C, N>() const`

     Uses cast() to convert the vector to contain dimensions of type C.

### Non-member functions

 - `gvec<C, sizeof...(T)> make_vec(Args&&... vals)`

     Creates a vector of type `C` and the number of dimensions equal to that of
     the number of arguments provided. Each dimension of the resulting vector is
     initialised with the provided arguments.
