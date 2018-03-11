#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int getHouses() const;
    void setHouses(int value);

    int getWells() const;
    void setWells(int value);

    int getConnections() const;

    int totalHouses(QString txt1, QString txt2 );

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_pushButton_2_clicked();

    void on_checkBox_clicked();

private:
    int houses;
    int wells;
    int connections;

    QVector<double> wellsX, wellsY;

    QVector<double> housesX, housesY;

    void setConnections(int value);

    bool isPointExists(QVector<double> &vectorX, QVector<double> &vectorY, double x, double y) const;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
