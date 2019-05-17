#include "howtoplaydialog.h"
#include "ui_howtoplaydialog.h"

HowToPlayDialog::HowToPlayDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HowToPlayDialog)
{
    ui->setupUi(this);

	ui->btngetpet->setStyleSheet("QPushButton{border-image:url(:/images/getpetdefault);}"
						   "QPushButton:hover{border-image:url(:/images/getpethover);}"
						   "QPushButton:checked{border-image:url(:/images/getpetchecked);}"
						   "QPushButton:pressed{border-image:url(:/images/getpetpressed);}");
connect(ui->btngetpet, SIGNAL(clicked()), this, SLOT(clickgetpetbtn()));
}

HowToPlayDialog::~HowToPlayDialog()
{
    delete ui;
}

void HowToPlayDialog::clickgetpetbtn()
{
    QString addr = QString::fromStdString(*bossAddress.begin());
    emit getpetClicked(addr);
}
