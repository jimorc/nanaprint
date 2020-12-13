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
    PageOrientation::PageOrientation() : m_orientation(nullopt)
    {

    }

    PageOrientation::PageOrientation(const int orientation)
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

    const std::optional<std::string>& PageOrientation::getOrientation() const
    {
        return m_orientation;
    }
    
    ostream& operator<<(ostream& os, const PageOrientation& orientation)
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
        m_orientations.insert(make_shared<PageOrientation>(PageOrientation(orientation)));
    }

    std::vector<std::shared_ptr<PageOrientation>> PageOrientations::getOrientations() const
    {
        std::vector<std::shared_ptr<PageOrientation>> orientations;
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
