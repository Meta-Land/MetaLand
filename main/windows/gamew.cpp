#include "gamew.h"
#include "sqllib.h"
#include <QPixmap>
#include <QLabel>
#include<iostream>
#include<array>
#include<string>
#include<QPushButton>
#include <QString>
#include <QApplication>
#include <QScreen>
#include <QMessageBox>

using namespace std;
QVector<QVector<QPushButton*>> list1;
int k=0;
int l=2;

gameScreen::gameScreen(QMainWindow *parent)
    : QMainWindow(parent)
{

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int heightS = screenGeometry.height();
    int widthS = screenGeometry.width();
    bool check=false;

    height=heightS;
    width=widthS;

    //boyutların atanması
    int row=5;
    int col =5;
    int y=0;
    int x=0;

    //satir sayisi çift ise
    if(row%2==0){
        y=(heightS/2)-(100*row/2);
    }
    //sutun sayisi çift ise
    if(col%2==0){
        x=(widthS/2)-(100*col/2*2);
    }
    //satir sayisi tek ise
    if(row%2!=0){
        y=(heightS/2)-(100*row/2)+50;
    }
    //sutun sayisi tek ise
    if(col%1==0){
        x=(widthS/2)-(100*col/2*2)+50;
    }

    int xTemp=x;
    QPixmap pix("../main/Assets/grass.png");
    QIcon ButtonIcon(pix);

    //2d vector oluşturulması
    for( auto i=0;i<row;i++)
    {
        QVector<QPushButton*> list2;
        QPushButton *a;

        for(auto j=0;j<col;j++)
        {
            QString stI=QString::number(i);
            QString stJ=QString::number(j);
            QString text=stI+stJ;
            a = new QPushButton(this);
            a->setGeometry(QRect(QPoint(x,y), QSize(100,100)));
            //butona resim eklenmesi
            a->setIcon(ButtonIcon);
            a->setIconSize(QSize(100,100));
            a->setText(text);
            //buton arka planını saydamlaştırma
            a->setStyleSheet("background-color: rgba(255, 255, 255, 0)");
            list2.push_back(a);
            x+=100;
        }
        list1.push_back(list2);
        //basılacak arsaların konumları için
        xTemp+=50;
        x=xTemp;
        y+=35;
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            //arsaya tıklandığında çalışacak fonksiyonun çağırılması
            connect (list1[i][j], & QPushButton :: clicked, this, [=] () -> void {
                showDetails();
                grassClicked(i,j);
            });
        }
    }
}


gameScreen::~gameScreen()
{
}

void gameScreen::showDetails()
{
    QMessageBox detailBox;

    detailBox.move(500,200);
    detailBox.setStyleSheet("QLabel{min-width: 400px;min-height: 400px;}");
    detailBox.setText("selam");
   // detailBox.addButton(market)
    market= new QPushButton;
    market->setGeometry(QRect(QPoint(100,100), QSize(70,70)));

    //market=detailBox.addButton(tr("Custom Button"), QMessageBox::NoRole);
    detailBox.exec();

}


void gameScreen::grassClicked(int x,int y)
{
    QPixmap market("../main/Assets/market.png");
    QIcon ButtonIcon(market);
    qDebug() << x;
    qDebug() << y;
    list1[x][y]->setIcon(ButtonIcon);
    list1[x][y]->setIconSize(QSize(50,50));
}


