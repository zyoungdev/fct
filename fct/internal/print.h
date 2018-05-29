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

#ifndef functional_algorithms_print_header
#define functional_algorithms_print_header

#include "fct/internal/include.h"
#include "fct/internal/using.h"
#include "fct/internal/show.h"

namespace fct
{
  // print :: T -> void
  template <typename T>
  auto print( T const& val, Char lastChar = '\n' ) -> void
  {
    std::cout << show( val ) << lastChar;
  }

  // print :: [Char] -> void
  auto print( String const& xs, Char lastChar = '\n' ) -> void
  {
    auto str = StdString{ begin( xs ), end( xs ) };
    std::cout << str << lastChar;
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
}

#endif
