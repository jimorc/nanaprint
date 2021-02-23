#pragma(once)
/**
 *  \file side.h
 *  \brief This file provides Side and Sides classes required by nanaprint
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
#include <vector>
#include <memory>
#include <iostream>
#include "values.h"

namespace nanaprint
{
    class side : public nanaprint_value<std::string>
    {
        public:
            side(const std::string& side);
            virtual ~side() {}
    };

    std::ostream& operator<<(std::ostream& os, const side& side);

    class sides : public nanaprint_values<side>
    {
        public:
            sides() {}
            virtual ~sides() {}
            void addSide(const std::string& side);
    };

    std::ostream& operator<<(std::ostream& os, const sides& sids);
}