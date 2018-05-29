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
}

#endif
