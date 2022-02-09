/**
 * @file gridwidget.h
 * @brief Contains main component of sudoku
 * @author Joe chen <joechenrh@gmail.com>
 */

#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include "basewidget.h"
#include "gridmarker.h"

#include <QJsonObject>

class GridWidget : public QWidget
{
    Q_OBJECT

    struct GridWidgetStyle
    {
        QString border_radius[2];
        QString border_color[2];
        QString font_color[3];

        QString background_color_hovered;
        QString background_color_unhovered;
        QString background_shadow_color;
        QString spacing_color;
    };

public:
    explicit GridWidget(int row, int col, int size = 75, QWidget *parent = nullptr);
    void setColorStyle(QJsonObject json);
    void setEnabled(bool enabled);
    bool isEnabled() const;
    void setValue(int value);
    void setMultiValue(int value);
    int value() const;
    int multiValue() const;
    void enter();
    void leave();
    void showBackground();
    void hideBackground();
    void changeConflict(int num);
    void clearConflict();
    int m_multiValue;

protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);

private slots:
    void buttonClicked();
    void buttonRightClicked();

signals:
    void hovered();
    void leaved();
    void clicked();
    void rightClicked();

/******************************/

private:
    GridWidgetStyle m_style;

    void setButtonStyle(int entered);

    BaseWidget *m_button;
    QVector<QLabel*> m_multiGrids;
    QLabel *m_singleGrid;
    GridMarker *m_marker;
    QLabel *m_background;
    BaseWidget *m_foreground;
    QString m_backgroundStyle;

    int m_value;
    int m_numConflict;

    QString m_borderRadius;
    QString m_borderColor;
    QString m_fontColor;
    QString m_buttonStyle;
};

#endif // GRIDWIDGET_H
