#include "cardbutton.h"
#include "manager.h"

CardButton::CardButton(const QString& text, Manager* x_manager):
    QPushButton(text, 0)
{
    manager = x_manager;
    this->word = text;
    hideCard();
    found = false;
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(selected()));
}

void CardButton::hideCard(){
    hidden = true;
    this->setText("?");
}

void CardButton::showCard(){
    hidden = false;
    this->setText(this->word);
}

void CardButton::cardFound(){
    found = true;
    this->hide();
    this->setText("");
}

bool CardButton::isHidden(){
    return hidden;
}

bool CardButton::isFound(){
    return found;
}

QString CardButton::getWord(){
    return word;
}

// slot
void CardButton::selected(){
    manager->selected(this);
}
