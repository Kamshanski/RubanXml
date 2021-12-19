#include <ExceptionsExtensions.h>
#include "Sink.h"

Sink* Sink::write(const std::string& str) {
    checkNotClosed();
    _write(str);
    return this;
}

Sink* Sink::write(char ch) {
    checkNotClosed();
    _write(ch);
    return this;
}

void Sink::close() {
    checkNotClosed();
    _close();
    _isClosed = true;
}

bool Sink::isClosed() {
    return _isClosed;
}

void Sink::checkNotClosed() {
    if (isClosed()) {
        throw IllegalStateException("This object cannot be used twice. Create a new one");
    }
}
