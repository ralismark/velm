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
explicit operator gvec<C, N>() const
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
	template <typename C> explicit operator gvec<C, N>() const { gvec<C, N> out; for(size_t i = 0; i < N; ++i) out[i] = static_cast<C>(vals[i]); return out; }

