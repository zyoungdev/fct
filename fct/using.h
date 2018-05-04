#ifndef functional_algorithms_using_header
#define functional_algorithms_using_header

namespace fct
{
  using String = std::string;
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
}

#endif
