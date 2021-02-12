#ifndef NANAPRINT_VALUES_H
#define NANAPRINT_VALUES_H

/**
 *  \file value.h
 *  \brief This file provides templated base class for various value classes.
 *
 *	This header file is used in both Unix and Win32 implementations
 *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 */

namespace nanaprint
{
    template<typename T>
    class nanaprint_values
    {
        public:
            struct iterator
            {
                using iterator_category = std::random_access_iterator_tag;
                using difference_type   = std::ptrdiff_t;
                using value_type        = T;
                using pointer           = T*;  // or also value_type*
                using reference         = T&;  // or also value_type& 

                explicit iterator(pointer ptr) : m_ptr(ptr) {}
                reference operator*() const { return *m_ptr; }
                pointer operator->() const { return m_ptr; }

                // Prefix increment
                iterator& operator++() { m_ptr++; return *this; }  

                // Postfix increment
                iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

                // Prefix decrement
                iterator& operator--() { m_ptr--; return *this; }  

                // Postfix decrement
                iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }

                friend bool operator== (const iterator& a, const iterator& b) { return a.m_ptr == b.m_ptr; };
                friend bool operator!= (const iterator& a, const iterator& b) { return a.m_ptr != b.m_ptr; };
                friend size_t operator- (const iterator&a, const iterator&b) { return a.m_ptr - b.m_ptr; };

                private:
                    pointer m_ptr;
            };

            nanaprint_values() {}
            virtual ~nanaprint_values() {}
    };
}

#endif      // NANAPRINT_VALUES_H