#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QPixmap>
#include <book.h>

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
    void on_previousPage_clicked();
    void on_nextPage_clicked();
    void on_lastPage_clicked();
    void on_firstPage_clicked();

    // Action on Menu
    void on_actionClose_triggered();
    void on_actionAbout_triggered();
    void on_actionOpen_triggered();
    void on_actionExtract_triggered();
    void on_actionCombine_triggered();

    // Display
    void setImage(QPixmap image);
    void refreshScreen(QString path);
    void refreshPage(int currPage, int totalPage);
    void msgBox(QString msg);

    void resizeEvent(QResizeEvent *event);

    void on_comboBox_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Book* currentBook;

signals:
};

#endif // MAINWINDOW_H
