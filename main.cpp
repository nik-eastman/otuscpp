/*!
\file
Homework 04 for OTUS course: C++ Developoer Professional.
*/

#include <iostream>
#include <vector>
#include <list>
#include <tuple>


/// delimiter, used for for IP printing
const char* delimiter = ".";

/////////////////// integer types support /////////////////////

/// Print IP only for integer types
template<typename T, typename = std::enable_if_t<
    std::is_integral<T>::value &&  // consider all intgral types
    (not std::is_same_v<T,bool>)   // excluding 'bool' type
    >>
void print_ip(T v) {
    for (int i = sizeof(v); i; --i) {
        int byte = (v >> ((i-1)*8) ) & 0xff;
        std::cout << byte;
        if(i != 1)
            std::cout << delimiter;
    }
}

/////////////////// std::vector, std::list support /////////////////////

/// Print IP for std::list and std::vector types
template <
	template <typename, typename> typename Container,
	typename Type,
	typename Allocator = std::allocator<Type>,
	typename = std::enable_if_t<
		std::is_same_v<Container<Type, Allocator>, std::vector<Type, Allocator>> ||
		std::is_same_v<Container<Type, Allocator>, std::list<Type, Allocator>>>>
void print_ip(const Container<Type, Allocator>& v) {
    for (auto it = std::begin(v); it != std::end(v); ++it) {
        if(it != std::begin(v))
            std::cout << delimiter;
        std::cout << *it;
    }
}

/////////////////// std::string support /////////////////////

/// Print IP for string type
template <typename T, typename = std::enable_if_t<std::is_same_v<T, std::string>>>
void print_ip(const T& v) {
    std::cout << v;
}

/////////////////// std::tuple support /////////////////////

/// Helper for tuple_holds_only 
template <typename, typename>
struct tuple_holds_only {};

/// Check if std::tuple holds only given type 
template <typename ...A, typename B>
struct tuple_holds_only<std::tuple<A...>, B>
    : std::bool_constant<(std::is_same_v<A, B> && ...)>
{};

template <typename... A>
struct is_monotype_tuple {};

/// Check if std::tuple holds values of the same types
template <typename A, typename ...B>
struct is_monotype_tuple<std::tuple<A, B...>>
    : tuple_holds_only<std::tuple<B...>, A>
{};

/// Prints one std::tuple value by index
template<typename tuple_type, size_t... I>
void print_tuple(const tuple_type& v, std::index_sequence<I...>)
{
    (..., (std::cout << (I == 0 ? "" : delimiter) << std::get<I>(v)));
}

/// Print IP from std::tuple only if all types in std::tuple are the same
template<
        template <typename...> typename tuple_type,
        typename... T, 
        typename = std::enable_if_t<is_monotype_tuple<tuple_type<T...>>::value>>
void print_ip(const tuple_type<T...>& v)
{
    print_tuple(v, std::make_index_sequence<sizeof...(T)>());
}

/////////////////// main() /////////////////////

int main (int, char **) {
    print_ip( int8_t{-1} ); // 255
    std::cout << std::endl;
    print_ip( int16_t{0} ); // 0.0
    std::cout << std::endl;
    print_ip( int32_t{2130706433} ); // 127.0.0.1
    std::cout << std::endl;
    print_ip( int64_t{8875824491850138409} ); // 123.45.67.89.101.112.131.41
    std::cout << std::endl;
    print_ip( std::string{"Hello, World!"} ); // Hello, World!
    std::cout << std::endl;
    print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    std::cout << std::endl;
    print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
    std::cout << std::endl;
    print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0
    std::cout << std::endl;
    return 0;
}
