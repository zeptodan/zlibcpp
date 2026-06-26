#include<benchmark/benchmark.h>
#include"zstl/vector.hpp"
template<typename T>
void zstl_vectoradd(vector<T>& vec,int n, const T& input){
    for(int i = 0; i < n; i++){
        vec.push_back(input);
    }
}
template<typename T>
void stl_vectoradd(std::vector<T>& vec,int n, const T& input){
    for(int i = 0; i < n; i++){
        vec.push_back(input);
    }
}
static void BM_zstl_vectoradd(benchmark::State& state){
    for (auto _ : state){
        vector<int> vec;
        zstl_vectoradd(vec,state.range(0),5);
        benchmark::DoNotOptimize(vec);
    }
}
static void BM_stl_vectoradd(benchmark::State& state){
    for (auto _ : state){
        std::vector<int> vec;
        stl_vectoradd(vec, state.range(0),5);
        benchmark::DoNotOptimize(vec);
    }
}
int main(int argc, char* argv[]){
    if (argc > 1){
        std::string arg(argv[1]);
        int n = 8 << 13;
        if (arg == "cgA"){
            vector<int> vec;
            zstl_vectoradd(vec, n, 5);
            return 0;
        }
        else if(arg == "cgB"){
            std::vector<int> vec;
            stl_vectoradd(vec, n, 5);
            return 0;
        }
    }
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
}
BENCHMARK(BM_zstl_vectoradd)->Range(8, 8 << 13);
BENCHMARK(BM_stl_vectoradd)->Range(8, 8 << 13);
