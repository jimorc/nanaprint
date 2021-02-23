#pragma(once)

/**
 *  \file mediasources.h
 *  \brief This file provides media sources required by nanaprint
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
#include <string>
#include <memory>
#include <iostream>
#include "values.h"

namespace nanaprint
{
    class media_source : public nanaprint_value<std::string>
    {
        public:
            media_source(const std::string& source);
            virtual ~media_source() {}
    };

    std::ostream& operator<<(std::ostream& os, const media_source& source);

    class media_sources
    {
        public:
            struct iterator
            {
                using iterator_category = std::random_access_iterator_tag;
                using difference_type   = std::ptrdiff_t;
                using value_type        = media_source;
                using pointer           = media_source*;  // or also value_type*
                using reference         = media_source&;  // or also value_type& 

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
                using value_type        = const media_source;
                using pointer           = const media_source*;  // or also value_type*
                using reference         = const media_source&;  // or also value_type& 

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

            media_sources() {}
            virtual ~media_sources() {}
            void add_source(const std::string& source);
            const std::vector<media_source>& get_sources() const;
            size_t size() { return m_sources.size(); }
            void clear() { m_sources.clear(); }
            media_source& operator[](size_t pos);
            const media_source& operator[](size_t post) const;
            media_source& at(size_t pos);
            const media_source& at(size_t pos) const;
            iterator begin() noexcept { return iterator(&m_sources[0]); }
            iterator end() noexcept { return iterator(&m_sources[m_sources.size()]); }
            const_iterator cbegin() const noexcept { return const_iterator(&m_sources[0]); }
            const_iterator cend() const noexcept { return const_iterator(&m_sources[m_sources.size()]); }
            iterator rbegin() noexcept { return iterator(&m_sources[m_sources.size() - 1]); }
            iterator rend() noexcept { return iterator(&m_sources[-1]); }
            const_iterator crbegin() const noexcept { return const_iterator(&m_sources[m_sources.size() - 1]); }
            const_iterator crend() const noexcept { return const_iterator(&m_sources[-1]); }
        private:
            std::vector<media_source> m_sources;
    };

    std::ostream& operator<<(std::ostream& os, const media_sources& sources);
}
