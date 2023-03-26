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
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), currentBook(0)
{
    ui->setupUi(this);
    setMinimumSize(800,600);
    resize(1000,500);
    /*           A adapter, ou à changer la policy                  */
    ui->scrollArea->resize(978, 483);
    Image::setSize(ui->scrollArea->width(), ui->scrollArea->height());
    ui->screen->resize(ui->scrollArea->width(), ui->scrollArea->height());
    setWindowTitle(tr("Comic Book Reader"));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete currentBook;
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

// Menu
void MainWindow::on_actionClose_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionOpen_triggered()
{
//    QString filter = "All File (*.*) ;; CBR File (*.cbr) ;; CBZ File (*.cbz)";
    QString path = QFileDialog::getExistingDirectory(this, "", "../data");


    currentBook = new Book();
    connect(currentBook, SIGNAL(pageChanged(QString)), this, SLOT(refreshScreen() ));
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



void MainWindow::setImage(QPixmap image) {
    ui->screen->setPixmap(image);
}


void MainWindow::refreshScreen() {
    if (currentBook==0) return;
    // Display image
    QSize valRatio;
    QPixmap image = currentBook->getCurrImage();
    if (ui->screen->pixmap()==0) {
        valRatio = image.size();
    } else {
        valRatio = ui->screen->pixmap()->size();
    }
    QPixmap scaledImage = Image::resize(image, currentBook->getRatio(), valRatio);
    setImage(scaledImage);
    ui->scrollArea->verticalScrollBar()->setSliderPosition(ui->scrollArea->verticalScrollBar()->minimum());
    ui->scrollArea->horizontalScrollBar()->setSliderPosition(ui->scrollArea->horizontalScrollBar()->minimum());
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

void MainWindow::resizeEvent(QResizeEvent *event) {
    Image::setSize(ui->scrollArea->width(), ui->scrollArea->height());
    refreshScreen();
//    std::cout<< "Taille screen" << ui->screen->width() << " et "<< ui->screen->height()<<std::endl;
//    std::cout<< "Taille scrollArea" << ui->scrollArea->width() << " et "<< ui->scrollArea->height()<<std::endl;
}


void MainWindow::on_comboBox_activated(const QString &r)
{
    currentBook->setRatio(r);
    refreshScreen();

}

void MainWindow::on_pushButton_clicked()
{
    QString path = QString("/home/antoine/Cours/IN204/Projet/Projet CBR/data/Captain Marvel");
    currentBook = new Book();
    connect(currentBook, SIGNAL(pageChanged(QString)), this, SLOT(refreshScreen() ));
    connect(currentBook, SIGNAL(changePageCounter(int,int)), this, SLOT(refreshPage(int,int)));
    connect(currentBook, SIGNAL(infoMsgBox(QString)), this, SLOT(msgBox(QString)));
    currentBook->setPathToDir(path);
}

void MainWindow::on_ZoomOut_clicked()
{
    currentBook->setRatio(QString("Custom"));
    ui->comboBox->setCurrentIndex(2);
    QPixmap image(currentBook->getCurrImagePath());
    setImage(Image::zoomOut(image, ui->screen->pixmap()->size()));
}

void MainWindow::on_ZoomIn_clicked()
{
    currentBook->setRatio(QString("Custom"));
    ui->comboBox->setCurrentIndex(2);
    QPixmap image(currentBook->getCurrImagePath());
    setImage(Image::zoomIn(image, ui->screen->pixmap()->size()));
}

void MainWindow::on_actionSingle_Page_triggered()
{
    currentBook->setSingleMode(true);
    refreshScreen();
}


void MainWindow::on_actionDouble_Page_triggered()
{
    currentBook->setSingleMode(false);
    refreshScreen();
}
