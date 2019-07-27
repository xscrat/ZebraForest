#!/bin/bash
sudo apt-get install qt5-default
sudo apt-get install qt5-qmake
sudo apt-get install qtbase5-dev
sudo apt-get install libqt5webkit5
sudo apt-get install libqt5webkit5-dev
sudo apt-get install libqt5websockets5
sudo apt-get install libqt5websockets5-dev
sudo apt-get install libqt5serialport5-dev
qmake
make -j4
./ZebraForest
