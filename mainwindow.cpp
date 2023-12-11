#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->batteryLabel->setText("Battery Level: Initializing");
    ui->powerButton->setCursor(Qt::PointingHandCursor);
    imageLabel = new QLabel(this);
    imageLabel->resize(200, 48);
    imageLabel->move(463, 170);
    imageLabel->raise();
    imageLabel->setStyleSheet("background-color: black;");

    imageLabelCPR = new QLabel(this);
    imageLabelCPR->move(470, 230);
    buttonEnable(false);
    connect(&aed, SIGNAL(batteryLevelChanged(int)), this, SLOT(updateBatteryLevel(int)));
    connect(&aed, SIGNAL(shockCountChanged(int)), this, SLOT(updateShockCount(int)));
    connect(ui->powerButton, SIGNAL(released()), this, SLOT(pressPowerButton()));
    connect(ui->adultPad1CheckBox, SIGNAL(stateChanged(int)), this, SLOT(applyPads()));
    connect(ui->adultPad2CheckBox, SIGNAL(stateChanged(int)), this, SLOT(applyPads()));
    connect(ui->childPad1CheckBox, SIGNAL(stateChanged(int)), this, SLOT(applyPads()));
    connect(ui->childPad2CheckBox, SIGNAL(stateChanged(int)), this, SLOT(applyPads()));
    connect(&aed, SIGNAL(displayHRSignal(int)), this, SLOT(displayHR(int)));
    connect(&aed, SIGNAL(displayCompressionsSignal(int)), this, SLOT(displayCompressions(int)));
    connect(&aed, SIGNAL(enableButton(bool)), this, SLOT(buttonEnable(bool)));
    connect(this, SIGNAL(badCPR()), &aed, SLOT(badCPRClicked()));
    connect(this, SIGNAL(okCPR()), &aed, SLOT(okCPRClicked()));
    connect(this, SIGNAL(goodCPR()), &aed, SLOT(goodCPRClicked()));
    connect(this, SIGNAL(Release()), &aed, SLOT(releaseClicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pressPowerButton() {

    if (aed.getPower()) {
        ui->powerButton->setStyleSheet("QPushButton{ image: url(:/images/power-button.png); border-radius: 30px; background-color: rgb(237, 51, 59);}");
    } else {
        ui->powerButton->setStyleSheet("QPushButton{ image: url(:/images/power-button.png); border-radius: 30px; background-color: rgb(51, 209, 122);}");       
        initializePatient();//Initialize patient when the device is turned on
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

void MainWindow::applyPads(){
    aed.setPadsStatus(ui->adultPad1CheckBox->isChecked(), ui->adultPad2CheckBox->isChecked(), ui->childPad1CheckBox->isChecked(), ui->childPad2CheckBox->isChecked());
}

void MainWindow::updateBatteryLevel(int level){

    // Adjust the color based on the battery level
    QString textColor;
    if (level <= 20) {
        textColor = "red";  // Change to your desired color
    } else if(level <= 60) {
        textColor = "white";  // Change to your default color
    }
    ui->batteryLabel->setText("Battery Level: " + QString::number(level) + "%");
    // Update the stylesheet
    ui->batteryLabel->setStyleSheet(QString("QLabel { color: %1; }").arg(textColor));
    QApplication::processEvents(); //Force UI updates
}

void MainWindow::updateShockCount(int count){
    ui->shockLabel->setText("# of Shocks: " + QString::number(count));
    QApplication::processEvents(); //Force UI updates
}






void MainWindow::displayHR(int status){
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
void MainWindow::displayCompressions(int quality){
    imageLabelCPR->raise();
    if (quality==1){
        imageLabelCPR->resize(20, 5);
        imageLabelCPR->setStyleSheet("background-color: red;");
    }
    else if (quality==2) {
        imageLabelCPR->resize(35, 5);
        imageLabelCPR->setStyleSheet("background-color: yellow;");
    }
    else if(quality==4){
        imageLabelCPR->resize(75, 5);
        imageLabelCPR->setStyleSheet("background-color: blue;");
    }
    else if(quality==0){
        imageLabelCPR->setStyleSheet("background-color: transparent;");
    }
    else{
        imageLabelCPR->resize(55, 5);
        imageLabelCPR->setStyleSheet("background-color: green;");
    }
    imageLabelCPR->show();
}

void MainWindow::on_pushButton_clicked()
{
    emit badCPR();
}


void MainWindow::on_pushButton_2_clicked()
{
    emit okCPR();
}


void MainWindow::on_pushButton_3_clicked()
{
    emit goodCPR();
}

void MainWindow::buttonEnable(bool value){
    ui->pushButton->setEnabled(value);
    ui->pushButton_2->setEnabled(value);
    ui->pushButton_3->setEnabled(value);
    ui->pushButton_4->setEnabled(value);
}

void MainWindow::on_pushButton_4_clicked()
{
    emit Release();
}

