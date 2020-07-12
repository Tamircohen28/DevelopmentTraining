#include "pch.h"
#include "gtest/gtest.h"

int add(int x, int y) { return x + y; }
int multiply(int x, int y) { return x * y; }

TEST(maths, AddTest) {
  EXPECT_EQ(add(5, 4), 9);
}

TEST(maths, MulTest) {
	EXPECT_EQ(multiply(5, 4), 20);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}