#include <cassert>
#include <limits>
#include <stdexcept>

//#include  <iostream>

#include "ip_address.h"

ipv4::ipv4(const container_type& v)
    :addr(v){}

ipv4 ipv4::from_string(const std::string &str)
{
    ipv4 ip{};
    auto it = str.cbegin();
    
    // get next octet value as a number
    // skip delimiter after octet
    auto parse_octet = [](auto &it, auto const &it_end)->ipv4::octet_type {
        //std::cout << std::endl;
        unsigned v =0; 
        int i =0;
        while(it != it_end)
        {
            //std::cout << "[" << v << "] " << *it << ' ';
            // check cerrent symbol
            if(!isdigit(*it)) {
                if(*it != ipv4::delimiter)
                    throw ("Unsupported symbol");
                else {
                    // skip delimiter
                    ++it;
                    // end of loop
                    break;
                }
            }

            // check for maximm 3 digits per octet
            if(++i > 3)
                throw ("Octet cannot be more than three digits");
            
            v = v*10 + *it-'0';
            ++it;
        }
        // check if octet use at least one symbol
        if(!i)
            throw ("Octet should use at least one symbol");

        // final check that octet is in correct range
        if(v > static_cast<unsigned>(ipv4::octet_max_value))
            throw ("Octet exceeds max value");

        return ipv4::octet_type(v);
    };
 
    // try to parse exactly four octets
    ip.set<3>(parse_octet(it, str.cend()));
    ip.set<2>(parse_octet(it, str.cend()));
    ip.set<1>(parse_octet(it, str.cend()));
    ip.set<0>(parse_octet(it, str.cend()));

    //std::cout << std::endl;

    return ip;
}

std::string ipv4::to_string() const
{
    std::ostringstream res;
        res << unsigned(get<3>()) << ipv4::delimiter;
        res << unsigned(get<2>()) << ipv4::delimiter;
        res << unsigned(get<1>()) << ipv4::delimiter;
        res << unsigned(get<0>()) ;
    return res.str();
}

bool ipv4::operator >(const ipv4& rhs) const noexcept
{
    return addr > rhs.addr;
}

bool ipv4::operator ==(const ipv4& rhs) const noexcept
{
    return addr == rhs.addr;
}
