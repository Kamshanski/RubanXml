#include "StringBuilder.h"
#include "StringUtils.h"

bool StringBuilder::isEmpty() const {
    return str.empty();
}

bool StringBuilder::isNotEmpty() const {
    return !isEmpty();
}

int StringBuilder::size() const {
    return str.size();
}

bool StringBuilder::isBlank() const {
    return is_blank(str);
}
bool StringBuilder::isNotBlank() const {
    return !isBlank();
}
void StringBuilder::append(const std::string& s) {
    str += s;
}

std::string StringBuilder::toString() {
    return str;
}

void StringBuilder::clear() {
    str = "";
}

std::string StringBuilder::extract() {
    std::stringstream ss;
    ss << toString();
    clear();
    return ss.str();
}
