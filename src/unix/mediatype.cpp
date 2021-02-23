/**
 *  \brief A Media type class
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

#include "mediatype.h"

using namespace std;

namespace nanaprint
{
    media_type::media_type(const std::string& mediaType)
        : nanaprint_value(mediaType)
    {

    }

    std::ostream& operator<<(std::ostream& os, const media_type& mType)
    {
        os << "    " << mType.get_value() << '\n';
        return os;
    }

    void MediaTypes::add_type(const std::string& mediaType)
    {
        m_types.push_back(media_type(mediaType));
    }

    const vector<media_type>& MediaTypes::get_types() const
    {
        return m_types;
    }

    std::ostream& operator<<(std::ostream& os, const MediaTypes& mType)
    {
        os << "Media Types:\n";
        auto types = mType.get_types();
        if(types.size() == 0)
        {
            os << "    None\n";
        }
        else
        {
            for (const auto& typ: types)
            {
                os << typ;
            }
        }
        return os;
    }

    media_type& MediaTypes::operator[](size_t pos)
    {
        return m_types[pos];
    }
    
    const media_type& MediaTypes::operator[](size_t pos) const
    {
        return m_types[pos];
    }

    media_type& MediaTypes::at(size_t pos)
    {
        if (pos >= m_types.size())
        {
            throw out_of_range("Out of range");
        }
        return m_types[pos];
    }

    const media_type& MediaTypes::at(size_t pos) const
    {
        if (pos >= m_types.size())
        {
            throw out_of_range("Out of range");
        }
        return m_types[pos];
    }
}
