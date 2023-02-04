#pragma once
#include <string>
#include <sstream>

// class to hold ipv4-address value
class ipv4
{
public:
    // type to hold the whole ip-address 
    typedef uint32_t container_type;

    // type to hold one octet
    typedef uint8_t octet_type;

    // often needed value
    static const octet_type octet_max_value = std::numeric_limits<octet_type>::max();

    // delimiter for the string representation
    static const char delimiter = '.';

public:
    ipv4() =default;
    ipv4(const container_type& v);

    // for sort algorithm
    bool operator >(const ipv4& rhs) const noexcept;

    // for testing purpose
    bool operator ==(const ipv4& rhs) const noexcept;

    // parse from std::string
    // expect only full form of ip-address: 
    // "*.*.*.*" where '*' is a number in [0-255] range
    static ipv4 from_string(const std::string &str);

    // serialize to std::string
    std::string to_string() const;

    // return exact octet value
    template<unsigned _N> 
    octet_type get() const noexcept
    { 
        // check for the range at compile time
        static_assert(_N < sizeof(container_type));

        unsigned shift = _N*8;
        return (addr & (octet_max_value << shift)) >> shift;
    }

    // set octet value
    template<unsigned _N> 
    void set(const octet_type& v) noexcept
    { 
        // check for the range at compile time
        static_assert(_N < sizeof(container_type));

        unsigned shift = _N*8;

        addr |= container_type(octet_max_value) << shift;
        addr &= ~(container_type(v) << shift);
        addr ^= (container_type(octet_max_value) << shift);
    }

private:
    container_type addr{};
};