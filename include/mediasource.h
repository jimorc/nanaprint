#pragma(once)

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
#include <map>
#include <string>

namespace nanaprint
{
    class MediaSource
    {
        public:
            MediaSource(const std::string& source);
            virtual ~MediaSource() {}
            std::string& getSource() { return m_source; }

        private:
            std::string m_source;
    };
}
