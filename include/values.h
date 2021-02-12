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

#include <vector>
#include <stdexcept>

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

            struct const_iterator
            {
                using iterator_category = std::random_access_iterator_tag;
                using difference_type   = std::ptrdiff_t;
                using value_type        = const T;
                using pointer           = const T*;  // or also value_type*
                using reference         = const T&;  // or also value_type& 

                explicit const_iterator(pointer ptr) : m_ptr(ptr) {}
                reference operator*() const { return *m_ptr; }
                pointer operator->() const { return m_ptr; }

                // Prefix increment
                const_iterator& operator++() { m_ptr++; return *this; }  

                // Postfix increment
                const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }

                // Prefix decrement
                const_iterator& operator--() { m_ptr--; return *this; }  

                // Postfix decrement
                const_iterator operator--(int) { const_iterator tmp = *this; --(*this); return tmp; }

                friend bool operator== (const const_iterator& a, const const_iterator& b) { return a.m_ptr == b.m_ptr; };
                friend bool operator!= (const const_iterator& a, const const_iterator& b) { return a.m_ptr != b.m_ptr; };
                friend size_t operator- (const const_iterator&a, const const_iterator&b) { return a.m_ptr - b.m_ptr; };

                private:
                    pointer m_ptr;
            };

            nanaprint_values() {}
            virtual ~nanaprint_values() {}
            void push_back(const T& value) { m_values.push_back(value); }
            const std::vector<T>& get_values() const { return m_values; }
            size_t size() const { return m_values.size(); }
            void clear() { m_values.clear(); }
            T& operator[](size_t pos) { return m_values[pos]; }
            const T& operator[](size_t pos) const { return m_values[pos]; }
            T& at(size_t pos)
            {
                if(pos >= m_values.size())
                {
                    throw std::out_of_range("Out of range");
                }
                return m_values[pos];
            }
            const T& at(size_t pos) const
            {
                if(pos >= m_values.size())
                {
                    throw std::out_of_range("Out of range");
                }
                return m_values[pos];
            }
            iterator begin() noexcept { return iterator(&m_values[0]); }
            iterator end() noexcept { return iterator(&m_values[m_values.size()]); }
            const_iterator cbegin() const noexcept { return const_iterator(&m_values[0]); }
            const_iterator cend() const noexcept { return const_iterator(&m_values[m_values.size()]); }
            iterator rbegin() noexcept { return iterator(&m_values[m_values.size() - 1]); }
            iterator rend() noexcept { return iterator(&m_values[-1]); }
            const_iterator crbegin() const noexcept { return const_iterator(&m_values[m_values.size() - 1]); }
            const_iterator crend() const noexcept { return const_iterator(&m_values[-1]); }

        protected:
            std::vector<T> m_values;
    };
}

#endif      // NANAPRINT_VALUES_H