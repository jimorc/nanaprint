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
#include <iostream>
#include <set>
#include <vector>
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

            friend std::ostream& operator<<(std::ostream& os, const PageOrientation& orientation);
        protected:
            PageOrientation() {}
    };

    std::ostream& operator<<(std::ostream& os, const PageOrientation& orientation);

    class PortraitOrientation : public PageOrientation
    {
        public:
            virtual ~PortraitOrientation() {}
            static std::shared_ptr<PortraitOrientation> create();
            virtual const std::string getOrientation() const override
            {
                return u8"Portrait";
            }
        protected:
            PortraitOrientation() {}
    };

    class LandscapeOrientation : public PageOrientation
    {
        public:
            virtual ~LandscapeOrientation() {}
            static std::shared_ptr<LandscapeOrientation> create();
            virtual const std::string getOrientation() const override
            {
                return u8"Landscape";
            }
        protected:
            LandscapeOrientation() {}
    };

    class ReverseLandscapeOrientation : public PageOrientation
    {
        public:
            virtual ~ReverseLandscapeOrientation() {}
            static std::shared_ptr<ReverseLandscapeOrientation> create();
            virtual const std::string getOrientation() const override
            {
                return u8"Reverse Landscape";
            }
        protected:
            ReverseLandscapeOrientation() {}
    };

    class ReversePortraitOrientation : public PageOrientation
    {
        public:
            virtual ~ReversePortraitOrientation() {}
            static std::shared_ptr<ReversePortraitOrientation> create();
            virtual const std::string getOrientation() const override
            {
                return u8"Reverse Portrait";
            }
        protected:
            ReversePortraitOrientation() {}
    };

    class PageOrientations
    {
        public:
            PageOrientations() {}
            virtual ~PageOrientations() {}
            void addOrientation(int orientation);
            std::vector<std::string> getOrientations();
            bool containsOrientation(const std::string& orientation) const;
            friend std::ostream& operator<<(std::ostream& os, const PageOrientations& orientations);
        private:
            std::set<std::shared_ptr<PageOrientation>> m_orientations;
    };

    std::ostream& operator<<(std::ostream& os, const PageOrientations& orientations);

}
