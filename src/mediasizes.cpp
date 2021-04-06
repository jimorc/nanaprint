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
#include <iterator>

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

    vector<string> media_sizes::get_media_size_translated_names_by_border(bool isBorderless) const
    {
        vector<media_size> mSizes;
        copy_if(cbegin(), cend(), back_inserter(mSizes), [this, isBorderless](media_size size) 
            { return (size.is_borderless() == isBorderless); });
        vector<string> sizes;
        for (auto& size : mSizes)
        {
            sizes.push_back(size.get_translated_name());
        }
        return sizes;
    }

    
    optional<media_size> media_sizes::get_default_media_size_from_name_and_border(
        const string& defaultSize)
    {
        string defSize(defaultSize);
        // default paper size for Canon printers is of form size.Borderless for borderless papers
        // e.g. A4.Borderless, just size (e.g. A4) for bordered papers.
        size_t pos = defSize.find(".Borderless");
        bool borderless = pos != defSize.npos;
        if (borderless)
        {
            defSize = defSize.substr(0, pos);
        }
        else
        {
            // default paper size for Brother printers is of form Brsize_B (e.g. BrA4-B) for
            // borderless papers and size (e.g. A4) for bordered papers.
            pos = defSize.find("_B");
            if (pos != defSize.npos)
            {
                defSize = defSize.substr(2, pos - 2);
            }
        }
        return get_media_size_by_translated_name_and_border(defSize, borderless);
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