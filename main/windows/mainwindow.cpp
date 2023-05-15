#include "mainwindow.h"
#include <chrono>
#include <ctime>
#include <QTime>
#include <QDate>
#include <QString>
#include <QApplication>
#include <QScreen>
#include "sqllib.h"

Screen::Screen(QMainWindow *parent)
    : QMainWindow(parent)
{

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    managerButton = new QPushButton("Manager", this);
    playerButton = new QPushButton("Player", this);
    // boyut ve konum atamaları yapılması
    int size_x = 200;
    int size_y = 50;
    int x = width/2-size_x*2.5/2;
    int y = height/2-size_y*2.5/2;
    managerButton->setGeometry(QRect(QPoint(x, y), QSize(size_x, size_y)));
    playerButton->setGeometry(QRect(QPoint(x+size_x*3/2, y), QSize(size_x, size_y)));

    // Connect button signal to appropriate slot
    connect(managerButton, &QPushButton::released, this, &Screen::manager_clicked);
    connect(playerButton, &QPushButton::released, this, &Screen::player_clicked);

    QDate cd = QDate::currentDate();
    QTime ct = QTime::currentTime();
    cd = cd.addDays(1);
    QString ct_s = ct.toString();
    QString cd_s = cd.toString();
    label = new QLabel(ct_s,this);
    label_2 = new QLabel(cd_s,this);
    label_2->move(100,0);

    AnalogClock clock;
    clock.show();

    /*getMoney(1);
    getFood(1);
    getStuff(1);
    setMoney(1,100);
    setFood(1,100);
    setStuff(1,100);
    getMoney(1);
    getFood(1);
    getStuff(1);
    */
}

void Screen::manager_clicked()
{
    //2. pencereye geçiş işleminin yapılaması
    secW = new EnteryScreen();
    secW->resize(1920,1080);
    secW->move(0, 0);
    secW->show();
    this->close();
}

void Screen::player_clicked()
{
    //2. pencereye geçiş işleminin yapılaması
    secW = new EnteryScreen();
    secW->resize(1920,1080);
    secW->move(0, 0);
    secW->show();
    this->close();
}

Screen::~Screen()
{
}


