#pragma(once)
/**
 *  \file colormode.h
 *  \brief This file provides ColorMode and ColorModes classes required by nanaprint
 *
 *	This header file is used in both Unix and Win32 implementations
 *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#include <string>

namespace nanaprint
{
    class ColorMode
    {
        public:
            ColorMode();
            ColorMode(const std::string& colormode);
            virtual ~ColorMode() {}
            const std::string& getColorMode() const { return m_colorMode; }
        private:
            std::string m_colorMode;
    };

    std::ostream& operator<<(std::ostream& os, const ColorMode& cmode);
}
