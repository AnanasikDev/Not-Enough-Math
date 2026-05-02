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

int main()
{
    quatr q0 = make_quat<real>(1, 0.5f, 1, 2);
    quatr q1 = make_quat<real>(2, 3, 4, 2.5f);
    std::cout << q0 << " * " << q1 << " = " << q0 * q1 << "\n";
    std::cout << q1 << " * " << q0 << " = " << q1 * q0 << "\n";
    int _;
    std::cin >> _;
    return 0;
}