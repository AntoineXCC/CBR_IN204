#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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

void MainWindow::on_actionClose_triggered()
{
    QApplication::quit();
}

void MainWindow::on_previousPage_clicked()
{
    QMessageBox::information(this, "", "Page précédente");
}

void MainWindow::on_nextPage_clicked()
{
    QMessageBox::information(this, "", "Page suivante");
}

void MainWindow::on_lastPage_clicked()
{
    QMessageBox::information(this, "", "Dernière page");
}

void MainWindow::on_firstPage_clicked()
{
    QMessageBox::information(this, "", "Première page");
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionOpen_triggered()
{
    QString filter = "All File (*.*) ;; CBR File (*.cbr) ;; CBZ File (*.cbz)";
    QString file_name = QFileDialog::getOpenFileName(this, "", "", filter);
}
