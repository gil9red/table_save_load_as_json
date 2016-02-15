#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QTableView>
#include <QStandardItemModel>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

public slots:
    void load();
    void save();

private:
    QTableView view;
    QStandardItemModel model;
};

#endif // MAINWINDOW_H
