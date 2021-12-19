#include <ExceptionsExtensions.h>
#include "Source.h"

bool Source::isClosed() const {
    return _isClosed;
}

bool Source::hasObtainedChar() const {
    return _isRead;
}

char Source::nextChar() {
    if (isClosed()) {
        throw std::ios_base::failure("Cannot read file as it is closed");
    }
    if (!hasObtainedChar()) {
        throw std::runtime_error("hasNext() must be invoked first");
    }
    _isRead = false;

    return obtainedChar;
}

bool Source::hasNext() {
    if (isClosed()) {
        return false;
    }

    char ch = obtainNextCharOrEof();

    if (ch) {
        obtainedChar = ch;
        _isRead = true;
        return true;
    } else {
        close();
        return false;
    }
}

bool Source::close() {
    if (!_isClosed) {
        _close();
        _isClosed = true;
        return true;
    }
    return false;
}
