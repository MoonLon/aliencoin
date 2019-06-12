#ifndef HOWTOPLAYDIALOG_H
#define HOWTOPLAYDIALOG_H

#include <set>
#include <QWidget>

using namespace std;

static const set<string> bossAddress{"AZrBpp4UymXF5dEa7u2kPbnEksnSXoioLi"};
namespace Ui {
class HowToPlayDialog;
}

class HowToPlayDialog : public QWidget
{
    Q_OBJECT

public:
    explicit HowToPlayDialog(QWidget *parent = nullptr);
    ~HowToPlayDialog();
	
public slots:
    void clickgetpetbtn();
signals:
    void getpetClicked(QString addr);

private:
    Ui::HowToPlayDialog *ui;
};

#endif // HOWTOPLAYDIALOG_H
