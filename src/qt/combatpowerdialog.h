#ifndef COMBATPOWERDIALOG_H
#define COMBATPOWERDIALOG_H

#include <QWidget>

namespace Ui {
class CombatPowerDialog;
}

class CombatPowerDialog : public QWidget
{
    Q_OBJECT

public:
    explicit CombatPowerDialog(QWidget *parent = nullptr);
    ~CombatPowerDialog();
public slots:
    void setAttr(int zhanli);

private:
    Ui::CombatPowerDialog *ui;
};

#endif // COMBATPOWERDIALOG_H
