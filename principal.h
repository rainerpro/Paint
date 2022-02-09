#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QImage>
#include <QPainter>
#include <QPaintEvent>
#include <QColorDialog>
#include <QInputDialog>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QtGui>
#include "acerca.h"
#define VERSION "1.0"
#define DEFAULT_ANCHO 2;

QT_BEGIN_NAMESPACE
namespace Ui { class principal; }
QT_END_NAMESPACE

class principal : public QMainWindow
{
    Q_OBJECT

public:
    principal(QWidget *parent = nullptr);
    ~principal();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void dibujarLineas();
    void lineaUnica();

private slots:
    void on_actionCOLOR_triggered();

    void on_actionANCHO_triggered();

    void on_actionGUARDAR_triggered();

    void on_actionLIBRE_triggered();

    void on_actionLINEAS_triggered();

    void on_actionRECTANGULOS_triggered();

    void on_actionCIRCUFERENCIA_triggered();

    void on_actionNUEVO_triggered();

    void on_actionSALIR_triggered();

    void on_actionRELLENO_triggered();

    void on_actionACERCA_DE_triggered();

private:
    Ui::principal *ui;
    QPen pincel;
    QColor m_Brush;
    QColor m_color; //Color de la linea
    int m_width; //Ancho de la linea
    int m_Orden;
    int m_numlineas; // numero
    int m_opcion; //Opcion de dibujo
    QImage *m_imagen; //Imagen sobre la cual se va a dibujar
    QPainter *m_painter; //El objeto painter
    QPoint m_ptInicial; //Punto inicial para dibujar
    QPoint m_ptFinal;   //Punto final para dibujar
    bool m_toogle = true;
};
#endif // PRINCIPAL_H
