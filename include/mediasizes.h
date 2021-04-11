#ifndef NANAPRINT_MEDIASIZES_H
#define NANAPRINT_MEDIASIZES_H

/**
 *  \brief A MediaSizes class
 *
 *	This header file is used in both Unix and Win32 implementations
 *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/mediasizes.h
 */

#include <vector>
#include <string>
#include <optional>
#include "mediasize.h"
#include "values.h"

namespace nanaprint
{
    class media_sizes : public nanaprint_values<media_size>
    {
        public:
           media_sizes();
            virtual ~media_sizes();

            std::vector<std::string> get_media_size_names() const;
            size_t get_media_size_index(const media_size& mediaSize) const;
            bool contains_borderless_paper() const;
            std::optional<media_size> get_media_size_by_translated_name_and_border(
                const std::string& translatedName, bool isBorderless) const;
            std::vector<std::string> get_media_size_translated_names_by_border(bool isBorderless) const;
            std::optional<media_size> get_default_media_size_from_name_and_border(
                const std::string& defaultSize);
    };

    std::ostream& operator<<(std::ostream& os, const media_sizes& sizes);
}

#endif      // NANAPRINT_MEDIASIZES_H