How to Use the Program

First of all, installing qt is required. To install qt on ubuntu, following terminal commands can be used:

sudo apt-get install build-essential 
sudo apt install -y qtcreator qtbase5-dev qt5-qmake cmake

To create Makefile, following command can be used:

qmake pairsGame.pro

Finally, to create executable, just use make command and executable will be created. After that executable can be run:

make
./pairsGame
