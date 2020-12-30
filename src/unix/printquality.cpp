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
    PrintQuality::PrintQuality() : m_quality(u8"None")
    {

    }

    PrintQuality::PrintQuality(const int quality)
    {
        switch (quality)
        {
            case PLAIN_NORMAL:
                m_quality = u8"Plain Normal";
                break;
            case FAST:
                m_quality = u8"Fast";
                break;
            case NORMAL:
                m_quality = u8"Normal";
                break;
            case HIGH:
                m_quality = u8"High";
                break;
            case PHOTO:
                m_quality = u8"Photo";
                break;
            default:
                throw invalid_argument("Invalid argument value input to PrintQuality constructor");
        }
        
    }

    std::string PrintQuality::getPrintQuality() const
    {
        return m_quality;
    }

    std::ostream& operator<<(std::ostream& os, const PrintQuality& quality)
    {
        os << quality.getPrintQuality();
        return os;
    }

    void PrintQualities::addPrintQuality(int quality)
    {
        m_qualities.insert(make_shared<PrintQuality>(quality));
    }

    bool PrintQualities::containsPrintQuality(const std::string& quality) const
    {
        for (auto iter = m_qualities.begin(); iter != m_qualities.end(); ++iter)
        {
            if ((*iter)->getPrintQuality() == quality)
            {
                return true;
            }
        }
        return false;
    }

    std::vector<std::shared_ptr<PrintQuality>> PrintQualities::getPrintQualities() const
    {
        vector<shared_ptr<PrintQuality>> qualities;
        for (auto quality: m_qualities)
        {
            qualities.push_back(quality);
        }
        return qualities;
    }

    std::ostream& operator<<(std::ostream& os, const PrintQualities& qualities)
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