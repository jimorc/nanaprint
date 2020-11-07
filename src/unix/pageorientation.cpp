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
    std::shared_ptr<PageOrientation> PageOrientation::create(const int orientation)
    {
        std::shared_ptr<PageOrientation> pageOrientation;
        switch (orientation)
        {
            case PORTRAIT:
                pageOrientation = PortraitOrientation::create();
                break;
            case LANDSCAPE:
                pageOrientation = LandscapeOrientation::create();
                break;
            case REVERSE_LANDSCAPE:
                pageOrientation = ReverseLandscapeOrientation::create();
                break;
            case REVERSE_PORTRAIT:
                pageOrientation = ReversePortraitOrientation::create();
                break;
            default:
                throw invalid_argument("Invalid argument value to PageOrientation::create");
        }

        return pageOrientation;
    }

    std::shared_ptr<PortraitOrientation> PortraitOrientation::create()
    {
        return make_unique<PortraitOrientation>(PortraitOrientation());
    }

    std::shared_ptr<LandscapeOrientation> LandscapeOrientation::create()
    {
        return make_unique<LandscapeOrientation>(LandscapeOrientation());
    }

    std::shared_ptr<ReverseLandscapeOrientation> ReverseLandscapeOrientation::create()
    {
        return make_unique<ReverseLandscapeOrientation>(ReverseLandscapeOrientation());
    }

    std::shared_ptr<ReversePortraitOrientation> ReversePortraitOrientation::create()
    {
        return make_unique<ReversePortraitOrientation>(ReversePortraitOrientation());
    }

    ostream& operator<<(ostream& os, const PageOrientation& orientation)
    {
        os << orientation.getOrientation();
        return os;
    }


    void PageOrientations::addOrientation(int orientation)
    {
        m_orientations.insert(PageOrientation::create(orientation));
    }

    std::vector<std::string> PageOrientations::getOrientations()
    {
        std::vector<std::string> orientations;
        for (auto orientation : m_orientations)
        {
            orientations.push_back(orientation->getOrientation());
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
        if (orientations.containsOrientation(u8"Portrait"))
        {
            os << u8"    Portrait\n"; 
        }
        if (orientations.containsOrientation(u8"Landscape"))
        {
            os << u8"    Landscape\n";
        }
        if (orientations.containsOrientation(u8"Reverse Landscape"))
        {
            os << u8"    Reverse Landscape\n";
        }
        if (orientations.containsOrientation(u8"Reverse Portrait"))
        {
            os << u8"    Reverse Portrait\n";
        }

        return os;
    }
}
