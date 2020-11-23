/**
 *  \brief A MediaSizes class
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/mediasizes.cpp
 */

#include "mediasizes.h"

using namespace std;

namespace nanaprint
{
    MediaSizes::MediaSizes()
    {

    }

    MediaSizes::~MediaSizes()
    {

    }

    void MediaSizes::addSize(std::shared_ptr<MediaSize> mediaSize)
    {
        m_mediaSizes.push_back(mediaSize);
    }

    vector<string> MediaSizes::getMediaSizeNames() const
    {
        vector<string> mediaNames;
        for (auto mediaSize: m_mediaSizes)
        {
            mediaNames.push_back(mediaSize->getMediaName());
        }
        return mediaNames;
    }

    size_t MediaSizes::getMediaSizeNumber(const MediaSize& mediaSize) const
    {
        size_t mediaSizeNum = 0;
        const auto sizeNames = getMediaSizeNames();
        for (size_t i = 0; i < getSize(); ++i)
        {
            if (mediaSize.getMediaName() == sizeNames[i])
            {
                mediaSizeNum = i;
                break;
            }
        }
        return mediaSizeNum;
    }

    std::ostream& operator<<(std::ostream& os, const MediaSizes& sizes)
    {
        os << "Media Sizes:\n";
        auto mediaSizes = sizes.getMediaSizes();
        if (mediaSizes.empty())
        {
            os << "None\n";
        }
        else
        {
            for (auto& size: mediaSizes)
            {
                os << *size;
            }
        }
        return os;
    }
}