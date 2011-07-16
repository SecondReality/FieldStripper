#include "PreviewHighlighter.h"
#include "FieldStripper.h"

PreviewHighlighter::PreviewHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
}

void PreviewHighlighter::highlightBlock(const QString & text)
{
    QTextCharFormat foundText;
    foundText.setFontWeight(QFont::Bold);
    foundText.setForeground(Qt::red);

    QColor green;
    green.setNamedColor("#00CC66");
    QTextCharFormat extractedText;
    extractedText.setFontWeight(QFont::Bold);
    extractedText.setForeground(Qt::white);
    extractedText.setBackground(green);

    // Pass the search fields and text to FieldStripper:
    FieldStripper f;
    FieldStripper::StringTable st;

    f.strip(searchFields_, text, st);

    foreach(auto row, st)
    {
        for(int i=0; i<row.length(); i++)
        {
            FieldStripper::FoundText ft=row[i];
            if(!ft.first.isEmpty())
            {
                setFormat(ft.second, searchFields_[i].searchText().length(), foundText);
                setFormat(ft.second+searchFields_[i].searchText().length(), ft.first.length(), extractedText);
            }
        }
    }
}

void PreviewHighlighter::setSearchFields(const SearchFields& searchFields)
{
    searchFields_ = searchFields;
}
