#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QComboBox>
#include <QSqlDatabase>
#include "signUpW.h"
#include "gamew.h"
#include "./managerW.h"

class EnteryScreen : public QMainWindow

{
    private:
        //id ve password girişleri için olan widgetlerin ön tanımlaması
        QSqlDatabase *db;
        QLineEdit *nameEntery;
        QLineEdit *gameNameEntery;
        QComboBox *schemaBox;
        QPushButton *gameSelectButton;
        QPushButton *newGameButton;
        QLabel *newGameLabel;
        QLabel *gameLabel;
        ManagerScreen *managerScreen;
        QLineEdit *surnameEntery;
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
        bool signIn(QString managerPlayer);
        void signUpClicked();
        void gameSelectClicked(QString managerPlayer);
        void newGameClicked();
        void updatecombo();
        void dbConnect();

    public:
        EnteryScreen(QString managerPlayer,QMainWindow *parent = nullptr);
        ~EnteryScreen();
};

