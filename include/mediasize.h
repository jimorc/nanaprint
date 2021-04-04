#ifndef NANAPRINT_MEDIASIZE_H
#define NANAPRINT_MEDIASIZE_H

/**
 *  \brief A MediaSize class
 *
 *	This header file is used in both Unix and Win32 implementations
 *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/mediasize.h
 */

#include <iostream>
#include <string>
#include "mediasizestranslator.h"

namespace nanaprint
{
    class media_size
    {
        public:
            media_size() : media_size("", 0, 0, 0, 0, 0, 0) {}
            media_size(const std::string& mediaName, const int width, const int height,
                const int bottom, const int left, const int right, const int top);
            virtual ~media_size();

            std::string get_name() const { return m_name; }
            std::string get_translated_name() const;
            int get_width() const { return m_width; }
            int get_height() const { return m_height; }
            int get_bottom() const { return m_bottom; }
            int get_left() const { return m_left; }
            int get_right() const { return m_right; }
            int get_top() const { return m_top; }
            bool is_borderless() const;

        private:
            static media_size_translator m_translator;
            std::string m_name;
            std::string m_translatedName;
            int m_width;
            int m_height;
            int m_bottom;
            int m_left;
            int m_right;
            int m_top;
    };

    std::ostream& operator<<(std::ostream& os, const media_size& size);
}

#endif      // NANAPRINT_MEDIASIZE_H