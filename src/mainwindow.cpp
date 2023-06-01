#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ttextedit.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_textEdit = new TTextEdit(this);
    ui->verticalLayout->addWidget(m_textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

