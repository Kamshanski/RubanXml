#include <sstream>
#include <plog/Log.h>
#include "LoggedSource.h"

LoggedSource::LoggedSource(Source& source, plog::Severity logLevel) : source(source), logLevel(logLevel) {}
char LoggedSource::nextChar() {
    PLOG(logLevel) << "Request next char from source";
    char ch = source.nextChar();
    std::ostringstream os;
    os << "Next char from source: " << ch;
    PLOG(logLevel) << os.str();
    return ch;
}
bool LoggedSource::hasNext() {
    PLOG(logLevel) << "Check is has next char in source";
    bool hasNext = source.hasNext();
    std::ostringstream os;
    os << "Source has next char: " << hasNext;
    PLOG(logLevel) << os.str();
    return hasNext;
}
bool LoggedSource::close() {
    PLOG(logLevel) << "Source close";
    return source.close();
}
bool LoggedSource::isClosed() const {
    PLOG(logLevel) << "Request source isClosed";
    return source.isClosed();
}
bool LoggedSource::hasObtainedChar() const {
    PLOG(logLevel) << "Request source hasObtainedChar";
    return source.hasObtainedChar();
}

char LoggedSource::obtainNextCharOrEof() {
    return 0;
}
void LoggedSource::_close() {

}
