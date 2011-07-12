#ifndef PREVIEWHIGHLIGHTER_H
#define PREVIEWHIGHLIGHTER_H

#include "SearchFields.h"

#include <QSyntaxHighlighter>

class PreviewHighlighter : public QSyntaxHighlighter
{
public:
    PreviewHighlighter(QTextDocument *parent = 0);

    void setSearchFields(const SearchFields&);

private:
    void highlightBlock(const QString & text);
    SearchFields searchFields_;
};

#endif // PREVIEWHIGHLIGHTER_H
