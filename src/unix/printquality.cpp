/**
 *  \brief print quality class
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/printquality.cpp
 */

#include "printquality.h"

using namespace std;

namespace nanaprint
{
    std::shared_ptr<PrintQuality> PrintQuality::create(int quality)
    {
        std::shared_ptr<PrintQuality> printQuality;
        switch (quality)
        {
            case PLAIN_NORMAL:
                printQuality = PlainNormalQuality::create();
                break;
            case FAST:
                printQuality = FastQuality::create();
                break;
            case NORMAL:
                printQuality = NormalQuality::create();
                break;
            case HIGH:
                printQuality = HighQuality::create();
                break;
            case PHOTO:
                printQuality = PhotoQuality::create();
                break;
            default:
                throw invalid_argument("Invalid argument value input to PrintQuality::create");
        }

        return printQuality;
    }

    std::shared_ptr<PlainNormalQuality> PlainNormalQuality::create()
    {
        return std::make_shared<PlainNormalQuality>(PlainNormalQuality());
    }

    std::shared_ptr<FastQuality> FastQuality::create()
    {
        return std::make_shared<FastQuality>(FastQuality());
    }

    std::shared_ptr<NormalQuality> NormalQuality::create()
    {
        return std::make_shared<NormalQuality>(NormalQuality());
    }
    
    std::shared_ptr<HighQuality> HighQuality::create()
    {
        return std::make_shared<HighQuality>(HighQuality());
    }
    
    std::shared_ptr<PhotoQuality> PhotoQuality::create()
    {
        return std::make_shared<PhotoQuality>(PhotoQuality());
    }
     
    std::string PlainNormalQuality::getPrintQuality() const
    {
        return "Plain Normal";
    }

    std::string FastQuality::getPrintQuality() const
    {
        return "Fast";
    }

    std::string NormalQuality::getPrintQuality() const
    {
        return "Normal";
    }

    std::string HighQuality::getPrintQuality() const
    {
        return "High";
    }

    std::string PhotoQuality::getPrintQuality() const
    {
        return "Photo";
    }

    std::ostream& operator<<(std::ostream& os, const PrintQuality& quality)
    {
        os << quality.getPrintQuality();
        return os;
    }
}