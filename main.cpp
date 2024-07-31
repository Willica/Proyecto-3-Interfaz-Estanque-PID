#include <QApplication>
#include "mainwindow.h"
int main(int argc, char *argv[]) { // Función principal que permite el bucle indefinido de ejecución
    QApplication app(argc, argv);
    MainWindow ventana;
    ventana.show();
    return app.exec(); // Se mantiene la ventana abierta hasta que se da en la X de la barra superior
}
