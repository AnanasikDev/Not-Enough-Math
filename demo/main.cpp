#include "nem.hpp"
#include <iostream>

using namespace nem;

int main() {
    float3 v0(1, 1, 1);
    float3 v1(2, 4, 8);
    float3 v2 = v0 + v1;
    std::cout << "NotEnoughMath Demo: " << v2.x << " " << v2.y << " " << v2.z << std::endl;
    int a;
    std::cin >> a;
    return 0;
}