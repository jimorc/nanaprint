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
#include <set>
#include <string>
#include <memory>
#include <iostream>

namespace nanaprint
{
    class MediaSource
    {
        public:
            MediaSource(const std::string& source);
            virtual ~MediaSource() {}
            const std::string& getSource() const { return m_source; }

        private:
            std::string m_source;
    };

    std::ostream& operator<<(std::ostream& os, const MediaSource& source);

    class MediaSources
    {
        public:
            struct iterator
            {
                using iterator_category = std::random_access_iterator_tag;
                using difference_type   = std::ptrdiff_t;
                using value_type        = MediaSource;
                using pointer           = MediaSource*;  // or also value_type*
                using reference         = MediaSource&;  // or also value_type& 

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

            virtual ~MediaSources() {}
            void addSource(const std::string& source);
            const std::vector<MediaSource> getSources() const;
            MediaSource& operator[](size_t pos);
            const MediaSource& operator[](size_t post) const;
            MediaSource& at(size_t pos);
            const MediaSource& at(size_t pos) const;
            iterator begin() { return iterator(&m_sources[0]); }
            iterator end() { return iterator(&m_sources[m_sources.size()]); }
        private:
            std::vector<MediaSource> m_sources;
    };

    std::ostream& operator<<(std::ostream& os, const MediaSources& sources);
}
