#include "petattrdialog.h"
#include "ui_petattrdialog.h"
#include <stdint.h>

PetAttrDialog::PetAttrDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PetAttrDialog)
{
    ui->setupUi(this);
}

PetAttrDialog::~PetAttrDialog()
{
    delete ui;
}

void PetAttrDialog::setAttr(int liliang, int minjie, int zhili, int tongshuai,
                            int gedang , int baoji, int yidong , int tiaoju, int gongju, int shunfa,
                            int keji, int chaonengli, int tuanzhan, int juejin, int dengji
                            )
{	
	/*
    int unit = walletModel->getOptionsModel()->getDisplayUnit();
    currentBalance = balance;
    currentUnconfirmedBalance = unconfirmedBalance;
    currentImmatureBalance = immatureBalance;
    currentWatchOnlyBalance = watchOnlyBalance;
    currentWatchUnconfBalance = watchUnconfBalance;
    currentWatchImmatureBalance = watchImmatureBalance;
    ui->labelBalance->setText(AliencoinUnits::formatWithUnit(unit, balance, false, AliencoinUnits::separatorAlways));
    ui->labelUnconfirmed->setText(AliencoinUnits::formatWithUnit(unit, unconfirmedBalance, false, AliencoinUnits::separatorAlways));
    ui->labelImmature->setText(AliencoinUnits::formatWithUnit(unit, immatureBalance, false, AliencoinUnits::separatorAlways));
    ui->labelTotal->setText(AliencoinUnits::formatWithUnit(unit, balance + unconfirmedBalance + immatureBalance, false, AliencoinUnits::separatorAlways));
    ui->labelWatchAvailable->setText(AliencoinUnits::formatWithUnit(unit, watchOnlyBalance, false, AliencoinUnits::separatorAlways));
    ui->labelWatchPending->setText(AliencoinUnits::formatWithUnit(unit, watchUnconfBalance, false, AliencoinUnits::separatorAlways));
	*/
    ui->label_liliang->setText(QString::number(liliang));
    ui->label_minjie->setText(QString::number(minjie));
    ui->label_zhili->setText(QString::number(zhili));
    ui->label_tongshuai->setText(QString::number(tongshuai));
    ui->label_gedang->setText(QString::number(gedang));
    ui->label_baoji->setText(QString::number(baoji));
    ui->label_yidong->setText(QString::number(yidong));
    ui->label_tiaoju->setText(QString::number(tiaoju));
    ui->label_gongju->setText(QString::number(gongju));
    ui->label_shunfa->setText(QString::number(shunfa));
    ui->label_keji->setText(QString::number(keji));
    ui->label_chaonengli->setText(QString::number(chaonengli));
    ui->label_tuanzhan->setText(QString::number(tuanzhan));
    ui->label_juejin->setText(QString::number(juejin));

    ui->label_dengji->setText(QString::number(dengji));
	/*
    ui->labelWatchTotal->setText(AliencoinUnits::formatWithUnit(unit, watchOnlyBalance + watchUnconfBalance + watchImmatureBalance, false, AliencoinUnits::separatorAlways));

    // only show immature (newly mined) balance if it's non-zero, so as not to complicate things
    // for the non-mining users
    bool showImmature = immatureBalance != 0;
    bool showWatchOnlyImmature = watchImmatureBalance != 0;

    // for symmetry reasons also show immature label when the watch-only one is shown
    ui->labelImmature->setVisible(showImmature || showWatchOnlyImmature);
    ui->labelImmatureText->setVisible(showImmature || showWatchOnlyImmature);
    ui->labelWatchImmature->setVisible(showWatchOnlyImmature); // show watch-only immature balance
	*/
}
