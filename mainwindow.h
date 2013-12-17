#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QObject>
#include <QString>
#include <QVariant>
#include <cstdlib>
#include <qglobal.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_pushButton_clicked();
    double curse(QVariant );
    double mbcalc(QVariant );
    void attMIcalc(QVariant );
    void defMIcalc(QVariant );
    int getDefAttacker(QVariant );
    int getDefDefender(QVariant );
    void PreBattleCalc();
    void itemDefEffectAttacker(QVariant );
    void itemDefEffectDefender(QVariant );
    void itemAttEffectAttacker(QVariant );
    void itemAttEffectDefender(QVariant );
    void itemHealthEffectAttacker(QVariant );
    void itemHealthEffectDefender(QVariant );
    void calcDef();
    void calcDmg();
    void calcHealth();
    void battle();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
