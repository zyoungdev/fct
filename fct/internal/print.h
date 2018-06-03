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
#include "fct/internal/transition.h"
#include "fct/internal/show.h"

namespace fct
{
  // print :: T -> void
  template <typename T>
  auto print( T const& val, Char lastChar = '\n' ) -> void
  {
    std::cout << toStdStr( show( val ) ) << lastChar;
  }
}

#endif
