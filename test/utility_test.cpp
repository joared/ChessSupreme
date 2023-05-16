#include <gtest/gtest.h>
#include "utility.h"

TEST(UtilityTest, SplitString)
{
    std::vector<std::string> split1 = Utils::splitString("xxx/yyyyy/zz", "/");
    ASSERT_EQ(3, split1.size());
    ASSERT_EQ("xxx", split1[0]);
    ASSERT_EQ("yyyyy", split1[1]);
    ASSERT_EQ("zz", split1[2]);
    
    std::vector<std::string> split2 = Utils::splitString("xxx/yyyyy zz", " ");
    ASSERT_EQ(2, split2.size());
    ASSERT_EQ("xxx/yyyyy", split2[0]);
    ASSERT_EQ("zz", split2[1]);
    
};