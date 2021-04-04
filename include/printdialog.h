#ifndef NANAPRINT_PRINTDIALOG_H
#define NANAPRINT_PRINTDIALOG_H

/**
 *  \file printdialog.h
 *  \brief This file provides PrintDialog class required by nanaprint
 *
 *	This header file is used in both Unix and Win32 implementations
 *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020-2021 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/tabbar.hpp>
#include "nanaprint.h"
#include "printsettings.h"
#include "printdialogsettings.h"
#include "printers.h"
#include "basicpanel.h"

namespace nanaprint
{
    class PrintDialog : nana::form
    {
        public:
            PrintDialog(nana::form& parent, print_settings& settings);
            virtual ~PrintDialog() {}
            void run();
        private:
            void buildBasicTab();
            print_settings& m_settings;
            PrintDialogSettings m_dialogSettings;

            nana::place m_layout;
            nana::tabbar<std::string> m_tabbar;
            basic_panel m_basic;
    };
}

#endif  // NANAPRINT_PRINTDIALOG_H
