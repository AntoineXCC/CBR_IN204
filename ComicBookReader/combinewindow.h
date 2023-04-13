#ifndef COMBINEWINDOW_H
#define COMBINEWINDOW_H

#include <QDialog>
#include <QString>
#include <QList>

namespace Ui {
    class CombineWindow;
}

class CombineWindow : public QDialog {
    Q_OBJECT

private:
    Ui::CombineWindow *ui;
    // Path of the archive
    QString zipPath;
    // List of all pages that have to be extracted
    QList<int> pageList;
    // Number of pages of the Comic Book
    int maxPage;

public:
    explicit CombineWindow(QWidget *parent = 0);
    CombineWindow(QWidget *parent = 0, int totalPage = 0);
    ~CombineWindow();

private slots:
    // Choosing path and name of the new archive, adding .cbz extension if not already set
    void on_fileSelectButton_clicked();
    // Update pageList when user types desired pages that have to be extracted
    // Can only be number separated with '-' or ',' otherwise clear pageList
    void on_choosenPage_editingFinished();
    // When clicking on Ok button, error if pageList or path empty otherwise emit signal
    void on_OkButton_clicked();
    // Cancel button
    void on_CancelButton_clicked();

signals:
    // Signal sent with pageList and zipPath
    void combineSignal(QList<int> l, QString s);
};

#endif // COMBINEWINDOW_H
