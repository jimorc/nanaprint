#ifndef NANAPRINT_MEDIASOURCE_H
#define NANAPRINT_MEDIASOURCE_H

/**
 *  \file mediasources.h
 *  \brief This file provides media sources required by nanaprint
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

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "values.h"

namespace nanaprint
{
    class media_source : public nanaprint_value<std::string>
    {
        public:
            media_source(const std::string& source);
            virtual ~media_source() {}
    };

    std::ostream& operator<<(std::ostream& os, const media_source& source);

    class media_sources : public nanaprint_values<media_source>
    {
        public:
           media_sources() {}
            virtual ~media_sources() {}
    };

    std::ostream& operator<<(std::ostream& os, const media_sources& sources);
}

#endif      // NANAPRINT_MEDIASOURCE_H