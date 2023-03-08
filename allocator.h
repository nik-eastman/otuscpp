#pragma once
#include <string>
#include <list>
#include <iostream>
#include <algorithm>

template<typename T, std::size_t N>
class ne_allocator {
public:
	using value_type = T;

	using pointer = T *;
	using const_pointer = const T *;
	//using reference = T &;
	//using const_reference = const T &;

	template <typename U>
	struct rebind {
		using other = ne_allocator<U,N>;
	};

	ne_allocator() noexcept = default;
	~ne_allocator() = default;

	template <typename U>
	ne_allocator(const ne_allocator<U,N> &) {
	}

    // return pointer to allocated memory
	value_type *allocate(std::size_t n) {
        if(!n) return nullptr; // UB

		//std::cout << "allocate: [n = " << n << "] " << std::endl;
        // try to find an empty pointer in current heaps
        for(auto &h: heaps) {
            auto ptr = h.allocate(n);
            if(ptr) return ptr;
        }
        // we need to add one more heap
        heaps.emplace_back(heap<value_type,N>());
        return heaps.back().allocate(n);
	}

    // mark the pointer as free
    // delete heap if it's necessary
	void deallocate(value_type *p, std::size_t n) {
		//std::cout << "deallocate: [n  = " << n << "] at " << p << std::endl;
        // try to find heap pointer belongs to
        for(auto h = heaps.begin(); h != heaps.end(); ++h) {
            if(h->deallocate(p,n)) {
                if(h->empty()) heaps.erase(h);
                return;
            }
        }
        // couldn't find a heap, the pointer belongs to
        throw std::bad_alloc();
	}

	template <typename U, typename... Args>
	void construct(U *p, Args &&...args) {
		//std::cout << "construct at " << p << std::endl;
		new (p) U(std::forward<Args>(args)...);
	};

	template <typename U>
	void destroy(U *p) {
		//std::cout << "destroy " << p << std::endl;
		p->~U();
	}

	bool operator==(const ne_allocator& other) const
	{
		return this==&other;
	}

private:
    std::list<heap<T,N>> heaps;
};