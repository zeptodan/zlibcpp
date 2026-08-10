#include<gtest/gtest.h>
#include<array>
#include<thread>
#include"zstl/locked_stack.hpp"
TEST(locked_stack_test, stack_add_pop){
    locked_stack<int> stack;
    stack.push(5);
    std::shared_ptr<int> val = stack.pop();
    ASSERT_EQ(*val,5);
}
TEST(locked_stack_test, stack_add_try_pop){
    locked_stack<int> stack;
    int val;
    bool isval = stack.try_pop(val);
    ASSERT_EQ(isval, false);
    stack.push(5);
    isval = stack.try_pop(val);
    ASSERT_EQ(isval,true);
    ASSERT_EQ(val,5);
}
TEST(parallel_locked_stack_test, stack_add_pop){
    constexpr int tot_threads = 20;
    constexpr int thread_pushes = 500;
    std::atomic<int> tot_elems = tot_threads * thread_pushes;
    std::array<std::thread, tot_threads> push_threads;
    std::array<std::thread, tot_threads> pop_threads;
    std::array<int, tot_threads> push_nums{};
    std::array<std::atomic<int>, tot_threads> pop_nums{};
    locked_stack<int> stack;
    for (int i = 0; i < tot_threads;i++){
        push_threads[i] = std::thread([i, &push_nums, &stack](){
            while(push_nums[i]++ < 500){
                stack.push(i);
            }
        });
    }
    for (int i = 0; i < tot_threads;i++){
        pop_threads[i] = std::thread([&tot_elems, &pop_nums, &stack](){
            while(tot_elems-- > 0){
                pop_nums[*stack.pop()]++;
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
TEST(parallel_locked_stack_test, stack_add_try_pop){
    constexpr int tot_threads = 20;
    constexpr int thread_pushes = 500;
    std::atomic<int> tot_elems = tot_threads * thread_pushes;
    std::array<std::thread, tot_threads> push_threads;
    std::array<std::thread, tot_threads> pop_threads;
    std::array<int, tot_threads> push_nums{};
    std::array<std::atomic<int>, tot_threads> pop_nums{};
    locked_stack<int> stack;
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
