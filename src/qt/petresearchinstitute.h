#ifndef PETRESEARCHINSTITUTE_H
#define PETRESEARCHINSTITUTE_H

#include "amount.h"

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include "petattrdialog.h"
#include "combatpowerdialog.h"
#include "petfeeddialog.h"
#include "howtoplaydialog.h"

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
#include "json/json_spirit_utils.h"
#include "json/json_spirit_value.h"
using namespace std;
using namespace boost;
using namespace boost::assign;
using namespace json_spirit;
#define __TEST_AMOUNT__

static const int confirms = 1;
#ifdef __TEST_AMOUNT__
static const CAmount firstAmount = 10;
static const CAmount eachFeedAmount = 1;
#else 
static const CAmount firstAmount = 100000;
static const CAmount eachFeedAmount = 10000;
#endif
static const set<string> xiaohuiAddress{"AbewbnvCn9M9Drz1Z4i9Vfr4nATDf7Wsr3"};
// TODO: should be 3300000
static const CAmount xiaohuiAmount = 3300000;


static const set<string> feedAddresses{ "AafiiGE9mtE7wT6N8oVTvNSnDJAJS3dMqq",
                                        "AND2ri13bpY2g1m8XkrwHpCB977D4TqRVw",
                                        "ANg4ww3464Si6QVCd2LzRAYvu69ZCzz7Wz",
                                        "Ac4UpCXkEYTRVUN4t2fD3UYh8TBz3w2Dsj",
                                        "AZFGo6CbhCSXPWyHfnbBMTaG4wrT5Q9tPx",
                                        "AXm5xYSeKbX12JnBT2QpMkkd11yQz7wBXt",
                                        "AM43rGjDZ6fP7ZJvZcFvtGVnaB52MTKXbz",
                                        "AanXYUBw3dvSd4EX2L3TVro56A1bFmG4xZ",
                                        "AQq5z6J1N4hoc9KCKBC6b9keEu8cFTXrbB",
                                        "ATKhArGh8AxCrMDzDkCCzU2PpYpGzsMegY",
                                        "AKRJLsSzj3Gz9CAXpt7pHyEh2YvGdxViQX",
                                        "AKuiytqn3VhAbYAzNbWyNxbRXTLSBB7mNT",
                                        "AMoGCKopSiwQDoXEFCqRfouVrn2KJjBXSr",
                                        "AbiRwBgW71KeWaHnPXRUL3vRDK81X1uDyv",
                                        "AexmHuQcnGn7PdY2xWxsfTApQAvoGWWjmg",
                                        "ANtXUQdDcA6oP24jpu3fMtsaCDDzDqrKyz",
                                        "ALuk7N4CQp8gAwjBDjCu531MYV591E58Cv",
                                        "AamiujKCndhrwzpZ9MZZmn6YdDDWXCm6bz",
                                        "AQchsrt2m7rwFjvjdsr6Fko6bhSfaikNTv",
                                        "AHiw2dXMABB3YWkp5jnPU67s2iksjpxs2W",
                                        "AX7Dzuym7yJNrosntcCmj9NRV7i5cpURAH",
                                        "AdmZ7mCLVCgaFzga2iCbzfqse6RakoBzbj",
                                        "Ae2VLGHcjeHHtc28j1kgAu9VaHuxVTGqT8",
                               };

static const int vaid_interval = 18 * 3600;
//默认代数为 99 未领养
extern int petBorn;
static int feedCount = 0;
static int zhanli = 0;
static int dengji = 0;
static int nextfeedtime = 0;


extern std::map<std::string, std::map<int, int>> petPropetyNumber;

extern std::map<std::string, int> petPropetyResult;

class WalletModel;
namespace Ui {
class PetResearchInstitute;
}

class PetResearchInstitute : public QWidget
{
    Q_OBJECT

public:
    PetAttrDialog *petAttrWidget;
    CombatPowerDialog* petPowerWidget;
    PetFeedDialog* petFeedWidget;
    HowToPlayDialog* petHowtoplay;

    explicit PetResearchInstitute(QWidget *parent = nullptr);
	void setWalletModel(WalletModel *walletModel);
    ~PetResearchInstitute();
private:
	
public slots:
		/** Switch to overview (home) page */
		void gotoPetAttr(bool flag);
		
		void gotoPetPower(bool flag);

		void gotoPetFeed(bool flag);
		
		void gotoPetPlay(bool flag);
		
		void setBalance(const CAmount& balance, const CAmount& unconfirmedBalance, const CAmount& immatureBalance,
                    const CAmount& watchOnlyBalance, const CAmount& watchUnconfBalance, const CAmount& watchImmatureBalance);
		void ListSendToBoss(const CWalletTx& wtx, const string& strAccount, int nMinDepth,
                    const set<string>& destAddresses, CAmount desAmount, Array& ret, vector<CTx4Pet>& ret4pet);
		void ListSendToSeed(const CWalletTx& wtx, const string& strAccount, int nMinDepth,
                    const set<string>& destAddresses, CAmount desAmount, Array& ret, vector<CTx4Pet>& ret4pet);
        void ListSendToXiaohui(const CWalletTx& wtx, const string& strAccount, int nMinDepth,
                    const set<string>& destAddresses, CAmount desAmount, Array& ret, vector<CTx4Pet>& ret4pet);

private:
    Ui::PetResearchInstitute *ui;
private:

// 设置Pet中心窗口的设计;
	void InitPetMainFrame(QWidget *pSubFrame);

	void InitPetMainLeftWidget(QWidget* pLeftWidget);
	
	WalletModel *walletModel;

	QWidget *leftPetWidget;

	QWidget *rightPetWidget;
	QPushButton* btnPower;
	QPushButton* btnAttr;
	void InitPetMainRightWidget(QWidget* pRightWidget);
	QStackedWidget *attrWidget;


	// 设置QPushButton的设置状态;
	void SetTabPushButtonSheet(QPushButton* pPushButton);
};

#endif // PETRESEARCHINSTITUTE_H
