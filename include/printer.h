#pragma(once)
/**
 *  \file printer.h
 *  \brief This file provides printer class and data structures required by nanaprint
 *
 *	This header file is used in both Unix and Win32 implementations
 *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#include <memory>
#include <string>
#include <map>
#include <optional>
#include <cups/cups.h>
#include "mediasizes.h"
#include "pageorientation.h"
#include "printquality.h"
#include "finishings.h"
#include "mediasource.h"
#include "mediatype.h"
#include "colormode.h"
#include "side.h"

namespace nanaprint
{
    class Printer
    {
        public:
            virtual ~Printer() {}
            static std::shared_ptr<Printer> create(cups_dest_t* dest);

            cups_dest_t* get_dest() const noexcept { return m_dest; }
            const std::string get_name() const { return std::string(m_dest->name); }
            bool is_default() const noexcept { return m_dest->is_default; }
            std::map<std::string, std::string> getOptions();
            const media_sizes& get_media_sizes() const noexcept;
            const std::optional<media_size>& get_default_media_size() const noexcept;
            bool canPrintMultipleCopies() const;
            const finishings& get_finishings() const noexcept;
            const finishings& get_default_finishings() const noexcept;
            const media_sources get_media_sources() const noexcept;
            const std::optional<media_source>& get_default_media_source() const noexcept;
            const media_types& get_media_types() const noexcept;
            const std::optional<media_type>& get_default_media_type() const noexcept;
            const page_orientations& get_orientations() const noexcept;
            const std::optional<page_orientation>& get_default_orientation() const noexcept;
            const color_modes& get_color_modes() const noexcept;
            const std::optional<color_mode>& getDefaultColorMode();
            print_qualities& getPrintQualities();
            const std::optional<print_quality>& getDefaultPrintQuality();
            sides& getSides();
            const std::optional<side>& getDefaultSide();

            std::string get_printer_state() const;
            std::string get_printer_make_and_model();
            std::string get_printer_location();
            std::string get_printer_info();

        protected:
            Printer(cups_dest_t* dest);

        private:
            const std::string get_printer_state_string(std::string value) const;
            const std::string get_printer_type_string(const std::string& value) const;
            void populate_media_sizes();
            void populate_default_media_size();
            void populate_finishings();
            void set_finishing(int finishing);
            void populate_default_finishings();
            void populate_media_sources();
            void populate_default_media_source();
            void populate_media_types();
            void populate_default_media_type();
            void populate_orientations();
            void populate_default_orientation();
            void populate_color_modes();
            void populateDefaultColorMode();
            void populatePrintQualities();
            void populateDefaultPrintQuality();
            void populateSides();
            void populateDefaultSide();

            cups_dest_t* m_dest;
            media_sizes m_mediaSizes;

            media_sources m_mediaSources;
            media_types m_mediaTypes;
            page_orientations m_orientations;
            color_modes m_colorModes;
            bool m_gotPrintQualities;
            print_qualities m_printQualities;
            bool m_gotSides;
            sides m_sides;
            finishings m_finishings;

            std::optional<media_size> m_defaultMediaSize;
            std::optional<media_source> m_defaultMediaSource;
            std::optional<media_type> m_defaultMediaType;
            std::optional<page_orientation> m_defaultOrientation;
            bool m_gotDefaultColorMode;
            std::optional<color_mode> m_defaultColorMode;
            bool m_gotDefaultPrintQuality;
            std::optional<print_quality> m_defaultPrintQuality;
            bool m_gotDefaultSide;
            std::optional<side> m_defaultSide;
            finishings m_defaultFinishings;
    };
}
