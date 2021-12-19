#include "../../rules/Syntax.h"
#include "Writer.h"

bool Writer::isUsed() const {
    return _isUsed;
}

void Writer::requireNotUsed() const {
    if (isUsed()) {
        throw IllegalStateException("This object cannot be used twice. Create a new one");
    }
}

Writer::Writer(Sink* sink, EncoderParams* params) : sink(sink), params(params) {
    if (this->sink == nullptr) {
        throw std::invalid_argument("Sink cannot be null");
    }
    if (this->params == nullptr) {
        throw std::invalid_argument("Encoder Params cannot be null");
    }
}

Sink* Writer::write(XmlElement* element) {
    requireNotUsed();
    _isUsed = true;

    writeElement(element);

    return sink;
}

void Writer::writeElement(XmlElement* element) {
    if (element->isXmlTag()) {
        writeTag(element->asXmlTag());
    } else if (element->isXmlPrimitive()) {
        writePrimitive(element->asXmlPrimitive());
    } else {
        throw std::invalid_argument("this type of element is not supported");
    }
}

void Writer::writeTag(XmlTag* tag) {
    if (tag->isNotEmpty() || !params->isShortenEmptyTags()) {
        writeFilledTag(tag);
    } else {
        writeEmptyTag(tag);
    }
}

void Writer::writeFilledTag(XmlTag* tag) {
    sink->write(TAG_OPEN_BRACE)
        ->write(tag->getName());
    writeAttributes(tag->getAttributes());
    sink->write(TAG_CLOSE_BRACE);

    indentation++;
    writeValue(tag->getValues());
    indentation--;

    if (params->isBeautify()) {
        if (tag->isNotEmpty() && !tag->getValues()->isLastPrimitive()) {
            sink->write(LINE_SEPARATOR);
            appendIndentation();
        }
    }

    sink->write(TAG_OPEN_BRACE)
        ->write(TAG_END_MARKER)
        ->write(tag->getName())
        ->write(TAG_CLOSE_BRACE);
}

void Writer::writeEmptyTag(XmlTag* tag) {
    sink->write(TAG_OPEN_BRACE)
        ->write(tag->getName());
    writeAttributes(tag->getAttributes());
    sink->write(TAG_END_MARKER)
        ->write(TAG_CLOSE_BRACE);

}

void Writer::writeAttributes(XmlAttributes* attributes) {
    int limit = attributes->size();
    for (int i = 0; i < limit; ++i) {
        auto entity = attributes->indexed(i);

        sink->write(ATTR_SEPARATOR)
                ->write(entity.first); // key

        if (params->isSpacesAroundAttributeEqualSign()) {
            sink->write(ATTR_SEPARATOR);
        }
        sink->write(ATTR_EQ);
        if (params->isSpacesAroundAttributeEqualSign()) {
            sink->write(ATTR_SEPARATOR);
        }
        
        sink->write(ATTR_QUOTE)
            ->write(entity.second)  // value
            ->write(ATTR_QUOTE);

    }
}

void Writer::writeValue(XmlValues* values) {
    if (values->isNotEmpty()) {
        bool beautify = params->isBeautify();
        
        if (values->isFirstTag() && beautify) {
            sink->write(LINE_SEPARATOR);
            appendIndentation();
        }
        
        int limit = values->size();
        for (int i = 0; i < limit; ++i) {
            auto element = values->get(i);
            writeElement(element);
            if (beautify && i < limit - 1) {
                sink->write(LINE_SEPARATOR);
                appendIndentation();
            }
        }
    }
}

void Writer::writePrimitive(XmlPrimitive* primitive) {
    sink->write(primitive->getValue());
}

void Writer::appendIndentation() {
    for (int i = 0; i < indentation; ++i) {
        sink->write(INDENTATION);
    }
}
