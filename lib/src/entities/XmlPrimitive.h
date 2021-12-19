#ifndef XML_RUBAN_XMLPRIMITIVE_H
#define XML_RUBAN_XMLPRIMITIVE_H

#include <ostream>
#include "XmlElement.h"

class XmlPrimitive : public XmlElement {
    private:
    std::string value;

    public:
    XmlPrimitive(std::string value);

    const std::string& getValue() const;
    void setValue(const std::string& value);
    void printTo(std::ostream& oss, int indentation) const override;
    bool isEmpty() const override;
    int size() const override;
    std::string getClassName() override;
    std::string asString() override;
    bool asBoolean();
    char asChar();
    int asInt();
    long asLong();
    float asFloat();
    double asDouble();


};


#endif //XML_RUBAN_XMLPRIMITIVE_H
