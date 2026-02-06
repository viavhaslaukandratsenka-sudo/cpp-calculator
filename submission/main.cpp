#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

 QApplication::setStyle("Fusion");

    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));                 // фон главного окна
    darkPalette.setColor(QPalette::WindowText, Qt::white);                     // белый текст на фоне окна 
    darkPalette.setColor(QPalette::WindowText, Qt::white);                    // белый текст на фоне окна 
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));                // 
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));       //  фон кнопок
    darkPalette.setColor(QPalette::ButtonText, Qt::white);           // фон знач. кнопок
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    qApp->setPalette(darkPalette); 
    
    MainWindow w;
    w.show();
    return a.exec();
}
