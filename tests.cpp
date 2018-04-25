#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "fct.h"
using namespace fct;

TEST_CASE( "head :: [T] -> Opt<T>", "[head]")
{
  Vec<int> a = { 1, 2, 3 };
  REQUIRE( head( a ).value() == 1 );

  Vec<int> b{};
  REQUIRE( head( b ).has_value() == false );
}

TEST_CASE( "last :: [T] -> Opt<T>", "[last]")
{
  Vec<int> a = { 1, 2, 3 };
  REQUIRE( last( a ).value() == 3 );

  Vec<int> b{};
  REQUIRE( last( b ).has_value() == false );
}

TEST_CASE( "fmap :: ( S -> T ) -> [S] -> [T]", "[fmap]" )
{
  Vec<int> a = { 1, 2, 3 };
  auto a_sq = fmap<int, int>( []( auto& x ){ return x * x; }, a );

  REQUIRE( a_sq == Vec<int>{1,4,9} );

  Vec<int> b{};
  auto b_sq = fmap<int, int>( []( auto& x ){ return x * x; }, b );

  REQUIRE( b_sq == Vec<int>{} );

  auto a_ch = fmap<int, char>( []( auto& x ){ return 'a' + x; }, a );
  REQUIRE( a_ch == Vec<char>{'b','c','d'} );
}

TEST_CASE( "transpose :: [[T]] -> [[T]]", "[transpose]" )
{
  Vec<Vec<int>> a = { {1,2,3},{4,5,6},{7,8,9} };
  auto a_tr = transpose( a );

  REQUIRE( a_tr == Vec<Vec<int>>{{1,4,7},{2,5,8},{3,6,9}} );

  Vec<Vec<int>> b{};
  auto b_tr = transpose( b );

  REQUIRE( b_tr == Vec<Vec<int>>{} );

  Vec<Vec<int>> c = { {1,2,3},{4,5},{7} };
  auto c_tr = transpose( c );

  REQUIRE( c_tr == Vec<Vec<int>>{{1,4,7},{2,5},{3}} );
}

TEST_CASE( "filter :: ( T -> bool ) -> [T]", "[filter]" )
{
  Vec<int> a = { 1,2,3,4,5,6,7,8,9 };
  auto a_filt = filter( []( auto& x ){ return x > 5; }, a );

  REQUIRE( a_filt == Vec<int>{ 6,7,8,9 } );

  Vec<int> b{};
  auto b_filt = filter( []( auto& x ){ return x > 5; }, b );

  REQUIRE( b_filt == Vec<int>{} );
}

TEST_CASE( "takeWhile :: ( T -> bool ) -> [T] -> [T]", "[takeWhile]" )
{
  Vec<int> a = { 1,2,3,4,5,6,7,8,9 };
  auto a_tw = takeWhile( []( auto& x ){ return x < 5; }, a );

  REQUIRE( a_tw == Vec<int>{ 1,2,3,4 } );

  Vec<int> b{};
  auto b_tw = takeWhile( []( auto& x ){ return x < 5; }, b );

  REQUIRE( b_tw == Vec<int>{} );
}

TEST_CASE( "dropWhile :: ( T -> bool ) -> [T] -> [T]", "[dropWhile]" )
{
  Vec<int> a = { 1,2,3,4,5,6,7,8,9 };
  auto a_dw = dropWhile( []( auto& x ){ return x < 5; }, a );

  REQUIRE( a_dw == Vec<int>{ 5,6,7,8,9 } );

  Vec<int> b{};
  auto b_dw = dropWhile( []( auto& x ){ return x < 5; }, b );

  REQUIRE( b_dw == Vec<int>{} );
}

TEST_CASE( "subsets :: [T] -> [[T]]", "[subsets]" )
{
  Vec<int> a = { 1,2,3 };
  auto a_ss = subsets( a );

  REQUIRE( a_ss == Vec<Vec<int>>{ {},{1},{2},{1,2},{3},{1,3},{2,3},{1,2,3} } );

  Vec<int> b{};
  auto b_ss = subsets( b );

  REQUIRE( b_ss == Vec<Vec<int>>{ Vec<int>{} } );
}

TEST_CASE( "even :: Num -> bool", "[even]" )
{
  int a = 2;
  long b = 2;

  REQUIRE( even( a ) == true );
  REQUIRE( even( a + 1 ) == false );
  REQUIRE( even( b ) == true );
  REQUIRE( even( b + 1 ) == false );

  REQUIRE( even( 0 ) == true );
}

TEST_CASE( "odd :: Num -> bool", "[odd]" )
{
  int a = 1;
  long b = 1;

  REQUIRE( odd( a ) == true );
  REQUIRE( odd( a + 1 ) == false );
  REQUIRE( odd( b ) == true );
  REQUIRE( odd( b + 1 ) == false );

  REQUIRE( odd( 0 ) == false );
}

TEST_CASE( "abs :: Num -> Num", "[abs]" )
{
  int a = 1;
  int b = -1;
  int c = 0;
  int d = -0;

  REQUIRE( abs( a ) == 1 );
  REQUIRE( abs( b ) == 1 );
  REQUIRE( abs( c ) == 0 );
  REQUIRE( abs( d ) == 0 );
}
