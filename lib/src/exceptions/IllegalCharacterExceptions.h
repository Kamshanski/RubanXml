#ifndef XML_RUBAN_ILLEGALCHARACTEREXCEPTIONS_H
#define XML_RUBAN_ILLEGALCHARACTEREXCEPTIONS_H

#include "string"
#include "iostream"
#include "BaseXmlException.h"
#include "../_utils/StringUtils.h"

class IllegalCharacterException : public XmlException {
    public:
    IllegalCharacterException(int index, const std::string& character, const std::string& where) : IllegalCharacterException("IllegalCharacterException", index, character, where) {}
    IllegalCharacterException(int index, char character, const std::string& where) : IllegalCharacterException("IllegalCharacterException", index, to_string(character), where) {}

    protected:
    IllegalCharacterException(const std::string& exceptionName, int index, const std::string& character, const std::string& where) :
            XmlException(exceptionName, index, to_string("Character '") + character + "' is not allowed in '" + where + "'") {}
};



class IllegalXmlTagStart : public IllegalCharacterException {
    public:
    IllegalXmlTagStart(int index, const std::string& character) :
        IllegalXmlTagStart("IllegalXmlTagStart", index, character) {}
    IllegalXmlTagStart(int index, char character) :
        IllegalXmlTagStart("IllegalXmlTagStart", index, to_string(character)) {}

    protected:
    IllegalXmlTagStart(const std::string& exceptionName, int index, const std::string& character) :
            IllegalCharacterException(exceptionName, index, character, "before open tag") {}

};


class IllegalCharInTagNameException : public IllegalCharacterException {
    public:
    IllegalCharInTagNameException(int index, const std::string& character) :
            IllegalCharInTagNameException("IllegalCharInTagNameException", index, character) {}
    IllegalCharInTagNameException(int index, char character) :
            IllegalCharInTagNameException("IllegalCharInTagNameException", index, to_string(character)) {}

    protected:
    IllegalCharInTagNameException(const std::string& exceptionName, int index, const std::string& character) :
            IllegalCharacterException(exceptionName, index, character, "tag name") {}

};

class IllegalCharInTagTextValueException : public IllegalCharacterException {
    public:
    IllegalCharInTagTextValueException(int index, const std::string& character) :
            IllegalCharInTagTextValueException("IllegalCharInTagTextValueException", index, character) {}
    IllegalCharInTagTextValueException(int index, char character) :
            IllegalCharInTagTextValueException("IllegalCharInTagTextValueException", index, to_string(character)) {}

    protected:
    IllegalCharInTagTextValueException(const std::string& exceptionName, int index, const std::string& character) :
            IllegalCharacterException(exceptionName, index, character, "tag text value") {}
};

class IllegalCharInOpenTagException : public IllegalCharacterException {
    public:
    IllegalCharInOpenTagException(int index, const std::string& character) :
            IllegalCharInOpenTagException("IllegalCharInOpenTagException", index, character) {}
    IllegalCharInOpenTagException(int index, char character) :
            IllegalCharInOpenTagException("IllegalCharInOpenTagException", index, to_string(character)) {}

    protected:
    IllegalCharInOpenTagException(const std::string& exceptionName, int index, const std::string& character) :
            IllegalCharacterException(exceptionName, index, character, "open tag") {}
};


class IllegalCharInAttrNameException : public IllegalCharacterException {
    public:
    IllegalCharInAttrNameException(int index, const std::string& character) :
            IllegalCharInAttrNameException("IllegalCharInAttrNameException", index, character) {}
    IllegalCharInAttrNameException(int index, char character) :
            IllegalCharInAttrNameException("IllegalCharInAttrNameException", index, to_string(character)) {}

    protected:
    IllegalCharInAttrNameException(const std::string& exceptionName, int index, const std::string& character) :
            IllegalCharacterException(exceptionName, index, character, "attr name") {}
};

class IllegalCharInAttrValueException : public IllegalCharacterException {
    public:
    IllegalCharInAttrValueException(int index, const std::string& character) :
            IllegalCharInAttrValueException("IllegalCharInAttrValueException", index, character) {}
    IllegalCharInAttrValueException(int index, char character) :
            IllegalCharInAttrValueException("IllegalCharInAttrValueException", index, to_string(character)) {}

    protected:
    IllegalCharInAttrValueException(const std::string& exceptionName, int index, const std::string& character) :
            IllegalCharacterException(exceptionName, index, character, "attr valeu") {}
};

class IllegalCharAfterTagCloseMarkerException : public IllegalCharacterException {
    public:
    IllegalCharAfterTagCloseMarkerException(int index, const std::string& character) :
            IllegalCharAfterTagCloseMarkerException("IllegalCharAfterTagCloseMarkerException", index, character) {}
    IllegalCharAfterTagCloseMarkerException(int index, char character) :
            IllegalCharAfterTagCloseMarkerException("IllegalCharAfterTagCloseMarkerException", index, to_string(character)) {}

    protected:
    IllegalCharAfterTagCloseMarkerException(const std::string& exceptionName, int index, const std::string& character) :
            IllegalCharacterException(exceptionName, index, character, "tag close marker") {}
};

class IllegalCharAfterTagEndException : public IllegalCharacterException {
    public:
    IllegalCharAfterTagEndException(int index, const std::string& character) :
            IllegalCharAfterTagEndException("IllegalCharAfterTagEndException", index, character) {}
    IllegalCharAfterTagEndException(int index, char character) :
            IllegalCharAfterTagEndException("IllegalCharAfterTagEndException", index, to_string(character)) {}

    protected:
    IllegalCharAfterTagEndException(const std::string& exceptionName, int index, const std::string& character) :
            IllegalCharacterException(exceptionName, index, character, "after close tag") {}
};










#endif //XML_RUBAN_ILLEGALCHARACTEREXCEPTIONS_H
