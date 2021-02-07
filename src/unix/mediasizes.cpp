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
    media_sizes::media_sizes()
    {

    }

    media_sizes::~media_sizes()
    {

    }

    void media_sizes::push_back(MediaSize mediaSize)
    {
        m_mediaSizes.push_back(mediaSize);
    }

    vector<string> media_sizes::get_media_size_names() const
    {
        vector<string> mediaNames;
        for (auto mediaSize: m_mediaSizes)
        {
            mediaNames.push_back(mediaSize.get_name());
        }
        return mediaNames;
    }

    size_t media_sizes::get_media_size_index(const MediaSize& mediaSize) const
    {
        auto sizes = get_media_size_names();
        auto iter = find_if(sizes.begin(), sizes.end(),
            [mediaSize](const string& size){ return mediaSize.get_name() == size; });

        // if mediaSize is not found, then return 0
        iter = (iter!=sizes.end()) ? iter : sizes.begin();
        return iter - sizes.begin();
    }

    bool media_sizes::contains_borderless_paper() const
    {
        for (auto& mediaSize: m_mediaSizes)
        {
            if (mediaSize.is_borderless())
                return true;
        }
        return false;
    }

    std::optional<MediaSize> media_sizes::get_media_size_by_translated_name_and_border(
        const std::string& translatedName, bool isBorderless) const
        {
            auto iter = find_if(m_mediaSizes.begin(), m_mediaSizes.end(), 
                [&](const MediaSize& size){ return ((size.get_translated_name() == translatedName) &&
                    (size.is_borderless() == isBorderless)); });
            return (iter != m_mediaSizes.end()) ? std::optional<MediaSize>(*iter) : nullopt;
        }

    std::ostream& operator<<(std::ostream& os, const media_sizes& sizes)
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

    MediaSize& media_sizes::operator[](size_t pos)
    {
        return m_mediaSizes[pos];
    }

    const MediaSize& media_sizes::operator[](size_t pos) const
    {
        return m_mediaSizes[pos];
    }

    MediaSize& media_sizes::at(size_t pos)
    {
        if(pos > m_mediaSizes.size() - 1)
            throw std::out_of_range("Out of range");
        return m_mediaSizes[pos];
    }

    const MediaSize& media_sizes::at(size_t pos) const
    {
        if(pos > m_mediaSizes.size() - 1)
            throw std::out_of_range("Out of range");
        return m_mediaSizes[pos];
    }
}