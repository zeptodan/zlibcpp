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
static void BM_zstl_intadd(benchmark::State& state){
    for (auto _ : state){
        vector<int> vec;
        zstl_vectoradd(vec,state.range(0),5);
        benchmark::DoNotOptimize(vec);
    }
}
static void BM_stl_intadd(benchmark::State& state){
    for (auto _ : state){
        std::vector<int> vec;
        stl_vectoradd(vec, state.range(0),5);
        benchmark::DoNotOptimize(vec);
    }
}
static void BM_zstl_stradd(benchmark::State& state){
    for (auto _ : state){
        vector<std::string> vec;
        zstl_vectoradd(vec,state.range(0),std::string("what da hell is dis senorita thats crazy aint it wow ma man"));
        benchmark::DoNotOptimize(vec);
    }
}
static void BM_stl_stradd(benchmark::State& state){
    for (auto _ : state){
        std::vector<std::string> vec;
        stl_vectoradd(vec, state.range(0),std::string("what da hell is dis senorita thats crazy aint it wow ma man"));
        benchmark::DoNotOptimize(vec);
    }
}
BENCHMARK(BM_zstl_intadd)->Range(8, 8 << 13);
BENCHMARK(BM_stl_intadd)->Range(8, 8 << 13);
BENCHMARK(BM_zstl_stradd)->Range(8, 8 << 13);
BENCHMARK(BM_stl_stradd)->Range(8, 8 << 13);
int main(int argc, char* argv[]){
    if (argc > 1){
        std::string arg(argv[1]);
        int n = 8 << 20;
        if (arg == "intA"){
            vector<int> vec;
            zstl_vectoradd(vec, n, 5);
            return 0;
        }
        else if(arg == "intB"){
            std::vector<int> vec;
            stl_vectoradd(vec, n, 5);
            return 0;
        }
        else if(arg == "strA"){
            vector<std::string> vec;
            zstl_vectoradd(vec,n,std::string("what da hell is dis senorita thats crazy aint it wow ma man"));
            return 0;
        }
        else if(arg == "strB"){
            std::vector<std::string> vec;
            stl_vectoradd(vec,n,std::string("what da hell is dis senorita thats crazy aint it wow ma man"));
            return 0;
        }
    }
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
}