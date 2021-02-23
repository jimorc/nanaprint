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
#include <set>
#include <vector>
#include <memory>
#include <iostream>

namespace nanaprint
{
    class side
    {
        public:
            side();
            side(const std::string& side);
            virtual ~side() {}
            const std::string& getSide() const { return m_side; }
        private:
            std::string m_side;
    };

    std::ostream& operator<<(std::ostream& os, const side& side);

    class Sides
    {
        public:
            Sides() {}
            virtual ~Sides() {}
            void addSide(const std::string& side);
            const std::vector<std::shared_ptr<side>> getSides() const;
        private:
            std::set<std::shared_ptr<side>> m_sides;
    };

    std::ostream& operator<<(std::ostream& os, const Sides& side);
}