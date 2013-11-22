#include "CppUTest/TestHarness.h" 

TEST_GROUP(db_test)
{
  void setup()
  {
  }
};

TEST(db_test, put_get)
{
  CHECK_EQUAL("hello", "hello");
  CHECK_EQUAL("hello", "bello");
}
