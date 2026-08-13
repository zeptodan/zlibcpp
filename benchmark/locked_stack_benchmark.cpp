#include<benchmark/benchmark.h>
#include"zstl/locked_stack.hpp"
static void BM_zstl_locked_stack(benchmark::State& state){
    static locked_stack<int> stack;
    const int total = state.range(0);
    const int threads = state.threads();

    const int start = (total * state.thread_index()) / threads;
    const int end = (total * (state.thread_index() + 1)) / threads;
    for(auto _ : state){
        for(int i = start; i < end;i++){
            stack.push(i);
        } 
        benchmark::DoNotOptimize(stack);
        state.PauseTiming();
        int val;
        while(stack.try_pop(val)){}
        state.ResumeTiming();
    }
}
BENCHMARK(BM_zstl_locked_stack)->Range(8, 8 << 18)->Threads(1)->Threads(2)->Threads(4)->Threads(8)->Threads(16);
int main(int argc, char* argv[]){
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
}