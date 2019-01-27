#include "gtest/gtest.h"
// g++ -std=c++11 -o sampleDemo -L../lib -lgtest -I../include sampleDemo.cpp
TEST(Test, simple)
{
    // 二进制比较
    ASSERT_EQ(1,1);     // 等于
    ASSERT_NE(1,2);     // 不等于
    ASSERT_GE(2,1);     // 大于等于
    ASSERT_GT(2,1);     // 大于
    ASSERT_LE(1,1);     // 小于等于
    ASSERT_LT(1,2);     // 小于


}

int main(int argc,char *argv[])
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS(); //开始所有测试
}
