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
    std::shared_ptr<PageOrientation> PageOrientation::create(const int orientation)
    {
        std::shared_ptr<PageOrientation> pageOrientation;
        switch (orientation)
        {
            case PORTRAIT:
                pageOrientation = std::make_shared<PortraitOrientation>(PortraitOrientation());
                break;
        }

        return pageOrientation;
    }
}
