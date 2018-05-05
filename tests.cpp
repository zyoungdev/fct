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

TEST_CASE( "FCT Composition", "[fct]" )
{
  Vec<Int> as = { 1,2,3,4 };
  auto b = fmap<Bool>( even, as );

  REQUIRE( b == Vec<Bool>{ false, true, false, true } );

  auto c = filter<Int>( []( auto& x ){ return x > 3; }, as );

  REQUIRE( c == Vec<Int>{ 4 } );

  auto s = String{ "this is lowercase" };

  REQUIRE( fmap( toUpper, s ) == String{ "THIS IS LOWERCASE" } );

  auto ss = Vec<Char>{'t','h','i','s',' ','i','s',' ','l','o','w','e','r','c','a','s','e'};

  REQUIRE( fmap<Char>( toUpper, ss ) == Vec<Char>{'T','H','I','S',' ','I','S',' ','L','O','W','E','R','C','A','S','E'} );
}

TEST_CASE( "toVec :: String -> Vec<Char>", "[toVec]" )
{
  String a = "String";

  REQUIRE( toVec( a ) == Vec<Char>{ 'S','t','r','i','n','g' } );

  String b{};

  REQUIRE( toVec( b ) == Vec<Char>{} );
}

TEST_CASE( "toStr :: Vec<Char> -> String", "[toStr]" )
{
  Vec<Char> as = { 'S','t','r','i','n','g' };

  REQUIRE( toStr( as ) == "String" );

  Vec<Char> bs{};

  REQUIRE( toStr( bs ) == String{} );
}

TEST_CASE( "head :: [T] -> Opt<T>", "[head]")
{
  Vec<Int> as = { 1, 2, 3 };
  REQUIRE( head( as ).value() == 1 );

  Vec<Int> bs{};
  REQUIRE( head( bs ).has_value() == false );
}

TEST_CASE( "last :: [T] -> Opt<T>", "[last]")
{
  Vec<Int> as = { 1, 2, 3 };
  REQUIRE( last( as ).value() == 3 );

  Vec<Int> bs{};
  REQUIRE( last( bs ).has_value() == false );
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

TEST_CASE( "maximum :: [T] -> Opt<T>", "[maximum]" )
{
  Vec<Int> as = { 1,2,3 };

  REQUIRE( maximum( as ).value() == 3 );

  Vec<Int> bs{};
  REQUIRE( maximum( bs ).has_value() == false );
}

TEST_CASE( "minimum :: [T] -> Opt<T>", "[minimum]" )
{
  Vec<Int> as = { 1,2,3 };

  REQUIRE( minimum( as ).value() == 1 );

  Vec<Int> bs{};
  REQUIRE( minimum( bs ).has_value() == false );
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
  String a = "This\nis\na\nString\n";

  REQUIRE( lines( a ) == Vec<String>{ "This", "is", "a", "String" } );

  String b = "";

  REQUIRE( lines( b ) == Vec<String>{} );

  String c = "This\n\nis\n\na\n\nString\n\n";

  REQUIRE( lines( c ) == Vec<String>{ "This", "", "is", "", "a", "", "String", "" } );
}

TEST_CASE( "words :: String -> [String]", "[words]" )
{
  String a = "This is a String";

  REQUIRE( words( a ) == Vec<String>{ "This", "is", "a", "String" } );

  String b = "";

  REQUIRE( words( b ) == Vec<String>{} );
}

TEST_CASE( "unlines :: [String] -> String", "[unlines]" )
{
  Vec<String> as = { "This", "is", "a", "String" };

  REQUIRE( unlines( as ) == String{ "This\nis\na\nString\n" } );

  Vec<String> bs{};

  REQUIRE( unlines( bs ) == String{} );
}

TEST_CASE( "unwords :: [String] -> String", "[unwords]" )
{
  Vec<String> as = { "This","is","a","String" };

  REQUIRE( unwords( as ) == String{ "This is a String" } );

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

TEST_CASE( "putStr :: String -> void", "[putStr]" )
{
  String a = "magic";
  print( "# Should print magic: " );
  putStr( a );
  print("");
}

TEST_CASE( "putStrLn :: String -> void", "[putStrLn]" )
{
  String a = "magic";
  print( "# Should print magic: " );
  putStr( a );
  print("");
}

TEST_CASE( "getChar :: Char", "[getChar]" )
{
  print( "Please type a character: ", ' ' );
  auto a = getChar();
  print( "You typed: " + String{ a } );
}

TEST_CASE( "getLine :: String", "[getLine]" )
{
  print( "Please type a line: ", ' ' );
  auto a = getLine();
  print( "You typed: " + a );
}

TEST_CASE( "readFile :: String -> String, writeFile :: String -> String -> void", "[readFile][writeFile]" )
{
  print( "Please name file to read/write in /tmp/: ", ' ' );
  auto a = getLine();
  print( a );
  a = String{ "/tmp/" + a };

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

TEST_CASE( "show :: T -> String", "[show]" )
{
  REQUIRE( show( 1 ) == String{ '1' } );
  REQUIRE( show( 1.999999 ) == String{ "1.999999" } );
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
  String a = "mississippi";

  REQUIRE( group( toVec( a ) ) == Vec<Vec<Char>>{ {'m'},{'i'},{'s','s'},{'i'},{'s','s'},{'i'},{'p','p'},{'i'} } );

  Vec<Char> bs{};
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
  String a = "This is a String";
  String b = "This";

  REQUIRE( isPrefixOf( toVec( b ), toVec( a ) ) == true );

  String c = "is";

  REQUIRE( isPrefixOf( toVec( c ), toVec( a ) ) == false );

  Vec<Char> ds{};

  REQUIRE( isPrefixOf( ds, toVec( a ) ) == true );

  REQUIRE( isPrefixOf( toVec( b ), ds ) == false );

  REQUIRE( isPrefixOf( ds, ds ) == true );
}

TEST_CASE( "isSuffixOf :: [T] -> [T] -> Bool", "[isSuffixOf]" )
{
  String a = "This is a String";
  String b = "String";

  REQUIRE( isSuffixOf( toVec( b ), toVec( a ) ) == true );

  String c = "is";

  REQUIRE( isSuffixOf( toVec( c ), toVec( a ) ) == false );

  Vec<Char> ds{};

  REQUIRE( isSuffixOf( ds, toVec( a ) ) == true );

  REQUIRE( isSuffixOf( toVec( b ), ds ) == false );

  REQUIRE( isSuffixOf( ds, ds ) == true );
}

TEST_CASE( "isInfixOf :: [T] -> [T] -> Bool", "[isInfixOf]" )
{
  String a = "This is a String";
  String b = "is";

  REQUIRE( isInfixOf( toVec( b ), toVec( a ) ) == true );

  Vec<Char> ds{};

  REQUIRE( isInfixOf( ds, toVec( a ) ) == true );

  REQUIRE( isInfixOf( toVec( b ), ds ) == false );

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
  Vec<String> cs = { "e","f","g","h","i" };

  REQUIRE( zip3( as, bs, cs ) == Vec<Tup<Int,Char,String>>{ {1,'a',"e"},{2,'b',"f"},{3,'c',"g"},{4,'d',"h"} } );

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

  REQUIRE( zipWith<String>( f, as, bs ) == Vec<String>{ "a1","b2","c3","d4","e5" } );

  Vec<Int> cs{};

  REQUIRE( zipWith<String>( f, cs, bs ) == Vec<String>{} );
}

TEST_CASE( "zipWith3 :: ( S -> T -> U ) -> [S] -> [T] -> [U]", "[zipWith3]" )
{
  Vec<Int> as = { 1,2,3,4,5,6,7,8,9 };
  Vec<String> bs = { "1.1","2.2","3.3","4.4" };
  Vec<Char> cs = { 'a','b','c','d','e' };

  auto f = []( auto& x, auto& y, auto& z ) -> String{
    return show( x ) + " + " + y + " = " + String{ z };
  };

  REQUIRE( zipWith3<String>( f, as, bs, cs ) == Vec<String>{ "1 + 1.1 = a","2 + 2.2 = b","3 + 3.3 = c","4 + 4.4 = d" } );

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
  Vec<Tup<Int,Char,String>> as = { {1,'a',"d"},{2,'b',"e"},{3,'c',"f"} };

  REQUIRE( unzip3( as ) == Tup<Vec<Int>,Vec<Char>,Vec<String>>{ {1,2,3},{'a','b','c'},{"d","e","f"} } );

  Vec<Tup<Int,Char,String>> bs{};

  REQUIRE( unzip3( bs ) == Tup<Vec<Int>,Vec<Char>,Vec<String>>{} );
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
