#include "sink/StringSink.h"

void StringSink::_write(const std::string& str) {
    ss << str;
}

void StringSink::_write(char ch) {
    ss << ch;
}

std::string StringSink::toString() {
    if (!isClosed()) {
        close();
    }
    return ss.str();
}
void StringSink::_close() {}

