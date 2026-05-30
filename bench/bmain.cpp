#include <iostream>
#include <vector>
#include "nem.hpp"
#include "exp/asmmath.hpp"
#include <benchmark/benchmark.h>

//volatile float arg1 = 1.0001f;
//volatile float arg2 = 2.0f;
//
//static void Bench_NoCache(benchmark::State& state)
//{
//    for (auto _ : state)
//    {
//        float a = arg1 + arg2;
//        benchmark::DoNotOptimize(a);
//    }
//    state.SetItemsProcessed(state.iterations() * 1000);
//}
//BENCHMARK(Bench_NoCache);
//
//static void Bench_NoInnerLoop(benchmark::State& state)
//{
//    for (auto _ : state)
//    {
//        benchmark::DoNotOptimize(arg1);
//        benchmark::DoNotOptimize(arg2);
//        float a = arg1 + arg2;
//        benchmark::DoNotOptimize(a);
//    }
//    state.SetItemsProcessed(state.iterations() * 1000);
//}
//BENCHMARK(Bench_NoInnerLoop);
//
//static void Bench_WithInnerLoop(benchmark::State& state)
//{
//    for (auto _ : state)
//    {
//        for (int i = 0; i < 1000; ++i)
//        {
//            benchmark::DoNotOptimize(arg1);
//            benchmark::DoNotOptimize(arg2);
//            float a = arg1 + arg2;
//            benchmark::DoNotOptimize(a);
//        }
//    }
//    state.SetItemsProcessed(state.iterations() * 1000);
//}
//BENCHMARK(Bench_WithInnerLoop);

namespace bm = benchmark;

static void f32_sin(bm::State& state)
{
    float argument = std::rand(), result = 0;
    for (auto _ : state)
    {
        argument += 1.0f;
        result = std::sin(argument);
        bm::DoNotOptimize(result);
    }
}
BENCHMARK(f32_sin);

static void f32_cos(bm::State& state)
{
    float argument = std::rand(), result = 0;
    for (auto _ : state)
    {
        argument += 1.0f;
        result = std::cos(argument);
        bm::DoNotOptimize(result);
    }
}
BENCHMARK(f32_cos);

static void f64_sin_maclaurin(bm::State& state)
{
    float argument = std::rand(), result = 0;
    for (auto _ : state)
    {
        argument += 1.0;
        result = argument - std::pow(argument, 3) / 6 + std::pow(argument, 5) / 120;
        bm::DoNotOptimize(result);
    }
}
BENCHMARK(f64_sin_maclaurin);

static void f64_sin_maclaurin_powless(bm::State& state)
{
    float argument = std::rand(), result = 0;
    for (auto _ : state)
    {
        argument += 1.0;
        result = (argument)-(argument * argument * argument) / 6.0 +
            (argument * argument * argument * argument * argument) / 120.0;
        bm::DoNotOptimize(result);
    }
}
BENCHMARK(f64_sin_maclaurin_powless);







static void f32_nem_sin_p3(bm::State& state)
{
    float argument = std::rand(), result = 0;
    for (auto _ : state)
    {
        argument += 1.0;
        result = nem::sin<float, 3>(argument);
        bm::DoNotOptimize(result);
    }
}
BENCHMARK(f32_nem_sin_p3);

static void f32_nem_sin_p2(bm::State& state)
{
    float argument = std::rand(), result = 0;
    for (auto _ : state)
    {
        argument += 1.0;
        result = nem::sin<float, 2>(argument);
        bm::DoNotOptimize(result);
    }
}
BENCHMARK(f32_nem_sin_p2);

static void f32_nem_sin_p1(bm::State& state)
{
    float argument = std::rand(), result = 0;
    for (auto _ : state)
    {
        argument += 1.0;
        result = nem::sin<float, 1>(argument);
        bm::DoNotOptimize(result);
    }
}
BENCHMARK(f32_nem_sin_p1);



static void f32_nem_cos_p3(bm::State& state)
{
    float argument = std::rand(), result = 0;
    for (auto _ : state)
    {
        argument += 1.0;
        result = nem::cos<float, 3>(argument);
        bm::DoNotOptimize(result);
    }
}
BENCHMARK(f32_nem_cos_p3);

static void f32_nem_cos_p2(bm::State& state)
{
    float argument = std::rand(), result = 0;
    for (auto _ : state)
    {
        argument += 1.0;
        result = nem::cos<float, 2>(argument);
        bm::DoNotOptimize(result);
    }
}
BENCHMARK(f32_nem_cos_p2);

static void f32_nem_cos_p1(bm::State& state)
{
    float argument = std::rand(), result = 0;
    for (auto _ : state)
    {
        argument += 1.0;
        result = nem::cos<float, 1>(argument);
        bm::DoNotOptimize(result);
    }
}
BENCHMARK(f32_nem_cos_p1);

//static void Bench_Add(benchmark::State& state)
//{
//    for (auto _ : state)
//    {
//        for (int i = 0; i < 1000; ++i)
//        {
//            benchmark::DoNotOptimize(arg1);
//            benchmark::DoNotOptimize(arg2);
//            float a = arg1 + arg2;
//            benchmark::DoNotOptimize(a);
//        }
//    }
//    state.SetItemsProcessed(state.iterations() * 1000);
//}
//BENCHMARK(Bench_Add);
//
//static void Bench_Mul(benchmark::State& state)
//{
//    for (auto _ : state)
//    {
//        for (int i = 0; i < 1000; ++i)
//        {
//            benchmark::DoNotOptimize(arg1);
//            benchmark::DoNotOptimize(arg2);
//            float a = arg1 * arg2;
//            benchmark::DoNotOptimize(a);
//        }
//    }
//    state.SetItemsProcessed(state.iterations() * 1000);
//}
//BENCHMARK(Bench_Mul);
//
//static void Bench_Sin(benchmark::State& state)
//{
//    for (auto _ : state)
//    {
//        for (int i = 0; i < 1000; ++i)
//        {
//            float b = 123.f;
//            benchmark::DoNotOptimize(b);
//            float a = sinf(b);
//            benchmark::DoNotOptimize(a);
//        }
//    }
//    state.SetItemsProcessed(state.iterations() * 1000);
//}
//BENCHMARK(Bench_Sin);
//
//static void Bench_Pow2(benchmark::State& state)
//{
//    for (auto _ : state)
//    {
//        for (int i = 0; i < 1000; ++i)
//        {
//            float b = 9.0f;
//            benchmark::DoNotOptimize(b);
//            float a = nem::pow2(b);
//            benchmark::DoNotOptimize(a);
//        }
//    }
//    state.SetItemsProcessed(state.iterations() * 1000);
//}
//BENCHMARK(Bench_Pow2);
//
//static void Bench_Pow16(benchmark::State& state)
//{
//    for (auto _ : state)
//    {
//        for (int i = 0; i < 1000; ++i)
//        {
//            float b = 1.0001f;  // small base so pow16 doesn't explode to inf
//            benchmark::DoNotOptimize(b);
//            float a = nem::pow4(nem::pow4(b));
//            benchmark::DoNotOptimize(a);
//        }
//    }
//    state.SetItemsProcessed(state.iterations() * 1000);
//}
//BENCHMARK(Bench_Pow16);
//
//static void Bench_PowN(benchmark::State& state)
//{
//    for (auto _ : state)
//    {
//        for (int i = 0; i < 1000; ++i)
//        {
//            float b = 423.f;
//            float c = 4.543f;
//            benchmark::DoNotOptimize(b);
//            benchmark::DoNotOptimize(c);
//            float a = nem::pow(b, c);
//            benchmark::DoNotOptimize(a);
//        }
//    }
//    state.SetItemsProcessed(state.iterations() * 1000);
//}
//BENCHMARK(Bench_PowN);
//
//static void Bench_Sqrt(benchmark::State& state)
//{
//    for (auto _ : state)
//    {
//        for (int i = 0; i < 1000; ++i)
//        {
//            float b = 4.543f;
//            benchmark::DoNotOptimize(b);
//            float a = nem::sqrt(b);
//            benchmark::DoNotOptimize(a);
//        }
//    }
//    state.SetItemsProcessed(state.iterations() * 1000);
//}
//BENCHMARK(Bench_Sqrt);
//
//static void Bench_Mat4xMat4(benchmark::State& state)
//{
//    for (auto _ : state)
//    {
//        for (int i = 0; i < 1000; ++i)
//        {
//            float a = 4.5f;
//            benchmark::DoNotOptimize(a);
//            float b = 7.2f;
//            benchmark::DoNotOptimize(b);
//
//            nem::mat4 m1(a);
//            nem::mat4 m2(b);
//            nem::mat4 m3 = m1 * m2;
//
//            benchmark::DoNotOptimize(m3);
//        }
//    }
//    state.SetItemsProcessed(state.iterations() * 1000);
//}
//BENCHMARK(Bench_Mat4xMat4);


BENCHMARK_MAIN();

//void demo()
//{
//    nem::quatr q0 = nem::make_quat<nem::real>(1, 0.5f, 1, 2);
//    nem::quatr q1 = nem::make_quat<nem::real>(2, 3, 4, 2.5f);
//    std::cout << q0 << " * " << q1 << " = " << q0 * q1 << "\n";
//    std::cout << q1 << " * " << q0 << " = " << q1 * q0 << "\n";
//
//    nem::mat2 src({ {3, 4}, {8, 9} });
//    nem::mat3 dst = nem::upscale<float, 2, 2, 3, 3>(src);
//    std::cout << "src: " << src << "\n" << "dst: " << dst << "\n";
//
//    std::vector<float> v;
//    v.push_back(3.3f);
//    std::cout << "std::vector! " << v[0] << "\n";
//
//    std::cout << "LOGarithm: " << ::log(nem::E<float>) << std::endl;
//
//    //nem::experimental::asmmath::mul(4, 6);
//    nem::experimental::asmmath::sin(nem::HALF_PI<float>);
//    nem::experimental::asmmath::sin(nem::HALF_PI<float> / 2.f);
//}
//
//
//int main()
//{
//    demo();
//
//    int _; std::cin >> _; return 0;
//}