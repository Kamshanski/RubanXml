#ifndef XML_RUBAN_PARSERSTATE_H
#define XML_RUBAN_PARSERSTATE_H


enum ParserState {
    NONE,
    START_READ_TAG,
    READ_TAG_NAME,
    INSIDE_TAG,
    READ_ATTR_NAME,
    WAIT_FOR_ATTR_EQ_SIGN,
    WAIT_FOR_ATTR_OPEN_QUOTE,
    READ_ATTR_VALUE,
    WAIT_FOR_ONE_WHITESPACE_THEN_INSIDE_TAG,
    READ_TAG_VALUE,
    TAG_CLOSED,
    CLOSE_MARKER_AFTER_TAG_OPENED,
    START_READ_CLOSE_TAG_NAME,
    READ_CLOSE_TAG_NAME,
    WAIT_FOR_ONE_CLOSE_BRACE_THEN_TAG_CLOSE
};


//https://stackoverflow.com/questions/5093460/how-to-convert-an-enum-type-variable-to-a-string
std::string to_string(ParserState v);

#endif //XML_RUBAN_PARSERSTATE_H
