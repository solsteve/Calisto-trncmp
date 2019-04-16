#include <limits.h>
#include "trncmp.hh"
#include "gtest/gtest.h"

namespace {

TEST(version, Positive) {
  EXPECT_STREQ("3.0.1", trncmpVersion());
}

TEST(version, Negative) {
  EXPECT_STRNE("3.1.1", trncmpVersion());
}

}
