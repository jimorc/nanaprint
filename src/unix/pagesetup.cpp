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
    PageSetup::PageSetup(nana::form& parent, PrintSettings settings) 
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
        string groupDiv = string("vert gap=10 margin=5 ") +
            "<<name weight=20%><printerCombox> weight=20>" +
            "<<status weight=20%><printerStatus>>" +
            "<<type weight=20%><printerType>>" +
            "<<where weight=20%><printerWhere>>" +
            "<<comment weight=20%><printerComment>>";        
        m_printerGroup.div(groupDiv.c_str());

        buildPrinterNameLabel();
        m_printerGroup["name"] << m_printerNameLabel;
    }

    void PageSetup::buildPrinterNameLabel()
    {
        m_printerNameLabel.caption("Name");
        m_printerNameLabel.size({100, 15});
    }

/*    void PageSetup::setupFormatForLabel()
    {
        m_formatForLabel.size(nana::size{ 130, 40} );
//        m_formatForLabel.text_align(align::right, align_v::center);
        m_formatForLabel.caption(u8"Format for:   ");
        m_formatForLabel.fgcolor(colors::dark_border);
    }

    void PageSetup::setupPrinterComBox()
    {
        m_printerCombox.size(nana::size{ 250, 25});
        m_printerCombox.editable(false);

        auto prs = m_printers.getPrinters();
        for(auto& printer: prs)
        {
            m_printerCombox.push_back(printer->getName());
        }

        m_printerCombox.events().selected( [this](const arg_combox &ar_cbx) {
            this->printer_selected(ar_cbx);
        });

        size_t defaultPrinter = m_printers.getDefaultPrinterNumber();
        m_printerCombox.option(defaultPrinter);
   }

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

    void PageSetup::printer_selected(const arg_combox &ar_cbx)
    {
        size_t printer = m_printerCombox.option();
        cout << printer << endl;
        m_settings.set_printer(printer);

        auto ptr = m_printers.getPrinters()[printer];
        auto paperSizes = ptr->getMediaSizes();
        m_paperSizeCombox.clear();
        for (size_t i = 0; i < paperSizes.getSize(); ++i)
        {
            m_paperSizeCombox.push_back(paperSizes.getMediaSizes()[i]->getTranslatedName());
        }
        auto defaultPaperSize = paperSizes.getMediaSizeNumber(m_settings.get_media_size());
        m_paperSizeCombox.option(defaultPaperSize);
    }
*/
    DialogStatus PageSetup::run()
    {
         modality();
        return DialogStatus::apply;
    }
}