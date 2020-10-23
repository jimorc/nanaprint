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

#include <vector>
#include <string>
#include "printer.h"

using namespace std;
using namespace nanaprint;

constexpr size_t RESOURCE_SIZE = 200;          // sets size of resources returned by cupsConnectDest
constexpr int MAX_CONNECT_ATTEMPT_TIME = 5000; // max allowed time for printer connect in ms

namespace nanaprint
{
    Printer::Printer(cups_dest_t *dest)
    : m_dest(dest)
    {
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
                    size.media, size.width, size.length, size.bottom, size.length,
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
}