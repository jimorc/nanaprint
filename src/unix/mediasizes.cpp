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
#include <algorithm>

using namespace std;

namespace nanaprint
{
    MediaSizes::MediaSizes()
    {

    }

    MediaSizes::~MediaSizes()
    {

    }

    void MediaSizes::push_back(MediaSize mediaSize)
    {
        m_mediaSizes.push_back(mediaSize);
    }

    vector<string> MediaSizes::getMediaSizeNames() const
    {
        vector<string> mediaNames;
        for (auto mediaSize: m_mediaSizes)
        {
            mediaNames.push_back(mediaSize.getMediaName());
        }
        return mediaNames;
    }

    size_t MediaSizes::getMediaSizeNumber(const MediaSize& mediaSize) const
    {
        size_t mediaSizeNum = 0;
        const auto sizeNames = getMediaSizeNames();
        for (size_t i = 0; i < size(); ++i)
        {
            if (mediaSize.getMediaName() == sizeNames[i])
            {
                mediaSizeNum = i;
                break;
            }
        }
        return mediaSizeNum;
    }

    bool MediaSizes::contains_borderless_paper() const
    {
        for (auto& mediaSize: m_mediaSizes)
        {
            if (mediaSize.isBorderless())
                return true;
        }
        return false;
    }

    std::optional<MediaSize> MediaSizes::getMediaSizeByTranslatedNameAndBorder(
        const std::string& translatedName, bool isBorderless) const
        {
            auto iter = find_if(m_mediaSizes.begin(), m_mediaSizes.end(), 
                [&](const MediaSize& size){ return ((size.getTranslatedName() == translatedName) &&
                    (size.isBorderless() == isBorderless)); });
            return (iter != m_mediaSizes.end()) ? std::optional<MediaSize>(*iter) : nullopt;
        }

    std::ostream& operator<<(std::ostream& os, const MediaSizes& sizes)
    {
        os << "Media Sizes:\n";
        if (sizes.size() == 0)
        {
            os << "None\n";
        }
        else
        {
            for (auto iter = sizes.cbegin(); iter != sizes.cend(); ++iter)
            {
                os << *iter;
            }
        }
        return os;
    }

    MediaSize& MediaSizes::operator[](size_t pos)
    {
        return m_mediaSizes[pos];
    }

    const MediaSize& MediaSizes::operator[](size_t pos) const
    {
        return m_mediaSizes[pos];
    }

    MediaSize& MediaSizes::at(size_t pos)
    {
        if(pos > m_mediaSizes.size() - 1)
            throw std::out_of_range("Out of range");
        return m_mediaSizes[pos];
    }

    const MediaSize& MediaSizes::at(size_t pos) const
    {
        if(pos > m_mediaSizes.size() - 1)
            throw std::out_of_range("Out of range");
        return m_mediaSizes[pos];
    }
}