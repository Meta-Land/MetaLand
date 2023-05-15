#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include "gamew.h"

class EnteryScreen : public QMainWindow

{
    private:
        //id ve password girişleri için olan widgetlerin ön tanımlaması
        QLineEdit *IdEntery;
        QLineEdit *PasswordEntery;
        QPushButton *signInButton;
        QPushButton *signUpButton;
        QLabel *picLabel;
        gameScreen *thirdS;

        Q_OBJECT

    // Fonksiyon ön tanımlamaları slots bölümünde yapılıyor.
    private slots:
        void signInClicked();
        void signUpClicked();

    public:
        EnteryScreen(QMainWindow *parent = nullptr);
        ~EnteryScreen();
};
