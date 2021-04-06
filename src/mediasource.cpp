/**
 *  \brief A Media source class
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/mediasource.cpp
 */

#include "mediasource.h"

using namespace std;

namespace nanaprint
{
    media_source::media_source(const string& source) : nanaprint_value(source) {}

    std::ostream& operator<<(std::ostream& os, const media_source& source)
    {
        os << "    " << source.get_value() << '\n';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const media_sources& sources)
    {
        os << "Media Sources:\n";
        auto srcs = sources.get_values();
        if(srcs.size() == 0)
        {
            os << "    None\n";
        }
        else
        {
            for (auto source: srcs)
            {
                os << "    " << source.get_value() << '\n';
            }
        }
        return os;
    }
}