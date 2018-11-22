#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "maths.h"


TEST(math, add)
{
   uint32_t result = add(15,30);
   EXPECT_EQ(result, 45); 
}

TEST(math, sub)
{
  uint32_t result = sub(50,10);
  EXPECT_EQ(result, 40);
}

TEST(math, mul)
{
  uint32_t result = mul(10,10);
  EXPECT_EQ(result, 100);
}
