#ifndef XML_RUBAN_STRINGUTILS_H
#define XML_RUBAN_STRINGUTILS_H

#include <sstream>
#include "string"
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

std::string to_string(char ch);

std::string to_string(const char* chars);

std::string repeat(const std::string& what, int times);

std::string repeat(char what, int times);

std::string to_escape_sequence(char ch, bool addNumericCode = false);

bool is_whitespace(unsigned char uch);
bool is_whitespace(char ch);
// for lambdas
int is_whitespace(int ch);

bool is_blank(const std::string& str);

// https://stackoverflow.com/a/217605/11103179s
// getTrim from start
std::string& ltrim(std::string& s);

// getTrim from end
std::string& rtrim(std::string& s);

// getTrim from both ends
std::string& trim(std::string& s);
#endif //XML_RUBAN_STRINGUTILS_H
