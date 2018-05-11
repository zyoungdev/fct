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

#ifndef functional_algorithms_transition_header
#define functional_algorithms_transition_header

#include "using.h"

namespace fct
{
  // operator+ :: [T] -> [T] -> [T]
  template <typename T, template <typename> typename Cont>
    auto operator+( Cont<T> const& x, Cont<T> const& y ) -> Cont<T>
    {
      Cont<T> out{};

      out.insert( end(out), begin( x ), end( x ) );
      out.insert( end(out), begin( y ), end( y ) );

      return out;
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
}

#endif
