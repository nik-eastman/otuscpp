#include <cassert>
#include <limits>
#include <stdexcept>

#include "ip_address.h"

namespace ipv4 {

    ipv4::container_type from_string(const std::string &str)
    {
        auto it = str.cbegin();
        
        // get next octet value as a number
        // skip delimiter after octet
        auto parse_octet = [](auto &it, auto const &it_end)->ipv4::octet_type {
            unsigned v =0; 
            int i =0;
            while(it != it_end)
            {
                // check if the symbol is not a digit or a delimiter
                if(!isdigit(*it)) {
                    if(*it != ipv4::delimiter)
                        throw std::invalid_argument("Unsupported symbol");
                    else {
                        // skip delimiter
                        ++it;
                        // end of loop
                        break;
                    }
                }

                // check for maximum 3 digits per octet
                if(++i > 3)
                    throw std::invalid_argument("Octet cannot be more than three digits");
                
                // calculate octet value
                v = v*10 + *it-'0';

                // go to the next symbol
                ++it;
            }
            // check if octet use at least one symbol
            if(!i)
                throw std::invalid_argument("Octet should use at least one symbol");

            // final check that octet is in correct range
            if(v > static_cast<unsigned>(std::numeric_limits<ipv4::octet_type>::max()))
                throw std::invalid_argument("Octet exceeds max value");

            return ipv4::octet_type(v);
        };

        // check special case if the last symbol is a delimiter
        if(str.back() == ipv4::delimiter)
            throw std::invalid_argument("Invalid last symbol");

        ipv4::container_type ip;

        // try to parse exactly four octets
        // we will have an exception if something is wrong
        std::get<0>(ip) = parse_octet(it, str.cend());
        std::get<1>(ip) = parse_octet(it, str.cend());
        std::get<2>(ip) = parse_octet(it, str.cend());
        std::get<3>(ip) = parse_octet(it, str.cend());

        // if still some symbols to parse
        if(it != str.cend())
            throw std::invalid_argument("Too much octets");

        return ip;
    }

    std::string to_string(const ipv4::container_type& v)
    {
        std::ostringstream res;
            res << unsigned(std::get<0>(v)) << delimiter;
            res << unsigned(std::get<1>(v)) << delimiter;
            res << unsigned(std::get<2>(v)) << delimiter;
            res << unsigned(std::get<3>(v)) ;
        return res.str();
    }
}