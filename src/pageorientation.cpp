/**
 *  \brief page orientation class
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/pageorientation.cpp
 */

#include "pageorientation.h"

using namespace std;

namespace nanaprint
{
    page_orientation::page_orientation() : m_orientationNum(0), m_orientation(nullopt) 
    {

    }

    page_orientation::page_orientation(const int orientation) : m_orientationNum(orientation)
    {
        switch (orientation)
        {
            case PORTRAIT:
                m_orientation = u8"Portrait";
                break;
            case LANDSCAPE:
                m_orientation = u8"Landscape";
                break;
            case REVERSE_LANDSCAPE:
                m_orientation = u8"Reverse Landscape";
                break;
            case REVERSE_PORTRAIT:
                m_orientation = u8"Reverse Portrait";
                break;
            default:
                m_orientation = nullopt;
                break;
        }
    }

    int page_orientation::get_orientation_number() const
    {
        return m_orientationNum;
    }

    const std::optional<std::string>& page_orientation::get_orientation() const
    {
        return m_orientation;
    }
    
    ostream& operator<<(ostream& os, const page_orientation& orientation)
    {
        os << "    ";
        auto orient = orientation.get_orientation();
        if (orient)
        {
            os << orientation.get_orientation().value() << '\n';
        }
        else
        {
            os << "None\n";
        }
        
        return os;
    }

    bool page_orientations::contains_orientation(const std::string& orientation) const
    {
        for (auto& ortn : get_values())
        {
            if (ortn.get_orientation() == orientation)
                return true;
        }
        return false;
    }

    std::ostream& operator<<(std::ostream& os, const page_orientations& orientations)
    {
        os << u8"Page Orientations:\n";
        for (const auto& orientation: orientations.get_values())
        {
            os << orientation;
        }
        return os;
    }
}
