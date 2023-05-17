#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

class ManagerScreen : public QMainWindow

{
    private:
        //id ve password girişleri için olan widgetlerin ön tanımlaması
        QLineEdit *startFoodEntery;
        QLabel *startFoodLabel;

        QLineEdit *startMoneyEntery;
        QLabel *startMoneyLabel;

        QLineEdit *startStuffEntery;
        QLabel *startStuffLabel;

        QLineEdit *dailyFoodExpenseEntery;
        QLabel *dailyFoodExpenseLabel;

        QLineEdit *dailyMoneyExpenseEntery;
        QLabel *dailyMoneyExpenseLabel;

        QLineEdit *dailyStuffExpenseEntery;
        QLabel *dailyStuffExpenseLabel;

        QLineEdit *gameStartDateEntery;
        QLabel *gameStartDateLabel;

        QLineEdit *gameSizeEntery;
        QLabel *gameSizeLabel;

        QLineEdit *placeOwnerFeeEntery;
        QLabel *placeOwnerFeeLabel;

        QLineEdit *fixedIncomeEntery;
        QLabel *fixedIncomeLabel;

        QLineEdit *fixedIncomeRateEntery;
        QLabel *fixedIncomeRateLabel;



        QPushButton *dataSetter;
        QLabel *picLabel;

        Q_OBJECT

    // Fonksiyon ön tanımlamaları slots bölümünde yapılıyor.
    private slots:
        void setData();

    public:
        ManagerScreen(QMainWindow *parent = nullptr);
        ~ManagerScreen();
};
