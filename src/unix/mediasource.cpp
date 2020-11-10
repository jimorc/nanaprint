/**
 *  \brief A Media source class
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/mediasource.cpp
 */

#include "mediasource.h"

using namespace std;

namespace nanaprint
{
    MediaSource::MediaSource(const string& source)
    {
        m_source = source;
    }
}