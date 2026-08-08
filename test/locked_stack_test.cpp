#include<gtest/gtest.h>
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
TEST(parallel_locked_stack_test, stack_add){

}
TEST(parallel_locked_stack_test, stack_pop){
    
}
TEST(parallel_locked_stack_test, stack_try_pop){

}
TEST(parallel_locked_stack_test, even_stack_add_pop){

}
