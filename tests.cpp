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

TEST_CASE( "quotRem :: (Integral a) => T -> T -> ( a, a )", "[quotRem]" )
{
  int a = 3;
  int b = 2;
  int c = 0;

  REQUIRE( quotRem( a, b ) == Tup<int, int>( 1, 1 ) );
  REQUIRE( quotRem( b, a ) == Tup<int, int>( 0, 2 ) );
  REQUIRE( quotRem( c, a ) == Tup<int, int>( 0, 0 ) );
}

TEST_CASE( "gcd :: T -> T -> T", "[gcd]" )
{
  REQUIRE( gcd( 0, 0 ) == 0 );

  REQUIRE( gcd( 12, 24 ) == 12 );
  REQUIRE( gcd( 24, 12 ) == 12 );

  REQUIRE( gcd( 17, 3 ) == 1 );
  REQUIRE( gcd( 3, 17 ) == 1 );
}

TEST_CASE( "elem :: T -> [T] -> bool", "[elem]" )
{
  Vec<int> a = { 1,2,3 };

  REQUIRE( elem( 1, a ) == true );
  REQUIRE( elem( 9, a ) == false );

  Vec<int> b{};

  REQUIRE( elem( 1, b ) == false );
}

TEST_CASE( "notElem :: T -> [T] -> bool", "[notElem]" )
{
  Vec<int> a = { 1,2,3 };

  REQUIRE( notElem( 1, a ) == false );
  REQUIRE( notElem( 9, a ) == true );

  Vec<int> b{};

  REQUIRE( notElem( 1, b ) == true );
}

TEST_CASE( "maximum :: [T] -> Opt<T>", "[maximum]" )
{
  Vec<int> a = { 1,2,3 };

  REQUIRE( maximum( a ).value() == 3 );

  Vec<int> b{};
  REQUIRE( maximum( b ).has_value() == false );
}

TEST_CASE( "minimum :: [T] -> Opt<T>", "[minimum]" )
{
  Vec<int> a = { 1,2,3 };

  REQUIRE( minimum( a ).value() == 1 );

  Vec<int> b{};
  REQUIRE( minimum( b ).has_value() == false );
}

TEST_CASE( "sum :: [T] -> T", "[sum]" )
{
  Vec<int> a = { 1,2,3 };

  REQUIRE( sum( a ) == 6 );

  Vec<int> b{};

  REQUIRE( sum( b ) == 0 );
}

TEST_CASE( "product :: [T] -> T", "[product]" )
{
  Vec<int> a = { 1,2,3 };

  REQUIRE( product( a ) == 6 );

  Vec<int> b{};

  REQUIRE( product( b ) == 1 );
}

TEST_CASE( "id :: T -> T", "[id]" )
{
  REQUIRE( id( 0 ) == 0 );
  REQUIRE( id( 1 ) == 1 );
}

TEST_CASE( "constant :: S -> T -> S", "[constant]" )
{
  REQUIRE( constant( 1, 9 ) == 1 );
  REQUIRE( constant( 'x', 1 ) == 'x' );
}

TEST_CASE( "flip :: ( S -> T -> U ) -> T -> S -> U", "[flip]" )
{
  auto f = []( auto& x, auto& y ){ return y / x; };

  REQUIRE( flip<int, int, int>( f, 3, 2 ) == 1 );
  REQUIRE( flip<int, int, int>( f, 2, 3 ) == 0 );
}

TEST_CASE( "until :: ( T -> bool ) -> ( T -> T ) -> T -> T", "[until]" )
{
  auto p = []( auto& x ){ return x > 10; };
  auto f = []( auto& x ){ return x + x; };

  REQUIRE( until( p, f, 1 ) == 16 );
}

TEST_CASE( "null :: [T] -> bool", "[null]" )
{
  Vec<int> a = { 1,2,3 };

  REQUIRE( null( a ) == false );

  Vec<int> b{};

  REQUIRE( null( b ) == true );
}

TEST_CASE( "length :: [T] -> Num", "[length]" )
{
  Vec<int> a = { 1,2,3 };

  REQUIRE( length( a ) == 3 );

  Vec<int> b{};

  REQUIRE( length( b ) == 0 );
}

TEST_CASE( "reverse :: [T] -> [T]", "[reverse]" )
{
  Vec<int> a = { 1,2,3 };

  REQUIRE( reverse( a ) == Vec<int>{ 3,2,1 } );

  Vec<int> b{};

  REQUIRE( reverse( b ) == Vec<int>{} );
}

TEST_CASE( "conjunction :: [T] -> bool", "[conjunction]" )
{
  Vec<bool> a = { true, true, true };

  REQUIRE( conjunction( a ) == true );

  Vec<bool> b = { false, false, false };

  REQUIRE( conjunction( b ) == false );

  Vec<bool> c = { true, false, true };

  REQUIRE( conjunction( c ) == false );

  Vec<bool> d{};

  REQUIRE( conjunction( d ) == true );
}

TEST_CASE( "disjunction :: [T] -> bool", "[disjunction]" )
{
  Vec<bool> a = { true, true, true };

  REQUIRE( disjunction( a ) == true );

  Vec<bool> b = { false, false, false };

  REQUIRE( disjunction( b ) == false );

  Vec<bool> c = { true, false, true };

  REQUIRE( disjunction( c ) == true );

  Vec<bool> d{};

  REQUIRE( disjunction( d ) == false );
}

TEST_CASE( "any :: ( T -> bool ) -> [T] -> bool", "[any]" )
{
  Vec<int> a = { 1,2,3 };

  auto p_even = []( auto& x ){ return even( x ); };

  REQUIRE( any( p_even, a ) == true );

  Vec<int> b = { 1,3,5 };

  REQUIRE( any( p_even, b ) == false );

  Vec<int> c{};

  REQUIRE( any( p_even, c ) == false );
}

TEST_CASE( "all :: ( T -> bool ) -> [T] -> bool", "[all]" )
{
  Vec<int> a = { 2,4,6 };

  auto p_even = []( auto& x ){ return even( x ); };

  REQUIRE( all( p_even, a ) == true );

  Vec<int> b = { 2,3,4 };

  REQUIRE( all( p_even, b ) == false );

  Vec<int> c{};

  REQUIRE( all( p_even, c ) == true );
}

TEST_CASE( "concat :: [[T]] -> [T]", "[concat]" )
{
  Vec<Vec<int>> a = { {1,2,3},{4,5,6},{7,8,9} };

  REQUIRE( concat( a ) == Vec<int>{ 1,2,3,4,5,6,7,8,9 } );

  Vec<Vec<int>> b{};

  REQUIRE( concat( b ) == Vec<int>{} );
}

TEST_CASE( "replicate :: UInt -> T - [T]", "[replicate]" )
{
  REQUIRE( replicate( 3, 'x' ) == Vec<Char>{ 'x','x','x' } );

  REQUIRE( replicate( 3, 1 ) == Vec<int>{ 1,1,1 } );

  REQUIRE( replicate( 0, 1 ) == Vec<int>{} );
}

TEST_CASE( "take :: UInt -> [T] -> [T]", "[take]" )
{
  Vec<int> a = { 1,2,3,4,5,6,7,8,9 };

  REQUIRE( take( 3, a ) == Vec<int>{ 1,2,3 } );

  REQUIRE( take( 0, a ) == Vec<int>{} );

  Vec<int> b{};

  REQUIRE( take( 3, b ) == Vec<int>{} );
}

TEST_CASE( "drop :: UInt -> [T] -> [T]", "[drop]" )
{
  Vec<int> a = { 1,2,3,4,5,6,7,8,9 };

  REQUIRE( drop( 3, a ) == Vec<int>{ 4,5,6,7,8,9 } );

  REQUIRE( drop( 0, a ) == Vec<int>{ 1,2,3,4,5,6,7,8,9 } );

  Vec<int> b{};

  REQUIRE( drop( 3, b ) == Vec<int>{} );
}
