#include "LinkedMap.h"
#include "XmlAttributes.h"
#include "../rules/CharExcapeRules.h"
#include "../exceptions/IllegalCharacterExceptions.h"

bool XmlAttributes::isEmpty() const {
    return attributes.isEmpty();
}

int XmlAttributes::size() const {
    return attributes.size();
}

void XmlAttributes::printTo(std::ostream& os, int indentation) const{
    int limit = size();
    for (int i = 0; i < limit; ++i) {
        attributes.forEachIndexed([&os, limit](int i, const std::string& name, const std::string& value) {
            os << name
               << "="
               << value;

            if (i < limit) {
                os << ", ";
            }
        });
    }
}
std::string XmlAttributes::getClassName() {
    return "XmlAttributes";
}
std::string XmlAttributes::get(const std::string& name) {
    return attributes.get(name);
}
void XmlAttributes::put(std::string name, std::string value) {
    int illegalNameCharIndex = name.find_first_of(ILLEGAL_TEXT_VALUE_CHARS);
    if (illegalNameCharIndex != std::string::npos) {
        throw IllegalCharacterException(illegalNameCharIndex, name[illegalNameCharIndex], "text name");
    }

    int illegalValueCharIndex = value.find_first_of(ILLEGAL_TEXT_VALUE_CHARS);
    if (illegalValueCharIndex != std::string::npos) {
        throw IllegalCharacterException(illegalValueCharIndex, value[illegalValueCharIndex], "text value");
    }

    attributes.put(name, value);
}
void XmlAttributes::putAll(LinkedMap<std::string, std::string>& attrs) {
    attrs.forEachIndexed([this](int i, std::string& name, std::string& value) {
        put(name, value);
    });
}

std::pair<std::string, std::string> XmlAttributes::indexed(int index) {
    return attributes.indexed(index);
}
void XmlAttributes::forEachAttribute(const std::function<void(int, const std::string&, const std::string&)>& consumer) {
    int limit = size();
    for (int i = 0; i < limit; ++i) {
        std::pair<std::string, std::string> pair = attributes.indexed(i);
        consumer(i, pair.first, pair.second);
    }
}
