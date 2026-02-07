#define BOOST_TEST_MODULE My_Tests
#include <boost/test/included/unit_test.hpp>
//#include<C:/boost/boost_1_88_0/boost/test/test_tools.hpp>
//#include<boost/test/test_tools.hpp>
#include "MyAllocator.h"
#include"factorial.h"
#include"MyContainer.h"

BOOST_AUTO_TEST_SUITE(Tests)

BOOST_AUTO_TEST_CASE(test_factorial)
{
 BOOST_TEST(1 == 1);
  BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE(test_factorial_NULL) {
    BOOST_TEST(factorial(0) == 1);
        BOOST_TEST(true);

    BOOST_CHECK_EQUAL(factorial(0), 1);
    BOOST_CHECK_EQUAL(factorial(5), 120);
    BOOST_CHECK_EQUAL(factorial(10), 3628800);
}

BOOST_AUTO_TEST_CASE(FactorialNegative) {
   BOOST_TEST_EXPECTED_FAILURE(true);
    BOOST_CHECK_EQUAL(factorial(-5), -1);
}

BOOST_AUTO_TEST_CASE(TestAllocator)
{
    MyAllocator<std::pair<const int, int>> map_alloc(10);
    BOOST_TEST(map_alloc.max_elements == 10);
   
}
BOOST_AUTO_TEST_CASE(TestContainer)
{
    MyAllocator<int> myAlloc;
    MyContainer<int, MyAllocator<int>> my_cont2(myAlloc);
      
    BOOST_TEST(my_cont2.empty() == true);
    for (int i = 0; i < 10; ++i) {
        my_cont2.push_back(i);
    }
    BOOST_TEST(my_cont2.empty() == false);
    BOOST_TEST(my_cont2.size() == 10);
    BOOST_TEST(my_cont2.at(0) == 0);
    BOOST_TEST(my_cont2.at(1) == 1);
}
BOOST_AUTO_TEST_SUITE_END()
