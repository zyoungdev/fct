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

#ifndef functional_algorithms_show_header
#define functional_algorithms_show_header

#include "fct/internal/include.h"
#include "fct/internal/using.h"

namespace fct
{
  // show :: T -> String
  template <typename T>
  auto show( T const& x ) -> String
  {
    return toStr( std::to_string( x ) );
  }

  // show :: Char -> String
  auto show( Char const& x ) -> String
  {
    return String{ x, 1 };
  }

  // show :: Char* -> String
  auto show( char const* x ) -> String
  {
    return String{ x, x + std::strlen( x ) };
  }

  // show :: Bool -> String
  auto show( Bool const& x ) -> String
  {
    return x ? "True"_s : "False"_s;
  }

  // show :: [Char] -> String
  auto show( String const& xs ) -> String
  {
    return xs;
  }

  // show :: Opt<T> -> String
  template <typename T>
  auto show( Opt<T> const& val ) -> String
  {
    String out;
    if ( val )
    {
      out = "Just "_s;
      String v = show( val.value() );
      out.insert( end( out ), begin( v ), end( v ) );
    }
    else
    {
      out = "Nothing"_s;
    }

    return out;
  }

  template<class ...Ts, std::size_t... Is>
  auto show_tuple( Tup<Ts...> const& tup, std::index_sequence<Is...> ) -> String
  {
    return ( ( show( std::get<Is>( tup ) ) + String{ ',' } ) + ... );
  }

  // show :: (Ts...) -> String
  template <typename ...Ts>
  auto show( Tup<Ts...> const& val ) -> String
  {
    String out{};
    out.push_back( '(' );
    auto v = show_tuple( val, std::index_sequence_for<Ts...>{} );
    out.insert( end( out ), begin( v ), end( v ) - 1 );
    out.push_back( ')' );

    return out;
  }

  // show :: [T] -> String
  template <typename T, template <typename> typename Cont>
  auto show( Cont<T> const& xs ) -> String
  {
    if ( xs.empty() )
    {
      return "[]"_s;
    }

    String out{};
    out.push_back( '[' );

    auto x = begin( xs );
    for ( ; x < end( xs ); advance( x, 1 ) )
    {
      auto v = show( *x );
      out.insert( end( out ),  begin( v ), end( v ) );

      if ( x == end( xs ) - 1 )
        out.push_back( ']' );
      else
        out.push_back( ',' );
    }

    return out;
  }
}

#endif
