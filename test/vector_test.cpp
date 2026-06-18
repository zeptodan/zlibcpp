#include<gtest/gtest.h>
#include"zstl/vector.hpp"
TEST(vector_tests, vector_add){
    vector<int> vec;
    vec.add(4);
    ASSERT_EQ(vec.get(0),4);
}