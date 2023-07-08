#include "hoverbutton.h"

void HoverButton::leaveEvent(QEvent* e)
{
	qDebug() << "Left\n";

	emit leave();
}

void HoverButton::enterEvent(QEnterEvent* e)
{ 
	qDebug() << "Entered\n";

	emit enter();
}