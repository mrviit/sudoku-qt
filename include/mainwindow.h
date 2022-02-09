/**
 * @file mainwindow.h
 * @brief Contains mainwindow of the game
 * @author Joe chen <joechenrh@gmail.com>
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "basewidget.h"
#include "selectpanel.h"
#include "gridwidget.h"
#include "counter.h"

#include <QMainWindow>
#include <QPushButton>
#include <QStack>

/**
 * @brief The Op struct
 */
struct Op
{
    int row;
    int col;
    int before;
    int after;
    Op(int _row = 0, int _col = 0, int _before = 0, int _after = 0)
        : row(_row), col(_col), before(_before), after(_after) {}
};


namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void highlight(int num, int active);

private slots:
    void receiveResult(int selected);
    void solve();
    void loadRandomPuzzle();
    void undo();
    void redo();
    void clearAll();
private:
    Ui::MainWindow *ui;

    void smartAssistOn(int r, int c);
    void smartAssistOff(int r, int c);
    void clearGrid(int r, int c);
    void changeNumber(int r, int c, int previous, int selected);

    /*****************************/

    QVector<QVector<GridWidget*>> m_grids;
    QVector<Counter*> m_counters;
    SelectPanel *m_panel;
    QPushButton *m_undoButton;
    QPushButton *m_redoButton;

    /*****************************/

    int m_sr;
    int m_sc;
    bool m_switching;
    bool m_forcing;

    QVector<QVector<QSet<QPair<int, int>>>> m_controlRanges;
    QVector<QSet<QPair<int, int>>> m_numPositions;
    QStack<Op> m_undoOps;
    QStack<Op> m_redoOps;
};

#endif // MAINWINDOW_H
