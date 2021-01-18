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

            std::string getName() { return std::string(m_dest->name); }
            bool isDefault() { return m_dest->is_default; }
            std::map<std::string, std::string> getOptions();
            MediaSizes& getMediaSizes();
            std::optional<MediaSize>& getDefaultMediaSize();
            bool canPrintMultipleCopies() const;
            const Finishings& getFinishings();
            const Finishings& getDefaultFinishings();
            const MediaSources getMediaSources();
            std::optional<MediaSource>& getDefaultMediaSource();
            MediaTypes& getMediaTypes();
            std::optional<MediaType>& getDefaultMediaType();
            PageOrientations& getOrientations();
            const std::optional<PageOrientation>& getDefaultOrientation();
            ColorModes& getColorModes();
            ColorMode& getDefaultColorMode();
            PrintQualities& getPrintQualities();
            PrintQuality& getDefaultPrintQuality();
            Sides& getSides();
            Side& getDefaultSide();

            std::string get_printer_state() const;
            std::string get_printer_make_and_model();
            std::string get_printer_location();
            std::string get_printer_info();

        protected:
            Printer(cups_dest_t* dest);

        private:
            std::string getPrinterStateString(std::string value);
            std::string getPrinterTypeString(const std::string value) const;
            void populateMediaSizes();
            void populateDefaultMediaSize();
            void populateFinishings();
            void setFinishing(int finishing);
            void populateDefaultFinishings();
            void populateMediaSources();
            void populateDefaultMediaSource();
            void populateMediaTypes();
            void populateDefaultMediaType();
            void populateOrientations();
            void populateDefaultOrientation();
            void populateColorModes();
            void populateDefaultColorMode();
            void populatePrintQualities();
            void populateDefaultPrintQuality();
            void populateSides();
            void populateDefaultSide();

            cups_dest_t* m_dest;
            MediaSizes m_mediaSizes;

            bool m_gotMediaSizes;
            bool m_gotMediaSources;
            MediaSources m_mediaSources;
            bool m_gotMediaTypes;
            MediaTypes m_mediaTypes;
            bool m_gotOrientations;
            PageOrientations m_orientations;
            bool m_gotColorModes;
            ColorModes m_colorModes;
            bool m_gotPrintQualities;
            PrintQualities m_printQualities;
            bool m_gotSides;
            Sides m_sides;
            bool m_gotFinishings;
            Finishings m_finishings;

            bool m_gotDefaultMediaSize;
            std::optional<MediaSize> m_defaultMediaSize;
            bool m_gotDefaultMediaSource;
            std::optional<MediaSource> m_defaultMediaSource;
            bool m_gotDefaultMediaType;
            std::optional<MediaType> m_defaultMediaType;
            bool m_gotDefaultOrientation;
            std::optional<PageOrientation> m_defaultOrientation;
            bool m_gotDefaultColorMode;
            ColorMode m_defaultColorMode;
            bool m_gotDefaultPrintQuality;
            PrintQuality m_defaultPrintQuality;
            bool m_gotDefaultSide;
            Side m_defaultSide;
            bool m_gotDefaultFinishings;
            Finishings m_defaultFinishings;
    };
}
