#include "../../rules/Syntax.h"
#include "XmlParser.h"
#include "../../exceptions/ParserInternalExceptions.h"
#include "../../exceptions/CharacterMisexpectationExceptions.h"

void XmlParser::setOpenTagReadStarted(char beginning) {
    state = START_READ_TAG;
    state = valueChar(beginning);
}

bool XmlParser::isUsed() const {
    return _isUsed;
}

void XmlParser::requireNotUsed() const {
    if (isUsed()) {
        throw IllegalStateException("This object cannot be used twice. Create a new one");
    }
}

Visitor* XmlParser::parse() {
    requireNotUsed();

    _isUsed = true;

    processSource();

    return visitor;
}

int XmlParser::processSource() {
    i = from;

    while (source->hasNext()) {
        char ch = source->nextChar();

        processChar(ch);

        if (state == TAG_CLOSED) {
            return i;
        }

        ++i;
    }

    return i;
}

void XmlParser::processChar(char ch) {
    int ii = i;
// may add & and ; for advanced string read
    if (ch == TAG_OPEN_BRACE) state = openTagSign();
    else if (ch == TAG_CLOSE_BRACE) state = closeTagSign();
    else if (is_whitespace(ch)) state = whitespace(ch);
    else if (ch == ATTR_EQ) state = equalitySign();
    else if (ch == ATTR_QUOTE) state = quoteSign();
    else if (ch == TAG_END_MARKER) state = endMarker();
    else state = valueChar(ch);

}

ParserState XmlParser::quoteSign() {
    char ch = ATTR_QUOTE;
    switch (state) {
        case NONE: throw IllegalXmlTagStart(i, ch);
        case START_READ_TAG:
        case READ_TAG_NAME:
        case START_READ_CLOSE_TAG_NAME:
        case READ_CLOSE_TAG_NAME: throw IllegalCharInTagNameException(i, ch);
        case INSIDE_TAG: throw IllegalCharInOpenTagException(i, ch);
        case READ_ATTR_NAME: throw IllegalCharInAttrNameException(i, ch);
        case WAIT_FOR_ATTR_EQ_SIGN: throw EqualSignMisexpectationException(i, ch);
        case WAIT_FOR_ATTR_OPEN_QUOTE: return READ_ATTR_VALUE;
        case READ_ATTR_VALUE: {
            readAttributeValue();
            return WAIT_FOR_ONE_WHITESPACE_THEN_INSIDE_TAG;
        }
        case WAIT_FOR_ONE_WHITESPACE_THEN_INSIDE_TAG: throw WhitespaceMisexpectationException(i, ch);
        case READ_TAG_VALUE: return valueChar(ch);
        case CLOSE_MARKER_AFTER_TAG_OPENED: throw IllegalCharAfterTagCloseMarkerException(i, ch);
        case TAG_CLOSED: throw IllegalCharAfterTagEndException(i, ch);
        case WAIT_FOR_ONE_CLOSE_BRACE_THEN_TAG_CLOSE: throw CloseBraceMisexpectationException(i, ch);
        default: throw UnknownSateException(i, state);
    }
}
ParserState XmlParser::equalitySign() {
    char ch = ATTR_EQ;
    switch (state) {
        case NONE: throw IllegalXmlTagStart(i, ch);
        case START_READ_TAG:
        case READ_TAG_NAME:
        case START_READ_CLOSE_TAG_NAME:
        case READ_CLOSE_TAG_NAME: throw IllegalCharInTagNameException(i, ch);
        case INSIDE_TAG: throw IllegalCharInOpenTagException(i, ch);
        case READ_ATTR_NAME: {
            readAttributeName();
            return WAIT_FOR_ATTR_OPEN_QUOTE;
        }
        case WAIT_FOR_ATTR_EQ_SIGN: return WAIT_FOR_ATTR_OPEN_QUOTE;
        case WAIT_FOR_ATTR_OPEN_QUOTE: throw QuoteSignMisexpectationException(i, ch);
        case READ_ATTR_VALUE:
        case READ_TAG_VALUE: {
            return valueChar(ch);
        }
        case WAIT_FOR_ONE_WHITESPACE_THEN_INSIDE_TAG: throw WhitespaceMisexpectationException(i, ch);
        case CLOSE_MARKER_AFTER_TAG_OPENED: throw IllegalCharAfterTagCloseMarkerException(i, ch);
        case TAG_CLOSED: throw IllegalCharAfterTagEndException(i, ch);
        case WAIT_FOR_ONE_CLOSE_BRACE_THEN_TAG_CLOSE: throw CloseBraceMisexpectationException(i, ch);
        default: throw UnknownSateException(i, state);
    }
}
ParserState XmlParser::whitespace(char ch) {
    switch (state) {
        case NONE: return SAME_STATE();
        case START_READ_TAG: throw IllegalCharInTagNameException(i, to_escape_sequence(true));
        case READ_TAG_NAME: {
            createTag();
            return INSIDE_TAG;
        }
        case INSIDE_TAG: return SAME_STATE();
        case READ_ATTR_NAME: {
            if (attrName == nullptr) {
                readAttributeName();
            }
            return WAIT_FOR_ATTR_EQ_SIGN;
        }
        case WAIT_FOR_ATTR_EQ_SIGN: return SAME_STATE();
        case WAIT_FOR_ATTR_OPEN_QUOTE: return SAME_STATE();
        case READ_ATTR_VALUE:return valueChar(ch);
        case WAIT_FOR_ONE_WHITESPACE_THEN_INSIDE_TAG: return INSIDE_TAG;
        case READ_TAG_VALUE: return valueChar(ch);
        case CLOSE_MARKER_AFTER_TAG_OPENED:
        case START_READ_CLOSE_TAG_NAME: throw IllegalCharAfterTagCloseMarkerException(i, ch);
        case TAG_CLOSED: return SAME_STATE();
        case READ_CLOSE_TAG_NAME: return WAIT_FOR_ONE_CLOSE_BRACE_THEN_TAG_CLOSE;
        case WAIT_FOR_ONE_CLOSE_BRACE_THEN_TAG_CLOSE: return SAME_STATE();
        default: throw UnknownSateException(i, state);
    }
}
ParserState XmlParser::endMarker() {
    char ch = TAG_END_MARKER;
    switch (state) {
        case NONE: throw IllegalXmlTagStart(i, ch);
        case START_READ_TAG: {
            if (isOpened) {
                return START_READ_CLOSE_TAG_NAME;
            } else {
                throw IllegalCharInTagNameException(i, ch);
            }
        }
        case READ_TAG_NAME: {
            createTag();
            return CLOSE_MARKER_AFTER_TAG_OPENED;
        }
        case INSIDE_TAG: return CLOSE_MARKER_AFTER_TAG_OPENED;
        case READ_ATTR_NAME: throw IllegalCharInAttrNameException(i, ch);
        case WAIT_FOR_ATTR_EQ_SIGN: throw EqualSignMisexpectationException(i, ch);
        case WAIT_FOR_ATTR_OPEN_QUOTE: throw QuoteSignMisexpectationException(i, ch);
        case READ_ATTR_VALUE: return valueChar(ch);
        case WAIT_FOR_ONE_WHITESPACE_THEN_INSIDE_TAG: return CLOSE_MARKER_AFTER_TAG_OPENED;
        case READ_TAG_VALUE: return valueChar(ch);
        case CLOSE_MARKER_AFTER_TAG_OPENED: throw IllegalCharAfterTagCloseMarkerException(i, ch);
        case TAG_CLOSED: throw IllegalCharAfterTagEndException(i, ch);
        case START_READ_CLOSE_TAG_NAME:
        case READ_CLOSE_TAG_NAME: throw IllegalCharInTagNameException(i, ch);
        case WAIT_FOR_ONE_CLOSE_BRACE_THEN_TAG_CLOSE: throw CloseBraceMisexpectationException(i, ch);
        default: throw UnknownSateException(i, state);
    }
}
ParserState XmlParser::closeTagSign() {
    char ch = TAG_CLOSE_BRACE;
    switch (state) {
        case NONE: throw IllegalXmlTagStart(i, ch);
        case START_READ_TAG:
        case START_READ_CLOSE_TAG_NAME : throw IllegalCharInTagNameException(i ,ch);
        case READ_TAG_NAME: {
            createTag();
            return READ_TAG_VALUE;
        }
        case INSIDE_TAG: {
            markTagIsOpened();
            return READ_TAG_VALUE;
        }
        case READ_ATTR_NAME: throw IllegalCharInAttrNameException(i, ch);
        case WAIT_FOR_ATTR_EQ_SIGN: throw EqualSignMisexpectationException(i, ch);
        case WAIT_FOR_ATTR_OPEN_QUOTE: throw QuoteSignMisexpectationException(i, ch);
        case READ_ATTR_VALUE: throw IllegalCharInAttrValueException(i, ch);
        case WAIT_FOR_ONE_WHITESPACE_THEN_INSIDE_TAG: {
            markTagIsOpened();
            return READ_TAG_VALUE;
        }
        case READ_TAG_VALUE: throw IllegalCharInTagTextValueException(i, ch);
        case CLOSE_MARKER_AFTER_TAG_OPENED: {
            if (visitor != nullptr) {
                std::string openTagName = requireTagNameNotNullOrBlank(tagName);
                try {
                    visitor->onTagClosed(openTagName);
                } catch (TagIsNullException& ex) {
                    throw TagIsNullException(i, state);
                }
            }
            return TAG_CLOSED;
        }
        case TAG_CLOSED: throw IllegalCharAfterTagEndException(i, ch);
        case READ_CLOSE_TAG_NAME:
        case WAIT_FOR_ONE_CLOSE_BRACE_THEN_TAG_CLOSE: {
            closeTag();
            return TAG_CLOSED;
        }
        default: throw UnknownSateException(i, state);
    }
}
ParserState XmlParser::openTagSign() {
    char ch = TAG_OPEN_BRACE;
    switch (state) {
        case NONE: return START_READ_TAG;
        case START_READ_TAG:
        case START_READ_CLOSE_TAG_NAME :
        case READ_TAG_NAME:
        case READ_CLOSE_TAG_NAME: throw IllegalCharInTagNameException(i ,ch);
        case INSIDE_TAG: throw IllegalCharInOpenTagException(i, ch);
        case READ_ATTR_NAME: throw IllegalCharInAttrNameException(i, ch);
        case WAIT_FOR_ATTR_EQ_SIGN: throw EqualSignMisexpectationException(i, ch);
        case WAIT_FOR_ATTR_OPEN_QUOTE: throw QuoteSignMisexpectationException(i, ch);
        case READ_ATTR_VALUE: throw IllegalCharInAttrValueException(i, ch);
        case WAIT_FOR_ONE_WHITESPACE_THEN_INSIDE_TAG: throw WhitespaceMisexpectationException(i, ch);
        case READ_TAG_VALUE: {
            readTextValue();
            return START_READ_TAG; // START_READ_TAG + isOpened=true дают чтение нового внутреннего тэга
        }
        case CLOSE_MARKER_AFTER_TAG_OPENED: throw IllegalCharAfterTagCloseMarkerException(i, ch);
        case TAG_CLOSED: throw IllegalCharAfterTagEndException(i, ch);
        case WAIT_FOR_ONE_CLOSE_BRACE_THEN_TAG_CLOSE: throw CloseBraceMisexpectationException(i, ch);
        default: throw UnknownSateException(i, state);
    }
}
ParserState XmlParser::valueChar(char ch) {
    switch (state) {
        case NONE: throw IllegalXmlTagStart(i, ch);
        case START_READ_TAG: {
            if (isOpened) {
                readTagValue(ch);
                return READ_TAG_VALUE;
            } else {
                append(ch);
                return READ_TAG_NAME;
            }
        }
        case READ_TAG_NAME: {
            append(ch);
            return SAME_STATE();
        }
        case INSIDE_TAG: {
            append(ch);
            return READ_ATTR_NAME;
        }
        case READ_ATTR_NAME: {
            append(ch);
            return SAME_STATE();
        }
        case WAIT_FOR_ATTR_EQ_SIGN: throw EqualSignMisexpectationException(i, ch);
        case WAIT_FOR_ATTR_OPEN_QUOTE: throw QuoteSignMisexpectationException(i, ch);
        case READ_ATTR_VALUE: {
            append(ch);
            return SAME_STATE();
        }
        case WAIT_FOR_ONE_WHITESPACE_THEN_INSIDE_TAG: throw WhitespaceMisexpectationException(i, ch);
        case READ_TAG_VALUE: {
            append(ch);
            return SAME_STATE();
        }
        case CLOSE_MARKER_AFTER_TAG_OPENED: throw IllegalCharAfterTagCloseMarkerException(i, ch);
        case TAG_CLOSED: throw IllegalCharAfterTagEndException(i, ch);
        case START_READ_CLOSE_TAG_NAME : {
            append(ch);
            return READ_CLOSE_TAG_NAME;
        }
        case READ_CLOSE_TAG_NAME: {
            append(ch);
            return SAME_STATE();
        }
        case WAIT_FOR_ONE_CLOSE_BRACE_THEN_TAG_CLOSE: throw CloseBraceMisexpectationException(i, ch);
        default: throw UnknownSateException(i, state);
    }
}

void XmlParser::readTagValue(char ch) {
    XmlParser innerParser = XmlParser(source, params, visitor, i+1); // +1 as '<' is already consumed
    innerParser.setOpenTagReadStarted(ch);

    i = innerParser.processSource();
}

void XmlParser::readTextValue() {
    checkTagIsOpened();

    if (buf.isNotEmpty()) {
        if (buf.isNotBlank() || params->isKeepBlankStringValues()) {
            std::string textValue = buf.extract();
            trimIfNeed(textValue);

            if (visitor != nullptr) {
                try {
                    visitor->onTagTextValue(textValue);
                } catch (TagIsNullException& ex) {
                    throw TagIsNullException(i, state);
                }
            }
        }

        buf.clear();
    }
}

void XmlParser::readAttributeValue() {
    std::string value = buf.extract();
    value = requireAttrValueNotNull(&value);

    std::string name = requireAttrNameNotNullOrBlank(attrName);

    if (visitor != nullptr) {
        try {
            visitor->onAttribute(name, value);
        } catch (TagIsNullException& ex) {
            throw TagIsNullException(i, state);
        }
    }
//
//    tag->addAttribute(name, value);

    attrName = nullptr;
}

void XmlParser::readAttributeName() {
    attrName = new std::string();
    *attrName = buf.extract();

    trimIfNeed(*attrName);
}

void XmlParser::createTag() {

    std::string tagName = buf.extract();
    tagName = requireTagNameNotNullOrBlank(&tagName);
    this->tagName = new std::string();
    *this->tagName = tagName;

    markTagIsOpened();

    if (visitor != nullptr) {
        try {
            visitor->onTagOpen(tagName);
        } catch (TagIsNullException& ex) {
            throw TagIsNullException(i, state);
        }
    }
}

void XmlParser::closeTag() {
    std::string closeTagName = buf.extract();
    closeTagName = requireTagNameNotNullOrBlank(&closeTagName);
    std::string openTagName = requireTagNameNotNullOrBlank(tagName);

    if (closeTagName != openTagName) {
        throw TagNamesAreDifferentException(i, state, openTagName, closeTagName);
    }

    if (visitor != nullptr) {
        try {
            visitor->onTagClosed(closeTagName);
        } catch (TagIsNullException& ex) {
            throw TagIsNullException(i, state);
        }
    }
}

void XmlParser::markTagIsOpened() {
    isOpened = true;
}

std::string& XmlParser::trimIfNeed(std::string& text) {
    if (params->isTrim()) {
        return trim(text);
    }
    return text;
}

void XmlParser::append(const std::string& s) {
    buf.append(s);
}

void XmlParser::append(char c) {
    buf.append(to_string(c));
}

ParserState XmlParser::SAME_STATE() {
    return state;
}


std::string XmlParser::requireTagNameNotNullOrBlank(std::string* tagName) {
    if (tagName == nullptr) {
        throw TagNameIsNullException(i, state);
    }
    if (is_blank(*tagName)) {
        throw TagNameIsBlankException(i, state);
    }
    return *tagName;
}

std::string XmlParser::requireAttrValueNotNull(std::string* attrValue) {
    if (attrValue == nullptr) {
        throw AttrValueIsNullException(i, state);
    }
    return *attrValue;
}

std::string XmlParser::requireAttrNameNotNullOrBlank(std::string* attrName) {
    if (attrName == nullptr) {
        throw AttrNameIsNullException(i, state);
    }
    if (is_blank(*attrName)) {
        throw AttrNameIsBlankException(i, state);
    }
    return *attrName;
}

void XmlParser::checkTagIsOpened() {
    if (!isOpened) {
        throw TagIsNotOpenedException(i, state);
    }
}

XmlParser::XmlParser(Source* source, DecoderParams* params, Visitor* visitor, int from) :
        source(source), params(params), visitor(visitor), from(from) {
    if (from < 0) {
        std::stringstream ss;
        ss << "From cant be less than 0: " << from;
        throw std::out_of_range(ss.str());
    }
}
XmlParser::XmlParser(Source* source, DecoderParams* params, Visitor* visitor) :
        XmlParser(source, params, visitor, 0) {
}
XmlParser::~XmlParser() {
    delete tagName;
    delete attrName;
}
