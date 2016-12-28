#include "xmlapp.h"
#include "ui_xmlapp.h"
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QTextCodec>


xmlApp::xmlApp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::xmlApp)
{
    ui->setupUi(this);
    //Модель использую просто чтобы все было нагляднее
    model = new QStandardItemModel(this);//создаем модель для хранения в ней элементов будущего QVector
    model->insertColumn(0);//добавляем в нее одну колонку
    for (int i = 0; i<3;i++)
    {
        model->insertRow(i);//добавляем строку
        model->setData(model->index(i,0),QVariant(QString("SomeElement" + QString::number(i))));//вставляем начальные значения
    }
    ui->listView->setModel(model);//задаем для левой части программы соданную модель
}

xmlApp::~xmlApp()
{
    delete ui;
}

void xmlApp::on_PB_saveVector_clicked()//основной код
{
    QVector<QString> vector;//создаем контейнер


    for(int i = 0;i<model->rowCount();i++)
    {
        //здесь мы наполняем контейнер элементами из ListView на левой части формы
        vector.append(model->data(model->index(i,0)).toString());
    }



    QString fileName = QFileDialog::getSaveFileName(this, tr("Save project as"), QDir::currentPath(),
         tr("Program project (*.xml)"));//задаем имя сохраняемого файла путем вызова диалога сохраения файла
    //в результате имя файла это то что вы указали в диалоге

     if (fileName.isEmpty() == false)//проверка - пустое ли имя файла
     {
         if (fileName.endsWith(".xml", Qt::CaseInsensitive) == false)//проверка - не забыли ли вы указать расширение xml
             fileName += ".xml";//если забыли - программа сама допишет его за вас

         // размер отступа
         const int Indent = 4;
         //используется технология DOM
         QDomDocument doc;//создаем xml документ

         QDomElement mainElement = doc.createElement("MyProgram");//создаем главный тэг программы
         doc.appendChild(mainElement);//добавляем его в документ (appendChild значит, что он добавится как дочерний, то есть с отступом)
         QDomElement vectorName = doc.createElement(ui->lineEdit->text());//создаем тэг, обозначающий наш контейнер
         mainElement.appendChild(vectorName);//добавляем его внутрь главного тэга

         for(int i = 0;i<vector.size();i++)//от начала и до конца нашего контейнера
         {
             QDomElement vectorElement = doc.createElement("vectorElement" + QString::number(i));//создаем тэг с номером элемента контейнера
             vectorName.appendChild(vectorElement);//добавляем его внутрь тэга, обозначающего контейнер
             QDomText vectorElementText = doc.createTextNode(vector.at(i));//создаем текст со значением элемента
             vectorElement.appendChild(vectorElementText);//добавляем его внутрь тэга, обозначающего элемент
         }


         QDomNode xmlNode = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");//указываем версию и кодировку
         doc.insertBefore(xmlNode, doc.firstChild());//добавляем эту информацию в начало файла

         QFile file(fileName);//создаем файл
         file.open(QIODevice::WriteOnly);//открываем его в режиме - Только запись

         QTextStream out(&file);//создаем текстовый поток, в котором указываем наш файл
         out.setCodec(QTextCodec::codecForName("UTF-8"));//задаем его кодировку

         doc.save(out, 5, QDomNode::EncodingFromTextStream);//сохраняем поток в файл
     }
}


void xmlApp::on_PB_deleteElement_clicked()
{
    model->removeRow(ui->listView->currentIndex().row());//удаление выбранного элемента
}

void xmlApp::on_PB_addElement_clicked()
{
    model->insertRow(model->rowCount());//добавление строки в конец
    model->setData(model->index(model->rowCount()-1,0),QVariant(ui->LE_elementName->text()));//добавление элемента в ListView, значение указываем в LE_nameElement в правой части формы
}
