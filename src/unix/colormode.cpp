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
    color_mode::color_mode() : m_colorMode("None")
    {

    }

    color_mode::color_mode(const string& cmode) : m_colorMode(cmode)
    {

    }

    std::ostream& operator<<(std::ostream& os, const color_mode& cmode)
    {
        os << "    " << cmode.get_mode() << '\n';
        return os;
    }

    void color_modes::add_mode(const std::string& cmode)
    {
        m_colorModes.push_back(cmode);
    }

    const std::vector<color_mode>& color_modes::getColorModes() const
    {
        return m_colorModes;
    }

    std::ostream& operator<<(std::ostream& os, const color_modes& cmode)
    {
        os << "Color Modes:\n";
        for (auto& mode: cmode.getColorModes())
        {
            os << mode;
        }
        return os;
    }

    color_mode& color_modes::operator[](size_t pos)
    {
        return m_colorModes[pos];
    }

    const color_mode& color_modes::operator[](size_t pos) const
    {
        return m_colorModes[pos];
    }

    color_mode& color_modes::at(size_t pos)
    {
        if(pos >= m_colorModes.size())
        {
            throw out_of_range("Out of range");
        }
        return m_colorModes[pos];
    }

    const color_mode& color_modes::at(size_t pos) const
    {
        if(pos >= m_colorModes.size())
        {
            throw out_of_range("Out of range");
        }
        return m_colorModes[pos];
    }
}

