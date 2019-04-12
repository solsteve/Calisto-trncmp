#include <limits.h>
#include "trncmp.hh"
#include "gtest/gtest.h"

namespace {

TEST(version, Positive) {
  EXPECT_EQ("3.1.0dev", version());
}

TEST(version, Negative) {
  EXPECT_NE("3.2.0dev", version());
}


}
