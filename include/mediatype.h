#pragma(once)

/**
 *  \file mediatype.h
 *  \brief This file provides media types required by nanaprint
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

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "values.h"

namespace nanaprint
{
    class media_type : public nanaprint_value<std::string>
    {
        public:
            media_type(const std::string& mediaType);
            virtual ~media_type() {}
     };

    std::ostream& operator<<(std::ostream& os, const media_type& mType);

    class media_types : public nanaprint_values<media_type>
    {
        public:
            virtual ~media_types() {}
    };

    std::ostream& operator<<(std::ostream& os, const media_types& mType);
}