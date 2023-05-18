#include <QSqlDatabase>
#include <QLineEdit>
#include <QLabel>
#include "dataBaseWindow.h"
#include "sqllib.h"

DataBaseScreen::DataBaseScreen(QMainWindow *parent)
    : QMainWindow(parent)
{
    db = new QSqlDatabase();
    *db = connectDataBase();
    schemaBox = new QComboBox(this);
    updatecombo();


    newGameLabel = new QLabel("New Game",this);
    newGameLabel->setGeometry(QRect(QPoint(570, 70), QSize(200, 30)));

    nameEntery = new QLineEdit(this);
    nameEntery->setGeometry(QRect(QPoint(500, 100), QSize(200, 30)));
    nameEntery->setPlaceholderText("Game Name");


    gameLabel = new QLabel("Game Select",this);
    gameLabel->setGeometry(QRect(QPoint(170, 70), QSize(200, 30)));

    schemaBox->setCurrentIndex(0);
    schemaBox->setGeometry(QRect(QPoint(100, 100), QSize(200, 30)));

    gameSelectButton = new QPushButton("Start Game", this);
    gameSelectButton->setGeometry(QRect(QPoint(100, 280), QSize(200, 30)));
    connect(gameSelectButton, &QPushButton::released, this, &DataBaseScreen::GameSelectClicked);

    newGameButton = new QPushButton("Create New Game", this);
    newGameButton->setGeometry(QRect(QPoint(500, 140), QSize(200, 30)));
    connect(newGameButton, &QPushButton::released, this, &DataBaseScreen::newGameClicked);

}

void DataBaseScreen::GameSelectClicked(){
    QString schema = schemaBox->currentText();
    if(connectDataBaseSchema(schema)){
        this->close();
    }else{

    }
    qDebug() << schema;
}

void DataBaseScreen::newGameClicked(){
    QString schemaName=nameEntery->text();
    createSchema(schemaName);
    updatecombo();
}

void DataBaseScreen::updatecombo(){
    QString schemas[50];
    getSchemas(schemas);
    for(int i=0;i<50;i++){
        schemaBox->removeItem(i);
        if(schemas[i] != ""){
            schemaBox->insertItem(i,schemas[i]);
            qDebug() <<schemas[i];
        }
    }
}

DataBaseScreen::~DataBaseScreen()
{
}
