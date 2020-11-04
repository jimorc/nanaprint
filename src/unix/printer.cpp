/**
 *  \brief A Printer class
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/printer.cpp
 */

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include "printer.h"

using namespace std;
using namespace nanaprint;

constexpr size_t RESOURCE_SIZE = 200;          // sets size of resources returned by cupsConnectDest
constexpr int MAX_CONNECT_ATTEMPT_TIME = 5000; // max allowed time for printer connect in ms

namespace nanaprint
{

    map<int, string> Printer::m_orientationMap {{3, "Portrait"}, {4, "Landscape"},
                {5, "Reverse Landscape"}, {6, "Reverse Portrait"}};
 

    Printer::Printer(cups_dest_t* dest)
        : m_dest(dest), m_gotFinishings(false), m_canBind(false), m_canCoverOutput(false),
            m_canFold(false), m_canPunch(false), m_canStaple(false), m_canTrim(false),
            m_noDefaultFinishings(false), m_defaultBind(false), m_defaultCoverOutput(false),
            m_defaultFold(false), m_defaultPunch(false), m_defaultStaple(false),
            m_defaultTrim(false), m_gotMediaSources(false), m_gotDefaultMediaSource(false),
            m_gotMediaTypes(false), m_gotDefaultMediaType(false), m_gotOrientations(false),
            m_gotDefaultOrientation(false), m_gotColorModes(false), m_gotDefaultColorMode(false)
    {
        populateDefaultFinishings();
    }

    std::shared_ptr<Printer> Printer::create(cups_dest_t *dest)
    {
    char resource[RESOURCE_SIZE];
    http_t *http = cupsConnectDest(dest, CUPS_DEST_FLAGS_DEVICE, MAX_CONNECT_ATTEMPT_TIME,
                                    NULL, resource, RESOURCE_SIZE, NULL, NULL);
    return std::make_shared<Printer>(Printer(dest));
    }

    std::map<std::string, std::string> Printer::getOptions()
    {
    map<string, string> opts;
    for (int i = 0; i < m_dest->num_options; ++i)
    {
        string option = string(m_dest->options[i].name);
        string value = string(m_dest->options[i].value);
        if (option == "printer-state")
        {
            opts[option] = getPrinterStateString(value);
        }
        else if (option == "printer-type")
        {
            opts[option] = getPrinterTypeString(value);
        }
        else
        {
            opts[string(m_dest->options[i].name)] = value;
        }
    }
    return opts;
    }

    string Printer::getPrinterStateString(string value)
    {
        int intState = atoi(value.c_str());
        string state;
        switch (intState)
        {
        case 3:
            state = "Idle";
            break;
        case 4:
            state = "Printing";
            break;
        case 5:
            state = "Stopped";
            break;
        default:
            state = "Unknown state: " + value;
            break;
        }
        return state;
    }

    string Printer::getPrinterTypeString(const string value) const
    {
        vector<string> types;
        int intValue = atoi(value.c_str());
        if (intValue & CUPS_PRINTER_FAX)
        {
            types.push_back("Fax");
        }
        if (intValue & CUPS_PRINTER_REMOTE)
        {
            types.push_back("Remote");
        }
        if (intValue & CUPS_PRINTER_DISCOVERED)
        {
            types.push_back("Networked");
        }
        if (intValue & CUPS_PRINTER_BW)
        {
            types.push_back("B&W");
        }
        if (intValue & CUPS_PRINTER_COLOR)
        {
            types.push_back("Color");
        }
        if (intValue & CUPS_PRINTER_DUPLEX)
        {
            types.push_back("Two-Sided Printing");
        }
        if (intValue & CUPS_PRINTER_STAPLE)
        {
            types.push_back("Can staple output");
        }
        if (intValue & CUPS_PRINTER_COLLATE)
        {
            types.push_back("Can collate copies");
        }
        if (intValue & CUPS_PRINTER_PUNCH)
        {
            types.push_back("Can punch output");
        }
        if (intValue & CUPS_PRINTER_COVER)
        {
            types.push_back("Can cover output");
        }
        if (intValue & CUPS_PRINTER_BIND)
        {
            types.push_back("Can bind output");
        }
        if (intValue & CUPS_PRINTER_SORT)
        {
            types.push_back("Can sort output");
        }
        if (intValue & CUPS_PRINTER_SMALL)
        {
            types.push_back("Can print on Letter/Legal/A4-size media");
        }
        if (intValue & CUPS_PRINTER_MEDIUM)
        {
            types.push_back("Can print on Tabloid/B/C/A3/A2-size media");
        }
        if (intValue & CUPS_PRINTER_LARGE)
        {
            types.push_back("Can print on D/E/A1/A0-size media");
        }
        if (intValue & CUPS_PRINTER_VARIABLE)
        {
            types.push_back("Can print on rolls and custom-size media");
        }
        string type;
        for (auto printerType : types)
        {
            if(type.size() != 0)
            {
                type += ", ";
            }
            type += printerType;
        }
        return type;
    }

    void Printer::populateMediaSizes()
    {
        if(m_mediaSizes.getSize() == 0)
        {
            char resource[RESOURCE_SIZE];
            http_t *http = cupsConnectDest(m_dest, CUPS_DEST_FLAGS_NONE, 5000,
            NULL, resource, RESOURCE_SIZE, NULL, NULL);
            cups_dinfo_t *info = cupsCopyDestInfo(http, m_dest);
            int mSizeCount = cupsGetDestMediaCount(http, m_dest, info, 0);
            cups_size_t size;
            for(int i = 0; i < mSizeCount; ++i)
            {
                int result = cupsGetDestMediaByIndex(http, m_dest, info, i, 0, &size);
                m_mediaSizes.addSize(make_shared<MediaSize>(MediaSize(
                    size.media, size.width, size.length, size.bottom, size.left,
                    size.right, size.top)));
            }
        }
    }

    std::vector<std::string> Printer::getMediaSizeNames()
    {
        populateMediaSizes();
        vector<string> mediaNames = m_mediaSizes.getMediaSizeNames();
        return mediaNames;
    }

    vector<shared_ptr<MediaSize>> Printer::getMediaSizes()
    {
        populateMediaSizes();
        return m_mediaSizes.getMediaSizes();
    }

    bool Printer::canPrintMultipleCopies() const
    {
        char resource[RESOURCE_SIZE];

        
        http_t *http = cupsConnectDest(m_dest, CUPS_DEST_FLAGS_NONE, 5000,
            NULL, resource, RESOURCE_SIZE, NULL, NULL);
        cups_dinfo_t *info = cupsCopyDestInfo(http, m_dest);
        return cupsCheckDestSupported(http, m_dest,
            info, CUPS_COPIES, NULL);
    }

    bool Printer::noFinishings()
    {
        populateFinishings();
        return m_noFinishings;
    }

    bool Printer::canBind()
    {
        populateFinishings();
        return m_canBind;
    }

    bool Printer::canStaple()
    {
        populateFinishings();
        return m_canStaple;
    }

    bool Printer::canCoverOutput()
    {
        populateFinishings();
        return m_canCoverOutput;
    }

    bool Printer::canFold()
    {
        populateFinishings();
        return m_canFold;
    }

    bool Printer::canPunch()
    {
        populateFinishings();
        return m_canPunch;
    }

    bool Printer::canTrim()
    {
        populateFinishings();
        return m_canTrim;
    }

    void Printer::populateFinishings()
    {
        if (!m_gotFinishings)
        {
            char resource[RESOURCE_SIZE];
            
            http_t *http = cupsConnectDest(m_dest, CUPS_DEST_FLAGS_NONE, 5000,
                NULL, resource, RESOURCE_SIZE, NULL, NULL);
            cups_dinfo_t *info = cupsCopyDestInfo(http, m_dest);
            if (cupsCheckDestSupported(http, m_dest, info, CUPS_FINISHINGS, NULL))
            {
                ipp_attribute_t *finishings = cupsFindDestSupported(http, m_dest,
                    info, CUPS_FINISHINGS);
                int count = ippGetCount(finishings);
                for (int i = 0; i < count; ++i)
                {
                    int finish = ippGetInteger(finishings, i);
                    setFinishing(finish);
                }
            }
            m_gotFinishings = true;
        }
    }

    void Printer::setFinishing(int finish)
    {
        char fin[10];       // should only need to be 2 or 3 characters long
        sprintf(fin, "%d", finish);
        if (strncmp(CUPS_FINISHINGS_NONE, fin, strlen(CUPS_FINISHINGS_NONE)) == 0)
        {
            m_noFinishings = true;
        }
        else if (strncmp(CUPS_FINISHINGS_BIND, fin, strlen(CUPS_FINISHINGS_BIND)) == 0)
        {
            m_canBind = true;
        }
        else if (strncmp(CUPS_FINISHINGS_COVER, fin, strlen(CUPS_FINISHINGS_COVER))== 0)
        {
            m_canCoverOutput = true;
        }
        else if (strncmp(CUPS_FINISHINGS_FOLD, fin, strlen(CUPS_FINISHINGS_FOLD))== 0)
        {
            m_canFold = true;
        }
        else if (strncmp(CUPS_FINISHINGS_PUNCH, fin, strlen(CUPS_FINISHINGS_PUNCH)) == 0)
        {
            m_canPunch = true;
        }
        else if (strncmp(CUPS_FINISHINGS_STAPLE, fin, strlen(CUPS_FINISHINGS_STAPLE)) == 0)
        {
            m_canStaple = true;
        }
        else if (strncmp(CUPS_FINISHINGS_TRIM, fin, strlen(CUPS_FINISHINGS_TRIM)) == 0)
        {
            m_canTrim = true;
        }

    }

    void Printer::populateMediaSources()
    {
        if (!m_gotMediaSources)
        {
            char resource[RESOURCE_SIZE];
            
            http_t *http = cupsConnectDest(m_dest, CUPS_DEST_FLAGS_NONE, 5000,
                NULL, resource, RESOURCE_SIZE, NULL, NULL);
            cups_dinfo_t *info = cupsCopyDestInfo(http, m_dest);
            if (cupsCheckDestSupported(http, m_dest, info, CUPS_FINISHINGS, NULL))
            {
                ipp_attribute_t *source = cupsFindDestSupported(http, m_dest,
                    info, CUPS_MEDIA_SOURCE);
                int count = ippGetCount(source);
                for (int i = 0; i < count; ++i)
                {
                    const char *src = ippGetString(source, i, NULL);
                    m_mediaSources.push_back(src);
                }
            }
            m_gotMediaSources = true;
        }   
    }

    vector<string>& Printer::getMediaSources()
    {
        populateMediaSources();
        return m_mediaSources;
    }

    bool Printer::noDefaultFinishings()
    {
        populateDefaultFinishings();
        return m_noDefaultFinishings;
    }

    bool Printer::defaultBind()
    {
        populateDefaultFinishings();
        return m_defaultBind;
    }

    bool Printer::defaultCoverOutput()
    {
        populateDefaultFinishings();
        return m_defaultCoverOutput;
    }

    bool Printer::defaultFold()
    {
        populateDefaultFinishings();
        return m_defaultFold;
    }

    bool Printer::defaultPunch()
    {
        populateDefaultFinishings();
        return m_defaultPunch;
    }

    bool Printer::defaultStaple()
    {
        populateDefaultFinishings();
        return m_defaultStaple;
    }

    bool Printer::defaultTrim()
    {
        populateDefaultFinishings();
        return m_defaultTrim;
    }

    void Printer::populateDefaultFinishings()
    {
        if (!m_gotDefaultFinishings)
        {
            char resource[RESOURCE_SIZE];

            http_t *http = cupsConnectDest(m_dest, CUPS_DEST_FLAGS_NONE, 5000,
                NULL, resource, RESOURCE_SIZE, NULL, NULL);
            cups_dinfo_t *info = cupsCopyDestInfo(http, m_dest);

            const char *defaultFinishings =
                cupsGetOption(CUPS_FINISHINGS, m_dest->num_options,
                    m_dest->options);
            ipp_attribute_t *defaultFinishings2 =
                cupsFindDestDefault(http, m_dest, info, CUPS_FINISHINGS);
            
            if(defaultFinishings != NULL)
            {
                regex rgx("[0-9]*");
                smatch match;

                string finishings = defaultFinishings;
                if( regex_search(finishings, match, rgx))
                {
                    for (auto m: match)
                    {
                        int finish = stoi(m.str());
                        setDefaultFinishing(finish);
                    }
                }
            }
            else
            {
                int count = ippGetCount(defaultFinishings2);
                for (int i = 0; i < count; ++i)
                {
                    int finish = ippGetInteger(defaultFinishings2, i);
                    setDefaultFinishing(finish);
                }
            }
        }
        m_gotDefaultFinishings = true;
    }

    void Printer::setDefaultFinishing(int finish)
    {
        char fin[10];       // should only need to be 2 or 3 characters long
        sprintf(fin, "%d", finish);
        if (strncmp(CUPS_FINISHINGS_NONE, fin, strlen(CUPS_FINISHINGS_NONE)) == 0)
        {
            m_noDefaultFinishings = true;
        }
        else if (strncmp(CUPS_FINISHINGS_BIND, fin, strlen(CUPS_FINISHINGS_BIND)) == 0)
        {
            m_defaultBind = true;
        }
        else if (strncmp(CUPS_FINISHINGS_COVER, fin, strlen(CUPS_FINISHINGS_COVER)) == 0)
        {
            m_defaultCoverOutput = true;
        }
        else if (strncmp(CUPS_FINISHINGS_FOLD, fin, strlen(CUPS_FINISHINGS_FOLD)) == 0)
        {
            m_defaultFold = true;
        }
        else if (strncmp(CUPS_FINISHINGS_PUNCH, fin, strlen(CUPS_FINISHINGS_PUNCH)) == 0)
        {
            m_defaultPunch = true;
        }
        else if (strncmp(CUPS_FINISHINGS_STAPLE, fin, strlen(CUPS_FINISHINGS_STAPLE)) == 0)
        {
            m_defaultStaple = true;
        }
        else if (strncmp(CUPS_FINISHINGS_TRIM, fin, strlen(CUPS_FINISHINGS_TRIM)) == 0)
        {
            m_defaultTrim = true;
        }
    }

    void Printer::populateDefaultMediaSource()
    {
        if (!m_gotDefaultMediaSource)
        {
            char resource[RESOURCE_SIZE];
            
            http_t *http = cupsConnectDest(m_dest, CUPS_DEST_FLAGS_NONE, 5000,
                NULL, resource, RESOURCE_SIZE, NULL, NULL);
            cups_dinfo_t *info = cupsCopyDestInfo(http, m_dest);
            const char *defaultSource =
                cupsGetOption(CUPS_MEDIA_SOURCE, m_dest->num_options, m_dest->options);
            if (defaultSource != nullptr)
            {
                m_defaultMediaSource = *defaultSource;
            }
            else
            {
                ipp_attribute_t *source = cupsFindDestDefault(http, m_dest,
                    info, CUPS_MEDIA_SOURCE);
                int count = ippGetCount(source);
                if (count != 0)
                {
                    const char *src = ippGetString(source, 0, NULL);
                    m_defaultMediaSource = *src;
                }
            }
            m_gotDefaultMediaSource = true;
        }   
    }

    string& Printer::getDefaultMediaSource()
    {
        populateDefaultMediaSource();
        return m_defaultMediaSource;
    }

    void Printer::populateMediaTypes()
    {
        if (!m_gotMediaTypes)
        {
            char resource[RESOURCE_SIZE];
            
            http_t *http = cupsConnectDest(m_dest, CUPS_DEST_FLAGS_NONE, 5000,
                NULL, resource, RESOURCE_SIZE, NULL, NULL);
            cups_dinfo_t *info = cupsCopyDestInfo(http, m_dest);
            if (cupsCheckDestSupported(http, m_dest, info, CUPS_MEDIA_TYPE, NULL))
            {
                ipp_attribute_t *type = cupsFindDestSupported(http, m_dest,
                    info, CUPS_MEDIA_TYPE);
                int count = ippGetCount(type);
                for (int i = 0; i < count; ++i)
                {
                    const char *mediaType = ippGetString(type, i, NULL);
                    m_mediaTypes.push_back(mediaType);
                }
            }
            m_gotMediaTypes = true;
        }   
    }

    std::vector<std::string>& Printer::getMediaTypes()
    {
        populateMediaTypes();
        return m_mediaTypes;
    }

    void Printer::populateDefaultMediaType()
    {
        if (!m_gotDefaultMediaType)
        {
            char resource[RESOURCE_SIZE];
            
            http_t *http = cupsConnectDest(m_dest, CUPS_DEST_FLAGS_NONE, 5000,
                NULL, resource, RESOURCE_SIZE, NULL, NULL);
            cups_dinfo_t *info = cupsCopyDestInfo(http, m_dest);
            const char *defaultType =
                cupsGetOption(CUPS_MEDIA_TYPE, m_dest->num_options, m_dest->options);
            if(defaultType != nullptr)
            {
                m_defaultMediaType = *defaultType;
            }
            else
            {
                ipp_attribute_t *type = cupsFindDestDefault(http, m_dest,
                    info, CUPS_MEDIA_TYPE);
                int count = ippGetCount(type);
                if (count != 0)
                {
                    const char *defaultType = ippGetString(type, 0, NULL);
                    m_defaultMediaType = *defaultType;
                }
            }
            m_gotDefaultMediaType = true;
        }   
    }

    std::string& Printer::getDefaultMediaType()
    {
        populateDefaultMediaType();
        return m_defaultMediaType;
    }

    void Printer::populateOrientations()
    {
        if (!m_gotOrientations)
        {
            char resource[RESOURCE_SIZE];
            
            http_t *http = cupsConnectDest(m_dest, CUPS_DEST_FLAGS_NONE, 5000,
                NULL, resource, RESOURCE_SIZE, NULL, NULL);
            cups_dinfo_t *info = cupsCopyDestInfo(http, m_dest);
            if (cupsCheckDestSupported(http, m_dest, info, CUPS_ORIENTATION, NULL))
            {
                ipp_attribute_t *orientations = cupsFindDestSupported(http, m_dest,
                    info, CUPS_ORIENTATION);
                int count = ippGetCount(orientations);
                for (int i = 0; i < count; ++i)
                {
                    int orientation = ippGetInteger(orientations, i);
                    m_orientations.push_back(m_orientationMap[orientation]);
                }
            }
            m_gotOrientations = true;
        }   
    }
    std::vector<std::string>& Printer::getOrientations()
    {
        populateOrientations();
        return m_orientations;
    }

    void Printer::populateDefaultOrientation()
    {
        if (!m_gotDefaultOrientation)
        {
            char resource[RESOURCE_SIZE];
            
            http_t *http = cupsConnectDest(m_dest, CUPS_DEST_FLAGS_NONE, 5000,
                NULL, resource, RESOURCE_SIZE, NULL, NULL);
            cups_dinfo_t *info = cupsCopyDestInfo(http, m_dest);
            const char *defaultOrientation =
                cupsGetOption(CUPS_ORIENTATION, m_dest->num_options, m_dest->options);
            if (defaultOrientation != nullptr)
            {
                int orientation = stoi(defaultOrientation);
                m_defaultOrientation = m_orientationMap[orientation];
            }
            else
            {
                ipp_attribute_t *defOrientation = cupsFindDestDefault(http, m_dest,
                    info, CUPS_ORIENTATION);
                int count = ippGetCount(defOrientation);
                if (count != 0)
                {
                    int defaultOr = ippGetInteger(defOrientation, 0);
                    m_defaultOrientation = m_orientationMap[defaultOr];
                }
            }
            m_gotDefaultMediaType = true;
        }   
    }
    std::string& Printer::getDefaultOrientation()
    {
        populateDefaultOrientation();
        return m_defaultOrientation;
    }

    void Printer::populateColorModes()
    {
        if (!m_gotColorModes)
        {
            char resource[RESOURCE_SIZE];
            
            http_t *http = cupsConnectDest(m_dest, CUPS_DEST_FLAGS_NONE, 5000,
                NULL, resource, RESOURCE_SIZE, NULL, NULL);
            cups_dinfo_t *info = cupsCopyDestInfo(http, m_dest);
            if (cupsCheckDestSupported(http, m_dest, info, CUPS_PRINT_COLOR_MODE, NULL))
            {
                ipp_attribute_t *colorModes = cupsFindDestSupported(http, m_dest,
                    info, CUPS_PRINT_COLOR_MODE);
                int count = ippGetCount(colorModes);
                for (int i = 0; i < count; ++i)
                {
                    const char *colorMode = ippGetString(colorModes, i, NULL);
                    m_colorModes.push_back(colorMode);
                }
            }
            m_gotColorModes = true;
        }   
    }
    std::vector<std::string>& Printer::getColorModes()
    {
        populateColorModes();
        return m_colorModes;
    }

    void Printer::populateDefaultColorMode()
    {
        if (!m_gotDefaultColorMode)
        {
            char resource[RESOURCE_SIZE];
            
            http_t *http = cupsConnectDest(m_dest, CUPS_DEST_FLAGS_NONE, 5000,
                NULL, resource, RESOURCE_SIZE, NULL, NULL);
            cups_dinfo_t *info = cupsCopyDestInfo(http, m_dest);
            const char *defaultColorMode =
                cupsGetOption(CUPS_PRINT_COLOR_MODE, m_dest->num_options, m_dest->options);
            if (defaultColorMode != nullptr)
            {
                m_defaultColorMode = defaultColorMode;
            }
            else
            {
                ipp_attribute_t *defColorMode = cupsFindDestDefault(http, m_dest,
                    info, CUPS_PRINT_COLOR_MODE);
                int count = ippGetCount(defColorMode);
                if (count != 0)
                {
                    const char *defaultColorMode = ippGetString(defColorMode, 0, NULL);
                    m_defaultColorMode = defaultColorMode;
                }
            }
            m_gotDefaultColorMode = true;
        }   
    }
    std::string& Printer::getDefaultColorMode()
    {
        populateDefaultColorMode();
        return m_defaultColorMode;
    }
}       