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
    std::unique_ptr<PageOrientation> PageOrientation::create(const int orientation)
    {
        std::unique_ptr<PageOrientation> pageOrientation;
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

    std::unique_ptr<PortraitOrientation> PortraitOrientation::create()
    {
        return make_unique<PortraitOrientation>(PortraitOrientation());
    }

    std::unique_ptr<LandscapeOrientation> LandscapeOrientation::create()
    {
        return make_unique<LandscapeOrientation>(LandscapeOrientation());
    }

    std::unique_ptr<ReverseLandscapeOrientation> ReverseLandscapeOrientation::create()
    {
        return make_unique<ReverseLandscapeOrientation>(ReverseLandscapeOrientation());
    }

    std::unique_ptr<ReversePortraitOrientation> ReversePortraitOrientation::create()
    {
        return make_unique<ReversePortraitOrientation>(ReversePortraitOrientation());
    }

    ostream& operator<<(ostream& os, const PageOrientation& orientation)
    {
        os << orientation.getOrientation();
        return os;
    }

}
