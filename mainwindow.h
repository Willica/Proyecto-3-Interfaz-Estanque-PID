#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QChart>
#include <QLineSeries>
#include <QChartView>
#include <QLineEdit>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots: // Metodos modificables desde mainwindow.cpp
    void openCylinderWindow();
    void openPrismWindow();
    void handleGraficarButtonClickCylinder();
    void handleGraficarButtonClickPrism();

private: // Atributos de la clase que pueden ser modificador mediante la modificación de los private slots

    QWidget *prismWindow;
    QWidget *cylinderWindow;

    QChart *chart1;
    QLineSeries *series1;
    QChartView *chartView1;

    QChart *chart2;
    QLineSeries *series2;
    QChartView *chartView2;

    QLineEdit *caudalInput;
    QLineEdit *alturaInput;
    QLineEdit *radioInput;
    QLineEdit *anchoInput;
    QLineEdit *largoInput;
    QLineEdit *llenadoInput;
    QLineEdit *vaciadoInput;
    QLineEdit *kpInput;
    QLineEdit *kiInput;
    QLineEdit *kdInput;

    double caudal;
    double largo;
    double ancho;
    double altura;
    double radio;
    double llenado;
    double vaciado;
    double kp;
    double ki;
    double kd;
};

#endif // MAINWINDOW_H
