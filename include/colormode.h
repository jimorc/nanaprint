#pragma(once)
/**
 *  \file colormode.h
 *  \brief This file provides ColorMode and ColorModes classes required by nanaprint
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

#include "value.h"
#include "values.h"
#include <string>
#include <optional>

namespace nanaprint
{
    class color_mode : public nanaprint_value<std::optional<std::string>>
    {
        public:
            color_mode() : nanaprint_value(std::nullopt) {}
            color_mode(const std::optional<std::string>& colormode) : nanaprint_value(colormode) {}
            virtual ~color_mode() {}
    };

    std::ostream& operator<<(std::ostream& os, const color_mode& cmode);

    class color_modes : public nanaprint_values<color_mode>
    {
        public:
            color_modes() {}
            virtual ~color_modes() {}
            color_mode& at(size_t pos);
            const color_mode& at(size_t pos) const;
            iterator begin() noexcept { return iterator(&m_values[0]); }
            iterator end() noexcept { return iterator(&m_values[m_values.size()]); }
            const_iterator cbegin() const noexcept { return const_iterator(&m_values[0]); }
            const_iterator cend() const noexcept { return const_iterator(&m_values[m_values.size()]); }
            iterator rbegin() noexcept { return iterator(&m_values[m_values.size() - 1]); }
            iterator rend() noexcept { return iterator(&m_values[-1]); }
            const_iterator crbegin() const noexcept { return const_iterator(&m_values[m_values.size() - 1]); }
            const_iterator crend() const noexcept { return const_iterator(&m_values[-1]); }
    };

    std::ostream& operator<<(std::ostream& os, const color_modes& cmode);
}
