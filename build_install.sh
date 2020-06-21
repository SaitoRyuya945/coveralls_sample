#!/bin/bash

sudo apt-get install llvm-9
sudo apt-get install ninja-build

sudo wget https://cpan.metacpan.org/authors/id/N/NW/NWCLARK/PerlIO-gzip-0.20.tar.gz
tar -zxvf PerlIO-gzip-0.20.tar.gz
cd PerlIO-gzip-0.20
perl Makefile.PL
make
sudo make install
cd 

sudo wget https://cpan.metacpan.org/authors/id/I/IS/ISHIGAKI/JSON-4.02.tar.gz
tar -zxvf JSON-4.02.tar.gz
cd JSON-4.02
perl Makefile.PL
make 
sudo make install
cd 

pwd
git clone https://github.com/linux-test-project/lcov.git ./lcov
cd lcov
sudo make install
cd 
sudo gem install lcoveralls
