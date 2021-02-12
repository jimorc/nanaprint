/**
 *  \brief ColorMode and ColorModes classes
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/colormode.cpp
 */

#include <iostream>
#include "colormode.h"

using namespace nanaprint;
using namespace std;

namespace nanaprint
{
    std::ostream& operator<<(std::ostream& os, const color_mode& cmode)
    {
        auto mode = cmode.get_value();
        os << "    ";
        os << ((mode) ? mode.value() : "None") << '\n';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const color_modes& cmode)
    {
        os << "Color Modes:\n";
        for (auto& mode: cmode.get_values())
        {
            os << mode;
        }
        return os;
    }

    color_mode& color_modes::operator[](size_t pos)
    {
        return m_values[pos];
    }

    const color_mode& color_modes::operator[](size_t pos) const
    {
        return m_values[pos];
    }

    color_mode& color_modes::at(size_t pos)
    {
        if(pos >= m_values.size())
        {
            throw out_of_range("Out of range");
        }
        return m_values[pos];
    }

    const color_mode& color_modes::at(size_t pos) const
    {
        if(pos >= m_values.size())
        {
            throw out_of_range("Out of range");
        }
        return m_values[pos];
    }
}

