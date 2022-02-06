#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class principal; }
QT_END_NAMESPACE

class principal : public QMainWindow
{
    Q_OBJECT

public:
    principal(QWidget *parent = nullptr);
    ~principal();

private:
    Ui::principal *ui;
};
#endif // PRINCIPAL_H
