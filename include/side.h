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
    class Side
    {
        public:
            Side(const std::string& side);
            virtual ~Side() {}
            const std::string& getSide() const { return m_side; }
        private:
            std::string m_side;
    };

    std::ostream& operator<<(std::ostream& os, const Side& side);

    class Sides
    {
        public:
            Sides() {}
            virtual ~Sides() {}
            void addSide(const std::string& side);
            const std::vector<std::shared_ptr<Side>> getSides() const;
        private:
            std::set<std::shared_ptr<Side>> m_sides;
    };

    std::ostream& operator<<(std::ostream& os, const Sides& side);
}