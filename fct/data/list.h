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

#ifndef functional_algorithms_data_list_header
#define functional_algorithms_data_list_header

#include "fct/internal/include.h"
#include "fct/internal/using.h"

namespace fct
{
  // transpose :: [[T]] -> [[T]]
  template <typename T, template <typename> typename Cont>
  constexpr auto transpose( Cont<Cont<T>> const& xxs ) -> Cont<Cont<T>>
  {
    Cont<Cont<T>> out{};

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

  // subsequences :: [T] -> [[T]]
  template <typename T, template <typename> typename Cont>
  constexpr auto subsequences( Cont<T> const& xs ) -> Cont<Cont<T>>
  {
    Cont<Cont<T>> out{};
    out.reserve( std::pow( 2, xs.size() ) );

    // Add the empty set
    out.push_back( Cont<T>{} );

    for ( auto const& x : xs )
    {
      // Create copy of current subsets
      Cont<Cont<T>> new_subsets{ begin( out ), end( out ) };

      // Add element to every new subset
      for ( Cont<T>& s : new_subsets )
        s.push_back( x );

      // Add new subsets to output
      out.insert( end( out ), begin( new_subsets ), end( new_subsets ) );
    }

    return out;
  }

  // intersect :: [T] -> [T] -> [T]
  template <typename T, template <typename> typename Cont>
  constexpr auto intersect( Cont<T> const& xs, Cont<T> const& ys ) -> Cont<T>
  {
    Cont<T> out{};
    auto const& smaller = xs.size() <= ys.size() ? xs : ys;
    auto const& larger = xs.size() > ys.size() ? xs : ys;

    for ( auto const& s : smaller )
      if ( elem( s, larger ) )
        out.push_back( s );

    return out;
  }

  // union :: [T] -> [T] -> [T]
  template <typename T, template <typename> typename Cont>
  constexpr auto union_of( Cont<T> const& xs, Cont<T> const& ys ) -> Cont<T>
  {
    Cont<T> out{};
    Cont<T> const* smaller = xs.size() <= ys.size() ? &xs : &ys;
    Cont<T> const* larger = xs.size() > ys.size() ? &xs : &ys;

    for ( auto const& s : *smaller )
      if ( notElem( s, *larger ) )
        out.push_back( s );

    for ( auto const& l : *larger )
      out.push_back( l );

    return out;
  }

  // intersperse :: T -> [T] -> [T]
  template <typename T, template <typename> typename Cont>
  constexpr auto intersperse( T const& y, Cont<T> const& xs ) -> Cont<T>
  {
    if ( xs.empty() )
      return Cont<T>{};

    Cont<T> out{};

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
  template <typename T, template <typename> typename Cont>
  constexpr auto intercalate( Cont<T> const& xs, Cont<Cont<T>> const& xxs ) -> Cont<T>
  {
    return concat( intersperse( xs, xxs ) );
  }

  // permutations :: [T] -> [[T]]
  template <typename T, template <typename> typename Cont>
  constexpr auto permutations( Cont<T> const& xs ) -> Cont<Cont<T>>
  {
    Cont<Cont<T>> out{};
    Cont<T> mut_xs = xs;

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

  // group :: [T] -> [[T]]
  template <typename T, template <typename> typename Cont>
  constexpr auto group( Cont<T> const& xs ) -> Cont<Cont<T>>
  {
    if ( xs.empty() )
      return Cont<Cont<T>>{};

    Cont<Cont<T>> out{};

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
        out.push_back( Cont<T>{ a, b } );
        a = b;
      }
    }
    out.push_back( Cont<T>{ a, b } );

    return out;
  }

  // inits :: [T] -> [[T]]
  template <typename T, template <typename> typename Cont>
  constexpr auto inits( Cont<T> const& xs ) -> Cont<Cont<T>>
  {
    Cont<Cont<T>> out{};

    auto i = begin( xs );

    for ( ; i < end( xs ); advance( i, 1 ) )
      out.push_back( Cont<T>{ begin( xs ), i } );
    out.push_back( Cont<T>{ begin( xs ), i } );

    return out;
  }

  // tails :: [T] -> [[T]]
  template <typename T, template <typename> typename Cont>
  constexpr auto tails( Cont<T> const& xs ) -> Cont<Cont<T>>
  {
    Cont<Cont<T>> out{};

    auto a = begin( xs );

    for ( ; a < end( xs ); advance( a, 1 ) )
      out.push_back( Cont<T>{ a, end( xs ) } );
    out.push_back( Cont<T>{} );

    return out;
  }

  // isPrefixOf :: [T] -> [T] -> Bool
  template <typename T, template <typename> typename Cont>
  constexpr auto isPrefixOf( Cont<T> const& xs, Cont<T> const& ys ) -> Bool
  {
    auto ys_inits = inits( ys );
    return elem( xs, ys_inits );
  }

  // isSuffixOf :: [T] -> [T] -> Bool
  template <typename T, template <typename> typename Cont>
  constexpr auto isSuffixOf( Cont<T> const& xs, Cont<T> const& ys ) -> Bool
  {
    auto ys_tails = tails( ys );
    return elem( xs, ys_tails );
  }

  // isInfixOf :: [T] -> [T] -> Bool
  template <typename T, template <typename> typename Cont>
  constexpr auto isInfixOf( Cont<T> const& xs, Cont<T> const& ys ) -> Bool
  {
    if ( xs.empty() )
      return true;

    auto a = begin( ys );
    auto b = begin( ys ) + xs.size();

    Cont<T> test{ begin( xs ), end( xs ) };

    for ( ; b < end( ys ); advance( a, 1 ), advance( b, 1 ) )
      if ( test == Cont<T>{ a, b } )
        return true;

    return false;
  }

  // partition :: ( T -> Bool ) -> [T] -> ( [T], [T] )
  template <typename T, typename F, template <typename> typename Cont>
  constexpr auto partition( F predicate, Cont<T> const& xs ) -> Tup<Cont<T>, Cont<T>>
  {
    Cont<T> left{};
    Cont<T> right{};

    for ( auto const& x : xs )
      if ( predicate( x ) )
        left.push_back( x );
      else
        right.push_back( x );

    return std::make_tuple( left, right );
  }

  // nub :: [T] -> [T]
  template <typename T, template <typename> typename Cont>
  constexpr auto nub( Cont<T> const& xs ) -> Cont<T>
  {
    Cont<T> out{};

    for ( auto const& x : xs )
      if ( ! elem( x, out ) )
        out.push_back( x );

    return out;
  }

  // sort :: [T] -> [T]
  template <typename T, template <typename> typename Cont>
  constexpr auto sort( Cont<T> const& xs ) -> Cont<T>
  {
    Cont<T> out{ begin( xs ), end( xs ) };
    std::sort( begin( out ), end( out ) );
    return out;
  }
}

#endif
