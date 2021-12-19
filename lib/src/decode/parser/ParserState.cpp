#include <string>
#include "ParserState.h"

//https://stackoverflow.com/questions/5093460/how-to-convert-an-enum-type-variable-to-a-string
std::string to_string(ParserState v) {
    switch (v) {
        case NONE: return { "NONE" };
        case START_READ_TAG: return { "START_READ_TAG" };
        case READ_TAG_NAME: return { "READ_TAG_NAME" };
        case INSIDE_TAG: return { "INSIDE_TAG" };
        case READ_ATTR_NAME: return { "READ_ATTR_NAME" };
        case WAIT_FOR_ATTR_EQ_SIGN: return { "WAIT_FOR_ATTR_EQ_SIGN" };
        case WAIT_FOR_ATTR_OPEN_QUOTE: return { "WAIT_FOR_ATTR_OPEN_QUOTE" };
        case READ_ATTR_VALUE: return { "READ_ATTR_VALUE" };
        case WAIT_FOR_ONE_WHITESPACE_THEN_INSIDE_TAG: return {"WAIT_FOR_ONE_WHITESPACE_THEN_INSIDE_TAG" };
        case READ_TAG_VALUE: return { "READ_TAG_VALUE" };
        case TAG_CLOSED: return { "TAG_CLOSED" };
        case CLOSE_MARKER_AFTER_TAG_OPENED: return {"CLOSE_MARKER_AFTER_TAG_OPENED" };
        case START_READ_CLOSE_TAG_NAME: return { "START_READ_CLOSE_TAG_NAME" };
        case READ_CLOSE_TAG_NAME: return { "READ_CLOSE_TAG_NAME" };
        case WAIT_FOR_ONE_CLOSE_BRACE_THEN_TAG_CLOSE: return { "WAIT_FOR_ONE_CLOSE_BRACE_THEN_TAG_CLOSE" };
        default: return { "[Unknown XmlParser State]" };
    }
}
