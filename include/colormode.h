#pragma(once)
/**
 *  \file colormode.h
 *  \brief This file provides ColorMode and ColorModes classes required by nanaprint
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

namespace nanaprint
{
    class color_mode
    {
        public:
            color_mode();
            color_mode(const std::string& colormode);
            virtual ~color_mode() {}
            const std::string& getColorMode() const { return m_colorMode; }
        private:
            std::string m_colorMode;
    };

    std::ostream& operator<<(std::ostream& os, const color_mode& cmode);

    class ColorModes
    {
        public:
            struct iterator
            {
                using iterator_category = std::random_access_iterator_tag;
                using difference_type   = std::ptrdiff_t;
                using value_type        = color_mode;
                using pointer           = color_mode*;  // or also value_type*
                using reference         = color_mode&;  // or also value_type& 

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
                using value_type        = const color_mode;
                using pointer           = const color_mode*;  // or also value_type*
                using reference         = const color_mode&;  // or also value_type& 

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

            ColorModes() {}
            virtual ~ColorModes() {}
            void addColorMode(const std::string& cmode);
            const std::vector<color_mode>& getColorModes() const;
            size_t size() const { return m_colorModes.size(); }
            void clear() { m_colorModes.clear(); }
            color_mode& operator[](size_t pos);
            const color_mode& operator[](size_t pos) const;
            color_mode& at(size_t pos);
            const color_mode& at(size_t pos) const;
            iterator begin() noexcept { return iterator(&m_colorModes[0]); }
            iterator end() noexcept { return iterator(&m_colorModes[m_colorModes.size()]); }
            const_iterator cbegin() const noexcept { return const_iterator(&m_colorModes[0]); }
            const_iterator cend() const noexcept { return const_iterator(&m_colorModes[m_colorModes.size()]); }
            iterator rbegin() noexcept { return iterator(&m_colorModes[m_colorModes.size() - 1]); }
            iterator rend() noexcept { return iterator(&m_colorModes[-1]); }
            const_iterator crbegin() const noexcept { return const_iterator(&m_colorModes[m_colorModes.size() - 1]); }
            const_iterator crend() const noexcept { return const_iterator(&m_colorModes[-1]); }
        private:
            std::vector<color_mode> m_colorModes;
    };

    std::ostream& operator<<(std::ostream& os, const ColorModes& cmode);
}
