#include "manager.h"

Manager::Manager(){
    QGridLayout *row1 = new QGridLayout;
    QLabel *label1 = new QLabel("Score");
    labelScore = new QLabel();
    QLabel *label3 = new QLabel("No. of Tries\n Remaining");
    labelNofTries = new QLabel();
    QPushButton *newGameButton = new QPushButton("New Game");
    QObject::connect(newGameButton, SIGNAL(clicked()), this, SLOT(startNewGame()));

    row1->addWidget(label1,0,0,1,1);
    row1->addWidget(labelScore,0,1,1,1);
    row1->addWidget(label3,0,2,1,1);
    row1->addWidget(labelNofTries,0,3,1,1);
    row1->addWidget(newGameButton,0,4,1,2);

    this->addLayout(row1);
    QSpacerItem *si = new QSpacerItem(0, 30);
    this->addSpacerItem(si);
    buttons = new QGridLayout();
    startNewGame();
    this->addLayout(buttons);
}

void Manager::startNewGame(){
    firstCardSelected = false;
    busy = false;
    score = 0;
    nofTries = 50;
    labelScore->setText(QString::number(score));
    labelNofTries->setText(QString::number(nofTries));

    QString arr[] = {"lion", "lion", "tiger", "tiger", "elephant", "elephant",
                     "giraffe", "giraffe", "zebra", "zebra", "monkey", "monkey",
                     "bear", "bear", "kangaroo", "kangaroo", "penguin", "penguin",
                     "snake", "snake", "hippo", "hippo", "crocodile", "crocodile",
                     "koala", "koala", "panda", "panda", "wolf", "wolf"};

    // Shuffling the array
    int size = sizeof(arr) / sizeof(arr[0]);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(arr, arr + size, gen);

    // first initilazition of buttons
    if(buttons->count() == 0){
        for(int row=0; row<5; row++){
            for(int col=0; col<6; col++){
                CardButton *randButton = new CardButton(arr[row*6+col],this);
                buttons->addWidget(randButton, row, col, 1, 1);
            }
        }
    }
    // replacing of buttons (when new game button is pressed)
    else{
        for(int i = 0; i < buttons->count(); ++i){
           QWidget *widget = qobject_cast<QWidget*>(buttons->itemAt(i)->widget());
           CardButton *randButton = new CardButton(arr[i],this);
           buttons->replaceWidget(widget, randButton);
           widget->hide();
        }
    }
}

void Manager::selected(CardButton* cardButton){
    if((!cardButton->isFound())&&(cardButton->isHidden())&&!busy){
        if(!firstCardSelected){
            cardButton->showCard();
            firstCardSelected = true;
            firstCard = cardButton;
        }
        else{
            firstCardSelected = false;
            cardButton->showCard();
            busy = true;

            // 1 second delay without freezing screen
            QTime dieTime= QTime::currentTime().addSecs(1);
            while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

            // pairs are matched
            if(!cardButton->getWord().compare(firstCard->getWord())){
                score++;
                labelScore->setText(QString::number(score));
                cardButton->cardFound();
                buttons->replaceWidget(cardButton, new QLabel());
                firstCard->cardFound();
                buttons->replaceWidget(firstCard, new QLabel());
                if(score >= 15){
                    // won
                    showMessageBox("You Won!");
                    return;
                }
            }
            // not matched
            else{
                nofTries--;
                labelNofTries->setText(QString::number(nofTries));
                cardButton->hideCard();
                firstCard->hideCard();
                if(nofTries <= 0){
                    // lost
                    showMessageBox("You Lost!");
                    return;
                }
            }
            busy = false;
        }
    }
}

void Manager::showMessageBox(QString message){
    QMessageBox msgBox;
    msgBox.setWindowTitle("Game Finished");
    msgBox.setText(message);
    QPushButton button;
    button.setText("New Game");
    msgBox.addButton(&button,QMessageBox::RejectRole);
    QObject::connect(&button, SIGNAL(clicked()), this, SLOT(startNewGame()));
    msgBox.exec();
}
