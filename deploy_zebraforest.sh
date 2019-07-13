#!/bin/bash
sudo apt-get install qt5-default
sudo apt-get install qt5-qmake
sudo apt-get install qtbase5-dev
qmake
make -j4
./ZebraForest
