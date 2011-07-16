#ifndef FIELDSTRIPPER_H
#define FIELDSTRIPPER_H

#include <QString>
#include <QList>
#include <QObject>
#include <QPair>

#include "SearchFields.h"

// Produces a grid of records.
// Also emits a signal for each field found.
class FieldStripper : public QObject
{
    Q_OBJECT

public:
    FieldStripper();

    typedef QPair<QString, int> FoundText; // Contains the found text, and the location it was found in the original document.
    typedef QList<QList<FoundText> > StringTable;

    void strip(const SearchFields& sf, const QString &searchText, StringTable& table);

signals:
    void foundField(SearchField, int location);
};

#endif // FIELDSTRIPPER_H
