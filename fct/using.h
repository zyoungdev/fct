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

#ifndef functional_algorithms_using_header
#define functional_algorithms_using_header

namespace fct
{
  using String = std::vector<char>;
  using StdString = std::string;
  using SS = std::stringstream;
  using Bool = bool;
  using Float = float;
  using Double = long double;
  using Int = int;
  using UInt = unsigned int;
  using Char = char;
  using Long = long long;
  using ULong = unsigned long long;
  using Size_t = std::size_t;

  template <typename T>
  using Opt = std::optional<T>;

  template <typename T>
  using Vec = std::vector<T>;

  // template <typename S, typename T>
  template <typename ...Ts>
  using Tup = std::tuple<Ts...>;

  using std::begin;
  using std::end;
  using std::rbegin;
  using std::rend;
  using std::advance;
  using std::next;
}

#endif
