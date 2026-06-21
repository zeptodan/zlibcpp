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
    ASSERT_EQ(vec.capacity(),15);
}
TEST(vector_tests, vector_sub){
    vector<int> vec;
    vec.add(1);
    vec.add(2);
    vec.erase(0);
    EXPECT_EQ(vec.size(),1);
    EXPECT_EQ(vec[0],2);
}
TEST(vector_tests, vector_iterator_test){
    int nums[5] = {1,2,3,4,5};
    vector<int> vec;
    vec.add(1);
    vec.add(2);
    vec.add(3);
    vec.add(4);
    vec.add(5);
    int i = 0;
    for(int num : vec){
        EXPECT_EQ(num, nums[i]);
        i++;
    }
}
TEST(vector_tests, vector_resize_iterator_test){
    int nums[10] = {1,2,3,4,5,6,7,8,9,10};
    vector<int> vec;
    vec.add(0);
    vec.add(1);
    vec.add(2);
    vec.add(3);
    vec.add(4);
    vec.add(5);
    vec.add(6);
    vec.add(7);
    vec.add(8);
    vec.add(9);
    vec.add(10);
    vec.erase(0);
    int i = 0;
    for(int num : vec){
        EXPECT_EQ(num, nums[i]);
        i++;
    }
}