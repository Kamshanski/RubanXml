#include "FileSink.h"

void FileSink::_write(const std::string& str) {
    file << str;
}
void FileSink::_write(char ch) {
    file << ch;
}
void FileSink::_close() {
    file.close();
}
FileSink::FileSink(std::string& path) {
    file = std::ofstream(path);
}
