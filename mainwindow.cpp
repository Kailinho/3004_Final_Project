#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    aed.createPatient("Someone", 18); // First scenario so we can start coding

    connect(ui->powerOnButton, SIGNAL(released()), this, SLOT(pressPowerButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pressPowerButton()
{
    if(aed.getDeviceStatus() == false)
    {
        aed.setDeviceOn();
    }
    else
    {
        aed.setDeviceOff();
    }
}
