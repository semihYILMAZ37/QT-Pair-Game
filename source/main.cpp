#include <QApplication>
#include "manager.h"

int main(int argc, char *argv[])
{
     QApplication app(argc, argv);
     QWidget *window = new QWidget;
     window->setWindowTitle("Card Match Game");

     Manager* manager = new Manager();
     window->setLayout(manager);
     window->show();

     return app.exec();
}
