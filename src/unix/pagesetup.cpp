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
        layout.div(string("vert ") +
            "<weight=5%>" +
            "<<weight=5%><formatfor weight=30%><printer weight=60%><weight=5%> weight=15%>" +
            "<weight=5%>"
            "<<weight=5%><papersize weight=30%><papersizes><weight=5%> weight=15%>" + 
            "<weight=5%>" +
            "<weight=10%>" +
            "<weight=5%>" +
            "<weight=15%>" +
            "<weight=5%>" +
            "<weight=15%>" +
            "<weight=5%>"
        );

        label formatFor(*this);
        formatFor.size(nana::size{ 130, 40} );
        formatFor.text_align(align::right, align_v::center);
        formatFor.caption(u8"Format for:   ");
        formatFor.fgcolor(colors::dark_border);
        combox printerListBox(*this);
        printerListBox.size(nana::size{ 250, 25});
        printerListBox.editable(false);

        auto prs = m_printers.getPrinters();
        size_t defaultPrinter = m_printers.getDefaultPrinterNumber();
        printerListBox.push_back(u8"Sample Printer\nDescriptive Text");
        printerListBox.option(defaultPrinter);

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