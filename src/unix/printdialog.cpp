/**
 *  \brief A PrintDialog class
 *
 *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020-2021 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/printdialog.cpp
 */

#include <chrono>
#include <thread>
#include <string>
#include <sstream>
#include <nana/gui.hpp>
#include "printdialog.h"

using namespace std;
using namespace nana;
using namespace nanaprint;

namespace nanaprint
{
    constexpr int MINIMUMCOPIES = 1;
    constexpr int MAXIMUMCOPIES = 100;

    PrintDialog::PrintDialog(form& parent, PrintSettings& settings)
        : form(parent, {750, 500}, appear::decorate<>()), m_settings(settings),
             m_dialogSettings(m_settings), m_layout(*this), m_basic(m_settings),
             m_tabbar(*this)
    {
        caption(u8"Print");
        m_layout.div(string("vert gap=10 margin=5") +
            "<<tab> weight=20>" +
            "<<tabframe> weight=88%>" +
            "<weight=5>" +
            "<gap=10 <weight=50%><cancel><weight=10><print> weight=10%>");

        m_basic.create(*this);
        m_tabbar.append(u8"Basic", m_basic);
        m_layout["tab"] << m_tabbar;
        m_layout["tabframe"] << m_basic;
        m_layout.collocate();
    }

    void PrintDialog::run()
    {
        modality();
    }
}
