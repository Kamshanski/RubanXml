#include "StringSource.h"
#include <stdexcept>
#include <iostream>

StringSource::StringSource(std::string source) : source(std::move(source)) {
    this->limit = this->source.size();
}

// return 0 if EOF
char StringSource::obtainNextCharOrEof() {
    if (index >= limit) return 0;

    return source[index++];
}

void StringSource::_close() { }

