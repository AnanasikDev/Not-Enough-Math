#include <iostream>
#include <vector>
#include "../nem/include/nem.hpp"
#include "easing.hpp"

// template <int N>
// struct my_vec
// {
//     int items[N];

//     friend my_vec operator+(my_vec a, my_vec b)
//     {
//         my_vec r;
//         for (int i = 0; i < N; i++)
//         {
//             r.items[i] = a.items[i] + b.items[i];
//         }
//         return r;
//     }
// };

// template <>
// struct my_vec<4>
// {
//     union
//     {
//         int items[4];
//         struct { int x, y, z, w; };
//     };

//     using my_vec::operator+;
// };

template <typename T, int N>
struct vec_storage
{
    T items[N];
};

template <typename T>
struct vec_storage<T, 4>
{
    union
    {
        int items[4];
        struct
        {
            int x, y, z, w;
        };
    };
};

template <typename T>
struct vec_storage<T, 2>
{
    union
    {
        int items[2];
        struct
        {
            int x, y;
        };
    };
};

template <typename T, int N>
struct my_vec : vec_storage<T, N>
{
    friend my_vec operator+(my_vec a, my_vec b)
    {
        my_vec r;
        for (int i = 0; i < N; i++)
            r.items[i] = a.items[i] + b.items[i];
        return r;
    }

    my_vec() = default;
    my_vec(int s)
    {
        for (int i = 0; i < N; ++i)
        {
            this->items[i] = s;
        }
    }

    template <typename... Args>
    requires (sizeof...(Args) == N) && ((std::is_floating_point_v<Args> || std::is_integral_v<Args>) && ...)
    my_vec(Args... args)
    {
        int i = 0;
        ((this->items[i++] = args), ...);
    }
};

void demo()
{
    nem::quat q0 = nem::make_quat<nem::real>(1, 0.5f, 1, 2);
    nem::quat q1 = nem::make_quat<nem::real>(2, 3, 4, 2.5f);
    std::cout << q0 << " * " << q1 << " = " << q0 * q1 << "\n";
    std::cout << q1 << " * " << q0 << " = " << q1 * q0 << "\n";

    nem::mat2 src({ {3, 4}, {8, 9} });
    nem::mat3 dst = nem::upscale<float, 2, 2, 3, 3>(src);
    std::cout << "src: " << src << "\n" << "dst: " << dst << "\n";

    std::vector<float> v;
    v.push_back(3.3f);
    std::cout << "std::vector! " << v[0] << "\n";

    std::cout << "Logarithm: " << ::log(nem::E<float>) << " sin: " << nem::sin(0.3f) << std::endl;

#if defined(_DEBUG)
    std::cout << "DEBUG!\n";
#elif defined(_RELEASE)
    std::cout << "RELEASE!\n";
#endif

    std::cout << "Sqrt(1231)" << nem::isqrt(1231) << std::endl;
    std::cout << "Cbrt(1231)" << nem::icbrt(1231) << std::endl;

    my_vec<int, 2> v2(2);
    my_vec<int, 4> v4(2.8f, 3, 4.2f, 5);
    my_vec<int, 4> v41(5.5f, 9.0, -4.1f, 5);
    my_vec<int, 4> v42 = v4 + v41;
    my_vec<int, 7> v7(18, 2, 31, 4, 5, 6, 855);
    my_vec<int, 1> v1(4);
    std::cout << "Size of v42: " << sizeof(v42) << std::endl;
    for (int i = 0; i < 4; i++)
    {
        std::cout << " " << v42.items[i];
    }
    std::cout << "Size of v7: " << sizeof(v7) << std::endl;
    for (int i = 0; i < 7; i++)
    {
        std::cout << " " << v7.items[i];
    }
}

int main()
{
    demo();
    return 0;
}