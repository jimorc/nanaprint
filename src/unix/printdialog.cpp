/**
 *  \brief A PrintDialog class
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/prkintdialog.cpp
 */

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/group.hpp>
#include "printdialog.h"

using namespace std;
using namespace nana;
using namespace nanaprint;

namespace nanaprint
{
    PrintDialog::PrintDialog(form& parent, PrintSettings& settings)
        : form(parent, {500, 500}, appear::decorate<>()), m_settings(settings)
    {

    }

    void PrintDialog::run()
    {
        modality();
    }
}
