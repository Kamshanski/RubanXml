#include <ostream>
#include "../rules/CharExcapeRules.h"
#include "../rules/Syntax.h"
#include "XmlPrimitive.h"
#include "../exceptions/IllegalCharacterExceptions.h"


XmlPrimitive::XmlPrimitive(std::string value) : value(std::move(value)) {
    auto illegalCharIndex = value.find_first_of(ILLEGAL_TEXT_VALUE_CHARS);
    if (illegalCharIndex != std::string::npos) {
        throw IllegalCharacterException(illegalCharIndex, value[illegalCharIndex], "text value");
    }
}

std::string XmlPrimitive::asString() {
    return value;
}



bool XmlPrimitive::isEmpty() const { return value.empty(); }
int XmlPrimitive::size() const { return value.size(); }

std::string XmlPrimitive::getClassName() {
    return "XmlPrimitive";
}

void XmlPrimitive::printTo(std::ostream& oss, int indentation) const{
    oss << repeat(INDENTATION, indentation)
        << "<primitive> {"
        << value
        << "}";
}
const std::string& XmlPrimitive::getValue() const {
    return value;
}
void XmlPrimitive::setValue(const std::string& value) {
    XmlPrimitive::value = value;
}

bool XmlPrimitive::asBoolean() {
    if (value.size() <= 5) { // false - 5 chars
        std::string boolStr = value;
        std::transform(boolStr.begin(), boolStr.end(), boolStr.begin(), ::tolower);
        if (boolStr == "true" || boolStr == "1") {
            return true;
        } else if (boolStr == "false" || boolStr == "0") {
            return false;
        }
    }
    throw BadCastException<bool>();
}
char XmlPrimitive::asChar() {
    if (value.size() == 1) {
        return value[0];
    }
    throw BadCastException<char>();
}
int XmlPrimitive::asInt() {
    return std::stoi(value);
}
long XmlPrimitive::asLong() {
    return std::stol(value);
}
float XmlPrimitive::asFloat() {
    return std::stof(value);
}
double XmlPrimitive::asDouble() {
    return std::stod(value);
}
