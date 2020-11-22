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

#include <iostream>
#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/combox.hpp>
#include "pagesetup.h"

using namespace std;
using namespace nana;
using namespace nanaprint;

namespace nanaprint
{
    PageSetup::PageSetup(nana::form& parent, PrintSettings& settings) 
        : form(parent, {500, 250}), m_settings(settings)
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
        setupFormatForLabel(formatFor);
        layout["formatfor"] << formatFor;

        combox printerCombox(*this);
        setupPrinterComBox(printerCombox);
        layout["printer"] << printerCombox;

        label paperSize(*this);
        setupPaperSizeLabel(paperSize);       
        layout["papersize"] << paperSize;

        layout.collocate();
        modality();
    }

    void PageSetup::setupFormatForLabel(nana::label& formatLabel) const
    {
        formatLabel.size(nana::size{ 130, 40} );
        formatLabel.text_align(align::right, align_v::center);
        formatLabel.caption(u8"Format for:   ");
        formatLabel.fgcolor(colors::dark_border);
    }

    void PageSetup::setupPrinterComBox(nana::combox& box)
    {
        box.size(nana::size{ 250, 25});
        box.editable(false);

        auto prs = m_printers.getPrinters();
        for(auto& printer: prs)
        {
            box.push_back(printer->getName());
        }

        box.events().selected( [this](const arg_combox &ar_cbx) {
            this->printer_selected(ar_cbx);
        });

        size_t defaultPrinter = m_printers.getDefaultPrinterNumber();
        box.option(defaultPrinter);
   }

    void PageSetup::setupPaperSizeLabel(nana::label& paperSizeLabel) const
    {
        paperSizeLabel.size(nana::size{ 130, 40} );
        paperSizeLabel.caption(u8"Paper size:   ");
        paperSizeLabel.text_align(align::right, align_v::center);
        paperSizeLabel.fgcolor(colors::dark_border);
    }

    void PageSetup::printer_selected(const arg_combox &ar_cbx)
    {
        size_t printer = m_printers.get_printer_number(ar_cbx.widget.caption());
        cout << printer << endl;
        m_settings.set_printer(printer);
    }
}