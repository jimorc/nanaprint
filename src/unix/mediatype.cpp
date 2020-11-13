/**
 *  \brief A Media type class
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

#include "mediatype.h"

using namespace std;

namespace nanaprint
{
    MediaType::MediaType(const std::string& mediaType)
        : m_type(mediaType)
    {

    }
}
