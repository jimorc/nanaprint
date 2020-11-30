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

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/group.hpp>
#include "pagesetup.h"

using namespace std;
using namespace nana;
using namespace nanaprint;

namespace nanaprint
{
    PageSetup::PageSetup(nana::form& parent, PrintSettings& settings) 
        : form(parent, {500, 500}), m_settings(settings), m_layout(*this),
            m_printerGroup(*this), m_printerNameLabel(m_printerGroup), m_printerCombox(m_printerGroup),
            m_printerStatusLabel(m_printerGroup), m_printerStatus(m_printerGroup),
            m_printerTypeLabel(m_printerGroup), m_printerType(m_printerGroup),
            m_printerWhereLabel(m_printerGroup), m_printerWhere(m_printerGroup),
            m_printerCommentLabel(m_printerGroup), m_printerComment(m_printerGroup)

    {
        caption(u8"Page Setup");
        m_layout.div(string("vert gap=10 margin=5") +
            "<printer weight=50%>");

        buildPrinterGroup();
        m_layout["printer"] << m_printerGroup;
        
        m_layout.collocate();
     }

    void PageSetup::buildPrinterGroup()
    {
        m_printerGroup.caption("Printer");
        string groupDiv = string("vert gap=5 margin=0 ") +
            "<<weight=10><name weight=20%><printerCombox><weight=10> weight=30>" +
            "<<weight=10><status weight=20%><printerStatus><weight=10> weight=30>" +
            "<<weight=10><type weight=20%><printerType><weight=10> weight=20>" +
            "<<weight=10><where weight=20%><printerWhere><weight=10> weight=20>" +
            "<<weight=10><comment weight=20%><printerComment><weight=10> weight=40>";        
        m_printerGroup.div(groupDiv.c_str());

        buildPrinterNameLabel();
        m_printerGroup["name"] << m_printerNameLabel;

        buildPrinterCombox();
        m_printerGroup["printerCombox"] << m_printerCombox;

        buildPrinterStatusLabel();
        m_printerGroup["status"] << m_printerStatusLabel;

        buildPrinterTypeLabel();
        m_printerGroup["type"] << m_printerTypeLabel;

        buildPrinterWhereLabel();
        m_printerGroup["where"] << m_printerWhereLabel;

        buildPrinterCommentLabel();
        m_printerGroup["comment"] << m_printerCommentLabel;
    }

    void PageSetup::buildPrinterNameLabel()
    {
        m_printerNameLabel.caption("Name:");
        m_printerNameLabel.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterCombox()
    {
        m_printerCombox.editable(false);
        auto printers = m_printers.getPrinters();
        for (auto& printer: printers)
        {
            m_printerCombox.push_back(printer->getName());
        }

        m_printerCombox.events().selected( [this](const arg_combox& ar_cbx) {
            printer_selected(ar_cbx);
        });

        size_t defaultPrinter = m_printers.getDefaultPrinterNumber();
        m_printerCombox.option(defaultPrinter);
    }

    void PageSetup::buildPrinterStatusLabel()
    {
        m_printerStatusLabel.caption("Status:");
        m_printerStatusLabel.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterStatus(size_t printer)
    {
        m_printerStatus.caption(m_printers.getPrinters()[printer]->get_printer_state());
        m_printerStatus.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterTypeLabel()
    {
        m_printerTypeLabel.caption("Type:");
        m_printerTypeLabel.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterType(size_t printer)
    {
        m_printerType.caption(m_printers.getPrinters()[printer]->get_printer_make_and_model());
        m_printerType.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterWhereLabel()
    {
        m_printerWhereLabel.caption("Location:");
        m_printerWhereLabel.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterWhere(size_t printer)
    {
        m_printerWhere.caption(m_printers.getPrinters()[printer]->get_printer_location());
        m_printerWhere.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterCommentLabel()
    {
        m_printerCommentLabel.caption("Comment:");
        m_printerCommentLabel.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterComment(size_t printer)
    {
        m_printerComment.caption(m_printers.getPrinters()[printer]->get_printer_info());
        m_printerComment.text_align(align::left, align_v::center);
    }

/*
    void PageSetup::setupPaperSizeLabel()
    {
        m_paperSizeLabel.size(nana::size{ 130, 40} );
        m_paperSizeLabel.caption(u8"Paper size:   ");
//        m_paperSizeLabel.text_align(align::right, align_v::center);
        m_paperSizeLabel.fgcolor(colors::dark_border);
    }

    void PageSetup::setupPaperSizeComBox()
    {
        m_paperSizeCombox.size(nana::size{ 250, 25});
        m_paperSizeCombox.editable(false);
    }

*/
    void PageSetup::printer_selected(const arg_combox &ar_cbx)
    {
        size_t printer = m_printerCombox.option();
        m_settings.set_printer(printer);
        buildPrinterStatus(printer);
        m_printerGroup["printerStatus"] << m_printerStatus;
        buildPrinterType(printer);
        m_printerGroup["printerType"] << m_printerType;
        buildPrinterWhere(printer);
        m_printerGroup["printerWhere"] << m_printerWhere;
        buildPrinterComment(printer);
        m_printerGroup["printerComment"] << m_printerComment;

/*        auto ptr = m_printers.getPrinters()[printer];
        auto paperSizes = ptr->getMediaSizes();
        m_paperSizeCombox.clear();
        for (size_t i = 0; i < paperSizes.getSize(); ++i)
        {
            m_paperSizeCombox.push_back(paperSizes.getMediaSizes()[i]->getTranslatedName());
        }
        auto defaultPaperSize = paperSizes.getMediaSizeNumber(m_settings.get_media_size());
        m_paperSizeCombox.option(defaultPaperSize); */
    }

    DialogStatus PageSetup::run()
    {
         modality();
        return DialogStatus::apply;
    }
}