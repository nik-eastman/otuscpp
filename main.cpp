/*!
@file
Homework 04 for OTUS course: C++ Developoer Professional.
*/

#include <iostream>
#include <vector>
#include <list>
#include <tuple>


/// @brief Delimiter, used in IP printing octets
const char* delimiter = ".";

/////////////////// integer types support /////////////////////

/// Print IP only for integer types
/// @param v any of integer types
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

/// @brief Print IP for std::list and std::vector types
/// @param v input container
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

/// @brief Print IP from std::string
/// @param v std::string value
template <typename T, typename = std::enable_if_t<std::is_same_v<T, std::string>>>
void print_ip(const T& v) {
    std::cout << v;
}

/////////////////// std::tuple support /////////////////////

/// @brief Helper for tuple_holds_only 
template <typename, typename>
struct tuple_holds_only {};

/// @brief Check if std::tuple holds only given type 
template <typename ...A, typename B>
struct tuple_holds_only<std::tuple<A...>, B>
    : std::bool_constant<(std::is_same_v<A, B> && ...)>
{};

/// @brief Helper for is_monotype_tuple 
template <typename>
struct is_monotype_tuple {};

/// @brief Check if std::tuple holds values of the same types
template <typename A, typename ...B>
struct is_monotype_tuple<std::tuple<A, B...>>
    : tuple_holds_only<std::tuple<B...>, A>
{};

/// @brief Print one std::tuple value by index
/// @param v value
/// @param I number of value in tuple_type
template<typename tuple_type, size_t... I>
void print_tuple(const tuple_type& v, std::index_sequence<I...>)
{
    (..., (std::cout << (I == 0 ? "" : delimiter) << std::get<I>(v)));
}

/// @brief Print IP from std::tuple 
/// @brief all types in std::tuple must be the same type
/// @param v - std::tuple value
template<
        template <typename...> typename tuple_type,
        typename... T, 
        typename = std::enable_if_t<is_monotype_tuple<tuple_type<T...>>::value>>
void print_ip(const tuple_type<T...>& v)
{
    print_tuple(v, std::make_index_sequence<sizeof...(T)>());
}

/////////////////// main() /////////////////////

/// @brief main fnuction to check functionality
/// @return 0 if everything is OK
/// @return !=0 if something is wrong 
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
