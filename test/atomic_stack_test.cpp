#include<gtest/gtest.h>
#include<array>
#include<thread>
#include"zstl/atomic_stack.hpp"
TEST(atomic_stack_test, stack_add_try_pop){
    atomic_stack<int> stack;
    int val;
    bool isval = stack.try_pop(val);
    ASSERT_EQ(isval, false);
    stack.push(5);
    isval = stack.try_pop(val);
    ASSERT_EQ(isval,true);
    ASSERT_EQ(val,5);
}
TEST(parallel_atomic_stack_test, stack_add_try_pop){
    constexpr int tot_threads = 20;
    constexpr int thread_pushes = 500;
    std::atomic<int> tot_elems = tot_threads * thread_pushes;
    std::array<std::thread, tot_threads> push_threads;
    std::array<std::thread, tot_threads> pop_threads;
    std::array<int, tot_threads> push_nums{};
    std::array<std::atomic<int>, tot_threads> pop_nums{};
    atomic_stack<int> stack;
    for (int i = 0; i < tot_threads;i++){
        push_threads[i] = std::thread([i, &push_nums, &stack](){
            while(push_nums[i]++ < 500){
                stack.push(i);
            }
        });
    }
    for (int i = 0; i < tot_threads;i++){
        pop_threads[i] = std::thread([&tot_elems, &pop_nums, &stack](){
            while(tot_elems > 0){
                int val;
                bool did_pop = stack.try_pop(val);
                if (did_pop){
                    --tot_elems;
                    pop_nums[val]++;
                }
            }
        });
    }
    for (int i = 0; i < tot_threads;i++){
        push_threads[i].join();
        pop_threads[i].join();
    }
    for (int i = 0; i < tot_threads;i++){
        ASSERT_EQ(pop_nums[i], thread_pushes) << "actual value is " << pop_nums[i] << "\n";
    }
}
