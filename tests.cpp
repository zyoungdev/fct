#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "fct.h"

using namespace fct;

// #define DEBUG_IO

TEST_CASE( "FCT Composition", "[fct]" )
{
  Vec<Int> a = { 1,2,3,4 };
  auto b = fmap<Bool>( even, a );

  REQUIRE( b == Vec<Bool>{ false, true, false, true } );

  auto c = filter<Int>( []( auto& x ){ return x > 3; }, a );

  REQUIRE( c == Vec<Int>{ 4 } );

  auto s = String{ "this is lowercase" };

  REQUIRE( fmap( toUpper, s ) == String{ "THIS IS LOWERCASE" } );

  auto ss = Vec<Char>{'t','h','i','s',' ','i','s',' ','l','o','w','e','r','c','a','s','e'};

  REQUIRE( fmap<Char>( toUpper, ss ) == Vec<Char>{'T','H','I','S',' ','I','S',' ','L','O','W','E','R','C','A','S','E'} );
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

TEST_CASE( "fst :: (S,T) -> S", "[fst]" )
{
  Tup<Int,Char> a = {1,'a'};

  REQUIRE( fst( a ) == 1 );
}

TEST_CASE( "snd :: (S,T) -> S", "[snd]" )
{
  Tup<Int,Char> a = {1,'a'};

  REQUIRE( snd( a ) == 'a' );
}

TEST_CASE( "fmap :: ( S -> T ) -> [S] -> [T]", "[fmap]" )
{
  Vec<Int> a = { 1, 2, 3 };
  auto a_sq = fmap<Int>( []( auto& x ){ return x * x; }, a );

  REQUIRE( a_sq == Vec<Int>{1,4,9} );

  Vec<Int> b{};
  auto b_sq = fmap<Int>( []( auto& x ){ return x * x; }, b );

  REQUIRE( b_sq == Vec<Int>{} );

  auto a_ch = fmap<Char>( []( auto& x ){ return 'a' + x; }, a );
  REQUIRE( a_ch == Vec<Char>{'b','c','d'} );
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

TEST_CASE( "filter :: ( T -> Bool ) -> [T]", "[filter]" )
{
  Vec<Int> a = { 1,2,3,4,5,6,7,8,9 };
  auto a_filt = filter( []( auto& x ){ return x > 5; }, a );

  REQUIRE( a_filt == Vec<Int>{ 6,7,8,9 } );

  Vec<Int> b{};
  auto b_filt = filter( []( auto& x ){ return x > 5; }, b );

  REQUIRE( b_filt == Vec<Int>{} );
}

TEST_CASE( "takeWhile :: ( T -> Bool ) -> [T] -> [T]", "[takeWhile]" )
{
  Vec<Int> a = { 1,2,3,4,5,6,7,8,9 };
  auto a_tw = takeWhile( []( auto& x ){ return x < 5; }, a );

  REQUIRE( a_tw == Vec<Int>{ 1,2,3,4 } );

  Vec<Int> b{};
  auto b_tw = takeWhile( []( auto& x ){ return x < 5; }, b );

  REQUIRE( b_tw == Vec<Int>{} );
}

TEST_CASE( "dropWhile :: ( T -> Bool ) -> [T] -> [T]", "[dropWhile]" )
{
  Vec<Int> a = { 1,2,3,4,5,6,7,8,9 };
  auto a_dw = dropWhile( []( auto& x ){ return x < 5; }, a );

  REQUIRE( a_dw == Vec<Int>{ 5,6,7,8,9 } );

  Vec<Int> b{};
  auto b_dw = dropWhile( []( auto& x ){ return x < 5; }, b );

  REQUIRE( b_dw == Vec<Int>{} );
}

TEST_CASE( "subsequences :: [T] -> [[T]]", "[subsequences]" )
{
  Vec<Int> a = { 1,2,3 };
  auto a_ss = subsequences( a );

  REQUIRE( a_ss == Vec<Vec<Int>>{ {},{1},{2},{1,2},{3},{1,3},{2,3},{1,2,3} } );

  Vec<Int> b{};
  auto b_ss = subsequences( b );

  REQUIRE( b_ss == Vec<Vec<Int>>{ Vec<Int>{} } );
}

TEST_CASE( "even :: Num -> Bool", "[even]" )
{
  Int a = 2;
  long b = 2;

  REQUIRE( even( a ) == true );
  REQUIRE( even( a + 1 ) == false );
  REQUIRE( even( b ) == true );
  REQUIRE( even( b + 1 ) == false );

  REQUIRE( even( 0 ) == true );
}

TEST_CASE( "odd :: Num -> Bool", "[odd]" )
{
  Int a = 1;
  long b = 1;

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

TEST_CASE( "quotRem :: (Integral a) => T -> T -> ( a, a )", "[quotRem]" )
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
  Vec<Int> a = { 1,2,3 };

  REQUIRE( elem( 1, a ) == true );
  REQUIRE( elem( 9, a ) == false );

  Vec<Int> b{};

  REQUIRE( elem( 1, b ) == false );
}

TEST_CASE( "notElem :: T -> [T] -> Bool", "[notElem]" )
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

TEST_CASE( "sum :: [Num] -> Num", "[sum]" )
{
  Vec<Int> a = { 1,2,3 };

  REQUIRE( sum( a ) == 6 );

  Vec<Int> b{};

  REQUIRE( sum( b ) == 0 );
}

TEST_CASE( "product :: [Num] -> Num", "[product]" )
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
  Vec<Int> a = { 1,2,3 };

  REQUIRE( null( a ) == false );

  Vec<Int> b{};

  REQUIRE( null( b ) == true );
}

TEST_CASE( "length :: [T] -> Size_t", "[length]" )
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

TEST_CASE( "conjunction :: [T] -> Bool", "[conjunction]" )
{
  Vec<Bool> a = { true, true, true };

  REQUIRE( conjunction( a ) == true );

  Vec<Bool> b = { false, false, false };

  REQUIRE( conjunction( b ) == false );

  Vec<Bool> c = { true, false, true };

  REQUIRE( conjunction( c ) == false );

  Vec<Bool> d{};

  REQUIRE( conjunction( d ) == true );
}

TEST_CASE( "disjunction :: [T] -> Bool", "[disjunction]" )
{
  Vec<Bool> a = { true, true, true };

  REQUIRE( disjunction( a ) == true );

  Vec<Bool> b = { false, false, false };

  REQUIRE( disjunction( b ) == false );

  Vec<Bool> c = { true, false, true };

  REQUIRE( disjunction( c ) == true );

  Vec<Bool> d{};

  REQUIRE( disjunction( d ) == false );
}

TEST_CASE( "any :: ( T -> Bool ) -> [T] -> Bool", "[any]" )
{
  Vec<Int> a = { 1,2,3 };

  auto p_even = []( auto& x ){ return even( x ); };

  REQUIRE( any( p_even, a ) == true );

  Vec<Int> b = { 1,3,5 };

  REQUIRE( any( p_even, b ) == false );

  Vec<Int> c{};

  REQUIRE( any( p_even, c ) == false );
}

TEST_CASE( "all :: ( T -> Bool ) -> [T] -> Bool", "[all]" )
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

  Vec<Vec<Int>> c{};

  REQUIRE( intercalate( a, c ) == Vec<Int>{} );

  REQUIRE( intercalate( Vec<Int>{}, c ) == Vec<Int>{} );

}

TEST_CASE( "permutations :: [T] -> [[T]]", "[permutations]" )
{
  Vec<Int> a = { 1,2,3 };

  REQUIRE( permutations( a ) == Vec<Vec<Int>>{ {1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1} } );

  Vec<Int> b{};

  REQUIRE( permutations( b ) == Vec<Vec<Int>>{ Vec<Int>{} } );
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
  Vec<Int> a = { 1,2,3,4,5,6,7,8,9 };
  auto f = []( auto& x ){ return x < 5; };

  REQUIRE( span( f, a ) == Tup<Vec<Int>, Vec<Int>>{ Vec<Int>{ 1,2,3,4 }, Vec<Int>{ 5,6,7,8,9 } } );

  Vec<Int> b{};

  REQUIRE( span( f, b ) == Tup<Vec<Int>, Vec<Int>>{ Vec<Int>{}, Vec<Int>{} } );
}

TEST_CASE( "break_when :: (T -> Bool) -> [T] -> ([T], [T])", "[break_when]" )
{
  Vec<Int> a = { 1,2,3,4,5,6,7,8,9 };
  auto f = []( auto& x ){ return x > 5; };

  REQUIRE( break_when( f, a ) == Tup<Vec<Int>, Vec<Int>>{ Vec<Int>{ 1,2,3,4,5 }, Vec<Int>{ 6,7,8,9 } } );

  Vec<Int> b{};

  REQUIRE( break_when( f, b ) == Tup<Vec<Int>, Vec<Int>>{ Vec<Int>{}, Vec<Int>{} } );
}

TEST_CASE( "group :: [T] -> [[T]]", "[group]" )
{
  String a = "mississippi";
  Vec<Char> aa{ begin( a ), end( a ) };

  REQUIRE( group( aa ) == Vec<Vec<Char>>{ {'m'},{'i'},{'s','s'},{'i'},{'s','s'},{'i'},{'p','p'},{'i'} } );

  Vec<Char> b{};
  REQUIRE( group( b ) == Vec<Vec<Char>>{} );
}

TEST_CASE( "inits :: [T] -> [[T]]", "[inits]" )
{
  Vec<Int> a = { 1,2,3 };

  REQUIRE( inits( a ) == Vec<Vec<Int>>{ {},{1},{1,2},{1,2,3} } );

  Vec<Int> b{};

  REQUIRE( inits( b ) == Vec<Vec<Int>>{ Vec<Int>{} } );
}

TEST_CASE( "tails :: [T] -> [[T]]", "[tails]" )
{
  Vec<Int> a = { 1,2,3 };

  REQUIRE( tails( a ) == Vec<Vec<Int>>{ {1,2,3},{2,3},{3},{} } );

  Vec<Int> b{};

  REQUIRE( tails( b ) == Vec<Vec<Int>>{ Vec<Int>{} } );
}

TEST_CASE( "isPrefixOf :: [T] -> [T] -> Bool", "[isPrefixOf]" )
{
  String a = "This is a String";
  Vec<Char> aa{ begin( a ), end( a ) };

  String b = "This";
  Vec<Char> bb{ begin( b ), end( b ) };

  REQUIRE( isPrefixOf( bb, aa ) == true );

  String c = "is";
  Vec<Char> cc{ begin( c ), end( c ) };

  REQUIRE( isPrefixOf( cc, aa ) == false );

  Vec<Char> dd{};

  REQUIRE( isPrefixOf( dd, aa ) == true );

  REQUIRE( isPrefixOf( bb, dd ) == false );

  REQUIRE( isPrefixOf( dd, dd ) == true );
}

TEST_CASE( "isSuffixOf :: [T] -> [T] -> Bool", "[isSuffixOf]" )
{
  String a = "This is a String";
  Vec<Char> aa{ begin( a ), end( a ) };

  String b = "String";
  Vec<Char> bb{ begin( b ), end( b ) };

  REQUIRE( isSuffixOf( bb, aa ) == true );

  String c = "is";
  Vec<Char> cc{ begin( c ), end( c ) };

  REQUIRE( isSuffixOf( cc, aa ) == false );

  Vec<Char> dd{};

  REQUIRE( isSuffixOf( dd, aa ) == true );

  REQUIRE( isSuffixOf( bb, dd ) == false );

  REQUIRE( isSuffixOf( dd, dd ) == true );
}

TEST_CASE( "isInfixOf :: [T] -> [T] -> Bool", "[isInfixOf]" )
{
  String a = "This is a String";
  Vec<Char> aa{ begin( a ), end( a ) };

  String b = "is";
  Vec<Char> bb{ begin( b ), end( b ) };

  REQUIRE( isInfixOf( bb, aa ) == true );

  Vec<Char> dd{};

  REQUIRE( isInfixOf( dd, aa ) == true );

  REQUIRE( isInfixOf( bb, dd ) == false );

  REQUIRE( isInfixOf( dd, dd ) == true );
}

TEST_CASE( "partition :: ( T -> Bool ) -> [T] -> ( [T], [T] )", "partition" )
{
  Vec<Int> a = { 1,2,3,4,5,6,7,8,9,0 };

  REQUIRE( partition( even, a ) == Tup<Vec<Int>,Vec<Int>>{ Vec<Int>{2,4,6,8,0},Vec<Int>{1,3,5,7,9} } );

  Vec<Int> b = { 1,3,5,7,9 };

  REQUIRE( partition( even, b ) == Tup<Vec<Int>,Vec<Int>>{ Vec<Int>{},Vec<Int>{1,3,5,7,9} } );

  REQUIRE( partition( odd, b ) == Tup<Vec<Int>,Vec<Int>>{ Vec<Int>{1,3,5,7,9},Vec<Int>{} } );

  Vec<Int> d = {};

  REQUIRE( partition( even, d ) == Tup<Vec<Int>,Vec<Int>>{ Vec<Int>{},Vec<Int>{} } );
}

TEST_CASE( "nub :: [T] -> [T]", "[nub]" )
{
  Vec<Int> a = { 1,1,2,2,3,3 };

  REQUIRE( nub( a ) == Vec<Int>{ 1,2,3 } );

  Vec<Int> b{};

  REQUIRE( nub( b ) == Vec<Int>{} );
}

TEST_CASE( "sort :: [T] -> [T]", "[sort]" )
{
  Vec<Int> a = { 3,2,1 };

  REQUIRE( sort( a ) == Vec<Int>{ 1,2,3 } );

  Vec<Vec<Int>> b = { {9,8,7},{6,5,4},{3,2,1} };

  REQUIRE( sort( b ) == Vec<Vec<Int>>{ {3,2,1},{6,5,4},{9,8,7} } );

  Vec<Int> c{};

  REQUIRE( sort( c ) == Vec<Int>{} );
}

TEST_CASE( "zip :: [S] -> [T] -> [(S, T)]", "zip" )
{
  Vec<Int> a = { 1,2,3,4,5,6,7,8,9 };
  Vec<Char> b = { 'a','b','c','d' };

  REQUIRE( zip( a, b ) == Vec<Tup<Int,Char>>{ {1,'a'},{2,'b'},{3,'c'},{4,'d'} } );

  Vec<Int> c{};

  REQUIRE( zip( a, c ) == Vec<Tup<Int,Int>>{} );

  REQUIRE( zip( c, c ) == Vec<Tup<Int,Int>>{} );
}

TEST_CASE( "zip3 :: [S] -> [T] -> [U] -> [(S,T,U)]", "[zip3]" )
{
  Vec<Int> a = { 1,2,3,4,5,6,7,8,9 };
  Vec<Char> b = { 'a','b','c','d' };
  Vec<String> c = { "e","f","g","h","i" };

  REQUIRE( zip3( a, b, c ) == Vec<Tup<Int,Char,String>>{ {1,'a',"e"},{2,'b',"f"},{3,'c',"g"},{4,'d',"h"} } );

  Vec<Int> d{};

  REQUIRE( zip3( a, b, d ) == Vec<Tup<Int,Char,Int>>{} );

  REQUIRE( zip3( d, d, d ) == Vec<Tup<Int,Int,Int>>{} );
}

TEST_CASE( "zipWith :: ( S -> T -> U ) -> [S] -> [T] -> [U]", "[zipWith]" )
{
  Vec<Int> a = { 1,2,3,4,5,6,7,8,9 };
  Vec<Char> b = { 'a','b','c','d','e' };

  auto f = []( auto& x, auto& y ){
    return String{ y } + show( x );
  };

  REQUIRE( zipWith<String>( f, a, b ) == Vec<String>{ "a1","b2","c3","d4","e5" } );

  Vec<Int> c{};

  REQUIRE( zipWith<String>( f, c, b ) == Vec<String>{} );
}

TEST_CASE( "foldl :: (T -> S -> T) -> T -> [S] -> T", "[foldl]" )
{
  Vec<Int> a = { 1,2,3,4,5,6,7,8,9 };

  auto f = []( auto& x, auto& y ){ return x + y; };

  REQUIRE( foldl( f, 0, a ) == 45 );

  Vec<Int> b{};

  REQUIRE( foldl( f, 0, b ) == 0 );
}

TEST_CASE( "scanl :: (T -> S -> T) -> T -> [S] -> T", "[scanl]" )
{
  Vec<Int> a = { 1,2,3,4,5,6,7,8,9 };

  auto f = []( auto& x, auto& y ){ return x + y; };

  REQUIRE( scanl( f, 0, a ) == Vec<Int>{ 0,1,3,6,10,15,21,28,36,45 } );

  Vec<Int> b{};

  REQUIRE( scanl( f, 0, b ) == Vec<Int>{ 0 } );
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
  Vec<Tup<Char,Int>> a = { {'a',1},{'b',2},{'c',3} };

  REQUIRE( lookup( 'a', a ) == Opt<Int>{ 1 } );

  REQUIRE( lookup( 'd', a ) == Opt<Int>{} );

  Vec<Tup<Char,Int>> b{};

  REQUIRE( lookup( 'a', b ) == Opt<Int>{} );
}
