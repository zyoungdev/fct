#include "fct.h"
#include <functional>
#include <chrono>

using namespace fct;

uint f( uint x )
{
  return x + x;
}
/*
 * map Function_W{ f } over `as` n times
 */
auto test1( uint n, Vec<Int>& as )
{
  std::cout << "--- Function_W\n";
  auto begin = std::chrono::high_resolution_clock::now();
  {
    for (uint i = 0 ; i < n ; i++)
    {
      auto x = fmap<Int>( Function_W{ f }, as );
      x = x;
    }
  }
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> diff = end - begin;

  std::cout << "Run time: " << diff.count() << "ms\n\n";

  return diff;
}

/*
 * map std::function{ f } over `as` n times
 */
auto test2( uint n, Vec<Int>& as )
{
  std::cout << "--- std::function\n";
  auto begin = std::chrono::high_resolution_clock::now();
  {
    for (uint i = 0 ; i < n ; i++)
    {
      auto x = fmap<Int>( std::function<int(int)>{ f }, as );
      x = x;
    }
  }
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> diff = end - begin;

  std::cout << "Run time: " << diff.count() << "ms\n\n";

  return diff;
}

/*
 * map toFct( f ) over `as` n times
 */
auto test3( uint n, Vec<Int>& as )
{
  std::cout << "--- toFct\n";
  auto begin = std::chrono::high_resolution_clock::now();
  {
    for (uint i = 0 ; i < n ; i++)
    {
      auto x = fmap<Int>( toFct( f ), as );
      x = x;
    }
  }
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> diff = end - begin;

  std::cout << "Run time: " << diff.count() << "ms\n\n";

  return diff;
}

/*
 * map lambda over `as` n times
 */
auto test4( uint n, Vec<Int>& as )
{
  auto f1 = [](int x){ return x * x; };

  std::cout << "--- Lambda\n";
  auto begin = std::chrono::high_resolution_clock::now();
  {
    for (uint i = 0 ; i < n ; i++)
    {
      auto x = fmap<Int>( f1, as );
      x = x;
    }
  }
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> diff = end - begin;

  std::cout << "Run time: " << diff.count() << "ms\n\n";

  return diff;
}

/*
 * map lambda | lambda composition over `as` n times
 */
auto test5( uint n, Vec<Int>& as )
{
  auto f1 = [](int x){ return x * x; };

  std::cout << "--- Lambda | Lambda Composition\n";
  auto begin = std::chrono::high_resolution_clock::now();
  {
    for (uint i = 0 ; i < n ; i++)
    {
      auto x = fmap<Int>( f1 | f1, as );
      x = x;
    }
  }
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> diff = end - begin;

  std::cout << "Run time: " << diff.count() << "ms\n\n";

  return diff;
}

/*
 * map Function_W{ f } | Function_W{ f } composition over `as` n times
 */
auto test6( uint n, Vec<Int>& as )
{
  std::cout << "--- Function_W | Function_W Composition\n";
  auto begin = std::chrono::high_resolution_clock::now();
  {
    for (uint i = 0 ; i < n ; i++)
    {
      auto x = fmap<Int>( Function_W{f} | Function_W{f}, as );
      x = x;
    }
  }
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> diff = end - begin;

  std::cout << "Run time: " << diff.count() << "ms\n\n";

  return diff;
}

int main()
{
  auto as = Vec<Int>{ 1,2,3,4 };

  uint n = 1000000;

  std::cout << "\n**************************************************\n"
            << "* map the function over the input vector n times *\n"
            << "**************************************************\n\n";

  auto diff1 = test4( n, as ); // Lambda
  auto diff2 = test2( n, as ); // std::function
  auto diff3 = test3( n, as ); // toFct
  auto diff4 = test1( n, as ); // Function_W

  std::cout << "******************************************************************\n"
            << "* map the composition of functions over the input vector n times *\n"
            << "******************************************************************\n\n";

  auto diff5 = test5( n, as ); // Lambda | Lambda
  auto diff6 = test6( n, as ); // Function_W | Function_W

  std::cout << "***********\n"
            << "* Results *\n"
            << "***********\n\n";

  std::cout << "-- Ratios -- (Lower is better)\n"
            << "Lambda:        " << diff1.count() / diff1.count() << "\n"
            << "std::function: " << (float) diff2.count() / diff1.count() << "\n"
            << "toFct:         " << (float) diff3.count() / diff1.count() << "\n"
            << "Function_W:    " << (float) diff4.count() / diff1.count() << "\n\n";

  std::cout << "-- Composition Ratios -- (Lower is better)\n"
            << "Lambda Lambda:         " << diff5.count() / diff5.count() << "\n"
            << "Function_W Function_W: " << (float) diff6.count() / diff5.count() << "\n";
}
