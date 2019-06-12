#include "petfeeddialog.h"
#include "ui_petfeeddialog.h"

PetFeedDialog::PetFeedDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PetFeedDialog)
{
    ui->setupUi(this);

	ui->btnfeed->setStyleSheet("QPushButton{border-image:url(:/images/feeddefault);}"
							   "QPushButton:hover{border-image:url(:/images/feedhover);}"
							   "QPushButton:checked{border-image:url(:/images/feedpressed);}"
							   "QPushButton:pressed{border-image:url(:/images/feedchecked);}");
	connect(ui->btnfeed, SIGNAL(clicked()), this, SLOT(clickfeedbtn()));
}

PetFeedDialog::~PetFeedDialog()
{
    delete ui;
}

void PetFeedDialog::clickfeedbtn()
{
    emit feedClicked();
}

void PetFeedDialog::setAttr(QString strnextfeed)
{
    ui->label_feedtime->setText(strnextfeed);
}
