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
             m_dialogSettings(m_settings), m_layout(*this), m_basic(*this), 
             m_basicLayout(m_basic),
             m_tabbar(*this), m_printerGroup(m_basic),
             m_printerLabel(m_printerGroup),
             m_rangeGroup(m_basic),
             m_rangeLayout(m_rangeGroup),
             m_allPages(m_rangeGroup), m_currentPage(m_rangeGroup),
             m_selection(m_rangeGroup), m_pages(m_rangeGroup),
             m_pagesBox(m_rangeGroup)
    {
        caption(u8"Print");
        m_layout.div(string("vert gap=10 margin=5") +
            "<<tab> weight=20>" +
            "<<tabframe> weight=88%>" +
            "<weight=5>" +
            "<gap=10 <weight=50%><cancel><weight=10><print> weight=10%>");

        m_tabbar.append(u8"Basic", m_basic);
        m_layout["tab"] << m_tabbar;
        buildGeneralTab();
        m_layout["tabframe"] << m_basic;
        m_layout.collocate();

//        select_printer();
    }

    void PrintDialog::buildGeneralTab()
    {
        m_basicLayout.div(string("vertical gap=10") +
            "<<printerGroup weight=48%><><paperGroup weight=48%> weight=30%>" +
            "<weight=10>" +
            "<<range weight=48%><weight=10><copies weight=48%> weight=22%>");

        buildPrinterGroup();
        m_basicLayout["printerGroup"] << m_printerGroup;
        
        buildRangeGroup();
        m_basicLayout["range"] << m_rangeGroup;


        m_basicLayout.collocate();
    }

    void PrintDialog::buildPrinterGroup()
    {
        m_printerGroup.caption(u8"Printer");

        auto div = string("vertical gap=10") +
            "<weight=10>" +
            "<<weight=10><printerLabel weight=30%><><printerList><> weight=20%>";
        m_printerGroup.div(div.c_str());

            buildPrinterLabel();
            m_printerGroup["printerLabel"] << m_printerLabel;

    }

    void PrintDialog::buildPrinterLabel()
    {
        m_printerLabel.caption(u8"Printer:");
    }

/*    void PrintDialog::buildPrinterListbox()
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
    }*/

    void PrintDialog::printer_selected(size_t pos)
    {
        m_dialogSettings.set_printer(pos);
    }

    void PrintDialog::buildRangeGroup()
    {
        m_rangeGroup.caption(u8"Range");
        string layout(string("vertical gap=10") +
            "<weight=25>" +
            "<<weight=30><allPages weight=35%><> weight=25>" +
            "<<weight=30><currentPage weight=35%><> weight=25> " +
            "<<weight=30><selection weight=35%><> weight=25>" +
            "<<weight=30><pages weight=35%><weight=10><pagesList weight=50%><> weight=25>");
        m_rangeLayout.div(layout.c_str());
        buildAllPagesCheckbox();
        m_rangeLayout["allPages"] << m_allPages;
        buildCurrentPageCheckbox();
        m_rangeLayout["currentPage"] << m_currentPage;
        buildSelectionCheckbox();
        m_rangeLayout["selection"] << m_selection;
        buildPagesCheckbox();
        m_rangeLayout["pages"] << m_pages;
        buildPagesBox();
        m_rangeLayout["pagesList"] << m_pagesBox;
    }

    void PrintDialog::buildAllPagesCheckbox()
    {
        m_allPages.caption(u8"All Pages");
        m_allPages.enabled(true);
        m_rangeRadioGroup.add(m_allPages);
    }

    void PrintDialog::buildCurrentPageCheckbox()
    {
        m_currentPage.caption(u8"Current Page");
        m_currentPage.enabled(false);
        m_rangeRadioGroup.add(m_currentPage);
    }

    void PrintDialog::buildSelectionCheckbox()
    {
        m_selection.caption(u8"Selection");
        m_selection.enabled(false);
        m_rangeRadioGroup.add(m_selection);
    }

    void PrintDialog::buildPagesCheckbox()
    {
        m_pages.caption(u8"Pages:");
        m_pages.enabled(true);
        m_rangeRadioGroup.add(m_pages);
    }

    void PrintDialog::buildPagesBox()
    {
        m_pagesBox.editable(true);
        m_pagesBox.multi_lines(false);
        m_pagesBox.indention(false);
    }

    void PrintDialog::run()
    {
        modality();
    }
}
