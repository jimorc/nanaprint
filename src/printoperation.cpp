/**
 *  \brief A PrintOperation class
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/printoperation.cpp
 */

#include "printoperation.h"
#include "pagesetup.h"
#include "printdialog.h"

using namespace nanaprint;
using namespace std;

namespace nanaprint
{
    PrintOperation::PrintOperation(nana::form& parentForm, print_settings& settings)
        : m_parentForm(parentForm), m_printSettings(settings)
    {

    }

    DialogStatus PrintOperation::run_page_setup()
    {
        PageSetup pageSetup(m_parentForm, m_printSettings);
        pageSetup.run();
        return DialogStatus::apply;
    }

    void PrintOperation::run_print()
    {
        PrintDialog printDialog(m_parentForm, m_printSettings);
        printDialog.run();
    }
}