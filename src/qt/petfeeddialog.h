#ifndef PETFEEDDIALOG_H
#define PETFEEDDIALOG_H

#include <QWidget>

namespace Ui {
class PetFeedDialog;
}

class PetFeedDialog : public QWidget
{
    Q_OBJECT

public:
    explicit PetFeedDialog(QWidget *parent = nullptr);
    ~PetFeedDialog();
public slots:
    void clickfeedbtn();
    void setAttr(QString strnextfeed);

signals:
    void feedClicked();
	
private:
    Ui::PetFeedDialog *ui;
};

#endif // PETFEEDDIALOG_H
