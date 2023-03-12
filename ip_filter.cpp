#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
#include "ip_address.h"

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<ipv4::container_type> ip_pool;

        for(std::string line; getline(std::cin, line);)
        {
            size_t pos = line.find_first_of('\t');
            if(pos != std::string::npos)
                ip_pool.emplace_back(ipv4::from_string(line.substr(0,pos)));
        }

        // reverse lexicographically sort
        std::sort(ip_pool.rbegin(), ip_pool.rend());

        // function to print ipv4-address in necessary form
        auto print_ip = [](const ipv4::container_type& ip)
        {
            std::cout << ipv4::to_string(ip) << std::endl;
        };

        // output all
        for(auto const &ip : ip_pool)
            print_ip(ip);

        // ip = filter(1.*.*.*)
        for(auto const &ip : ip_pool)
            if(std::get<0>(ip) == 1) print_ip(ip);
 
        // ip = filter(46.70.*.*)
        for(auto const &ip : ip_pool)
            if(std::get<0>(ip) == 46 && 
               std::get<1>(ip) == 70 ) print_ip(ip);

        // ip = filter_any(*46*)
        for(auto const &ip : ip_pool)
            if(std::any_of(ip.cbegin(), ip.cend(), [](const auto& octet) { return octet == 46; } ))
                print_ip(ip);
    }
    catch(std::exception e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}
