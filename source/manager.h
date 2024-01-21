#ifndef MANAGER_H
#define MANAGER_H

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <algorithm>
#include <random>
#include <QTime>
#include <QMessageBox>
#include <QEventLoop>
#include <QCoreApplication>
#include "cardbutton.h"

class Manager: public QVBoxLayout
{
    Q_OBJECT
private:
    int score, nofTries;
    bool firstCardSelected, busy;
    CardButton* firstCard;
    QLabel* labelScore, *labelNofTries;
    QGridLayout* buttons;
    void showMessageBox(QString);
public:
    Manager();
    void selected(CardButton*);
private slots:
    void startNewGame();
};

#endif // MANAGER_H
