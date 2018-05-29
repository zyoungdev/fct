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

  // fromMaybe :: T -> Opt<T> -> T
  template <typename T>
  auto fromMaybe( T const& def, Opt<T> const& x )
  {
    return x.value_or( def );
  }

  // listToMaybe :: [T] -> Opt<T>
  template <typename T, template <typename> typename Cont>
  auto listToMaybe( Cont<T> const& xs ) -> Opt<T>
  {
    return xs.empty() ? Opt<T>{} : *( begin( xs ) );
  }

  // maybeToList :: Opt<T> -> [T]
  template <template <typename> typename Cont, typename T>
  auto maybeToList( Opt<T> const& x ) -> Cont<T>
  {
    return x.has_value() ? Cont<T>{ x.value() } : Cont<T>{};
  }

  // catMaybes :: [Opt<T>] -> [T]
  template <typename T, template <typename> typename Cont>
  auto catMaybes( Cont<Opt<T>> const& xs ) -> Cont<T>
  {
    Cont<T> out{};

    for ( auto const& x : xs )
      if ( x.has_value() )
        out.push_back( x.value() );

    return out;
  }
}

#endif
