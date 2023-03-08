#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm> 
#include <map> 

#include "heap.h"
#include "allocator.h"
#include "container.h"

int main(int argc, char const *argv[])
{
    auto fill_map = [](auto& m, size_t N) {
        m[0]=0;
        for(int i=1, v=1; i<N; i++)
            m[i]= (v*=i);
    };

    auto print_map = [](const auto& m) {
        for(auto const& [k,v]: m)
            std::cout << k << " " << v << std::endl;
    };

    {
        std::map<int,int> m;
        fill_map(m, 10);
        print_map(m);
    }
    {
        std::map<int, int, std::less<int>, ne_allocator<std::pair<int,int>,3>> m;
        fill_map(m, 10);
        print_map(m);
    }

    auto fill_container = [](auto& c, size_t N) {
        for(int i=0; i<N; i++)
            c.push_back(i);
    };

    auto print_container = [](const auto& c) {
        for(auto & k: c)
           std::cout << k << " ";
    
        std::cout << std::endl;
    };

    {
        ne_container<int> c;
        fill_container(c,10);
        print_container(c);
    }

    {
        ne_container<int, ne_allocator<int,10>> c;
        fill_container(c,10);
        print_container(c);
    }

    return 0;
}
