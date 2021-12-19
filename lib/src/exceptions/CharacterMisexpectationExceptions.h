#ifndef XML_RUBAN_CHARACTERMISEXPECTATIONEXCEPTIONS_H
#define XML_RUBAN_CHARACTERMISEXPECTATIONEXCEPTIONS_H

#include "rules/Syntax.h"
#include "BaseXmlException.h"
#include "StringUtils.h"

class MisexpectationException : public XmlException {
    public:
    MisexpectationException(int index, const std::string& expected, const std::string& actual) :
            MisexpectationException("MisexpectationException", index, expected, actual) {}
    MisexpectationException(int index, const char expected, const std::string& actual) :
            MisexpectationException("MisexpectationException", index, to_string(expected), actual) {}
    MisexpectationException(int index, const std::string& expected, char actual) :
            MisexpectationException("MisexpectationException", index, expected, to_string(actual)) {}
    MisexpectationException(int index, char expected, char actual) :
            MisexpectationException("MisexpectationException", index, to_string(expected), to_string(actual)) {}

    protected:
    MisexpectationException(const std::string& exceptionName, int index, const std::string& expected, const std::string& actual) :
            XmlException(exceptionName, index, to_string("Expected character '") + expected + "', but '" + actual + "' was found") {}

};

class EqualSignMisexpectationException : public MisexpectationException {
    public:
    EqualSignMisexpectationException(int index, const std::string& actual) :
            EqualSignMisexpectationException("EqualSignMisexpectationException", index, actual) {}
    EqualSignMisexpectationException(int index, char actual) :
            EqualSignMisexpectationException("EqualSignMisexpectationException", index, to_string(actual)) {}

    protected:
    EqualSignMisexpectationException(const std::string& exceptionName, int index, const std::string& actual) :
            MisexpectationException(exceptionName, index, to_string(ATTR_EQ), actual) {}
};

class QuoteSignMisexpectationException : public MisexpectationException {
    public:
    QuoteSignMisexpectationException(int index, const std::string& actual) :
            QuoteSignMisexpectationException("QuoteSignMisexpectationException", index, actual) {}
    QuoteSignMisexpectationException(int index, char actual) :
            QuoteSignMisexpectationException("QuoteSignMisexpectationException", index, to_string(actual)) {}

    protected:
    QuoteSignMisexpectationException(const std::string& exceptionName, int index, const std::string& actual) :
            MisexpectationException(exceptionName, index, to_string(ATTR_QUOTE), actual) {}
};

class WhitespaceMisexpectationException : public MisexpectationException {
    public:
    WhitespaceMisexpectationException(int index, const std::string& actual) :
            WhitespaceMisexpectationException("WhitespaceMisexpectationException", index, actual) {}
    WhitespaceMisexpectationException(int index, char actual) :
            WhitespaceMisexpectationException("WhitespaceMisexpectationException", index, to_string(actual)) {}

    protected:
    WhitespaceMisexpectationException(const std::string& exceptionName, int index, const std::string& actual) :
            MisexpectationException(exceptionName, index, to_string(ATTR_SEPARATOR), actual) {}
};

class CloseBraceMisexpectationException : public MisexpectationException {
    public:
    CloseBraceMisexpectationException(int index, const std::string& actual) :
            CloseBraceMisexpectationException("CloseBraceMisexpectationException", index, actual) {}
    CloseBraceMisexpectationException(int index, char actual) :
            CloseBraceMisexpectationException("CloseBraceMisexpectationException", index, to_string(actual)) {}


    protected:
    CloseBraceMisexpectationException(const std::string& exceptionName, int index, const std::string& expected) :
            MisexpectationException(exceptionName, index, to_string(TAG_END_MARKER), expected) {}
};


#endif //XML_RUBAN_CHARACTERMISEXPECTATIONEXCEPTIONS_H
