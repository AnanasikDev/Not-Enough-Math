#include "nem.hpp"
#include "vec_io.hpp"
#include <iostream>

using namespace nem;

int main() {
    float3 v0(1, 1, 1);
    float3 v1(2, 4, 8);
    float3 v2 = v0 + v1;
    std::cout << v0 << std::endl;
    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;
    float3 v3;
    std::cout << v3.normalize() << std::endl;
    float3 i0;
    std::cin >> i0;
    std::cout << i0 << std::endl;
    int a;
    std::cin >> a;
    return 0;
}