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
  along with fct.  If not, see <http://www.gnu.org/licenses/>.

  Copyright 2018 Zachary Young
  */

#ifndef functional_algorithms_prelude_header
#define functional_algorithms_prelude_header

#include "fct/include.h"
#include "fct/using.h"

namespace fct
{
  constexpr Double pi = 3.141592653589793238462643383279502884;
  constexpr Double e  = 2.718281828459045235360287471352662497;

  // show :: T -> StdString
  template <typename T>
  auto show( T const& x ) -> StdString
  {
    return std::to_string( x );
  }

  // show :: Char -> Char
  auto show( Char const& x ) -> Char
  {
    return x;
  }

  // show :: Char* -> StdString
  auto show( char const* x ) -> StdString
  {
    return StdString{ x };
  }

  // show :: Bool -> StdString
  auto show( Bool const& x ) -> StdString
  {
    return x ? "True" : "False";
  }

  // print :: T -> void
  template <typename T>
  auto print( T const& val, Char lastChar = '\n' ) -> void
  {
    std::cout << show( val ) << lastChar;
  }

  // print :: StdString -> void
  auto print( StdString const& val, Char lastChar = '\n' ) -> void
  {
    std::cout << val << lastChar;
  }

  template <typename T>
  auto print( Opt<T> const& val, Char lastChar = '\n' ) -> void
  {
    if ( val )
      print( val.value(), lastChar );
    else
      std::cout << "Nothing" << lastChar;
  }

  template<class ...Ts, std::size_t... Is>
  void print_tuple( Tup<Ts...> const& tup, std::index_sequence<Is...> )
  {
    ( ( print( Is == 0 ? "" : ",", '\0' ) , print( std::get<Is>( tup ), '\0' ) ) , ... );
  }

  // print :: (Ts...) -> void
  template <typename ...Ts>
  auto print( Tup<Ts...> const& val, Char lastChar = '\n' ) -> void
  {
    std::cout << '(';
    print_tuple( val, std::index_sequence_for<Ts...>{} );
    std::cout << ")" << lastChar;
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
    auto x = begin( xs );
    for ( ; x < end( xs ) - 1; advance( x, 1 ) )
      print( *x, ',' );
    print( *x, ']' );
    std::cout << lastChar;
  }

  // print :: [Char] -> void
  auto print( String const& xs, Char lastChar = '\n' ) -> void
  {
    for ( auto x = begin( xs ) ; x < end( xs ); advance( x, 1 ) )
      print( *x, '\0' );
    std::cout << lastChar;
  }

  // print :: [[T]] -> void
  template <typename T, template <typename> typename Cont>
  auto print( Cont<Cont<T>> const& xxs, Char lastChar = '\n' ) -> void
  {
    if ( xxs.empty() )
    {
      std::cout << "[]" << lastChar;
      return;
    }

    std::cout << "[";

    auto xs = begin( xxs );
    for ( ; xs < end( xxs ) - 1; advance( xs, 1 ) )
      print( *xs, ',' );
    print( *xs, ']' );

    std::cout << lastChar;
  }

  // toStr :: StdString -> String
  auto toStr( StdString const& x ) -> String
  {
    return String{ begin( x ), end( x ) };
  }

  // toStdStr :: String -> StdString
  auto toStdStr( String const& xs ) -> StdString
  {
    return StdString{ begin( xs ), end( xs ) };
  }

  // Str :: const Char* -> String
  auto Str( const Char* x ) -> String
  {
    return String{ x, x + std::strlen( x ) };
  }

  // operator "" _s :: const Char* -> std::size_t -> String
  auto operator "" _s( const Char* x, std::size_t s ) -> String
  {
    return String{ x, x + s };
  }

  // toUpper :: Char -> Char
  auto toUpper( Char const& x ) -> Char
  {
    return x > 0x60 && x < 0x7B ? x - 0x20 : x;
  }

  // toLower :: Char -> Char
  auto toLower( Char const& x ) -> Char
  {
    return x > 0x40 && x < 0x5B ? x + 0x20 : x;
  }

  // fmap :: ( S -> T ) -> [S] -> [T]
  template <typename T, typename S, template <typename> typename Cont, typename F>
  auto fmap( F fct, Cont<S> const& xs ) -> Cont<T>
  {
    Cont<T> out{};
    out.reserve( xs.size() );

    for ( auto const& x : xs )
      out.push_back( fct( x ) );

    return out;
  }

  // fmap :: ( Char -> Char ) -> StdString -> StdString 
  template <typename F>
  auto fmap( F fct, StdString const& xs ) -> StdString
  {
    StdString out{};
    out.reserve( xs.size() );

    for ( auto const& x : xs )
      out.push_back( fct( x ) );

    return out;
  }

  // filter :: ( T -> Bool ) -> [T]
  template <typename T, template <typename> typename Cont, typename F>
  auto filter( F predicate, Cont<T> const& xs ) -> Cont<T>
  {
    Cont<T> out{};
    out.reserve( xs.size() );

    for ( auto const& x : xs )
      if ( predicate( x ) )
        out.push_back( x );

    return out;
  }

  // takeWhile :: ( T -> Bool ) -> [T] -> [T]
  template <typename T, template <typename> typename Cont, typename F>
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

  // dropWhile :: ( T -> Bool ) -> [T] -> [T]
  template <typename T, template <typename> typename Cont, typename F>
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

  // fst :: (S,T) -> S
  template <typename S, typename T>
  auto fst( Tup<S,T> const& tup )
  {
    return std::get<0>( tup );
  }

  // snd :: (S,T) -> T
  template <typename S, typename T>
  auto snd( Tup<S,T> const& tup )
  {
    return std::get<1>( tup );
  }

  // odd :: Int -> Bool
  auto odd( Int const& val ) -> Bool
  {
    return val & 1;
  }

  // even :: Int -> Bool
  auto even( Int const& val ) -> Bool
  {
    return ! odd( val );
  }

  // negate :: Num -> Num
  template <typename Num>
  auto negate( Num const& x ) -> Num
  {
    return -x;
  }

  // abs :: Num -> Num
  template <typename Num>
  auto abs( Num const& x ) -> Num
  {
    return x < 0 ? -x : x;
  }

  // signum :: Num -> Int
  template <typename Num>
  auto signum( Num const& x ) -> Int
  {
    if ( x < 0 )
      return -1;
    else if ( x > 0 )
      return 1;

    return 0;
  }

  // quotRem :: T -> T -> ( T, T )
  template <typename T>
  auto quotRem( T const& x, T const& y ) -> Tup<T, T>
  {
    T q = x / y;
    T r = x % y;

    return std::make_tuple( q, r );
  }

  // exp :: Num -> Double
  template <typename Num>
  auto exp( Num const& x ) -> Double
  {
    return std::pow( e, x );
  }

  // log :: Num -> Double
  template <typename Num>
  auto log( Num const& x ) -> Double
  {
    return std::log( x );
  }

  // logBase :: Num -> Num -> Double
  template <typename Num>
  auto logBase( Num const& base, Num const& x ) -> Double
  {
    return std::log( x ) / std::log( base );
  }

  // sqrt :: Num -> Double
  template <typename Num>
  auto sqrt( Num const& x ) -> Double
  {
    return std::sqrt( x );
  }

  // gcd :: Num -> Num -> Num
  template <typename Num>
  auto gcd( Num const& x, Num const& y ) -> Num
  {
    Num end = x <= y ? x : y;

    Num j = 0;
    for ( Num i = 1 ; i <= end; i++ )
      if ( abs( x ) % i == 0 && abs( y ) % i == 0 )
        j = i;

    return j;
  }

  // lcm :: Num -> Num -> Num
  template <typename Num>
  auto lcm( Num const& x, Num const& y ) -> Num
  {
    Num end = x <= y ? x : y;

    for ( Num i = 2 ; i <= end; i++ )
      if ( x % i == 0 && y % i == 0 )
        return i;

    return 1;
  }

  // elem :: T -> [b] -> Bool
  template <typename T, template <typename> typename Cont>
  auto elem( T const& el, Cont<T> const& xs ) -> Bool
  {
    return any( [&el]( auto const& x ){ return el == x; }, xs );
  }

  // notElem :: T -> [T] -> Bool
  template <typename T, template <typename> typename Cont>
  auto notElem( T const& el, Cont<T> const& xs ) -> Bool
  {
    return ! elem( el, xs );
  }

  // max :: T -> T -> T
  template <typename T>
  auto max( T const& x, T const& y ) -> T
  {
    return x >= y ? x : y;
  }

  // min :: T -> T -> T
  template <typename T>
  auto min( T const& x, T const& y ) -> T
  {
    return x <= y ? x : y;
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

  // sum :: [Num] -> Num
  template <typename Num, template <typename> typename Cont>
  auto sum( Cont<Num> const& xs ) -> Num
  {
    if ( xs.empty() )
      return 0;

    Num out = xs.at( 0 );
    for ( auto i = begin( xs ) + 1; i < end( xs ); advance( i, 1 ) )
      out += *i;

    return out;
  }

  // product :: [Num] -> Num
  template <typename Num, template <typename> typename Cont>
  auto product( Cont<Num> const& xs ) -> Num
  {
    if ( xs.empty() )
      return 1;

    Num out = xs.at( 0 );
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
  auto constant( S const& x, [[maybe_unused]] T const& y ) -> S
  {
    return x;
  }

  // flip :: ( S -> T -> U ) -> T -> S -> U
  template <typename U, typename S, typename T, typename F>
  auto flip( F func, S const& x, T const& y ) -> U
  {
    return func( y, x );
  }

  // until :: ( T -> Bool ) -> ( T -> T ) -> T -> T
  template <typename T, typename P, typename F>
  auto until( P predicate, F func, T const& x ) -> T
  {
    T out = x;
    while ( ! predicate( out ) )
      out = func( out );

    return out;
  }

  // null :: [T] -> Bool
  template <typename T, template <typename> typename Cont>
  auto null( Cont<T> const& xs ) -> Bool
  {
    return xs.empty();
  }

  // length :: [T] -> Size_t
  template <typename S, template <typename> typename Cont>
  auto length( Cont<S> const& xs ) -> size_t
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
  // conjunction :: [T] -> Bool
  template <typename T, template <typename> typename Cont>
  auto conjunction( Cont<T> const& xs ) -> Bool
  {
    if ( xs.empty() )
      return true;

    Bool out = xs.at( 0 );
    for ( auto i = begin( xs ) + 1; i < end( xs ); advance( i, 1 ) )
      out = out && *i;

    return out;
  }

  // disjunction :: [T] -> Bool
  template <typename T, template <typename> typename Cont>
  auto disjunction( Cont<T> const& xs ) -> Bool
  {
    if ( xs.empty() )
      return false;

    Bool out = xs.at( 0 );
    for ( auto i = begin( xs ) + 1; i < end( xs ); advance( i, 1 ) )
      out = out || *i;

    return out;
  }

  // any :: ( T -> Bool ) -> [T] -> Bool
  template <typename T, template <typename> typename Cont, typename F>
  auto any( F predicate, Cont<T> const& xs ) -> Bool
  {
    return std::any_of( begin( xs ), end( xs ), predicate );
  }

  // all :: ( T -> Bool ) -> [T] -> Bool
  template <typename T, template <typename> typename Cont, typename F>
  auto all( F predicate, Cont<T> const& xs ) -> Bool
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
    ss.str( toStdStr( str ) );
    for ( StdString line; std::getline( ss, line ); )
      out.push_back( toStr( line ) );

    return out;
  }

  // words :: String -> [String]
  auto words( String const& x ) -> Vec<String>
  {
    Vec<String> out{};

    SS ss;
    ss.str( toStdStr( x ) );
    for ( StdString line; std::getline( ss, line, ' ' ); )
      out.push_back( toStr( line ) );

    return out;
  }

  // unlines :: [String] -> String
  template <template <typename> typename Cont>
  auto unlines( Cont<String> const& xs ) -> String
  {
    String out{};
    for ( auto const& x : xs )
    {
      out.insert( end( out ), begin( x ), end( x ) );
      out.push_back( '\n' );
    }
      // out += x + "\n";

    return out;
  }

  // unwords :: [String] -> String
  template <template <typename> typename Cont>
  auto unwords( Cont<String> const& xs ) -> String
  {
    if ( xs.empty() )
      return String{};

    String out{};
    auto a = begin( xs );
    for ( ; a < end( xs ) - 1; advance( a, 1 ) )
    {
      out.insert( end( out ), begin( *a ), end( *a ) );
      out.push_back( ' ' );
    }
    out.insert( end( out ), begin( *a ), end( *a ) );

    return out;
  }

  // putChar :: Char -> void
  auto putChar( Char const& ch ) -> void
  {
    std::cout << ch;
  }

  // putStr :: String -> void
  auto putStr( String const& xs ) -> void
  {
    for ( auto const& x : xs )
      std::cout << x;
  }

  // putStrLn :: String -> void
  auto putStrLn( String const& xs ) -> void
  {
    for ( auto const& x : xs )
      std::cout << x;
    std::cout << '\n';
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
    StdString out{};
    std::getline( std::cin, out );
    return toStr( out );
  }

  // readFile :: StdString -> StdString
  auto readFile( StdString const& filePath ) -> StdString
  {
    std::ifstream file( filePath, std::ios_base::in );

    return StdString{ std::istreambuf_iterator<Char>(file), std::istreambuf_iterator<Char>() };
  }

  // readLn :: StdString -> StdString
  auto readLn( StdString const& filePath ) -> StdString
  {
    std::ifstream file( filePath, std::ios_base::in );
    StdString out = "";
    std::getline( file, out );
    return out;
  }

  // writeFile :: StdString -> StdString -> void
  auto writeFile( StdString const& filePath, StdString const& str ) -> void
  {
    std::ofstream file( filePath, std::ios_base::out );
    file << str;
  }

  // appendFile :: StdString -> StdString -> void
  auto appendFile( StdString const& filePath, StdString const& str ) -> void
  {
    std::ofstream file( filePath, std::ios_base::app );
    file << str;
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
  template <typename T, template <typename> typename Cont, typename F>
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
  template <typename T, template <typename> typename Cont, typename F>
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

  // zip3 :: [S] -> [T] -> [U] -> [(S, T, U)]
  template <typename S, typename T, typename U, template <typename> typename Cont>
  auto zip3( Cont<S> const& xs, Cont<T> const& ys, Cont<U> const& zs ) -> Cont<Tup<S,T,U>>
  {
    Cont<Tup<S,T,U>> out{};

    Size_t min = minimum( Cont<Size_t>{ xs.size(), ys.size(), zs.size() } ).value();
    out.reserve( min );

    auto x = begin( xs );
    auto y = begin( ys );
    auto z = begin( zs );

    while ( x < end( xs ) && y < end( ys ) && z < end( zs ) )
    {
      out.push_back( Tup<S,T,U>{ *x, *y, *z } );
      advance( x, 1 );
      advance( y, 1 );
      advance( z, 1 );
    }

    return out;
  }

  // zipWith :: ( S -> T -> U ) -> [S] -> [T] -> [U]
  template <typename U, typename S, typename T, template <typename> typename Cont, typename F>
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

  // zipWith3 :: ( S -> T -> U -> V ) -> [S] -> [T] -> [U] -> [V]
  template <typename V, typename U, typename S, typename T, template <typename> typename Cont, typename F>
  auto zipWith3( F func, Cont<S> const& xs, Cont<T> const& ys, Cont<U> const& zs ) -> Cont<V>
  {
    Cont<V> out{};

    Size_t min = minimum( Cont<Size_t>{ xs.size(), ys.size(), zs.size() } ).value();
    out.reserve( min );

    auto x = begin( xs );
    auto y = begin( ys );
    auto z = begin( zs );

    while ( x < end( xs ) && y < end( ys ) && z < end( zs ) )
    {
      out.push_back( func( *x, *y, *z ) );
      advance( x, 1 );
      advance( y, 1 );
      advance( z, 1 );
    }

    return out;
  }

  // unzip :: [(S,T)] -> ([S],[T])
  template <typename S, typename T, template <typename> typename Cont>
  auto unzip( Cont<Tup<S,T>> const& xs )
  {
    Cont<S> ss;
    Cont<T> ts;
    ss.reserve( xs.size() );
    ts.reserve( xs.size() );

    for ( auto const& x : xs )
    {
      ss.push_back( std::get<0>( x ) );
      ts.push_back( std::get<1>( x ) );
    }

    return Tup<Vec<S>,Vec<T>>{ ss, ts };
  }

  // unzip3 :: [(S,T)] -> ([S],[T])
  template <typename S, typename T, typename U, template <typename> typename Cont>
  auto unzip3( Cont<Tup<S,T,U>> const& xs )
  {
    Cont<S> ss;
    Cont<T> ts;
    Cont<U> us;
    ss.reserve( xs.size() );
    ts.reserve( xs.size() );
    us.reserve( xs.size() );

    for ( auto const& x : xs )
    {
      ss.push_back( std::get<0>( x ) );
      ts.push_back( std::get<1>( x ) );
      us.push_back( std::get<2>( x ) );
    }

    return Tup<Vec<S>,Vec<T>,Vec<U>>{ ss, ts, us };
  }

  // foldl :: (T -> S -> T) -> T -> [S] -> T
  template <typename S, typename T, template <typename> typename Cont, typename F>
  auto foldl( F func, T const& y, Cont<S> const& xs ) -> T
  {
    T out = y;

    for ( auto const& x : xs )
      out = func( out, x );

    return out;
  }

  // scanl :: (T -> S -> T) -> T -> [S] -> T
  template <typename S, typename T, template <typename> typename Cont, typename F>
  auto scanl( F func, T const& y, Cont<S> const& xs ) -> Cont<T>
  {
    Cont<T> out{};
    out.reserve( xs.size() );

    T init = y;
    out.push_back( init );

    for ( auto const& x : xs )
    {
      init = func( init, x );
      out.push_back( init );
    }

    return out;
  }

  // ceiling :: Num -> Int
  template <typename Num>
  auto ceiling( Num const& x ) -> Int
  {
    return std::ceil( x );
  }

  // floor :: Num -> Int
  template <typename Num>
  auto floor( Num const& x ) -> Int
  {
    return std::floor( x );
  }

  // round :: Num -> Int
  template <typename Num>
  auto round( Num const& x ) -> Int
  {
    return std::round( x );
  }

  // lookup :: S -> [(S,T)] -> Opt<T>
  template <typename S, typename T, template <typename> typename Cont>
  auto lookup( S const& needle, Cont<Tup<S,T>> const& xs ) -> Opt<T>
  {
    for ( auto const& x : xs )
      if ( needle == std::get<0>( x ) )
        return Opt<T>{ std::get<1>( x ) };

    return Opt<T>{};
  }
}

#endif
