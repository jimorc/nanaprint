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
    PrintDialogSettings::PrintDialogSettings(print_settings& settings)
        :   m_settings(settings),
            m_printer(settings.get_printer()), m_borderless(settings.get_borderless()),
            m_mediaSize(settings.get_media_size()), m_finishings(settings.get_finishings()),
            m_mediaSource(settings.get_media_source()), m_mediaType(settings.get_media_type()),
            m_orientation(settings.get_page_orientation()), m_colorMode(settings.get_color_mode()),
            m_printQuality(settings.get_print_quality()), m_side(settings.get_side()),
            m_canPrintMultipleCopies(settings.can_print_multiple_copies())
    {

    }

    void PrintDialogSettings::set_printer(size_t printer)
    {
        if(printer == m_printer)
            return;
        set_default_settings(printer);
    }

    // fill the print settings with the printer's defaults
    void PrintDialogSettings::set_default_settings(size_t printerNum)
    {
        m_printer = printerNum;
        auto printer = m_settings.get_printers().get_printers()[m_printer];
        set_borderless(false);
        set_media_size(printer->get_default_media_size());
        set_finishings(printer->get_default_finishings());
        set_media_source(printer->get_default_media_source());
        set_media_type(printer->get_default_media_type()),
        set_page_orientation(printer->get_default_orientation());
        set_color_mode(printer->get_default_color_mode());
        set_print_quality(printer->get_default_print_quality());
        set_side(printer->get_default_side());
        m_canPrintMultipleCopies = printer->can_print_multiple_copies();
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

    void PrintDialogSettings::set_side(const std::optional<side>& sid)
    {
        m_side = sid;
    }
}
