#include "FieldStripper.h"
#include <QStringList>

FieldStripper::FieldStripper()
{
}

void FieldStripper::strip(const SearchFields& sf, const QString &searchText, StringTable& table)
{
    if(sf.length()==0)
    {
        return;
    }

    int from(0);
    bool searching(true);
    while(searching && from<searchText.size())
    {
        QList<FoundText> row;
        for(int i=0; i<sf.size(); i++)
        {
            row.push_back(FoundText("", -1));
        }

        for(int i=0; i<sf.size(); i++)
        {
            int newIndex = searchText.indexOf(sf[i].searchText(), from);
            if(newIndex==-1)
            {
                if(i==sf.size()-1)
                {
                    searching=false;
                    break;
                }
                else
                {
                    continue;
                }
            }

            QString foundData = searchText.mid(newIndex+sf[i].searchText().length(), sf[i].fieldLength()).trimmed();
            from = newIndex+sf[i].searchText().length()+sf[i].fieldLength();

            FoundText ft = FoundText(foundData, newIndex);
            row[i]=ft;
        }
        table.push_back(row);
    }
}
