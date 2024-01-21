#ifndef CARDBUTTON_H
#define CARDBUTTON_H

#include <QPushButton>
class Manager;

class CardButton : public QPushButton
{
    Q_OBJECT
private:
    Manager* manager;
    QString word;
    bool found, hidden;
public:
    CardButton(const QString& text, Manager* x_manager);
    bool isHidden();
    bool isFound();
    QString getWord();
    void hideCard();
    void showCard();
    void cardFound();
public slots:
    void selected();
};

#endif // CARDBUTTON_H
