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
    unordered_map<int, int> map;
    map[4] = 5;
    EXPECT_EQ(map.contains(4), true);
    map.erase(4);
    EXPECT_EQ(map.contains(4),false);
    map.erase(4);
    EXPECT_EQ(map.contains(4), false);
}
TEST(unordered_map_test, constructor_test){
    unordered_map<int, int> map;
    map[4] = 5;
    unordered_map<int, int> map2(map);
    EXPECT_EQ(map2.contains(4),true);
    EXPECT_EQ(map2[4],5);
    unordered_map<int, int> map3(std::move(map));
    EXPECT_EQ(map3[4],5);
    map = map2;
    EXPECT_EQ(map[4], 5);
    map3[1] = 2;
    map = std::move(map3);
    EXPECT_EQ(map[1], 2);
}
TEST(unordered_map_test, obj_test){
    unordered_map<std::string, std::string> map;
    map["huh"] = "yeah";
    EXPECT_EQ(map["huh"], "yeah");
    std::string str("yolo");
    map[str] = str;
    EXPECT_EQ(map[str], str);
}
TEST(unordered_map_test, compat_test){
    unordered_map<int, int> map;
    map[1] = 2;
    map[3] = 4;
    map[5] = 6;
    for(auto it = map.begin();it != map.end();++it) {}
    EXPECT_EQ(std::distance(map.begin(), map.end()), map.size());
}