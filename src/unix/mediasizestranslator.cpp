#include "mediasizestranslator.h"

namespace nanaprint
{
    media_size_translator::media_size_translator()
    {
        m_mediaMap["oe_photo-l_3.5x5in"] = "3.5x5in";
        m_mediaMap["oe_photo-l_3.5x5in_borderless"] = "3.5x5in";
        m_mediaMap["na_monarch_3.875x7.5in"] = "Monarch 3.875x7.5in";
        m_mediaMap["na_monarch_3.875x7.5in_borderless"] = "Monarch 3.875x7.5in";
        m_mediaMap["na_index-4x6_4x6in"] = "4x6in";
        m_mediaMap["na_index-4x6_4x6in_borderless"] = "4x6in";
        m_mediaMap["na_number-10_4.125x9.5in"] = "No. 10 Envelope";
        m_mediaMap["na_number-10_4.125x9.5in_borderless"] = "No. 10 Envelope";
        m_mediaMap["iso_a6_105x148mm"] = "A6";
        m_mediaMap["iso_a6_105x148mm_borderless"] = "A6";
        m_mediaMap["iso_c6_114x162mm"] = "C6";
        m_mediaMap["iso_c6_114x162mm"] = "C6";
        m_mediaMap["iso_dl_110x220mm"] = "DL Envelope";
        m_mediaMap["iso_dl_110x220mm_borderless"] = "DL Envelope";
        m_mediaMap["na_5x7_5x7in"] = "5x7in";
        m_mediaMap["na_5x7_5x7in_borderless"] = "5x7in";
        m_mediaMap["na_index-5x8_5x8in"] = "5x8in";
        m_mediaMap["na_index-5x8_5x8in_borderless"] = "5x8in";
        m_mediaMap["iso_a5_148x210mm"] = "A5";
        m_mediaMap["iso_a5_148x210mm_borderless"] = "A5";
        m_mediaMap["iso_c5_162x229mm"] = "C5";
        m_mediaMap["iso_c5_162x229mm_borderless"] = "C5";
        m_mediaMap["na_executive_7.25x10.5in"] = "Executive 7.25x10.5in";
        m_mediaMap["na_executive_7.25x10.5in_borderless"] = "Executive 7.25x10.5in";
        m_mediaMap["iso_a4_210x297mm"] = "A4";
        m_mediaMap["iso_a4_210x297mm_borderless"] = "A4";
        m_mediaMap["iso_a3_297x420mm"] = "A3";
        m_mediaMap["iso_a3_297x420mm_borderless"] = "A3";
        m_mediaMap["na_letter_8.5x11in"] = "Letter";
        m_mediaMap["na_letter_8.5x11in_borderless"] = "Letter";
        m_mediaMap["na_legal_8.5x14in"] = "Legal";
        m_mediaMap["na_legal_8.5x14in_borderless"] = "Legal";
        m_mediaMap["na_ledger_11x17in"] = "Ledger";
        m_mediaMap["na_ledger_11x17in_borderless"] = "Ledger";
        m_mediaMap["na_govt-letter_8x10in"] = "Gov't Letter";
        m_mediaMap["na_govt-letter_8x10in_borderless"] = "Gov't Letter";
        m_mediaMap["jpn_chou4_90x205mm"] = "Nagagata 4";
        m_mediaMap["jpn_chou4_90x205mm_borderless"] = "Nagagata 4";
        m_mediaMap["jpn_hagaki_100x148mm"] = "Hagaki";
        m_mediaMap["jpn_hagaki_100x148mm_borderless"] = "Hagaki",
        m_mediaMap["jpn_you4_105x235mm"] = "Yougata 4";
        m_mediaMap["jpn_you4_105x235mm_borderless"] = "Yougata 4";
        m_mediaMap["jpn_you6_98x190mm"] = "Yougata 6";
        m_mediaMap["jpn_you6_98x190mm_borderless"] = "Yougata 6";
        m_mediaMap["jpn_chou3_120x235mm"] = "Nagagata 3";
        m_mediaMap["jpn_chou3_120x235mm_borderless"] = "Nagagata 3";
        m_mediaMap["jpn_oufuku_148x200mm"] = "Oufuku";
        m_mediaMap["jis_b5_182x257mm"] = "JIS B5";
        m_mediaMap["jis_b5_182x257mm_borderless"] = "JIS B5";
        m_mediaMap["jis_b4_257x364mm"] = "JIS B4";
        m_mediaMap["custom_55x91mm_55x91mm"] = "Custom 55x91mm";
        m_mediaMap["custom_55x91mm_55x91mm_borderless"] = "Custom 55x91mm";
        m_mediaMap["custom_55.03x91.02mm_55.03x91.02mm"] = "Custom 55x91mm";
        m_mediaMap["custom_89x89mm_89x89mm"] = "Custom 89x89mm";
        m_mediaMap["custom_89x89mm_89x89mm_borderless"] = "Custom 89x89mm";
        m_mediaMap["custom_3.5x3.5in_3.5x3.5in"] = "Custom 3.5x3.5in";
        m_mediaMap["custom_5x5in_5x5in"] = "Custom 5x5in";
        m_mediaMap["custom_5x5in_5x5in_borderless"] = "Custom 5x5in";
        m_mediaMap["custom_7x10in_7x10in"] = "Custom 7x10in";
        m_mediaMap["custom_7x10in_7x10in_borderless"] = "Custom 7x10in";
    }

    media_size_translator::~media_size_translator()
    {

    }

    const std::string media_size_translator::getTranslatedSize(const std::string& mediaName) const
    {
        auto iter = m_mediaMap.find(mediaName);
        if(iter == m_mediaMap.end())
        {
            return mediaName;
        }
        else
        {
            return iter->second;
        }
    }
}