#ifndef NANAPRINT_PAGEORIENTATION_H
#define NANAPRINT_PAGEORIENTATION_H

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
#include <vector>
#include <optional>
#include "values.h"

namespace nanaprint
{
    constexpr int PORTRAIT = 3;
    constexpr int LANDSCAPE = 4;
    constexpr int REVERSE_LANDSCAPE = 5;
    constexpr int REVERSE_PORTRAIT = 6;
    
    class page_orientation
    {
        public:
            page_orientation();
            page_orientation(size_t orientation);
            virtual ~page_orientation() {}
            const std::optional<std::string>& get_orientation() const;
            size_t get_orientation_number() const;

        private:
            size_t m_orientationNum;
            std::optional<std::string> m_orientation;
    };

    std::ostream& operator<<(std::ostream& os, const page_orientation& orientation);

    class page_orientations : public nanaprint_values<page_orientation>
    {
        public:
            page_orientations() {}
            virtual ~page_orientations() {}
            bool contains_orientation(const std::string& orientation) const;
    };

    std::ostream& operator<<(std::ostream& os, const page_orientations& orientations);

}

#endif      // NANAPRINT_PAGEORIENTATION_H