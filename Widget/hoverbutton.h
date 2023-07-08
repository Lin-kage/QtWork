#ifndef HOVERBUTTON_H
#define HOVERBUTTON_H


#include <qpushbutton.h>

class HoverButton :
    public QPushButton
{
    Q_OBJECT

public:
    HoverButton(QWidget* parent = nullptr) : QPushButton(parent) { 
        this->setFlat(true); 
        this->setStyleSheet("background:transparent");
    }

signals:
    void leave();
signals:
    void enter();

protected:
    void leaveEvent(QEvent* e);
    void enterEvent(QEnterEvent* e);
};


#endif