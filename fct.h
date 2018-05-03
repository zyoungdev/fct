#ifndef functional_algorithms_header
#define functional_algorithms_header

#include <vector>
#include <iostream>
#include <cmath>
#include <tuple>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <optional>
#include <iterator>

namespace fct
{
  using String = std::string;
  using SS = std::stringstream;
  using Bool = bool;
  using Float = float;
  using Double = long double;
  using Int = int;
  using UInt = unsigned int;
  using Char = char;

  template <typename T>
  using Opt = std::optional<T>;

  template <typename T>
  using Vec = std::vector<T>;

  // template <typename S, typename T>
  template <typename ...Ts>
  using Tup = std::tuple<Ts...>;

  using std::begin;
  using std::end;
  using std::rbegin;
  using std::rend;
  using std::advance;

  Double pi = 3.141592653589793238462643383279502884;
  Double e  = 2.718281828459045235360287471352662497;

  template <typename T>
  auto print( Opt<T> const& val, Char lastChar = '\n' ) -> void
  {
    if ( val )
      std::cout << val.value() << lastChar;
    else
      std::cout << "Nothing" << lastChar;
  }

  // print :: T -> void
  template <typename T>
  auto print( T const& val, Char lastChar = '\n' ) -> void
  {
    std::cout << val << lastChar;
  }

  // print :: [T] -> void
  template <typename T>
  auto print( Vec<T> const& xs, Char lastChar = '\n' ) -> void
  {
    if ( xs.empty() )
    {
      std::cout << "[]" << lastChar;
      return;
    }

    std::cout << "[";
    auto i = begin( xs );
    for ( ; i < end( xs ) - 1; advance( i, 1 ) )
      std::cout << *i << ',';
    std::cout << *i << "]" << lastChar;
  }

  // print :: [[T]] -> void
  template <typename T>
  auto print( Vec<Vec<T>> const& xxs, Char lastChar = '\n' ) -> void
  {
    std::cout << "[ ";
    for ( auto const& xs : xxs )
    {
      std::cout << "[ ";
      for ( auto const& x : xs )
      {
        std::cout << x << ' ';
      }
      std::cout << "] ";
    }
    std::cout << "]" << lastChar;
  }

  // toUpper :: Char -> Char
  auto toUpper( Char const& x ) -> Char
  {
    return x == 0x20 ? 0x20 : x - 0x20;
  }

  // toLower :: Char -> Char
  auto toLower( Char const& x ) -> Char
  {
    return x == 0x20 ? 0x20 : x + 0x20;
  }

  // fmap :: ( S -> T ) -> [S] -> [T]
  template <typename S, typename T, typename F>
  auto fmap( F fct, Vec<S> const& xs ) -> Vec<T>
  {
    Vec<T> out{};
    out.reserve( xs.size() );

    for ( auto const& x : xs )
      out.push_back( fct( x ) );

    return out;
  }

  // fmap :: ( Char -> Char ) -> String -> Vec<Char>
  template <typename F>
  auto fmap( F fct, String const& xs ) -> String
  {
    String out{};
    out.reserve( xs.size() );

    for ( auto const& x : xs )
      out.push_back( fct( x ) );

    return out;
  }

  // transpose :: [[T]] -> [[T]]
  template <typename T>
  auto transpose( Vec<Vec<T>> const& xxs ) -> Vec<Vec<T>>
  {
    Vec<Vec<T>> out{};

    for ( uint i = 0; i < xxs.size(); i++ )
    {
      auto const& xs = xxs.at( i );
      for ( uint j = 0; j < xs.size(); j++ )
      {
        auto const& x = xs.at( j );

        if ( j >= out.size() )
          out.push_back( { x } );
        else
          out.at( j ).push_back( x );
      }
    }

    return out;
  }

  // filter :: ( T -> bool ) -> [T]
  template <typename T, typename F>
  auto filter( F predicate, Vec<T> const& xs ) -> Vec<T>
  {
    Vec<T> out{};
    out.reserve( xs.size() );

    for ( auto const& x : xs )
      if ( predicate( x ) )
        out.push_back( x );

    return out;
  }

  // takeWhile :: ( T -> bool ) -> [T] -> [T]
  template <typename T, typename F>
  auto takeWhile( F predicate, Vec<T> const& xs ) -> Vec<T>
  {
    Vec<T> out{};
    out.reserve( xs.size() );

    for ( auto const& x : xs )
      if ( predicate( x ) )
        out.push_back( x );
      else
        break;

    return out;
  }

  // dropWhile :: ( T -> bool ) -> [T] -> [T]
  template <typename T, typename F>
  auto dropWhile( F predicate, Vec<T> const& xs ) -> Vec<T>
  {
    Int i = 0;
    for ( auto const& x : xs )
      if ( predicate( x ) )
        i++;
      else
        break;

    return Vec<T>{ begin( xs ) + i, end( xs ) };
  }

  // head :: [T] -> Opt<T>
  template <typename T>
  auto head( Vec<T> const& xs ) -> Opt<T>
  {
    if ( xs.empty() )
      return Opt<T>{};

    return Opt<T>{ xs.at( 0 ) };
  }

  // tail :: [T] -> [T]
  template <typename T>
  auto tail( Vec<T> const& xs ) -> Vec<T>
  {
    return Vec<T>{ begin( xs ) + 1, end( xs ) };
  }

  // init :: [T] -> [T]
  template <typename T>
  auto init( Vec<T> const& xs ) -> Vec<T>
  {
    return Vec<T>{ begin( xs ), end( xs ) - 1 };
  }

  // last :: [T] -> Opt<T>
  template <typename T>
  auto last( Vec<T> const& xs ) -> Opt<T>
  {
    if ( xs.empty() )
      return Opt<T>{};

    return Opt<T>{ *( end( xs ) - 1 ) };
  }

  // subsets :: [T] -> [[T]]
  template <typename T>
  auto subsets( Vec<T> const& xs ) -> Vec<Vec<T>>
  {
    Vec<Vec<T>> out{};
    out.reserve( std::pow( 2, xs.size() ) );

    // Add the empty set
    out.push_back( Vec<T>{} );

    for ( auto const& x : xs )
    {
      // Create copy of current subsets
      Vec<Vec<T>> new_subsets{ begin( out ), end( out ) };

      // Add element to every new subset
      for ( Vec<T>& s : new_subsets )
        s.push_back( x );

      // Add new subsets to output
      out.insert( end( out ), begin( new_subsets ), end( new_subsets ) );
    }

    return out;
  }

  // odd :: Int -> bool
  auto odd( Int const& val ) -> bool
  {
    return val & 1;
  }

  // even :: Int -> bool
  auto even( Int const& val ) -> bool
  {
    return ! odd( val );
  }

  // abs :: Num -> Num
  template <typename T>
  auto abs( T const& x ) -> T
  {
    return x < 0 ? -x : x;
  }

  // abs :: Num -> Int
  template <typename T>
  auto signum( T const& x ) -> Int
  {
    if ( x < 0 )
      return -1;
    else if ( x > 0 )
      return 1;

    return 0;
  }

  // quotRem :: (Integral a) => T -> T -> ( a, a )
  template <typename T>
  auto quotRem( T const& x, T const& y ) -> Tup<T, T>
  {
    T q = x / y;
    T r = x % y;

    return std::make_tuple( q, r );
  }

  // exp :: Num -> Double
  template <typename T>
  auto exp( T const& x ) -> Double
  {
    return std::pow( e, x );
  }

  // log :: Num -> Double
  template <typename T>
  auto log( T const& x ) -> Double
  {
    return std::log( x );
  }

  // logBase :: T -> T -> T
  template <typename T>
  auto logBase( T const& base, T const& x ) -> Double
  {
    return std::log( x ) / std::log( base );
  }

  // sqrt :: Num -> Double
  template <typename T>
  auto sqrt( T const& x ) -> Double
  {
    return std::sqrt( x );
  }

  // gcd :: T -> T -> T
  template <typename T>
  auto gcd( T const& x, T const& y ) -> T
  {
    T end = x <= y ? x : y;

    T j = 0;
    for ( T i = 1 ; i <= end; i++ )
      if ( abs( x ) % i == 0 && abs( y ) % i == 0 )
        j = i;

    return j;
  }

  // lcm :: T -> T -> T
  template <typename T>
  auto lcm( T const& x, T const& y ) -> T
  {
    T end = x <= y ? x : y;

    for ( T i = 2 ; i <= end; i++ )
      if ( x % i == 0 && y % i == 0 )
        return i;

    return 1;
  }

  // elem :: T -> [b] -> bool
  template <typename T>
  auto elem( T const& el, Vec<T> const& xs ) -> bool
  {
    return any( [&el]( auto const& x ){ return el == x; }, xs );
  }

  // notElem :: T -> [T] -> bool
  template <typename T>
  auto notElem( T const& el, Vec<T> const& xs ) -> bool
  {
    return ! elem( el, xs );
  }

  // maximum :: [T] -> Opt<T>
  template <typename T>
  auto maximum( Vec<T> const& xs ) -> Opt<T>
  {
    if ( xs.empty() )
      return Opt<T>{};

    T out = xs.at( 0 );

    for ( auto const& x : xs )
      if ( x > out )
        out = x;

    return Opt<T>{ out };
  }

  // minimum :: [T] -> Opt<T>
  template <typename T>
  auto minimum( Vec<T> const& xs ) -> Opt<T>
  {
    if ( xs.empty() )
      return Opt<T>{};

    T out = xs.at( 0 );

    for ( auto const& x : xs )
      if ( x < out )
        out = x;

    return Opt<T>{ out };
  }

  // sum :: [T] -> T
  template <typename T>
  auto sum( Vec<T> const& xs ) -> T
  {
    if ( xs.empty() )
      return 0;

    T out = xs.at( 0 );
    for ( auto i = begin( xs ) + 1; i < end( xs ); advance( i, 1 ) )
      out += *i;

    return out;
  }

  // product :: [T] -> T
  template <typename T>
  auto product( Vec<T> const& xs ) -> T
  {
    if ( xs.empty() )
      return 1;

    T out = xs.at( 0 );
    for ( auto i = begin( xs ) + 1; i < end( xs ); advance( i, 1 ) )
      out *= *i;

    return out;
  }

  // id :: T -> T
  template <typename T>
  auto id( T const& x ) -> T
  {
    return x;
  }

  // constant :: S -> T -> S
  template <typename S, typename T>
  auto constant( S const& x, T const& y ) -> S
  {
    // Do some gymnastics to
    // get around unused variable warning
    T out = y;
    out = out;
    return x;
  }

  // flip :: ( S -> T -> U ) -> T -> S -> U
  template <typename S, typename T, typename U, typename F>
  auto flip( F func, S const& x, T const& y ) -> U
  {
    return func( y, x );
  }

  // until :: ( T -> bool ) -> ( T -> T ) -> T -> T
  template <typename T, typename P, typename F>
  auto until( P predicate, F func, T const& x ) -> T
  {
    T out = x;
    while ( ! predicate( out ) )
      out = func( out );

    return out;
  }

  // null :: [T] -> bool
  template <typename T>
  auto null( Vec<T> const& xs ) -> bool
  {
    return xs.empty();
  }

  // length :: [T] -> Num
  template <typename S, typename T = size_t>
  auto length( Vec<S> const& xs ) -> T
  {
    return xs.size();
  }

  // reverse :: [T] -> [T]
  template <typename T>
  auto reverse( Vec<T> const& xs ) -> Vec<T>
  {
    return Vec<T>{ rbegin( xs ), rend( xs ) };
  }

  // conjunction :: [T] -> bool
  template <typename T>
  auto conjunction( Vec<T> const& xs ) -> bool
  {
    if ( xs.empty() )
      return true;

    bool out = xs.at( 0 );
    for ( auto i = begin( xs ) + 1; i < end( xs ); advance( i, 1 ) )
      out = out && *i;

    return out;
  }

  // disjunction :: [T] -> bool
  template <typename T>
  auto disjunction( Vec<T> const& xs ) -> bool
  {
    if ( xs.empty() )
      return false;

    bool out = xs.at( 0 );
    for ( auto i = begin( xs ) + 1; i < end( xs ); advance( i, 1 ) )
      out = out || *i;

    return out;
  }

  // any :: ( T -> bool ) -> [T] -> bool
  template <typename T, typename F>
  auto any( F predicate, Vec<T> const& xs ) -> bool
  {
    return std::any_of( begin( xs ), end( xs ), predicate );
  }

  // all :: ( T -> bool ) -> [T] -> bool
  template <typename T, typename F>
  auto all( F predicate, Vec<T> const& xs ) -> bool
  {
    return std::all_of( begin( xs ), end( xs ), predicate );
  }

  // concat :: [[T]] -> [T]
  template <typename T>
  auto concat( Vec<Vec<T>> const& xxs ) -> Vec<T>
  {
    // Count number of items;
    size_t i = 0;
    for ( auto const& xs : xxs )
      i += xs.size();

    Vec<T> out{};
    out.reserve( i );

    for ( auto const& xs : xxs )
      out.insert( end( out ), begin( xs ), end( xs ) );

    return out;
  }

  // replicate :: UInt -> T - [T]
  template <typename T>
  auto replicate( UInt num, T const& val ) -> Vec<T>
  {
    return Vec<T>( num, val );
  }

  // take :: UInt -> [T] -> [T]
  template <typename T>
  auto take( UInt num, Vec<T> const& xs ) -> Vec<T>
  {
    if ( xs.empty() )
      return Vec<T>{};
    return Vec<T>{ begin( xs ), begin( xs ) + num };
  }

  // drop :: UInt -> [T] -> [T]
  template <typename T>
  auto drop( UInt num, Vec<T> const& xs ) -> Vec<T>
  {
    if ( xs.empty() )
      return Vec<T>{};
    return Vec<T>{ begin( xs ) + num, end( xs ) };
  }

  // splitAt :: UInt -> [T] -> ( [T], [T] )
  template <typename T>
  auto splitAt( UInt index, Vec<T> const& xs ) -> Tup<Vec<T>, Vec<T>>
  {
    if ( index >= xs.size() )
      return std::make_tuple( Vec<T>{ begin( xs ), end( xs ) }, Vec<T>{} );

    Vec<T> left{ begin( xs ), begin( xs ) + index };
    Vec<T> right{ begin( xs ) + index, end( xs ) };

    return std::make_tuple( left, right );
  }

  // lines :: String -> [String]
  auto lines( String const& str ) -> Vec<String>
  {
    Vec<String> out{};

    SS ss;
    ss.str( str );
    for ( String line; std::getline( ss, line ); )
      out.push_back( line );

    return out;
  }

  // words :: String -> [String]
  auto words( String const& str ) -> Vec<String>
  {
    Vec<String> out{};

    SS ss;
    ss.str( str );
    for ( String line; std::getline( ss, line, ' ' ); )
      out.push_back( line );

    return out;
  }

  // unlines :: [String] -> String
  auto unlines( Vec<String> const& xs ) -> String
  {
    String out = "";
    for ( auto const& x : xs )
      out += x + "\n";

    return out;
  }

  // unwords :: [String] -> String
  auto unwords( Vec<String> const& xs ) -> String
  {
    if ( xs.empty() )
      return String{};

    String out = "";
    auto a = begin( xs );
    auto last = end( xs ) - 1;

    for ( ; a < last; advance( a, 1 ) )
      out += *a + " ";
    out += *last;

    return out;
  }

  // putChar :: Char -> void
  auto putChar( Char const& ch ) -> void
  {
    std::cout << ch;
  }

  // putStr :: String -> void
  auto putStr( String const& str ) -> void
  {
    std::cout << str;
  }

  // putStrLn :: String -> void
  auto putStrLn( String const& str ) -> void
  {
    std::cout << str << '\n';
  }

  // getChar :: Char
  auto getChar() -> Char
  {
    Char out;
    std::cin >> out;
    return out;
  }

  // getLine :: String
  auto getLine() -> String
  {
    String out = "";
    std::getline( std::cin, out );
    return out;
  }

  // readFile :: String -> String
  auto readFile( String const& filePath ) -> String
  {
    std::ifstream file( filePath, std::ios_base::in );

    return String{ std::istreambuf_iterator<Char>(file), std::istreambuf_iterator<Char>() };
  }

  // readLn :: String -> String
  auto readLn( String const& filePath ) -> String
  {
    std::ifstream file( filePath, std::ios_base::in );
    String out = "";
    std::getline( file, out );
    return out;
  }

  // writeFile :: String -> String -> void
  auto writeFile( String const& filePath, String const& str ) -> void
  {
    std::ofstream file( filePath, std::ios_base::out );
    file << str;
  }

  // appendFile :: String -> String -> void
  auto appendFile( String const& filePath, String const& str ) -> void
  {
    std::ofstream file( filePath, std::ios_base::app );
    file << str;
  }

  // show :: T -> String
  template <typename T>
  auto show( T const& x ) -> String
  {
    return std::to_string( x );
  }

  // intersect :: [T] -> [T] -> [T]
  template <typename T>
  auto intersect( Vec<T> const& xs, Vec<T> const& ys ) -> Vec<T>
  {
    Vec<T> out{};
    auto const& smaller = xs.size() <= ys.size() ? xs : ys;
    auto const& larger = xs.size() > ys.size() ? xs : ys;

    for ( auto const& s : smaller )
      if ( elem( s, larger ) )
        out.push_back( s );

    return out;
  }

  // union :: [T] -> [T] -> [T]
  template <typename T>
  auto union_of( Vec<T> const& xs, Vec<T> const& ys ) -> Vec<T>
  {
    Vec<T> out{};
    Vec<T> const* smaller = xs.size() <= ys.size() ? &xs : &ys;
    Vec<T> const* larger = xs.size() > ys.size() ? &xs : &ys;

    for ( auto const& s : *smaller )
      if ( notElem( s, *larger ) )
        out.push_back( s );

    for ( auto const& l : *larger )
      out.push_back( l );

    return out;
  }

  // intersperse :: T -> [T] -> [T]
  template <typename T>
  auto intersperse( T const& y, Vec<T> const& xs ) -> Vec<T>
  {
    if ( xs.empty() )
      return Vec<T>{};

    Vec<T> out{};

    auto a = begin( xs );
    for ( ; a < end( xs ) - 1; advance( a, 1 ) )
    {
      out.push_back( *a );
      out.push_back( y );
    }
    out.push_back( *a );

    return out;
  }

  // intercalate :: [T] -> [[T]] -> [T]
  template <typename T>
  auto intercalate( Vec<T> const& xs, Vec<Vec<T>> const& xxs ) -> Vec<T>
  {
    return concat( intersperse( xs, xxs ) );
  }

  // permutations :: [T] -> [[T]]
  template <typename T>
  auto permutations( Vec<T> const& xs ) -> Vec<Vec<T>>
  {
    Vec<Vec<T>> out{};
    Vec<T> mut_xs = xs;

    std::sort( begin( mut_xs ), end( mut_xs ) );

    // Factorial of xs.size() == # of permutations
    UInt size = 1;
    for (UInt i = xs.size(); i > 0; i--)
      size *= i;
    mut_xs.reserve( size );

    do
    {
      out.push_back( mut_xs );
    }
    while ( std::next_permutation( begin( mut_xs ), end( mut_xs ) ) );

    return out;
  }

  // iterate :: (T -> T) -> T -> [T]
  template <typename T, typename F>
  auto iterate( UInt num, F func, T const& x ) -> Vec<T>
  {
    Vec<T> out{};
    out.reserve( num );

    for ( uint i = 0; i < num; i++ )
      out.push_back( func( x ) );

    return out;
  }

  // span :: (T -> Bool) -> [T] -> ([T], [T])
  template <typename T, typename F>
  auto span( F predicate, Vec<T> const& xs ) -> Tup<Vec<T>, Vec<T>>
  {
    Int i = 0;
    for ( auto const& x : xs )
      if ( predicate( x ) )
        i++;
      else
        break;

    return std::make_tuple( Vec<T>{ begin( xs ), begin( xs ) + i }, Vec<T>{ begin( xs ) + i, end( xs ) } );
  }

  // break_when :: (T -> Bool) -> [T] -> ([T], [T])
  template <typename T, typename F>
  auto break_when( F predicate, Vec<T> const& xs ) -> Tup<Vec<T>, Vec<T>>
  {
    Int i = 0;
    for ( auto const& x : xs )
      if ( ! predicate( x ) )
        i++;
      else
        break;

    return std::make_tuple( Vec<T>{ begin( xs ), begin( xs ) + i }, Vec<T>{ begin( xs ) + i, end( xs ) } );
  }

  // group :: [T] -> [[T]]
  template <typename T>
  auto group( Vec<T> const& xs ) -> Vec<Vec<T>>
  {
    if ( xs.empty() )
      return Vec<Vec<T>>{};

    Vec<Vec<T>> out{};

    auto a = begin( xs );
    auto b = a;

    while ( b < end( xs ) )
    {
      if ( *b == *a )
      {
        advance( b, 1 );
      }
      else
      {
        out.push_back( Vec<T>{ a, b } );
        a = b;
      }
    }
    out.push_back( Vec<T>{ a, b } );

    return out;
  }

  // inits :: [T] -> [[T]]
  template <typename T>
  auto inits( Vec<T> const& xs ) -> Vec<Vec<T>>
  {
    Vec<Vec<T>> out{};

    auto i = begin( xs );

    for ( ; i < end( xs ); advance( i, 1 ) )
      out.push_back( Vec<T>{ begin( xs ), i } );
    out.push_back( Vec<T>{ begin( xs ), i } );

    return out;
  }

  // tails :: [T] -> [[T]]
  template <typename T>
  auto tails( Vec<T> const& xs ) -> Vec<Vec<T>>
  {
    Vec<Vec<T>> out{};

    auto a = begin( xs );

    for ( ; a < end( xs ); advance( a, 1 ) )
      out.push_back( Vec<T>{ a, end( xs ) } );
    out.push_back( Vec<T>{} );

    return out;
  }

  // isPrefixOf :: [T] -> [T] -> Bool
  template <typename T>
  auto isPrefixOf( Vec<T> const& xs, Vec<T> const& ys ) -> bool
  {
    auto ys_inits = inits( ys );
    return elem( xs, ys_inits );
  }

  // isSuffixOf :: [T] -> [T] -> Bool
  template <typename T>
  auto isSuffixOf( Vec<T> const& xs, Vec<T> const& ys ) -> bool
  {
    auto ys_tails = tails( ys );
    return elem( xs, ys_tails );
  }

  // isInfixOf :: [T] -> [T] -> Bool
  template <typename T>
  auto isInfixOf( Vec<T> const& xs, Vec<T> const& ys ) -> bool
  {
    if ( xs.empty() )
      return true;

    auto a = begin( ys );
    auto b = begin( ys ) + xs.size();

    Vec<T> test{ begin( xs ), end( xs ) };

    for ( ; b < end( ys ); advance( a, 1 ), advance( b, 1 ) )
      if ( test == Vec<T>{ a, b } )
        return true;

    return false;
  }

  // partition :: ( T -> bool ) -> [T] -> ( [T], [T] )
  template <typename T, typename F>
  auto partition( F predicate, Vec<T> const& xs ) -> Tup<Vec<T>, Vec<T>>
  {
    Vec<T> left{};
    Vec<T> right{};

    for ( auto const& x : xs )
      if ( predicate( x ) )
        left.push_back( x );
      else
        right.push_back( x );

    return std::make_tuple( left, right );
  }

  // nub :: [T] -> [T]
  template <typename T>
  auto nub( Vec<T> const& xs ) -> Vec<T>
  {
    Vec<T> out{};

    for ( auto const& x : xs )
      if ( ! elem( x, out ) )
        out.push_back( x );

    return out;
  }

  // sort :: [T] -> [T]
  template <typename T>
  auto sort( Vec<T> const& xs ) -> Vec<T>
  {
    Vec<T> out{ begin( xs ), end( xs ) };
    std::sort( begin( out ), end( out ) );
    return out;
  }

  // zip :: [S] -> [T] -> [(S, T)]
  template <typename S, typename T>
  auto zip( Vec<S> const& xs, Vec<T> const& ys ) -> Vec<Tup<S,T>>
  {
    Vec<Tup<S,T>> out{};

    auto x = begin( xs );
    auto y = begin( ys );

    while ( x < end( xs ) && y < end( ys ) )
    {
      out.push_back( Tup<S,T>{ *x, *y } );
      advance( x, 1 );
      advance( y, 1 );
    }

    return out;
  }
}

#endif
