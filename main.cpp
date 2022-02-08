#include "principal.h"

#include <QApplication>
#include <QTranslator>
#include <QInputDialog>
#include <QLocale>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLocale location;
    QString text = location.languageToString(location.language());
    qDebug()<<location.languageToString(location.language());
    // Objeto para manejar las traducciones
       QTranslator traducion;

       // Dependiendo del idioma seleccionado, carga el archivo de rtaducción
       if (text == "Japanese"){
           traducion.load(":/paint_japones.qm");
       }else if (text == "Portuguese"){
           traducion.load(":/paint_portuges.qm");
       }
       // Si es diferente de español, se instala la traducción en TODA la aplicación
       if (text != QLocale::Spanish){
           a.installTranslator(&traducion);
       }
    principal w;
    w.show();
    return a.exec();
}
