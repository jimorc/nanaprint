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
    media_type::media_type(const std::string& mediaType)
        : nanaprint_value(mediaType)
    {

    }

    std::ostream& operator<<(std::ostream& os, const media_type& mType)
    {
        os << "    " << mType.get_value() << '\n';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const media_types& mType)
    {
        os << "Media Types:\n";
        auto types = mType.get_values();
        if(types.size() == 0)
        {
            os << "    None\n";
        }
        else
        {
            for (const auto& typ: types)
            {
                os << typ;
            }
        }
        return os;
    }
}
