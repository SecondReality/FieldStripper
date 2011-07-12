#include "FieldStripper.h"
#include <QStringList>

FieldStripper::FieldStripper()
{
}

void FieldStripper::strip(const SearchFields& sf, const QString &searchText, StringTable& table)
{
    int from(0);
    bool searching(true);
    while(searching && from<searchText.size())
    {
        QStringList row;
        for(int i=0; i<sf.size(); i++)
        {
            row.push_back("");
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


            QString foundData = searchText.mid(newIndex+searchFields[i].length(), searchFieldLengths[i]).trimmed();
            from = newIndex+searchFields[i].length()+searchFieldLengths[i];
            std::cout << foundData.toStdString() << std::endl;
            //words.append(foundData);
            row[i]=foundData;
        }
        table.push_back(row);
    }


    std::cout << "Generating output file...";

    // Now create the resulting tab spaced file:
    QFile output("out.txt");
    output.open(QIODevice::WriteOnly);

    for(int i=0; i<results.size(); i++)
    {
        for(int n=0; n<searchFieldLengths.size(); n++)
        {
            output.write(results[i][n].toAscii());
            output.write("\t");
        }
        output.write("\r\n");
    }

    std::cout << "done!" << std::endl;

    return 0;
}
