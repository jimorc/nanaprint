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

    std::ostream& operator<<(std::ostream& os, const MediaType& mType)
    {
        os << "    " << mType.getType() << '\n';
        return os;
    }

    void MediaTypes::addMediaType(const std::string& mediaType)
    {
        m_types.insert(make_shared<MediaType>(MediaType(mediaType)));
    }

    vector<shared_ptr<MediaType>> MediaTypes::getMediaTypes() const
    {
        vector<shared_ptr<MediaType>> mediaTypes;
        for(auto& mediaType: m_types)
        {
            mediaTypes.push_back(mediaType);
        }
        return mediaTypes;
    }

    std::ostream& operator<<(std::ostream& os, const MediaTypes& mType)
    {
        os << "Media Types:\n";
        auto types = mType.getMediaTypes();
        for (const auto& typ: types)
        {
            os << *typ;
        }
        return os;

    }
}
