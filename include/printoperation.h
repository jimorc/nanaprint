#ifndef NANAPRINT_PRINTOPERATION_H
#define NANAPRINT_PRINTOPERATION_H

/**
 *  \brief A PrintOperation class
 *
 *	This header file is used in both Unix and Win32 implementations
 *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/printoperation.h
 */

#include <memory>
#include <nana/gui.hpp>
#include "nanaprint.h"
#include "printers.h"
#include "printsettings.h"

namespace nanaprint
{
    class PrintOperation
    {
        public:
            PrintOperation(nana::form& parent);
            virtual ~PrintOperation() {}
            DialogStatus run_page_setup();
            void run_print();

        private:
            nana::form& m_parentForm;
            Printers m_printers;
            PrintSettings m_printSettings;
    };
}
#endif      // NANAPRINT_PRINTOPERATION_H