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
   * Function Wrapper Class
   *
   * Used to wrap non-lambda functions
   * This makes grabbing the return type and argument types
   *   easy with function templates
   *
   * Lambda functions can be wrapped but require
   *   explicit template parameters or casting to pointers
   */
  template <typename F_ret, typename... F_args>
  class Function_W
  {
  public:
    F_ret (*fct)(F_args...);

    explicit Function_W( F_ret (*fct_val)(F_args...) )
      : fct{ fct_val }
    {}

    template <typename... G_args>
    F_ret operator()( G_args... args ) const
    {
      return fct( args... );
    }
  };

  /*
   * Helper: Convert a lambda function to Function_W
   */
  template <typename F, typename F_ret, typename ...F_args>
  auto toFct( F const& f, F_ret ( F::* )( F_args... ) const ) -> Function_W<F_ret,F_args...>
  {
    return Function_W<F_ret,F_args...>{f};
  }

  /*
   * Convert a lambda function to an std::function
   */
  template <typename F>
  auto toFct( F const& f )
  {
    return toFct( f, &F::operator() );
  }

  /*
   * Convert a non-lambda function to an Function_W
   */
  template <typename F_ret, typename... F_args>
  auto toFct( F_ret ( *const f )( F_args... ) ) -> Function_W<F_ret,F_args...>
  {
    return Function_W<F_ret,F_args...>{f};
  }

  /*
   * Convert a Function_W to an std::function
   */
  template <typename F_ret, typename... F_args>
  auto toStdFct( Function_W<F_ret,F_args...> const& f ) -> Function<F_ret(F_args...)>
  {
    return f;
  }

  /*
   * Helper: Convert a lambda function to an std::function
   */
  template <typename F, typename F_ret, typename ...F_args>
  auto toStdFct( F const& f, F_ret ( F::* )( F_args... ) const ) -> Function<F_ret(F_args...)>
  {
    return f;
  }

  /*
   * Convert a lambda function to an std::function
   */
  template <typename F>
  auto toStdFct( F const& f )
  {
    return toStdFct( f, &F::operator() );
  }

  /*
   * Convert a non-lambda function to an std::function
   */
  template <typename F_ret, typename... F_args>
  auto toStdFct( F_ret ( *const f )( F_args... ) ) -> Function<F_ret(F_args...)>
  {
    return Function<F_ret(F_args...)>{f};
  }

  /*
   * compose :: F -> F_ret(F_args...) -> G -> G_ret(G_args...) -> Function<G_ret(F_args...)>
   *
   * Composes two std::functions using the mathematical composition [i.e. (f.g)(x) ]
   */
  template <typename F, typename F_ret, typename ...F_args,
            typename G, typename G_ret, typename ...G_args>
  auto compose( F const& f, F_ret ( F::* )( F_args... ) const ,
                G const& g, G_ret ( G::* )( G_args... ) const )
  {
    return [f, g]( G_args... args ) -> F_ret { return f( g( args... ) ); };
  }

  /*
   * Compose two lambdas using pipe style.
   * Evaluates right to left
   */
  template <typename F, typename G>
  auto operator | ( F f, G g )
  {
    return compose( f, &F::operator(),
                    g, &G::operator() );
  }

  /*
   * operator | :: (S -> T) -> (T -> U) -> (S -> U)
   *
   * Composes two Function_W wrappers
   */
  template <typename F_ret, typename ...F_args,
            typename G_ret, typename ...G_args>
  auto operator | ( Function_W<F_ret, F_args...> f, Function_W<G_ret, G_args...> g )
  {
    return [f, g]( G_args... args ) -> F_ret { return f( g( args... ) ); };
  }

  /*
   * Compose a Lambda with a Function_W
   * Evaluates right to left
   */
  template <typename F, typename F_ret, typename ...F_args,
                        typename G_ret, typename ...G_args>
  auto compose( F const& f, F_ret ( F::* )( F_args... ) const ,
                 Function_W<G_ret, G_args...> g ) -> Function<F_ret ( G_args... )>
  {
    return [f, g]( G_args... args ) { return f( g( args... ) ); };
  }

  /*
   * operator | :: (S -> T) -> (T -> U) -> (S -> U)
   *
   * Composes a Lambda with a Function_W
   */
  template <typename F, typename G_ret, typename ...G_args>
  auto operator | ( F f, Function_W<G_ret, G_args...> g )
  {
    return compose( f, &F::operator(),
                    g );
  }

  /*
   * Compose a Function_W with a Lambda
   * Evaluates right to left
   */
  template <            typename F_ret, typename ...F_args,
            typename G, typename G_ret, typename ...G_args>
  auto compose( Function_W<F_ret, F_args...> f,
                G const& g, G_ret ( G::* )( G_args... ) const ) -> Function<F_ret ( G_args... )>
  {
    return [f, g]( G_args... args ) { return f( g( args... ) ); };
  }

  /*
   * operator | :: (S -> T) -> (T -> U) -> (S -> U)
   *
   * Composes a Function_W with a Lambda
   */
  template <typename F_ret, typename ...F_args, typename G>
  auto operator | ( Function_W<F_ret, F_args...> f, G g )
  {
    return compose( f, g, &G::operator() );
  }
}

#endif
