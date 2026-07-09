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

static void f64_sin_maclaurin_powless_multiplication(bm::State& state)
{
    float argument = std::rand(), result = 0;
    constexpr float a1 = 1.0f / 6.0;
    constexpr float a2 = 1.0f / 120.0;
    const float a3 = argument * argument;

    for (auto _ : state)
    {
        argument += 1.0;
        result = argument * (1.0f - a3 * a1 + a3 * a3 * a2);
        bm::DoNotOptimize(result);
    }
}
BENCHMARK(f64_sin_maclaurin_powless_multiplication);



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

static void f32_nem_sincos_naive_p1(bm::State& state)
{
    float argument = std::rand();
    nem::sincos<float> result{};
    for (auto _ : state)
    {
        argument += 1.0f;
        result.sin = nem::sin<float, 1>(argument);
        result.cos = nem::cos<float, 1>(argument);
        bm::DoNotOptimize(result);
    }
}
BENCHMARK(f32_nem_sincos_naive_p1);

static void f32_nem_sincos_optimized_p1(bm::State& state)
{
    float argument = std::rand();
    nem::sincos<float> result{};
    for (auto _ : state)
    {
        argument += 1.0f;
        result = nem::get_sincos<float, 1>(argument);
        bm::DoNotOptimize(result);
    }
}
BENCHMARK(f32_nem_sincos_optimized_p1);

static void f32_nem_sincos_naive_p2(bm::State& state)
{
    float argument = std::rand();
    nem::sincos<float> result{};
    for (auto _ : state)
    {
        argument += 1.0f;
        result.sin = nem::sin<float, 2>(argument);
        result.cos = nem::cos<float, 2>(argument);
        bm::DoNotOptimize(result);
    }
}
BENCHMARK(f32_nem_sincos_naive_p2);

static void f32_nem_sincos_optimized_p2(bm::State& state)
{
    float argument = std::rand();
    nem::sincos<float> result{};
    for (auto _ : state)
    {
        argument += 1.0f;
        result = nem::get_sincos<float, 2>(argument);
        bm::DoNotOptimize(result);
    }
}
BENCHMARK(f32_nem_sincos_optimized_p2);

static void f32_nem_sincos_naive_p3(bm::State& state)
{
    float argument = std::rand();
    nem::sincos<float> result{};
    for (auto _ : state)
    {
        argument += 1.0f;
        result.sin = nem::sin<float, 3>(argument);
        result.cos = nem::cos<float, 3>(argument);
        bm::DoNotOptimize(result);
    }
}
BENCHMARK(f32_nem_sincos_naive_p3);

static void f32_nem_sincos_optimized_p3(bm::State& state)
{
    float argument = std::rand();
    nem::sincos<float> result{};
    for (auto _ : state)
    {
        argument += 1.0f;
        result = nem::get_sincos<float, 3>(argument);
        bm::DoNotOptimize(result);
    }
}
BENCHMARK(f32_nem_sincos_optimized_p3);



static void f32_std_log2(bm::State& state)
{
    float argument = std::rand(), result = 0;
    for (auto _ : state)
    {
        argument += 1.0;
        result = std::log2f(argument);
        bm::DoNotOptimize(result);
    }
}
BENCHMARK(f32_std_log2);

static void f32_nem_log2(bm::State& state)
{
    float argument = std::rand(), result = 0;
    for (auto _ : state)
    {
        argument += 1.0;
        result = nem::accurate::log2(argument);
        bm::DoNotOptimize(result);
    }
}
BENCHMARK(f32_nem_log2);

static void f32_nem_fast_log2(bm::State& state)
{
    float argument = std::rand(), result = 0;
    for (auto _ : state)
    {
        argument += 1.0;
        result = nem::fast::log2(argument);
        bm::DoNotOptimize(result);
    }
}
BENCHMARK(f32_nem_fast_log2);


BENCHMARK_MAIN();