#ifndef MEDIASIZE_H
#define MEDIASIZE_H

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
    class MediaSize
    {
        public:
            MediaSize() : MediaSize("", 0, 0, 0, 0, 0, 0) {}
            MediaSize(const std::string& mediaName, const int width, const int height,
                const int bottom, const int left, const int right, const int top);
            virtual ~MediaSize();

            std::string get_name() const { return m_name; }
            std::string get_translated_name() const;
            int get_width() const { return m_width; }
            int getHeight() const { return m_height; }
            int getBottom() const { return m_bottom; }
            int getLeft() const { return m_left; }
            int getRight() const { return m_right; }
            int getTop() const { return m_top; }
            bool isBorderless() const;

        private:
            static MediaSizesTranslator m_translator;
            std::string m_name;
            std::string m_translatedName;
            int m_width;
            int m_height;
            int m_bottom;
            int m_left;
            int m_right;
            int m_top;
    };

    std::ostream& operator<<(std::ostream& os, const MediaSize& size);
}

#endif      // MEDIASIZE_H