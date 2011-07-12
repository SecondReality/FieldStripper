#include "SearchFields.h"

SearchField::SearchField(QString text, int length): searchText_(text), fieldLength_(length)
{
}

void SearchField::setSearchText(const QString& text)
{
    searchText_ = text;
}

QString SearchField::searchText() const
{
    return searchText_;
}

void SearchField::setFieldLength(int length)
{
    fieldLength_ = length;
}

int SearchField::fieldLength() const
{
    return fieldLength_;
}
