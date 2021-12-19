#ifndef XML_RUBAN_XMLELEMENT_H
#define XML_RUBAN_XMLELEMENT_H

#include <string>
#include <ostream>
#include "../_utils/ExceptionsExtensions.h"
#include "../_utils/ClassExctensions.h"

class XmlTag;

class XmlPrimitive;

class XmlElement : Object {
public:

    bool isXmlTag() const;
    bool isXmlPrimitive() const;

    XmlTag* asXmlTag();
    XmlPrimitive* asXmlPrimitive();

    virtual std::string asString();

    virtual int size() const;
    virtual bool isEmpty() const;
    bool isNotEmpty() const;

    // Only for toString() (or ostream <<)output
    virtual void printTo(std::ostream& oss, int indentation) const= 0;

    std::string getClassName() override;

    // это убожество нужно, чтоб компилятор не кидал ошибку, если D instanceof C, где D:A, C:A
    //https://stackoverflow.com/questions/15114093/getting-source-type-is-not-polymorphic-when-trying-to-use-dynamic-cast
    virtual ~XmlElement() = default;
};


#endif //XML_RUBAN_XMLELEMENT_H
