#!/bin/bash

apt-get download python3 python3.7 python3.7-minimal libpython3.7-minimal
sudo dpkg -i *python3*.deb
sudo apt install -f

apt-get download software-properties-common
sudo dpkg -i *software-properties-common*.deb
sudo apt install -f

apt-get remove --purge python2.7-minimal
sudo apt-get autoremove
