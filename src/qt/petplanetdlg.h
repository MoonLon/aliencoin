#ifndef PETPLANETDLG_H
#define PETPLANETDLG_H
#include "amount.h"

#include "base58.h"
#include "core_io.h"
#include "rpcserver.h"
#include "init.h"
#include "net.h"
#include "netbase.h"
#include "timedata.h"
#include "util.h"
#include "utilmoneystr.h"
#include "wallet.h"
#include "walletdb.h"

#include <stdint.h>

#include <boost/assign/list_of.hpp>
#include <boost/assign/list_of.hpp>
#include "json/json_spirit_utils.h"
#include "json/json_spirit_value.h"

#include <set>
#include <vector>
#include <QWidget>
using namespace std;
using namespace boost;
using namespace boost::assign;
using namespace json_spirit;

static const set<string> planetAddr{"AP6ujp2pxsefXhczhKgyQVtgxYjfyjgZUz"};
class WalletModel;

namespace Ui {
class PetPlanetDlg;
}

class PetPlanetDlg : public QWidget
{
    Q_OBJECT

public:
    explicit PetPlanetDlg(QWidget *parent = nullptr);
    ~PetPlanetDlg();
	void setWalletModel(WalletModel *walletModel);
	struct PlanetGetInfo {
			CAmount totalResource;// 总资源;
			unsigned int uiNorPlanetCount;
			unsigned int uiSupperPlanetCount;
			unsigned int uiTopPlanetCount;
			double dTotalInCome; // 总收益;
			double dTotalFenhong; // 分红;
			bool IsAbleBuyMore; // 超过10个矿星不让继续购买;
			int  uiPlanetLevel;
		};

private:
    Ui::PetPlanetDlg *ui;
	WalletModel *walletModel;
public slots:
	void clickupdatebtn();
	void clickgetplanetbtn();
	void updateBalance(const CAmount& balance, const CAmount& unconfirmedBalance, const CAmount& immatureBalance,
                    const CAmount& watchOnlyBalance, const CAmount& watchUnconfBalance, const CAmount& watchImmatureBalance);
signals:
	void updatePlanet(QString addr);
	void getPlanet(QString addr);
protected:
	void ListSendToPlanetAddr(const CWalletTx& wtx, const string& strAccount, int nMinDepth,
                    const set<string>& destAddresses, CAmount desAmount, Array& ret, vector<CTx4Pet>& ret4pet);
private:
	int GetUpdateSucCounts(vector<CTx4Pet>& planets);

	void GetPlanetInfos(vector<CTx4Pet>& planets,PlanetGetInfo& info);
	bool IsUpdateSucc(string strTxid);

	

	qint64 getPlanetOwnTime(int begintime);

	void UpdatePlanetClutrue(int lvl);
	void updateOwnerPlanetInfo(PlanetGetInfo& info);
};

#endif // PETPLANETDLG_H
