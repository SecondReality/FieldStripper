#include "PreviewHighlighter.h"
#include "FieldStripper.h"

PreviewHighlighter::PreviewHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
}

void PreviewHighlighter::highlightBlock(const QString & text)
{
    QTextCharFormat foundText;
    foundText.setFontWeight(QFont::Bold);
    foundText.setForeground(Qt::darkMagenta);

    QTextCharFormat extractedText;
    extractedText.setFontWeight(QFont::Bold);
    extractedText.setForeground(Qt::darkMagenta);

    // Pass the search fields and text to FieldStripper:
    FieldStripper f;

    foreach(SearchField searchField, searchFields_)
    {

    }
}

void PreviewHighlighter::setSearchFields(const SearchFields& searchFields)
{
    searchFields_ = searchFields;
}
