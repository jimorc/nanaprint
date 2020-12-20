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

#include <string>
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
        : form(parent, {750, 500}, appear::decorate<>()), m_settings(settings),
             m_dialogSettings(m_settings), m_layout(*this), m_general(*this), 
             m_generalLayout(m_general),
             m_tabbar(*this), m_printerListbox(m_general)
    {
        caption(u8"Print");
        m_layout.div(string("vert gap=10 margin=5") +
            "<<tab> weight=20>" +
            "<<tabframe> weight=88%>" +
            "<weight=5>" +
            "<gap=10 <weight=50%><cancel><weight=10><print> weight=10%>");

        m_tabbar.append(u8"General", m_general);
//        m_tabbar.activated(0);
        m_layout["tab"] << m_tabbar;
        buildGeneralTab();
        m_layout["tabframe"] << m_general;
        m_layout.collocate();

        select_printer();
    }

    void PrintDialog::buildGeneralTab()
    {
        m_generalLayout.div(string("vertical gap=10") +
            "<<printers> weight=70%>");

        buildPrinterListbox();
        m_generalLayout["printers"] << m_printerListbox;

        m_generalLayout.collocate();
    }

    void PrintDialog::buildPrinterListbox()
    {
        m_printerListbox.enable_single(true, false);
        m_printerListbox.append_header(u8"Printer", 200);
        m_printerListbox.append_header(u8"Location", 200);
        m_printerListbox.append_header(u8"Status", 330);

        auto printers = m_settings.getPrinters();
        for (auto printer: printers)
        {
            auto name = printer->getName();
            auto location = printer->get_printer_location();
            auto status = printer->get_printer_state();
            auto cat = m_printerListbox.at(0);
            cat.append({name, location, status});
        }
        m_printerListbox.events().selected([this](const arg_listbox& arg){
            printer_selected(arg.item.pos().item);
        });
    }

    void PrintDialog::select_printer()
    {
        auto selectedPrinter = m_printerListbox.at(m_dialogSettings.get_printer());
        selectedPrinter.select(true);
    }

    void PrintDialog::printer_selected(size_t pos)
    {

    }

    void PrintDialog::run()
    {
        modality();
    }
}
