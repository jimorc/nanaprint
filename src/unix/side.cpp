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
    side::side(const std::string& sid) : nanaprint_value(sid)
    {

    }

    std::ostream& operator<<(std::ostream& os, const side& side)
    {
        os << side.get_value();
        return os;
    }

    void sides::addSide(const std::string& sid)
    {
        m_sides.insert(make_shared<side>(side(sid)));
    }

    const std::vector<std::shared_ptr<side>> sides::getSides() const
    {
        vector<shared_ptr<side>> sides;
        for (auto& side: m_sides)
        {
            sides.push_back(side);
        }
        return sides;
    }

    std::ostream& operator<<(std::ostream& os, const sides& sides)
    {
        os << "Sides:\n";
        auto sids = sides.getSides();
        if(sids.empty())
        {
            os << "    None\n";
        }
        else
        {
            for (auto& side: sids)
            {
                os << "    " << *side << '\n';
            }
        }
        return os;
    }
}