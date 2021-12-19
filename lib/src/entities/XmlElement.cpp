#include "ClassExctensions.h"
#include "ExceptionsExtensions.h"
#include <string>
#include "XmlElement.h"
#include "XmlTag.h"
#include "XmlPrimitive.h"

std::string XmlElement::getClassName() {
    return {"XmlElement"};
}

bool XmlElement::isXmlTag() const {
    return instanceof<XmlTag>(this);
}

bool XmlElement::isXmlPrimitive() const {
    return instanceof<XmlPrimitive>(this);
}

XmlTag* XmlElement::asXmlTag() {
    if (instanceof<XmlTag>(this))
        return dynamic_cast<XmlTag*>(this);
    else
        throw BadCastException<XmlTag>();

}

XmlPrimitive* XmlElement::asXmlPrimitive() {
    if (instanceof<XmlPrimitive>(this))
        return dynamic_cast<XmlPrimitive*>(this);
    else
        throw BadCastException<XmlPrimitive>();
}

std::string XmlElement::asString() {
    throw UnsupportedOperationException("Cannot cast this XML element as String");
}
bool XmlElement::isEmpty() const {
    throw UnsupportedOperationException("This XML element has no size");
}
bool XmlElement::isNotEmpty() const {
    return !isEmpty();
}
int XmlElement::size() const {
    throw UnsupportedOperationException("This XML element has no size");
}
