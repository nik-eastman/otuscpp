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
        std::vector<ipv4> ip_pool;

        for(std::string line; getline(std::cin, line);)
        {
            size_t pos = line.find_first_of('\t');
            if(pos != std::string::npos)
                ip_pool.emplace_back(ipv4::from_string(line.substr(0,pos)));
        }

        // reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<ipv4>());

        // function to print ipv4-address in necessary form
        auto print_ip = [](const ipv4& ip)
        {
            std::cout << ip.to_string() << std::endl;
        };

        // output all
        for(auto const &ip : ip_pool)
            print_ip(ip);

        // ip = filter(1.*.*.*)
        for(auto const &ip : ip_pool)
            if(ip.get<3>() == 1) print_ip(ip);
 
        // ip = filter(46.70.*.*)
        for(auto const &ip : ip_pool)
            if(ip.get<3>() == 46 && 
               ip.get<2>() == 70 ) print_ip(ip);

        // ip = filter_any(*46*)
        for(auto const &ip : ip_pool)
            if(ip.get<3>() == 46 || 
               ip.get<2>() == 46 ||
               ip.get<1>() == 46 ||
               ip.get<0>() == 46 ) print_ip(ip);
    }
    catch(std::exception e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}
