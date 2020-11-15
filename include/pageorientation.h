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
            PageOrientation();
            PageOrientation(int orientation);
            virtual ~PageOrientation() {}
            const std::string& getOrientation() const;

        private:
            std::string m_orientation;
    };

    std::ostream& operator<<(std::ostream& os, const PageOrientation& orientation);

    class PageOrientations
    {
        public:
            PageOrientations() {}
            virtual ~PageOrientations() {}
            void addOrientation(int orientation);
            std::vector<std::shared_ptr<PageOrientation>> getOrientations() const;
            bool containsOrientation(const std::string& orientation) const;
        private:
            std::set<std::shared_ptr<PageOrientation>> m_orientations;
    };

    std::ostream& operator<<(std::ostream& os, const PageOrientations& orientations);

}
