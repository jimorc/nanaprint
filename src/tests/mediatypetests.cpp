
#include <sstream>
#include <cups/cups.h>
#include "gtest/gtest.h"
#include "mediatype.h"

using namespace nanaprint;
using namespace std;

// Test ctor
TEST(MediaTypeTests, testConstructor)
{
    media_type mediaType(CUPS_MEDIA_TYPE_LETTERHEAD);

    ASSERT_STREQ(CUPS_MEDIA_TYPE_LETTERHEAD, mediaType.get_type().c_str());
} 

// Test MediaType insertion operator
TEST(MediaTypeTests, testInsertionOperator)
{
    stringstream ss;
    media_type mediaType(CUPS_MEDIA_TYPE_LETTERHEAD);
    string let = "    " + string(CUPS_MEDIA_TYPE_LETTERHEAD) + '\n';

    ss << mediaType;

    ASSERT_STREQ(let.c_str(), ss.str().c_str());
} 

// Test MediaSources::addMediaType
TEST(MediaTypesTests, testAddMediaType)
{
    MediaTypes mediaTypes;
    mediaTypes.add_type(CUPS_MEDIA_TYPE_LETTERHEAD);
    mediaTypes.add_type(CUPS_MEDIA_TYPE_PLAIN);
    mediaTypes.add_type(CUPS_MEDIA_TYPE_ENVELOPE);

    auto types = mediaTypes.get_types();

    ASSERT_STREQ(CUPS_MEDIA_TYPE_LETTERHEAD, types[0].get_type().c_str());
    ASSERT_STREQ(CUPS_MEDIA_TYPE_PLAIN, types[1].get_type().c_str());
    ASSERT_STREQ(CUPS_MEDIA_TYPE_ENVELOPE, types[2].get_type().c_str());
}

// Test MediaTypes insertion operator
TEST(MediaTypesTests, testInsertionOperator)
{
    stringstream ss, ss2;
    MediaTypes mediaTypes;

    ss2 << mediaTypes;

    mediaTypes.add_type(CUPS_MEDIA_TYPE_LETTERHEAD);
    mediaTypes.add_type(CUPS_MEDIA_TYPE_PHOTO);
    string let = "Media Types:\n    " + string(CUPS_MEDIA_TYPE_LETTERHEAD) + '\n' +
        "    " + string(CUPS_MEDIA_TYPE_PHOTO) + '\n';

    ss << mediaTypes;

    ASSERT_STREQ("Media Types:\n    None\n", ss2.str().c_str());
    ASSERT_STREQ(let.c_str(), ss.str().c_str());
} 

TEST(MediaTypesTests, testAccessOperator)
{
    MediaTypes types;
    types.add_type(CUPS_MEDIA_TYPE_LETTERHEAD);
    types.add_type(CUPS_MEDIA_TYPE_PHOTO);

    ASSERT_EQ(CUPS_MEDIA_TYPE_LETTERHEAD, types[0].get_type());
    ASSERT_EQ(CUPS_MEDIA_TYPE_PHOTO, types[1].get_type());

    const MediaTypes cTypes = types;

    ASSERT_EQ(CUPS_MEDIA_TYPE_LETTERHEAD, cTypes[0].get_type());
    ASSERT_EQ(CUPS_MEDIA_TYPE_PHOTO, cTypes[1].get_type());
 }

TEST(MediaTypesTests, testAt)
{
    MediaTypes types;
    types.add_type(CUPS_MEDIA_TYPE_LETTERHEAD);
    types.add_type(CUPS_MEDIA_TYPE_PHOTO);

    ASSERT_EQ(CUPS_MEDIA_TYPE_LETTERHEAD, types.at(0).get_type());
    ASSERT_EQ(CUPS_MEDIA_TYPE_PHOTO, types.at(1).get_type());

    const MediaTypes cTypes = types;

    ASSERT_EQ(CUPS_MEDIA_TYPE_LETTERHEAD, cTypes.at(0).get_type());
    ASSERT_EQ(CUPS_MEDIA_TYPE_PHOTO, cTypes.at(1).get_type());

    try
    {
        auto t = types.at(2);
        FAIL() << "Didn't throw out_of_range exception";
    }
    catch(const std::out_of_range& e)
    {
        EXPECT_EQ(e.what(), std::string("Out of range"));
    }
    catch(...)
    {
        FAIL() << "Expected out_of_range exception";
    }
    
    try
    {
        auto t = cTypes.at(2);
        FAIL() << "Didn't throw out_of_range exception";
    }
    catch(const std::out_of_range& e)
    {
        EXPECT_EQ(e.what(), std::string("Out of range"));
    }
    catch(...)
    {
        FAIL() << "Expected out_of_range exception";
    }
 }

TEST(MediaTypesTests, testIterator)
{
    MediaTypes types;
    std::vector<media_type> vTypes;
    for (auto &typ: types)
    {
        vTypes.push_back(typ);
    }
    ASSERT_EQ(0, vTypes.size());

    types.add_type(CUPS_MEDIA_TYPE_LETTERHEAD);
    types.add_type(CUPS_MEDIA_TYPE_PLAIN);
    types.add_type(CUPS_MEDIA_TYPE_ENVELOPE);

    auto begin = types.begin();
    ASSERT_EQ(CUPS_MEDIA_TYPE_LETTERHEAD, begin->get_type());
    ASSERT_EQ(CUPS_MEDIA_TYPE_LETTERHEAD, (*begin).get_type());

    for (auto &typ: types)
    {
        vTypes.push_back(typ);
    }
    ASSERT_EQ(CUPS_MEDIA_TYPE_LETTERHEAD, vTypes[0].get_type());
    ASSERT_EQ(CUPS_MEDIA_TYPE_PLAIN, vTypes[1].get_type());
    ASSERT_EQ(CUPS_MEDIA_TYPE_ENVELOPE, vTypes[2].get_type());
}

TEST(MediaSourcesTests, testConstIterator)
{
    MediaTypes types;
    std::vector<media_type> vTypes;
    for (auto &typ: types)
    {
        vTypes.push_back(typ);
    }
    ASSERT_EQ(0, vTypes.size());

    types.add_type(CUPS_MEDIA_TYPE_LETTERHEAD);
    types.add_type(CUPS_MEDIA_TYPE_PLAIN);
    types.add_type(CUPS_MEDIA_TYPE_ENVELOPE);

    auto begin = types.begin();
    ASSERT_EQ(CUPS_MEDIA_TYPE_LETTERHEAD, begin->get_type());
    ASSERT_EQ(CUPS_MEDIA_TYPE_LETTERHEAD, (*begin).get_type());

    for (auto iter = types.cbegin(); iter != types.cend(); ++iter)
    {
        vTypes.push_back(*iter);
    }
    ASSERT_EQ(CUPS_MEDIA_TYPE_LETTERHEAD, vTypes[0].get_type());
    ASSERT_EQ(CUPS_MEDIA_TYPE_PLAIN, vTypes[1].get_type());
    ASSERT_EQ(CUPS_MEDIA_TYPE_ENVELOPE, vTypes[2].get_type());
}

TEST(MediaTypesTests, testReverseIterator)
{
    MediaTypes types;
    std::vector<media_type> vTypes;

    types.add_type(CUPS_MEDIA_TYPE_LETTERHEAD);
    types.add_type(CUPS_MEDIA_TYPE_PLAIN);
    types.add_type(CUPS_MEDIA_TYPE_ENVELOPE);

    auto begin = types.rbegin();
    ASSERT_EQ(CUPS_MEDIA_TYPE_ENVELOPE, begin->get_type());
    ASSERT_EQ(CUPS_MEDIA_TYPE_ENVELOPE, (*begin).get_type());

    for (auto iter = types.rbegin(); iter != types.rend(); --iter)
    {
        vTypes.push_back(*iter);
    }
    ASSERT_EQ(CUPS_MEDIA_TYPE_LETTERHEAD, vTypes[2].get_type());
    ASSERT_EQ(CUPS_MEDIA_TYPE_PLAIN, vTypes[1].get_type());
    ASSERT_EQ(CUPS_MEDIA_TYPE_ENVELOPE, vTypes[0].get_type());
}

TEST(MediaTypesTests, testConstReverseIterator)
{
    MediaTypes types;
    std::vector<media_type> vTypes;

    types.add_type(CUPS_MEDIA_TYPE_LETTERHEAD);
    types.add_type(CUPS_MEDIA_TYPE_PLAIN);
    types.add_type(CUPS_MEDIA_TYPE_ENVELOPE);

    auto begin = types.crbegin();
    ASSERT_EQ(CUPS_MEDIA_TYPE_ENVELOPE, begin->get_type());
    ASSERT_EQ(CUPS_MEDIA_TYPE_ENVELOPE, (*begin).get_type());

    for (auto iter = types.crbegin(); iter != types.crend(); --iter)
    {
        vTypes.push_back(*iter);
    }
    ASSERT_EQ(CUPS_MEDIA_TYPE_LETTERHEAD, vTypes[2].get_type());
    ASSERT_EQ(CUPS_MEDIA_TYPE_PLAIN, vTypes[1].get_type());
    ASSERT_EQ(CUPS_MEDIA_TYPE_ENVELOPE, vTypes[0].get_type());
}

TEST(MediaTypesTests, testIteratorWithStdLib)
{
    MediaTypes types;
    types.add_type(CUPS_MEDIA_TYPE_LETTERHEAD);
    types.add_type(CUPS_MEDIA_TYPE_PLAIN);
    types.add_type(CUPS_MEDIA_TYPE_ENVELOPE);

    MediaTypes types2 = types;      // types2 is used later. This saves extra initialization

    std::fill(types.begin(), types.end(), media_type(CUPS_MEDIA_TYPE_PLAIN));

    ASSERT_EQ(CUPS_MEDIA_TYPE_PLAIN, types[0].get_type());
    ASSERT_EQ(CUPS_MEDIA_TYPE_PLAIN, types[1].get_type());
    ASSERT_EQ(CUPS_MEDIA_TYPE_PLAIN, types[2].get_type());
   
    std::fill(begin(types), end(types), media_type(CUPS_MEDIA_TYPE_ENVELOPE));
    
    ASSERT_EQ(CUPS_MEDIA_TYPE_ENVELOPE, types[0].get_type());
    ASSERT_EQ(CUPS_MEDIA_TYPE_ENVELOPE, types[1].get_type());
    ASSERT_EQ(CUPS_MEDIA_TYPE_ENVELOPE, types[2].get_type());

    std::copy(types2.begin(), types2.end(), types.begin());
    
    ASSERT_EQ(CUPS_MEDIA_TYPE_LETTERHEAD, types[0].get_type());
    ASSERT_EQ(CUPS_MEDIA_TYPE_PLAIN, types[1].get_type());
    ASSERT_EQ(CUPS_MEDIA_TYPE_ENVELOPE, types[2].get_type());
}

TEST(MediaTypesTests, testClear)
{
    MediaTypes types;
    types.add_type(CUPS_MEDIA_TYPE_LETTERHEAD);
    types.add_type(CUPS_MEDIA_TYPE_PLAIN);
    types.add_type(CUPS_MEDIA_TYPE_ENVELOPE);

    ASSERT_EQ(3, types.size());

    types.clear();
    ASSERT_EQ(0, types.size());
}