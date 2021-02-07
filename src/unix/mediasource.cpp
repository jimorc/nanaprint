/**
 *  \brief A Media source class
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/mediasource.cpp
 */

#include "mediasource.h"

using namespace std;

namespace nanaprint
{
    MediaSource::MediaSource(const string& source)
    {
        m_source = source;
    }

    std::ostream& operator<<(std::ostream& os, const MediaSource& source)
    {
        os << "    " << source.getSource() << '\n';
        return os;
    }

    void MediaSources::addSource(const std::string& source)
    {
        m_sources.push_back(MediaSource(source));
    }

    MediaSource& MediaSources::operator[](size_t pos)
    {
        return m_sources[pos];
    }

    const std::vector<MediaSource> MediaSources::getSources() const
    {
        std::vector<MediaSource> sources;
        for (auto source: m_sources)
        {
            sources.push_back(source);
        }
        return sources;
    }

    std::ostream& operator<<(std::ostream& os, const MediaSources& sources)
    {
        os << "Media Sources:\n";
        auto srcs = sources.getSources();
        if(srcs.size() == 0)
        {
            os << "    None\n";
        }
        else
        {
            for (auto source: srcs)
            {
                os << "    " << source.getSource() << '\n';
            }
        }
        return os;
    }
}