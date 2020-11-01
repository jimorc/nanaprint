#ifndef MEDIASIZETRANSLATOR_H
#define MEDIASIZETRANSLATOR_H

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
    class MediaSizesTranslator
    {
        public:
            MediaSizesTranslator();
            virtual ~MediaSizesTranslator();
            const std::string getTranslatedSize(const std::string& mediaName) const;

        private:
            std::map<std::string, std::string> m_mediaMap;
   };
}

#endif      // MEDIASIZETRANSLATOR_H