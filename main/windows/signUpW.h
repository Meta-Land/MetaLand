#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

class SignUpScreen : public QMainWindow

{
    private:
        //id ve password girişleri için olan widgetlerin ön tanımlaması
        QLineEdit *nameEntery;
        QLineEdit *surnameEntery;
        QLineEdit *PasswordEntery;
        QLineEdit *PasswordControlEntery;
        QPushButton *signInButton;
        QPushButton *signUpButton;
        QPushButton *backButton;
        QLabel *picLabel;

        Q_OBJECT

    // Fonksiyon ön tanımlamaları slots bölümünde yapılıyor.
    private slots:
        void signUpClicked();

    public:
        SignUpScreen(QMainWindow *parent = nullptr);
        ~SignUpScreen();
};
