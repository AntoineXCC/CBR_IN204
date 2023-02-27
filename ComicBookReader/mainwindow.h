#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionClose_triggered();

    void on_previousPage_clicked();

    void on_nextPage_clicked();

    void on_lastPage_clicked();

    void on_firstPage_clicked();

//    Action on Menu
    void on_actionAbout_triggered();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
