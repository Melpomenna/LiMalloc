#include <benchmark/benchmark.h>

static void Benchmark_Example([[maybe_unused]] benchmark::State& state)
{
    for ([[maybe_unused]] const auto& _ : state)
    {
        benchmark::DoNotOptimize(1 + 1);
    }
}

BENCHMARK(Benchmark_Example);
