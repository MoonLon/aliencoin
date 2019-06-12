#ifndef PETATTRDIALOG_H
#define PETATTRDIALOG_H

#include <QWidget>

namespace Ui {
class PetAttrDialog;
}

class PetAttrDialog : public QWidget
{
    Q_OBJECT

public:
    explicit PetAttrDialog(QWidget *parent = nullptr);
    ~PetAttrDialog();
public slots:
    //    "liliang", "minjie", "zhili", "tongshuai",
    //    "gedang", "baoji", "yidong", "tiaoju", "gongju", "shunfa",
    //    "keji", "chaonengli", "tuanzhan" ,"juejin"

    void setAttr(int liliang, int minjie, int zhili, int tongshuai,
                 int gedang , int baoji, int yidong , int tiaoju, int gongju, int shunfa,
                 int keji, int chaonengli, int tuanzhan, int juejin, int dengji
                 );
private:
    Ui::PetAttrDialog *ui;
};

#endif // PETATTRDIALOG_H
