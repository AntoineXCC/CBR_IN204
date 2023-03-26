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
private:
    Ui::MainWindow *ui;
    Book* currentBook;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_previousPage_clicked();
    void on_nextPage_clicked();
    void on_lastPage_clicked();
    void on_firstPage_clicked();
    void on_comboBox_activated(const QString &r);

    // Action on Menu
    void on_actionClose_triggered();
    void on_actionAbout_triggered();
    void on_actionOpen_triggered();
    void on_actionExtract_triggered();
    void on_actionCombine_triggered();
    void on_actionSingle_Page_triggered();
    void on_actionDouble_Page_triggered();

    // Display
    void setImage(QPixmap image);
    void refreshScreen();
    void refreshPage(int currPage, int totalPage);
    void msgBox(QString msg);

    void resizeEvent(QResizeEvent *event);

    // Temp
    void on_pushButton_clicked();

    // Shortcuts




    void on_ZoomOut_clicked();

    void on_ZoomIn_clicked();



signals:
};

#endif // MAINWINDOW_H
