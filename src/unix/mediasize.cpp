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
    MediaSize::MediaSize(const string& mediaName, const int width, const int height,
        const int bottom, const int left, const int right, const int top)
        : m_mediaName(mediaName), m_width(width), m_height(height),
            m_bottom(bottom), m_left(left), m_right(right),
            m_top(top)
    {

    }

    MediaSize::~MediaSize()
    {

    }
}