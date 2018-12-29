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

#ifndef functional_algorithms_composition_header
#define functional_algorithms_composition_header

#include "fct/internal/include.h"
#include "fct/internal/using.h"

namespace fct
{
  /*
   * toFct :: F_ret (F_args...) -> Function<F_ret(F_args...)>
   *
   * Convert an explicit function to an std::function
   */
  template <typename F_ret, typename... F_args>
  auto toFct( F_ret ( *f )( F_args... ) ) -> Function<F_ret ( F_args... )>
  {
    return f;
  }

  /*
   * compose :: F -> F_ret(F_args...) -> G -> G_ret(G_args...) -> Function<G_ret(F_args...)>
   *
   * Composes two std::functions using the mathematical composition [i.e. (f.g)(x) ]
   */
  template <typename F, typename F_ret, typename ...F_args,
            typename G, typename G_ret, typename ...G_args>
  auto compose( F const& f, F_ret ( F::* )( F_args... ) const ,
                G const& g, G_ret ( G::* )( G_args... ) const ) -> Function<F_ret ( G_args... )>
  {
    return [f, g]( G_args... args ) { return f( g( args... ) ); };
  }

  /*
   * operator | :: (S -> T) -> (T -> U) -> (S -> U)
   *
   * Compose two lambdas using pipe style.
   * Evaluates right to left
   */
  template <typename F, typename G>
  auto operator | ( F f, G g )
  {
    return compose( f, &F::operator(),
                    g, &G::operator() );
  }
}

#endif
