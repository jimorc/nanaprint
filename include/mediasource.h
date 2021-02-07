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
#include <set>
#include <string>
#include <memory>
#include <iostream>

namespace nanaprint
{
    class MediaSource
    {
        public:
            MediaSource(const std::string& source);
            virtual ~MediaSource() {}
            const std::string& getSource() const { return m_source; }

        private:
            std::string m_source;
    };

    std::ostream& operator<<(std::ostream& os, const MediaSource& source);

    class MediaSources
    {
        public:
            virtual ~MediaSources() {}
            void addSource(const std::string& source);
            const std::vector<MediaSource> getSources() const;
            MediaSource& operator[](size_t pos);
            MediaSource& at(size_t pos);
        private:
            std::vector<MediaSource> m_sources;
    };

    std::ostream& operator<<(std::ostream& os, const MediaSources& sources);
}
