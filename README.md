# Functional Programming Library for C++

Try your hand at functional programming in C++ by harnessing the power of mirrored Haskell functions.

## Prerequisites

* [http://en.cppreference.com/w/cpp/compiler_support](C++17 compatible compiler) (need std::optional)
* [https://gitlab.kitware.com/cmake/cmake](CMake)
* [https://github.com/catchorg/Catch2](Catch2) (for tests)

## Why?

Maybe you've been reading about functional programming but don't want to dive in head first. Maybe you keep writing the same functions over and over and need something solid to rely on. Maybe you think C++ isn't difficult enough to use so you want to add an extra layer of fun!

## What Can I Do?

```C++
// a :: [Double]
auto as = Vec<Double>{ 1.1,7.7,3.3,9.9,5.5 };
// b :: [Int]
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
print( a );
print( b );
```

As this code snippet demonstrates, you can compose functions without affecting the original objects as every function defines its inputs as constant.

Here is the the same thing hand written in C++ without the `<algorithm>` library.

```C++
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

## Installation

* (Optional) Install [https://github.com/catchorg/Catch2](Catch2) using your distribution's package manager or download it manually and install it to `/usr/lib/catch`
* `> cd ~`
* `> git clone https://github.com/zyisrad/fct`
* `> mkdir fct_build; cd fct_build`
* `> cmake ~/fct`
* `> make fct_test && ./fct_test`

## Strings

In Haskell `String` is equivalent to `[Char]` and they are both implicitly covertable to eachother. In order to make this library consistent without the need to overload every function with an equivalent `std::string` version, `std::string` has been type aliased as `StdString` and `std::vector<char>` has been type aliased as `String`. Convenience functions follow:

```C++
// toStr :: StdString -> String
auto toStr( StdString const& x ) -> String

// toStdStr :: String -> StdString
auto toStdStr( String const& xs ) -> StdString

// Str :: const Char* -> String
auto Str( const Char* x ) -> String
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
* If you can't get [https://github.com/catchorg/Catch2](Catch2) working, copy and paste code snippets from `tests.cpp` into `main()`
