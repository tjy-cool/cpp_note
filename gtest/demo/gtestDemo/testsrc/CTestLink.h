#ifndef __CTESTLINK_H
#define __CTESTLINK_H

#include "CLink.h"
#include "gtest/gtest.h"

class CTestLink : public testing::Test
{
public:
    virtual void SetUp();
    virtual void TearDown();
private:
    CLink link;
};

#endif