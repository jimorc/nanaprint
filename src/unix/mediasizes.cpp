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

    vector<string> media_sizes::get_media_size_names() const
    {
        vector<string> mediaNames;
        for (auto mediaSize: get_values())
        {
            mediaNames.push_back(mediaSize.get_name());
        }
        return mediaNames;
    }

    size_t media_sizes::get_media_size_index(const media_size& mediaSize) const
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
        for (auto& mediaSize: get_values())
        {
            if (mediaSize.is_borderless())
                return true;
        }
        return false;
    }

    std::optional<media_size> media_sizes::get_media_size_by_translated_name_and_border(
        const std::string& translatedName, bool isBorderless) const
        {
            auto iter = find_if(cbegin(), cend(), 
                [&](const media_size& size){ return ((size.get_translated_name() == translatedName) &&
                    (size.is_borderless() == isBorderless)); });
            return (iter != cend()) ? std::optional<media_size>(*iter) : nullopt;
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
}