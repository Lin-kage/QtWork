
#include "widget.h"
#include "config.h"
#include <QApplication>
#include <ctime>
#include <cstdlib>
#include <QFont>
#include <QFontDatabase>
#include <QStringList>

int main(int argc, char *argv[])
{   
    QApplication a(argc, argv);
    Widget w;

    w.setWindowTitle(QString("Nile\'s Lengend of Sword"));
    w.setWindowIcon(QPixmap("picture/icon/title_icon.png"));

    qDebug() << QFontDatabase::addApplicationFont(QCoreApplication::applicationDirPath() + "/font/Mouse.otf");
    qDebug() << QFontDatabase::addApplicationFont(QCoreApplication::applicationDirPath() + "/font/ice_pixel-7.ttf");
    qDebug() << QFontDatabase::addApplicationFont(QCoreApplication::applicationDirPath() + "/font/BACKTO1982.TTF");
    qDebug() << QFontDatabase::addApplicationFont(QCoreApplication::applicationDirPath() + "/font/thirteen_pixel_fonts.ttf");

    QString Pixel_font = QFontDatabase::applicationFontFamilies(0).at(0);

    QApplication::setFont(QFont(Pixel_font));

    qDebug() << JumpNumber_Angel_Min << ' ' << JumpNumber_Angel_Max << '\n';

    srand(time(0));

    w.setFixedSize(1000, 600);

    w.show();
    return a.exec();
}
