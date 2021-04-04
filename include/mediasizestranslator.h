#ifndef NANAPRINT_MEDIASIZETRANSLATOR_H
#define NANAPRINT_MEDIASIZETRANSLATOR_H

/**
 *  \brief A MediaSizesTranslator class
 *
 *	This header file is used in both Unix and Win32 implementations
 *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/mediasizestranslator.h
 */

#include <map>
#include <string>

namespace nanaprint
{
    class media_size_translator
    {
        public:
            media_size_translator();
            virtual ~media_size_translator();
            const std::string get_translated_size(const std::string& mediaName) const;

        private:
            std::map<std::string, std::string> m_mediaMap;
   };
}

#endif      // NANAPRINT_MEDIASIZETRANSLATOR_H