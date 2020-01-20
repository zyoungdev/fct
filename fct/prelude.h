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

#include "fct/internal/include.h"
#include "fct/internal/using.h"
#include "fct/internal/composition.h"
#include "fct/internal/transition.h"
#include "fct/internal/show.h"
#include "fct/internal/print.h"

namespace fct
{
  constexpr Double pi = 3.141592653589793238462643383279502884;
  constexpr Double e  = 2.718281828459045235360287471352662497;

  // toUpper :: Char -> Char
  constexpr auto toUpper( Char const& x ) -> Char
  {
    return x > 0x60 && x < 0x7B ? x - 0x20 : x;
  }

  // toLower :: Char -> Char
  constexpr auto toLower( Char const& x ) -> Char
  {
    return x > 0x40 && x < 0x5B ? x + 0x20 : x;
  }

  // fmap :: ( S -> T ) -> [S] -> [T]
  template <typename T, typename S, template <typename> typename Cont, typename F>
  constexpr auto fmap( F fct, Cont<S> const& xs ) -> Cont<T>
  {
    Cont<T> out{};
    out.reserve( xs.size() );

    for ( auto const& x : xs )
      out.push_back( fct( x ) );

    return out;
  }

  // fmap :: ( Char -> Char ) -> StdString -> StdString 
  template <typename F>
  constexpr auto fmap( F fct, StdString const& xs ) -> StdString
  {
    StdString out{};
    out.reserve( xs.size() );

    for ( auto const& x : xs )
      out.push_back( fct( x ) );

    return out;
  }

  // filter :: ( T -> Bool ) -> [T]
  template <typename T, template <typename> typename Cont, typename F>
  constexpr auto filter( F predicate, Cont<T> const& xs ) -> Cont<T>
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
  constexpr auto takeWhile( F predicate, Cont<T> const& xs ) -> Cont<T>
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
  constexpr auto dropWhile( F predicate, Cont<T> const& xs ) -> Cont<T>
  {
    Int i = 0;
    for ( auto const& x : xs )
      if ( predicate( x ) )
        i++;
      else
        break;

    return Cont<T>{ begin( xs ) + i, end( xs ) };
  }

  // head :: [T] -> T
  template <typename T, template <typename> typename Cont>
  constexpr auto head( Cont<T> const& xs ) -> T
  {
    return *( begin( xs ) );
  }

  // tail :: [T] -> [T]
  template <typename T, template <typename> typename Cont>
  constexpr auto tail( Cont<T> const& xs ) -> Cont<T>
  {
    return Cont<T>{ begin( xs ) + 1, end( xs ) };
  }

  // init :: [T] -> [T]
  template <typename T, template <typename> typename Cont>
  constexpr auto init( Cont<T> const& xs ) -> Cont<T>
  {
    return Cont<T>{ begin( xs ), end( xs ) - 1 };
  }

  // last :: [T] -> T
  template <typename T, template <typename> typename Cont>
  constexpr auto last( Cont<T> const& xs ) -> T
  {
    return *( end( xs ) - 1 );
  }

  // fst :: (S,T) -> S
  template <typename S, typename T>
  constexpr auto fst( Tup<S,T> const& tup )
  {
    return std::get<0>( tup );
  }

  // snd :: (S,T) -> T
  template <typename S, typename T>
  constexpr auto snd( Tup<S,T> const& tup )
  {
    return std::get<1>( tup );
  }

  // odd :: Int -> Bool
  constexpr auto odd( Int const& val ) -> Bool
  {
    return val & 1;
  }

  // even :: Int -> Bool
  constexpr auto even( Int const& val ) -> Bool
  {
    return ! odd( val );
  }

  // negate :: Num -> Num
  template <typename Num>
  constexpr auto negate( Num const& x ) -> Num
  {
    return -x;
  }

  // abs :: Num -> Num
  template <typename Num>
  constexpr auto abs( Num const& x ) -> Num
  {
    return x < 0 ? -x : x;
  }

  // signum :: Num -> Int
  template <typename Num>
  constexpr auto signum( Num const& x ) -> Int
  {
    if ( x < 0 )
      return -1;
    else if ( x > 0 )
      return 1;

    return 0;
  }

  // quotRem :: T -> T -> ( T, T )
  template <typename T>
  constexpr auto quotRem( T const& x, T const& y ) -> Tup<T, T>
  {
    T q = x / y;
    T r = x % y;

    return std::make_tuple( q, r );
  }

  // exp :: Num -> Double
  template <typename Num>
  constexpr auto exp( Num const& x ) -> Double
  {
    return std::pow( e, x );
  }

  // log :: Num -> Double
  template <typename Num>
  constexpr auto log( Num const& x ) -> Double
  {
    return std::log( x );
  }

  // logBase :: Num -> Num -> Double
  template <typename Num>
  constexpr auto logBase( Num const& base, Num const& x ) -> Double
  {
    return std::log( x ) / std::log( base );
  }

  // sqrt :: Num -> Double
  template <typename Num>
  constexpr auto sqrt( Num const& x ) -> Double
  {
    return std::sqrt( x );
  }

  // gcd :: Num -> Num -> Num
  template <typename Num>
  constexpr auto gcd( Num const& x, Num const& y ) -> Num
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
  constexpr auto lcm( Num const& x, Num const& y ) -> Num
  {
    Num end = x <= y ? x : y;

    for ( Num i = 2 ; i <= end; i++ )
      if ( x % i == 0 && y % i == 0 )
        return i;

    return 1;
  }

  // elem :: T -> [b] -> Bool
  template <typename T, template <typename> typename Cont>
  constexpr auto elem( T const& el, Cont<T> const& xs ) -> Bool
  {
    return any( [&el]( auto const& x ){ return el == x; }, xs );
  }

  // notElem :: T -> [T] -> Bool
  template <typename T, template <typename> typename Cont>
  constexpr auto notElem( T const& el, Cont<T> const& xs ) -> Bool
  {
    return ! elem( el, xs );
  }

  // max :: T -> T -> T
  template <typename T>
  constexpr auto max( T const& x, T const& y ) -> T
  {
    return x >= y ? x : y;
  }

  // min :: T -> T -> T
  template <typename T>
  constexpr auto min( T const& x, T const& y ) -> T
  {
    return x <= y ? x : y;
  }

  // maximum :: [T] -> T
  template <typename T, template <typename> typename Cont>
  constexpr auto maximum( Cont<T> const& xs ) -> T
  {
    auto a = begin( xs );
    auto b = end( xs );
    auto it = a + 1;

    for ( ; it < b ; advance( it, 1 ) )
    {
      if ( *it > *a )
        a = it;
    }

    return *a;
  }

  // minimum :: [T] -> T
  template <typename T, template <typename> typename Cont>
  constexpr auto minimum( Cont<T> const& xs ) -> T
  {
    auto a = begin( xs );
    auto b = end( xs );
    auto it = a + 1;

    for ( ; it < b ; advance( it, 1 ) )
    {
      if ( *it < *a )
        a = it;
    }

    return *a;
  }

  // sum :: [Num] -> Num
  template <typename Num, template <typename> typename Cont>
  constexpr auto sum( Cont<Num> const& xs ) -> Num
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
  constexpr auto product( Cont<Num> const& xs ) -> Num
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
  constexpr auto id( T const& x ) -> T
  {
    return x;
  }

  // constant :: S -> T -> S
  template <typename S, typename T>
  constexpr auto constant( S const& x, [[maybe_unused]] T const& y ) -> S
  {
    return x;
  }

  // flip :: ( S -> T -> U ) -> T -> S -> U
  template <typename U, typename S, typename T, typename F>
  constexpr auto flip( F func, S const& x, T const& y ) -> U
  {
    return func( y, x );
  }

  // until :: ( T -> Bool ) -> ( T -> T ) -> T -> T
  template <typename T, typename P, typename F>
  constexpr auto until( P predicate, F func, T const& x ) -> T
  {
    T out = x;
    while ( ! predicate( out ) )
      out = func( out );

    return out;
  }

  // null :: [T] -> Bool
  template <typename T, template <typename> typename Cont>
  constexpr auto null( Cont<T> const& xs ) -> Bool
  {
    return xs.empty();
  }

  // length :: [T] -> Size_t
  template <typename S, template <typename> typename Cont>
  constexpr auto length( Cont<S> const& xs ) -> size_t
  {
    return xs.size();
  }

  // reverse :: [T] -> [T]
  template <typename T, template <typename> typename Cont>
  constexpr auto reverse( Cont<T> const& xs ) -> Cont<T>
  {
    return Cont<T>{ rbegin( xs ), rend( xs ) };
  }

  // Haskell and
  // conjunction :: [T] -> Bool
  template <typename T, template <typename> typename Cont>
  constexpr auto conjunction( Cont<T> const& xs ) -> Bool
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
  constexpr auto disjunction( Cont<T> const& xs ) -> Bool
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
  constexpr auto any( F predicate, Cont<T> const& xs ) -> Bool
  {
    return std::any_of( begin( xs ), end( xs ), predicate );
  }

  // all :: ( T -> Bool ) -> [T] -> Bool
  template <typename T, template <typename> typename Cont, typename F>
  constexpr auto all( F predicate, Cont<T> const& xs ) -> Bool
  {
    return std::all_of( begin( xs ), end( xs ), predicate );
  }

  // concat :: [[T]] -> [T]
  template <typename T, template <typename> typename Cont>
  constexpr auto concat( Cont<Cont<T>> const& xxs ) -> Cont<T>
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
  constexpr auto replicate( UInt num, T const& val ) -> Vec<T>
  {
    return Vec<T>( num, val );
  }

  // take :: UInt -> [T] -> [T]
  template <typename T, template <typename> typename Cont>
  constexpr auto take( UInt num, Cont<T> const& xs ) -> Cont<T>
  {
    if ( xs.empty() )
      return Cont<T>{};
    return Cont<T>{ begin( xs ), begin( xs ) + num };
  }

  // drop :: UInt -> [T] -> [T]
  template <typename T, template <typename> typename Cont>
  constexpr auto drop( UInt num, Cont<T> const& xs ) -> Cont<T>
  {
    if ( xs.empty() )
      return Cont<T>{};
    return Cont<T>{ begin( xs ) + num, end( xs ) };
  }

  // splitAt :: UInt -> [T] -> ( [T], [T] )
  template <typename T, template <typename> typename Cont>
  constexpr auto splitAt( UInt index, Cont<T> const& xs ) -> Tup<Cont<T>, Cont<T>>
  {
    if ( index >= xs.size() )
      return std::make_tuple( Cont<T>{ begin( xs ), end( xs ) }, Cont<T>{} );

    Cont<T> left{ begin( xs ), begin( xs ) + index };
    Cont<T> right{ begin( xs ) + index, end( xs ) };

    return std::make_tuple( left, right );
  }

  // lines :: String -> [String]
  template <typename T, template <typename> typename Cont>
  // auto lines( String const& str ) -> Vec<String>
  constexpr auto lines( Cont<T> const& str ) -> Cont<Cont<T>>
  {
    Cont<Cont<T>> out{};

    auto a = begin( str );
    auto b = end( str );
    auto it = a;

    for ( ; it != b ; advance( it, 1 ) )
    {
      if ( *it == '\n' )
      {
        out.push_back( Cont<T>{ a, it } );
        a = it + 1;
      }
    }

    auto last = Cont<T>{ a, b };
    if ( ! last.empty() )
      out.push_back( Cont<T>{ a, b } );

    return out;
  }

  // words :: String -> [String]
  template <typename T, template <typename> typename Cont>
  constexpr auto words( Cont<T> const& xs ) -> Cont<Cont<T>>
  {
    Cont<Cont<T>> out{};

    auto a = begin( xs );
    auto b = end( xs );
    auto it = a;

    for ( ; it != b ; )
    {
      if ( *it == ' ' )
      {
        out.push_back( Cont<T>{ a, it } );

        while ( *it == ' ' )
          it++;

        a = it;

      }

      if ( it != b )
        advance( it, 1 );
    }

    if ( a == b )
      return out;

    auto last = Cont<T>{ a, b };
    if ( ! last.empty() )
      out.push_back( Cont<T>{ a, b } );

    return out;
  }

  // unlines :: [String] -> String
  template <template <typename> typename Cont>
  constexpr auto unlines( Cont<String> const& xs ) -> String
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
  constexpr auto unwords( Cont<String> const& xs ) -> String
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

  // read :: String -> T
  template <typename T>
  auto read( String const& xs ) -> T
  {
    StrStream ss{ toStdStr( xs ) };

    T out;
    ss >> out;

    if ( ! ss )
      throw std::runtime_error( "Prelude.read: no parse" );

    return out;
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
  constexpr auto iterate( UInt num, F func, T const& x ) -> Vec<T>
  {
    Vec<T> out{};
    out.reserve( num );

    for ( uint i = 0; i < num; i++ )
      out.push_back( func( x ) );

    return out;
  }

  // span :: (T -> Bool) -> [T] -> ([T], [T])
  template <typename T, template <typename> typename Cont, typename F>
  constexpr auto span( F predicate, Cont<T> const& xs ) -> Tup<Cont<T>, Cont<T>>
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
  constexpr auto break_when( F predicate, Cont<T> const& xs ) -> Tup<Cont<T>, Cont<T>>
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
  constexpr auto zip( Cont<S> const& xs, Cont<T> const& ys ) -> Cont<Tup<S,T>>
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
  constexpr auto zip3( Cont<S> const& xs, Cont<T> const& ys, Cont<U> const& zs ) -> Cont<Tup<S,T,U>>
  {
    Cont<Tup<S,T,U>> out{};

    Size_t min = minimum( Cont<Size_t>{ xs.size(), ys.size(), zs.size() } );
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
  constexpr auto zipWith( F func, Cont<S> const& xs, Cont<T> const& ys ) -> Cont<U>
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
  constexpr auto zipWith3( F func, Cont<S> const& xs, Cont<T> const& ys, Cont<U> const& zs ) -> Cont<V>
  {
    Cont<V> out{};

    Size_t min = minimum( Cont<Size_t>{ xs.size(), ys.size(), zs.size() } );
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
  constexpr auto unzip( Cont<Tup<S,T>> const& xs )
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
  constexpr auto unzip3( Cont<Tup<S,T,U>> const& xs )
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
  constexpr auto foldl( F func, T const& y, Cont<S> const& xs ) -> T
  {
    T out = y;

    for ( auto const& x : xs )
      out = func( out, x );

    return out;
  }

  // scanl :: (T -> S -> T) -> T -> [S] -> T
  template <typename S, typename T, template <typename> typename Cont, typename F>
  constexpr auto scanl( F func, T const& y, Cont<S> const& xs ) -> Cont<T>
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
  constexpr auto ceiling( Num const& x ) -> Int
  {
    return std::ceil( x );
  }

  // floor :: Num -> Int
  template <typename Num>
  constexpr auto floor( Num const& x ) -> Int
  {
    return std::floor( x );
  }

  // round :: Num -> Int
  template <typename Num>
  constexpr auto round( Num const& x ) -> Int
  {
    return std::round( x );
  }

  // lookup :: S -> [(S,T)] -> Opt<T>
  template <typename S, typename T, template <typename> typename Cont>
  constexpr auto lookup( S const& needle, Cont<Tup<S,T>> const& xs ) -> Opt<T>
  {
    for ( auto const& x : xs )
      if ( needle == std::get<0>( x ) )
        return Opt<T>{ std::get<1>( x ) };

    return Opt<T>{};
  }

  // mapM_ :: ( S -> void ) -> [S] -> void
  template <typename S, typename F, template <typename> typename Cont>
  constexpr auto mapM_( F func, Cont<S> const& xs ) -> void
  {
    for ( auto const& x : xs )
      func( x );
  }
}

#endif
