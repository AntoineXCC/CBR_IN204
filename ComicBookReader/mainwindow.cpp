#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "book.h"
#include "archive.h"
#include "image.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QPixmap>
#include <QDir>
#include <iostream>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), currentBook(0)
{
    ui->setupUi(this);
    setMinimumSize(800,600);
    resize(1000,500);
    Image::setSize(ui->screen->width(), ui->screen->height());
    setWindowTitle(tr("Comic Book Reader"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setImage(QPixmap image) {
    ui->screen->setPixmap(image);
}

void MainWindow::refreshScreen(QString path) {
    // Display image
    QPixmap image(path);
    QPixmap scaledImage = Image::resize(image, currentBook->getRatio());

    MainWindow::setImage(scaledImage);
}

void MainWindow::refreshPage(int currPage=0, int totalPage=0) {
    if (totalPage!=0) {
        ui->totalPageDisplay->setText(QString("/") + QString::number(totalPage));
    }
    ui->currPageDisplay->setNum(currPage+1);
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



// Open menu
void MainWindow::on_actionOpen_triggered()
{
//    QString filter = "All File (*.*) ;; CBR File (*.cbr) ;; CBZ File (*.cbz)";
    QString path = QFileDialog::getExistingDirectory(this, "", "../data");


    currentBook = new Book();
    connect(currentBook, SIGNAL(pageChanged(QString)), this, SLOT(refreshScreen(QString) ));
    connect(currentBook, SIGNAL(changePageCounter(int,int)), this, SLOT(refreshPage(int,int)));
    connect(currentBook, SIGNAL(infoMsgBox(QString)), this, SLOT(msgBox(QString)));
    currentBook->setPathToDir(path);
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionExtract_triggered()
{
    QString zipPath = QFileDialog::getOpenFileName(this, tr("Choix archivre", ""));
    Unzip(zipPath);
}

void MainWindow::on_actionCombine_triggered()
{
    QString filter = "CBR File (*.cbr) ;; CBZ File (*.cbz)";
    QString path = QFileDialog::getExistingDirectory(this, tr("Choix lieu extraction"), "../data");
    QString zipPath = QFileDialog::getSaveFileName(this, tr("Choix lieu archivage"), "", QString("All File (*.*) ;; ") + filter);
    QDir dir(path);
    dir.setFilter(QDir::Files);
    QFileInfoList fileList = dir.entryInfoList();
    Zip(fileList, zipPath);
}


void MainWindow::resizeEvent(QResizeEvent *event) {
    Image::setSize(ui->screen->width(), ui->screen->height());
    std::cout<<ui->screen->width()<< ui->screen->height()<<std::endl;
    if (ui->screen->pixmap()!=0) {
        QPixmap image(currentBook->getCurrImagePath());
        MainWindow::setImage(Image::resize(image, currentBook->getRatio()));
    }
}


void MainWindow::on_comboBox_activated(const QString &r)
{
    currentBook->setRatio(r);
}
