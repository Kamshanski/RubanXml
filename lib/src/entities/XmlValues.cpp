#include "XmlValues.h"
#include "XmlTag.h"
#include "XmlPrimitive.h"

int XmlValues::size() const { return elements.size(); }

bool XmlValues::isEmpty() const { return elements.empty(); }

XmlElement* XmlValues::get(int index) { return elements[index]; }

void XmlValues::put(XmlElement* element) { elements.push_back(element); }

bool XmlValues::isSingle() { return elements.size() == 1; }

bool XmlValues::isLastPrimitive() const { return instanceof<XmlPrimitive>(elements[0]); }

bool XmlValues::isFirstTag()  const { return instanceof<XmlTag>(elements[size() - 1]); }

void XmlValues::printTo(std::ostream& oss, int indentation) const{
    int limit = size();
    for (int i = 0; i < limit; ++i) {
        XmlElement* element = elements[i];
        element->printTo(oss, indentation);
        if (i < limit) {
            oss << "," << std::endl;
        }
    }
}

std::string XmlValues::getClassName() {
    return "XmlValues";
}
XmlElement* XmlValues::single() {
    return elements[0];
}
std::string XmlValues::asString() {
    if (isSingle()) {
        return single()->asString();
    }
    return XmlElement::asString();
}
XmlValues::~XmlValues() {
    for (XmlElement* e: elements) {
        delete e;
    }
}
XmlTag* XmlValues::firstOrNullTag(const std::string& tagName) {
    int limit = size();
    for (int i = 0; i < limit; ++i) {
        XmlElement* element = get(i);
        if (element->isXmlTag()) {
            XmlTag* tag = element->asXmlTag();
            if (tag->getName() == tagName) {
                return tag;
            }
        }
    }

    return nullptr;
}
void XmlValues::forEachTag(const std::function<void(int, XmlTag*)>& consumer) {
    int limit = size();
    for (int i = 0; i < limit; ++i) {
        XmlElement* element = elements[0];
        if (element->isXmlTag()) {
            XmlTag* tag = element->asXmlTag();
            consumer(i, tag);
        }
    }

}
void XmlValues::forEachPrimitive(const std::function<void(int, XmlPrimitive*)>& consumer) {
    int limit = size();
    for (int i = 0; i < limit; ++i) {
        XmlElement* element = elements[0];
        if (element->isXmlTag()) {
            XmlPrimitive* primitive = element->asXmlPrimitive();
            consumer(i, primitive);
        }
    }
}


