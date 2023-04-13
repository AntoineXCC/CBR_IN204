#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "book.h"
#include "archiveManager.h"
#include "image.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QPixmap>
#include <QDir>
#include <QScrollArea>
#include <QScrollBar>
#include <QShortcut>
#include <QWheelEvent>


QString MainWindow::filter = QString("Supported Files (*.cbr *.cbz *.rar *zip *.7z *.7zip)");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), currentBook(0)
{
// Initialisation
    ui->setupUi(this);
    setMinimumSize(800,600);
    resize(1000,500);
    // Set size of the scroll area to get good size for the image
    ui->scrollArea->resize(978, 483);
    Image::setSize(ui->scrollArea->width(), ui->scrollArea->height());
    ui->screen->resize(ui->scrollArea->width(), ui->scrollArea->height());
    // Set an event filter to the mouse wheel so that if ctrl key is pressed and we use the mouse wheel a zoom is performed instead of scrolling
    ui->scrollArea->verticalScrollBar()->installEventFilter(this);
    setWindowTitle(tr("Comic Book Reader"));

// Shortcut part
    QShortcut *zoomInShortcut = new QShortcut(QKeySequence("CTRL++"), this);
    QShortcut *zoomOutShortcut = new QShortcut(QKeySequence("CTRL+-"), this);
    QShortcut *resetZoom = new QShortcut(QKeySequence("CTRL+0"), this);
    connect(zoomInShortcut, &QShortcut::activated, this, &MainWindow::on_ZoomIn_clicked);
    connect(zoomOutShortcut, &QShortcut::activated, this, &MainWindow::on_ZoomOut_clicked);
    connect(resetZoom, &QShortcut::activated, this, &MainWindow::setDefaultZoom);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete currentBook;
    QDir dir("../data/");
    dir.removeRecursively();
}

void MainWindow::on_previousPage_clicked()
{
    if (currentBook) {
        currentBook->previous();
    } else {
        msgBox(QString("No Comic Book"));
    }
}

void MainWindow::on_nextPage_clicked()
{
    if (currentBook) {
        currentBook->next();
    } else {
        msgBox(QString("No Comic Book"));
    }
}

void MainWindow::on_lastPage_clicked()
{
    if (currentBook) {
        currentBook->last();
    } else {
        msgBox(QString("No Comic Book"));
    }
}

void MainWindow::on_firstPage_clicked()
{
    if (currentBook) {
        currentBook->first();
    } else {
        msgBox(QString("No Comic Book"));
    }
}

void MainWindow::on_ZoomOut_clicked()
{
    if (!currentBook) return;
    currentBook->setRatio(QString("Custom"));
    ui->comboBox->setCurrentIndex(2);
    QPixmap image = currentBook->getCurrImage();
    setImage(Image::zoomOut(image, ui->screen->pixmap()->size()));
}

void MainWindow::on_ZoomIn_clicked()
{
    if (!currentBook) return;
    currentBook->setRatio(QString("Custom"));
    ui->comboBox->setCurrentIndex(2);
    QPixmap image = currentBook->getCurrImage();
    setImage(Image::zoomIn(image, ui->screen->pixmap()->size()));
}

void MainWindow::on_comboBox_activated(const QString &r)
{
    if (!currentBook) return;
    currentBook->setRatio(r);
    refreshScreen(false);

}

void MainWindow::on_currPageDisplay_editingFinished()
{
    int page = ui->currPageDisplay->text().toInt();
    if (!currentBook) {
        return;
    }
    if (page<=0 || page>currentBook->getTotalPage()) {
        ui->currPageDisplay->setText(QString::number(currentBook->getCurrPage()+1));
    } else {
        currentBook->setCurrPage(page-1);
    }
}


void MainWindow::on_actionClose_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open", "../", filter);
    if (filename==QString("")) return;
    QString path = QString("../data/" + QFileInfo(filename).baseName());
    Unzip(filename, path);
    QDir dir(path);
    dir.setNameFilters(Image::imageFilters);
    if (!dir.count()) {
        msgBox(QString("No image or no image supported"));
        return;
    }
    currentBook = new Book();
    ui->comboBox->setCurrentIndex(0);
    connect(currentBook, SIGNAL(pageChanged(bool)), this, SLOT(refreshScreen(bool) ));
    connect(currentBook, SIGNAL(infoMsgBox(QString)), this, SLOT(msgBox(QString)));
    currentBook->setPathToDir(path);
}

void MainWindow::on_actionCombine_triggered()
{
    if (currentBook) {
        combineDialogWindow = new CombineWindow(this, currentBook->getTotalPage());
        combineDialogWindow->show();
        connect(combineDialogWindow, SIGNAL(combineSignal(QList<int>,QString)), this, SLOT(combineSlot(QList<int>,QString)));
    } else {
        msgBox(QString("No Comic Book"));
    }
}

void MainWindow::on_actionSingle_Page_triggered()
{
    if (!currentBook) return;
    currentBook->setSingleMode(true);
    refreshScreen(false);
}

void MainWindow::on_actionCover_page_triggered()
{
    if (!currentBook) return;
    currentBook->setCoverPageMode(true);
    refreshScreen(false);
}

void MainWindow::on_actionNo_cover_page_triggered()
{
    if (!currentBook) return;
    currentBook->setCoverPageMode(false);
    refreshScreen(false);
}


void MainWindow::setImage(QPixmap image) {
    ui->screen->setPixmap(image);
}


void MainWindow::refreshScreen(bool numPageChanged) {
    if (!currentBook) return;
    QSize valRatio;
    QPixmap image = currentBook->getCurrImage();
    if (ui->screen->pixmap()==0) {
        valRatio = image.size();
    } else {
        valRatio = QSize(image.scaledToHeight(ui->screen->pixmap()->height()).size());
    }
    QPixmap scaledImage = Image::resize(image, currentBook->getRatio(), valRatio);
    setImage(scaledImage);
    ui->scrollArea->verticalScrollBar()->setSliderPosition(ui->scrollArea->verticalScrollBar()->minimum());
    ui->scrollArea->horizontalScrollBar()->setSliderPosition(ui->scrollArea->horizontalScrollBar()->minimum());
    if (numPageChanged) {
        ui->totalPageDisplay->setText(QString("/") + QString::number(currentBook->getTotalPage()));
        ui->currPageDisplay->setText(QString::number(currentBook->getCurrPage()+1));
    }
}

void MainWindow::msgBox(QString msg) {
    QMessageBox::information(this, "", msg);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    Image::setSize(ui->scrollArea->width(), ui->scrollArea->height());
    refreshScreen(false);
}

void MainWindow::setDefaultZoom() {
    if (!currentBook) return;
    currentBook->setRatio(QString("Fit page"));
    ui->comboBox->setCurrentIndex(0);
    refreshScreen(false);
}


void MainWindow::combineSlot(QList<int> l, QString s) {
    QFileInfoList* fileList = currentBook->getFileInfoList((QList<int>) l);
    Zip(*fileList, s);
    delete fileList;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::Wheel) {
        QWheelEvent* we = static_cast<QWheelEvent*>(event);
        wheelEvent(we);
        event->accept();
        return true;
    }
    return false;
}

void MainWindow::wheelEvent(QWheelEvent *event) {
    if (event->modifiers().testFlag(Qt::ControlModifier)) {
        if (event->delta() >0) {
            on_ZoomIn_clicked();
        } else if (event->delta()<0){
            on_ZoomOut_clicked();
        }
    } else {
        if (event->delta() <0) {
            int newValue = ui->scrollArea->verticalScrollBar()->value() + 3*ui->scrollArea->verticalScrollBar()->singleStep();
            ui->scrollArea->verticalScrollBar()->setValue(newValue);
        } else if (event->delta() > 0) {
            int newValue = ui->scrollArea->verticalScrollBar()->value() - 3*ui->scrollArea->verticalScrollBar()->singleStep();
            ui->scrollArea->verticalScrollBar()->setValue(newValue);
        }
    }
    event->accept();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (!currentBook) return;
    switch (event->key()) {
        case Qt::Key_Left :
            if (ui->scrollArea->horizontalScrollBar()->value()==ui->scrollArea->horizontalScrollBar()->minimum()
                    && currentBook->getCurrPage()!=0) {
                on_previousPage_clicked();
                ui->scrollArea->horizontalScrollBar()->setValue(ui->scrollArea->horizontalScrollBar()->maximum());
            }
            break;
        case Qt::Key_Right :
            if (ui->scrollArea->horizontalScrollBar()->value()==ui->scrollArea->horizontalScrollBar()->maximum()
                       && currentBook->getCurrPage()!=currentBook->getTotalPage() - 1) {
                on_nextPage_clicked();
            }
            break;
        case Qt::Key_End :
            on_lastPage_clicked();
            break;
    case Qt::Key_Home :
        on_firstPage_clicked();
        break;
    }
}

