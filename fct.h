#ifndef functional_algorithms_header
#define functional_algorithms_header

#include <vector>
#include <iostream>
#include <cmath>
#include <tuple>
#include <algorithm>
#include <sstream>
#include <fstream>

namespace fct
{
    using String = std::string;
    using SS = std::stringstream;

    template <typename T>
    using Vec = std::vector<T>;

    template <typename S, typename T>
    using Tup = std::tuple<S, T>;

    long double pi = 3.141592653589793238462643383279502884;
    long double e  = 2.718281828459045235360287471352662497;

    // print :: a -> void
    template <typename T>
    void print( T const& val, char end = '\n' )
    {
        std::cout << val << end;
    }

    // print :: [a] -> void
    template <typename T>
    void print( Vec<T> const& val, char end = '\n' )
    {
        std::cout << "[ ";
        for ( auto const& v : val )
            std::cout << v << ' ';
        std::cout << "]" << end;
    }

    // print :: [[a]] -> void
    template <typename T>
    void print( Vec<Vec<T>> const& xxs, char end = '\n' )
    {
        std::cout << "[ ";
        for ( auto const& xs : xxs )
        {
            std::cout << "[ ";
            for ( auto const& x : xs )
            {
                std::cout << x << ' ';
            }
            std::cout << "] ";
        }
        std::cout << "]" << end;
    }

    // fmap :: ( a -> b ) -> [a] -> [b]
    template <typename S, typename T, typename F>
    Vec<T> fmap( F fct, Vec<S> const& xs )
    {
        Vec<T> out{};
        out.reserve( xs.size() );

        for ( auto const& x : xs )
            out.push_back( fct( x ) );

        return out;
    }

    // transpose :: [[a]] -> [[a]]
    template <typename T>
    Vec<Vec<T>> transpose( Vec<Vec<T>> const& xxs )
    {
        Vec<Vec<T>> out{};

        for ( uint i = 0; i < xxs.size(); i++ )
        {
            auto const& xs = xxs.at( i );
            for ( uint j = 0; j < xs.size(); j++ )
            {
                auto const& x = xs.at( j );

                if ( j >= out.size() )
                    out.push_back( { x } );
                else
                    out.at( j ).push_back( x );
            }
        }

        return out;
    }

    // filter :: ( a -> bool ) -> [a]
    template <typename T, typename F>
    Vec<T> filter( F predicate, Vec<T> const& xs )
    {
        Vec<T> out{};
        out.reserve( xs.size() );

        for ( auto const& x : xs )
            if ( predicate( x ) )
                out.push_back( x );

        return out;
    }

    // takeWhile :: ( a -> bool ) -> [a] -> [a]
    template <typename T, typename F>
    Vec<T> takeWhile( F predicate, Vec<T> const& xs )
    {
        Vec<T> out{};
        out.reserve( xs.size() );

        for ( auto const& x : xs )
            if ( predicate( x ) )
                out.push_back( x );
            else
                break;

        return out;
    }

    // dropWhile :: ( a -> bool ) -> [a] -> [a]
    template <typename T, typename F>
    Vec<T> dropWhile( F predicate, Vec<T> const& xs )
    {
        int i = 0;
        for ( auto const& x : xs )
            if ( predicate( x ) )
                i++;
            else
                break;

        return Vec<T>{ xs.begin() + i, xs.end() };
    }

    // head :: [a] -> a
    template <typename T>
    T head( Vec<T> const& xs )
    {
        return xs.at( 0 );
    }

    // tail :: [a] -> [a]
    template <typename T>
    Vec<T> tail( Vec<T> const& xs )
    {
        return xs.at( 0 );
    }

    // init :: [a] -> [a]
    template <typename T>
    Vec<T> init( Vec<T> const& xs )
    {
        return Vec<T>{ xs.begin(), xs.end() - 1 };
    }

    // last :: [a] -> a
    template <typename T>
    T last( Vec<T> const& xs )
    {
        return xs[ xs.size() - 1 ];
    }

    // subsets :: [a] -> [[a]]
    template <typename T>
    Vec<Vec<T>> subsets( Vec<T> const& xs )
    {
        Vec<Vec<T>> out{};
        out.reserve( std::pow( 2, xs.size() ) );

        // Add the empty set
        out.push_back( Vec<T>{} );

        for ( auto const& x : xs )
        {
            // Create copy of current subsets
            Vec<Vec<T>> new_subsets{ out.begin(), out.end() };

            // Add element to every new subset
            for ( Vec<T>& s : new_subsets )
                s.push_back( x );

            // Add new subsets to output
            out.insert( out.end(), new_subsets.begin(), new_subsets.end() );
        }

        return out;
    }

    // even :: Num -> bool
    template <typename T>
    bool even( T const& val )
    {
        return ! ( val & 1 );
    }

    // odd :: Num -> bool
    template <typename T>
    bool odd( T const& val )
    {
        return ! even( val );
    }

    // abs :: Num -> Num
    template <typename T>
    T abs( T const& x )
    {
        if ( x < 0 )
            return -x;
        return x;
    }

    // abs :: Num -> Int
    template <typename T>
    int signum( T const& x )
    {
        if ( x < 0 )
            return -1;
        else if ( x > 0 )
            return 1;

        return 0;
    }

    // quotRem :: (Integral a) => a -> a -> ( a, a )
    template <typename T>
    Tup<T, T> quotRem( T const& x, T const& y )
    {
        T q = x / y;
        T r = x % y;

        return std::make_tuple( q, r );
    }

    // exp :: Num -> double
    template <typename T>
    long double exp( T const& x )
    {
        return std::pow( e, x );
    }

    // log :: Num -> double
    template <typename T>
    long double log( T const& x )
    {
        return std::log( x );
    }

    // logBase :: a -> a -> a
    template <typename T>
    long double logBase( T const& base, T const& x )
    {
        return std::log( x ) / std::log( base );
    }

    // sqrt :: Num -> double
    template <typename T>
    long double sqrt( T const& x )
    {
        return std::sqrt( x );
    }

    // gcd :: a -> a -> a
    template <typename T>
    T gcd( T const& x, T const& y )
    {
        T end = x <= y ? x : y;

        T j = 1;
        for ( T i = j ; i <= end; i++ )
            if ( abs( x ) % i == 0 && abs( y ) % i == 0 )
                j = i;

        return j;
    }

    // lcm :: a -> a -> a
    template <typename T>
    T lcm( T const& x, T const& y )
    {
        T end = x <= y ? x : y;

        for ( T i = 2 ; i <= end; i++ )
            if ( x % i == 0 && y % i == 0 )
                return i;

        return 1;
    }

    // elem :: a -> [b] -> bool
    template <typename T>
    bool elem( T const& el, Vec<T> const& xs )
    {
        return std::any_of( xs.begin(), xs.end(), [&el]( auto const& x ){ return el == x; } );
    }

    // notElem :: a -> [b] -> bool
    template <typename T>
    bool notElem( T const& el, Vec<T> const& xs )
    {
        return ! elem( el, xs );
    }

    // maximum :: [a] -> a
    template <typename T>
    T maximum( Vec<T> const& xs )
    {
        T out = xs.at( 0 );

        for ( auto const& x : xs )
            if ( x > out )
                out = x;

        return out;
    }

    // minimum :: [a] -> a
    template <typename T>
    T minimum( Vec<T> const& xs )
    {
        T out = xs.at( 0 );

        for ( auto const& x : xs )
            if ( x < out )
                out = x;

        return out;
    }

    // sum :: [a] -> a
    template <typename T>
    T sum( Vec<T> const& xs )
    {
        T out = xs.at( 0 );
        for ( auto i = xs.begin() + 1; i < xs.end(); i++ )
            out += *i;

        return out;
    }

    // product :: [a] -> a
    template <typename T>
    T product( Vec<T> const& xs )
    {
        T out = xs.at( 0 );
        for ( auto i = xs.begin() + 1; i < xs.end(); i++ )
            out *= *i;

        return out;
    }

    // id :: a -> a
    template <typename T>
    T id( T const& x )
    {
        return x;
    }

    // constant :: a -> b -> a
    template <typename S, typename T>
    S constant( S const& x, T const& y )
    {
        // Do some gymnastics to
        // get around unused variable warning
        T out = y;
        out = out;
        return x;
    }

    // flip :: ( a -> b -> c ) -> a -> b -> c
    template <typename S, typename T, typename U, typename F>
    U flip( F func, S const& x, T const& y )
    {
        return func( y, x );
    }

    // until :: ( a -> bool ) -> ( a -> a ) -> a -> a
    template <typename T, typename P, typename F>
    T until( P predicate, F func, T const& x )
    {
        T out = x;
        while ( ! predicate( out ) )
            out = func( out );

        return out;
    }

    // null :: [a] -> bool
    template <typename T>
    bool null( Vec<T> const& xs )
    {
        return xs.empty();
    }

    // length :: [a] -> Num
    template <typename S, typename T = size_t>
    T length( Vec<S> const& xs )
    {
        return xs.size();
    }

    // reverse :: [a] -> [a]
    template <typename T>
    Vec<T> reverse( Vec<T> const& xs )
    {
        Vec<T> out = xs;
        std::reverse( out.begin(), out.end() );
        return out;
    }

    // conjunction :: [a] -> bool
    template <typename T>
    bool conjunction( Vec<T> const& xs )
    {
        bool out = xs.at( 0 );
        for ( auto i = xs.begin() + 1; i < xs.end(); i++ )
            out = out && *i;

        return out;
    }

    // disjunction :: [a] -> bool
    template <typename T>
    bool disjunction( Vec<T> const& xs )
    {
        bool out = xs.at( 0 );
        for ( auto i = xs.begin() + 1; i < xs.end(); i++ )
            out = out || *i;

        return out;
    }

    // any :: ( a -> bool ) -> [a] -> bool
    template <typename T, typename F>
    bool any( F predicate, Vec<T> const& xs )
    {
        return std::any_of( xs.begin(), xs.end(), predicate );
    }

    // all :: ( a -> bool ) -> [a] -> bool
    template <typename T, typename F>
    bool all( F predicate, Vec<T> const& xs )
    {
        return std::all_of( xs.begin(), xs.end(), predicate );
    }

    // concat :: [[a]] -> [a]
    template <typename T>
    Vec<T> concat( Vec<Vec<T>> const& xxs )
    {
        // Count number of items;
        size_t i = 0;
        for ( auto const& xs : xxs )
            i += xs.size();

        Vec<T> out{};
        out.reserve( i );

        for ( auto const& xs : xxs )
            out.insert( out.end(), xs.begin(), xs.end() );

        return out;
    }

    // replicate :: Int -> a - [a]
    template <typename T>
    Vec<T> replicate( int num, T const& val )
    {
        return Vec<T>( num, val );
    }

    // take :: Int -> [a] -> [a]
    template <typename T>
    Vec<T> take( int num, Vec<T> const& xs )
    {
        return Vec<T>{ xs.begin(), xs.begin() + num };
    }

    // drop :: Int -> [a] -> [a]
    template <typename T>
    Vec<T> drop( int num, Vec<T> const& xs )
    {
        return Vec<T>{ xs.begin() + num, xs.end() };
    }

    // splitAt :: Int -> [a] -> ( [a], [a] )
    template <typename T>
    Tup<Vec<T>, Vec<T>> splitAt( int index, Vec<T> const& xs )
    {
        Vec<T> left{ xs.begin(), xs.begin() + index };
        Vec<T> right{ xs.begin() + index, xs.end() };

        return std::make_tuple( left, right );
    }

    // lines :: String -> [String]
    Vec<String> lines( String const& str )
    {
        Vec<String> out{};

        SS ss;
        ss.str( str );
        for ( String line; std::getline( ss, line ); )
            out.push_back( line );

        return out;
    }

    // words :: String -> [String]
    Vec<String> words( String const& str )
    {
        Vec<String> out{};

        SS ss;
        ss.str( str );
        for ( String line; std::getline( ss, line, ' ' ); )
            out.push_back( line );

        return out;
    }

    // unlines :: [String] -> String
    String unlines( Vec<String> const& xs )
    {
        String out = "";
        for ( auto const& x : xs )
            out += x + "\n";

        return out;
    }

    // unwords :: [String] -> String
    String unwords( Vec<String> const& xs )
    {
        String out = "";
        for ( auto const& x : xs )
            out += x + " ";

        return out;

        return xs.at(0);
    }

    // putChar :: Char -> void
    void putChar( char const& ch )
    {
        std::cout << ch;
    }

    // putStr :: String -> void
    void putStr( String const& str )
    {
        std::cout << str;
    }

    // putStrLn :: String -> void
    void putStrLn( String const& str )
    {
        std::cout << str << '\n';
    }

    // getChar :: Char
    char getChar()
    {
        char out;
        std::cin >> out;
        return out;
    }

    // getLine :: String
    String getLine()
    {
        String out = "";
        std::getline( std::cin, out );
        return out;
    }

    // readFile :: String -> String
    String readFile( String const& filePath )
    {
        std::ifstream file( filePath, std::ios_base::in );

        return String{ std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
    }

    // readLn :: String -> String
    String readLn( String const& filePath )
    {
        std::ifstream file( filePath, std::ios_base::in );
        String out = "";
        std::getline( file, out );
        return out;
    }

    // writeFile :: String -> String -> void
    void writeFile( String const& filePath, String const& str )
    {
        std::ofstream file( filePath, std::ios_base::out );
        file << str;
    }

    // appendFile :: String -> String -> void
    void appendFile( String const& filePath, String const& str )
    {
        std::ofstream file( filePath, std::ios_base::app );
        file << str;
    }

    // show :: a -> String
    template <typename T>
    String show( T const& x )
    {
        return std::to_string( x );
    }

    // intersect :: [a] -> [a] -> [a]
    template <typename T>
    Vec<T> intersect( Vec<T> const& xs, Vec<T> const& ys )
    {
        Vec<T> out{};
        Vec<T> const* smaller = xs.size() <= ys.size() ? &xs : &ys;
        Vec<T> const* larger = xs.size() > ys.size() ? &xs : &ys;

        for ( auto const& s : *smaller )
            if ( elem( s, *larger ) )
                out.push_back( s );

        return out;
    }

    // union :: [a] -> [a] -> [a]
    template <typename T>
    Vec<T> union_of( Vec<T> const& xs, Vec<T> const& ys )
    {
        Vec<T> out{};
        Vec<T> const* smaller = xs.size() <= ys.size() ? &xs : &ys;
        Vec<T> const* larger = xs.size() > ys.size() ? &xs : &ys;

        for ( auto const& s : *smaller )
            if ( notElem( s, *larger ) )
                out.push_back( s );

        for ( auto const& l : *larger )
            out.push_back( l );

        return out;
    }

    // intersperse :: a -> [a] -> [a]
    template <typename T>
    Vec<T> intersperse( T const& y, Vec<T> const& xs )
    {
        Vec<T> out{};

        auto i = xs.begin();
        for ( ; i < xs.end() - 1; i++ )
        {
            out.push_back( *i );
            out.push_back( y );
        }
        out.push_back( *i );

        return out;
    }

    // intercalate :: [a] -> [[a]] -> [a]
    template <typename T>
    Vec<T> intercalate( Vec<T> const& xs, Vec<Vec<T>> const& xxs )
    {
        return concat( intersperse( xs, xxs ) );
    }

    // permutations :: [a] -> [[a]]
    template <typename T>
    Vec<Vec<T>> permutations( Vec<T> const& xs )
    {
        Vec<Vec<T>> out{};
        Vec<T> mut_xs = xs;

        std::sort( mut_xs.begin(), mut_xs.end() );

        do
        {
            out.push_back( mut_xs );
        }
        while ( std::next_permutation( mut_xs.begin(), mut_xs.end() ) );

        return out;
    }

    // iterate :: (a -> a) -> a -> [a]
    template <typename T, typename F>
    Vec<T> iterate( int num, F func, T const& x )
    {
        Vec<T> out{};
        for ( uint i = 0; i < num; i++ )
            out.push_back( func( x ) );

        return out;
    }

    // span :: (a -> Bool) -> [a] -> ([a], [a])
    template <typename T, typename F>
    Tup<Vec<T>, Vec<T>> span( F predicate, Vec<T> const& xs )
    {
        int i = 0;
        for ( auto const& x : xs )
            if ( predicate( x ) )
                i++;
            else
                break;

        return std::make_tuple( Vec<T>{ xs.begin(), xs.begin() + i }, Vec<T>{ xs.begin() + i, xs.end() } );
    }

    // break_of :: (a -> Bool) -> [a] -> ([a], [a])
    template <typename T, typename F>
    Tup<Vec<T>, Vec<T>> break_of( F predicate, Vec<T> const& xs )
    {
        int i = 0;
        for ( auto const& x : xs )
            if ( ! predicate( x ) )
                i++;
            else
                break;

        return std::make_tuple( Vec<T>{ xs.begin(), xs.begin() + i }, Vec<T>{ xs.begin() + i, xs.end() } );
    }

    // group :: [a] -> [[a]]
    template <typename T>
    Vec<Vec<T>> group( Vec<T> const& xs )
    {
        Vec<Vec<T>> out{};

        auto a = xs.begin();
        auto b = a;

        while ( b < xs.end() )
        {
            if ( *b == *a )
            {
                b++;
            }
            else
            {
                out.push_back( Vec<T>{ a, b } );
                a = b;
            }
        }
        out.push_back( Vec<T>{ a, b } );

        return out;
    }

    // inits :: [a] -> [[a]]
    template <typename T>
    Vec<Vec<T>> inits( Vec<T> const& xs )
    {
        Vec<Vec<T>> out{};

        auto i = xs.begin();

        for ( ; i < xs.end(); i++ )
            out.push_back( Vec<T>{ xs.begin(), i } );
        out.push_back( Vec<T>{ xs.begin(), i } );

        return out;
    }

    // tails :: [a] -> [[a]]
    template <typename T>
    Vec<Vec<T>> tails( Vec<T> const& xs )
    {
        Vec<Vec<T>> out{};

        auto i = xs.end();

        for ( ; i < xs.begin(); i-- )
            out.push_back( Vec<T>{ xs.begin(), i } );
        out.push_back( Vec<T>{ xs.begin(), i } );

        return out;
    }

    // isPrefixOf :: [a] -> [a] -> Bool
    template <typename T>
    bool isPrefixOf( Vec<T> const& xs, Vec<T> const& ys )
    {
        auto ys_inits = inits( ys );
        return elem( xs, ys_inits );
    }

    // isSuffixOf :: [a] -> [a] -> Bool
    template <typename T>
    bool isSuffixOf( Vec<T> const& xs, Vec<T> const& ys )
    {
        auto ys_rev_tails = tails( reverse( ys ) );
        auto xs_rev = reverse( xs );

        return elem( xs_rev, ys_rev_tails );
    }

    // isInfixOf :: [a] -> [a] -> Bool
    template <typename T>
    bool isInfixOf( Vec<T> const& xs, Vec<T> const& ys )
    {
        auto a = ys.begin();
        auto b = ys.begin() + xs.size();

        Vec<T> test{ xs.begin(), xs.end() };

        for ( ; b < ys.end(); a++, b++ )
            if ( test == Vec<T>{ a, b } )
                return true;

        return false;
    }

    // partition :: ( a -> bool ) -> [a] -> ( [a], [a] )
    template <typename T, typename F>
    Tup<Vec<T>, Vec<T>> partition( F predicate, Vec<T> const& xs )
    {
        Vec<T> left{};
        Vec<T> right{};

        for ( auto const& x : xs )
            if ( predicate( x ) )
                left.push_back( x );
            else
                right.push_back( x );

        return std::make_tuple( left, right );
    }

    // nub :: [a] -> [a]
    template <typename T>
    Vec<T> nub( Vec<T> const& xs )
    {
        Vec<T> out{};

        for ( auto const& x : xs )
            if ( ! elem( x, out ) )
                out.push_back( x );

        return out;
    }
}

#endif
