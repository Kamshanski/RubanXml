
#include "StringUtils.h"

std::string repeat(char what, int times) {
    std::ostringstream oss;
    for (int i = 0; i < times; ++i) {
        oss << what;
    }
    return oss.str();
}
std::string repeat(const std::string& what, int times) {
    std::ostringstream oss;
    for (int i = 0; i < times; ++i) {
        oss << what;
    }
    return oss.str();
}
std::string to_escape_sequence(char ch, bool addNumericCode) {
    std::string ee;
    switch (ch) {
        case '\t': ee = "\\t";
        case '\b': ee = "\\b";
        case '\n': ee = "\\n";
        case '\r': ee = "\\r";
        case '\'': ee = "\\'";
        case '\"': ee = "\\\"";
        case '\\': ee = "\\\\";
        default: ee = to_string(ch);
    }

    if (addNumericCode) {
        ee += "(" + std::to_string((int) ch) + ")";
    }

    return ee;
}
std::string to_string(char ch) {
    std::stringstream ss;
    ss << ch;
    return ss.str();
}
std::string to_string(const char* chars) {
    std::stringstream ss;
    ss << chars;
    return ss.str();
}
bool is_whitespace(char ch) {
    return is_whitespace(static_cast<unsigned char>(ch));
}
bool is_whitespace(unsigned char uch) {
    return std::isspace(uch) || std::iscntrl(uch);
}
int is_whitespace(int uch) {
    return std::isspace(uch) || std::iscntrl(uch);
}
bool is_blank(const std::string& str) {
    int size = str.size();
    for (int i = 0; i < size; ++i) {
        char ch = str[i];
        if (!is_whitespace(ch)) {
            return false;
        }
    }
    return true;
}
std::string& ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(is_whitespace))));
    return s;
}
std::string& rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(is_whitespace))).base(), s.end());
    return s;
}
std::string& trim(std::string& s) {
    return ltrim(rtrim(s));
}
