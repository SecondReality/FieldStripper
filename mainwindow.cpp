#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTextStream>

const int inputPreviewSize=4000;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList headers;
    headers << "Search Text" << "Field Width";
    ui->searchFieldsTable->setHorizontalHeaderLabels(headers);

    highlighter_.setDocument(ui->inputPreview->document());
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::browseForInputFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Input File"));
    ui->inputFilePathEdit->setText(fileName);

    // Load the contents of the file into the input preview pane:
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly))
    {
        // The file is invalid:
        ui->convertButton->setEnabled(false);

        //QMessageBox::information(0, "error", file.errorString());
        return;
    }

    // The file is valid:
    // Enable the convert button:
    ui->convertButton->setEnabled(true);
    ui->outputPreview->setEnabled(true);
    ui->inputPreview->setEnabled(true);

    QTextStream in(&file);
    inputFileContents_= in.read(inputPreviewSize);

    // Limit the amount of text shown in the preview area:
    ui->inputPreview->setText(inputFileContents_.left(3000));
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

}

void MainWindow::searchFieldsSave()
{

}

void MainWindow::searchFieldsSelectionChanged()
{
    bool rowSelected = ui->searchFieldsTable->currentRow() != -1;
    ui->deleteRowButton->setEnabled(rowSelected);
}

void MainWindow::searchFieldsCellChanged(int row, int column)
{
    // Get the item text:
    //

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
