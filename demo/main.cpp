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
    mat2 m0 = identity<float, 2>();
    mat3 m1 = identity<mat3>();
    std::cout << m0 << "\n\n";
    std::cout << m1 << "\n\n";
    int _;
    std::cin >> _;
    return 0;
}