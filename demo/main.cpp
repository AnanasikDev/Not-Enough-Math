#include <iostream>
#include <vector>
#include "nem.hpp"

void demo()
{
    nem::quatr q0 = nem::make_quat<nem::real>(1, 0.5f, 1, 2);
    nem::quatr q1 = nem::make_quat<nem::real>(2, 3, 4, 2.5f);
    std::cout << q0 << " * " << q1 << " = " << q0 * q1 << "\n";
    std::cout << q1 << " * " << q0 << " = " << q1 * q0 << "\n";

    nem::mat2 src({ {3, 4}, {8, 9} });
    nem::mat3 dst = nem::upscale<float, 2, 2, 3, 3>(src);
    std::cout << "src: " << src << "\n" << "dst: " << dst << "\n";

    std::vector<float> v;
    v.push_back(3.3f);
    std::cout << "std::vector! " << v[0] << "\n";

    std::cout << "Logarithm: " << ::log(nem::E<float>()) << std::endl;
}

int main()
{
    demo();

    int _; std::cin >> _; return 0;
}