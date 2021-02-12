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

#include <stdexcept>
#include "pageorientation.h"

using namespace std;

namespace nanaprint
{
    page_orientation::page_orientation() : m_orientation(nullopt), m_orientationNum(0)
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

    const int page_orientation::getOrientationNumber() const
    {
        return m_orientationNum;
    }

    const std::optional<std::string>& page_orientation::getOrientation() const
    {
        return m_orientation;
    }
    
    ostream& operator<<(ostream& os, const page_orientation& orientation)
    {
        os << "    ";
        auto orient = orientation.getOrientation();
        if (orient)
        {
            os << orientation.getOrientation().value() << '\n';
        }
        else
        {
            os << "None\n";
        }
        
        return os;
    }


    void PageOrientations::addOrientation(int orientation)
    {
        m_orientations.insert(make_shared<page_orientation>(page_orientation(orientation)));
    }

    std::vector<std::shared_ptr<page_orientation>> PageOrientations::getOrientations() const
    {
        std::vector<std::shared_ptr<page_orientation>> orientations;
        for (auto orientation : m_orientations)
        {
            orientations.push_back(orientation);
        }
        return orientations;
    }

    bool PageOrientations::containsOrientation(const std::string& orientation) const
    {
        for (auto iter = m_orientations.begin(); iter != m_orientations.end(); ++iter)
        {
            if ((*iter)->getOrientation() == orientation)
                return true;
        }
        return false;
    }

    std::ostream& operator<<(std::ostream& os, const PageOrientations& orientations)
    {
        os << u8"Page Orientations:\n";
        for (const auto& orientation: orientations.getOrientations())
        {
            os << *orientation;
        }
        return os;
    }
}
