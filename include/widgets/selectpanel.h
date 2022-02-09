/**
 * @file selectpanel.h
 * @brief Contains select panel widget for choose number
 * @author Joe chen <joechenrh@gmail.com>
 */

#ifndef SELECTPANEL_H
#define SELECTPANEL_H

#include "basewidget.h"

#include <QVector>
#include <QLabel>
#include <QList>
#include <QJsonObject>

class PanelBase : public QLabel
{
    Q_OBJECT

public:
    PanelBase(int size, QWidget *parent = nullptr);
    void setColor(QString color);
protected:
    void paintEvent(QPaintEvent *event);
private:
    QColor m_color;
    int m_size;
};

class SelectPanel : public QFrame
{
    Q_OBJECT

public:
    SelectPanel(int size = 75, QWidget *parent = nullptr);

    void setColorStyle(QJsonObject json);
    bool show(int x, int y);
    bool hide();
    bool canHide();
    bool isVisible() const;
    void setSelected(int value);

    int m_selected;

private:

    QPropertyAnimation *m_showAnimation;
    QPropertyAnimation *m_hideAnimation;
    QVector<BaseWidget*> m_buttons;
    PanelBase *m_background;
    QWidget *m_container;

signals:
    void finish(int);
};

#endif // SELECTPANEL_H
