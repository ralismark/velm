#include "vector.hpp"
#include "ops.hpp"

#include <typeinfo>

const char* s;

int main()
{
	velm::vector<int, 3> x = 1u, y = 1;
	velm::vector<double, 3> z = 4;

	auto val = x * y / x + y - x;
	y.swizzle<0,1,2>() = x;
	x += y;

	s = typeid(std::common_type_t<decltype(x.xx), decltype(z.xx)>).name();

	return x.x;
}
