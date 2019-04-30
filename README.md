[![pipeline status](https://gitlab.com/zerovectorspace/fct/badges/master/pipeline.svg)](https://gitlab.com/zerovectorspace/fct/commits/master)

# Functional Programming Library for C++

Try your hand at pure functional programming in C++ by harnessing the power of the various Haskell libraries.

## Prerequisites

* [C++17 compatible compiler](http://en.cppreference.com/w/cpp/compiler_support) (need std::optional)
* [CMake](https://gitlab.kitware.com/cmake/cmake)
* [Catch2](https://github.com/catchorg/Catch2) (for tests)

## Why?

Maybe you've been reading about functional programming but don't want to dive in head first. Maybe you keep writing the same functions over and over and need something solid to rely on. Maybe you think C++ isn't difficult enough to use so you want to add an extra layer of fun!

## What Can I Do?

```c++
// as :: [Double]
auto as = Vec<Double>{ 1.1,7.7,3.3,9.9,5.5 };
// bs :: [Int]
auto bs = Vec<Int>{ 6,2,8,4,10 };

// square :: Int -> Int
auto square = []( auto& x ){ return x * x; };
// round_p2 :: Double -> Int
auto round_p2 = []( auto& x ){ return round( x ) + 2; };

// 1. Round all numbers in a, add 2 to each
// 2. Zip the rounded list of a and b into a Vec<Int>
//    of the maxes between matching indices
// 3. Square those maxes into a Vec<Int>
// 4. Print

print( fmap<Int>( square, zipWith<Int>( max<Int>, fmap<Int>( round_p2, as ), bs ) ) );
print( as );
print( bs );
```

As this code snippet demonstrates, you can compose functions without affecting the original objects as every function defines its inputs as constant.

Here is the the same thing hand written in C++ without the `<algorithm>` library.

```c++
auto as = std::vector<double>{ 1.1,7.7,3.3,9.9,5.5 };
auto bs = std::vector<int>{ 6,2,8,4,10 };

for ( auto& a : as )
  a = std::round( a ) + 2;

auto cs = std::vector<int>{};
auto a_p = std::begin( as );
auto b_p = std::begin( bs );

while ( a_p < std::end( as ) && b_p < std::end( bs ) )
{
  cs.push_back( *a_p >= *b_p ? *a_p : *b_p );
  std::advance( a_p, 1 );
  std::advance( b_p, 1 );
}

for ( auto& c : cs )
  c = c * c;

print( cs );
```

### Function Composition

Unfortunately, C++ does not allow you to change the language so overloading `operator |` for two non-lambda functions is impossible. Though, we are still able to overload `operator |` for two lambdas which means we can wrap non-lambda functions in lambdas or wrap them with `std::function`. A helper function `toFct` is also available to wrap functions with `Function_W` and `toStdFct` to wrap functions with `std::function`.

```c++
template <typename S, typename T>
auto f1( S x ) -> T
{
  return x + 1;
}

int main()
{
  auto as = Vec<Int>{ 1, 2, 3, 4 };

  // Lambda
  auto f2 = [](Int x){ return x * x; };

  // Function wrapped with lambda
  auto f3 = [](Int x){ return f1<Int,Int>( x ); };

  // Function wrapped with std::function
  auto f4 = Function<Int(Int)>{ f1<Int,Int> };

  auto bs = fmap<Bool>( toStdFct( even ) | f4 | f3 | f2 | toFct( f1<Int,Int> ), as );

  REQUIRE( bs == Vec<Bool>{ True, False, True, False } );
}
```

### Pretty Print `classes`, `structs`, and `enums`

To utilize `fct::print()` for `classes`, `structs`, or `enums`, simply define an overloaded instance of `fct::show()` which takes the `class`, `struct`, or `enum` as a parameter and returns a `String`.

```c++
#include "fct.h"

using namespace fct;

enum class Color {
  RED,
  GREEN,
  BLUE
};

// show :: Color -> String
auto show( Color const& c ) -> String
{
  if ( c == Color::RED )
    return "RED"_s;
  if ( c == Color::GREEN )
    return "GREEN"_s;
  if ( c == Color::BLUE )
    return "BLUE"_s;

  return ""_s;
}

int main()
{
  Color r = Color::RED;
  Color g = Color::GREEN;
  Color b = Color::BLUE;

  print( r );
  print( g );
  print( b );
}
```

## Installation

(Optional) Install [Catch2](https://github.com/catchorg/Catch2) using your distribution's package manager or download it manually and install it to `/usr/lib/catch2`

```bash
> cd ~
> git clone https://gitlab.com/zerovectorspace/fct
> mkdir fct_build; cd fct_build
> cmake ~/fct
> make tests && ./tests
```

## Strings

In Haskell `String` is equivalent to `[Char]` and they are both implicitly convertable to eachother. In order to make this library consistent without the need to overload every function with an equivalent `std::string` version, `std::string` has been type aliased as `StdString` and `std::vector<char>` has been type aliased as `String`. Convenience functions follow:

```c++
// toStr :: StdString -> String
auto toStr( StdString const& x ) -> String

// toStdStr :: String -> StdString
auto toStdStr( String const& xs ) -> StdString

// Str :: const Char* -> String
auto Str( const Char* x ) -> String

// operator "" _s :: const Char* -> std::size_t -> String
auto operator "" _s( const Char* x, std::size_t s ) -> String
```

## Caveats

* Heavily templated so compilation is slow and binary is large
* Composing functions is not as nice as Haskell, requires making intermediary lambda functions
* Functions that take a `[T]` as input need to have the `push_back` method available (vector, dequeue, list)
* Functions that may return Nothing will return `std::optional<T>`
* Heavily experimental
* It may work, it may explode the universe

## Troubleshooting
* If you get a compilation error that contains `<unresolved overloaded function type>`, you need to specify either the output or the input type as a template argument. In the previous example `max<Int>` is specifying `Int` as a template argument for the input type and `fmap<Int>` is specifying `Int` as a template argument for the output type.
* If you can't get [Catch2](https://github.com/catchorg/Catch2) working, copy and paste code snippets from `tests.cpp` into `main()`
