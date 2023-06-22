#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJSEngine>
#include <QDebug>
#include <QtGlobal>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

