#include "principal.h"
#include "ui_principal.h"

principal::principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::principal)
{
    ui->setupUi(this);
    //Instancia de la imagen
    m_imagen = new QImage(this->size(), QImage::Format_ARGB32_Premultiplied);

    //Rellenar de blanco
    m_imagen->fill(Qt::white);

    //Instanciar el objeto painter
    m_painter = new QPainter(m_imagen);
    m_painter->setRenderHint(QPainter::Antialiasing);
    m_color = Qt::black;
    m_Orden=0;
    m_width = DEFAULT_ANCHO;
    m_numlineas=0;
    m_opcion = 1;
    m_Brush= Qt::transparent;
}

principal::~principal()
{
    delete ui;
    delete m_painter;
    delete m_imagen;
}

void principal::paintEvent(QPaintEvent *event)
{
    //Crear otro painter (local)
    QPainter painter(this);

    //Dibujar la imagen
    painter.drawImage(0,0, *m_imagen);

    //Aceptar el evento
    event->accept();
}

void principal::mousePressEvent(QMouseEvent *event)
{
    if(m_opcion == 1){
        m_ptInicial = event->pos();
    }else if (m_opcion == 2){
        if (m_toogle){
            m_ptInicial = event->pos();
        }else {
            m_ptFinal = event->pos();
            QPen pincel;
            pincel.setColor(m_color);
            pincel.setWidth(m_width);
            m_painter->setPen(pincel);
            m_painter->drawLine(m_ptInicial, m_ptFinal);
            //Redibujar la interfaz grafica
            update();
        }
    }else if(m_opcion == 3){
        if (m_toogle){
            m_ptInicial = event->pos();
        }else {
            m_ptFinal = event->pos();
            //Dibujar rectangulo
            int ancho = m_ptFinal.x() - m_ptInicial.y();
            int alto = m_ptFinal.y() - m_ptInicial.y();

            QPen pincel;
            pincel.setColor(m_color);
            pincel.setWidth(m_width);
            m_painter->setPen(pincel);
            m_painter->drawRect(m_ptInicial.x(), m_ptInicial.y(), ancho, alto);
            //Redibujar la interfaz grafica
            update();
        }
    }else if(m_opcion == 4){
        if (m_toogle){
            m_ptInicial = event->pos();
        }else {
            m_ptFinal = event->pos();
            //Dibujar rectangulo
            QPen pincel;
            pincel.setColor(m_color);
            pincel.setWidth(m_width);
            QRectF circulo(m_ptInicial, m_ptFinal);
            m_painter->setPen(pincel);
            m_painter->drawEllipse(circulo);
            //Redibujar la interfaz grafica
            update();
        }
    }
    m_toogle = !m_toogle;
}

void principal::mouseMoveEvent(QMouseEvent *event)
{
    if(m_opcion == 1){
        m_ptFinal = event->pos();
        QPen pincel;
        pincel.setColor(m_color);
        pincel.setBrush(m_Brush);
        pincel.setWidth(m_width);
        m_painter->setPen(pincel);
        m_painter->drawLine(m_ptInicial, m_ptFinal);
        m_painter->setBrush(m_Brush);
        m_ptInicial = m_ptFinal;
        if(m_Orden==1&&ui->actionLIBRE->isChecked()){
        dibujarLineas();
        m_ptInicial = m_ptFinal;
        }

    }
    update();
}

void principal::dibujarLineas()
{
    m_painter->drawLine(m_ptInicial, m_ptFinal);
    // Mostrar el número de líneas en la barra de estado
    ui->statusbar->showMessage("Número de líneas: " + QString::number(++m_numlineas));
    // Actualizar la interfaz
    update();
}

void principal::lineaUnica()
{
    m_painter->drawLine(m_ptInicial, m_ptFinal);
    // Mostrar el número de líneas en la barra de estado
    ui->statusbar->showMessage("Número de líneas: " + QString::number(++m_numlineas));
    // Actualizar la interfaz
    update();
}

void principal::on_actionCOLOR_triggered()
{
    m_color = QColorDialog::getColor(m_color,this,"Color del pincel");
}

void principal::on_actionANCHO_triggered()
{
    m_width = QInputDialog::getInt(this, "Ancho del pincel",
                                   "Inserte el ancho del pincel",
                                   1,1,10);
}

void principal::on_actionGUARDAR_triggered()
{
    //Crear un objeto QDir a partir del directorio del usuario
    QDir directorio = QDir::home();

    //Agregar al path absoluto del objeto un nombre por defecto del archivo
    QString pathArchivo = directorio.absolutePath();

    QString nombreArchivo = QFileDialog::getSaveFileName(
                this,"Guardar imagen",pathArchivo,"Imagenes (*.png)");
    if (!nombreArchivo.isEmpty()){
        if (m_imagen->save(nombreArchivo))
            QMessageBox::information(this,"Guardar imagen","Archivo guarado en: " + nombreArchivo);
        else
            QMessageBox::warning(this,"Guardar imagen","No se pudo guardar el archivo");
    }
}

void principal::on_actionLIBRE_triggered()
{
    m_opcion = 1;
}

void principal::on_actionLINEAS_triggered()
{
    m_opcion = 2;
    m_toogle = true;
}

void principal::on_actionRECTANGULOS_triggered()
{
    m_opcion = 3;
    ui->actionLIBRE->setChecked(false);
}

void principal::on_actionCIRCUFERENCIA_triggered()
{
    m_opcion = 4;
}

void principal::on_actionNUEVO_triggered()
{
    m_imagen->fill(Qt::white);
    m_color = Qt::black;
    m_opcion = 1;
    update();
}

void principal::on_actionSALIR_triggered()
{
    this->close();
}

void principal::on_actionRELLENO_triggered()
{
    m_Brush = QColorDialog::getColor(m_Brush,this,"Color de relleno")   ;
}

