#pragma(once)

/**
 *  \file mediatype.h
 *  \brief This file provides media types required by nanaprint
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

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "values.h"

namespace nanaprint
{
    class media_type : public nanaprint_value<std::string>
    {
        public:
            media_type(const std::string& mediaType);
            virtual ~media_type() {}
     };

    std::ostream& operator<<(std::ostream& os, const media_type& mType);

    class MediaTypes
    {
        public:
            struct iterator
            {
                using iterator_category = std::random_access_iterator_tag;
                using difference_type   = std::ptrdiff_t;
                using value_type        = media_type;
                using pointer           = media_type*;  // or also value_type*
                using reference         = media_type&;  // or also value_type& 

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
                using value_type        = const media_type;
                using pointer           = const media_type*;  // or also value_type*
                using reference         = const media_type&;  // or also value_type& 

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

            virtual ~MediaTypes() {}
            void add_type(const std::string& mediaType);
            const std::vector<media_type>& get_types() const;
            size_t size() { return m_types.size(); }
            void clear() { m_types.clear(); }
            media_type& operator[](size_t pos);
            const media_type& operator[](size_t pos) const;
            media_type& at(size_t pos);
            const media_type& at(size_t pos) const;
            iterator begin() noexcept { return iterator(&m_types[0]); }
            iterator end() noexcept { return iterator(&m_types[m_types.size()]); }
            const_iterator cbegin() const noexcept { return const_iterator(&m_types[0]); }
            const_iterator cend() const noexcept { return const_iterator(&m_types[m_types.size()]); }
            iterator rbegin() noexcept { return iterator(&m_types[m_types.size() - 1]); }
            iterator rend() noexcept { return iterator(&m_types[-1]); }
            const_iterator crbegin() const noexcept { return const_iterator(&m_types[m_types.size() - 1]); }
            const_iterator crend() const noexcept { return const_iterator(&m_types[-1]); }
        public:
            std::vector<media_type> m_types;
    };

    std::ostream& operator<<(std::ostream& os, const MediaTypes& mType);
}