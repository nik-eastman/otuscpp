#pragma once
#include <list>
#include <algorithm>

template<typename T, std::size_t N>
class heap {
public:
    heap() {
   		auto p = std::malloc(N * sizeof(T));

		if (!p) 
            throw std::bad_alloc();

		base_ptr = reinterpret_cast<T *>(p);
        std::fill(used_map.begin(), used_map.end(), 0);
    }

    heap(const heap&) = delete;

    heap(heap &&other) {
        base_ptr = other.base_ptr;
        used_map = other.used_map;
        
        other.base_ptr = nullptr;
    }

    ~heap() {
        std::free(base_ptr);
    }

    // try to find empty slot
    T* allocate(std::size_t n) {
        if(!base_ptr) throw std::bad_alloc();
        if(n!=1) throw std::bad_alloc();
        if(!n) return nullptr;

        // go through slots map
        for(auto i=0; i<used_map.size(); ++i) {
            if(!used_map[i]) {
                // marks slot as used
                used_map[i] = 1;
                // return pointer
                return base_ptr+i;
            }
        }
        // if we didn't found an empty slot
        return nullptr;
    }

    // mark pointer as free if the pointer belongs to this heap
    // return 'false' if the pointer not from this heap
    bool deallocate(T *p, std::size_t n) {
        if(!base_ptr) throw std::bad_alloc();
        if(n!=1) throw std::bad_alloc();
        
        bool my_one = belogs_to(p);
        if(my_one)
            used_map[p-base_ptr] = 0;

        return my_one;            
    }

    // check if the pointer belongs to this heap
    bool belogs_to(T *p) {
        if(!base_ptr) throw std::bad_alloc();
        return (p >= base_ptr) && (p < (base_ptr + N));
    }

    // check if the whole heap is free
    bool empty() {
        if(!base_ptr) throw std::bad_alloc();
        return std::all_of(used_map.cbegin(), used_map.cend(), [](const uint8_t& v){ return v==0; });
    }

private:
    typedef std::array<uint8_t, N> map_type;
    map_type used_map {};
    T *base_ptr {};
};
