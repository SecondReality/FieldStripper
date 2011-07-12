#include <QtGui/QApplication>
#include "mainwindow.h"
//#include <QtCore/QCoreApplication>

#include <iostream>
#include <QFile>
#include <QStringList>
#include <QVector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

/*
    std::cout << "----------------------------------" << std::endl;
    std::cout << "    Field stripper version 0.2" << std::endl;
    std::cout << "           by Steven Mark Rose" << std::endl;
		std::cout << "         smr@secondreality.co.uk" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    if(argc<3)
    {
        std::cout << "Two parameters are required" << std::endl
        << "parameter 1: A text file containing which fields to strip" << std::endl
        << "\tAn example of the format that the text file should be in:" << std::endl
        << "\t\tNAME:,20" << std::endl
        << "\t\tAGE:,10" << std::endl
        << "\tThe numbers denote how many characters long the field following the search text is." << std::endl
        << "\tThe result of running this on a report would create a table with two columns, name and age." << std::endl
        << "parameter 2: A file to strip the information from.";
        return -1;
    }

    std::cout << "Fields to strip: " << argv[1] << std::endl;
    std::cout << "File to mine: " << argv[2]  << std::endl;

    std::cout << "Loading files...";

    QFile fieldFile(argv[1]);
    if(!fieldFile.open(QIODevice::ReadOnly))
    {
        std::cout << "Error: Could not open field file" << std::endl;
        return -1;
    }

    QStringList searchFields;
    QVector<int> searchFieldLengths;
    QByteArray line;
    while(true)
    {
        line = fieldFile.readLine();
        if(line.length()==0)
        {
            break;
        }
        //searchFields << line;
        QString line2=line;
        QStringList splitted = line2.split(",");
        if(splitted.length()<2)
        {
            std::cout << "Badly formed search field line {" << line2.toStdString() << "} ignoring...";
        }
        else
        {
            searchFields << splitted[0];
            searchFieldLengths << splitted[1].toUInt();
        }
    }

    // Load the report file:
    QFile inputFile(argv[2]);
    if(!inputFile.open(QIODevice::ReadOnly))
    {
        std::cout << "Error: Could not open report file" << std::endl;
        return -1;
    }

    QByteArray data = inputFile.readAll();
    std::cout << "done" << std::endl;

    std::cout << std::endl << "Search fields" << std::endl;
    for(int i=0; i<searchFieldLengths.size(); i++)
    //foreach(QString s, searchFields)
    {
        std::cout << searchFields[i].toStdString() << "\t:\t" << searchFieldLengths[i] << std::endl;
    }

    std::cout << "Searching report data, building database..." << std::endl;

    QString tester = data;

    QVector< QStringList > results;
    //std::cout << tester.toStdString();
    // For each of the fields:

    int from(0);
    bool searching(true);
    while(searching && from<tester.size())
    {
        QStringList row;
        for(int i=0; i<searchFieldLengths.size(); i++)
        {
            row.push_back("");
        }

        for(int i=0; i<searchFieldLengths.size(); i++)
        {
            int newIndex = tester.indexOf(searchFields[i], from);
            if(newIndex==-1)
            {
                if(i==searchFieldLengths.size()-1)
                {
                    searching=false;
                    break;
                }
                else
                {
                    continue;
                }
            }

            // We found this string:
            std::cout << "Found data:";

            QString foundData = tester.mid(newIndex+searchFields[i].length(), searchFieldLengths[i]).trimmed();
            from = newIndex+searchFields[i].length()+searchFieldLengths[i];
            std::cout << foundData.toStdString() << std::endl;
            //words.append(foundData);
            row[i]=foundData;
        }
        results.push_back(row);
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
*/
