#include "pch.h"
#include <iomanip>
#include <regex>
#include <iostream>
#include <codecvt>
#include "ParseContext.h"
#include "TextBlock.h"
#include "DateTimePreparser.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

TextBlock::TextBlock() :
    BaseCardElement(CardElementType::TextBlock), TextElement(), m_wrap(false), m_maxLines(0), m_hAlignment(HorizontalAlignment::Left)
{
    PopulateKnownPropertiesSet();
}

Json::Value TextBlock::SerializeToJsonValue() const
{
    Json::Value root = BaseCardElement::SerializeToJsonValue();

    if (m_textSize != TextSize::Default)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Size)] = TextSizeToString(m_textSize);
    }

    if (m_textColor != ForegroundColor::Default)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Color)] = ForegroundColorToString(m_textColor);
    }

    if (m_textWeight != TextWeight::Default)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Weight)] = TextWeightToString(m_textWeight);
    }

    if (m_fontStyle != FontStyle::Default)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::FontStyle)] = FontStyleToString(m_fontStyle);
    }

    if (m_hAlignment != HorizontalAlignment::Left)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::HorizontalAlignment)] = HorizontalAlignmentToString(m_hAlignment);
    }

    if (m_maxLines != 0)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::MaxLines)] = m_maxLines;
    }

    if (m_isSubtle)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsSubtle)] = true;
    }

    if (m_wrap)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Wrap)] = true;
    }

    root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Text)] = GetText();

    return root;
}

bool TextBlock::GetWrap() const
{
    return m_wrap;
}

void TextBlock::SetWrap(const bool value)
{
    m_wrap = value;
}

unsigned int TextBlock::GetMaxLines() const
{
    return m_maxLines;
}

void TextBlock::SetMaxLines(const unsigned int value)
{
    m_maxLines = value;
}

HorizontalAlignment TextBlock::GetHorizontalAlignment() const
{
    return m_hAlignment;
}

void TextBlock::SetHorizontalAlignment(const HorizontalAlignment value)
{
    m_hAlignment = value;
}

std::shared_ptr<BaseCardElement> TextBlockParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    ParseUtil::ExpectTypeString(json, CardElementType::TextBlock);

    std::shared_ptr<TextBlock> textBlock = BaseCardElement::Deserialize<TextBlock>(context, json);
    textBlock->SetText(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Text, true));
    textBlock->SetTextSize(ParseUtil::GetEnumValue<TextSize>(json, AdaptiveCardSchemaKey::Size, TextSize::Default, TextSizeFromString));
    textBlock->SetTextColor(
        ParseUtil::GetEnumValue<ForegroundColor>(json, AdaptiveCardSchemaKey::Color, ForegroundColor::Default, ForegroundColorFromString));
    textBlock->SetTextWeight(
        ParseUtil::GetEnumValue<TextWeight>(json, AdaptiveCardSchemaKey::TextWeight, TextWeight::Default, TextWeightFromString));
    textBlock->SetFontStyle(
        ParseUtil::GetEnumValue<FontStyle>(json, AdaptiveCardSchemaKey::FontStyle, FontStyle::Default, FontStyleFromString));
    textBlock->SetWrap(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::Wrap, false));
    textBlock->SetIsSubtle(ParseUtil::GetBool(json, AdaptiveCardSchemaKey::IsSubtle, false));
    textBlock->SetMaxLines(ParseUtil::GetUInt(json, AdaptiveCardSchemaKey::MaxLines, 0));
    textBlock->SetHorizontalAlignment(ParseUtil::GetEnumValue<HorizontalAlignment>(
        json, AdaptiveCardSchemaKey::HorizontalAlignment, HorizontalAlignment::Left, HorizontalAlignmentFromString));

    return textBlock;
}

std::shared_ptr<BaseCardElement> TextBlockParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return TextBlockParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void TextBlock::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Text),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Size),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Color),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::TextWeight),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::FontStyle),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Wrap),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IsSubtle),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::MaxLines),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::HorizontalAlignment)});
}
