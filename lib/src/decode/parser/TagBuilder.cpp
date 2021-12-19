#include <CheckExtensions.h>
#include "TagBuilder.h"

void TagBuilder::onTagOpen(std::string tagName) {
    XmlTag* newTag = new XmlTag(tagName);
    if (root == nullptr) {
        root = newTag;
    }
    branch.push_back(newTag);
}

void TagBuilder::onTagClosed(std::string tagName) {
    auto current = getCurrent();
    auto parent = getCurrentsParent();

    if (current != root) {
        parent->addValue(current);
    }

    branch.pop_back();
}

void TagBuilder::onAttribute(std::string attrName, std::string attrValue) {
    auto current = getCurrent();
    if (current != nullptr) {
        current->addAttribute(attrName, attrValue);
    }
}

void TagBuilder::onTagTextValue(std::string tagTextValue) {
    auto current = getCurrent();
    checkNotNull(current);

    if (current != nullptr) {
        current->addValue(tagTextValue);
    }
}

XmlTag* TagBuilder::getCurrent() const {
    if (!branch.empty()) {
        return branch[branch.size() - 1];
    }
    return nullptr;
}

XmlTag* TagBuilder::getCurrentsParent() const {
    if (branch.size() > 1) {
        return branch[branch.size() - 2];
    }
    return nullptr;
}

XmlTag* TagBuilder::getRoot() const {
    return root;
}
