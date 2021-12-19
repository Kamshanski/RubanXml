cmake_minimum_required (VERSION 3.8)

project(RubanXmlLib)

set(CPP_FILES
        include/xml_ruban/MutableDecoderParams.h
        include/xml_ruban/MutableEncoderParams.cpp
        include/xml_ruban/MutableEncoderParams.h
        include/xml_ruban/RubanXml.h
        include/xml_ruban/RubanXmlBuilder.h
        src/decode/DecoderParams.cpp
        src/decode/DecoderParams.h
        src/decode/MutableDecoderParams.cpp
        src/decode/parser/XmlParser.cpp
        src/decode/parser/XmlParser.h
        src/decode/parser/LoggedParser.cpp
        src/decode/parser/Parser.h
        src/decode/parser/LoggedParser.h
        src/decode/parser/ParserState.cpp
        src/decode/parser/ParserState.h
        src/decode/parser/TagBuilder.cpp
        src/decode/parser/TagBuilder.h
        src/decode/parser/Visitor.h
        src/decode/parser/LoggedVisitor.h
        src/decode/parser/LoggedVisitor.cpp
        src/decode/parser/XmlParserFactory.cpp
        src/decode/parser/XmlParserFactory.h
        src/encode/EncoderParams.cpp
        src/encode/EncoderParams.h
        src/encode/writer/Writer.cpp
        src/encode/writer/Writer.h
        src/encode/writer/XmlWriterFactory.cpp
        src/encode/writer/XmlWriterFactory.h
        src/entities/XmlAttributes.cpp
        src/entities/XmlAttributes.h
        src/entities/XmlElement.cpp
        src/entities/XmlElement.h
        src/entities/XmlPrimitive.cpp
        src/entities/XmlPrimitive.h
        src/entities/XmlTag.cpp
        src/entities/XmlTag.h
        src/entities/XmlValues.cpp
        src/entities/XmlValues.h
        src/exceptions/BaseXmlException.h
        src/exceptions/CharacterMisexpectationExceptions.h
        src/exceptions/IllegalCharacterExceptions.h
        src/exceptions/ParserInternalExceptions.h
        src/RubanXml.cpp
        src/RubanXmlBuilder.cpp
        src/rules/CharExcapeRules.h
        src/rules/Syntax.h
        src/sink/FileSink.cpp
        src/sink/FileSink.h
        src/sink/Sink.cpp
        src/sink/Sink.h
        src/sink/LoggedSink.cpp
        src/sink/LoggedSink.h
        src/sink/StringSink.cpp
        src/sink/StringSink.h
        src/source/FileSource.cpp
        src/source/FileSource.h
        src/source/Source.cpp
        src/source/Source.h
        src/source/LoggedSource.cpp
        src/source/LoggedSource.h
        src/source/StringSource.cpp
        src/source/StringSource.h
        src/_utils/CheckExtensions.h
        src/_utils/ClassExctensions.h
        src/_utils/ExceptionsExtensions.h
        src/_utils/LinkedMap.h
        src/_utils/StringBuilder.cpp
        src/_utils/StringBuilder.h
        src/_utils/StringUtils.cpp
        src/_utils/StringUtils.h
        )

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(RubanXmlLib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/xml_ruban)
include_directories(RubanXmlLib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(RubanXmlLib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/_utils)

add_library(RubanXmlLib STATIC ${CPP_FILES})

target_link_libraries(RubanXmlLib ${CONAN_LIBS})







##target_include_directories(RubanXml ${CMAKE_CURRENT_SOURCE_DIR})

##include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/_utils ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include/xml_ruban)
#
#project(RubanXmlLib)
##https://stackoverflow.com/questions/3201154/automatically-add-all-files-in-a-folder-to-a-target-using-cmake
#set(CPP_FILES
#        include/xml_ruban/MutableDecoderParams.h
#        include/xml_ruban/MutableEncoderParams.cpp
#        include/xml_ruban/MutableEncoderParams.h
#        include/xml_ruban/RubanXml.h
#        include/xml_ruban/RubanXmlBuilder.h
#        src/decode/DecoderParams.cpp
#        src/decode/DecoderParams.h
#        src/decode/MutableDecoderParams.cpp
#        src/decode/parser/XmlParser.cpp
#        src/decode/parser/XmlParser.h
#        src/decode/parser/ParserState.cpp
#        src/decode/parser/ParserState.h
#        src/decode/parser/TagBuilder.cpp
#        src/decode/parser/TagBuilder.h
#        src/decode/parser/Visitor.h
#        src/decode/parser/XmlParserFactory.cpp
#        src/decode/parser/XmlParserFactory.h
#        src/encode/EncoderParams.cpp
#        src/encode/EncoderParams.h
#        src/encode/writer/Writer.cpp
#        src/encode/writer/Writer.h
#        src/encode/writer/XmlWriterFactory.cpp
#        src/encode/writer/XmlWriterFactory.h
#        src/entities/XmlAttributes.cpp
#        src/entities/XmlAttributes.h
#        src/entities/XmlElement.cpp
#        src/entities/XmlElement.h
#        src/entities/XmlPrimitive.cpp
#        src/entities/XmlPrimitive.h
#        src/entities/XmlTag.cpp
#        src/entities/XmlTag.h
#        src/entities/XmlValues.cpp
#        src/entities/XmlValues.h
#        src/exceptions/BaseXmlException.h
#        src/exceptions/CharacterMisexpectationExceptions.h
#        src/exceptions/IllegalCharacterExceptions.h
#        src/exceptions/ParserInternalExceptions.h
#        src/RubanXml.cpp
#        src/RubanXmlBuilder.cpp
#        src/rules/CharExcapeRules.h
#        src/rules/Syntax.h
#        src/sink/FileSink.cpp
#        src/sink/FileSink.h
#        src/sink/Sink.cpp
#        src/sink/Sink.h
#        src/sink/StringSink.cpp
#        src/sink/StringSink.h
#        src/source/FileSource.cpp
#        src/source/FileSource.h
#        src/source/Source.cpp
#        src/source/Source.h
#        src/source/StringSource.cpp
#        src/source/StringSource.h
#        src/_utils/CheckExtensions.h
#        src/_utils/ClassExctensions.h
#        src/_utils/ExceptionsExtensions.h
#        src/_utils/LinkedMap.h
#        src/_utils/StringBuilder.cpp
#        src/_utils/StringBuilder.h
#        src/_utils/StringUtils.cpp
#        src/_utils/StringUtils.h
#        )
##file(GLOB_RECURSE CPP_FILES CONFIGURE_DEPENDS "*.cpp" "*.h")
##message(${CPP_FILES})
###https://stackoverflow.com/questions/15550777/how-do-i-exclude-a-single-file-from-a-cmake-fileglob-pattern/15551302
##list(FILTER CPP_FILES EXCLUDE REGEX ".*cmake-build.*")
#add_library(RubanXmlLib STATIC ${CPP_FILES})
#message(${CPP_FILES})
#target_include_directories(RubanXmlLib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/xml_ruban)
#target_include_directories(RubanXmlLib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
##target_include_directories(RubanXml PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
##add_library(xml_ruban library.cpp)
#
##add_executable(RubanXml main.cpp library.cpp)



