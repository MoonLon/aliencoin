#include "combatpowerdialog.h"
#include "ui_combatpowerdialog.h"

CombatPowerDialog::CombatPowerDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CombatPowerDialog)
{
    ui->setupUi(this);
}

CombatPowerDialog::~CombatPowerDialog()
{
    delete ui;
}

void CombatPowerDialog::setAttr(int zhanli)
{
    ui->label_zhanli->setText(QString::number(zhanli));
}
