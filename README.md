# Velm

Velm is a generic vector library which provides the template class
`velm::vector<T, N>`. This supports any type and any number of dimensions.
Additionally, it supports [swizzling][1] using references, which results in no
copies and transparent assignment to the swizzled members.

  [1]: https://en.wikipedia.org/wiki/Swizzling_(computer_graphics)

## Installation

This is a header-only library, so nothing needs to be built. Copy the contents
of include/ into your include directory to install the library.

Include `velm.hpp` to use all off the library. Alternatively, include files in
the velm/ subdirectory for specific components:
 - `velm/vector.hpp`: The core vector class, you probably want this
 - `velm/ops.hpp`: Operator overloads for vectors
 - `velm/funcs.hpp`: GLSL math functions for vectors and scalars


## Getting Started

Everything in the library is in `namespace velm`, such as the core vector class.
By also including `velm/ops.hpp`, most arithmetic operators are usable.

``` cpp
{
	velm::vector<int, 5> a = {1, 2, 3, 4, 5};
	velm::vector<int, 3> b = a.ywz; // b == { 2, 4, 3 }
	int c = (a.xxx + b).xy().x; // c = 1 + 2 = 3
	int d = c + a[4]; // d = 3 + 5 = 8
}
```

> Note: swizzles do not have named members themselves. Call them without
> parameters to convert to a normal vector.

By including `velm/funcs.hpp`, other functions are available.

``` cpp
{
	velm::vector<double, 2> a = { 3, 4 };
	double d = velm::length(a);
	bool x = all(greaterThan(a, 1)); // true
	bool y = none(lessThanEqual(a, 3)); // false
}
```

See header files for additional references.
