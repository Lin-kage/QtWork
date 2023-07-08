
#ifndef JUMPNUMBER_H
#define JUMPNUMBER_H

#include <QLabel>
#include <QTimer>
#include "config.h"

class JumpNumber : public QLabel
{
private:
    double _v_x, _v_y, _acc;
    int _num;

    QTimer *_timer;

private slots:
    void move_num() {
        this->move(this->x() + _v_x, this->y() + _v_y);
        _v_y += _acc;

        if (this->x() + 20 < 0 || this->x() > Main_Window_Width || this->y() > Main_Window_Height)
        {
            _timer->stop();
            _timer->deleteLater();
            this->deleteLater();
        }
    }

public:
    // direction为正朝右，为负朝左
    JumpNumber(QWidget *parent, int num, int x, int y, int direction = 1);

    JumpNumber(QWidget* parent, QString str, int x, int y, int direction = 1);

    virtual ~JumpNumber() { qDebug() << "Number Deleted\n";}
};

#endif // JUMPNUMBER_H
