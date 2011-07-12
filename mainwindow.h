#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <PreviewHighlighter.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PreviewHighlighter highlighter_;
private slots:
    void browseForInputFile();
    void searchFieldsAddRow();
    void searchFieldsCellChanged(int row, int column);
};

#endif // MAINWINDOW_H
