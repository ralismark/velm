#pragma once

#include <array>

/**
 * \file
 * \brief base container definitions
 *
 * This file defines the struct vec_base, which is used to create the swizzle
 * members. Additionally, this simplifies the actual vector class definition,
 * which would require overloads for each size otherwise (as well as
 * reimplementing the member function).
 *
 * vec_base requires several language extensions (e.g. anonymous structs in
 * unions). While supported by major compilers, they still issue a warning.
 * These are suppressed with pragmas.
 */

#if defined(__llvm__)
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
	#pragma clang diagnostic ignored "-Wnested-anon-types"
#elif defined(_MSC_VER)
	#pragma warning(push)
	#pragma warning(disable: 4201)
#elif defined(__GNUC__)
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wpedantic"
#endif

namespace velm {

template <typename T, unsigned int N, template <typename, unsigned int...> typename ProxyGen>
struct vec_base
{
	union {
		std::array<T, N> data;
		struct {
			T x, y, z, w;
		};

		// {{{
		ProxyGen<T, 0, 0, 0, 0> xxxx;
		ProxyGen<T, 0, 0, 0, 1> xxxy;
		ProxyGen<T, 0, 0, 0, 2> xxxz;
		ProxyGen<T, 0, 0, 0, 3> xxxw;
		ProxyGen<T, 0, 0, 1, 0> xxyx;
		ProxyGen<T, 0, 0, 1, 1> xxyy;
		ProxyGen<T, 0, 0, 1, 2> xxyz;
		ProxyGen<T, 0, 0, 1, 3> xxyw;
		ProxyGen<T, 0, 0, 2, 0> xxzx;
		ProxyGen<T, 0, 0, 2, 1> xxzy;
		ProxyGen<T, 0, 0, 2, 2> xxzz;
		ProxyGen<T, 0, 0, 2, 3> xxzw;
		ProxyGen<T, 0, 0, 3, 0> xxwx;
		ProxyGen<T, 0, 0, 3, 1> xxwy;
		ProxyGen<T, 0, 0, 3, 2> xxwz;
		ProxyGen<T, 0, 0, 3, 3> xxww;
		ProxyGen<T, 0, 1, 0, 0> xyxx;
		ProxyGen<T, 0, 1, 0, 1> xyxy;
		ProxyGen<T, 0, 1, 0, 2> xyxz;
		ProxyGen<T, 0, 1, 0, 3> xyxw;
		ProxyGen<T, 0, 1, 1, 0> xyyx;
		ProxyGen<T, 0, 1, 1, 1> xyyy;
		ProxyGen<T, 0, 1, 1, 2> xyyz;
		ProxyGen<T, 0, 1, 1, 3> xyyw;
		ProxyGen<T, 0, 1, 2, 0> xyzx;
		ProxyGen<T, 0, 1, 2, 1> xyzy;
		ProxyGen<T, 0, 1, 2, 2> xyzz;
		ProxyGen<T, 0, 1, 2, 3> xyzw;
		ProxyGen<T, 0, 1, 3, 0> xywx;
		ProxyGen<T, 0, 1, 3, 1> xywy;
		ProxyGen<T, 0, 1, 3, 2> xywz;
		ProxyGen<T, 0, 1, 3, 3> xyww;
		ProxyGen<T, 0, 2, 0, 0> xzxx;
		ProxyGen<T, 0, 2, 0, 1> xzxy;
		ProxyGen<T, 0, 2, 0, 2> xzxz;
		ProxyGen<T, 0, 2, 0, 3> xzxw;
		ProxyGen<T, 0, 2, 1, 0> xzyx;
		ProxyGen<T, 0, 2, 1, 1> xzyy;
		ProxyGen<T, 0, 2, 1, 2> xzyz;
		ProxyGen<T, 0, 2, 1, 3> xzyw;
		ProxyGen<T, 0, 2, 2, 0> xzzx;
		ProxyGen<T, 0, 2, 2, 1> xzzy;
		ProxyGen<T, 0, 2, 2, 2> xzzz;
		ProxyGen<T, 0, 2, 2, 3> xzzw;
		ProxyGen<T, 0, 2, 3, 0> xzwx;
		ProxyGen<T, 0, 2, 3, 1> xzwy;
		ProxyGen<T, 0, 2, 3, 2> xzwz;
		ProxyGen<T, 0, 2, 3, 3> xzww;
		ProxyGen<T, 0, 3, 0, 0> xwxx;
		ProxyGen<T, 0, 3, 0, 1> xwxy;
		ProxyGen<T, 0, 3, 0, 2> xwxz;
		ProxyGen<T, 0, 3, 0, 3> xwxw;
		ProxyGen<T, 0, 3, 1, 0> xwyx;
		ProxyGen<T, 0, 3, 1, 1> xwyy;
		ProxyGen<T, 0, 3, 1, 2> xwyz;
		ProxyGen<T, 0, 3, 1, 3> xwyw;
		ProxyGen<T, 0, 3, 2, 0> xwzx;
		ProxyGen<T, 0, 3, 2, 1> xwzy;
		ProxyGen<T, 0, 3, 2, 2> xwzz;
		ProxyGen<T, 0, 3, 2, 3> xwzw;
		ProxyGen<T, 0, 3, 3, 0> xwwx;
		ProxyGen<T, 0, 3, 3, 1> xwwy;
		ProxyGen<T, 0, 3, 3, 2> xwwz;
		ProxyGen<T, 0, 3, 3, 3> xwww;
		ProxyGen<T, 1, 0, 0, 0> yxxx;
		ProxyGen<T, 1, 0, 0, 1> yxxy;
		ProxyGen<T, 1, 0, 0, 2> yxxz;
		ProxyGen<T, 1, 0, 0, 3> yxxw;
		ProxyGen<T, 1, 0, 1, 0> yxyx;
		ProxyGen<T, 1, 0, 1, 1> yxyy;
		ProxyGen<T, 1, 0, 1, 2> yxyz;
		ProxyGen<T, 1, 0, 1, 3> yxyw;
		ProxyGen<T, 1, 0, 2, 0> yxzx;
		ProxyGen<T, 1, 0, 2, 1> yxzy;
		ProxyGen<T, 1, 0, 2, 2> yxzz;
		ProxyGen<T, 1, 0, 2, 3> yxzw;
		ProxyGen<T, 1, 0, 3, 0> yxwx;
		ProxyGen<T, 1, 0, 3, 1> yxwy;
		ProxyGen<T, 1, 0, 3, 2> yxwz;
		ProxyGen<T, 1, 0, 3, 3> yxww;
		ProxyGen<T, 1, 1, 0, 0> yyxx;
		ProxyGen<T, 1, 1, 0, 1> yyxy;
		ProxyGen<T, 1, 1, 0, 2> yyxz;
		ProxyGen<T, 1, 1, 0, 3> yyxw;
		ProxyGen<T, 1, 1, 1, 0> yyyx;
		ProxyGen<T, 1, 1, 1, 1> yyyy;
		ProxyGen<T, 1, 1, 1, 2> yyyz;
		ProxyGen<T, 1, 1, 1, 3> yyyw;
		ProxyGen<T, 1, 1, 2, 0> yyzx;
		ProxyGen<T, 1, 1, 2, 1> yyzy;
		ProxyGen<T, 1, 1, 2, 2> yyzz;
		ProxyGen<T, 1, 1, 2, 3> yyzw;
		ProxyGen<T, 1, 1, 3, 0> yywx;
		ProxyGen<T, 1, 1, 3, 1> yywy;
		ProxyGen<T, 1, 1, 3, 2> yywz;
		ProxyGen<T, 1, 1, 3, 3> yyww;
		ProxyGen<T, 1, 2, 0, 0> yzxx;
		ProxyGen<T, 1, 2, 0, 1> yzxy;
		ProxyGen<T, 1, 2, 0, 2> yzxz;
		ProxyGen<T, 1, 2, 0, 3> yzxw;
		ProxyGen<T, 1, 2, 1, 0> yzyx;
		ProxyGen<T, 1, 2, 1, 1> yzyy;
		ProxyGen<T, 1, 2, 1, 2> yzyz;
		ProxyGen<T, 1, 2, 1, 3> yzyw;
		ProxyGen<T, 1, 2, 2, 0> yzzx;
		ProxyGen<T, 1, 2, 2, 1> yzzy;
		ProxyGen<T, 1, 2, 2, 2> yzzz;
		ProxyGen<T, 1, 2, 2, 3> yzzw;
		ProxyGen<T, 1, 2, 3, 0> yzwx;
		ProxyGen<T, 1, 2, 3, 1> yzwy;
		ProxyGen<T, 1, 2, 3, 2> yzwz;
		ProxyGen<T, 1, 2, 3, 3> yzww;
		ProxyGen<T, 1, 3, 0, 0> ywxx;
		ProxyGen<T, 1, 3, 0, 1> ywxy;
		ProxyGen<T, 1, 3, 0, 2> ywxz;
		ProxyGen<T, 1, 3, 0, 3> ywxw;
		ProxyGen<T, 1, 3, 1, 0> ywyx;
		ProxyGen<T, 1, 3, 1, 1> ywyy;
		ProxyGen<T, 1, 3, 1, 2> ywyz;
		ProxyGen<T, 1, 3, 1, 3> ywyw;
		ProxyGen<T, 1, 3, 2, 0> ywzx;
		ProxyGen<T, 1, 3, 2, 1> ywzy;
		ProxyGen<T, 1, 3, 2, 2> ywzz;
		ProxyGen<T, 1, 3, 2, 3> ywzw;
		ProxyGen<T, 1, 3, 3, 0> ywwx;
		ProxyGen<T, 1, 3, 3, 1> ywwy;
		ProxyGen<T, 1, 3, 3, 2> ywwz;
		ProxyGen<T, 1, 3, 3, 3> ywww;
		ProxyGen<T, 2, 0, 0, 0> zxxx;
		ProxyGen<T, 2, 0, 0, 1> zxxy;
		ProxyGen<T, 2, 0, 0, 2> zxxz;
		ProxyGen<T, 2, 0, 0, 3> zxxw;
		ProxyGen<T, 2, 0, 1, 0> zxyx;
		ProxyGen<T, 2, 0, 1, 1> zxyy;
		ProxyGen<T, 2, 0, 1, 2> zxyz;
		ProxyGen<T, 2, 0, 1, 3> zxyw;
		ProxyGen<T, 2, 0, 2, 0> zxzx;
		ProxyGen<T, 2, 0, 2, 1> zxzy;
		ProxyGen<T, 2, 0, 2, 2> zxzz;
		ProxyGen<T, 2, 0, 2, 3> zxzw;
		ProxyGen<T, 2, 0, 3, 0> zxwx;
		ProxyGen<T, 2, 0, 3, 1> zxwy;
		ProxyGen<T, 2, 0, 3, 2> zxwz;
		ProxyGen<T, 2, 0, 3, 3> zxww;
		ProxyGen<T, 2, 1, 0, 0> zyxx;
		ProxyGen<T, 2, 1, 0, 1> zyxy;
		ProxyGen<T, 2, 1, 0, 2> zyxz;
		ProxyGen<T, 2, 1, 0, 3> zyxw;
		ProxyGen<T, 2, 1, 1, 0> zyyx;
		ProxyGen<T, 2, 1, 1, 1> zyyy;
		ProxyGen<T, 2, 1, 1, 2> zyyz;
		ProxyGen<T, 2, 1, 1, 3> zyyw;
		ProxyGen<T, 2, 1, 2, 0> zyzx;
		ProxyGen<T, 2, 1, 2, 1> zyzy;
		ProxyGen<T, 2, 1, 2, 2> zyzz;
		ProxyGen<T, 2, 1, 2, 3> zyzw;
		ProxyGen<T, 2, 1, 3, 0> zywx;
		ProxyGen<T, 2, 1, 3, 1> zywy;
		ProxyGen<T, 2, 1, 3, 2> zywz;
		ProxyGen<T, 2, 1, 3, 3> zyww;
		ProxyGen<T, 2, 2, 0, 0> zzxx;
		ProxyGen<T, 2, 2, 0, 1> zzxy;
		ProxyGen<T, 2, 2, 0, 2> zzxz;
		ProxyGen<T, 2, 2, 0, 3> zzxw;
		ProxyGen<T, 2, 2, 1, 0> zzyx;
		ProxyGen<T, 2, 2, 1, 1> zzyy;
		ProxyGen<T, 2, 2, 1, 2> zzyz;
		ProxyGen<T, 2, 2, 1, 3> zzyw;
		ProxyGen<T, 2, 2, 2, 0> zzzx;
		ProxyGen<T, 2, 2, 2, 1> zzzy;
		ProxyGen<T, 2, 2, 2, 2> zzzz;
		ProxyGen<T, 2, 2, 2, 3> zzzw;
		ProxyGen<T, 2, 2, 3, 0> zzwx;
		ProxyGen<T, 2, 2, 3, 1> zzwy;
		ProxyGen<T, 2, 2, 3, 2> zzwz;
		ProxyGen<T, 2, 2, 3, 3> zzww;
		ProxyGen<T, 2, 3, 0, 0> zwxx;
		ProxyGen<T, 2, 3, 0, 1> zwxy;
		ProxyGen<T, 2, 3, 0, 2> zwxz;
		ProxyGen<T, 2, 3, 0, 3> zwxw;
		ProxyGen<T, 2, 3, 1, 0> zwyx;
		ProxyGen<T, 2, 3, 1, 1> zwyy;
		ProxyGen<T, 2, 3, 1, 2> zwyz;
		ProxyGen<T, 2, 3, 1, 3> zwyw;
		ProxyGen<T, 2, 3, 2, 0> zwzx;
		ProxyGen<T, 2, 3, 2, 1> zwzy;
		ProxyGen<T, 2, 3, 2, 2> zwzz;
		ProxyGen<T, 2, 3, 2, 3> zwzw;
		ProxyGen<T, 2, 3, 3, 0> zwwx;
		ProxyGen<T, 2, 3, 3, 1> zwwy;
		ProxyGen<T, 2, 3, 3, 2> zwwz;
		ProxyGen<T, 2, 3, 3, 3> zwww;
		ProxyGen<T, 3, 0, 0, 0> wxxx;
		ProxyGen<T, 3, 0, 0, 1> wxxy;
		ProxyGen<T, 3, 0, 0, 2> wxxz;
		ProxyGen<T, 3, 0, 0, 3> wxxw;
		ProxyGen<T, 3, 0, 1, 0> wxyx;
		ProxyGen<T, 3, 0, 1, 1> wxyy;
		ProxyGen<T, 3, 0, 1, 2> wxyz;
		ProxyGen<T, 3, 0, 1, 3> wxyw;
		ProxyGen<T, 3, 0, 2, 0> wxzx;
		ProxyGen<T, 3, 0, 2, 1> wxzy;
		ProxyGen<T, 3, 0, 2, 2> wxzz;
		ProxyGen<T, 3, 0, 2, 3> wxzw;
		ProxyGen<T, 3, 0, 3, 0> wxwx;
		ProxyGen<T, 3, 0, 3, 1> wxwy;
		ProxyGen<T, 3, 0, 3, 2> wxwz;
		ProxyGen<T, 3, 0, 3, 3> wxww;
		ProxyGen<T, 3, 1, 0, 0> wyxx;
		ProxyGen<T, 3, 1, 0, 1> wyxy;
		ProxyGen<T, 3, 1, 0, 2> wyxz;
		ProxyGen<T, 3, 1, 0, 3> wyxw;
		ProxyGen<T, 3, 1, 1, 0> wyyx;
		ProxyGen<T, 3, 1, 1, 1> wyyy;
		ProxyGen<T, 3, 1, 1, 2> wyyz;
		ProxyGen<T, 3, 1, 1, 3> wyyw;
		ProxyGen<T, 3, 1, 2, 0> wyzx;
		ProxyGen<T, 3, 1, 2, 1> wyzy;
		ProxyGen<T, 3, 1, 2, 2> wyzz;
		ProxyGen<T, 3, 1, 2, 3> wyzw;
		ProxyGen<T, 3, 1, 3, 0> wywx;
		ProxyGen<T, 3, 1, 3, 1> wywy;
		ProxyGen<T, 3, 1, 3, 2> wywz;
		ProxyGen<T, 3, 1, 3, 3> wyww;
		ProxyGen<T, 3, 2, 0, 0> wzxx;
		ProxyGen<T, 3, 2, 0, 1> wzxy;
		ProxyGen<T, 3, 2, 0, 2> wzxz;
		ProxyGen<T, 3, 2, 0, 3> wzxw;
		ProxyGen<T, 3, 2, 1, 0> wzyx;
		ProxyGen<T, 3, 2, 1, 1> wzyy;
		ProxyGen<T, 3, 2, 1, 2> wzyz;
		ProxyGen<T, 3, 2, 1, 3> wzyw;
		ProxyGen<T, 3, 2, 2, 0> wzzx;
		ProxyGen<T, 3, 2, 2, 1> wzzy;
		ProxyGen<T, 3, 2, 2, 2> wzzz;
		ProxyGen<T, 3, 2, 2, 3> wzzw;
		ProxyGen<T, 3, 2, 3, 0> wzwx;
		ProxyGen<T, 3, 2, 3, 1> wzwy;
		ProxyGen<T, 3, 2, 3, 2> wzwz;
		ProxyGen<T, 3, 2, 3, 3> wzww;
		ProxyGen<T, 3, 3, 0, 0> wwxx;
		ProxyGen<T, 3, 3, 0, 1> wwxy;
		ProxyGen<T, 3, 3, 0, 2> wwxz;
		ProxyGen<T, 3, 3, 0, 3> wwxw;
		ProxyGen<T, 3, 3, 1, 0> wwyx;
		ProxyGen<T, 3, 3, 1, 1> wwyy;
		ProxyGen<T, 3, 3, 1, 2> wwyz;
		ProxyGen<T, 3, 3, 1, 3> wwyw;
		ProxyGen<T, 3, 3, 2, 0> wwzx;
		ProxyGen<T, 3, 3, 2, 1> wwzy;
		ProxyGen<T, 3, 3, 2, 2> wwzz;
		ProxyGen<T, 3, 3, 2, 3> wwzw;
		ProxyGen<T, 3, 3, 3, 0> wwwx;
		ProxyGen<T, 3, 3, 3, 1> wwwy;
		ProxyGen<T, 3, 3, 3, 2> wwwz;
		ProxyGen<T, 3, 3, 3, 3> wwww;

		ProxyGen<T, 0, 0, 0> xxx;
		ProxyGen<T, 0, 0, 1> xxy;
		ProxyGen<T, 0, 0, 2> xxz;
		ProxyGen<T, 0, 0, 3> xxw;
		ProxyGen<T, 0, 1, 0> xyx;
		ProxyGen<T, 0, 1, 1> xyy;
		ProxyGen<T, 0, 1, 2> xyz;
		ProxyGen<T, 0, 1, 3> xyw;
		ProxyGen<T, 0, 2, 0> xzx;
		ProxyGen<T, 0, 2, 1> xzy;
		ProxyGen<T, 0, 2, 2> xzz;
		ProxyGen<T, 0, 2, 3> xzw;
		ProxyGen<T, 0, 3, 0> xwx;
		ProxyGen<T, 0, 3, 1> xwy;
		ProxyGen<T, 0, 3, 2> xwz;
		ProxyGen<T, 0, 3, 3> xww;
		ProxyGen<T, 1, 0, 0> yxx;
		ProxyGen<T, 1, 0, 1> yxy;
		ProxyGen<T, 1, 0, 2> yxz;
		ProxyGen<T, 1, 0, 3> yxw;
		ProxyGen<T, 1, 1, 0> yyx;
		ProxyGen<T, 1, 1, 1> yyy;
		ProxyGen<T, 1, 1, 2> yyz;
		ProxyGen<T, 1, 1, 3> yyw;
		ProxyGen<T, 1, 2, 0> yzx;
		ProxyGen<T, 1, 2, 1> yzy;
		ProxyGen<T, 1, 2, 2> yzz;
		ProxyGen<T, 1, 2, 3> yzw;
		ProxyGen<T, 1, 3, 0> ywx;
		ProxyGen<T, 1, 3, 1> ywy;
		ProxyGen<T, 1, 3, 2> ywz;
		ProxyGen<T, 1, 3, 3> yww;
		ProxyGen<T, 2, 0, 0> zxx;
		ProxyGen<T, 2, 0, 1> zxy;
		ProxyGen<T, 2, 0, 2> zxz;
		ProxyGen<T, 2, 0, 3> zxw;
		ProxyGen<T, 2, 1, 0> zyx;
		ProxyGen<T, 2, 1, 1> zyy;
		ProxyGen<T, 2, 1, 2> zyz;
		ProxyGen<T, 2, 1, 3> zyw;
		ProxyGen<T, 2, 2, 0> zzx;
		ProxyGen<T, 2, 2, 1> zzy;
		ProxyGen<T, 2, 2, 2> zzz;
		ProxyGen<T, 2, 2, 3> zzw;
		ProxyGen<T, 2, 3, 0> zwx;
		ProxyGen<T, 2, 3, 1> zwy;
		ProxyGen<T, 2, 3, 2> zwz;
		ProxyGen<T, 2, 3, 3> zww;
		ProxyGen<T, 3, 0, 0> wxx;
		ProxyGen<T, 3, 0, 1> wxy;
		ProxyGen<T, 3, 0, 2> wxz;
		ProxyGen<T, 3, 0, 3> wxw;
		ProxyGen<T, 3, 1, 0> wyx;
		ProxyGen<T, 3, 1, 1> wyy;
		ProxyGen<T, 3, 1, 2> wyz;
		ProxyGen<T, 3, 1, 3> wyw;
		ProxyGen<T, 3, 2, 0> wzx;
		ProxyGen<T, 3, 2, 1> wzy;
		ProxyGen<T, 3, 2, 2> wzz;
		ProxyGen<T, 3, 2, 3> wzw;
		ProxyGen<T, 3, 3, 0> wwx;
		ProxyGen<T, 3, 3, 1> wwy;
		ProxyGen<T, 3, 3, 2> wwz;
		ProxyGen<T, 3, 3, 3> www;

		ProxyGen<T, 0, 0> xx;
		ProxyGen<T, 0, 1> xy;
		ProxyGen<T, 0, 2> xz;
		ProxyGen<T, 0, 3> xw;
		ProxyGen<T, 1, 0> yx;
		ProxyGen<T, 1, 1> yy;
		ProxyGen<T, 1, 2> yz;
		ProxyGen<T, 1, 3> yw;
		ProxyGen<T, 2, 0> zx;
		ProxyGen<T, 2, 1> zy;
		ProxyGen<T, 2, 2> zz;
		ProxyGen<T, 2, 3> zw;
		ProxyGen<T, 3, 0> wx;
		ProxyGen<T, 3, 1> wy;
		ProxyGen<T, 3, 2> wz;
		ProxyGen<T, 3, 3> ww;
		// }}}
	};
};

template <typename T, template <typename, unsigned int...> typename ProxyGen>
struct vec_base<T, 3, ProxyGen>
{
	union {
		std::array<T, 3> data;
		struct {
			T x, y, z;
		};

		// {{{
		ProxyGen<T, 0, 0, 0, 0> xxxx;
		ProxyGen<T, 0, 0, 0, 1> xxxy;
		ProxyGen<T, 0, 0, 0, 2> xxxz;
		ProxyGen<T, 0, 0, 1, 0> xxyx;
		ProxyGen<T, 0, 0, 1, 1> xxyy;
		ProxyGen<T, 0, 0, 1, 2> xxyz;
		ProxyGen<T, 0, 0, 2, 0> xxzx;
		ProxyGen<T, 0, 0, 2, 1> xxzy;
		ProxyGen<T, 0, 0, 2, 2> xxzz;
		ProxyGen<T, 0, 1, 0, 0> xyxx;
		ProxyGen<T, 0, 1, 0, 1> xyxy;
		ProxyGen<T, 0, 1, 0, 2> xyxz;
		ProxyGen<T, 0, 1, 1, 0> xyyx;
		ProxyGen<T, 0, 1, 1, 1> xyyy;
		ProxyGen<T, 0, 1, 1, 2> xyyz;
		ProxyGen<T, 0, 1, 2, 0> xyzx;
		ProxyGen<T, 0, 1, 2, 1> xyzy;
		ProxyGen<T, 0, 1, 2, 2> xyzz;
		ProxyGen<T, 0, 2, 0, 0> xzxx;
		ProxyGen<T, 0, 2, 0, 1> xzxy;
		ProxyGen<T, 0, 2, 0, 2> xzxz;
		ProxyGen<T, 0, 2, 1, 0> xzyx;
		ProxyGen<T, 0, 2, 1, 1> xzyy;
		ProxyGen<T, 0, 2, 1, 2> xzyz;
		ProxyGen<T, 0, 2, 2, 0> xzzx;
		ProxyGen<T, 0, 2, 2, 1> xzzy;
		ProxyGen<T, 0, 2, 2, 2> xzzz;
		ProxyGen<T, 1, 0, 0, 0> yxxx;
		ProxyGen<T, 1, 0, 0, 1> yxxy;
		ProxyGen<T, 1, 0, 0, 2> yxxz;
		ProxyGen<T, 1, 0, 1, 0> yxyx;
		ProxyGen<T, 1, 0, 1, 1> yxyy;
		ProxyGen<T, 1, 0, 1, 2> yxyz;
		ProxyGen<T, 1, 0, 2, 0> yxzx;
		ProxyGen<T, 1, 0, 2, 1> yxzy;
		ProxyGen<T, 1, 0, 2, 2> yxzz;
		ProxyGen<T, 1, 1, 0, 0> yyxx;
		ProxyGen<T, 1, 1, 0, 1> yyxy;
		ProxyGen<T, 1, 1, 0, 2> yyxz;
		ProxyGen<T, 1, 1, 1, 0> yyyx;
		ProxyGen<T, 1, 1, 1, 1> yyyy;
		ProxyGen<T, 1, 1, 1, 2> yyyz;
		ProxyGen<T, 1, 1, 2, 0> yyzx;
		ProxyGen<T, 1, 1, 2, 1> yyzy;
		ProxyGen<T, 1, 1, 2, 2> yyzz;
		ProxyGen<T, 1, 2, 0, 0> yzxx;
		ProxyGen<T, 1, 2, 0, 1> yzxy;
		ProxyGen<T, 1, 2, 0, 2> yzxz;
		ProxyGen<T, 1, 2, 1, 0> yzyx;
		ProxyGen<T, 1, 2, 1, 1> yzyy;
		ProxyGen<T, 1, 2, 1, 2> yzyz;
		ProxyGen<T, 1, 2, 2, 0> yzzx;
		ProxyGen<T, 1, 2, 2, 1> yzzy;
		ProxyGen<T, 1, 2, 2, 2> yzzz;
		ProxyGen<T, 2, 0, 0, 0> zxxx;
		ProxyGen<T, 2, 0, 0, 1> zxxy;
		ProxyGen<T, 2, 0, 0, 2> zxxz;
		ProxyGen<T, 2, 0, 1, 0> zxyx;
		ProxyGen<T, 2, 0, 1, 1> zxyy;
		ProxyGen<T, 2, 0, 1, 2> zxyz;
		ProxyGen<T, 2, 0, 2, 0> zxzx;
		ProxyGen<T, 2, 0, 2, 1> zxzy;
		ProxyGen<T, 2, 0, 2, 2> zxzz;
		ProxyGen<T, 2, 1, 0, 0> zyxx;
		ProxyGen<T, 2, 1, 0, 1> zyxy;
		ProxyGen<T, 2, 1, 0, 2> zyxz;
		ProxyGen<T, 2, 1, 1, 0> zyyx;
		ProxyGen<T, 2, 1, 1, 1> zyyy;
		ProxyGen<T, 2, 1, 1, 2> zyyz;
		ProxyGen<T, 2, 1, 2, 0> zyzx;
		ProxyGen<T, 2, 1, 2, 1> zyzy;
		ProxyGen<T, 2, 1, 2, 2> zyzz;
		ProxyGen<T, 2, 2, 0, 0> zzxx;
		ProxyGen<T, 2, 2, 0, 1> zzxy;
		ProxyGen<T, 2, 2, 0, 2> zzxz;
		ProxyGen<T, 2, 2, 1, 0> zzyx;
		ProxyGen<T, 2, 2, 1, 1> zzyy;
		ProxyGen<T, 2, 2, 1, 2> zzyz;
		ProxyGen<T, 2, 2, 2, 0> zzzx;
		ProxyGen<T, 2, 2, 2, 1> zzzy;
		ProxyGen<T, 2, 2, 2, 2> zzzz;

		ProxyGen<T, 0, 0, 0> xxx;
		ProxyGen<T, 0, 0, 1> xxy;
		ProxyGen<T, 0, 0, 2> xxz;
		ProxyGen<T, 0, 1, 0> xyx;
		ProxyGen<T, 0, 1, 1> xyy;
		ProxyGen<T, 0, 1, 2> xyz;
		ProxyGen<T, 0, 2, 0> xzx;
		ProxyGen<T, 0, 2, 1> xzy;
		ProxyGen<T, 0, 2, 2> xzz;
		ProxyGen<T, 1, 0, 0> yxx;
		ProxyGen<T, 1, 0, 1> yxy;
		ProxyGen<T, 1, 0, 2> yxz;
		ProxyGen<T, 1, 1, 0> yyx;
		ProxyGen<T, 1, 1, 1> yyy;
		ProxyGen<T, 1, 1, 2> yyz;
		ProxyGen<T, 1, 2, 0> yzx;
		ProxyGen<T, 1, 2, 1> yzy;
		ProxyGen<T, 1, 2, 2> yzz;
		ProxyGen<T, 2, 0, 0> zxx;
		ProxyGen<T, 2, 0, 1> zxy;
		ProxyGen<T, 2, 0, 2> zxz;
		ProxyGen<T, 2, 1, 0> zyx;
		ProxyGen<T, 2, 1, 1> zyy;
		ProxyGen<T, 2, 1, 2> zyz;
		ProxyGen<T, 2, 2, 0> zzx;
		ProxyGen<T, 2, 2, 1> zzy;
		ProxyGen<T, 2, 2, 2> zzz;

		ProxyGen<T, 0, 0> xx;
		ProxyGen<T, 0, 1> xy;
		ProxyGen<T, 0, 2> xz;
		ProxyGen<T, 1, 0> yx;
		ProxyGen<T, 1, 1> yy;
		ProxyGen<T, 1, 2> yz;
		ProxyGen<T, 2, 0> zx;
		ProxyGen<T, 2, 1> zy;
		ProxyGen<T, 2, 2> zz;
		// }}}
	};
};

template <typename T, template <typename, unsigned int...> typename ProxyGen>
struct vec_base<T, 2, ProxyGen>
{
	union {
		std::array<T, 2> data;
		struct {
			T x, y;
		};

		// {{{
		ProxyGen<T, 0, 0, 0, 0> xxxx;
		ProxyGen<T, 0, 0, 0, 1> xxxy;
		ProxyGen<T, 0, 0, 1, 0> xxyx;
		ProxyGen<T, 0, 0, 1, 1> xxyy;
		ProxyGen<T, 0, 1, 0, 0> xyxx;
		ProxyGen<T, 0, 1, 0, 1> xyxy;
		ProxyGen<T, 0, 1, 1, 0> xyyx;
		ProxyGen<T, 0, 1, 1, 1> xyyy;
		ProxyGen<T, 1, 0, 0, 0> yxxx;
		ProxyGen<T, 1, 0, 0, 1> yxxy;
		ProxyGen<T, 1, 0, 1, 0> yxyx;
		ProxyGen<T, 1, 0, 1, 1> yxyy;
		ProxyGen<T, 1, 1, 0, 0> yyxx;
		ProxyGen<T, 1, 1, 0, 1> yyxy;
		ProxyGen<T, 1, 1, 1, 0> yyyx;
		ProxyGen<T, 1, 1, 1, 1> yyyy;

		ProxyGen<T, 0, 0, 0> xxx;
		ProxyGen<T, 0, 0, 1> xxy;
		ProxyGen<T, 0, 1, 0> xyx;
		ProxyGen<T, 0, 1, 1> xyy;
		ProxyGen<T, 1, 0, 0> yxx;
		ProxyGen<T, 1, 0, 1> yxy;
		ProxyGen<T, 1, 1, 0> yyx;
		ProxyGen<T, 1, 1, 1> yyy;

		ProxyGen<T, 0, 0> xx;
		ProxyGen<T, 0, 1> xy;
		ProxyGen<T, 1, 0> yx;
		ProxyGen<T, 1, 1> yy;
		// }}}
	};
};

template <typename T, template <typename, unsigned int...> typename ProxyGen>
struct vec_base<T, 1, ProxyGen>
{
	union {
		std::array<T, 1> data;
		struct {
			T x;
		};

		// {{{
		ProxyGen<T, 0, 0, 0, 0> xxxx;
		ProxyGen<T, 0, 0, 0> xxx;
		ProxyGen<T, 0, 0> xx;
		// }}}
	};
};

// why?
template <typename T, template <typename, unsigned int...> typename ProxyGen>
struct vec_base<T, 0, ProxyGen>
{
	std::array<T, 0> data;
};

} // namespace velm

#if defined(__llvm__)
	#pragma clang diagnostic pop
#elif defined(_MSC_VER)
	#pragma warning(pop)
#elif defined(__GNUC__)
	#pragma GCC diagnostic pop
#endif
