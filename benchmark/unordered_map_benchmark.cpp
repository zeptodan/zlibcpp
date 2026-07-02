#include<benchmark/benchmark.h>
#include"zstl/unordered_map.hpp"
static void BM_zstl_unordered_map_int(benchmark::State& state){
    unordered_map<int, int> map;
    for(std::size_t i = 0; i < state.range(0);i++){
        map[i] = i;
    }
}
static void BM_stl_unordered_map_int(benchmark::State& state){
    std::unordered_map<int, int> map;
    for(std::size_t i = 0; i < state.range(0);i++){
        map[i] = i;
    }
}
BENCHMARK(BM_zstl_unordered_map_int)->Range(8, 8 << 18);
BENCHMARK(BM_stl_unordered_map_int)->Range(8, 8 << 18);
// int main(){

// }