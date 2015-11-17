#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class Button: public QPushButton
{
    Q_OBJECT
public:
    explicit Button(QWidget *parent = 0);
protected:
    virtual void enterEvent(QEvent *e);//событие наступающее когда курсор мыши наводится на любую часть виджета
    virtual void leaveEvent(QEvent *e);//событие наступающее когда курсор мыши выходит за пределы виджета
};

#endif // BUTTON_H
