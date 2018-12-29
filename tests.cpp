/*
  This file is part of fct.

  fct is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  fct is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with fct.  If not, see <http://www.gnu.org/licenses/>. */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "fct.h"

using namespace fct;

// #define DEBUG_IO

template <typename S, typename T>
auto f1( S x ) -> T
{
  return x + 1;
}

TEST_CASE( "FCT Composition", "[fct]" )
{
  auto as = Vec<Int>{ 1, 2, 3, 4 };

  // Lambda
  auto f2 = [](Int x){ return x * x; };

  // Function wrapped with function
  auto f3 = [](Int x){ return f1<Int,Int>( x ); };

  // Function wrapped with std::function
  // Function<Int(Int)> f4 = f1<Int,Int>;
  auto f4 = Function<Int(Int)>{ f1<Int,Int> };

  auto bs = fmap<Bool>( toFct( even ) | f4 | f3 | f2 | toFct( f1<Int,Int> ), as );

  REQUIRE( bs == Vec<Bool>{ true, false, true, false } );
}

TEST_CASE( "toStr :: StdString -> String", "[toStr]" )
{
  StdString a = "String";

  REQUIRE( toStr( a ) == Vec<Char>{ 'S','t','r','i','n','g' } );

  StdString b{};

  REQUIRE( toStr( b ) == Vec<Char>{} );
}

TEST_CASE( "toStdStr :: String -> StdString", "[toStdStr]" )
{
  String as = { 'S','t','r','i','n','g' };

  REQUIRE( toStdStr( as ) == "String" );

  String bs{};

  REQUIRE( toStdStr( bs ) == StdString{} );
}

TEST_CASE( "head :: [T] -> T", "[head]")
{
  Vec<Int> as = { 1, 2, 3 };
  REQUIRE( head( as ) == 1 );

  // Segmentation Fault
  // Vec<Int> bs{};
  // head( bs );
}

TEST_CASE( "last :: [T] -> T", "[last]")
{
  Vec<Int> as = { 1, 2, 3 };
  REQUIRE( last( as ) == 3 );

  // Segmentation Fault
  // Vec<Int> bs{};
  // last( bs );
}

TEST_CASE( "fst :: (S,T) -> S", "[fst]" )
{
  Tup<Int,Char> as = {1,'a'};

  REQUIRE( fst( as ) == 1 );
}

TEST_CASE( "snd :: (S,T) -> S", "[snd]" )
{
  Tup<Int,Char> a = {1,'a'};

  REQUIRE( snd( a ) == 'a' );
}

TEST_CASE( "fmap :: ( S -> T ) -> [S] -> [T]", "[fmap]" )
{
  Vec<Int> as = { 1, 2, 3 };
  auto a_sq = fmap<Int>( []( auto& x ){ return x * x; }, as );

  REQUIRE( a_sq == Vec<Int>{1,4,9} );

  Vec<Int> bs{};
  auto b_sq = fmap<Int>( []( auto& x ){ return x * x; }, bs );

  REQUIRE( b_sq == Vec<Int>{} );

  auto a_ch = fmap<Char>( []( auto& x ){ return 'a' + x; }, as );
  REQUIRE( a_ch == Vec<Char>{'b','c','d'} );
}

TEST_CASE( "transpose :: [[T]] -> [[T]]", "[transpose]" )
{
  Vec<Vec<Int>> as = { {1,2,3},{4,5,6},{7,8,9} };
  auto a_tr = transpose( as );

  REQUIRE( a_tr == Vec<Vec<Int>>{{1,4,7},{2,5,8},{3,6,9}} );

  Vec<Vec<Int>> bs{};
  auto b_tr = transpose( bs );

  REQUIRE( b_tr == Vec<Vec<Int>>{} );

  Vec<Vec<Int>> cs = { {1,2,3},{4,5},{7} };
  auto c_tr = transpose( cs );

  REQUIRE( c_tr == Vec<Vec<Int>>{{1,4,7},{2,5},{3}} );
}

TEST_CASE( "filter :: ( T -> Bool ) -> [T]", "[filter]" )
{
  Vec<Int> as = { 1,2,3,4,5,6,7,8,9 };
  auto a_filt = filter( []( auto& x ){ return x > 5; }, as );

  REQUIRE( a_filt == Vec<Int>{ 6,7,8,9 } );

  Vec<Int> bs{};
  auto b_filt = filter( []( auto& x ){ return x > 5; }, bs );

  REQUIRE( b_filt == Vec<Int>{} );
}

TEST_CASE( "takeWhile :: ( T -> Bool ) -> [T] -> [T]", "[takeWhile]" )
{
  Vec<Int> as = { 1,2,3,4,5,6,7,8,9 };
  auto a_tw = takeWhile( []( auto& x ){ return x < 5; }, as );

  REQUIRE( a_tw == Vec<Int>{ 1,2,3,4 } );

  Vec<Int> bs{};
  auto b_tw = takeWhile( []( auto& x ){ return x < 5; }, bs );

  REQUIRE( b_tw == Vec<Int>{} );
}

TEST_CASE( "dropWhile :: ( T -> Bool ) -> [T] -> [T]", "[dropWhile]" )
{
  Vec<Int> as = { 1,2,3,4,5,6,7,8,9 };
  auto a_dw = dropWhile( []( auto& x ){ return x < 5; }, as );

  REQUIRE( a_dw == Vec<Int>{ 5,6,7,8,9 } );

  Vec<Int> bs{};
  auto b_dw = dropWhile( []( auto& x ){ return x < 5; }, bs );

  REQUIRE( b_dw == Vec<Int>{} );
}

TEST_CASE( "subsequences :: [T] -> [[T]]", "[subsequences]" )
{
  Vec<Int> as = { 1,2,3 };
  auto a_ss = subsequences( as );

  REQUIRE( a_ss == Vec<Vec<Int>>{ {},{1},{2},{1,2},{3},{1,3},{2,3},{1,2,3} } );

  Vec<Int> bs{};
  auto b_ss = subsequences( bs );

  REQUIRE( b_ss == Vec<Vec<Int>>{ Vec<Int>{} } );
}

TEST_CASE( "even :: Num -> Bool", "[even]" )
{
  Int a = 2;
  Long b = 2;

  REQUIRE( even( a ) == true );
  REQUIRE( even( a + 1 ) == false );
  REQUIRE( even( b ) == true );
  REQUIRE( even( b + 1 ) == false );

  REQUIRE( even( 0 ) == true );
}

TEST_CASE( "odd :: Num -> Bool", "[odd]" )
{
  Int a = 1;
  Long b = 1;

  REQUIRE( odd( a ) == true );
  REQUIRE( odd( a + 1 ) == false );
  REQUIRE( odd( b ) == true );
  REQUIRE( odd( b + 1 ) == false );

  REQUIRE( odd( 0 ) == false );
}

TEST_CASE( "negate :: Num -> Num", "[negate]" )
{
  REQUIRE( negate( 1 ) == -1 );

  REQUIRE( negate( -1 ) == 1 );

  REQUIRE( negate( 0 ) == 0 );
}

TEST_CASE( "abs :: Num -> Num", "[abs]" )
{
  Int a = 1;
  Int b = -1;
  Int c = 0;
  Int d = -0;

  REQUIRE( abs( a ) == 1 );
  REQUIRE( abs( b ) == 1 );
  REQUIRE( abs( c ) == 0 );
  REQUIRE( abs( d ) == 0 );
}

TEST_CASE( "quotRem :: T -> T -> ( T, T )", "[quotRem]" )
{
  Int a = 3;
  Int b = 2;
  Int c = 0;

  REQUIRE( quotRem( a, b ) == Tup<Int, Int>( 1, 1 ) );
  REQUIRE( quotRem( b, a ) == Tup<Int, Int>( 0, 2 ) );
  REQUIRE( quotRem( c, a ) == Tup<Int, Int>( 0, 0 ) );
}

TEST_CASE( "gcd :: Num -> Num -> Num", "[gcd]" )
{
  REQUIRE( gcd( 0, 0 ) == 0 );

  REQUIRE( gcd( 12, 24 ) == 12 );
  REQUIRE( gcd( 24, 12 ) == 12 );

  REQUIRE( gcd( 17, 3 ) == 1 );
  REQUIRE( gcd( 3, 17 ) == 1 );
}

TEST_CASE( "elem :: T -> [T] -> Bool", "[elem]" )
{
  Vec<Int> as = { 1,2,3 };

  REQUIRE( elem( 1, as ) == true );
  REQUIRE( elem( 9, as ) == false );

  Vec<Int> bs{};

  REQUIRE( elem( 1, bs ) == false );
}

TEST_CASE( "notElem :: T -> [T] -> Bool", "[notElem]" )
{
  Vec<Int> as = { 1,2,3 };

  REQUIRE( notElem( 1, as ) == false );
  REQUIRE( notElem( 9, as ) == true );

  Vec<Int> bs{};

  REQUIRE( notElem( 1, bs ) == true );
}

TEST_CASE( "max :: T -> T -> T", "[max]" )
{
  REQUIRE( max( 1, 2 ) == 2 );

  REQUIRE( max( 2, 1 ) == 2 );
}

TEST_CASE( "min :: T -> T -> T", "[min]" )
{
  REQUIRE( min( 1, 2 ) == 1 );

  REQUIRE( min( 2, 1 ) == 1 );
}

TEST_CASE( "maximum :: [T] -> T", "[maximum]" )
{
  Vec<Int> as = { 1,2,3 };

  REQUIRE( maximum( as ) == 3 );

  // Segmentation Fault
  // Vec<Int> bs{};
  // maximum( bs );
}

TEST_CASE( "minimum :: [T] -> T", "[minimum]" )
{
  Vec<Int> as = { 1,2,3 };

  REQUIRE( minimum( as ) == 1 );

  // Segmentation Fault
  // Vec<Int> bs{};
  // minimum( bs );
}

TEST_CASE( "sum :: [Num] -> Num", "[sum]" )
{
  Vec<Int> as = { 1,2,3 };

  REQUIRE( sum( as ) == 6 );

  Vec<Int> bs{};

  REQUIRE( sum( bs ) == 0 );
}

TEST_CASE( "product :: [Num] -> Num", "[product]" )
{
  Vec<Int> as = { 1,2,3 };

  REQUIRE( product( as ) == 6 );

  Vec<Int> bs{};

  REQUIRE( product( bs ) == 1 );
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

  REQUIRE( flip<Int>( f, 3, 2 ) == 1 );
  REQUIRE( flip<Int>( f, 2, 3 ) == 0 );
}

TEST_CASE( "until :: ( T -> Bool ) -> ( T -> T ) -> T -> T", "[until]" )
{
  auto p = []( auto& x ){ return x > 10; };
  auto f = []( auto& x ){ return x + x; };

  REQUIRE( until( p, f, 1 ) == 16 );
}

TEST_CASE( "null :: [T] -> Bool", "[null]" )
{
  Vec<Int> as = { 1,2,3 };

  REQUIRE( null( as ) == false );

  Vec<Int> bs{};

  REQUIRE( null( bs ) == true );
}

TEST_CASE( "length :: [T] -> Size_t", "[length]" )
{
  Vec<Int> as = { 1,2,3 };

  REQUIRE( length( as ) == 3 );

  Vec<Int> bs{};

  REQUIRE( length( bs ) == 0 );
}

TEST_CASE( "reverse :: [T] -> [T]", "[reverse]" )
{
  Vec<Int> as = { 1,2,3 };

  REQUIRE( reverse( as ) == Vec<Int>{ 3,2,1 } );

  Vec<Int> bs{};

  REQUIRE( reverse( bs ) == Vec<Int>{} );
}

TEST_CASE( "conjunction :: [T] -> Bool", "[conjunction]" )
{
  Vec<Bool> as = { true, true, true };

  REQUIRE( conjunction( as ) == true );

  Vec<Bool> bs = { false, false, false };

  REQUIRE( conjunction( bs ) == false );

  Vec<Bool> cs = { true, false, true };

  REQUIRE( conjunction( cs ) == false );

  Vec<Bool> ds{};

  REQUIRE( conjunction( ds ) == true );
}

TEST_CASE( "disjunction :: [T] -> Bool", "[disjunction]" )
{
  Vec<Bool> as = { true, true, true };

  REQUIRE( disjunction( as ) == true );

  Vec<Bool> bs = { false, false, false };

  REQUIRE( disjunction( bs ) == false );

  Vec<Bool> cs = { true, false, true };

  REQUIRE( disjunction( cs ) == true );

  Vec<Bool> ds{};

  REQUIRE( disjunction( ds ) == false );
}

TEST_CASE( "any :: ( T -> Bool ) -> [T] -> Bool", "[any]" )
{
  Vec<Int> as = { 1,2,3 };

  auto p_even = []( auto& x ){ return even( x ); };

  REQUIRE( any( p_even, as ) == true );

  Vec<Int> bs = { 1,3,5 };

  REQUIRE( any( p_even, bs ) == false );

  Vec<Int> cs{};

  REQUIRE( any( p_even, cs ) == false );
}

TEST_CASE( "all :: ( T -> Bool ) -> [T] -> Bool", "[all]" )
{
  Vec<Int> as = { 2,4,6 };

  auto p_even = []( auto& x ){ return even( x ); };

  REQUIRE( all( p_even, as ) == true );

  Vec<Int> bs = { 2,3,4 };

  REQUIRE( all( p_even, bs ) == false );

  Vec<Int> cs{};

  REQUIRE( all( p_even, cs ) == true );
}

TEST_CASE( "concat :: [[T]] -> [T]", "[concat]" )
{
  Vec<Vec<Int>> as = { {1,2,3},{4,5,6},{7,8,9} };

  REQUIRE( concat( as ) == Vec<Int>{ 1,2,3,4,5,6,7,8,9 } );

  Vec<Vec<Int>> bs{};

  REQUIRE( concat( bs ) == Vec<Int>{} );
}

TEST_CASE( "replicate :: UInt -> T - [T]", "[replicate]" )
{
  REQUIRE( replicate( 3, 'x' ) == Vec<Char>{ 'x','x','x' } );

  REQUIRE( replicate( 3, 1 ) == Vec<Int>{ 1,1,1 } );

  REQUIRE( replicate( 0, 1 ) == Vec<Int>{} );
}

TEST_CASE( "take :: UInt -> [T] -> [T]", "[take]" )
{
  Vec<Int> as = { 1,2,3,4,5,6,7,8,9 };

  REQUIRE( take( 3, as ) == Vec<Int>{ 1,2,3 } );

  REQUIRE( take( 0, as ) == Vec<Int>{} );

  Vec<Int> bs{};

  REQUIRE( take( 3, bs ) == Vec<Int>{} );
}

TEST_CASE( "drop :: UInt -> [T] -> [T]", "[drop]" )
{
  Vec<Int> as = { 1,2,3,4,5,6,7,8,9 };

  REQUIRE( drop( 3, as ) == Vec<Int>{ 4,5,6,7,8,9 } );

  REQUIRE( drop( 0, as ) == Vec<Int>{ 1,2,3,4,5,6,7,8,9 } );

  Vec<Int> bs{};

  REQUIRE( drop( 3, bs ) == Vec<Int>{} );
}

TEST_CASE( "splitAt :: UInt -> [T] -> ( [T], [T] )", "[splitAt]" )
{
  Vec<Int> as = { 1,2,3,4,5,6,7,8,9 };

  REQUIRE( splitAt( 4, as ) == Tup<Vec<Int>, Vec<Int>>{ Vec<Int>{ 1,2,3,4 }, Vec<Int>{ 5,6,7,8,9 } } );

  REQUIRE( splitAt( 0, as ) == Tup<Vec<Int>, Vec<Int>>{ Vec<Int>{}, Vec<Int>{ 1,2,3,4,5,6,7,8,9 } } );

  Vec<Int> bs = { 1,2,3 };

  REQUIRE( splitAt( 9, bs ) == Tup<Vec<Int>, Vec<Int>>{ Vec<Int>{ 1,2,3 }, Vec<Int>{} } );

  Vec<Int> cs{};

  REQUIRE( splitAt( 9, cs ) == Tup<Vec<Int>, Vec<Int>>{ Vec<Int>{}, Vec<Int>{} } );
}

TEST_CASE( "lines :: String -> [String]", "[lines]" )
{
  auto a = Str( "This\nis\na\nString\n" );

  REQUIRE( lines( a ) == Vec<String>{ "This"_s, "is"_s, "a"_s, "String"_s } );

  auto b = Str( "" );

  REQUIRE( lines( b ) == Vec<String>{} );

  auto c = Str( "This\n\nis\n\na\n\nString\n\n" );

  REQUIRE( lines( c ) == Vec<String>{ "This"_s, ""_s, "is"_s, ""_s, "a"_s, ""_s, "String"_s, ""_s } );
}

TEST_CASE( "words :: String -> [String]", "[words]" )
{
  auto a = Str( "This is a String" );

  REQUIRE( words( a ) == Vec<String>{ "This"_s, "is"_s, "a"_s, "String"_s } );

  auto b = Str( "" );

  REQUIRE( words( b ) == Vec<String>{} );
}

TEST_CASE( "unlines :: [StdString] -> StdString", "[unlines]" )
{
  Vec<String> as = { Str( "This" ), Str( "is" ), Str( "a" ), Str( "String" ) };

  REQUIRE( unlines( as ) == Str( "This\nis\na\nString\n" ) );

  Vec<String> bs{};

  REQUIRE( unlines( bs ) == String{} );
}

TEST_CASE( "unwords :: [StdString] -> StdString", "[unwords]" )
{
  Vec<String> as = { Str( "This" ),Str( "is" ),Str( "a" ),Str( "String" ) };

  REQUIRE( unwords( as ) == Str( "This is a String" ) );

  Vec<String> bs{};

  REQUIRE( unwords( bs ) == String{} );
}

#ifdef DEBUG_IO
TEST_CASE( "putChar :: Char -> void", "[putChar]" )
{
  Char a = 'a';
  print( "# Should print a: " );
  putChar( a );
  print("");
}

TEST_CASE( "putStr :: StdString -> void", "[putStr]" )
{
  StdString a = "magic";
  print( "# Should print magic: " );
  putStr( a );
  print("");
}

TEST_CASE( "putStrLn :: StdString -> void", "[putStrLn]" )
{
  StdString a = "magic";
  print( "# Should print magic: " );
  putStr( a );
  print("");
}

TEST_CASE( "getChar :: Char", "[getChar]" )
{
  print( "Please type a character: ", ' ' );
  auto a = getChar();
  print( "You typed: " + StdString{ a } );
}

TEST_CASE( "getLine :: StdString", "[getLine]" )
{
  print( "Please type a line: ", ' ' );
  auto a = getLine();
  print( "You typed: " + a );
}

TEST_CASE( "readFile :: StdString -> StdString, writeFile :: StdString -> StdString -> void", "[readFile][writeFile]" )
{
  print( "Please name file to read/write in /tmp/: ", ' ' );
  auto a = getLine();
  print( a );
  a = StdString{ "/tmp/" + a };

  writeFile( a, "DATA" );
  print( "wrote DATA to " + a );

  print( "Reading: " + a );
  auto b = readFile( a );

  print( "Appending DATA to: " + a );
  appendFile( a, b );

  print( "Reading: " + a );
  b = readFile( a );

  print( a + ": " + b );
}
#endif

TEST_CASE( "show :: T -> StdString", "[show]" )
{
  REQUIRE( show( 1 ) == "1"_s );
  REQUIRE( show( 1.999999 ) == "1.999999"_s );
}

TEST_CASE( "union :: [T] -> [T] -> [T]", "[union]" )
{
  Vec<Int> as = { 1,2,3 };
  Vec<Int> bs = { 4,5,6 };

  REQUIRE( union_of( as, bs ) == Vec<Int>{ 1,2,3,4,5,6 } );

  REQUIRE( union_of( Vec<Int>{}, Vec<Int>{} ) == Vec<Int>{} );
}

TEST_CASE( "intersperse :: T -> [T] -> [T]", "[intersperse]" )
{
  Int a = 1;
  Vec<Int> bs = { 1,2,3 };

  REQUIRE( intersperse( a, bs ) == Vec<Int>{ 1,1,2,1,3 } );

  Vec<Int> cs{};

  REQUIRE( intersperse( a, cs ) == Vec<Int>{} );
}

TEST_CASE( "intercalate :: [T] -> [[T]] -> [T]", "[intercalate]" )
{
  Vec<Int> as = { 0,0,0 };
  Vec<Vec<Int>> bs = { {1,2,3},{4,5,6},{7,8,9} };

  REQUIRE( intercalate( as, bs ) == Vec<Int>{ 1,2,3,0,0,0,4,5,6,0,0,0,7,8,9 } );

  REQUIRE( intercalate( Vec<Int>{}, bs ) == Vec<Int>{ 1,2,3,4,5,6,7,8,9 } );

  Vec<Vec<Int>> cs{};

  REQUIRE( intercalate( as, cs ) == Vec<Int>{} );

  REQUIRE( intercalate( Vec<Int>{}, cs ) == Vec<Int>{} );

}

TEST_CASE( "permutations :: [T] -> [[T]]", "[permutations]" )
{
  Vec<Int> as = { 1,2,3 };

  REQUIRE( permutations( as ) == Vec<Vec<Int>>{ {1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1} } );

  Vec<Int> bs{};

  REQUIRE( permutations( bs ) == Vec<Vec<Int>>{ Vec<Int>{} } );
}

TEST_CASE( "iterate :: (T -> T) -> T -> [T]", "[iterate]" )
{
  Int a = 2;
  auto f = []( auto& x ){ return x * x; };

  REQUIRE( iterate( 3, f, a ) == Vec<Int>{ 4,4,4 } );

  REQUIRE( iterate( 0, f, a ) == Vec<Int>{} );
}

TEST_CASE( "span :: (T -> Bool) -> [T] -> ([T], [T])", "[span]" )
{
  Vec<Int> as = { 1,2,3,4,5,6,7,8,9 };
  auto f = []( auto& x ){ return x < 5; };

  REQUIRE( span( f, as ) == Tup<Vec<Int>, Vec<Int>>{ Vec<Int>{ 1,2,3,4 }, Vec<Int>{ 5,6,7,8,9 } } );

  Vec<Int> bs{};

  REQUIRE( span( f, bs ) == Tup<Vec<Int>, Vec<Int>>{ Vec<Int>{}, Vec<Int>{} } );
}

TEST_CASE( "break_when :: (T -> Bool) -> [T] -> ([T], [T])", "[break_when]" )
{
  Vec<Int> as = { 1,2,3,4,5,6,7,8,9 };
  auto f = []( auto& x ){ return x > 5; };

  REQUIRE( break_when( f, as ) == Tup<Vec<Int>, Vec<Int>>{ Vec<Int>{ 1,2,3,4,5 }, Vec<Int>{ 6,7,8,9 } } );

  Vec<Int> bs{};

  REQUIRE( break_when( f, bs ) == Tup<Vec<Int>, Vec<Int>>{ Vec<Int>{}, Vec<Int>{} } );
}

TEST_CASE( "group :: [T] -> [[T]]", "[group]" )
{
  String a = Str( "mississippi" );

  REQUIRE( group( a ) == Vec<Vec<Char>>{ {'m'},{'i'},{'s','s'},{'i'},{'s','s'},{'i'},{'p','p'},{'i'} } );

  String bs{};
  REQUIRE( group( bs ) == Vec<Vec<Char>>{} );
}

TEST_CASE( "inits :: [T] -> [[T]]", "[inits]" )
{
  Vec<Int> as = { 1,2,3 };

  REQUIRE( inits( as ) == Vec<Vec<Int>>{ {},{1},{1,2},{1,2,3} } );

  Vec<Int> bs{};

  REQUIRE( inits( bs ) == Vec<Vec<Int>>{ Vec<Int>{} } );
}

TEST_CASE( "tails :: [T] -> [[T]]", "[tails]" )
{
  Vec<Int> as = { 1,2,3 };

  REQUIRE( tails( as ) == Vec<Vec<Int>>{ {1,2,3},{2,3},{3},{} } );

  Vec<Int> bs{};

  REQUIRE( tails( bs ) == Vec<Vec<Int>>{ Vec<Int>{} } );
}

TEST_CASE( "isPrefixOf :: [T] -> [T] -> Bool", "[isPrefixOf]" )
{
  auto a = Str( "This is a String" );
  auto b = Str( "This" );

  REQUIRE( isPrefixOf( b, a ) == true );

  auto c = Str( "is" );

  REQUIRE( isPrefixOf( c, a ) == false );

  String ds{};

  REQUIRE( isPrefixOf( ds, a ) == true );

  REQUIRE( isPrefixOf( a, ds ) == false );

  REQUIRE( isPrefixOf( ds, ds ) == true );
}

TEST_CASE( "isSuffixOf :: [T] -> [T] -> Bool", "[isSuffixOf]" )
{
  auto a = Str( "This is a String" );
  auto b = Str( "String" );

  REQUIRE( isSuffixOf( b, a ) == true );

  auto c = Str( "is" );

  REQUIRE( isSuffixOf( c, a ) == false );

  String ds{};

  REQUIRE( isSuffixOf( ds, a ) == true );

  REQUIRE( isSuffixOf( b, ds ) == false );

  REQUIRE( isSuffixOf( ds, ds ) == true );
}

TEST_CASE( "isInfixOf :: [T] -> [T] -> Bool", "[isInfixOf]" )
{
  auto a = Str( "This is a String" );
  auto b = Str( "is" );

  REQUIRE( isInfixOf( b, a ) == true );

  String ds{};

  REQUIRE( isInfixOf( ds, a ) == true );

  REQUIRE( isInfixOf( b, ds ) == false );

  REQUIRE( isInfixOf( ds, ds ) == true );
}

TEST_CASE( "partition :: ( T -> Bool ) -> [T] -> ( [T], [T] )", "partition" )
{
  Vec<Int> as = { 1,2,3,4,5,6,7,8,9,0 };

  REQUIRE( partition( even, as ) == Tup<Vec<Int>,Vec<Int>>{ Vec<Int>{2,4,6,8,0},Vec<Int>{1,3,5,7,9} } );

  Vec<Int> bs = { 1,3,5,7,9 };

  REQUIRE( partition( even, bs ) == Tup<Vec<Int>,Vec<Int>>{ Vec<Int>{},Vec<Int>{1,3,5,7,9} } );

  REQUIRE( partition( odd, bs ) == Tup<Vec<Int>,Vec<Int>>{ Vec<Int>{1,3,5,7,9},Vec<Int>{} } );

  Vec<Int> ds{};

  REQUIRE( partition( even, ds ) == Tup<Vec<Int>,Vec<Int>>{ Vec<Int>{},Vec<Int>{} } );
}

TEST_CASE( "nub :: [T] -> [T]", "[nub]" )
{
  Vec<Int> as = { 1,1,2,2,3,3 };

  REQUIRE( nub( as ) == Vec<Int>{ 1,2,3 } );

  Vec<Int> bs{};

  REQUIRE( nub( bs ) == Vec<Int>{} );
}

TEST_CASE( "sort :: [T] -> [T]", "[sort]" )
{
  Vec<Int> as = { 3,2,1 };

  REQUIRE( sort( as ) == Vec<Int>{ 1,2,3 } );

  Vec<Vec<Int>> bs = { {9,8,7},{6,5,4},{3,2,1} };

  REQUIRE( sort( bs ) == Vec<Vec<Int>>{ {3,2,1},{6,5,4},{9,8,7} } );

  Vec<Int> cs{};

  REQUIRE( sort( cs ) == Vec<Int>{} );
}

TEST_CASE( "zip :: [S] -> [T] -> [(S, T)]", "[zip]" )
{
  Vec<Int> as = { 1,2,3,4,5,6,7,8,9 };
  Vec<Char> bs = { 'a','b','c','d' };

  REQUIRE( zip( as, bs ) == Vec<Tup<Int,Char>>{ {1,'a'},{2,'b'},{3,'c'},{4,'d'} } );

  Vec<Int> cs{};

  REQUIRE( zip( as, cs ) == Vec<Tup<Int,Int>>{} );

  REQUIRE( zip( cs, cs ) == Vec<Tup<Int,Int>>{} );
}

TEST_CASE( "zip3 :: [S] -> [T] -> [U] -> [(S,T,U)]", "[zip3]" )
{
  Vec<Int> as = { 1,2,3,4,5,6,7,8,9 };
  Vec<Char> bs = { 'a','b','c','d' };
  Vec<StdString> cs = { "e","f","g","h","i" };

  REQUIRE( zip3( as, bs, cs ) == Vec<Tup<Int,Char,StdString>>{ {1,'a',"e"},{2,'b',"f"},{3,'c',"g"},{4,'d',"h"} } );

  Vec<Int> ds{};

  REQUIRE( zip3( as, bs, ds ) == Vec<Tup<Int,Char,Int>>{} );

  REQUIRE( zip3( ds, ds, ds ) == Vec<Tup<Int,Int,Int>>{} );
}

TEST_CASE( "zipWith :: ( S -> T -> U ) -> [S] -> [T] -> [U]", "[zipWith]" )
{
  Vec<Int> as = { 1,2,3,4,5,6,7,8,9 };
  Vec<Char> bs = { 'a','b','c','d','e' };

  auto f = []( auto& x, auto& y ){
    return String{ y } + show( x );
  };

  REQUIRE( zipWith<String>( f, as, bs ) == Vec<String>{ "a1"_s,"b2"_s,"c3"_s,"d4"_s,"e5"_s } );

  Vec<Int> cs{};

  REQUIRE( zipWith<String>( f, cs, bs ) == Vec<String>{} );
}

TEST_CASE( "zipWith3 :: ( S -> T -> U ) -> [S] -> [T] -> [U]", "[zipWith3]" )
{
  Vec<Int> as = { 1,2,3,4,5,6,7,8,9 };
  Vec<String> bs = { "1.1"_s,"2.2"_s,"3.3"_s,"4.4"_s };
  auto cs = "abcde"_s;

  auto f = []( auto& x, auto& y, auto& z ) -> String
  {
    return show( x ) + " + "_s + y + " = "_s + String{ z };
  };

  REQUIRE( zipWith3<String>( f, as, bs, cs ) == Vec<String>{ "1 + 1.1 = a"_s,"2 + 2.2 = b"_s,"3 + 3.3 = c"_s,"4 + 4.4 = d"_s } );

  Vec<Char> ds{};

  REQUIRE( zipWith3<String>( f, as, bs, ds ) == Vec<String>{} );
}

TEST_CASE( "unzip :: [(S,T)] -> ([S],[T])", "[unzip]" )
{
  Vec<Tup<Int,Char>> as = { {1,'a'},{2,'b'},{3,'c'} };

  REQUIRE( unzip( as ) == Tup<Vec<Int>,Vec<Char>>{ {1,2,3},{'a','b','c'} } );

  Vec<Tup<Int,Char>> bs{};

  REQUIRE( unzip( bs ) == Tup<Vec<Int>,Vec<Char>>{} );
}

TEST_CASE( "unzip3 :: [(S,T)] -> ([S],[T])", "[unzip3]" )
{
  Vec<Tup<Int,Char,StdString>> as = { {1,'a',"d"},{2,'b',"e"},{3,'c',"f"} };

  REQUIRE( unzip3( as ) == Tup<Vec<Int>,Vec<Char>,Vec<StdString>>{ {1,2,3},{'a','b','c'},{"d","e","f"} } );

  Vec<Tup<Int,Char,StdString>> bs{};

  REQUIRE( unzip3( bs ) == Tup<Vec<Int>,Vec<Char>,Vec<StdString>>{} );
}

TEST_CASE( "foldl :: (T -> S -> T) -> T -> [S] -> T", "[foldl]" )
{
  Vec<Int> as = { 1,2,3,4,5,6,7,8,9 };

  auto f = []( auto& x, auto& y ){ return x + y; };

  REQUIRE( foldl( f, 0, as ) == 45 );

  Vec<Int> bs{};

  REQUIRE( foldl( f, 0, bs ) == 0 );
}

TEST_CASE( "scanl :: (T -> S -> T) -> T -> [S] -> T", "[scanl]" )
{
  Vec<Int> as = { 1,2,3,4,5,6,7,8,9 };

  auto f = []( auto& x, auto& y ){ return x + y; };

  REQUIRE( scanl( f, 0, as ) == Vec<Int>{ 0,1,3,6,10,15,21,28,36,45 } );

  Vec<Int> bs{};

  REQUIRE( scanl( f, 0, bs ) == Vec<Int>{ 0 } );
}

TEST_CASE( "ceiling :: Num -> Int", "[ceiling]" )
{
  REQUIRE( ceiling( 2.3 ) == 3 );

  REQUIRE( ceiling( 1.7 ) == 2 );

  REQUIRE( ceiling( 0 ) == 0 );

  REQUIRE( ceiling( 1 ) == 1 );
}

TEST_CASE( "floor :: Num -> Int", "[floor]" )
{
  REQUIRE( floor( 2.3 ) == 2 );

  REQUIRE( floor( 1.7 ) == 1 );

  REQUIRE( floor( 0 ) == 0 );

  REQUIRE( floor( 1 ) == 1 );
}

TEST_CASE( "round :: Num -> Int", "[round]" )
{
  REQUIRE( round( 2.3 ) == 2 );

  REQUIRE( round( 2.5 ) == 3 );

  REQUIRE( round( 1.7 ) == 2 );

  REQUIRE( round( 0 ) == 0 );

  REQUIRE( round( 1 ) == 1 );
}

TEST_CASE( "lookup :: S -> [(S,T)] -> Opt<T>", "[lookup]" )
{
  Vec<Tup<Char,Int>> as = { {'a',1},{'b',2},{'c',3} };

  REQUIRE( lookup( 'a', as ) == Opt<Int>{ 1 } );

  REQUIRE( lookup( 'd', as ) == Opt<Int>{} );

  Vec<Tup<Char,Int>> bs{};

  REQUIRE( lookup( 'a', bs ) == Opt<Int>{} );
}

TEST_CASE( "splitOn :: [T] -> [T] -> [[T]]", "[splitOn]" )
{
  auto as = "This is a string "_s;
  REQUIRE( splitOn( " "_s, as ) == Vec<Vec<Char>>{ "This"_s,"is"_s,"a"_s,"string"_s,""_s } );

  auto bs = "a..b...c....d.."_s;
  REQUIRE( splitOn( ".."_s, bs ) == Vec<Vec<Char>>{ "a"_s,"b"_s,".c"_s,""_s,"d"_s,""_s } );
}

TEST_CASE( "splitOneOf :: [T] -> [T] -> [[T]]", "[splitOneOf]" )
{
  auto as = "foo,bar;baz.glurk"_s;
  REQUIRE( splitOneOf( ";.,"_s, as ) == Vec<Vec<Char>>{ "foo"_s,"bar"_s,"baz"_s,"glurk"_s } );

  auto bs = "abc,.def;;ghi.jkl,"_s;
  REQUIRE( splitOneOf( ",.;"_s, bs ) == Vec<Vec<Char>>{ "abc"_s,""_s,"def"_s,""_s,"ghi"_s,"jkl"_s,""_s } );
}

TEST_CASE( "splitWhen :: ( T -> Bool ) -> [T] -> [[T]]", "[splitWhen]" )
{
  auto as = Vec<Int>{ 1,3,-4,5,7,-9,0,2 };
  auto pred = []( auto& x ){ return x < 0; };

  REQUIRE( splitWhen( pred, as ) == Vec<Vec<Int>>{ {1,3},{5,7},{0,2} } );
}

TEST_CASE( "endBy :: [T] -> [T] -> [[T]]", "[endBy]" )
{
  auto as = "This is a string "_s;
  REQUIRE( endBy( " "_s, as ) == Vec<Vec<Char>>{ "This"_s,"is"_s,"a"_s,"string"_s } );

  auto bs = "This is a string"_s;
  REQUIRE( endBy( " "_s, bs ) == Vec<Vec<Char>>{ "This"_s,"is"_s,"a"_s,"string"_s } );

  auto cs = "a..b...c....d.."_s;
  REQUIRE( endBy( ".."_s, cs ) == Vec<Vec<Char>>{ "a"_s,"b"_s,".c"_s,""_s,"d"_s } );

  auto ds = "a..b...c....d"_s;
  REQUIRE( endBy( ".."_s, ds ) == Vec<Vec<Char>>{ "a"_s,"b"_s,".c"_s,""_s,"d"_s } );
}

TEST_CASE( "endByOneOf :: [T] -> [T] -> [[T]]", "[endByOneOf]" )
{
  auto as = "foo,bar;baz.glurk;"_s;
  REQUIRE( endByOneOf( ";.,"_s, as ) == Vec<Vec<Char>>{ "foo"_s,"bar"_s,"baz"_s,"glurk"_s } );

  auto bs = "abc,.def;;ghi.jkl,"_s;
  REQUIRE( endByOneOf( ",.;"_s, bs ) == Vec<Vec<Char>>{ "abc"_s,""_s,"def"_s,""_s,"ghi"_s,"jkl"_s } );
}

TEST_CASE( "wordsBy :: ( T -> Bool ) -> [T] -> [[T]]", "[wordsBy]" )
{
  auto as = "dogxxxcatxbirdxx"_s;
  auto pred = []( auto& x ){ return x == 'x'; };

  REQUIRE( wordsBy( pred, as ) == Vec<String>{ "dog"_s,"cat"_s,"bird"_s } );
}

TEST_CASE( "linesBy :: ( T -> Bool ) -> [T] -> [[T]]", "[linesBy]" )
{
  auto as = "dogxxxcatxbirdxx"_s;
  auto pred = []( auto& x ){ return x == 'x'; };

  REQUIRE( linesBy( pred, as ) == Vec<String>{ "dog"_s,""_s,""_s,"cat"_s,"bird"_s,""_s } );
}

TEST_CASE( "chunksOf :: UInt -> [T] -> [[T]]", "[chunksOf]" )
{
  auto as = "abcdefg"_s;

  REQUIRE( chunksOf( 1, as ) == Vec<String>{ "a"_s,"b"_s,"c"_s,"d"_s,"e"_s,"f"_s,"g"_s } );
  REQUIRE( chunksOf( 2, as ) == Vec<String>{ "ab"_s,"cd"_s,"ef"_s,"g"_s } );
  REQUIRE( chunksOf( 3, as ) == Vec<String>{ "abc"_s,"def"_s,"g"_s } );

  // REQUIRE( chunksOf( 0, as ) == INFINITE_LOOP );
}

TEST_CASE( "splitPlaces :: [UInt] -> [T] -> [[T]]", "[splitPlaces]" )
{
  auto as = Vec<Int>{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
  REQUIRE( splitPlaces( Vec<UInt>{ 2,3,4 }, as ) == Vec<Vec<Int>>{ {1,2},{3,4,5},{6,7,8,9} } );

  as = Vec<Int>{ 1,2,3,4,5,6,7,8,9,10 };
  REQUIRE( splitPlaces( Vec<UInt>{ 4,9 }, as ) == Vec<Vec<Int>>{ {1,2,3,4},{5,6,7,8,9,10} } );

  REQUIRE( splitPlaces( Vec<UInt>{ 4,9,3 }, as ) == Vec<Vec<Int>>{ {1,2,3,4},{5,6,7,8,9,10} } );

  REQUIRE( splitPlaces( Vec<UInt>{ 1,2,3,4,5,6,7,8,9 }, as ) == Vec<Vec<Int>>{ {1},{2,3},{4,5,6},{7,8,9,10} } );
}

TEST_CASE( "splitPlacesBlanks :: [UInt] -> [T] -> [[T]]", "[splitPlacesBlanks]" )
{
  auto as = Vec<Int>{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
  REQUIRE( splitPlacesBlanks( Vec<UInt>{ 2,3,4 }, as ) == Vec<Vec<Int>>{ {1,2},{3,4,5},{6,7,8,9} } );

  as = Vec<Int>{ 1,2,3,4,5,6,7,8,9,10 };
  REQUIRE( splitPlacesBlanks( Vec<UInt>{ 4,9 }, as ) == Vec<Vec<Int>>{ {1,2,3,4},{5,6,7,8,9,10} } );

  REQUIRE( splitPlacesBlanks( Vec<UInt>{ 4,9,3 }, as ) == Vec<Vec<Int>>{ {1,2,3,4},{5,6,7,8,9,10},{} } );

  REQUIRE( splitPlacesBlanks( Vec<UInt>{ 1,2,3,4,5,6,7,8,9 }, as ) == Vec<Vec<Int>>{ {1},{2,3},{4,5,6},{7,8,9,10},{},{},{},{},{} } );
}

TEST_CASE( "divvy :: UInt -> UInt -> [T] -> [[T]]", "[divvy]" )
{
  auto as = Vec<Int>{ 1,2,3,4,5,6,7,8,9,10 };
  REQUIRE( divvy( 5, 5, as ) == Vec<Vec<Int>>{ {1,2,3,4,5},{6,7,8,9,10} } );

  auto bs = Vec<Int>{ 1,2,3,4,5,6,7,8,9};
  REQUIRE( divvy( 5, 5, bs ) == Vec<Vec<Int>>{ {1,2,3,4,5} } );

  auto cs = Vec<Int>{ 1,2,3,4,5,6,7,8,9,10,11 };
  REQUIRE( divvy( 5, 5, cs ) == Vec<Vec<Int>>{ {1,2,3,4,5},{6,7,8,9,10} } );
}

TEST_CASE( "maybe :: T -> ( S -> T ) -> Opt<S> -> T", "[maybe]" )
{
  auto f = []( auto& x ){ return x * x; };
  REQUIRE( maybe( 99, f, Opt<Int>{ 3 } ) == 9 );
  REQUIRE( maybe( 99, f, Opt<Int>{} ) == 99 );

  auto g = []( auto& x ){ return StdString{ x }; };
  REQUIRE( maybe<StdString>( "", g, Opt<Char>{ 'x' } ) == StdString{ 'x' } );
  REQUIRE( maybe<StdString>( "", g, Opt<Char>{} ) == StdString{} );
}

TEST_CASE( "isJust :: Opt<T> -> Bool", "[isJust]" )
{
  REQUIRE( isJust( Opt<Int>{ 3 } ) == true );
  REQUIRE( isJust( Opt<Int>{} ) == false );
}

TEST_CASE( "isNothing :: Opt<T> -> Bool", "[isNothing]" )
{
  REQUIRE( isNothing( Opt<Int>{ 3 } ) == false );
  REQUIRE( isNothing( Opt<Int>{} ) == true );
}

TEST_CASE( "fromMaybe :: T -> Opt<T> -> T", "[fromMaybe]" )
{
  REQUIRE( fromMaybe( 9, Opt<Int>{ 3 } ) == 3 );
  REQUIRE( fromMaybe( 9, Opt<Int>{} ) == 9 );
}

TEST_CASE( "listToMaybe :: [T] -> Opt<T>", "[listToMaybe]" )
{
  REQUIRE( listToMaybe( Vec<Int>{ 1,2,3 } ) == Opt<Int>{ 1 } );
  REQUIRE( listToMaybe( Vec<Int>{} ) == Opt<Int>{} );
}

TEST_CASE( "maybeToList :: Opt<T> -> [T]", "[maybeToList]" )
{
  REQUIRE( maybeToList<Vec>( Opt<Int>{ 1 } ) == Vec<Int>{ 1 } );
  REQUIRE( maybeToList<Vec>( Opt<Int>{} ) == Vec<Int>{} );
}

TEST_CASE( "catMaybes :: [Opt<T>] -> [T]", "[catMaybes]" )
{
  auto as = Vec<Opt<Int>>{ 1,2,3 };
  REQUIRE( catMaybes( as ) == Vec<Int>{ 1,2,3 } );

  auto bs = Vec<Opt<Int>>{ 1,2,Opt<Int>{},3 };
  REQUIRE( catMaybes( bs ) == Vec<Int>{ 1,2,3 } );
}

TEST_CASE( "mapMaybe :: ( S -> Opt<T> ) -> [S] -> [T]", "[mapMaybe]" )
{
  auto as = Vec<Int>{ 0,1,2,3,4 };
  auto af = []( auto& x ){ return x == 0 ? Opt<Int>{} : Opt<Int>{ x*x }; };
  REQUIRE( mapMaybe<Int>( af, as ) == Vec<Int>{ 1,4,9,16 } );

  auto bs = Vec<Opt<Int>>{ 0,1,Opt<Int>{},2,3,4 };
  auto bf = []( auto& x ){ return x; };
  REQUIRE( mapMaybe<Int>( bf, bs ) == Vec<Int>{ 0,1,2,3,4 } );
}
