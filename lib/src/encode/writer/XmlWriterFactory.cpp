#include "encode/writer/XmlWriterFactory.h"

XmlWriterFactory::XmlWriterFactory(EncoderParams* encoderParams) : encoderParams(encoderParams) {
    if (this->encoderParams == nullptr) {
        throw std::invalid_argument("Encoder Params cannot be null");
    }
}

Writer* XmlWriterFactory::get(Sink* sink) {
    if (sink == nullptr) {
        throw std::invalid_argument("Source cannot be null");
    }
    return new Writer(sink, encoderParams);
}
XmlWriterFactory::~XmlWriterFactory() {
    delete encoderParams;

}
