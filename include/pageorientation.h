#pragma(once)

/**
 *  \file pageorientation.h
 *  \brief This file provides orientation class and data structures required by nanaprint
 *
 *	This header file is used in both Unix and Win32 implementations
 *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#include <string>
#include <memory>
#include <cups/cups.h>

namespace nanaprint
{
    constexpr int PORTRAIT = 3;
    constexpr int LANDSCAPE = 4;
    constexpr int REVERSE_LANDSCAPE = 5;
    constexpr int REVERSE_PORTRAIT = 6;
    
    class PageOrientation
    {
        public:
            static std::shared_ptr<PageOrientation> create(const int orientation);
            virtual const std::string getOrientation() const = 0;
    };

    class PortraitOrientation : public PageOrientation
    {
        public:
            virtual ~PortraitOrientation() {}
            virtual const std::string getOrientation() const override
            {
                return u8"Portrait";
            }
    };

    class LandscapeOrientation : public PageOrientation
    {
        public:
            virtual ~LandscapeOrientation() {}
            virtual const std::string getOrientation() const override
            {
                return u8"Landscape";
            }
    };

    class ReverseLandscapeOrientation : public PageOrientation
    {
        public:
            virtual ~ReverseLandscapeOrientation() {}
            virtual const std::string getOrientation() const override
            {
                return u8"Reverse Landscape";
            }
    };

}
