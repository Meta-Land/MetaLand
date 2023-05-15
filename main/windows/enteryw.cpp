#include "enteryw.h"
#include "sqllib.h"

EnteryScreen::EnteryScreen(QMainWindow *parent)
    : QMainWindow(parent)
{
    //giriş bölümlerinin tanımlanması
    IdEntery = new QLineEdit(this);
    PasswordEntery = new QLineEdit(this);
    //giriş bölümlerine konum ve boyut atanması
    IdEntery->setGeometry(QRect(QPoint(150, 100), QSize(200, 30)));
    PasswordEntery->setGeometry(QRect(QPoint(150, 140), QSize(200, 30)));
    // giriş bölmelerine yer tutucu eklenmesi (hiçbir giriş yokken kullanıcıya nereye ne gireceği hakkında bilgi verir)
    IdEntery->setPlaceholderText("Id Entery");
    PasswordEntery->setPlaceholderText("Password Entery");
    IdEntery->setFocus();

    signInButton = new QPushButton("Singin", this);
    signUpButton = new QPushButton("Singup", this);
    // butonlar için boyut ve konum atamaları yapılması
    signInButton->setGeometry(QRect(QPoint(50, 200), QSize(300, 30)));
    signUpButton->setGeometry(QRect(QPoint(50, 235), QSize(300, 30)));

    // Connect button sinyalinin fonksiyonlara bağlanması
    connect(signInButton, &QPushButton::released, this, &EnteryScreen::signInClicked);
    connect(signUpButton, &QPushButton::released, this, &EnteryScreen::signUpClicked);

    picLabel= new QLabel("",this);
    picLabel->setGeometry(QRect(QPoint(50, 91), QSize(90, 90)));

    //label resim ekleme
    QPixmap pic("C:/Users/Pc_1/Desktop/prj's/prj_2/user.jpg");
    picLabel->setPixmap(pic);
}

void EnteryScreen::signInClicked()
{
    //Kullanıcı giriş yapmak istemektedir ve datalar okunarak bir sonraki adıma ilerlenmelidir
    QString name=IdEntery->text();
    QString password=PasswordEntery->text();
    QMessageBox msgBox;
    if(name == ""){
        msgBox.setText("ID Bölümü Boş Geçilemez!");
        msgBox.exec();
    }else if(password == ""){
        msgBox.setText("Password Bölümü Boş Geçilemez!");
        msgBox.exec();
    }else{
        // verilen id ve password bulundu ise eşsiz datasını döndürür. bulunamadıysa -1
        int personNum = IdPasswordControl(name,password);
        if(personNum != -1){
            //id password bulunmuştur.
            qDebug() << "id password bulunmuştur.";
        }else{
            //id ve password bulunamamıştır.
            qDebug() << "id ve password bulunamamıştır.";
            msgBox.setText("ID Ve Password Bulunamamıştır.");
            msgBox.exec();
        }
    }
}

void EnteryScreen::signUpClicked()
{
    //kullanıcı kayıt olmak istemektedir yeni bir ekrana yönlendirilmelidir.
    secW = new SignUpScreen();
    secW->resize(1920,1080);
    secW->move(0, 0);
    secW->show();
    this->close();
}


EnteryScreen::~EnteryScreen()
{
}


