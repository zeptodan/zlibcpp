#include<gtest/gtest.h>
#include"zstl/unordered_map.hpp"
TEST(unordered_map_test, add_test){
    unordered_map<int,int> map;
    map[4] = 5;
    EXPECT_EQ(map[4], 5);
    map[4] = 7;
    EXPECT_EQ(map[4], 7);
    map[1] = 3;
    map[2] = 4;
    map[3] = 5;
    map[5] = 6;
    map[6] = 8;
    map[7] = 9;
    map[8] = 1;
    map[9] = 10;
    map[10] = 23;
    map[11] = 31;
    EXPECT_EQ(map[11],31);
    EXPECT_EQ(map[7],9);
}
TEST(unordered_map_test, erase_test){

}
TEST(unordered_map_test, constructor_test){

}
TEST(unordered_map_test, obj_test){

}
TEST(unordered_map_test, compat_test){
    
}