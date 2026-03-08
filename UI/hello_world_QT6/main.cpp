#include <QMessageBox>
#include <QtWidgets>

/*Should have g++, cmake, qmake6, and qt6-base-dev (other qt6 installations should work)*/

/*
Shout out to this legend on the Linux forums: https://www.linux.org/threads/c-tutorial-create-qt-applications-without-qtcreator.18409/
who gives a really good step by step guide on how to write QT applications without the IDE bc for some reason not a lot of people address this
(or at least sources that I found, definitely could be a skill issue). I've taken their steps and make it even simpler but he provides a really
good starting point for developing the kind of UI applications we'll be depending on.
*/

/*
This is a super simple QT6 application that can be run as an example/smoke test of the dash system. To compile, run '$ qmake6 -project'
which will create a file 'hello_world_QT6.pro' This file needs to be edited by going below 'INCLUDEPATH += .' and pasting 'QT += widgets'.
Once this is done, run '$ qmake6 hello_world_QT6.pro' which will generate a Makefile. Run this with standard '$ make' which will produce an 
executable with the same name as the .pro file (which is named after the directory we are working in).
*/

int main(int argc, char* argv[]){ //I like pointer characters on the data type instead of the object, sue me
    QApplication a(argc, argv); //Starts instance of a QT Application - handles widget init and finalization: https://doc.qt.io/qt-6/qapplication.html
    QMessageBox msgBox; //creates the message box object that will be displayed
    msgBox.setText("Hello World"); //defines the text content of the message box
    msgBox.showFullScreen(); //Makes the message box launch as a fullscreen window by default
    return msgBox.exec(); //launches the message box that when closed, will cause the program to exit as well.
}


