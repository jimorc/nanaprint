/**
 *  \file printer.h
 *  \brief This file provides printer class and data structures required by nanaprint
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

#include <memory>
#include <cups/cups.h>

namespace nanaprint
{
    class Printer
    {
        public:
             virtual ~Printer() {}
             static std::shared_ptr<Printer> create(cups_dest_t* dest);

             cups_dest_t* getDest() { return m_dest; }

        protected:
            Printer(cups_dest_t* dest);

        private:
            cups_dest_t* m_dest;
    };
}

