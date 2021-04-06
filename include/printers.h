#ifndef PRINTERS_H
#define PRINTERS_H

/**
 *  \brief A Printers class
 *
 *	This header file is used in both Unix and Win32 implementations
 *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/printers/
 */

#include <vector>
#include <memory>
#include <cups/cups.h>
#include "printer.h"


namespace nanaprint
{
   class printers
    {
        public:
            printers();
            virtual ~printers();
            std::vector<std::shared_ptr<printer>> get_printers() const { return m_printers; }
            size_t get_default_printer_number() const;
            size_t get_printer_number(const std::string& printerName) const;

        private:
            void enumerate_printers();

            std::vector<std::shared_ptr<printer>> m_printers;
    };

    std::ostream& operator<<(std::ostream& os, const printers& prtrs);
}
#endif      // PRINTERS_H