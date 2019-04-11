#include <limits.h>
#include "trncmp.hh"
#include "gtest/gtest.h"

namespace {

TEST(version, Positive) {
  EXPECT_EQ("3.1.0dev", version());
}


TEST(author, Positive) {
  EXPECT_EQ("Stephen W. Soliday", author());
}

}
