#pragma(once)

/**
 *  \file printquality.h
 *  \brief This file provides printquality class required by nanaprint
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

#include <memory>

namespace nanaprint
{
    constexpr int PLAIN_NORMAL = 2;
    constexpr int FAST = 3;
    constexpr int NORMAL = 4;
    constexpr int HIGH = 5;
    constexpr int PHOTO = 6;

    class PrintQuality
    {
        public:
            ~PrintQuality() {}
            static std::shared_ptr<PrintQuality> create(const int quality);
            virtual std::string getPrintQuality() = 0;

        protected:
            PrintQuality() {}
    };

    class PlainNormalQuality : public PrintQuality
    {
        public:
            static std::shared_ptr<PlainNormalQuality> create();
            std::string getPrintQuality() override;
            virtual ~PlainNormalQuality() {}

        protected:
            PlainNormalQuality() {}
    };

    class FastQuality : public PrintQuality
    {
        public:
            static std::shared_ptr<FastQuality> create();
            std::string getPrintQuality() override;
            virtual ~FastQuality() {}

        protected:
            FastQuality() {}
    };

    class NormalQuality : public PrintQuality
    {
        public:
            static std::shared_ptr<NormalQuality> create();
            std::string getPrintQuality() override;
            virtual ~NormalQuality() {}

        protected:
            NormalQuality() {}
    };
}