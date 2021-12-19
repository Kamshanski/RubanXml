#ifndef XML_RUBAN_PARSER_H
#define XML_RUBAN_PARSER_H


#include "../../source/Source.h"
#include "../DecoderParams.h"
#include "../../_utils/StringBuilder.h"
#include "../../entities/XmlTag.h"
#include "Visitor.h"
#include "Parser.h"
#include "ParserState.h"

class XmlParser : public Parser {
private:
    Source* source;
    DecoderParams* params;
    Visitor* visitor = nullptr;

    ParserState state = ParserState::NONE;
    int i = 0;
    int from = 0;
    StringBuilder buf;

    bool isOpened = false;

    std::string* tagName = nullptr;
    std::string* attrName = nullptr;

    bool _isUsed = false;
////////////////////////////////////////////////////////
    void setOpenTagReadStarted(char beginning);
    XmlParser(Source* source, DecoderParams* params, Visitor* visitor, int i);
public:
    XmlParser(Source* source, DecoderParams* params, Visitor* visitor);

    bool isUsed() const override ;
    void requireNotUsed() const override;

    Visitor* parse() override;
private:

    int processSource();
    void processChar(char ch);

    ParserState quoteSign();
    ParserState equalitySign();
    ParserState whitespace(char ch);
    ParserState endMarker();
    ParserState closeTagSign();
    ParserState openTagSign();
    ParserState valueChar(char ch);

    void readTagValue(char ch);
    void readTextValue();
    void readAttributeValue();
    void readAttributeName();
    void createTag();
    void closeTag();
    void markTagIsOpened();

    std::string& trimIfNeed(std::string& text);

    void append(const std::string& s);
    void append(char c);

    ParserState SAME_STATE();

    XmlTag* requireTagNotNull(XmlTag* tag, bool inner = false);
    std::string requireTagNameNotNullOrBlank(std::string* tagName);
    std::string requireAttrValueNotNull(std::string* attrValue);
    std::string requireAttrNameNotNullOrBlank(std::string* attrName);

    void checkTagIsOpened();

public:
    virtual ~XmlParser();
};


#endif //XML_RUBAN_PARSER_H
