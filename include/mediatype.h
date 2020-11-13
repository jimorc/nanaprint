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
#include <set>
#include <vector>
#include <memory>

namespace nanaprint
{
    class MediaType
    {
        public:
            MediaType(const std::string& mediaType);
            virtual ~MediaType() {}
            std::string& getType() { return m_type; }

        private:
            std::string m_type;
    };

    class MediaTypes
    {
        public:
            virtual ~MediaTypes() {}
            void addMediaType(const std::string& mediaType);
            std::vector<std::shared_ptr<MediaType>> getMediaTypes() const;
        public:
            std::set<std::shared_ptr<MediaType>> m_types;
    };
}