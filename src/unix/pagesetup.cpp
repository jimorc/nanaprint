/**
 *  \brief A PageSetup class
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/pagesetup.cpp
 */

#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/combox.hpp>
#include "pagesetup.h"

using namespace std;
using namespace nana;
using namespace nanaprint;

namespace nanaprint
{
    PageSetup::PageSetup(nana::form& parent, Printers& printers) 
        : form(parent, {500, 250}), m_printers(printers)
    {
        caption(u8"Page Setup");
        place layout(*this);
        layout.div(string("vert <<formatfor weight=30%><printer weight=60%><> weight=20%><<papersize weight=30%>") +
            "<papersizes> weight=20%><weight=20%><weight=20%><weight=20%>");

        label formatFor(*this);
        formatFor.size(nana::size{ 130, 40} );
        formatFor.text_align(align::right, align_v::center);
        formatFor.caption(u8"Format for:   ");
        formatFor.fgcolor(colors::grey);
        combox printerListBox(*this);
        printerListBox.size(nana::size{ 250, 25});

        auto prs = m_printers.getPrinters();
        for (auto printer: prs)
        {
            printerListBox.push_back(printer->getName());
        }

        layout["formatfor"] << formatFor;
        layout["printer"] << printerListBox;

        label paperSize(*this);
        paperSize.caption(u8"Paper size:   ");
        paperSize.text_align(align::right, align_v::center);
        paperSize.fgcolor(colors::dark_border);
        
        layout["papersize"] << paperSize;

        layout.collocate();
        modality();


    }
}