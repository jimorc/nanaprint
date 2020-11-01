#ifndef MEDIASIZES_H
#define MEDIASIZES_H

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

#include <memory>
#include <vector>
#include <cups/cups.h>
#include "mediasize.h"

namespace nanaprint 
{
    class MediaSizes
    {
        public:
            MediaSizes();
            virtual ~MediaSizes();

            int getSize() const { return m_mediaSizes.size(); }
            void addSize(std::shared_ptr<MediaSize> mediaSize);
            std::vector<std::string> getMediaSizeNames();

        private:
            std::vector<std::shared_ptr<MediaSize>> m_mediaSizes;
    };
}

#endif      // MEDIASIZES_H