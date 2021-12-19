#ifndef XML_RUBAN_PARSERINTERNALEXCEPTIONS_H
#define XML_RUBAN_PARSERINTERNALEXCEPTIONS_H

#include "decode/parser/ParserState.h"

class XmlParserError : public XmlException {
public:
    XmlParserError(int index, ParserState state, const std::string& msg) :
            XmlParserError("XmlParserError", index, state, msg) {}

protected:
    XmlParserError(const std::string& exceptionName, int index, ParserState state, const std::string& msg) :
            XmlException(exceptionName, index, to_string("at parser state '") + to_string(state) + "' " + msg) {}
};


class UnknownSateException : public XmlParserError {
public:
    UnknownSateException(int index, ParserState state) :
            UnknownSateException("UnknownSateException", index, state) {}

protected:
    UnknownSateException(const std::string& exceptionName, int index, ParserState state) :
            XmlParserError(exceptionName, index, state, "Unknown state") {}
};

class TagNamesAreDifferentException : public XmlParserError {
public:
    TagNamesAreDifferentException(int index, ParserState state, const std::string& openTagName,
                                  const std::string& closeTagName) :
            TagNamesAreDifferentException("TagNamesAreDifferentException", index, state, openTagName, closeTagName) {}

protected:
    TagNamesAreDifferentException(const std::string& exceptionName, int index, ParserState state,
                                  const std::string& openTagName,
                                  const std::string& closeTagName) :
            XmlParserError(exceptionName, index, state,
                           to_string("Open and Close tag are different: [") + openTagName + "] vs [" + closeTagName +
                           "]") {}
};

class TagIsNullException : public XmlParserError {
public:
    TagIsNullException(int index, ParserState state) :
            TagIsNullException("IllegalXmlTagStart", index, state) {}

protected:
    TagIsNullException(const std::string& exceptionName, int index, ParserState state) :
            XmlParserError(exceptionName, index, state, "Tag is null") {}
};


class InnerTagIsNullException : public XmlParserError {
public:
    InnerTagIsNullException(int index, ParserState state) :
            InnerTagIsNullException("InnerTagIsNullException", index, state) {}

protected:
    InnerTagIsNullException(const std::string& exceptionName, int index, ParserState state) :
            XmlParserError(exceptionName, index, state, "Inner tag is null") {}
};

class TagNameIsNullException : public XmlParserError {
public:
    TagNameIsNullException(int index, ParserState state) :
            TagNameIsNullException("TagNameIsNullException", index, state) {}

protected:
    TagNameIsNullException(const std::string& exceptionName, int index, ParserState state) :
            XmlParserError(exceptionName, index, state, "Tag name is null") {}
};

class AttrNameIsNullException : public XmlParserError {
public:
    AttrNameIsNullException(int index, ParserState state) :
            AttrNameIsNullException("AttrNameIsNullException", index, state) {}

protected:
    AttrNameIsNullException(const std::string& exceptionName, int index, ParserState state) :
            XmlParserError(exceptionName, index, state, "Attribute name is null") {}
};

class AttrNameIsBlankException : public XmlParserError {
public:
    AttrNameIsBlankException(int index, ParserState state) :
            AttrNameIsBlankException("AttrNameIsBlankException", index, state) {}

protected:
    AttrNameIsBlankException(const std::string& exceptionName, int index, ParserState state) :
            XmlParserError(exceptionName, index, state, "Attribute name is black") {}
};

class AttrValueIsNullException : public XmlParserError {
public:
    AttrValueIsNullException(int index, ParserState state) :
            AttrValueIsNullException("AttrValueIsNullException", index, state) {}

protected:
    AttrValueIsNullException(const std::string& exceptionName, int index, ParserState state) :
            XmlParserError(exceptionName, index, state, "Attribute value is null") {}
};

class TagIsNotOpenedException : public XmlParserError {
public:
    TagIsNotOpenedException(int index, ParserState state) :
            TagIsNotOpenedException("TagIsNotOpenedException", index, state) {}

protected:
    TagIsNotOpenedException(const std::string& exceptionName, int index, ParserState state) :
            XmlParserError(exceptionName, index, state, "Tag is not opened at state") {}
};

class TagNameIsBlankException : public XmlParserError {
public:
    TagNameIsBlankException(int index, ParserState state) :
            TagNameIsBlankException("TagNameIsBlankException", index, state) {}

protected:
    TagNameIsBlankException(const std::string& exceptionName, int index, ParserState state) :
            XmlParserError(exceptionName, index, state, "Tag name is blank") {}
};


#endif //XML_RUBAN_PARSERINTERNALEXCEPTIONS_H
