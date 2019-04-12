#include <limits.h>
#include "trncmp.hh"
#include "gtest/gtest.h"

namespace {

TEST(author, Positive) {
  EXPECT_EQ("Stephen W. Soliday", author());
}

TEST(author, Negative) {
  EXPECT_NE("Stephen Soliday", author());
}

}
