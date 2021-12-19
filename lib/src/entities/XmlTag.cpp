#include "../rules/Syntax.h"
#include "XmlTag.h"
#include "XmlPrimitive.h"

void XmlTag::addElementToValues(XmlElement* xmlElement) {
    values->put(xmlElement);
}
void XmlTag::addValue(std::string text) {
    addElementToValues(new XmlPrimitive(std::move(text)));
}
void XmlTag::addValue(XmlTag* tag) {
    addElementToValues(tag);
}
void XmlTag::addAttribute(std::string name, std::string value) {
    attributes->put(std::move(name), std::move(value));
}
void XmlTag::printTo(std::ostream& os, int indentation) const {
    std::string indentations = repeat(INDENTATION, indentation);
    os << indentations
       << name;
    if (attributes->isNotEmpty()) {
        os << " (";
        attributes->printTo(os, indentation);
        os << ")";
    }
    os << " {";
    if (values->isNotEmpty()) {
        os << '\n';
        values->printTo(os, indentation + 1);
        os << '\n'
           << indentations;
    }
    os << '}';
}
XmlTag::XmlTag(std::string name, XmlValues* values, XmlAttributes* attributes) : name(std::move(name)), values(values),
        attributes(attributes) {}

XmlTag::XmlTag(std::string name, XmlAttributes* attributes) : XmlTag(std::move(name), new XmlValues(), attributes) {}

XmlTag::XmlTag(std::string name, XmlValues* values) : XmlTag(std::move(name), values, new XmlAttributes()) {}

XmlTag::XmlTag(std::string name) : XmlTag(std::move(name), new XmlValues(), new XmlAttributes()) {}

std::string XmlTag::asString() {
    // allow extracting string of single inner tag
    if (values->isSingle()) {
        return values->single()->asString();
    }
    return XmlElement::asString();
}
bool XmlTag::isEmpty() const {
    return values->isEmpty();
}
int XmlTag::size() const {
    return values->size();
}
std::string XmlTag::getClassName() {
    return "XmlTag";
}

std::ostream& operator<<(std::ostream& os, const XmlTag& tag) {
    tag.printTo(os, 0);
    return os;
}
std::string XmlTag::getName() const {
    return name;
}
XmlValues* XmlTag::getValues() const {
    return values;
}
XmlAttributes* XmlTag::getAttributes() const {
    return attributes;
}
void XmlTag::setName(const std::string& name) {
    XmlTag::name = name;
}
void XmlTag::setValues(XmlValues* values) {
    XmlTag::values = values;
}
void XmlTag::setAttributes(XmlAttributes* attributes) {
    XmlTag::attributes = attributes;
}

XmlTag* XmlTag::firstOrNullTag(const std::string& tagName) {
    int limit = values->size();
    for (int i = 0; i < limit; ++i) {
        XmlElement* element = values->get(i);
        if (element->isXmlTag()) {
            XmlTag* tag = element->asXmlTag();
            if (tag->name == tagName) {
                return tag;
            }
        }
    }

    return nullptr;
}

void XmlTag::forEachTag(const std::function<void(int, XmlTag*)>& consumer) {
    values->forEachTag(consumer);
}
void XmlTag::forEachPrimitive(const std::function<void(int, XmlPrimitive*)>& consumer) {
    values->forEachPrimitive(consumer);
}
void XmlTag::forEachAttribute(const std::function<void(int, const std::string&, const std::string&)>& consumer) {
    attributes->forEachAttribute(consumer);
}

XmlTag::~XmlTag() {
    delete values;
    delete attributes;
}
