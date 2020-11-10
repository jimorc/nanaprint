#ifndef PRINTER_H
#define PRINTER_H

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
#include <cups/cups.h>
#include "mediasizes.h"
#include "pageorientation.h"
#include "printquality.h"
#include "finishings.h"

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
            std::vector<std::string> getMediaSizeNames();
            std::vector<std::shared_ptr<MediaSize>> getMediaSizes();
            bool canPrintMultipleCopies() const;
            const Finishings& getFinishings();
            const Finishings& getDefaultFinishings();
            std::vector<std::string>& getMediaSources();
            std::string& getDefaultMediaSource();
            std::vector<std::string>& getMediaTypes();
            std::string& getDefaultMediaType();
            PageOrientations& getOrientations();
            const std::string getDefaultOrientation();
            std::vector<std::string>& getColorModes();
            std::string& getDefaultColorMode();
            PrintQualities& getPrintQualities();
            std::shared_ptr<PrintQuality> getDefaultPrintQuality();
            std::vector<std::string>& getSides();
            std::string& getDefaultSide();

        protected:
            Printer(cups_dest_t* dest);

        private:
            std::string getPrinterStateString(std::string value);
            std::string getPrinterTypeString(const std::string value) const;
            void populateMediaSizes();
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

            bool m_gotMediaSources;
            std::vector<std::string> m_mediaSources;
            bool m_gotMediaTypes;
            std::vector<std::string> m_mediaTypes;
            bool m_gotOrientations;
            PageOrientations m_orientations;
            bool m_gotColorModes;
            std::vector<std::string> m_colorModes;
            bool m_gotPrintQualities;
            PrintQualities m_printQualities;
            bool m_gotSides;
            std::vector<std::string> m_sides;
            bool m_gotFinishings;
            Finishings m_finishings;

            bool m_gotDefaultMediaSource;
            std::string m_defaultMediaSource;
            bool m_gotDefaultMediaType;
            std::string m_defaultMediaType;
            bool m_gotDefaultOrientation;
            std::string m_defaultOrientation;
            bool m_gotDefaultColorMode;
            std::string m_defaultColorMode;
            bool m_gotDefaultPrintQuality;
            std::shared_ptr<PrintQuality> m_defaultPrintQuality;
            bool m_gotDefaultSide;
            std::string m_defaultSide;
            bool m_gotDefaultFinishings;
            Finishings m_defaultFinishings;
    };
}

#endif      // PRINTER_H