#ifndef SEARCHFIELDS_H
#define SEARCHFIELDS_H

#include <QString>
#include <QList>

struct SearchField
{
    SearchField(QString, int);

    void setSearchText(const QString&);
    QString searchText() const;
    void setFieldLength(int);
    int fieldLength() const;
private:
    QString searchText_;
    int fieldLength_;
};

/*
class SearchFields
{
public:
    SearchFields();
    QList <SearchField> fields;
};*/

typedef QList<SearchField> SearchFields;

#endif // SEARCHFIELDS_H
