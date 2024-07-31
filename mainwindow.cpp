
// --------------------- SE INCLUYEN SOLO LAS LIBRERIAS NECESARIAS ---------------------------- //

#include <iostream>     // Librería de entrada y salida
#include <iomanip>      // Librería para incluir set precision (reducir decimales mostrados en pantalla)
#include <fstream>      // Librería para archivos externos
#include <QApplication> // Librería principal de Qt
#include <QWidget>      // Librería para la ventana principal y otras ventanas
#include <QPushButton>  // Librería para botones
#include <QLabel>       // Librería para etiquetas
#include <QLineEdit>    // Librería para campos de texto
#include <QChart>       // Librería para gráficos
#include <QChartView>   // Librería para ver gráficos
#include <QValueAxis>   // Librería para ejes en gráficos
#include <QEvent>       // Librería para eventos
#include <QFont>        // Librería para fuentes
#include <QFile>        // Libreria para manejar archivos
#include <QMessageBox>  // Libreria para mostrar mensajes
#include "mainwindow.h" // Librería asociada a las ventanas
#include "tanque.h"     // Librería que incluye los estanques y el controlador PID

// Utilización del espacio de nombre std y estanques
using namespace std; using namespace Estanques;

// Ventana Principal
MainWindow::MainWindow() {
    // Configuración de la ventana principal
    setWindowTitle("Control de nivel de estanque mediante controlador PID");
    setFixedSize(800, 600); // Ventana no redimensionable
    setStyleSheet("background-color: white; color: black;");
    // Inicialización de ventanas de acuerdo a la forma
    prismWindow = nullptr;
    cylinderWindow = nullptr;
    // Título
    QLabel *titulo1 = new QLabel("Control de nivel de estanque mediante controlador PID", this);
    titulo1->setGeometry(0, 20, 800, 50);
    titulo1->setAlignment(Qt::AlignCenter);
    QFont serifFont("Times", 20, QFont::Bold);
    titulo1->setFont(serifFont);
    titulo1->setStyleSheet("color: black; background-color: transparent;");
    // Subtítulo
    QLabel *subtitulo = new QLabel("Proyecto 3 Programación en C/C++", this);
    subtitulo->setGeometry(0, 70, 800, 30);
    subtitulo->setAlignment(Qt::AlignCenter);
    QFont serifFontSub("Times", 16, QFont::Bold);
    subtitulo->setFont(serifFontSub);
    subtitulo->setStyleSheet("color: black; background-color: transparent;");
    // Texto "Seleccione la forma:"
    QLabel *seleccioneForma = new QLabel("Seleccione la forma:", this);
    seleccioneForma->setGeometry(0, 150, 800, 30);
    seleccioneForma->setAlignment(Qt::AlignCenter);
    QFont serifFontSelect("Times", 14, QFont::Bold);
    seleccioneForma->setFont(serifFontSelect);
    seleccioneForma->setStyleSheet("color: black; background-color: transparent;");
    // Botón forma cilíndrica
    QPushButton *forma1 = new QPushButton(this);
    forma1->setGeometry(150, 200, 200, 200);
    forma1->setIcon(QIcon(":/images/cilindro.png"));
    forma1->setIconSize(QSize(150, 150));
    forma1->setStyleSheet("color: black; background-color: white; border: 2px solid black; border-radius: 10px;");
    connect(forma1, &QPushButton::clicked, this, &MainWindow::openCylinderWindow);
    // Etiqueta para el botón forma cilíndrica
    QLabel *labelForma1 = new QLabel("Cilindro", this);
    labelForma1->setGeometry(150, 410, 200, 30);
    labelForma1->setAlignment(Qt::AlignCenter);
    QFont serifFontLabel("Times", 14, QFont::Bold);
    labelForma1->setFont(serifFontLabel);
    labelForma1->setStyleSheet("color: black; background-color: transparent;");
    // Botón forma prisma rectangular
    QPushButton *forma2 = new QPushButton(this);
    forma2->setGeometry(450, 200, 200, 200);
    forma2->setIcon(QIcon(":/images/prisma_rectangular.png"));
    forma2->setIconSize(QSize(150, 150));
    forma2->setStyleSheet("color: black; background-color: white; border: 2px solid black; border-radius: 10px;");
    connect(forma2, &QPushButton::clicked, this, &MainWindow::openPrismWindow);
    // Etiqueta para el botón forma prisma rectangular
    QLabel *labelForma2 = new QLabel("Prisma rectangular", this);
    labelForma2->setGeometry(450, 410, 200, 30);
    labelForma2->setAlignment(Qt::AlignCenter);
    labelForma2->setFont(serifFontLabel);
    labelForma2->setStyleSheet("color: black; background-color: transparent;");
    // Efecto oscurecer boton
    forma1->installEventFilter(this);
    forma2->installEventFilter(this);
    // INTEGRANTES
    QLabel *nombres = new QLabel("Wilfredo Lara Jordán\nIgnacio Henríquez Molina", this);
    nombres->setGeometry(10, 550, 300, 40);
    QFont serifFontNames("Times", 12, QFont::Bold);
    nombres->setFont(serifFontNames);
    nombres->setStyleSheet("color: black; background-color: transparent;");
}
MainWindow::~MainWindow() {// Destructor
}
// Filtro oscuerecer botón de forma.
bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    QPushButton *button = qobject_cast<QPushButton*>(watched);
    if (button) {
        if (event->type() == QEvent::Enter) {
            button->setStyleSheet("background-color: rgba(0, 0, 0, 0.3); border: 2px solid black; border-radius: 10px;");
        } else if (event->type() == QEvent::Leave) {
            button->setStyleSheet("background-color: white; border: 2px solid black; border-radius: 10px;");
        }
    }
    return QWidget::eventFilter(watched, event);
}
// Ventana de Cilindro
void MainWindow::openCylinderWindow() {
    // Crear una nueva ventana para la forma cilíndrica
    QWidget *cylinderWindow = new QWidget();
    cylinderWindow->setWindowTitle("Cilindro");
    cylinderWindow->setFixedSize(800, 640); // Dimensiones 800x600
    cylinderWindow->setStyleSheet("background-color: white; color: black;");
    // Título de la ventana del Cilindro
    QLabel *tituloCilindro = new QLabel("Control PID para estanque Cilíndrico", cylinderWindow);
    tituloCilindro->setGeometry(0, 10, 800, 30);
    tituloCilindro->setAlignment(Qt::AlignCenter);
    QFont serifFont("Times", 16, QFont::Bold);
    tituloCilindro->setFont(serifFont);
    tituloCilindro->setStyleSheet("color: black; background-color: transparent;");
    // Parámetros
    QLabel *parametrosTitulo = new QLabel("Parámetros", cylinderWindow);
    parametrosTitulo->setGeometry(550, 60, 200, 30);
    QFont serifFontParam("Times", 14, QFont::Bold);
    parametrosTitulo->setFont(serifFontParam);
    // Parametros: Altura
    QLabel *alturaLabel = new QLabel("Altura:", cylinderWindow);
    alturaLabel->setGeometry(550, 100, 100, 30);
    alturaInput = new QLineEdit(cylinderWindow);
    alturaInput->setGeometry(650, 100, 100, 30);
    alturaInput->setStyleSheet("border: 1px solid black;");
    // Parametros: Radio
    QLabel *radioLabel = new QLabel("Radio:", cylinderWindow);
    radioLabel->setGeometry(550, 140, 100, 30);
    radioInput = new QLineEdit(cylinderWindow);
    radioInput->setGeometry(650, 140, 100, 30);
    radioInput->setStyleSheet("border: 1px solid black;");
    // Parametros: Caudal
    QLabel *caudalLabel = new QLabel("Caudal:", cylinderWindow);
    caudalLabel->setGeometry(550, 180, 100, 30);
    caudalInput = new QLineEdit(cylinderWindow);
    caudalInput->setGeometry(650, 180, 100, 30);
    caudalInput->setStyleSheet("border: 1px solid black;");
    // Set Points
    QLabel *setPointsTitulo = new QLabel("Set Points", cylinderWindow);
    setPointsTitulo->setGeometry(550, 230, 200, 30);
    setPointsTitulo->setFont(serifFontParam);
    // Set Points: Llenado
    QLabel *llenadoLabel = new QLabel("Porcentaje llenado:", cylinderWindow);
    llenadoLabel->setGeometry(550, 270, 150, 30);
    llenadoInput = new QLineEdit(cylinderWindow);
    llenadoInput->setGeometry(700, 270, 50, 30);
    llenadoInput->setStyleSheet("border: 1px solid black;");
    // Set points: Vaciado
    QLabel *vaciadoLabel = new QLabel("Porcentaje vaciado:", cylinderWindow);
    vaciadoLabel->setGeometry(550, 310, 150, 30);
    vaciadoInput = new QLineEdit(cylinderWindow);
    vaciadoInput->setGeometry(700, 310, 50, 30);
    vaciadoInput->setStyleSheet("border: 1px solid black;");
    // Parámetros PID
    QLabel *pidTitulo = new QLabel("Parámetros PID", cylinderWindow);
    pidTitulo->setGeometry(550, 360, 200, 30);
    pidTitulo->setFont(serifFontParam);
    // Parametros PID: Kp
    QLabel *kpLabel = new QLabel("Kp:", cylinderWindow);
    kpLabel->setGeometry(550, 400, 100, 30);
    kpInput = new QLineEdit(cylinderWindow);
    kpInput->setGeometry(650, 400, 100, 30);
    kpInput->setStyleSheet("border: 1px solid black;");
    // Parametros PID: Ki
    QLabel *kiLabel = new QLabel("Ki:", cylinderWindow);
    kiLabel->setGeometry(550, 440, 100, 30);
    kiInput = new QLineEdit(cylinderWindow);
    kiInput->setGeometry(650, 440, 100, 30);
    kiInput->setStyleSheet("border: 1px solid black;");
    // Parametros PID Kp.
    QLabel *kdLabel = new QLabel("Kd:", cylinderWindow);
    kdLabel->setGeometry(550, 480, 100, 30);
    kdInput = new QLineEdit(cylinderWindow);
    kdInput->setGeometry(650, 480, 100, 30);
    kdInput->setStyleSheet("border: 1px solid black;");
    // Gráfica control estanque
    QLabel *graficaTitulo = new QLabel("Gráfica control estanque", cylinderWindow);
    graficaTitulo->setGeometry(135, 60, 400, 30);
    graficaTitulo->setFont(serifFontParam);
    // Grafica de nivel
    chart1 = new QChart();
    series1 = new QLineSeries();
    chart1->addSeries(series1);
    chart1->legend()->hide();
    QValueAxis *axisX1 = new QValueAxis();
    axisX1->setTitleText("Tiempo (s)");
    chart1->addAxis(axisX1, Qt::AlignBottom);
    series1->attachAxis(axisX1);
    QValueAxis *axisY1 = new QValueAxis();
    axisY1->setTitleText("Nivel (m)");
    chart1->addAxis(axisY1, Qt::AlignLeft);
    series1->attachAxis(axisY1);
    chartView1 = new QChartView(chart1, cylinderWindow);
    chartView1->setGeometry(0, 100, 500, 280);
    chartView1->setRenderHint(QPainter::Antialiasing);
    // Grafica de volumen
    chart2 = new QChart();
    series2 = new QLineSeries();
    chart2->addSeries(series2);
    chart2->legend()->hide();
    QValueAxis *axisX2 = new QValueAxis();
    axisX2->setTitleText("Tiempo (s)");
    chart2->addAxis(axisX2, Qt::AlignBottom);
    series2->attachAxis(axisX2);
    QValueAxis *axisY2 = new QValueAxis();
    axisY2->setTitleText("Volumen (m3)");
    chart2->addAxis(axisY2, Qt::AlignLeft);
    series2->attachAxis(axisY2);
    chartView2 = new QChartView(chart2, cylinderWindow);
    chartView2->setGeometry(0, 360, 500, 280);
    chartView2->setRenderHint(QPainter::Antialiasing);
    // Botón Graficar
    QPushButton *graficarButton = new QPushButton("Graficar", cylinderWindow);
    graficarButton->setGeometry(600, 530, 100, 30);
    graficarButton->setStyleSheet("background-color: white; color: black; border: 2px solid black; border-radius: 5px;");
    graficarButton->installEventFilter(this);
    connect(graficarButton, &QPushButton::clicked, this, &MainWindow::handleGraficarButtonClickCylinder);
    // Show()
    cylinderWindow->show();
}
// Ventana Prisma Rectangular
void MainWindow::openPrismWindow() {
    // Crear una nueva ventana para la forma del prisma rectangular
    QWidget *prismWindow = new QWidget();
    prismWindow->setWindowTitle("Prisma Rectangular");
    prismWindow->setFixedSize(800, 640); // Dimensiones 800x600
    prismWindow->setStyleSheet("background-color: white; color: black;");
    // Título de la ventana del Prisma Rectangular
    QLabel *tituloPrisma = new QLabel("Control PID para estanque Prisma Rectangular", prismWindow);
    tituloPrisma->setGeometry(0, 10, 800, 30);
    tituloPrisma->setAlignment(Qt::AlignCenter);
    QFont serifFont("Times", 16, QFont::Bold);
    tituloPrisma->setFont(serifFont);
    // Parámetros
    QLabel *parametrosTitulo = new QLabel("Parámetros", prismWindow);
    parametrosTitulo->setGeometry(550, 60, 200, 30);
    QFont serifFontParam("Times", 14, QFont::Bold);
    parametrosTitulo->setFont(serifFontParam);
    // Parametros: Altura
    QLabel *alturaLabel = new QLabel("Altura:", prismWindow);
    alturaLabel->setGeometry(550, 100, 100, 30);
    alturaInput = new QLineEdit(prismWindow);
    alturaInput->setGeometry(650, 100, 100, 30);
    alturaInput->setStyleSheet("border: 1px solid black;");
    // Parametros: Largo
    QLabel *largoLabel = new QLabel("Largo:", prismWindow);
    largoLabel->setGeometry(550, 140, 100, 30);
    largoInput = new QLineEdit(prismWindow);
    largoInput->setGeometry(650, 140, 100, 30);
    largoInput->setStyleSheet("border: 1px solid black;");
    // Parametros: Ancho
    QLabel *anchoLabel = new QLabel("Ancho:", prismWindow);
    anchoLabel->setGeometry(550, 180, 100, 30);
    anchoInput = new QLineEdit(prismWindow);
    anchoInput->setGeometry(650, 180, 100, 30);
    anchoInput->setStyleSheet("border: 1px solid black;");
    // Parametros: Caudal
    QLabel *caudalLabel = new QLabel("Caudal:", prismWindow);
    caudalLabel->setGeometry(550, 220, 100, 30);
    caudalInput = new QLineEdit(prismWindow);
    caudalInput->setGeometry(650, 220, 100, 30);
    caudalInput->setStyleSheet("border: 1px solid black;");
    // Set Points
    QLabel *setPointsTitulo = new QLabel("Set Points", prismWindow);
    setPointsTitulo->setGeometry(550, 270, 200, 30);
    setPointsTitulo->setFont(serifFontParam);
    // Set Point: Llenado
    QLabel *llenadoLabel = new QLabel("Porcentaje llenado:", prismWindow);
    llenadoLabel->setGeometry(550, 310, 150, 30);
    llenadoInput = new QLineEdit(prismWindow);
    llenadoInput->setGeometry(700, 310, 50, 30);
    llenadoInput->setStyleSheet("border: 1px solid black;");
    // Set Point: Vaciado
    QLabel *vaciadoLabel = new QLabel("Porcentaje vaciado:", prismWindow);
    vaciadoLabel->setGeometry(550, 350, 150, 30);
    vaciadoInput = new QLineEdit(prismWindow);
    vaciadoInput->setGeometry(700, 350, 50, 30);
    vaciadoInput->setStyleSheet("border: 1px solid black;");
    // Coeficientes PID
    QLabel *pidTitulo = new QLabel("Parámetros PID", prismWindow);
    pidTitulo->setGeometry(550, 400, 200, 30);
    pidTitulo->setFont(serifFontParam);
    // Coeficientes PID: Kp
    QLabel *kpLabel = new QLabel("Kp:", prismWindow);
    kpLabel->setGeometry(550, 440, 100, 30);
    kpInput = new QLineEdit(prismWindow);
    kpInput->setGeometry(650, 440, 100, 30);
    kpInput->setStyleSheet("border: 1px solid black;");
    // Coeficientes PID: Ki
    QLabel *kiLabel = new QLabel("Ki:", prismWindow);
    kiLabel->setGeometry(550, 480, 100, 30);
    kiInput = new QLineEdit(prismWindow);
    kiInput->setGeometry(650, 480, 100, 30);
    kiInput->setStyleSheet("border: 1px solid black;");
    // Coeficientes PID: Kd
    QLabel *kdLabel = new QLabel("Kd:", prismWindow);
    kdLabel->setGeometry(550, 520, 100, 30);
    kdInput = new QLineEdit(prismWindow);
    kdInput->setGeometry(650, 520, 100, 30);
    kdInput->setStyleSheet("border: 1px solid black;");
    // Gráfica control estanque
    QLabel *graficaTitulo = new QLabel("Gráfica control estanque", prismWindow);
    graficaTitulo->setGeometry(135, 60, 400, 30);
    graficaTitulo->setFont(serifFontParam);
    // Grafica de Nivel
    chart1 = new QChart();
    series1 = new QLineSeries();
    chart1->addSeries(series1);
    chart1->legend()->hide();
    QValueAxis *axisX1 = new QValueAxis();
    axisX1->setTitleText("Tiempo (s)");
    chart1->addAxis(axisX1, Qt::AlignBottom);
    series1->attachAxis(axisX1);
    QValueAxis *axisY1 = new QValueAxis();
    axisY1->setTitleText("Nivel (m)");
    chart1->addAxis(axisY1, Qt::AlignLeft);
    series1->attachAxis(axisY1);
    chartView1 = new QChartView(chart1, prismWindow);
    chartView1->setGeometry(0, 100, 500, 280);
    chartView1->setRenderHint(QPainter::Antialiasing);
    // Grafica de volumen
    chart2 = new QChart();
    series2 = new QLineSeries();
    chart2->addSeries(series2);
    chart2->legend()->hide();

    QValueAxis *axisX2 = new QValueAxis();
    axisX2->setTitleText("Tiempo (s)");
    chart2->addAxis(axisX2, Qt::AlignBottom);
    series2->attachAxis(axisX2);

    QValueAxis *axisY2 = new QValueAxis();
    axisY2->setTitleText("Volumen (m3)");
    chart2->addAxis(axisY2, Qt::AlignLeft);
    series2->attachAxis(axisY2);

    chartView2 = new QChartView(chart2, prismWindow);
    chartView2->setGeometry(0, 360, 500, 280);
    chartView2->setRenderHint(QPainter::Antialiasing);
    // Botón Graficar
    QPushButton *graficarButton = new QPushButton("Graficar", prismWindow);
    graficarButton->setGeometry(600, 570, 100, 30);
    graficarButton->setStyleSheet("background-color: white; color: black; border: 2px solid black; border-radius: 5px;");
    graficarButton->installEventFilter(this);
    connect(graficarButton, &QPushButton::clicked, this, &MainWindow::handleGraficarButtonClickPrism);
    // Show()
    prismWindow->show();
}

// ----------------------------- PRISMA SETEO PARAMETROS PARA GRAFICA ----------------------------- //

// Escritura a parametros de Prisma
void MainWindow::handleGraficarButtonClickPrism() {
    // Instanciamiento del objeto
    Tanque* estanque = new Prisma(0, 0, 0);
    // Obtención de los parametros a partir de los cuadros de texto
    altura = alturaInput->text().toDouble();
    largo = largoInput->text().toDouble();
    ancho = anchoInput->text().toDouble();
    caudal = caudalInput->text().toDouble();
    llenado = llenadoInput->text().toDouble();
    vaciado = vaciadoInput->text().toDouble();
    ki = kiInput->text().toDouble();
    kd = kdInput->text().toDouble();
    kp = kpInput->text().toDouble();
    // Seteo de parametros
    estanque->SetterPrametros(altura, largo, ancho);
    estanque->set_caudal(caudal);
    // Instanciamiento de PID
    PIDController* pid = new PIDController(kp, ki, kd); // Se instancia la clase PIDController
    // Inicialización de variables
    float nivel_actual = 0, altura_actual = 0, dt = 0.1, tiempo_total = 0;
    float volumen_llenado = estanque->get_volumen() * llenado / 100;
    float volumen_vaciado = estanque->get_volumen() * vaciado / 100;
    float tiempo_inicio = 3;
    // Creación de CSV
    ofstream proceso_data("prisma_data.csv");
    proceso_data << tiempo_total << "," << 0 << "," << 0 << "," << 0 << "," << 0 << "\n";
    // Inicio del proceso
    while (tiempo_total <= tiempo_inicio) {
        tiempo_total += dt;
        proceso_data << tiempo_total << "," << 0 << "," << 0 << "," << 0 << "," << 0 << "\n";
    }
    // Proceso de llenado
    while (nivel_actual <= volumen_llenado) {
        float ajuste_caudal = pid->calculate(volumen_llenado, nivel_actual, dt, estanque->get_caudal());
        nivel_actual += ajuste_caudal * dt;
        altura_actual = estanque->CalcularNivel(nivel_actual);
        tiempo_total += dt;
        if (tiempo_total > 1000) {
            proceso_data.close();
            QMessageBox::warning(prismWindow, "Advertencia", "El tiempo total ha superado los 1000 segundos. La creación del archivo CSV ha sido detenida. Por favor verifica los parámetros.");
            delete estanque;
            delete pid;
            return;
        }
        proceso_data << tiempo_total << "," << altura_actual << "," << estanque->CalcularNivel(estanque->get_volumen() * llenado / 100) << "," << nivel_actual << "," << volumen_llenado << "\n";
    }
    // Estado estacionario
    float tiempo_ss1 = tiempo_total + 2;
    while (tiempo_total <= tiempo_ss1) {
        tiempo_total += dt;
        proceso_data << tiempo_total << "," << altura_actual << "," << estanque->CalcularNivel(estanque->get_volumen() * llenado / 100) << "," << nivel_actual << "," << volumen_llenado << "\n";
    }
    // Proceso de vaciado
    nivel_actual = volumen_llenado;
    while (nivel_actual >= volumen_vaciado) {
        float ajuste_caudal = pid->calculate(volumen_vaciado, nivel_actual, dt, estanque->get_caudal());
        nivel_actual -= ajuste_caudal * dt;
        altura_actual = estanque->CalcularNivel(nivel_actual);
        tiempo_total += dt;
        if (tiempo_total > 1000) {
            proceso_data.close();
            QMessageBox::warning(prismWindow, "Advertencia", "El tiempo total ha superado los 1000 segundos. La creación del archivo CSV ha sido detenida. Por favor verifica los parámetros.");
            delete estanque;delete pid;
            return;
        }
        proceso_data << tiempo_total << "," << altura_actual << "," << estanque->CalcularNivel(estanque->get_volumen() * vaciado / 100) << "," << nivel_actual << "," << volumen_vaciado << "\n";
    }
    // Estado estacionario
    tiempo_ss1 = tiempo_total + 2;
    while (tiempo_total <= tiempo_ss1) {
        tiempo_total += dt;
        proceso_data << tiempo_total << "," << altura_actual << "," << estanque->CalcularNivel(estanque->get_volumen() * vaciado / 100) << "," << nivel_actual << "," << volumen_vaciado << "\n";
    }
    // Fin
    proceso_data.close();
    delete estanque; delete pid;
    // Cargar datos desde el archivo .csv
    QFile file("prisma_data.csv");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo");
        return;
    }
    // Crear series para las gráficas
    QLineSeries *seriesNivelActual = new QLineSeries();
    QLineSeries *seriesNivelDeseado = new QLineSeries();
    QLineSeries *seriesVolumenActual = new QLineSeries();
    QLineSeries *seriesVolumenDeseado = new QLineSeries();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() >= 5) {
            bool okX, okY, okY2, okY3, okY4;
            double x = fields[0].toDouble(&okX);
            double y = fields[1].toDouble(&okY);
            double y2 = fields[2].toDouble(&okY2);
            double y3 = fields[3].toDouble(&okY3);
            double y4 = fields[4].toDouble(&okY4);
            if (okX && okY && okY2 && okY3 && okY4) {
                seriesNivelActual->append(x, y);
                seriesNivelDeseado->append(x, y2);
                seriesVolumenActual->append(x, y3);
                seriesVolumenDeseado->append(x, y4);
            }
        }
    }
    file.close();
    // Configurar el primer grafico
    if (chart1 == nullptr) {
        chart1 = new QChart();
        chart1->setTitle("Nivel vs Tiempo");
        chartView1 = new QChartView(chart1, prismWindow);
        chartView1->setGeometry(0, 100, 500, 250);
        chartView1->setRenderHint(QPainter::Antialiasing);
    } else {
        chart1->removeAllSeries(); // Eliminar series anteriores
    }
    chart1->addSeries(seriesNivelActual);
    chart1->addSeries(seriesNivelDeseado);
    seriesNivelActual->setName("Nivel Actual");
    seriesNivelDeseado->setName("Nivel Deseado");
    // Configurar ejes de forma automatica
    chart1->createDefaultAxes();
    QValueAxis *axisX1 = qobject_cast<QValueAxis *>(chart1->axes(Qt::Horizontal).at(0));
    QValueAxis *axisY1 = qobject_cast<QValueAxis *>(chart1->axes(Qt::Vertical).at(0));
    // Ajustar el rango del eje Y para proporcionar un margen
    if (axisY1) {
        double minY = axisY1->min();
        double maxY = axisY1->max();
        double margin = (maxY - minY) * 0.1;
        axisY1->setRange(minY - margin, maxY + margin);
    }
    axisX1->setTitleText("Tiempo (s)");
    axisY1->setTitleText("Nivel (m)");
    chart1->legend()->show(); // Mostrar el legend para el primer grafico
    // Configurar el segundo grafico
    if (chart2 == nullptr) {
        chart2 = new QChart();
        chart2->setTitle("Volumen vs Tiempo");
        chartView2 = new QChartView(chart2, prismWindow);
        chartView2->setGeometry(0, 360, 500, 250);
        chartView2->setRenderHint(QPainter::Antialiasing);
    } else {
        chart2->removeAllSeries(); // Eliminar series anteriores
    }
    chart2->addSeries(seriesVolumenActual);
    chart2->addSeries(seriesVolumenDeseado);
    seriesVolumenActual->setName("Volumen Actual");
    seriesVolumenDeseado->setName("Volumen Deseado");
    // Configurar ejes de forma automática
    chart2->createDefaultAxes();
    QValueAxis *axisX2 = qobject_cast<QValueAxis *>(chart2->axes(Qt::Horizontal).at(0));
    QValueAxis *axisY2 = qobject_cast<QValueAxis *>(chart2->axes(Qt::Vertical).at(0));
    // Ajustar el rango del eje Y para proporcionar un margen
    if (axisY2) {
        double minY = axisY2->min();
        double maxY = axisY2->max();
        double margin = (maxY - minY) * 0.1;
        axisY2->setRange(minY - margin, maxY + margin);
    }
    axisX2->setTitleText("Tiempo (s)");
    axisY2->setTitleText("Volumen (m³)");
    chart2->legend()->show(); // Mostrar el legend para el segundo grafico
    // Mostrar las gráficas
    chartView1->show();
    chartView2->show();
}

// ----------------------------- Cilindro SETEO PARAMETROS PARA GRAFICA ----------------------------- //

// Escritura a parámetros de cilindro
void MainWindow::handleGraficarButtonClickCylinder() {
    // Instanciamiento del objeto
    Tanque* estanque = new Cilindro(0, 0);
    // Obtención de los parámetros a partir de los cuadros de texto
    altura = alturaInput->text().toDouble();
    radio = radioInput->text().toDouble();
    caudal = caudalInput->text().toDouble();
    llenado = llenadoInput->text().toDouble();
    vaciado = vaciadoInput->text().toDouble();
    kp = kpInput->text().toDouble();
    ki = kiInput->text().toDouble();
    kd = kdInput->text().toDouble();
    // Seteo de parámetros
    estanque->SetterPrametros(altura, radio, 0);
    estanque->set_caudal(caudal);
    // Instanciamiento de PID
    PIDController* pid = new PIDController(kp, ki, kd);
    // Inicialización de variables
    float nivel_actual = 0, altura_actual = 0, dt = 0.1, tiempo_total = 0;
    float volumen_llenado = estanque->get_volumen() * llenado / 100;
    float volumen_vaciado = estanque->get_volumen() * vaciado / 100;
    float tiempo_inicio = 3;
    // Creación de CSV
    ofstream proceso_data("cilindro_data.csv");
    proceso_data << tiempo_total << "," << 0 << "," << 0 << "," << 0 << "," << 0 << "\n";
    // Inicio del proceso
    while (tiempo_total <= tiempo_inicio) {
        tiempo_total += dt;
        proceso_data << tiempo_total << "," << 0 << "," << 0 << "," << 0 << "," << 0 << "\n";
    }
    // Proceso de llenado
    while (nivel_actual <= volumen_llenado) {
        float ajuste_caudal = pid->calculate(volumen_llenado, nivel_actual, dt, estanque->get_caudal());
        nivel_actual += ajuste_caudal * dt;
        altura_actual = estanque->CalcularNivel(nivel_actual);
        tiempo_total += dt;
        if (tiempo_total > 1000) {
            proceso_data.close();
            QMessageBox::warning(cylinderWindow, "Advertencia", "El tiempo total ha superado los 1000 segundos. La creación del archivo CSV ha sido detenida. Por favor verifica los parámetros.");
            delete estanque;
            delete pid;
            return;
        }
        proceso_data << tiempo_total << "," << altura_actual << "," << estanque->CalcularNivel(estanque->get_volumen() * llenado / 100) << "," << nivel_actual << "," << volumen_llenado << "\n";
    }
    // Estado estacionario
    float tiempo_ss1 = tiempo_total + 2;
    while (tiempo_total <= tiempo_ss1) {
        tiempo_total += dt;
        proceso_data << tiempo_total << "," << altura_actual << "," << estanque->CalcularNivel(estanque->get_volumen() * llenado / 100) << "," << nivel_actual << "," << volumen_llenado << "\n";
    }
    // Proceso de vaciado
    nivel_actual = volumen_llenado;
    while (nivel_actual >= volumen_vaciado) {
        float ajuste_caudal = pid->calculate(volumen_vaciado, nivel_actual, dt, estanque->get_caudal());
        nivel_actual -= ajuste_caudal * dt;
        altura_actual = estanque->CalcularNivel(nivel_actual);
        tiempo_total += dt;
        if (tiempo_total > 1000) {
            proceso_data.close();
            QMessageBox::warning(cylinderWindow, "Advertencia", "El tiempo total ha superado los 1000 segundos. La creación del archivo CSV ha sido detenida. Por favor verifica los parámetros.");
            delete estanque;
            delete pid;
            return;
        }
        proceso_data << tiempo_total << "," << altura_actual << "," << estanque->CalcularNivel(estanque->get_volumen() * vaciado / 100) << "," << nivel_actual << "," << volumen_vaciado << "\n";
    }
    // Estado estacionario
    tiempo_ss1 = tiempo_total + 2;
    while (tiempo_total <= tiempo_ss1) {
        tiempo_total += dt;
        proceso_data << tiempo_total << "," << altura_actual << "," << estanque->CalcularNivel(estanque->get_volumen() * vaciado / 100) << "," << nivel_actual << "," << volumen_vaciado << "\n";
    }
    // Fin
    proceso_data.close();
    delete estanque;delete pid;
    // Cargar datos desde el archivo .csv
    QFile file("cilindro_data.csv");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo");
        return;
    }
    // Crear series para las graficas
    QLineSeries *seriesNivelActual = new QLineSeries();
    QLineSeries *seriesNivelDeseado = new QLineSeries();
    QLineSeries *seriesVolumenActual = new QLineSeries();
    QLineSeries *seriesVolumenDeseado = new QLineSeries();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() >= 5) {
            bool okX, okY, okY2, okY3, okY4;
            double x = fields[0].toDouble(&okX);
            double y = fields[1].toDouble(&okY);
            double y2 = fields[2].toDouble(&okY2);
            double y3 = fields[3].toDouble(&okY3);
            double y4 = fields[4].toDouble(&okY4);
            if (okX && okY && okY2 && okY3 && okY4) {
                seriesNivelActual->append(x, y);
                seriesNivelDeseado->append(x, y2);
                seriesVolumenActual->append(x, y3);
                seriesVolumenDeseado->append(x, y4);
            }
        }
    }
    file.close();
    // Configurar el primer grafico
    if (chart1 == nullptr) {
        chart1 = new QChart();
        chart1->setTitle("Nivel vs Tiempo");
        chartView1 = new QChartView(chart1, cylinderWindow);
        chartView1->setGeometry(0, 100, 500, 250);
        chartView1->setRenderHint(QPainter::Antialiasing);
    } else {
        chart1->removeAllSeries(); // Eliminar series anteriores
    }
    chart1->addSeries(seriesNivelActual);
    chart1->addSeries(seriesNivelDeseado);
    seriesNivelActual->setName("Nivel Actual");
    seriesNivelDeseado->setName("Nivel Deseado");
    // Configurar ejes de forma automática
    chart1->createDefaultAxes();
    QValueAxis *axisX1 = qobject_cast<QValueAxis *>(chart1->axes(Qt::Horizontal).at(0));
    QValueAxis *axisY1 = qobject_cast<QValueAxis *>(chart1->axes(Qt::Vertical).at(0));
    // Ajustar el rango del eje Y para proporcionar un margen
    if (axisY1) {
        double minY = axisY1->min();
        double maxY = axisY1->max();
        double margin = (maxY - minY) * 0.1;
        axisY1->setRange(minY - margin, maxY + margin);
    }
    axisX1->setTitleText("Tiempo (s)");
    axisY1->setTitleText("Nivel (m)");
    chart1->legend()->show(); // Mostrar el legend para el primer grafico
    // Configurar el segundo grafico
    if (chart2 == nullptr) {
        chart2 = new QChart();
        chart2->setTitle("Volumen vs Tiempo");
        chartView2 = new QChartView(chart2, cylinderWindow);
        chartView2->setGeometry(0, 360, 500, 250);
        chartView2->setRenderHint(QPainter::Antialiasing);
    } else {
        chart2->removeAllSeries(); // Eliminar series anteriores
    }
    chart2->addSeries(seriesVolumenActual);
    chart2->addSeries(seriesVolumenDeseado);
    seriesVolumenActual->setName("Volumen Actual");
    seriesVolumenDeseado->setName("Volumen Deseado");
    // Configurar ejes de forma automática
    chart2->createDefaultAxes();
    QValueAxis *axisX2 = qobject_cast<QValueAxis *>(chart2->axes(Qt::Horizontal).at(0));
    QValueAxis *axisY2 = qobject_cast<QValueAxis *>(chart2->axes(Qt::Vertical).at(0));
    // Ajustar el rango del eje Y para proporcionar un margen
    if (axisY2) {
        double minY = axisY2->min();
        double maxY = axisY2->max();
        double margin = (maxY - minY) * 0.1;
        axisY2->setRange(minY - margin, maxY + margin);
    }
    axisX2->setTitleText("Tiempo (s)");
    axisY2->setTitleText("Volumen (m³)");
    chart2->legend()->show(); // Mostrar el legend para el segundo gráfico
    // Mostrar las gráficas
    chartView1->show();
    chartView2->show();
}
