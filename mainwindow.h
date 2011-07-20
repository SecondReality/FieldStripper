#undef __STRICT_ANSI__
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <PreviewHighlighter.h>

#include "FieldStripper.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QString toCSV(const FieldStripper::StringTable &st);
    Ui::MainWindow *ui;
    PreviewHighlighter highlighter_;
    QString inputFileContents_;
    SearchFields searchFields_;

private slots:
    void browseForInputFile();
    void searchFieldsAddRow();
    void searchFieldsDeleteRow();
    void searchFieldsLoad();
    void searchFieldsSave();
    void searchFieldsSelectionChanged();
    void searchFieldsCellChanged(int row, int column);
    void go();
};

#endif // MAINWINDOW_H
