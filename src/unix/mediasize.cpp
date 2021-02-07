/**
 *  \brief A MediaSize class
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/mediasize.cpp
 */

#include "mediasize.h"

using namespace std;

namespace nanaprint
{
    MediaSizesTranslator MediaSize::m_translator;

    MediaSize::MediaSize(const string& mediaName, const int width, const int height,
        const int bottom, const int left, const int right, const int top)
        : m_name(mediaName), m_width(width), m_height(height),
            m_bottom(bottom), m_left(left), m_right(right),
            m_top(top)
    {
        m_translatedName = m_translator.getTranslatedSize(m_name);
    }

    MediaSize::~MediaSize()
    {

    }

    std::string MediaSize::get_translated_name() const
    {
        return m_translatedName;
    }

    bool MediaSize::isBorderless() const
    {
        return m_top == 0 && m_bottom == 0 && m_left == 0 && m_right == 0;
    }

    std::ostream& operator<<(std::ostream& os, const MediaSize& size)
    {
        os << size.get_translated_name();
        if (size.isBorderless())
        {
            os << "    Borderless";
        }
        os << "\n    width = " << size.get_width() << ", height = " << size.get_height() << ",\n";
        os << "    top = " << size. get_top() << ", bottom = " << size.get_bottom() << ",\n";
        os << "    left = " << size.get_left() <<", right = " << size.get_right() <<  '\n';
        return os;
    }
}