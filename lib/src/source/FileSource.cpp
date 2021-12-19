#include "FileSource.h"

FileSource::FileSource(const std::string& path) {
    file = std::ifstream(path);

    if (!file.is_open()) {
        std::cerr << "Could not open the file - '"
                  << path << "'" << std::endl;
        close();
        throw std::ios_base::failure("File can't be opened");
    }
}

// return 0 if EOF
char FileSource::obtainNextCharOrEof() {
    return file.get();
}

void FileSource::_close() {
    file.close();
}
