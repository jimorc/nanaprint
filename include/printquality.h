#pragma(once)

/**
 *  \file printquality.h
 *  \brief This file provides printquality class required by nanaprint
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

#include <memory>
#include <iostream>
#include <set>
#include <vector>
#include "values.h"

namespace nanaprint
{
    constexpr int PLAIN_NORMAL = 2;
    constexpr int FAST = 3;
    constexpr int NORMAL = 4;
    constexpr int HIGH = 5;
    constexpr int PHOTO = 6;

    class print_quality : public nanaprint_value<std::string>
    {
        public:
            print_quality();
            print_quality(const int quality);
            virtual ~print_quality() {}
    };

    std::ostream& operator<<(std::ostream& os, const print_quality& quality);
    
    class print_qualities
    {
        public:
            print_qualities() {}
            ~print_qualities() {}
            void addPrintQuality(int quality);
            bool containsPrintQuality(const std::string& quality) const;
            std::vector<std::shared_ptr<print_quality>> getPrintQualities() const;

        private:
            std::vector<std::shared_ptr<print_quality>> m_qualities;
    };


    std::ostream& operator<<(std::ostream& os, const print_qualities& qualities);
}