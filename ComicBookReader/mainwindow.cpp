#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <book.h>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QPixmap>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), currentBook(0)
{
    ui->setupUi(this);
    setMinimumSize(800,600);
    resize(1000,500);
    setWindowTitle(tr("Comic Book Reader"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshScreen(QString path, QString pageText) {
    // Display image
    QPixmap image(path);
    int w = ui->screen->width();
    int h = ui->screen->height();
    ui->screen->setPixmap(image.scaled(w,h,Qt::KeepAspectRatio));

    // Display page
    ui->pageDisplay->setText(pageText);
}

void MainWindow::msgBox(QString msg) {
    QMessageBox::information(this, "", msg);
}

void MainWindow::on_actionClose_triggered()
{
    QApplication::quit();
}

void MainWindow::on_previousPage_clicked()
{
    currentBook->previous();
}

void MainWindow::on_nextPage_clicked()
{
    currentBook->next();
}

void MainWindow::on_lastPage_clicked()
{
    currentBook->last();
}

void MainWindow::on_firstPage_clicked()
{
    currentBook->first();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::aboutQt(this);
}


// Open menu
void MainWindow::on_actionOpen_triggered()
{
//    QString filter = "All File (*.*) ;; CBR File (*.cbr) ;; CBZ File (*.cbz)";
    QString path = QFileDialog::getExistingDirectory(this, "", "../data");
    currentBook = new Book();
    connect(currentBook, SIGNAL(pageChanged(QString, QString)), this, SLOT(refreshScreen(QString,QString) ));
    connect(currentBook, SIGNAL(infoMsgBox(QString)), this, SLOT(msgBox(QString)));
    currentBook->setPathToDir(path);
}
