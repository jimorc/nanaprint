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

    std::string PlainNormalQuality::getPrintQuality()
    {
        return "Plain Normal";
    }

    std::string FastQuality::getPrintQuality()
    {
        return "Fast";
    }
}