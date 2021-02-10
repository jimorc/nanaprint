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
    ColorMode::ColorMode() : m_colorMode("None")
    {

    }

    ColorMode::ColorMode(const string& cmode) : m_colorMode(cmode)
    {

    }

    std::ostream& operator<<(std::ostream& os, const ColorMode& cmode)
    {
        os << "    " << cmode.getColorMode() << '\n';
        return os;
    }

    void ColorModes::addColorMode(const std::string& cmode)
    {
        m_colorModes.push_back(make_shared<ColorMode>(cmode));
    }

    const std::vector<std::shared_ptr<ColorMode>>& ColorModes::getColorModes() const
    {
        return m_colorModes;
    }

    std::ostream& operator<<(std::ostream& os, const ColorModes& cmode)
    {
        os << "Color Modes:\n";
        for (auto& mode: cmode.getColorModes())
        {
            os << *mode;
        }
        return os;
    }
}

