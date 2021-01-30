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

    void MediaSizes::addSize(MediaSize mediaSize)
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
            for (auto size: m_mediaSizes)
            {
                if (size.getTranslatedName() == translatedName &&
                    size.isBorderless() == isBorderless)
                {
                    return optional<MediaSize>(size);
                }
            }
            return nullopt;
        }

    std::ostream& operator<<(std::ostream& os, const MediaSizes& sizes)
    {
        os << "Media Sizes:\n";
        auto numberOfSizes = sizes.getSize();
        if (numberOfSizes == 0)
        {
            os << "None\n";
        }
        else
        {
            for (auto i = 0; i < numberOfSizes; ++i)
            {
                os << sizes[i];
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