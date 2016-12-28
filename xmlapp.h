#ifndef XMLAPP_H
#define XMLAPP_H

#include <QWidget>
#include "QStandardItemModel"
#include <QtXml/QDomElement>

namespace Ui {
class xmlApp;
}

class xmlApp : public QWidget
{
    Q_OBJECT

public:
    explicit xmlApp(QWidget *parent = 0);
    ~xmlApp();
    QStandardItemModel *model;


private slots:

    void on_PB_saveVector_clicked();

    void on_PB_deleteElement_clicked();

    void on_PB_addElement_clicked();

private:
    Ui::xmlApp *ui;
};

#endif // XMLAPP_H
