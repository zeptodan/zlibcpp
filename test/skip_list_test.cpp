#include<gtest/gtest.h>
#include"zstl/skip_list.hpp"
TEST(skip_list_test, insert_test){
    skip_list<int, int> sl;
    sl[4] = 5;
    EXPECT_EQ(sl[4], 5);
    sl[4] = 3;
    EXPECT_EQ(sl[4], 3);
    int i = 5;
    int j = 7;
    sl[i] = j;
    EXPECT_EQ(sl[i], j);
}
TEST(skip_list_test, delete_test){
    skip_list<int, int> sl;
    sl[4] = 5;
    EXPECT_EQ(sl.erase(4), 1);
    EXPECT_EQ(sl.contains(4), false);
    EXPECT_EQ(sl.erase(4), 0);
}
TEST(skip_list_test, constructor_test){
    skip_list<int, int> sl;
    sl[4] = 5;
    skip_list<int, int> sl2(sl);
    EXPECT_EQ(sl2.contains(4), true);
    skip_list<int, int> sl3(std::move(sl));
    EXPECT_EQ(sl3.contains(4), true);
    // sl2[5] = 6;
    // sl = sl2;
    // EXPECT_EQ(sl[5], 6);
    // sl3 = std::move(sl);
    // EXPECT_EQ(sl3[5], 6);
}
TEST(skip_list_test, compat_test){
    skip_list<int, int> sl;
    sl[1] = 2;
    sl[3] = 4;
    sl[5] = 6;
    for(auto start = sl.begin();start != sl.end();start++){}
    EXPECT_EQ(std::distance(sl.begin(), sl.end()), sl.size());
}
TEST(skip_list_test, obj_test){
    skip_list<std::string, std::string> sl;
    sl["huh"] = "yo";
    EXPECT_EQ(sl["huh"], "yo");
    std::string str1("naw");
    std::string str2("dude");
    sl[str1] = str2;
    EXPECT_EQ(sl[str1], str2);
}