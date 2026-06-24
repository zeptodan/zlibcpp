#include<gtest/gtest.h>
#include<algorithm>
#include<numeric>
#include"zstl/vector.hpp"
TEST(vector_tests, vector_add){
    vector<int> vec;
    vec.push_back(4);
    ASSERT_EQ(vec.get(0),4);
    int i = 5;
    vec.push_back(i);
    ASSERT_EQ(vec.get(1),5);
    vec.push_back(4);
    vec.push_back(4);
    vec.push_back(4);
    vec.push_back(4);
    vec.push_back(4);
    vec.push_back(4);
    vec.push_back(4);
    ASSERT_EQ(vec.is_full(),false);
    ASSERT_EQ(vec.size(),9);
    ASSERT_EQ(vec.capacity(),10);
    vec.push_back(4);
    ASSERT_EQ(vec.is_full(),false);
    ASSERT_EQ(vec.capacity(),15);
}
TEST(vector_tests, vector_sub){
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.erase(0);
    EXPECT_EQ(vec.size(),1);
    EXPECT_EQ(vec[0],2);
}
TEST(vector_tests, vector_iterator_test){
    int nums[5] = {1,2,3,4,5};
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    int i = 0;
    for(int num : vec){
        EXPECT_EQ(num, nums[i]);
        i++;
    }
}
TEST(vector_tests, vector_resize_iterator_test){
    int nums[10] = {1,2,3,4,5,6,7,8,9,10};
    vector<int> vec;
    vec.push_back(0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(6);
    vec.push_back(7);
    vec.push_back(8);
    vec.push_back(9);
    vec.push_back(10);
    vec.erase(0);
    int i = 0;
    for(int num : vec){
        EXPECT_EQ(num, nums[i]);
        i++;
    }
}
TEST(vector_tests, vector_constructor_assignment_test){
    vector<int> vec{1,2,3};
    EXPECT_EQ(vec[0],1);
    EXPECT_EQ(vec[1],2);
    EXPECT_EQ(vec[2],3);
    vector<int> vec2(vec);
    EXPECT_EQ(vec2[0],1);
    EXPECT_EQ(vec2[1],2);
    EXPECT_EQ(vec2[2],3);
    vector<int> vec3(std::move(vec2));
    EXPECT_EQ(vec3[0],1);
    EXPECT_EQ(vec3[1],2);
    EXPECT_EQ(vec3[2],3);
    vector<int> vec4{1,2};
    vec4 = vec3;
    EXPECT_EQ(vec4[0],1);
    EXPECT_EQ(vec4[1],2);
    EXPECT_EQ(vec4[2],3);
    vector<int> vec5{1,2};
    vec5 = std::move(vec4);
    EXPECT_EQ(vec5[0],1);
    EXPECT_EQ(vec5[1],2);
    EXPECT_EQ(vec5[2],3);
}
TEST(vector_tests, vector_std_compat_test){
    vector<int> vec{6,3,7,2,8,1,9,4,5,0};
    std::vector<int> stdvec{6,3,7,2,8,1,9,4,5,0};
    std::sort(vec.begin(),vec.end());
    std::sort(stdvec.begin(),stdvec.end());
    for (int i = 0; i < stdvec.size();i++){
        EXPECT_EQ(stdvec[i],vec[i]);
    }
    auto it = std::find(vec.begin(),vec.end(),5);
    auto it2 = std::find(stdvec.begin(),stdvec.end(),5);
    EXPECT_EQ(*it,*it2);
    bool fd = std::binary_search(vec.begin(),vec.end(),8);
    bool fd2 = std::binary_search(stdvec.begin(),stdvec.end(),8);
    EXPECT_EQ(fd,fd2);
    int sum = std::accumulate(vec.begin(),vec.end(),0);
    int sum2 = std::accumulate(stdvec.begin(),stdvec.end(),0);
    EXPECT_EQ(sum, sum2);

}