#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton_2->setEnabled(false);


    QPen pen;

    pen.setColor(QColor(255,0,0));

    ui->plot->addGraph();
    ui->plot->addGraph();

    ui->plot->graph(0)->setName("Welss");
    ui->plot->graph(1)->setName("Houses");

    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCross);

    ui->plot->graph(0)->setPen(pen);
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->plot->graph(1)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->plot->xAxis->setLabel("X");
    ui->plot->yAxis->setLabel("Y");
    ui->plot->xAxis->setRange(0,100);
    ui->plot->yAxis->setRange(0,100);

    //ui->plot->legend->setVisible(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::totalHouses(QString txt1, QString txt2 ) {

    int value1;
    int value2;
    try{
        value1 = txt1.toInt();
        value2 = txt2.toInt();
        setWells(value1);
        setConnections(value2);
        setHouses(value1 * value2);
        return value1 * value2;

    }catch(std::exception e) {
        return 0;
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->lineEdit_3->text() == ""){
        return;
    }

    housesX.clear();
    housesY.clear();

    wellsX.clear();
    wellsY.clear();

    int min = 1;
    int range = 99;

    for(int i = 0; i < getWells(); i++) {
        double x = (rand() % range) + min;
        double y = (rand() % range) + min;

        // if point exists, get another random point instead.
        if(isPointExists(wellsX,wellsY,x,y)){
            i--;
            continue;
        }

        wellsX.push_back(x);
        wellsY.push_back(y);
    }

    for(int i = 0; i < getHouses(); i++) {
        double x = (rand() % range) + min;
        double y = (rand() % range) + min;

        // if point exists, get another random point instead.
        if(isPointExists(housesX,housesY,x,y)){
            i--;
            continue;
        }

        housesX.push_back(x);
        housesY.push_back(y);
    }

    ui->plot->graph(0)->setData(wellsX, wellsY);

    ui->plot->graph(1)->setData(housesX, housesY);

    ui->plot->replot();

    ui->pushButton_2->setEnabled(true);

}

void MainWindow::on_lineEdit_editingFinished()
{
    QString txt1 = ui->lineEdit->text();
    QString txt2 = ui->lineEdit_2->text();
    ui->lineEdit_3->setText( QString::number(totalHouses(txt1,txt2)));
}

void MainWindow::on_lineEdit_2_editingFinished()
{
    QString txt1 = ui->lineEdit->text();
    QString txt2 = ui->lineEdit_2->text();
    ui->lineEdit_3->setText( QString::number(totalHouses(txt1,txt2)));
}

int MainWindow::getConnections() const
{
    return connections;
}

void MainWindow::setConnections(int value)
{
    connections = value;
}

bool MainWindow::isPointExists(QVector<double> &vectorX, QVector<double> &vectorY, double x, double y) const
{
    bool found = false;
    for(int i = 0; i < vectorX.length(); i++) {
        if(vectorX[i] == x && vectorY[i] == y){
            found = true;
            break;
        }
    }

    return found;
}

int MainWindow::getWells() const
{
    return wells;
}

void MainWindow::setWells(int value)
{
    wells = value;
}

int MainWindow::getHouses() const
{
    return houses;
}

void MainWindow::setHouses(int value)
{
    houses = value;
}




void MainWindow::on_pushButton_2_clicked()
{
    QString strInput = ui->lineEdit_4->text();
    QString filename = strInput + ".txt";
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
        file.resize(0);

        QTextStream stream(&file);

        stream << "%;" << "h;" << houses << ";w;" << wells << ";" << endl;

        for(int i = 0; i < wells; i++ ){
            stream << "W;" << wellsX[i] << ";" << wellsY[i] << ";" << "w" << QString::number(i) << ";" << endl;
        }

        for(int i = 0; i < houses; i++){
            stream << "H;" << housesX[i] << ";" << housesY[i] << ";" << "h" << QString::number(i) << ";" << endl;
        }
    }

    QMessageBox::information(this,"Save","Data Saved");
}

void MainWindow::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked()){
        ui->plot->legend->setVisible(true);
    }else{
        ui->plot->legend->setVisible(false);
    }

    ui->plot->replot();
}
