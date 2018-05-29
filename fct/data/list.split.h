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

#ifndef functional_algorithms_data_list_split_header
#define functional_algorithms_data_list_split_header

#include "fct/internal/include.h"
#include "fct/internal/using.h"

namespace fct
{
  // splitOn :: [T] -> [T] -> [[T]]
  template <typename T, template <typename> typename Cont>
  auto splitOn( Cont<T> const& needle, Cont<T> const& haystack ) -> Cont<Cont<T>>
  {
    Cont<Cont<T>> out{};

    auto a = begin( haystack );
    auto b = end( haystack );
    auto c = begin( needle );
    auto d = end( needle );

    auto it = search( a, b, c, d );
    while ( it != b )
    {
      out.push_back( Cont<T>{ a, it } );

      a = it + needle.size();
      it = search( a, b, c, d );
    }
    out.push_back( Cont<T>{ a, it } );

    return out;
  }

  // splitOneOf :: [T] -> [T] -> [[T]]
  template <typename T, template <typename> typename Cont>
  auto splitOneOf( Cont<T> const& needles, Cont<T> const& haystack ) -> Cont<Cont<T>>
  {
    Cont<Cont<T>> out{};

    auto a = begin( haystack );
    auto it = a;
    auto b = end( haystack );

    for ( ; it != b; advance( it, 1 ) )
    {
      auto pred = [&it]( auto const& x ){ return *it == x; };
      if ( std::any_of( begin( needles ), end( needles ), pred ) )
      {
        out.push_back( Cont<T>{ a, it } );
        a = it + 1;
      }
    }
    out.push_back( Cont<T>{ a, b } );

    return out;
  }

  // splitWhen :: ( T -> Bool ) -> [T] -> [[T]]
  template <typename T, typename F, template <typename> typename Cont>
  auto splitWhen( F pred, Cont<T> const& xs ) -> Cont<Cont<T>>
  {
    Cont<Cont<T>> out{};

    auto a = begin( xs );
    auto b = end( xs );
    auto it = a;

    for ( ; it != b; advance( it, 1 ) )
    {
      if ( pred( *it ) )
      {
        out.push_back( Cont<T>{ a, it } );
        a = it + 1;
      }
    }
    out.push_back( Cont<T>{ a, b } );

    return out;
  }

  // endBy :: [T] -> [T] -> [[T]]
  template <typename T, template <typename> typename Cont>
  auto endBy( Cont<T> const& needle, Cont<T> const& haystack ) -> Cont<Cont<T>>
  {
    Cont<Cont<T>> out{};

    auto a = begin( haystack );
    auto b = end( haystack );
    auto c = begin( needle );
    auto d = end( needle );

    auto it = search( a, b, c, d );
    while ( it != b )
    {
      out.push_back( Cont<T>{ a, it } );

      a = it + needle.size();
      it = search( a, b, c, d );
    }

    auto last = Cont<T>{ a, it };
    if ( ! last.empty() )
      out.push_back( last );

    return out;
  }

  // endByOneOf :: [T] -> [T] -> [[T]]
  template <typename T, template <typename> typename Cont>
  auto endByOneOf( Cont<T> const& needles, Cont<T> const& haystack ) -> Cont<Cont<T>>
  {
    Cont<Cont<T>> out{};

    auto a = begin( haystack );
    auto it = a;
    auto b = end( haystack );

    for ( ; it != b; advance( it, 1 ) )
    {
      auto pred = [&it]( auto const& x ){ return *it == x; };
      if ( std::any_of( begin( needles ), end( needles ), pred ) )
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

  // wordsBy :: ( T -> Bool ) -> [T] -> [[T]]
  template <typename T, typename F, template <typename> typename Cont>
  auto wordsBy( F pred, Cont<T> const& xs ) -> Cont<Cont<T>>
  {
    Cont<Cont<T>> out{};

    auto a = begin( xs );
    auto b = end( xs );
    auto it = a;

    for ( ; it != b; advance( it, 1 ) )
    {
      if ( pred( *it ) )
      {
        auto word = Cont<T>{ a, it };
        if ( ! word.empty() )
          out.push_back( word );

        a = it + 1;
      }
    }

    auto word = Cont<T>{ a, it };
    if ( ! word.empty() )
      out.push_back( Cont<T>{ a, b } );

    return out;
  }

  // linesBy :: ( T -> Bool ) -> [T] -> [[T]]
  template <typename T, typename F, template <typename> typename Cont>
  auto linesBy( F pred, Cont<T> const& xs ) -> Cont<Cont<T>>
  {
    Cont<Cont<T>> out{};

    auto a = begin( xs );
    auto b = end( xs );
    auto it = a;

    for ( ; it != b; advance( it, 1 ) )
    {
      if ( pred( *it ) )
      {
        out.push_back( Cont<T>{ a, it } );
        a = it + 1;
      }
    }

    auto word = Cont<T>{ a, it };
    if ( ! word.empty() )
      out.push_back( Cont<T>{ a, b } );

    return out;
  }

  // chunksOf :: UInt -> [T] -> [[T]]
  template <typename T, template <typename> typename Cont>
  auto chunksOf( UInt n, Cont<T> const& xs ) -> Cont<Cont<T>>
  {
    Cont<Cont<T>> out{};

    auto a = begin( xs );
    auto b = end( xs );
    auto it = a + n;

    for ( ; it < b ;  )
    {
      out.push_back( Cont<T>{ a, it } );
      a = it;
      it = a + n;
    }
    out.push_back( Cont<T>{ a, b } );

    return out;
  }

  // splitPlaces:: [UInt] -> [T] -> [[T]]
  template <typename T, template <typename> typename Cont>
  auto splitPlaces( Cont<UInt> const& ns, Cont<T> const& xs ) -> Cont<Cont<T>>
  {
    Cont<Cont<T>> out{};

    auto a = begin( xs );
    auto b = end( xs );

    for ( auto const& n : ns )
    {
      auto it = a + n;

      if ( it < b )
        out.push_back( Cont<T>{ a, it } );
      else
      {
        out.push_back( Cont<T>{ a, b } );
        break;
      }

      a = it;
    }

    return out;
  }

  // splitPlacesBlanks :: [UInt] -> [T] -> [[T]]
  template <typename T, template <typename> typename Cont>
  auto splitPlacesBlanks( Cont<UInt> const& ns, Cont<T> const& xs ) -> Cont<Cont<T>>
  {
    Cont<Cont<T>> out{};

    auto a = begin( xs );
    auto b = end( xs );

    for ( auto const& n : ns )
    {
      if ( a > b )
      {
        out.push_back( Cont<T>{} );
        continue;
      }

      auto it = a + n;
      if ( it < b )
      {
        out.push_back( Cont<T>{ a, it } );
      }
      else
        out.push_back( Cont<T>{ a, b } );

      a = it;
    }

    return out;
  }

  // divvy :: UInt -> UInt -> [T] -> [[T]]
  template <typename T, template <typename> typename Cont>
  auto divvy( UInt n, UInt m, Cont<T> const& xs ) -> Cont<Cont<T>>
  {
    Cont<Cont<T>> out{};

    auto a = begin( xs );
    auto b = end( xs );

    while ( a < b )
    {
      auto it = a + n;
      if ( it > b )
        break;

      out.push_back( Cont<T>{ a, it } );

      a += m;
    }

    return out;
  }
}

#endif
