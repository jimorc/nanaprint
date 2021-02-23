/**
 *  \brief print quality class
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/printquality.cpp
 */

#include "printquality.h"

using namespace std;

namespace nanaprint
{
    print_quality::print_quality() : nanaprint_value(u8"None")
    {

    }

    print_quality::print_quality(const int quality) : nanaprint_value("")
    {
        switch (quality)
        {
            case PLAIN_NORMAL:
                set_value(u8"Plain Normal");
                break;
            case FAST:
                set_value(u8"Fast");
                break;
            case NORMAL:
                set_value(u8"Normal");
                break;
            case HIGH:
                set_value(u8"High");
                break;
            case PHOTO:
                set_value(u8"Photo");
                break;
            default:
                throw invalid_argument("Invalid argument value input to PrintQuality constructor");
        }
        
    }

    std::ostream& operator<<(std::ostream& os, const print_quality& quality)
    {
        os << quality.get_value();
        return os;
    }

    void print_qualities::addPrintQuality(int quality)
    {
        m_qualities.push_back(make_shared<print_quality>(quality));
    }

    bool print_qualities::containsPrintQuality(const std::string& quality) const
    {
        std::vector<shared_ptr<print_quality>> qualities = getPrintQualities();
        for (auto& qual : qualities)
        {
            if (qual->get_value() == quality)
            {
                return true;
            }
        }
        return false;
    }

    std::vector<std::shared_ptr<print_quality>> print_qualities::getPrintQualities() const
    {
        return m_qualities;
    }

    std::ostream& operator<<(std::ostream& os, const print_qualities& qualities)
    {
        os << "Print Qualities:\n";
        if (qualities.containsPrintQuality(u8"Plain Normal"))
        {
            os << u8"    Plain Normal\n"; 
        }
        if (qualities.containsPrintQuality(u8"Fast"))
        {
            os << u8"    Fast\n";
        }
        if (qualities.containsPrintQuality(u8"Normal"))
        {
            os << u8"    Normal\n";
        }
        if (qualities.containsPrintQuality(u8"High"))
        {
            os << u8"    High\n";
        }
        if (qualities.containsPrintQuality(u8"Photo"))
        {
            os << u8"    Photo\n";
        }

        return os;

    }
}