#include "gamew.h"
#include "sqllib.h"
#include <QPixmap>
#include <QLabel>
#include<iostream>
#include<array>
#include<string>

using namespace std;
gameScreen::gameScreen(QMainWindow *parent)
    : QMainWindow(parent)
{
    l1 = new QLabel("",this);
    l1->setGeometry(QRect(QPoint(100, 350), QSize(100,100)));

    l2 = new QLabel("",this);
    l2->setGeometry(QRect(QPoint(200, 350), QSize(100,100)));

    l3 = new QLabel("",this);
    l3->setGeometry(QRect(QPoint(300, 350), QSize(100,100)));

    l4 = new QLabel("",this);
    l4->setGeometry(QRect(QPoint(150, 385), QSize(100,100)));

    l5 = new QLabel("",this);
    l5->setGeometry(QRect(QPoint(250, 385), QSize(100,100)));

    l6 = new QLabel("",this);
    l6->setGeometry(QRect(QPoint(350, 385), QSize(100,100)));

    //labela fotoğraf ekleme
    QPixmap pix("../main/Assets/grass.png");
    l1->setPixmap(pix.scaled(100,100));
    l2->setPixmap(pix.scaled(100,100));
    l3->setPixmap(pix.scaled(100,100));
    l4->setPixmap(pix.scaled(100,100));
    l5->setPixmap(pix.scaled(100,100));
    l6->setPixmap(pix.scaled(100,100));


}

gameScreen::~gameScreen()
{
}

