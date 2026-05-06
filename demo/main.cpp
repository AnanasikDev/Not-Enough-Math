#include "nem.hpp"
#include "vec_io.hpp"
#include "vec_utils.hpp"
#include "mat.hpp"
#include "mat_io.hpp"
#include "mat_utils.hpp"
#include <iostream>
#include "quat_utils.hpp"
#include "quat_io.hpp"

using namespace nem;

#define MAIN_END int _; std::cin >> _; return 0;

int main()
{
    quatr q0 = make_quat<real>(1, 0.5f, 1, 2);
    quatr q1 = make_quat<real>(2, 3, 4, 2.5f);
    std::cout << q0 << " * " << q1 << " = " << q0 * q1 << "\n";
    std::cout << q1 << " * " << q0 << " = " << q1 * q0 << "\n";

    mat2 src({ {3, 4}, {8, 9} });
    mat3 dst = nem::upscale<float, 2, 2, 3, 3>(src);
    std::cout << "src: " << src << "\n" << "dst: " << dst << "\n";



    MAIN_END
}