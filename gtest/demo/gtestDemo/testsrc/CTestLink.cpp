
#include <iostream>
#include "CTestLink.h"

using namespace std;

void CTestLink::SetUp()
{
    cout<<"SetUp"<<endl;
    for(int i=1;i<=5;i++)
        link.PushBack(i);
}

void CTestLink::TearDown()
{
    cout<<"TearDown"<<endl;
    link.Destroy();
}

// TEST_F(CTestLink,PushBack)
// {
//     ASSERT_FALSE(link.pHead == NULL);
//     link.PushBack(9);
//     LinkNode *res=link.FindNode(9);
//     ASSERT_FALSE(res == NULL);
// }
 
// TEST_F(CTestLink,PopBack)
// {
//     for(int i=1;i<=5;i++)
//         link.PopBack();
// }
 
// TEST_F(CTestLink,FindNode)
// {
//     ASSERT_TRUE(link.FindNode(3));
//     ASSERT_TRUE(link.FindNode(2));
//     ASSERT_TRUE(link.FindNode(4));
//     ASSERT_TRUE(link.FindNode(5));
//     ASSERT_TRUE(link.FindNode(1));
//     ASSERT_FALSE(link.FindNode(7));
// }
 
// TEST_F(CTestLink,Delete12123)
// {
//     ASSERT_FALSE(link.pHead == NULL);
//     ASSERT_TRUE(link.Delete(3) == true);
//     ASSERT_TRUE(link.Delete(9) == false);
// }

TEST(Test, simple)
{
    ASSERT_EQ(1,1);
}