#pragma(once)
/**
 *  \file printdialog.h
 *  \brief This file provides PrintDialog class required by nanaprint
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

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/group.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/place.hpp>
#include <nanaprint.h>
#include "printsettings.h"
#include "printers.h"

namespace nanaprint
{
    class PrintDialog : nana::form
    {
        public:
            PrintDialog(nana::form& parent, PrintSettings& settings);
            virtual ~PrintDialog() {}
            void run();
        private:
            PrintSettings m_settings;
    };
}
