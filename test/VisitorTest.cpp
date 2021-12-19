#include "src/source/StringSource.h"
#include "include/xml_ruban/MutableDecoderParams.h"
#include "src/decode/parser/TagBuilder.h"
#include "gtest/gtest.h"
#include "src/decode/parser/XmlParser.h"
#include "entities/XmlPrimitive.h"

namespace VisitorTest {

    TEST(TagCreation, WHEN_two_open_tag_and_two_close_tag_EXPECT_root_tag_with_one_inner_tag) {
        TagBuilder* builder = new TagBuilder();

        builder->onTagOpen("root");
        builder->onTagOpen("inner");
        builder->onTagClosed("inner");
        builder->onTagClosed("root");

        auto valuesCount = builder->getRoot()->getValues()->size();
        EXPECT_EQ(valuesCount, 1);
    }
    TEST(TagCreation, WHEN_2_open_tag_EXPECT_root_tag_with_no_values) {
        TagBuilder* builder = new TagBuilder();

        builder->onTagOpen("root");
        builder->onTagOpen("inner");

        auto valuesCount = builder->getRoot()->getValues()->size();
        EXPECT_EQ(valuesCount, 0);
    }



    TEST(AttributeCreation, WHEN_create_attribute_EXPECT_value_of_attr_ATTR_is_VAL) {
        TagBuilder* builder = new TagBuilder();

        builder->onTagOpen("root");
        builder->onAttribute("ATTR", "VAL");
        builder->onTagClosed("root");

        auto tagValue = builder->getRoot()->getAttributes()->get("ATTR");
        EXPECT_EQ(tagValue, "VAL");
    }
    TEST(AttributeCreation, WHEN_add_attribute_with_no_root_tag_EXPECT_skip_this_call) {
        TagBuilder* builder = new TagBuilder();

        EXPECT_NO_THROW(builder->onAttribute("ATTR", "VAL"));
    }


    TEST(TagValuesCreation, WHEN_add_text_values_and_text_EXPECT_3_tag_values) {
        TagBuilder* builder = new TagBuilder();

        builder->onTagOpen("root");

        builder->onTagOpen("inner0");
        builder->onTagClosed("inner0");

        builder->onTagTextValue("TEXT_1");

        builder->onTagOpen("inner1");
        builder->onTagClosed("inner1");

        builder->onTagClosed("root");

        int valuesCount = builder->getRoot()->getValues()->size();

        EXPECT_EQ(valuesCount, 3);
    }
}