#pragma once
#include <list>
#include <algorithm>

// allocator class
//  - allocate by chunks (heaps) of N elements each
//  - can allocate only one element at once
//  - if chunk is being deleted if it's empty after deleting an element
template<typename T, std::size_t N>
class ne_allocator {
public:
	using value_type = T;

	using pointer = T *;
	using const_pointer = const T *;

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
		new (p) U(std::forward<Args>(args)...);
	};

	template <typename U>
	void destroy(U *p) {
		p->~U();
	}

	template <class T, class U>
	bool operator==(ne_allocator<T> const&, ne_allocator<U> const&) noexcept
	{
		return true;
	}

	template <class T, class U>
	bool operator!=(ne_allocator<T> const& x, ne_allocator<U> const& y) noexcept
	{
		return !(x == y);
	}

private:
    std::list<heap<T,N>> heaps;
};