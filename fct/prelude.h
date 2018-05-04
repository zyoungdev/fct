#ifndef functional_algorithms_prelude_header
#define functional_algorithms_prelude_header

#include "fct/include.h"
#include "fct/using.h"

namespace fct
{
  constexpr Double pi = 3.141592653589793238462643383279502884;
  constexpr Double e  = 2.718281828459045235360287471352662497;

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
  template <typename T, template <typename> typename Cont>
  auto print( Cont<T> const& xs, Char lastChar = '\n' ) -> void
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
  template <typename T, template <typename> typename Cont>
  auto print( Cont<Cont<T>> const& xxs, Char lastChar = '\n' ) -> void
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
  template <typename T, typename S, typename F, template <typename> typename Cont>
  auto fmap( F fct, Cont<S> const& xs ) -> Cont<T>
  {
    Cont<T> out{};
    out.reserve( xs.size() );

    for ( auto const& x : xs )
      out.push_back( fct( x ) );

    return out;
  }

  // fmap :: ( Char -> Char ) -> String -> String 
  template <typename F>
  auto fmap( F fct, String const& xs ) -> String
  {
    String out{};
    out.reserve( xs.size() );

    for ( auto const& x : xs )
      out.push_back( fct( x ) );

    return out;
  }

  // filter :: ( T -> bool ) -> [T]
  template <typename T, typename F, template <typename> typename Cont>
  auto filter( F predicate, Cont<T> const& xs ) -> Cont<T>
  {
    Cont<T> out{};
    out.reserve( xs.size() );

    for ( auto const& x : xs )
      if ( predicate( x ) )
        out.push_back( x );

    return out;
  }

  // takeWhile :: ( T -> bool ) -> [T] -> [T]
  template <typename T, typename F, template <typename> typename Cont>
  auto takeWhile( F predicate, Cont<T> const& xs ) -> Cont<T>
  {
    Cont<T> out{};
    out.reserve( xs.size() );

    for ( auto const& x : xs )
      if ( predicate( x ) )
        out.push_back( x );
      else
        break;

    return out;
  }

  // dropWhile :: ( T -> bool ) -> [T] -> [T]
  template <typename T, typename F, template <typename> typename Cont>
  auto dropWhile( F predicate, Cont<T> const& xs ) -> Cont<T>
  {
    Int i = 0;
    for ( auto const& x : xs )
      if ( predicate( x ) )
        i++;
      else
        break;

    return Cont<T>{ begin( xs ) + i, end( xs ) };
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
  template <typename T, template <typename> typename Cont>
  auto tail( Cont<T> const& xs ) -> Cont<T>
  {
    return Cont<T>{ begin( xs ) + 1, end( xs ) };
  }

  // init :: [T] -> [T]
  template <typename T, template <typename> typename Cont>
  auto init( Cont<T> const& xs ) -> Cont<T>
  {
    return Cont<T>{ begin( xs ), end( xs ) - 1 };
  }

  // last :: [T] -> Opt<T>
  template <typename T, template <typename> typename Cont>
  auto last( Cont<T> const& xs ) -> Opt<T>
  {
    if ( xs.empty() )
      return Opt<T>{};

    return Opt<T>{ *( end( xs ) - 1 ) };
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
  template <typename T, template <typename> typename Cont>
  auto elem( T const& el, Cont<T> const& xs ) -> bool
  {
    return any( [&el]( auto const& x ){ return el == x; }, xs );
  }

  // notElem :: T -> [T] -> bool
  template <typename T, template <typename> typename Cont>
  auto notElem( T const& el, Cont<T> const& xs ) -> bool
  {
    return ! elem( el, xs );
  }

  // maximum :: [T] -> Opt<T>
  template <typename T, template <typename> typename Cont>
  auto maximum( Cont<T> const& xs ) -> Opt<T>
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
  template <typename T, template <typename> typename Cont>
  auto minimum( Cont<T> const& xs ) -> Opt<T>
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
  template <typename T, template <typename> typename Cont>
  auto sum( Cont<T> const& xs ) -> T
  {
    if ( xs.empty() )
      return 0;

    T out = xs.at( 0 );
    for ( auto i = begin( xs ) + 1; i < end( xs ); advance( i, 1 ) )
      out += *i;

    return out;
  }

  // product :: [T] -> T
  template <typename T, template <typename> typename Cont>
  auto product( Cont<T> const& xs ) -> T
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
  template <typename U, typename S, typename T, typename F>
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
  template <typename T, template <typename> typename Cont>
  auto null( Cont<T> const& xs ) -> bool
  {
    return xs.empty();
  }

  // length :: [T] -> Num
  template <typename S, typename T = size_t, template <typename> typename Cont>
  auto length( Cont<S> const& xs ) -> T
  {
    return xs.size();
  }

  // reverse :: [T] -> [T]
  template <typename T, template <typename> typename Cont>
  auto reverse( Cont<T> const& xs ) -> Cont<T>
  {
    return Cont<T>{ rbegin( xs ), rend( xs ) };
  }

  // Haskell and
  // conjunction :: [T] -> bool
  template <typename T, template <typename> typename Cont>
  auto conjunction( Cont<T> const& xs ) -> bool
  {
    if ( xs.empty() )
      return true;

    bool out = xs.at( 0 );
    for ( auto i = begin( xs ) + 1; i < end( xs ); advance( i, 1 ) )
      out = out && *i;

    return out;
  }

  // disjunction :: [T] -> bool
  template <typename T, template <typename> typename Cont>
  auto disjunction( Cont<T> const& xs ) -> bool
  {
    if ( xs.empty() )
      return false;

    bool out = xs.at( 0 );
    for ( auto i = begin( xs ) + 1; i < end( xs ); advance( i, 1 ) )
      out = out || *i;

    return out;
  }

  // any :: ( T -> bool ) -> [T] -> bool
  template <typename T, typename F, template <typename> typename Cont>
  auto any( F predicate, Cont<T> const& xs ) -> bool
  {
    return std::any_of( begin( xs ), end( xs ), predicate );
  }

  // all :: ( T -> bool ) -> [T] -> bool
  template <typename T, typename F, template <typename> typename Cont>
  auto all( F predicate, Cont<T> const& xs ) -> bool
  {
    return std::all_of( begin( xs ), end( xs ), predicate );
  }

  // concat :: [[T]] -> [T]
  template <typename T, template <typename> typename Cont>
  auto concat( Cont<Cont<T>> const& xxs ) -> Cont<T>
  {
    // Count number of items;
    size_t i = 0;
    for ( auto const& xs : xxs )
      i += xs.size();

    Cont<T> out{};
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
  template <typename T, template <typename> typename Cont>
  auto take( UInt num, Cont<T> const& xs ) -> Cont<T>
  {
    if ( xs.empty() )
      return Cont<T>{};
    return Cont<T>{ begin( xs ), begin( xs ) + num };
  }

  // drop :: UInt -> [T] -> [T]
  template <typename T, template <typename> typename Cont>
  auto drop( UInt num, Cont<T> const& xs ) -> Cont<T>
  {
    if ( xs.empty() )
      return Cont<T>{};
    return Cont<T>{ begin( xs ) + num, end( xs ) };
  }

  // splitAt :: UInt -> [T] -> ( [T], [T] )
  template <typename T, template <typename> typename Cont>
  auto splitAt( UInt index, Cont<T> const& xs ) -> Tup<Cont<T>, Cont<T>>
  {
    if ( index >= xs.size() )
      return std::make_tuple( Cont<T>{ begin( xs ), end( xs ) }, Cont<T>{} );

    Cont<T> left{ begin( xs ), begin( xs ) + index };
    Cont<T> right{ begin( xs ) + index, end( xs ) };

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
  template <template <typename> typename Cont>
  auto unlines( Cont<String> const& xs ) -> String
  {
    String out = "";
    for ( auto const& x : xs )
      out += x + "\n";

    return out;
  }

  // unwords :: [String] -> String
  template <template <typename> typename Cont>
  auto unwords( Cont<String> const& xs ) -> String
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
  template <typename T, typename F, template <typename> typename Cont>
  auto span( F predicate, Cont<T> const& xs ) -> Tup<Cont<T>, Cont<T>>
  {
    Int i = 0;
    for ( auto const& x : xs )
      if ( predicate( x ) )
        i++;
      else
        break;

    return std::make_tuple( Cont<T>{ begin( xs ), begin( xs ) + i }, Cont<T>{ begin( xs ) + i, end( xs ) } );
  }

  // break_when :: (T -> Bool) -> [T] -> ([T], [T])
  template <typename T, typename F, template <typename> typename Cont>
  auto break_when( F predicate, Cont<T> const& xs ) -> Tup<Cont<T>, Cont<T>>
  {
    Int i = 0;
    for ( auto const& x : xs )
      if ( ! predicate( x ) )
        i++;
      else
        break;

    return std::make_tuple( Cont<T>{ begin( xs ), begin( xs ) + i }, Cont<T>{ begin( xs ) + i, end( xs ) } );
  }

  // zip :: [S] -> [T] -> [(S, T)]
  template <typename S, typename T, template <typename> typename Cont>
  auto zip( Cont<S> const& xs, Cont<T> const& ys ) -> Cont<Tup<S,T>>
  {
    Cont<Tup<S,T>> out{};
    out.reserve( xs.size() <= ys.size() ? xs.size() : ys.size() );

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

  // zipWith :: ( S -> T -> U ) -> [S] -> [T] -> [U]
  template <typename U, typename S, typename T, typename F, template <typename> typename Cont>
  auto zipWith( F func, Cont<S> const& xs, Cont<T> const& ys ) -> Cont<U>
  {
    Cont<U> out{};
    out.reserve( xs.size() <= ys.size() ? xs.size() : ys.size() );

    auto x = begin( xs );
    auto y = begin( ys );

    while ( x < end( xs ) && y < end( ys ) )
    {
      out.push_back( func( *x, *y ) );
      advance( x, 1 );
      advance( y, 1 );
    }

    return out;
  }
}

#endif