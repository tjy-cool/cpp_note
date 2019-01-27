#include "HelloWorld.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MockMessenger.h"
#include <string>
#include <memory>
using namespace testing;

// g++ -std=c++11 HelloWorld.cpp HelloWorld_UnitTest.cpp -L../../lib -lgtest -lgmock -I../../include -o HelloWorld_UnitTest

TEST(HelloWorldTest, getMessage)
{
    MockMessenger messenger;
    std::string msg = "Hello World";
    EXPECT_CALL(messenger, getMessage()).WillRepeatedly(Return(ByRef(msg)));
 
    HelloWorld helloWorld;
    EXPECT_EQ("Hello World", helloWorld.getMessage(&messenger));
    EXPECT_EQ("Hello1 World", helloWorld.getMessage(&messenger));
    // EXPECT_EQ("Hello World", helloWorld.getMessage(&messenger));
    // EXPECT_EQ("Hello World", helloWorld.getMessage(&messenger));
}
 
int main(int argc, char** argv)
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
