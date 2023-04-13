#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QPixmap>
#include <QList>
#include <book.h>
#include <combinewindow.h>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    Book* currentBook;
    // Dialog window used when combining images
    CombineWindow* combineDialogWindow;
    // Supported files filter
    static QString filter;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
// Push buttons
    void on_previousPage_clicked();
    void on_nextPage_clicked();
    void on_lastPage_clicked();
    void on_firstPage_clicked();
    void on_ZoomOut_clicked();
    void on_ZoomIn_clicked();
    // Changing the performed zoom
    void on_comboBox_activated(const QString &r);
    // Set the current page
    void on_currPageDisplay_editingFinished();

// Action on Menu
    void on_actionClose_triggered();
    void on_actionAbout_triggered();
    // Open a comic book, extension have to be in filter
    // Display the first page of the comic book
    void on_actionOpen_triggered();
    // Combine images and create an archive with these images
    void on_actionCombine_triggered();
    // Set single page mode
    void on_actionSingle_Page_triggered();
    // Set double page mode and cover page mode (first page is shown alone)
    void on_actionCover_page_triggered();
    // Set double page mode and non cover page mode (first two pages are shown)
    void on_actionNo_cover_page_triggered();

// Display
    void setImage(QPixmap image);
    // Refresh the image shown according to parameters, update the page number if necessary
    void refreshScreen(bool numPageChanged);
    // Display an informtion box message
    void msgBox(QString msg);
    // Resize the image when the main window is resized
    void resizeEvent(QResizeEvent *event);
    // Set "Page fit" zoom, only used for the reset zoom shortcut
    void setDefaultZoom();

    // Create an archive with path s containing all images in l, only used after successful call of on_actionCombine_triggered
    void combineSlot(QList<int> l, QString s);
    // Event filter : Ctrl + mouse wheel applies a zoom instead of a scroll
    bool eventFilter(QObject *watched, QEvent *event);
    void wheelEvent(QWheelEvent *event) override;
    // Key shortcuts
    void keyReleaseEvent(QKeyEvent *event);


signals:
};

#endif // MAINWINDOW_H
