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
    media_source::media_source(const string& source)
    {
        m_source = source;
    }

    std::ostream& operator<<(std::ostream& os, const media_source& source)
    {
        os << "    " << source.get_source() << '\n';
        return os;
    }

    void media_sources::add_source(const std::string& source)
    {
        m_sources.push_back(media_source(source));
    }

    media_source& media_sources::operator[](size_t pos)
    {
        return m_sources[pos];
    }
    const media_source& media_sources::operator[](size_t pos) const
    {
        return m_sources[pos];
    }

    media_source& media_sources::at(size_t pos)
    {
        if (pos >= m_sources.size())
        {
            throw out_of_range("Out of range");
        }
        return m_sources[pos];
    }

    const media_source& media_sources::at(size_t pos) const
    {
        if (pos >= m_sources.size())
        {
            throw out_of_range("Out of range");
        }
        return m_sources[pos];
    }

    const std::vector<media_source> media_sources::get_sources() const
    {
        std::vector<media_source> sources;
        for (auto source: m_sources)
        {
            sources.push_back(source);
        }
        return sources;
    }

    std::ostream& operator<<(std::ostream& os, const media_sources& sources)
    {
        os << "Media Sources:\n";
        auto srcs = sources.get_sources();
        if(srcs.size() == 0)
        {
            os << "    None\n";
        }
        else
        {
            for (auto source: srcs)
            {
                os << "    " << source.get_source() << '\n';
            }
        }
        return os;
    }
}