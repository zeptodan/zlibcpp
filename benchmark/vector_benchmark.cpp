#include<benchmark/benchmark.h>
#include"zstl/vector.hpp"
static void BM_zstl_vectoradd(benchmark::State& state){
    for (auto _ : state){
        vector<int> vec;
        for(int i = 0; i < state.range(0); i++){
            vec.add(i);
        }
        benchmark::DoNotOptimize(vec);
    }
}
static void BM_stl_vectoradd(benchmark::State& state){
    for (auto _ : state){
        std::vector<int> vec;
        for(int i = 0; i < state.range(0); i++){
            vec.push_back(i);
        }
        benchmark::DoNotOptimize(vec);
    }
}
BENCHMARK(BM_zstl_vectoradd)->Range(8, 8 << 13);
BENCHMARK(BM_stl_vectoradd)->Range(8, 8 << 13);
BENCHMARK_MAIN();