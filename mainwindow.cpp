#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTextStream>
#include <QDir>
#include <QDataStream>

const int inputPreviewSize=4000;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    loading_(false)
{
    ui->setupUi(this);

    QStringList headers;
    headers << "Search Text" << "Field Width";
    ui->searchFieldsTable->setHorizontalHeaderLabels(headers);
    highlighter_.setDocument(ui->inputPreview->document());

    QSettings settings(getSettingsFilename(), QSettings::IniFormat);
    QString inputFileName=settings.value("inputFileName").toString();
    if(!inputFileName.isEmpty())
    {
        loadInputFile(translateSettingsPath(inputFileName));
    }

    QString filterFileName=settings.value("filterFileName").toString();
    if(!filterFileName.isEmpty())
    {
        loadFilterFile(translateSettingsPath(filterFileName));
    }

    // Populate/update the output preview:
    searchFieldsCellChanged(0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::translateSettingsPath(const QString inputFileName) const
{
    QFile file(inputFileName);
    if(file.exists())
    {
        return inputFileName;
    }
    QDir applicationDir(QCoreApplication::applicationDirPath());
    return applicationDir.filePath(inputFileName);
}

QString MainWindow::getSettingsFilename() const
{
    QDir applicationDir(QCoreApplication::applicationDirPath());
    return applicationDir.filePath("settings.ini");
}

QString MainWindow::toCSV(const FieldStripper::StringTable &st)
{
    QString output;
    for(int row=0; row<st.size(); row++)
    {
       for(int column=0; column<st[row].size(); column++)
       {
           output+="\"";
           QString value=st[row][column].first;
           output+=value.replace("\"", "\"\"");
           output+="\"";
           output+=",";
       }
       output+="\r\n";
    }
    return output;
}

void MainWindow::loadInputFile(const QString& filename)
{
    ui->inputFilePathEdit->setText(filename);

    // Load the contents of the file into the input preview pane:
    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly))
    {
        // The file is invalid:
        ui->convertButton->setEnabled(false);

        //QMessageBox::information(0, "error", file.errorString());
        return;
    }

    // The file is valid:
    QSettings settings(getSettingsFilename(), QSettings::IniFormat);
    settings.setValue("inputFileName", filename);

    // Enable the convert button:
    ui->convertButton->setEnabled(true);
    ui->outputPreview->setEnabled(true);
    ui->inputPreview->setEnabled(true);

    QTextStream in(&file);
    inputFileContents_= in.read(inputPreviewSize);

    // Limit the amount of text shown in the preview area:
    ui->inputPreview->setText(inputFileContents_.left(3000));
}

void MainWindow::loadFilterFile(const QString& filename)
{
       // set filterFilename_
    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly))
    {
        // The file is invalid:
        ui->convertButton->setEnabled(false);

        //QMessageBox::information(0, "error", file.errorString());
        // ???
        return;
    }

    QDataStream out(&file);

    searchFields_.clear();

    int length;
    out >> length;
    for(int i=0; i<length; i++)
    {
        int fieldLength;
        QString searchText;

        out >> fieldLength;
        out >> searchText;
        searchFields_.push_back(SearchField(searchText, fieldLength));
    }

    // Populate the user interface:
    ui->searchFieldsTable->clearContents();
    ui->searchFieldsTable->setRowCount(searchFields_.length());

    loading_=true;
    for(int row=0; row<searchFields_.length(); row++)
    {
        QTableWidgetItem * w = new QTableWidgetItem(searchFields_[row].searchText());
        ui->searchFieldsTable->setItem(row, 0, w);

        QTableWidgetItem * fieldLength = new QTableWidgetItem(QString::number(searchFields_[row].fieldLength()));
        ui->searchFieldsTable->setItem(row, 1, fieldLength);
    }
    loading_=false;

    filterFilename_=filename;
    QSettings settings(getSettingsFilename(), QSettings::IniFormat);
    settings.setValue("filterFileName", filename);
}

void MainWindow::browseForInputFile()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Input File"));
    loadInputFile(filename);
    // Populate/update the output preview:
    searchFieldsCellChanged(0, 0);
}

void MainWindow::searchFieldsAddRow()
{
    ui->searchFieldsTable->setRowCount(ui->searchFieldsTable->rowCount()+1);
}

void MainWindow::searchFieldsDeleteRow()
{
    ui->searchFieldsTable->removeRow(ui->searchFieldsTable->currentRow());
}

void MainWindow::searchFieldsLoad()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Input File"), QString(), "Filter File (*.frf)");
    loadFilterFile(filename);
}

void MainWindow::searchFieldsSave()
{
    if(filterFilename_.isEmpty())
    {
        // Display the SaveAs dialog:
        QString fileName=QFileDialog::getSaveFileName(this, tr("Save File"), QString(), tr("Filter File (*.frf)"));
        if(fileName.isEmpty())
        {
            return;
        }
        filterFilename_=fileName;
    }

    QFile file(filterFilename_);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    out << searchFields_.length();
    foreach(const SearchField& sf, searchFields_)
    {
        out << sf.fieldLength();
        out << sf.searchText();
    }

    QSettings settings(getSettingsFilename(), QSettings::IniFormat);
    settings.setValue("filterFileName", filterFilename_);
}

void MainWindow::searchFieldsSelectionChanged()
{
    bool rowSelected = ui->searchFieldsTable->currentRow() != -1;
    ui->deleteRowButton->setEnabled(rowSelected);
}

void MainWindow::searchFieldsCellChanged(int row, int column)
{
    if(loading_)
    {
        return;
    }

    //Create the SearchFields:
    searchFields_.clear();
    for(int i=0; i<ui->searchFieldsTable->rowCount(); i++)
    {
        if(!ui->searchFieldsTable->item(i, 0))
        {
            continue;
        }
        QString searchText = ui->searchFieldsTable->item(i, 0)->text();
        if(searchText.isEmpty())
        {
            continue;
        }
        if(!ui->searchFieldsTable->item(i, 1))
        {
            continue;
        }
        QString fieldLengthString = ui->searchFieldsTable->item(i, 1)->text();
        bool ok=false;
        int fieldLength=fieldLengthString.toInt(&ok);
        if(!ok)
        {
            continue;
        }
        SearchField f(searchText, fieldLength);
        searchFields_.push_back(f);
    }

    // Pass these fields to the syntax highlighter;
    highlighter_.setSearchFields(searchFields_);
    highlighter_.rehighlight();

    //Create the column names of the preview table:

    QStringList previewHeader;
    foreach(auto field, searchFields_)
    {
        previewHeader << field.searchText();
    }
    ui->outputPreview->clearContents();
    ui->outputPreview->setColumnCount(searchFields_.length());
    ui->outputPreview->setHorizontalHeaderLabels(previewHeader);

    // Populate the preview table:
    FieldStripper f;
    FieldStripper::StringTable st;
    f.strip(searchFields_, ui->inputPreview->toPlainText(), st);
    ui->outputPreview->setRowCount(st.length());

    for(int row=0; row<st.length(); row++)
    {
        for(int column=0; column<st[row].length(); column++)
        {
            QTableWidgetItem * w = new QTableWidgetItem(st[row][column].first);
            w->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            ui->outputPreview->setItem(row, column, w);
        }
    }
}

void MainWindow::go()
{
    // Strip the fields from the full file:
    FieldStripper f;
    FieldStripper::StringTable st;
    f.strip(searchFields_, inputFileContents_, st);

    QString csv=toCSV(st);
    // Now create the resulting tab spaced file:

    QString fileName=QFileDialog::getSaveFileName(this, tr("Save File"), QString(), tr("Comma Separated Values (*.csv)"));
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << csv;
}
