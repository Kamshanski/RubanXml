
#include "src/source/StringSource.h"
#include "include/xml_ruban/MutableDecoderParams.h"
#include "src/decode/parser/TagBuilder.h"
#include "gtest/gtest.h"
#include "src/decode/parser/XmlParser.h"
#include "entities/XmlPrimitive.h"

namespace ParserTest {

    std::string TEST_STRING = "<0 param=\"value\">\n"
                              "\t<1>\n"
                              "         Some Text\n"
                              "     </1>\n"
                              "     <2 param2=\"something\" param3=\"nothing\">\n"
                              "         Pre-Text <Inline>Inlined text</Inline> Inner-text <Inline attr = \"inlined text 2\"/> Post-text.\n"
                              "     </2>\n"
                              "     <3/>\n"
                              "     <4 at=\"1\"  apa  =  \"popo\"/>\n"
                              "     <5   at=\"2\"  apa  = \"uuuu\"     />\n"
                              "     <6   at=\"2\"   ></6>\n"
                              "     <7>    </7>\n"
                              "</0>  ";

    Source* getSource() {
        return new StringSource(TEST_STRING);
    }

    XmlTag* getParsedTag() {
        Source* source = getSource();

        MutableDecoderParams* params = new MutableDecoderParams();
        params->setTrim(true);
        params->setKeepBlankStringValues(false);

        TagBuilder* visitor = new TagBuilder();

        Parser* parser = new XmlParser(source, params, (Visitor*) visitor);

        parser->parse();

        XmlTag* tag = visitor->getRoot();

        return tag;
    }

    TEST(AttributeParse, WHEN_parse_root_tag_EXPECT_one_attribute) {
        int attributesCount = getParsedTag()->getAttributes()->size();
        EXPECT_EQ(attributesCount, 1);
    }

    TEST(AttributeParse, WHEN_parse_second_inner_tag_EXPECT_two_attributes) {
        int attributesCount = getParsedTag()->getValues()->get(1)->asXmlTag()->getAttributes()->size();
        EXPECT_EQ(attributesCount, 2);
    }

    TEST(AttributeParse, WHEN_parse_attributes_with_many_space_delimeters_EXPECT_two_attributes) {
        int attributesCount = getParsedTag()->getValues()->get(4)->asXmlTag()->getAttributes()->size();
        EXPECT_EQ(attributesCount, 2);
    }

    TEST(AttributeParse, WHEN_parse_fourth_inner_tag_EXPECT_two_attributes) {
        auto fourthTag = getParsedTag()->getValues()->get(3)->asXmlTag();

        int attributesCount = fourthTag->getAttributes()->size();
        EXPECT_EQ(attributesCount, 2);
    }

    TEST(AttributeParse, WHEN_parse_fourth_inner_tag_EXPECT_first_attr_name_at) {
        auto fourthTag = getParsedTag()->getValues()->get(3)->asXmlTag();

        std::string firstAttrName = fourthTag->getAttributes()->indexed(0).first;
        EXPECT_EQ(firstAttrName, "at");
    }

    TEST(AttributeParse, WHEN_parse_fourth_inner_tag_EXPECT_first_attr_value_1) {
        auto fourthTag = getParsedTag()->getValues()->get(3)->asXmlTag();

        std::string firstAttrValue = fourthTag->getAttributes()->indexed(0).second;
        EXPECT_EQ(firstAttrValue, "1");
    }

    TEST(AttributeParse, WHEN_parse_fourth_inner_tag_EXPECT_second_attr_name_at) {
        auto fourthTag = getParsedTag()->getValues()->get(3)->asXmlTag();

        std::string secondAttrName = fourthTag->getAttributes()->indexed(1).first;
        EXPECT_EQ(secondAttrName, "apa");
    }

    TEST(AttributeParse, WHEN_parse_fourth_inner_tag_EXPECT_second_attr_value_1) {
        auto fourthTag = getParsedTag()->getValues()->get(3)->asXmlTag();

        std::string secondAttrValue = fourthTag->getAttributes()->indexed(1).second;
        EXPECT_EQ(secondAttrValue, "popo");
    }





    TEST(TagParse, WHEN_parse_closed_tag_EXPECT_name_is_3) {
        auto tagName = getParsedTag()->asXmlTag()->getValues()->get(2)->asXmlTag()->getName();
        EXPECT_EQ(tagName, "3");
    }
    TEST(TagParse, WHEN_parse_empty_tag_EXPECT_no_values) {
        auto valuesCount = getParsedTag()->asXmlTag()->getValues()->get(6)->asXmlTag()->getValues()->size();
        EXPECT_EQ(valuesCount, 0);
    }
    TEST(TagParse, WHEN_parse_second_inner_tag_EXPECT_2_XmlTag_values) {
        auto values = getParsedTag()->getValues()->get(1)->asXmlTag()->getValues();

        int tagCount = 0;
        for (int i = 0; i < values->size(); ++i) {
            if (values->get(i)->isXmlTag()) {
                tagCount++;
            }
        }

        EXPECT_EQ(tagCount, 2);
    }
    TEST(TagParse, WHEN_parse_root_tag_EXPECT_7_XmlTag_values) {
        auto values = getParsedTag()->asXmlTag()->getValues();

        int tagCount = 0;
        for (int i = 0; i < values->size(); ++i) {
            if (values->get(i)->isXmlTag()) {
                tagCount++;
            }
        }

        EXPECT_EQ(tagCount, 7);
    }



    TEST(TextValueParse, WHEN_parse_root_tag_EXPECT_first_value_is_PreText) {
        auto val = getParsedTag()->asXmlTag()->getValues()->get(1)->asXmlTag()->getValues()->get(0)->asXmlPrimitive();
        auto strValue = val->asString();
        EXPECT_EQ(strValue, "Pre-Text");
    }
    TEST(TextValueParse, WHEN_parse_root_tag_EXPECT_third_value_is_InnterText) {
        auto val = getParsedTag()->asXmlTag()->getValues()->get(1)->asXmlTag()->getValues()->get(2)->asXmlPrimitive();
        auto strValue = val->asString();
        EXPECT_EQ(strValue, "Inner-text");
    }
    TEST(TextValueParse, WHEN_parse_root_tag_EXPECT_fifth_value_is_PostText) {
        auto val = getParsedTag()->asXmlTag()->getValues()->get(1)->asXmlTag()->getValues()->get(4)->asXmlPrimitive();
        auto strValue = val->asString();
        EXPECT_EQ(strValue, "Post-text.");
    }
}