/**
 * @file hoverbutton.h
 * @brief Contains button widget
 * @author Joe chen <joechenrh@gmail.com>
 */

#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QLabel>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

class BaseWidget : public QLabel
{
    Q_OBJECT

    Q_PROPERTY(double fontPointSize READ fontSize WRITE setFontSize)

public:
    BaseWidget(QWidget *parent = nullptr);

    double fontSize() const;
    void setFont(const QFont &font);
    void setFontSize(double size);
    void zoomIn();
    void zoomOut();
    void setOpacity(double opacity);
    double opacity() const;
    void hide();
    void reveal();

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

private slots:
    void mousePressEvent(QMouseEvent *e);

signals:
    void hovered();
    void leaved();
    void rightClicked();
    void clicked();
    void midClicked();

private:
    QGraphicsOpacityEffect *m_opacity;
    double m_fontSize;
    QPropertyAnimation *m_animation;
    QPropertyAnimation *m_scaleAnimation;
};

#endif // BASEWIDGET_H
