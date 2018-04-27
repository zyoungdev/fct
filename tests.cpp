#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "fct.h"
using namespace fct;

// #define DEBUG_IO

TEST_CASE( "FCT Composition", "[fct]" )
{
  Vec<Int> a = { 1,2,3,4 };
  auto b = fmap<Int, Bool>( even, a );

  REQUIRE( b == Vec<Bool>{ false, true, false, true } );

  auto c = filter<Int>( []( auto& x ){ return x > 3; }, a );

  REQUIRE( c == Vec<Int>{ 4 } );

  auto s = String{ "this is lowercase" };

  REQUIRE( fmap( toUpper, s ) == String{ "THIS IS LOWERCASE" } );

  auto ss = Vec<Char>{'t','h','i','s',' ','i','s',' ','l','o','w','e','r','c','a','s','e'};

  REQUIRE( fmap<Char, Char>( toUpper, ss ) == Vec<Char>{'T','H','I','S',' ','I','S',' ','L','O','W','E','R','C','A','S','E'} );
}

TEST_CASE( "head :: [T] -> Opt<T>", "[head]")
{
  Vec<Int> a = { 1, 2, 3 };
  REQUIRE( head( a ).value() == 1 );

  Vec<Int> b{};
  REQUIRE( head( b ).has_value() == false );
}

TEST_CASE( "last :: [T] -> Opt<T>", "[last]")
{
  Vec<Int> a = { 1, 2, 3 };
  REQUIRE( last( a ).value() == 3 );

  Vec<Int> b{};
  REQUIRE( last( b ).has_value() == false );
}

TEST_CASE( "fmap :: ( S -> T ) -> [S] -> [T]", "[fmap]" )
{
  Vec<Int> a = { 1, 2, 3 };
  auto a_sq = fmap<Int, Int>( []( auto& x ){ return x * x; }, a );

  REQUIRE( a_sq == Vec<Int>{1,4,9} );

  Vec<Int> b{};
  auto b_sq = fmap<Int, Int>( []( auto& x ){ return x * x; }, b );

  REQUIRE( b_sq == Vec<Int>{} );

  auto a_ch = fmap<Int, char>( []( auto& x ){ return 'a' + x; }, a );
  REQUIRE( a_ch == Vec<char>{'b','c','d'} );
}

TEST_CASE( "transpose :: [[T]] -> [[T]]", "[transpose]" )
{
  Vec<Vec<Int>> a = { {1,2,3},{4,5,6},{7,8,9} };
  auto a_tr = transpose( a );

  REQUIRE( a_tr == Vec<Vec<Int>>{{1,4,7},{2,5,8},{3,6,9}} );

  Vec<Vec<Int>> b{};
  auto b_tr = transpose( b );

  REQUIRE( b_tr == Vec<Vec<Int>>{} );

  Vec<Vec<Int>> c = { {1,2,3},{4,5},{7} };
  auto c_tr = transpose( c );

  REQUIRE( c_tr == Vec<Vec<Int>>{{1,4,7},{2,5},{3}} );
}

TEST_CASE( "filter :: ( T -> bool ) -> [T]", "[filter]" )
{
  Vec<Int> a = { 1,2,3,4,5,6,7,8,9 };
  auto a_filt = filter( []( auto& x ){ return x > 5; }, a );

  REQUIRE( a_filt == Vec<Int>{ 6,7,8,9 } );

  Vec<Int> b{};
  auto b_filt = filter( []( auto& x ){ return x > 5; }, b );

  REQUIRE( b_filt == Vec<Int>{} );
}

TEST_CASE( "takeWhile :: ( T -> bool ) -> [T] -> [T]", "[takeWhile]" )
{
  Vec<Int> a = { 1,2,3,4,5,6,7,8,9 };
  auto a_tw = takeWhile( []( auto& x ){ return x < 5; }, a );

  REQUIRE( a_tw == Vec<Int>{ 1,2,3,4 } );

  Vec<Int> b{};
  auto b_tw = takeWhile( []( auto& x ){ return x < 5; }, b );

  REQUIRE( b_tw == Vec<Int>{} );
}

TEST_CASE( "dropWhile :: ( T -> bool ) -> [T] -> [T]", "[dropWhile]" )
{
  Vec<Int> a = { 1,2,3,4,5,6,7,8,9 };
  auto a_dw = dropWhile( []( auto& x ){ return x < 5; }, a );

  REQUIRE( a_dw == Vec<Int>{ 5,6,7,8,9 } );

  Vec<Int> b{};
  auto b_dw = dropWhile( []( auto& x ){ return x < 5; }, b );

  REQUIRE( b_dw == Vec<Int>{} );
}

TEST_CASE( "subsets :: [T] -> [[T]]", "[subsets]" )
{
  Vec<Int> a = { 1,2,3 };
  auto a_ss = subsets( a );

  REQUIRE( a_ss == Vec<Vec<Int>>{ {},{1},{2},{1,2},{3},{1,3},{2,3},{1,2,3} } );

  Vec<Int> b{};
  auto b_ss = subsets( b );

  REQUIRE( b_ss == Vec<Vec<Int>>{ Vec<Int>{} } );
}

TEST_CASE( "even :: Num -> bool", "[even]" )
{
  Int a = 2;
  long b = 2;

  REQUIRE( even( a ) == true );
  REQUIRE( even( a + 1 ) == false );
  REQUIRE( even( b ) == true );
  REQUIRE( even( b + 1 ) == false );

  REQUIRE( even( 0 ) == true );
}

TEST_CASE( "odd :: Num -> bool", "[odd]" )
{
  Int a = 1;
  long b = 1;

  REQUIRE( odd( a ) == true );
  REQUIRE( odd( a + 1 ) == false );
  REQUIRE( odd( b ) == true );
  REQUIRE( odd( b + 1 ) == false );

  REQUIRE( odd( 0 ) == false );
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

TEST_CASE( "quotRem :: (Integral a) => T -> T -> ( a, a )", "[quotRem]" )
{
  Int a = 3;
  Int b = 2;
  Int c = 0;

  REQUIRE( quotRem( a, b ) == Tup<Int, Int>( 1, 1 ) );
  REQUIRE( quotRem( b, a ) == Tup<Int, Int>( 0, 2 ) );
  REQUIRE( quotRem( c, a ) == Tup<Int, Int>( 0, 0 ) );
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
  Vec<Int> a = { 1,2,3 };

  REQUIRE( elem( 1, a ) == true );
  REQUIRE( elem( 9, a ) == false );

  Vec<Int> b{};

  REQUIRE( elem( 1, b ) == false );
}

TEST_CASE( "notElem :: T -> [T] -> bool", "[notElem]" )
{
  Vec<Int> a = { 1,2,3 };

  REQUIRE( notElem( 1, a ) == false );
  REQUIRE( notElem( 9, a ) == true );

  Vec<Int> b{};

  REQUIRE( notElem( 1, b ) == true );
}

TEST_CASE( "maximum :: [T] -> Opt<T>", "[maximum]" )
{
  Vec<Int> a = { 1,2,3 };

  REQUIRE( maximum( a ).value() == 3 );

  Vec<Int> b{};
  REQUIRE( maximum( b ).has_value() == false );
}

TEST_CASE( "minimum :: [T] -> Opt<T>", "[minimum]" )
{
  Vec<Int> a = { 1,2,3 };

  REQUIRE( minimum( a ).value() == 1 );

  Vec<Int> b{};
  REQUIRE( minimum( b ).has_value() == false );
}

TEST_CASE( "sum :: [T] -> T", "[sum]" )
{
  Vec<Int> a = { 1,2,3 };

  REQUIRE( sum( a ) == 6 );

  Vec<Int> b{};

  REQUIRE( sum( b ) == 0 );
}

TEST_CASE( "product :: [T] -> T", "[product]" )
{
  Vec<Int> a = { 1,2,3 };

  REQUIRE( product( a ) == 6 );

  Vec<Int> b{};

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

  REQUIRE( flip<Int, Int, Int>( f, 3, 2 ) == 1 );
  REQUIRE( flip<Int, Int, Int>( f, 2, 3 ) == 0 );
}

TEST_CASE( "until :: ( T -> bool ) -> ( T -> T ) -> T -> T", "[until]" )
{
  auto p = []( auto& x ){ return x > 10; };
  auto f = []( auto& x ){ return x + x; };

  REQUIRE( until( p, f, 1 ) == 16 );
}

TEST_CASE( "null :: [T] -> bool", "[null]" )
{
  Vec<Int> a = { 1,2,3 };

  REQUIRE( null( a ) == false );

  Vec<Int> b{};

  REQUIRE( null( b ) == true );
}

TEST_CASE( "length :: [T] -> Num", "[length]" )
{
  Vec<Int> a = { 1,2,3 };

  REQUIRE( length( a ) == 3 );

  Vec<Int> b{};

  REQUIRE( length( b ) == 0 );
}

TEST_CASE( "reverse :: [T] -> [T]", "[reverse]" )
{
  Vec<Int> a = { 1,2,3 };

  REQUIRE( reverse( a ) == Vec<Int>{ 3,2,1 } );

  Vec<Int> b{};

  REQUIRE( reverse( b ) == Vec<Int>{} );
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
  Vec<Int> a = { 1,2,3 };

  auto p_even = []( auto& x ){ return even( x ); };

  REQUIRE( any( p_even, a ) == true );

  Vec<Int> b = { 1,3,5 };

  REQUIRE( any( p_even, b ) == false );

  Vec<Int> c{};

  REQUIRE( any( p_even, c ) == false );
}

TEST_CASE( "all :: ( T -> bool ) -> [T] -> bool", "[all]" )
{
  Vec<Int> a = { 2,4,6 };

  auto p_even = []( auto& x ){ return even( x ); };

  REQUIRE( all( p_even, a ) == true );

  Vec<Int> b = { 2,3,4 };

  REQUIRE( all( p_even, b ) == false );

  Vec<Int> c{};

  REQUIRE( all( p_even, c ) == true );
}

TEST_CASE( "concat :: [[T]] -> [T]", "[concat]" )
{
  Vec<Vec<Int>> a = { {1,2,3},{4,5,6},{7,8,9} };

  REQUIRE( concat( a ) == Vec<Int>{ 1,2,3,4,5,6,7,8,9 } );

  Vec<Vec<Int>> b{};

  REQUIRE( concat( b ) == Vec<Int>{} );
}

TEST_CASE( "replicate :: UInt -> T - [T]", "[replicate]" )
{
  REQUIRE( replicate( 3, 'x' ) == Vec<Char>{ 'x','x','x' } );

  REQUIRE( replicate( 3, 1 ) == Vec<Int>{ 1,1,1 } );

  REQUIRE( replicate( 0, 1 ) == Vec<Int>{} );
}

TEST_CASE( "take :: UInt -> [T] -> [T]", "[take]" )
{
  Vec<Int> a = { 1,2,3,4,5,6,7,8,9 };

  REQUIRE( take( 3, a ) == Vec<Int>{ 1,2,3 } );

  REQUIRE( take( 0, a ) == Vec<Int>{} );

  Vec<Int> b{};

  REQUIRE( take( 3, b ) == Vec<Int>{} );
}

TEST_CASE( "drop :: UInt -> [T] -> [T]", "[drop]" )
{
  Vec<Int> a = { 1,2,3,4,5,6,7,8,9 };

  REQUIRE( drop( 3, a ) == Vec<Int>{ 4,5,6,7,8,9 } );

  REQUIRE( drop( 0, a ) == Vec<Int>{ 1,2,3,4,5,6,7,8,9 } );

  Vec<Int> b{};

  REQUIRE( drop( 3, b ) == Vec<Int>{} );
}

TEST_CASE( "splitAt :: UInt -> [T] -> ( [T], [T] )", "[splitAt]" )
{
  Vec<Int> a = { 1,2,3,4,5,6,7,8,9 };

  REQUIRE( splitAt( 4, a ) == Tup<Vec<Int>, Vec<Int>>{ Vec<Int>{ 1,2,3,4 }, Vec<Int>{ 5,6,7,8,9 } } );

  REQUIRE( splitAt( 0, a ) == Tup<Vec<Int>, Vec<Int>>{ Vec<Int>{}, Vec<Int>{ 1,2,3,4,5,6,7,8,9 } } );

  Vec<Int> b = { 1,2,3 };

  REQUIRE( splitAt( 9, b ) == Tup<Vec<Int>, Vec<Int>>{ Vec<Int>{ 1,2,3 }, Vec<Int>{} } );

  Vec<Int> c{};

  REQUIRE( splitAt( 9, c ) == Tup<Vec<Int>, Vec<Int>>{ Vec<Int>{}, Vec<Int>{} } );
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
  Vec<String> a = { "This", "is", "a", "String" };

  REQUIRE( unlines( a ) == String{ "This\nis\na\nString\n" } );

  Vec<String> b{};

  REQUIRE( unlines( b ) == String{} );
}

TEST_CASE( "unwords :: [String] -> String", "[unwords]" )
{
  Vec<String> a = { "This","is","a","String" };

  REQUIRE( unwords( a ) == String{ "This is a String" } );

  Vec<String> b{};

  REQUIRE( unwords( b ) == String{} );
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
  Vec<Int> a = { 1,2,3 };
  Vec<Int> b = { 4,5,6 };

  REQUIRE( union_of( a, b ) == Vec<Int>{ 1,2,3,4,5,6 } );

  REQUIRE( union_of( Vec<Int>{}, Vec<Int>{} ) == Vec<Int>{} );
}

TEST_CASE( "intersperse :: T -> [T] -> [T]", "[intersperse]" )
{
  Int a = 1;
  Vec<Int> b = { 1,2,3 };

  REQUIRE( intersperse( a, b ) == Vec<Int>{ 1,1,2,1,3 } );

  Vec<Int> c{};

  REQUIRE( intersperse( a, c ) == Vec<Int>{} );
}

TEST_CASE( "intercalate :: [T] -> [[T]] -> [T]", "[intercalate]" )
{
  Vec<Int> a = { 0,0,0 };
  Vec<Vec<Int>> b = { {1,2,3},{4,5,6},{7,8,9} };

  REQUIRE( intercalate( a, b ) == Vec<Int>{ 1,2,3,0,0,0,4,5,6,0,0,0,7,8,9 } );

  REQUIRE( intercalate( Vec<Int>{}, b ) == Vec<Int>{ 1,2,3,4,5,6,7,8,9 } );
}
