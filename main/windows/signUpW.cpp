#include "signUpW.h"
#include "sqllib.h"

SignUpScreen::SignUpScreen(QMainWindow *parent)
    : QMainWindow(parent)
{
    //giriş bölümlerinin tanımlanması
    IdEntery = new QLineEdit(this);
    PasswordEntery = new QLineEdit(this);
    PasswordControlEntery = new QLineEdit(this);
    //giriş bölümlerine konum ve boyut atanması
    IdEntery->setGeometry(QRect(QPoint(150, 100), QSize(200, 30)));
    PasswordEntery->setGeometry(QRect(QPoint(150, 140), QSize(200, 30)));
    PasswordControlEntery->setGeometry(QRect(QPoint(150, 180), QSize(200, 30)));
    // giriş bölmelerine yer tutucu eklenmesi (hiçbir giriş yokken kullanıcıya nereye ne gireceği hakkında bilgi verir)
    IdEntery->setPlaceholderText("Id Entery");
    PasswordEntery->setPlaceholderText("Password Entery");
    PasswordControlEntery->setPlaceholderText("Password Control Entery");
    IdEntery->setFocus();

    signUpButton = new QPushButton("Singup", this);
    // butonlar için boyut ve konum atamaları yapılması
    signUpButton->setGeometry(QRect(QPoint(50, 220), QSize(300, 30)));

    // Connect button sinyalinin fonksiyonlara bağlanması
    connect(signUpButton, &QPushButton::released, this, &SignUpScreen::signUpClicked);

    picLabel= new QLabel("",this);
    picLabel->setGeometry(QRect(QPoint(50, 91), QSize(90, 90)));

    //label resim ekleme
    QPixmap pic("C:/Users/Pc_1/Desktop/prj's/prj_2/user.jpg");
    picLabel->setPixmap(pic);
    int * list = getEliminated();
    for(int i = 0;i<10;i++){
        qDebug() << list[i];
    }
    delEliminated();
    list = getEliminated();
    for(int i = 0;i<10;i++){
        qDebug() << list[i];
    }
}
void SignUpScreen::signUpClicked()
{
    //datalar alınır
    QString name=IdEntery->text();
    QString password=PasswordEntery->text();
    QString passwordControl=PasswordControlEntery->text();
    QMessageBox msgBox;
    //uygunluk durumu kontrol edilir
    if(name == ""){
        msgBox.setText("ID Bölümü Boş Geçilemez!");
        msgBox.exec();
    }else if(password == ""){
        msgBox.setText("Password Bölümü Boş Geçilemez!");
        msgBox.exec();
    }else if(passwordControl == ""){
        msgBox.setText("Password Kontrol Bölümü Boş Geçilemez!");
        msgBox.exec();
    }else if(passwordControl != password){
        msgBox.setText("Password Ve Password Kontrol Uyuşmuyor!");
        msgBox.exec();
    //uygun ise
    }else{
        // kayıt işlemi yapılmalıdır
        if(signUp(name,password)){
            //eğer kayıt işlemi başarılı ise
            msgBox.setText("Kayıt Başarılı!");
            msgBox.exec();
        }
    }
}

SignUpScreen::~SignUpScreen()
{
}
