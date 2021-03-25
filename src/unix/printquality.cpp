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
    print_quality::print_quality(const string& quality): nanaprint_value(quality)
    {}
    
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

    bool print_qualities::contains_quality(const std::string& quality) const
    {
        vector<print_quality> qualities = get_values();
        for (auto& qual : qualities)
        {
            if (qual.get_value() == quality)
            {
                return true;
            }
        }
        return false;
    }

    std::ostream& operator<<(std::ostream& os, print_qualities& qualities)
    {
        os << u8"Print Qualities:\n";
        if (qualities.size() == 0)
        {
            os << u8"    None\n";
        }
        else
        {
            for (const auto& quality : qualities)
            {
            os << "    " << quality.get_value() << '\n';
            }
        }
        return os;
    }
}