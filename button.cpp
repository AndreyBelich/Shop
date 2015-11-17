#include "button.h"

Button::Button(QWidget *parent):QPushButton(parent)
{
    setFixedSize(250,250);
    setStyleSheet("Button{background-color:#C52756;color:#2AC5BD;font-size:18px;}");
}

void Button::enterEvent(QEvent *)
{
    setStyleSheet("Button{background-color:#C5A6A6;color:#C51340;font-size:18px;}");
}

void Button::leaveEvent(QEvent *)
{
     setStyleSheet("Button{background-color:#C52756;color:#2AC5BD;font-size:18px;}");
}
