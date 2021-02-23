/**
 *  \brief A PrintDialogSettings class
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/printsettings.cpp
 */

#include <climits>
#include "printdialogsettings.h"

using namespace std;
using namespace nanaprint;

namespace nanaprint
{
    PrintDialogSettings::PrintDialogSettings(PrintSettings& settings)
        :   m_settings(settings),
            m_printer(settings.get_printer()), m_borderless(settings.get_borderless()),
            m_mediaSize(settings.get_media_size()), m_finishings(settings.get_finishings()),
            m_mediaSource(settings.get_media_source()), m_mediaType(settings.get_media_type()),
            m_orientation(settings.get_page_orientation()), m_colorMode(settings.get_color_mode()),
            m_printQuality(settings.get_print_quality()), m_side(settings.get_side()),
            m_canPrintMultipleCopies(settings.can_print_multiple_copies())
    {

    }

    void PrintDialogSettings::set_printer(int printer)
    {
        if(printer == m_printer)
            return;
        set_default_settings(printer);
    }

    // fill the print settings with the printer's defaults
    void PrintDialogSettings::set_default_settings(int printerNum)
    {
        m_printer = printerNum;
        auto printer = m_settings.get_printers().getPrinters()[m_printer];
        set_borderless(false);
        set_media_size(printer->getDefaultMediaSize());
        set_finishings(printer->getDefaultFinishings());
        set_media_source(printer->getDefaultMediaSource());
        set_media_type(printer->getDefaultMediaType()),
        set_page_orientation(printer->getDefaultOrientation());
        set_color_mode(printer->getDefaultColorMode());
        set_print_quality(printer->getDefaultPrintQuality());
        set_side(printer->getDefaultSide());
        m_canPrintMultipleCopies = printer->canPrintMultipleCopies();
    }

    void PrintDialogSettings::set_borderless(bool borderless)
    {
        m_borderless = borderless;
    }

    void PrintDialogSettings::set_media_size(const std::optional<media_size>& mediaSize)
    {
        m_mediaSize = mediaSize;
    }

    void PrintDialogSettings::set_finishings(const finishings finishings)
    {
        m_finishings = finishings;
    }

    void PrintDialogSettings::set_media_source(const std::optional<media_source>& source)
    {
        m_mediaSource = source;
    }

    void PrintDialogSettings::set_media_source(const std::string& source)
    {
        m_mediaSource = source;
    }
    
    void PrintDialogSettings::set_media_type(const std::optional<media_type>& mediaType)
    {
        m_mediaType = mediaType;
    }

    void PrintDialogSettings::set_page_orientation(const optional<page_orientation>& orientation)
    {
        m_orientation = orientation;
    }

    void PrintDialogSettings::set_color_mode(const std::optional<color_mode>& colorMode)
    {
        m_colorMode = colorMode;
    }

    void PrintDialogSettings::set_print_quality(const std::optional<print_quality>& quality)
    {
        m_printQuality = quality;
    }

    void PrintDialogSettings::set_side(const std::optional<Side>& side)
    {
        m_side = side;
    }
}
