# Gvector

A header-only generic n-dimensional (math) vector.

Similar to `std::valarray`, it allows you to store an array of values of a
specified type, and perform operations with them.

## API Reference

The generic vector is named `gvec` and has two template arguments:

1. `typename T` - the type of each dimension.
2. `size_t N` - the number of dimensions. Must be greater than 0.

This type can be used as `gvec<T, N>`, such as `gvec<int, 3>` for a
3-dimensional vector of integers. In the following documentation, the templates
are hidden for simplicity. Some other elements are hidden, though follow
conventions or are explained later.

### Member Access

 - `gvec.x`, `gvec.y`, `gvec.z`, `gvec.w`

     Direct access to the corresponding dimension, if present.

 - `T& gvec::operator[](size_t n)`,
     `const T& gvec::operator[](size_t n) const`

     These operators allow access to the `n`th dimension. `n` is not checked to
     ensure it references a valid dimension, so the user must do this.

### Member Functions

 - `gvec::gvec(T init = T())` _constructor_

     Initialises all the dimensions of the vector to the passed argument,
     defaulting to `T`'s default constructor if not provided. Requires T to be
     `MoveAssignable` and `DefaultConstructible`.

 - `gvec::gvec(Args&&... args)` _constructor_

     Initialises the dimensions to the corresponding argument. Dimensions that
     do not correspond to an argument are default initialised (Requires `T` to
     be `DefaultConstructible` if this is the case). This constructor is only
     applicable if there are more than 1 argument. Requires `T` to be
     convertible from each of the used types.

 - `gvec<C, N> gvec::cast<C>() const`

     Creates a new vector with type `C` instead of `T`. A vector is default
     initialised, and each dimension is statically cast to `C`. Requires `T` to
     be convertible to `C`, and `C` to be `DefaultConstructible` and
     `MoveAssignable`.

### Non-member Functions

 - `gvec operator+(const gvec& self)`

     Creates a copy of `self`, and returns it. `T` must be `CopyConstructible`.

 - `gvec operator-(gvec copy)`

     Negates every dimension of `copy`. Requires `T` to be `MoveAssignable` and
     have the negation operator.

 - `gvec& operator+=(gvec& self, const gvec& other)`,
     `gvec& operator-=(gvec& self, const gvec& other)`,
     `gvec& operator*=(gvec& self, const gvec& other)`,
     `gvec& operator/=(gvec& self, const gvec& other)`

     Performs compound assignment on each dimension of `self` with the
     corresponding dimension of `other`. The corresponding compound assignment
     operator must be present for `T`.

 - `gvec operator+(gvec left, const gvec& right)`,
     `gvec operator-(gvec left, const gvec& right)`,
     `gvec operator/(gvec left, const gvec& right)`,
     `gvec operator*(gvec left, const gvec& right)`

     Returns the sum/difference/product/quotient of `left` and `right`. This
     done with the compound assignment operators, and as such, requires the
     corresponding one.

 - `bool operator==(const gvec& left, const gvec& right)`,
     `bool operator!=(const gvec& left, const gvec& right)`

     Checks if two vectors are equal, by checking each dimension. It is short
     circuited, the operator returns early if a dimension differ. Requires `T`
     to be `EqualityComparable`.

 - `bool operator<(const gvec& left, const gvec& right)`,
     `bool operator>(const gvec& left, const gvec& right)`,
     `bool operator<=(const gvec& left, const gvec& right)`,
     `bool operator>=(const gvec& left, const gvec& right)`

     Lexicographically (first, then second, and so on) compares two vectors.
     Similar to the equality operators, this is short circuited. Requires `T` to
     be `LessThanComparable`.

## Implementation Reference

The vector is not a class, but in fact a union. This is what allows member
access to the first few dimensions, and still permit more dimensions after that.
However, this meant that the union had to be specialised for N between 0 and 4.
These only had some of the named members. An issue arose from this - a lot of
code was going to be duplicated. To counter this, most of the operators were
made into non-member functions, and the rest were put into a macro.

There is a slight preprocessor hell in `pp_begin.hpp`, which provides macros for
disabling GNU anonymous struct warnings, which were needed in the union. Since
each compiler has a different pragma for storing the state, disabling the
warning, and restoring the previous state, there is a specialisation for each
compiler. More pragmas are then needed to stop these macros from potentially
overriding previous macros. At least it works for Clang, GCC and MSVC.
