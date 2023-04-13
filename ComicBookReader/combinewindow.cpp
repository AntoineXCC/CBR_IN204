#include "combinewindow.h"
#include "ui_combinewindow.h"
#include <QFileDialog>
#include <stdlib.h>
#include <QMessageBox>

#include <iostream>

CombineWindow::CombineWindow(QWidget *parent) :
    CombineWindow::CombineWindow(parent, 0)
{

}

CombineWindow::CombineWindow(QWidget *parent, int totalPage) :
    QDialog(parent),
    zipPath(QString("")),
    pageList(QList<int>()),
    maxPage(totalPage),
    ui(new Ui::CombineWindow)
{
    ui->setupUi(this);
    ui->pathSelected->setReadOnly(true);
    setWindowTitle(tr("Combine"));
    resize(360, 120);

    ui->choosenPage->setText(QString("1-")+QString::number(maxPage));
}

CombineWindow::~CombineWindow()
{
    delete ui;
}

void CombineWindow::on_fileSelectButton_clicked()
{
    zipPath = QFileDialog::getSaveFileName(this, tr("Combine"), "../data");
    if (zipPath.right(4)!=QString(".cbz")) {
        zipPath = zipPath + QString(".cbz");
    }
    ui->pathSelected->setText(zipPath);
}

void CombineWindow::on_choosenPage_editingFinished()
{
    QStringList splitList = ui->choosenPage->text().split(u',');
    QString s;
    foreach(s, splitList) {
        if (s.contains('-')) {
            QStringList tmp = s.split('-');
            if (tmp.size()!=2) {
                pageList.clear();
                break;
            }
            int fst = tmp[0].toInt();
            int scd = tmp[1].toInt();
            if (fst<1 || fst>maxPage || scd<1 || scd>maxPage || fst>scd) {
                pageList.clear();
                break;
            }
            for (int i=fst; i<=scd; i++) {
                pageList.append(i);
            }

        } else {
            int elt = s.toInt();
            if (elt<1 || elt>maxPage) {
                pageList.clear();
                break;
            }
            pageList.append(elt);
        }
    }
}

void CombineWindow::on_OkButton_clicked()
{
    if (zipPath == QString("") || pageList.empty()) {
        QMessageBox::information(this, "Combine", QString("Error"));
    } else {
        emit combineSignal(pageList, zipPath);
        close();
    }
}

void CombineWindow::on_CancelButton_clicked()
{
    close();
}
