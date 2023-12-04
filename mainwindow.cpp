#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->batteryLabel->setText("Battery Level: Initializing");

    aed.createPatient(true, 3); // First scenario so we can start coding

    imageLabel = new QLabel(this);
    imageLabel->resize(200, 48);
    imageLabel->move(463, 170);
    imageLabel->raise();
    imageLabel->setStyleSheet("background-color: black;");

    connect(&aed, SIGNAL(batteryLevelChanged(int)), this, SLOT(updateBatteryLevel(int)));
    connect(&aed, SIGNAL(shockCountChanged(int)), this, SLOT(updateShockCount(int)));
    connect(ui->powerButton, SIGNAL(released()), this, SLOT(pressPowerButton()));
    connect(ui->adultPad1CheckBox, SIGNAL(stateChanged(int)), this, SLOT(applyPads()));
    connect(ui->adultPad2CheckBox, SIGNAL(stateChanged(int)), this, SLOT(applyPads()));
    connect(ui->childPad1CheckBox, SIGNAL(stateChanged(int)), this, SLOT(applyPads()));
    connect(ui->childPad2CheckBox, SIGNAL(stateChanged(int)), this, SLOT(applyPads()));
    connect(&aed, SIGNAL(displayHRSignal(int)), this, SLOT(displayHR(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pressPowerButton(){
    if(aed.getPower()){
        ui->powerButton->setStyleSheet("QPushButton{ image: url(:/images/power-button.png); border-radius: 30px; background-color: rgb(237, 51, 59);}"); 
    }
    else{
        ui->powerButton->setStyleSheet("QPushButton{ image: url(:/images/power-button.png); border-radius: 30px; background-color: rgb(51, 209, 122);}");
    }

    aed.togglePower();
    if(aed.getPower()){
        ui->powerButton->setStyleSheet("QPushButton{ image: url(:/images/power-button.png); border-radius: 30px; color: rgb(255, 255, 255); background-color: rgb(51, 209, 122);}");
        ui->adultPad1CheckBox->setEnabled(true);
        ui->adultPad2CheckBox->setEnabled(true);
        ui->childPad1CheckBox->setEnabled(true);
        ui->childPad2CheckBox->setEnabled(true);
    }
    else{
        ui->powerButton->setStyleSheet("QPushButton{ image: url(:/images/power-button.png); border-radius: 30px; background-color: rgb(237, 51, 59);}");
        ui->batteryLabel->setText("Battery Level: Initializing");

        ui->adultPad1CheckBox->setChecked(false);
        ui->adultPad2CheckBox->setChecked(false);
        ui->childPad1CheckBox->setChecked(false);
        ui->childPad2CheckBox->setChecked(false);

        ui->adultPad1CheckBox->setEnabled(false);
        ui->adultPad2CheckBox->setEnabled(false);
        ui->childPad1CheckBox->setEnabled(false);
        ui->childPad2CheckBox->setEnabled(false);
    }
}

void MainWindow::applyPads()
{
    aed.setPadsStatus(ui->adultPad1CheckBox->isChecked(), ui->adultPad2CheckBox->isChecked(), ui->childPad1CheckBox->isChecked(), ui->childPad2CheckBox->isChecked());
}

void MainWindow::updateBatteryLevel(int level) {
    ui->batteryLabel->setText("Battery Level: " + QString::number(level) + "%");
    QApplication::processEvents(); //Force UI updates
}

void MainWindow::updateShockCount(int count) {
    ui->shockLabel->setText("# of Shocks: " + QString::number(count));
    QApplication::processEvents(); //Force UI updates
}

void MainWindow::displayHR(int status) {
    QPixmap originalImage;

    // Update the image based on the status
    switch (status) {
        case 1:
            originalImage.load(":/images/asys.jpg");
            break;
        case 2:
            originalImage.load(":/images/stable.jpg");
            break;
        case 3:
            originalImage.load(":/images/vfib.jpg");
            break;
        case 4:
            originalImage.load(":/images/vtach.jpg");
            break;
        case 5:
            originalImage.load(":/images/pea.jpg");
            break;
        case 6:
            originalImage.load(":/images/black.jpg");
        default:
            break;
    }

    // Resize and set the image
    QPixmap resizedImage = originalImage.scaled(200, 48, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    imageLabel->setPixmap(resizedImage);

    // Show the QLabel
    imageLabel->show();
}
