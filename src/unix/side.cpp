/**
 *  \brief Side and Sides classes
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/side.cpp
 */

#include "side.h"

using namespace nanaprint;
using namespace std;

namespace nanaprint
{
    Side::Side(const std::string& side) : m_side(side)
    {

    }

    std::ostream& operator<<(std::ostream& os, const Side& side)
    {
        os << side.getSide();
        return os;
    }

    void Sides::addSide(const std::string& side)
    {
        m_sides.insert(make_shared<Side>(Side(side)));
    }

    const std::vector<std::shared_ptr<Side>> Sides::getSides() const
    {
        vector<shared_ptr<Side>> sides;
        for (auto& side: m_sides)
        {
            sides.push_back(side);
        }
        return sides;
    }
}