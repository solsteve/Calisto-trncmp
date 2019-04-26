#include <limits.h>
#include "trncmp.hh"
#include "gtest/gtest.h"


namespace {


TEST(author, Positive) {
  EXPECT_STREQ("Stephen Soliday", trncmpAuthor());
}


TEST(author, Negative) {
  EXPECT_STRNE("Stephen X. Soliday", trncmpAuthor());
}


}
