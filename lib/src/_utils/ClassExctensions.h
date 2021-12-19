#ifndef XML_RUBAN_CLASSEXCTENSIONS_H
#define XML_RUBAN_CLASSEXCTENSIONS_H

#include <string>

class Object {
    virtual std::string getClassName() {
        return {"Object"};
    }
};

// https://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor
// source: http://cpp.sh/8owv
// Перед применением важно, чтобы к этому моменту T зависело от Base (или наоборот).
// Т.е. все заголовочные файлы с наследованием должны быть объявлены
template<typename Base, typename T>
bool instanceof(const T* ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}


// Shortcut to just prevent the compiler from spitting out
// warnings about unused parameters or variables.
template<typename T>
inline void unused(T) {}

template<typename Base, typename T>
bool refInstanceof(const T& ptr) {
    try {
        unused(dynamic_cast<const Base&>(ptr));
        return true;
    }
    catch (std::bad_cast& e) {
        return false;
    }
}

#endif XML_RUBAN_CLASSEXCTENSIONS_H
