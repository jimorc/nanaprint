#include "values.h"
#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <algorithm>

using namespace nanaprint;

class Val : public nanaprint_value<std::string>
{
    public:
        Val(const std::string& str) : nanaprint_value(str) {}
        virtual ~Val() {}
};

class Vals : public nanaprint_values<Val>
{
    public:
        using value_type = Val;
        Vals() {}
        virtual ~Vals() {}
};

TEST(IterTests, testNoValues)
{
    std::vector<std::string> vals;
    auto end = vals.end();
    auto begin = vals.begin();
    ASSERT_EQ(begin, end);
}

TEST(IterTests, testIterator)
{
    Vals values;
    values.push_back(Val(std::string("string 1")));
    Val val(std::string("string 2"));
    values.push_back(val);
    auto iter = values.begin();

    ASSERT_EQ("string 1", iter->get_value());
    ++iter;
    ASSERT_EQ("string 2", iter->get_value());
    iter--;
    ASSERT_EQ("string 1", (*iter).get_value());

    std::stringstream ss;
    for (auto& v: values)
    {
        ss << v.get_value() << ' ';
    }
    ASSERT_EQ("string 1 string 2 ", ss.str());

    iter = --(values.end());
    ASSERT_EQ("string 2", iter->get_value());

    iter = ++(values.begin());
    ASSERT_EQ("string 2", iter->get_value());

    iter = values.end();
    iter--;
    ASSERT_EQ("string 2", iter->get_value());

    iter = values.begin();
    iter++;
    ASSERT_EQ("string 2", iter->get_value());

    ASSERT_TRUE(iter == iter);

    auto iter2 = iter--;
    ASSERT_TRUE(iter != iter2);
}

TEST(IterTests, testConstIterator)
{
    Vals values;
    values.push_back(Val(std::string("string 1")));
    Val val(std::string("string 2"));
    values.push_back(val);

    const Vals values2 = values;    
    auto iter = values2.cbegin();

    ASSERT_EQ(std::string("string 1"), iter->get_value());
    ++iter;
    ASSERT_EQ("string 2", iter->get_value());
    iter--;
    ASSERT_EQ("string 1", (*iter).get_value());

    std::stringstream ss;
    for (auto& v: values)
    {
        ss << v.get_value() << ' ';
    }
    ASSERT_EQ("string 1 string 2 ", ss.str());

    iter = --(values.cend());
    ASSERT_EQ("string 2", iter->get_value());

    iter = ++(values.cbegin());
    ASSERT_EQ("string 2", iter->get_value());

    iter = values.cend();
    iter--;
    ASSERT_EQ("string 2", iter->get_value());

    iter = values.cbegin();
    iter++;
    ASSERT_EQ("string 2", iter->get_value());

    ASSERT_TRUE(iter == iter);

    auto iter2 = iter--;
    ASSERT_TRUE(iter != iter2);
}

TEST(IterTests, testReverseIterator)
{
    Vals values;
    values.push_back(Val(std::string("string 1")));
    Val val(std::string("string 2"));
    values.push_back(val);
    auto iter = values.rbegin();

    ASSERT_EQ("string 2", iter->get_value());
    ++iter;
    ASSERT_EQ("string 1", iter->get_value());
    --iter;
    ASSERT_EQ("string 2", (*iter).get_value());

    iter = --(values.rend());
    ASSERT_EQ("string 1", iter->get_value());

    std::stringstream ss;
    for (auto iter = values.rbegin(); iter != values.rend(); iter++)
    {
        ss << iter->get_value() << ' ';
    }
    ASSERT_EQ("string 2 string 1 ", ss.str());

    iter = ++(values.rbegin());
    ASSERT_EQ("string 1", iter->get_value());

    iter = values.rend();
    iter--;
    ASSERT_EQ("string 1", iter->get_value());

    iter = values.rbegin();
    iter++;
    ASSERT_EQ("string 1", iter->get_value());

    ASSERT_TRUE(iter == iter);

    auto iter2 = iter--;
    ASSERT_TRUE(iter != iter2);
}

TEST(IterTests, testConstReverseIterator)
{
    Vals values;
    values.push_back(Val(std::string("string 1")));
    Val val(std::string("string 2"));
    values.push_back(val);
    auto iter = values.crbegin();

    ASSERT_EQ("string 2", iter->get_value());
    ++iter;
    ASSERT_EQ("string 1", iter->get_value());
    --iter;
    ASSERT_EQ("string 2", (*iter).get_value());

    iter = --(values.crend());
    ASSERT_EQ("string 1", iter->get_value());

    std::stringstream ss;
    for (auto iter = values.crbegin(); iter != values.crend(); iter++)
    {
        ss << iter->get_value() << ' ';
    }
    ASSERT_EQ("string 2 string 1 ", ss.str());

    iter = ++(values.crbegin());
    ASSERT_EQ("string 1", iter->get_value());

    iter = values.crend();
    iter--;
    ASSERT_EQ("string 1", iter->get_value());

    iter = values.crbegin();
    iter++;
    ASSERT_EQ("string 1", iter->get_value());

    ASSERT_TRUE(iter == iter);

    auto iter2 = iter--;
    ASSERT_TRUE(iter != iter2);
}

TEST(IterTests, testIteratorWithStdLib)
{
    Vals values;
    values.push_back(Val(std::string("string 1")));
    Val val(std::string("string 2"));
    values.push_back(val);

    Vals values2;
    values2.push_back(Val(std::string("string 3")));
    values2.push_back(Val(std::string("string 4")));
    std::copy(values.begin(), values.end(), values2.begin());

    ASSERT_EQ("string 1", values2[0].get_value());
    ASSERT_EQ("string 2", values2[1].get_value());

    values2.push_back(Val(std::string("string 1")));
    values.clear();
    values.push_back(Val(std::string("string 3")));
    values.push_back(Val(std::string("string 4")));
    std::copy_if(values2.begin(), values2.end(), values.begin(),
        [](Val val){ return val.get_value()==std::string("string 1"); });
    
    ASSERT_EQ(2, values.size());
    ASSERT_EQ("string 1", values[0].get_value());
    ASSERT_EQ("string 1", values[1].get_value());

    auto iter = std::find_if(values2.begin(), values2.end(), 
        [](Val val){ return val.get_value() == std::string("string 2"); });

    ASSERT_EQ("string 2", iter->get_value());

    std::fill(values.begin(), values.end(), Val(std::string("string 0")));

    ASSERT_EQ("string 0", values[0].get_value());
    ASSERT_EQ("string 0", values[1].get_value());

    values[1] = Val(std::string("string 4"));
    std::reverse(values.begin(), values.end());

    ASSERT_EQ("string 4", values[0].get_value());
    ASSERT_EQ("string 0", values[1].get_value());

    std::reverse_copy(values.begin(), values.end(), values2.begin());

    ASSERT_EQ("string 0", values2[0].get_value());
    ASSERT_EQ("string 4", values2[1].get_value());
}

TEST(IterTests, testReverseIteratorWithStdLib)
{
    Vals values;
    values.push_back(Val(std::string("string 1")));
    Val val(std::string("string 2"));
    values.push_back(val);

    Vals values2;
    values2.push_back(Val(std::string("string 3")));
    values2.push_back(Val(std::string("string 4")));
    std::copy(values.begin(), values.end(), values2.rbegin());

    ASSERT_EQ("string 2", values2[0].get_value());
    ASSERT_EQ("string 1", values2[1].get_value());

    values2.push_back(Val(std::string("string 1")));
    values.clear();
    values.push_back(Val(std::string("string 3")));
    values.push_back(Val(std::string("string 4")));
    std::copy_if(values2.rbegin(), values2.rend(), values.begin(),
        [](Val val){ return val.get_value()==std::string("string 1"); });
    
    ASSERT_EQ(2, values.size());
    ASSERT_EQ("string 1", values[0].get_value());
    ASSERT_EQ("string 1", values[1].get_value());

    auto iter = std::find_if(values2.rbegin(), values2.rend(), 
        [](Val val){ return val.get_value() == std::string("string 2"); });

    ASSERT_EQ("string 2", iter->get_value());

    std::fill(values.rbegin(), values.rend(), Val(std::string("string 0")));

    ASSERT_EQ("string 0", values[0].get_value());
    ASSERT_EQ("string 0", values[1].get_value());

    values[1] = Val(std::string("string 4"));
    std::reverse(values.begin(), values.end());

    ASSERT_EQ("string 4", values[0].get_value());
    ASSERT_EQ("string 0", values[1].get_value());

    std::reverse_copy(values.rbegin(), values.rend(), values2.begin());

    ASSERT_EQ("string 4", values2[0].get_value());
    ASSERT_EQ("string 0", values2[1].get_value());
}

TEST(IterTests, testInserter)
{
    Vals values, values1, values2;
    values.push_back(Val(std::string("0")));
    values.push_back(Val(std::string("1")));
    values1 = values;

    values2.push_back(Val(std::string("2")));
    values2.push_back(Val(std::string("3")));

    auto iter = ++values1.begin();
    std::copy(values2.begin(), values2.end(), std::inserter(values1, iter));

    ASSERT_EQ("0", values1[0].get_value());
    ASSERT_EQ("2", values1[1].get_value());
    ASSERT_EQ("3", values1[2].get_value());
    ASSERT_EQ("1", values1[3].get_value());

    values1 = values;
    iter = values1.end();
    std::reverse_copy(values2.begin(), values2.end(), std::inserter(values1, iter));
    
    ASSERT_EQ("0", values1[0].get_value());
    ASSERT_EQ("1", values1[1].get_value());
    ASSERT_EQ("3", values1[2].get_value());
    ASSERT_EQ("2", values1[3].get_value());

    values1 = values;
    std::copy(values2.begin(), values2.end(), std::back_inserter(values1));
    
    ASSERT_EQ("0", values1[0].get_value());
    ASSERT_EQ("1", values1[1].get_value());
    ASSERT_EQ("2", values1[2].get_value());
    ASSERT_EQ("3", values1[3].get_value());

    values1 = values;
    std::copy(values2.begin(), values2.end(), std::front_inserter(values1));
    ASSERT_EQ("3", values1[0].get_value());
    ASSERT_EQ("2", values1[1].get_value());
    ASSERT_EQ("0", values1[2].get_value());
    ASSERT_EQ("1", values1[3].get_value());
}