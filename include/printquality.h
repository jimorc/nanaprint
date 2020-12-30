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

namespace nanaprint
{
    constexpr int PLAIN_NORMAL = 2;
    constexpr int FAST = 3;
    constexpr int NORMAL = 4;
    constexpr int HIGH = 5;
    constexpr int PHOTO = 6;

    class PrintQuality
    {
        public:
            PrintQuality();
            PrintQuality(const int quality);
            virtual ~PrintQuality() {}
            virtual std::string getPrintQuality() const;
            
        private:
            std::string m_quality;
    };

    std::ostream& operator<<(std::ostream& os, const PrintQuality& quality);
    
    class PrintQualities
    {
        public:
            PrintQualities() {}
            ~PrintQualities() {}
            void addPrintQuality(int quality);
            bool containsPrintQuality(const std::string& quality) const;
            std::vector<std::shared_ptr<PrintQuality>> getPrintQualities() const;

        private:
            std::set<std::shared_ptr<PrintQuality>> m_qualities;
    };


    std::ostream& operator<<(std::ostream& os, const PrintQualities& qualities);
}