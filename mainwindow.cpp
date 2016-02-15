#include "mainwindow.h"
#include "modelstorage.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QMenu* fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction("Load", this, SLOT(load()));
    fileMenu->addAction("Save", this, SLOT(save()));

    QStringList headers = QStringList() << "Trip name" << "Trip days";
    model.setHorizontalHeaderLabels(headers);
    model.setColumnCount(headers.size());

    const int rowCount = 5;

    for (int row = 0; row < rowCount; row++) {
        QList <QStandardItem *> rowItems;

        for (int column = 0; column < model.columnCount(); column++) {
            QStandardItem* item = new QStandardItem(QString("%1_%2x%3").arg(headers[column]).arg(row).arg(column));
            rowItems.append(item);
        }

        model.appendRow(rowItems);
    }

    view.setModel(&model);

    setCentralWidget(&view);
}

void MainWindow::load()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (fileName.isEmpty()) {
        return;
    }

    ModelStorage::load(fileName, model);
}
void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty()) {
        return;
    }

    ModelStorage::save(fileName, model);
}
