#include "nem.hpp"
#include "vec_io.hpp"
#include "vec_utils.hpp"
#include "mat.hpp"
#include "mat_io.hpp"
#include "mat_utils.hpp"
//#include "sys.hpp"
#include <iostream>

using namespace nem;

int main()
{
    //auto v = nem::sys::language::language_version();
    //std::cout << "C++: " << static_cast<int>(v) << "\n";
    //std::cout << (nem::sys::byte::is_little() ? "little" : "big") << "\n";

    float3 v0(1, 1, 1);
    float3 v1(2, 4, 8);
    float3 v2 = v0 + v1;
    std::cout << v0 << std::endl;
    std::cout << v1 << std::endl;
    BaseVector<float, 8> a(2);
    BaseVector<float, 8> b(4);
    std::cout << dot(a, b) << std::endl;
    std::cout << v2 << std::endl;
    float3 v3;
    std::cout << v3.normalized() << std::endl;
    std::cout << normalize(v3) << std::endl;

    mat2 m0;
    m0 | [m0](size_t r, size_t c, float v) { return m0.index(r, c); };
    mat2 m1{ 8, 2, 3, 1 };
    m0 = m1;

    mat3 m2{
        { 6, 9, 0 },
        { 5, 5, 4 },
        { 7, 3, 0.1f }
    };

    std::cout << m0 << std::endl;
    std::cout << m1 << std::endl;
    std::cout << m0 * m1 << std::endl;
    std::cout << m1 * m0 << std::endl;
    std::cout << m2 << std::endl;

    float3 i0;
    std::cin >> i0;
    std::cout << i0 << std::endl;
    int _;
    std::cin >> _;
    return 0;
}