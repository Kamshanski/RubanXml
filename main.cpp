
#include <iostream>
#include <src/decode/DecoderParams.h>
#include <plog/Init.h>
#include "lib/include/xml_ruban/RubanXml.h"
#include "lib/include/xml_ruban/RubanXmlBuilder.h"



std::string TEST_XML_STRING = "<0 param=\"value\">\n"
                              "     <1>\n"
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
                              "</0>";


class MyVisitor : public Visitor {
    void onAttribute(std::string attrName, std::string attrValue) override {
        std::cout << "Found attribute: " << attrName << "=" << attrValue << std::endl;
    }
    void onTagOpen(std::string tagName) override {
        std::cout << "Tag opened: " << tagName << std::endl;
    }
    void onTagClosed(std::string tagName) override {
        std::cout << "Tag closed: " << tagName << std::endl;
    }
    void onTagTextValue(std::string tagTextValue) override {
        std::cout << "Tag text value: " << tagTextValue << std::endl;
    }
};

void testVisitor() {
    Visitor* visitor = new MyVisitor();
    StringSource ss = StringSource(TEST_XML_STRING);

    RubanXmlBuilder* builder = (new RubanXmlBuilder())
            ->setLoggingLevel(plog::error, "ERROR_VISITOR.txt")
            ->shortenEmptyTags(true)
            ->keepBlankStringValues(false)
            ->setPrettyPrinting(true)
            ->setTrim(true);
    RubanXml rx = builder->create();

    rx.parseFromSource(&ss, visitor);

    delete visitor;
}

void testString() {
    std::cout << "\n\nTest String\n\n";

    RubanXmlBuilder* builder = (new RubanXmlBuilder())
            ->setLoggingLevel(plog::debug, "DEBUG_STRING.txt")
            ->shortenEmptyTags(true)
            ->keepBlankStringValues(false)
            ->setPrettyPrinting(true)
            ->setTrim(true);
    RubanXml rx = builder->create();

    auto tag = rx.xmlTreeFromString(TEST_XML_STRING);
    std::cout << rx.xmlTagToString(tag) << std::endl;

    delete builder;
    delete tag;
}

void testFile(std::string sourcePath, std::string sinkPath) {
    std::cout << "\n\nTest File\n\n";

    RubanXmlBuilder* builder = (new RubanXmlBuilder())
            ->setLoggingLevel(plog::info, "INFO_FILE.txt")
            ->shortenEmptyTags(true)
            ->keepBlankStringValues(false)
            ->setPrettyPrinting(true)
            ->setTrim(true);
    RubanXml rx = builder->create();

    auto tag = rx.xmlTreeFromFile(sourcePath);

    rx.xmlTagToFile(tag, std::move(sinkPath));

    delete builder;
    delete tag;
}

void testCustomTree() {
    std::cout << "\n\nTest Custom Tree\n\n";

    RubanXmlBuilder* builder = (new RubanXmlBuilder())
            ->setLoggingLevel(plog::debug, "DEBUG.txt")
            ->shortenEmptyTags(true)
            ->keepBlankStringValues(false)
            ->setPrettyPrinting(true)
            ->setTrim(true);
    RubanXml rx = builder->create();

    auto rootTag = new XmlTag("Tag1");
    rootTag->addAttribute("attr1", "val1");
    rootTag->addAttribute("attr2", "val2");

    rootTag->addValue("Text Before");

    auto innerTag1 = new XmlTag("attrTag");
    innerTag1->addAttribute("attrTag2", "valTag2");
    rootTag->addValue(innerTag1);

    auto innerTag2 = new XmlTag("Integer");
    innerTag2->addValue("1234");
    rootTag->addValue(innerTag2);

    auto innerTag3 = new XmlTag("EmptyTag");
    rootTag->addValue(innerTag3);

    auto innerTag4 = new XmlTag("Boolean");
    innerTag4->addValue("tRuE");
    rootTag->addValue(innerTag4);

    rootTag->addValue("Text After");

    rootTag->getValues();

    std::cout << rx.xmlTagToString(rootTag) << std::endl;

    XmlTag* intTag = rootTag->firstOrNullTag("Integer");
    if (intTag != nullptr) {
        std::cout << "Integer tag = " << intTag->getValues()->single()->asXmlPrimitive()->asInt() << std::endl;
    } else {
        std::cout << "Integer tag was not found" << std::endl;
    }

    XmlTag* boolTag = rootTag->firstOrNullTag("Boolean");
    if (boolTag != nullptr) {
        std::cout << "Boolean tag = " << std::boolalpha << boolTag->getValues()->single()->asXmlPrimitive()->asBoolean() << std::endl;
    } else {
        std::cout << "Boolean tag was not found" << std::endl;
    }


    delete builder;
    delete rootTag;
}

int main() {
    // Замечания:
    // создавать XmlTag в visitor +
    // сделать source closeable +
    // обрабатывать ошибки, чтобы закрыть файл +

    testVisitor();

//    testString();

//    testFile("C:\\Users\\Dawan\\Desktop\\source.xml", "C:\\Users\\Dawan\\Desktop\\sink.xml");

//    testCustomTree();

    return 0;
}