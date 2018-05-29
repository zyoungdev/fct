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

#ifndef functional_algorithms_data_maybe_header
#define functional_algorithms_data_maybe_header

#include "fct/internal/include.h"
#include "fct/internal/using.h"

namespace fct
{
  // maybe :: T -> ( S -> T ) -> Opt<S> -> T
  template <typename T, typename S, typename F>
  auto maybe( T const& def, F func, Opt<S> const& x ) -> T
  {
    return x.has_value() ? func( x.value() ) : def;
  }

  // isJust :: Opt<T> -> Bool
  template <typename T>
  auto isJust( Opt<T> const& x ) -> Bool
  {
    return x.has_value();
  }

  // isNothing :: Opt<T> -> Bool
  template <typename T>
  auto isNothing( Opt<T> const& x ) -> Bool
  {
    return ! x.has_value();
  }
}

#endif