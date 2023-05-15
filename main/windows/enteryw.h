#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include "signUpW.h"
#include "gamew.h"

class EnteryScreen : public QMainWindow

{
    private:
        //id ve password girişleri için olan widgetlerin ön tanımlaması
        QLineEdit *IdEntery;
        QLineEdit *PasswordEntery;
        QPushButton *signInButton;
        QPushButton *signUpButton;
        QPushButton *backButton;
        QLabel *picLabel;
        SignUpScreen *secW;
        gameScreen* thirdS;

        Q_OBJECT

    // Fonksiyon ön tanımlamaları slots bölümünde yapılıyor.
    private slots:
        void signInClicked();
        void signUpClicked();

    public:
        EnteryScreen(QMainWindow *parent = nullptr);
        ~EnteryScreen();
};
