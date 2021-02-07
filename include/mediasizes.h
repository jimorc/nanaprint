#pragma(once)
/**
 *  \brief A MediaSizes class
 *
 *	This header file is used in both Unix and Win32 implementations
 *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/mediasizes.h
 */

#include <vector>
#include <string>
#include <optional>
#include <cups/cups.h>
#include "mediasize.h"

namespace nanaprint 
{
    class media_sizes
    {
        public:
            struct iterator
            {
                using iterator_category = std::random_access_iterator_tag;
                using difference_type   = std::ptrdiff_t;
                using value_type        = MediaSize;
                using pointer           = MediaSize*;  // or also value_type*
                using reference         = MediaSize&;  // or also value_type& 

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
                using value_type        = MediaSize;
                using pointer           = MediaSize const*;  // or also value_type*
                using reference         = MediaSize const&;  // or also value_type& 

                explicit const_iterator(const pointer ptr) : m_ptr(ptr) {}
                const reference operator*() const { return *m_ptr; }
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

            media_sizes();
            virtual ~media_sizes();

            int size() const { return m_mediaSizes.size(); }
            void push_back(MediaSize mediaSize);
            void clear() { m_mediaSizes.clear(); }
            std::vector<std::string> get_media_size_names() const;
            size_t get_media_size_index(const MediaSize& mediaSize) const;
            bool contains_borderless_paper() const;
            std::optional<MediaSize> get_media_size_by_translated_name_and_border(
                const std::string& translatedName, bool isBorderless) const;
            MediaSize& operator[](size_t pos);
            const MediaSize& operator[](size_t pos) const;
            MediaSize& at(size_t pos);
            const MediaSize& at(size_t pos) const;

            iterator begin() { return iterator(&m_mediaSizes[0]); }
            iterator end() { return iterator(&m_mediaSizes[m_mediaSizes.size()]); }
            const_iterator cbegin() const { return const_iterator(&m_mediaSizes[0]); } 
            const_iterator cend() const { return const_iterator(&m_mediaSizes[m_mediaSizes.size()]); }
            iterator rbegin() { return iterator(&m_mediaSizes[m_mediaSizes.size() - 1]); }
            iterator rend() { return iterator(&m_mediaSizes[-1]); }
            const_iterator crbegin() const { return const_iterator(&m_mediaSizes[m_mediaSizes.size() - 1]); }
            const_iterator crend() const { return const_iterator(&m_mediaSizes[-1]); }
        private:
            std::vector<MediaSize> m_mediaSizes;
    };

    std::ostream& operator<<(std::ostream& os, const media_sizes& sizes);
}
