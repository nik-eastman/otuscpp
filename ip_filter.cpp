#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm> 
#include "ip_address.h"

int main(int argc, char const *argv[])
{
    using namespace std;
    try
    {
        vector<ipv4> ip_pool;

        for(string line; getline(cin, line);)
        {
            size_t pos = line.find_first_of('\t');
            if(pos != string::npos)
                ip_pool.emplace_back(ipv4::from_string(line.substr(0,pos)));
        }

        // reverse lexicographically sort
        sort(ip_pool.begin(), ip_pool.end(), greater<ipv4>());

        // function to print ipv4-address in necessary form
        auto print_ip = [](const ipv4& ip)
        {
            cout << ip.to_string() << endl;
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
    catch(const char *s)
    {
        cerr << s << endl;
        return -1;
    }
    catch(std::exception e)
    {
        cerr << e.what() << endl;
        return -2;
    }

    return 0;
}
