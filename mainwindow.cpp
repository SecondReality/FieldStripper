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

    QTextStream in(&file);
    QString inputPreview = in.read(inputPreviewSize);
    ui->inputPreview->setText(inputPreview);
}

void MainWindow::searchFieldsAddRow()
{
    ui->searchFieldsTable->setRowCount(ui->searchFieldsTable->rowCount()+1);
}

void MainWindow::searchFieldsCellChanged(int row, int column)
{
    // Get the item text:
    //

    //Create the SearchFields:
    SearchFields sf;
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
        sf.push_back(f);
    }

    // Pass these fields to the syntax highlighter;
    highlighter_.setSearchFields(sf);
    highlighter_.rehighlight();
}
