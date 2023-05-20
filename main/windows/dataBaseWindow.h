#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QSqlDatabase>
#include "sqllib.h"
#include <QLabel>
#include "./managerW.h"

class DataBaseScreen : public QMainWindow

{
    private:
        Q_OBJECT
        QSqlDatabase *db;
        QLineEdit *nameEntery;
        QComboBox *schemaBox;
        QPushButton *gameSelectButton;
        QPushButton *newGameButton;
        QLabel *newGameLabel;
        QLabel *gameLabel;
        ManagerScreen *managerScreen;

    // Fonksiyon ön tanımlamaları slots bölümünde yapılıyor.
    private slots:
        void GameSelectClicked();
        void newGameClicked();
        void updatecombo();


    public:
        DataBaseScreen(QMainWindow *parent = nullptr);
        ~DataBaseScreen();
};
