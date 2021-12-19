#ifndef XML_RUBAN_CHAREXCAPERULES_H
#define XML_RUBAN_CHAREXCAPERULES_H

// TODO: ДОБАВИТЬ СПЕЦИАЛЬНУЮ ОБРАБОТКУ UTF-8 (можно не надо - русские буквы не нужны)

const char ILLEGAL_TAG_NAME_CHARS[] = "</>='\"\\&;";
const char ILLEGAL_ATTR_NAME_CHARS[] = "</>='\"\\&;";
const char ILLEGAL_ATTR_VALUE_CHARS[] = "/='\\&";
const char ILLEGAL_TEXT_VALUE_CHARS[] = "<>&";

#endif //XML_RUBAN_CHAREXCAPERULES_H
