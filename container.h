#pragma once
#include <string>
#include <sstream>
#include <array>
#include <list>
#include <iostream>
#include <algorithm>
#include <iterator>

template<typename _Type>
struct ne_node{
    ne_node *next =nullptr;
    _Type value;

    ne_node(const ne_node& ) =default;
    ne_node(ne_node&& ) =default;

    ne_node(const _Type& v)
        :value(v) {}

    ne_node(const _Type&& v)
        :value(v) {}
};

// iterator class
template <typename _Type>
class ne_iterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type        = _Type;
    using difference_type   = std::ptrdiff_t;
    using pointer           = value_type*;
    using reference         = value_type&;

private:
    using self = ne_iterator<_Type>;
    using ContainerType = ne_node<_Type>;
    ContainerType *_data = nullptr;

// ctor/dtor
public:
    ne_iterator(ContainerType *v)
    : _data(v) {}

    ~ne_iterator() =default;

// standard operations for iterator
public:
    reference operator*() {
        return _data->value;
    }
    
    pointer operator->() {
        return &(_data->value);
    }

    ne_iterator& operator++() {
        _data = _data->next;
        return *this;
    }

    ne_iterator& operator++(int) {
        self copy(*this);
        _data = _data->next;
        return copy;
    }

    bool operator ==(const ne_iterator& other) const {
        return _data == other._data;
    }

    bool operator !=(const ne_iterator& other) const {
        return !(*this == other);
    }
};

template<typename _Type, typename A = std::allocator<_Type>>
class ne_container {

// ctors\dtors
public:
    ne_container() =default;
    ~ne_container() {
        clear();
    }

// adding data
public:
    void push_back(const _Type& v) {
        data_type *ptr = allocate_element(v);
        if(!_head) 
            _head = _last = ptr;
        else {
            _last->next = ptr;
            _last = ptr;
        }
    }

    void emplace_back(const _Type&& v) {
        data_type *ptr = allocate_element(v);
        if(!_head) 
            _head = _last = ptr;
        else {
            _last->next = ptr;
            _last = ptr;
        }
    }

// common container operations
public:
    std::size_t size() const {
        return _size;
    }
 
    bool empty() const {
        return size() >0;
    }

    void clear() {
        auto ptr = _head;
        while(ptr) {
            auto next = ptr->next;
            free_element(ptr);
            ptr = next;
        }
        _size =0;
        _head =nullptr;
        _last =nullptr;
        _end  =nullptr;
    }

// internal data types
private:
    using data_type = ne_node<_Type>;

// internal operations
private:
    template<typename ... Args>
    data_type* allocate_element(Args &&...args) {
       data_type* ptr = allocator.allocate(1);
       allocator.construct(ptr, std::forward<Args>(args)...);
       return ptr;
    }

    void free_element(data_type *ptr) {
        allocator.destroy(ptr);
        allocator.deallocate(ptr,1);
    }

// range operators 
public:
    using iterator = ne_iterator<_Type>;

    iterator begin() const {
        return iterator(_head);
    }

    iterator end() const {
        return iterator(nullptr);
    }

// internal data
private:
    std::size_t _size =0;
    data_type  *_head =nullptr;
    data_type  *_last =nullptr;
    data_type   *_end =nullptr;
    
// internal allocator     
private:    
    using ne_local_allocator = typename A::template rebind<data_type>::other;
    ne_local_allocator allocator;
};
