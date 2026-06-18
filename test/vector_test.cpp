#include<gtest/gtest.h>
#include"zstl/vector.hpp"
TEST(vector_tests, vector_add){
    vector<int> vec;
    vec.add(4);
    ASSERT_EQ(vec.get(0),4);
    int i = 5;
    vec.add(i);
    ASSERT_EQ(vec.get(1),5);
    vec.add(4);
    vec.add(4);
    vec.add(4);
    vec.add(4);
    vec.add(4);
    vec.add(4);
    vec.add(4);
    ASSERT_EQ(vec.is_full(),false);
    ASSERT_EQ(vec.size(),9);
    ASSERT_EQ(vec.capacity(),10);
    vec.add(4);
    ASSERT_EQ(vec.is_full(),false);

}