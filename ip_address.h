#pragma once
#include <string>
#include <sstream>
#include <array>


namespace ipv4 {
    // type to hold one octet
    typedef uint8_t octet_type;

    // class to hold the whole ipv4-address value
    typedef std::array<octet_type,4> container_type;

    // delimiter for the string representation
    static const char delimiter = '.';

    // parse ipv4-address from std::string
    // expect only full form of ip-address: 
    // "*.*.*.*" where '*' is a number in [0-255] range
    container_type from_string(const std::string&);

    // serialize to std::string
    std::string to_string(const container_type& );
}