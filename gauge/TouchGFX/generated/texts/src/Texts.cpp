/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#include <stdarg.h>
#include <touchgfx/TextProvider.hpp>
#include <touchgfx/Texts.hpp>
#include <touchgfx/TypedText.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/lcd/LCD.hpp>
#include <texts/TypedTextDatabase.hpp>

uint16_t touchgfx::Font::getStringWidth(const touchgfx::Unicode::UnicodeChar* text, ...) const
{
    va_list pArg;
    va_start(pArg, text);
    uint16_t width = getStringWidthLTR(TEXT_DIRECTION_LTR, text, pArg);
    va_end(pArg);
    return width;
}

uint16_t touchgfx::Font::getStringWidth(touchgfx::TextDirection textDirection, const touchgfx::Unicode::UnicodeChar* text, ...) const
{
    va_list pArg;
    va_start(pArg, text);
    uint16_t width = getStringWidthLTR(textDirection, text, pArg);
    va_end(pArg);
    return width;
}

touchgfx::Unicode::UnicodeChar touchgfx::TextProvider::getNextLigature(TextDirection direction)
{
    if (fontGsubTable && nextCharacters.peekChar())
    {
        substituteGlyphs();
        if (nextCharacters.peekChar(1) == 0x093F) // Hindi I-matra
        {
            nextCharacters.replaceAt1(nextCharacters.peekChar());
            nextCharacters.replaceAt0(0x093F);
        }
    }
    return getNextChar();
}

void touchgfx::TextProvider::initializeInternal()
{
    fillInputBuffer();
}

void touchgfx::LCD::drawString(touchgfx::Rect widgetArea, const touchgfx::Rect& invalidatedArea, const touchgfx::LCD::StringVisuals& stringVisuals, const touchgfx::Unicode::UnicodeChar* format, ...)
{
    va_list pArg;
    va_start(pArg, format);
    drawStringLTR(widgetArea, invalidatedArea, stringVisuals, format, pArg);
    va_end(pArg);
}

// Default TypedTextDatabase
extern const touchgfx::TypedText::TypedTextData* const typedTextDatabaseArray[];

TEXT_LOCATION_FLASH_PRAGMA
KEEP extern const touchgfx::Unicode::UnicodeChar texts_all_languages[] TEXT_LOCATION_FLASH_ATTRIBUTE = {
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x57, 0x61, 0x72, 0x6e, 0x69, 0x6e, 0x67, 0x21, 0x20, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x54, 0x6f, 0x6f, 0x20, 0x62, 0x69, 0x67, 0x20, 0x64, 0x69, 0x66, 0x66, 0x65, 0x72, 0x65, 0x6e, 0x63, 0x65, 0x20, 0x69, 0x6e, 0x20, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x6d, 0x65, 0x61, 0x73, 0x75, 0x72, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x73, 0x2e, 0xa, 0x43, 0x68, 0x65, 0x63, 0x6b, 0x20, 0x74, 0x68, 0x65, 0x20, 0x67, 0x61, 0x75, 0x67, 0x65, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x72, 0x65, 0x73, 0x65, 0x74, 0x20, 0x74, 0x68, 0x65, 0x20, 0x64, 0x65, 0x76, 0x69, 0x63, 0x65, 0x2e, 0x0, // @0 "                  Warning! \n         Too big difference in \n              measurements.\nCheck the gauge and reset the device."
    0x50, 0x72, 0x65, 0x73, 0x73, 0x75, 0x72, 0x65, 0x5b, 0x6d, 0x62, 0x61, 0x72, 0x5d, 0x3a, 0x0, // @126 "Pressure[mbar]:"
    0x57, 0x61, 0x69, 0x74, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x73, 0x74, 0x61, 0x74, 0x75, 0x73, 0x0, // @142 "Wait for status"
    0x53, 0x45, 0x43, 0x55, 0x52, 0x49, 0x54, 0x59, 0x20, 0x3a, 0x20, 0x4f, 0x46, 0x46, 0x0, // @158 "SECURITY : OFF"
    0x57, 0x61, 0x69, 0x74, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x70, 0x6f, 0x77, 0x65, 0x72, 0x0, // @173 "Wait for power"
    0x53, 0x45, 0x43, 0x55, 0x52, 0x49, 0x54, 0x59, 0x20, 0x3a, 0x20, 0x4f, 0x4e, 0x0, // @188 "SECURITY : ON"
    0x49, 0x4e, 0x30, 0x20, 0x2, 0x56, 0x0, // @202 "IN0 <>V"
    0x49, 0x4e, 0x37, 0x20, 0x2, 0x56, 0x0, // @209 "IN7 <>V"
    0x49, 0x4e, 0x38, 0x20, 0x2, 0x56, 0x0, // @216 "IN8 <>V"
    0x50, 0x4f, 0x57, 0x45, 0x52, 0x20, 0x53, 0x55, 0x50, 0x50, 0x4c, 0x59, 0x0, // @223 "POWER SUPPLY"
    0x43, 0x48, 0x41, 0x4e, 0x47, 0x45, 0xa, 0x56, 0x49, 0x45, 0x57, 0x0, // @236 "CHANGE\nVIEW"
    0x2f, 0x20, 0x2, 0x56, 0x0, // @248 "/ <>V"
    0x4e, 0x4f, 0x20, 0x50, 0x4f, 0x57, 0x45, 0x52, 0x0, // @253 "NO POWER"
    0x2, 0x0, // @262 "<>"
    0x53, 0x54, 0x41, 0x54, 0x55, 0x53, 0x0, // @264 "STATUS"
    0x30, 0x0 // @271 "0"
};

TEXT_LOCATION_FLASH_PRAGMA
KEEP extern const uint32_t indicesGb[] TEXT_LOCATION_FLASH_ATTRIBUTE;

// Array holding dynamically installed languages
struct TranslationHeader
{
    uint32_t offset_to_texts;
    uint32_t offset_to_indices;
    uint32_t offset_to_typedtext;
};
static const TranslationHeader* languagesArray[1] = { 0 };

// Compiled and linked in languages
static const uint32_t* const staticLanguageIndices[] = {
    indicesGb
};

touchgfx::LanguageId touchgfx::Texts::currentLanguage = static_cast<touchgfx::LanguageId>(0);
static const touchgfx::Unicode::UnicodeChar* currentLanguagePtr = 0;
static const uint32_t* currentLanguageIndices = 0;

void touchgfx::Texts::setLanguage(touchgfx::LanguageId id)
{
    const touchgfx::TypedText::TypedTextData* currentLanguageTypedText = 0;
    if (id < 1)
    {
        if (languagesArray[id] != 0)
        {
            // Dynamic translation is added
            const TranslationHeader* translation = languagesArray[id];
            currentLanguagePtr = (const touchgfx::Unicode::UnicodeChar*)(((const uint8_t*)translation) + translation->offset_to_texts);
            currentLanguageIndices = (const uint32_t*)(((const uint8_t*)translation) + translation->offset_to_indices);
            currentLanguageTypedText = (const touchgfx::TypedText::TypedTextData*)(((const uint8_t*)translation) + translation->offset_to_typedtext);
        }
        else
        {
            // Compiled and linked in languages
            currentLanguagePtr = texts_all_languages;
            currentLanguageIndices = staticLanguageIndices[id];
            currentLanguageTypedText = typedTextDatabaseArray[id];
        }
    }

    if (currentLanguageTypedText)
    {
        currentLanguage = id;
        touchgfx::TypedText::registerTypedTextDatabase(currentLanguageTypedText,
                                                       TypedTextDatabase::getFonts(), TypedTextDatabase::getInstanceSize());
    }
}

void touchgfx::Texts::setTranslation(touchgfx::LanguageId id, const void* translation)
{
    languagesArray[id] = (const TranslationHeader*)translation;
}

const touchgfx::Unicode::UnicodeChar* touchgfx::Texts::getText(TypedTextId id) const
{
    return &currentLanguagePtr[currentLanguageIndices[id]];
}
