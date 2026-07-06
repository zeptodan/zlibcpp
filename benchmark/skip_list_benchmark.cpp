#include<benchmark/benchmark.h>
#include"zstl/skip_list.hpp"
static void BM_zstl_skip_list_int(benchmark::State& state){
    for (auto _ : state){
        skip_list<int, int> sl;
        for(std::size_t i = 0; i < state.range(0);i++){
            sl[i] = i;
        }
        benchmark::DoNotOptimize(sl);
    }
}
BENCHMARK(BM_zstl_skip_list_int)->Range(8, 8 << 18);
int main(int argc, char* argv[]){
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
}