#include "petplanetdlg.h"
#include "ui_petplanetdlg.h"
#include "aliencoinunits.h"

#include "walletmodel.h"
#include "init.h"
#include "util.h"
#include "core_io.h"
#include "utilmoneystr.h"
#include <stdint.h>

#include "amount.h"
#include "base58.h"

#include "rpcserver.h"
#include "net.h"
#include "netbase.h"
#include "timedata.h"

#include "wallet.h"
#include "walletdb.h"
#include <QDateTime>

#include <boost/assign/list_of.hpp>
#include "json/json_spirit_utils.h"
#include "json/json_spirit_value.h"
#include "petresearchinstitute.h"
#include <QString> 

static const int planetconfirms = 0;
#ifdef __TEST_AMOUNT__
static const CAmount PlanetUpdteAmount = 1;
static const CAmount PlanetNormalAmount = 2;
static const CAmount PlanetSupperAmount = 3;
static const CAmount PlanetTopAmount = 5;
static const int 	updateLvl0 = 1;//35;
static const int 	updateLvl1 = 2;//70;
static const double IncomeCoinsPerYear = (0.1);
#else
static const CAmount PlanetUpdteAmount = 20000;
static const CAmount PlanetNormalAmount = 1000000;
static const CAmount PlanetSupperAmount = 10000000;
static const CAmount PlanetTopAmount =    100000000;
static const int 	updateLvl0 = 35;//35;
static const int 	updateLvl1 = 70;//70;
static const double IncomeCoinsPerYear = (0.00001);
#endif

static const double PlanetNormalValue = 0.1;
static const double PlanetSupperValue = 0.5;
static const double PlanetTopValue = 1;

static const int 	DaysPerYear = 365;




static const int onedaytimevalsec = (24*3600);

PetPlanetDlg::PetPlanetDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PetPlanetDlg)
{
    ui->setupUi(this);
	connect(ui->btnupdate, SIGNAL(clicked()), this, SLOT(clickupdatebtn()));
	connect(ui->btnbuyplanet, SIGNAL(clicked()), this, SLOT(clickgetplanetbtn()));
}

PetPlanetDlg::~PetPlanetDlg()
{
    delete ui;
}
void PetPlanetDlg::clickupdatebtn()
{
	QString addr = QString::fromStdString(*planetAddr.begin());

    emit updatePlanet(addr);
}

void PetPlanetDlg::clickgetplanetbtn()
{
	QString addr = QString::fromStdString(*planetAddr.begin());

    emit getPlanet(addr);
}

void PetPlanetDlg::setWalletModel(WalletModel *model)
{
    this->walletModel = model;
    if(model && model->getOptionsModel())
    {
        // Set up transaction list
		
        // Keep up to date with wallet

        updateBalance(model->getBalance(), model->getUnconfirmedBalance(), model->getImmatureBalance(),
                   model->getWatchBalance(), model->getWatchUnconfirmedBalance(), model->getWatchImmatureBalance());
		// 因为计算需要宠物的掘金值，所以在walletview中监听此信号;
 //       connect(model, SIGNAL(balanceChanged(CAmount,CAmount,CAmount,CAmount,CAmount,CAmount)), this, SLOT(updateBalance(CAmount,CAmount,CAmount,CAmount,CAmount,CAmount)));
		
    }

}
void PetPlanetDlg::UpdatePlanetClutrue(int lvl)
{
	//更新星球文明信息;
	int juejinValue = petPropetyResult["juejin"];
	QString strseedBonusValue = QString("%1%").arg(lvl);
	ui->labseedbonus->setText(strseedBonusValue);
	
	ui->labwmlvl->setText(QString::number(lvl));
	double djuejinValue = (double)(juejinValue) * (1+ 0.01*lvl);
	ui->labseedvalue->setText(QString::number(djuejinValue));

	if (lvl >=0 && lvl <= updateLvl0){
		ui->lablvlimage->setStyleSheet(QLatin1String("background-image: url();\n"
			"border-image: url(:/images/planetlvl0);"));
	} else if(lvl > updateLvl0 && lvl <= updateLvl1) {
		ui->lablvlimage->setStyleSheet(QLatin1String("background-image: url();\n"
			"border-image: url(:/images/planetlvl1);"));
	} else {
		ui->lablvlimage->setStyleSheet(QLatin1String("background-image: url();\n"
			"border-image: url(:/images/planetlvl2);"));
	}
}
void PetPlanetDlg::updateOwnerPlanetInfo(PlanetGetInfo& info)
{
	//更新已经拥有的星球信息;
	// 标准星球个数
	QString strStandard = QString("标准矿星(%1)").arg(info.uiNorPlanetCount);
	ui->labstandNum->setText(strStandard);
	// 超级星球个数
	QString strSupper = QString("超级矿星(%1)").arg(info.uiSupperPlanetCount);
	ui->labsupperNum->setText(strSupper);
	// 顶级矿星个数
	QString strTopest = QString("顶级矿星(%1)").arg(info.uiTopPlanetCount);
	ui->labtopNum->setText(strTopest);

	// 总资源
	QString strRes = QString("%1").arg(info.totalResource);
	ui->labtotalRes->setText(strRes);
	// 掘金
	QString strjuejin = QString("%1 ALX").arg(info.dTotalInCome);
	ui->labjuejin->setText(strjuejin);
	// 分红
	ui->labfenhong->setText(QString::number(info.dTotalFenhong));

	if(info.IsAbleBuyMore == false){
		ui->btnbuyplanet->setEnabled(false);
	}
}

void PetPlanetDlg::updateBalance(const CAmount& balance, const CAmount& unconfirmedBalance, const CAmount& immatureBalance, const CAmount& watchOnlyBalance, const CAmount& watchUnconfBalance, const CAmount& watchImmatureBalance)
{
	// find all the coin send to planet addr ,and find 20000 / 10000000 / 1000000000 / 10000000000

	string strAccount = "*";

    Array ret4cli;
    vector<CTx4Pet> ret4pet;
    std::list<CAccountingEntry> acentries;
    CWallet::TxItems txOrdered;

    // find all the tx to planet addr;
    //---------------------------------------------------------------------------------------//
    txOrdered = pwalletMain->OrderedTxItems(acentries, strAccount);

    for (CWallet::TxItems::iterator it = txOrdered.begin(); it != txOrdered.end(); ++it)
    {
        CWalletTx *const pwtx = (*it).second.first;
        if (pwtx != 0)
    	{
    		ListSendToPlanetAddr(*pwtx, strAccount, planetconfirms, planetAddr, 1, ret4cli, ret4pet);
    	}
	}

	// 更新升级信息;
	int iupdatesucCount = GetUpdateSucCounts(ret4pet);

	UpdatePlanetClutrue(iupdatesucCount);
	// 更新矿星信息;

	PlanetGetInfo info;
	memset(&info,0,sizeof(info));
	info.uiPlanetLevel = iupdatesucCount;
	GetPlanetInfos(ret4pet,info);

	updateOwnerPlanetInfo(info);
	
}
int PetPlanetDlg::GetUpdateSucCounts(vector<CTx4Pet>& planets)
{
	int iValidCount = 0;
	for (unsigned int i = 0; i < planets.size(); i++)
    {
    	if(planets.at(i).sendAmount == PlanetUpdteAmount && planets.at(i).confirmcount >= 1) {
	        string strTxid = planets.at(i).sendTxid;
			if(IsUpdateSucc(strTxid)){
				iValidCount += 1;
			}
    	}
    }
	return iValidCount;
}
// 通过秒来计算实际天数;
qint64 PetPlanetDlg::getPlanetOwnTime(int begintime)
{
	QDateTime now = QDateTime::currentDateTime();
	QDateTime dtime = QDateTime::fromTime_t(begintime);
	// 计算时间;
	qint64 result = dtime.secsTo(now);

	result /= onedaytimevalsec;
	return result;
}

bool PetPlanetDlg::IsUpdateSucc(string strTxid)
{	
	int nNumberCount = 0;
	if(strTxid.length() < 5){
		return false;
	}

	for(int i = 0; i< 5; i++){
		if(strTxid[i] >= '0' && strTxid[i] <= '9'){
			nNumberCount += 1;
		}
	}
	return nNumberCount >= 3;
}

void PetPlanetDlg::GetPlanetInfos(vector<CTx4Pet>& planets,PlanetGetInfo& info)
{
	// 当前掘金值;
	int juejinValue = petPropetyResult["juejin"];


	
	int iCount = 0;
	// 待添加掘矿和分红;
	double tempvalue = 1.0;
	for (unsigned int i = 0; i < planets.size(); i++)
    {
    	int uiDays = getPlanetOwnTime(planets.at(i).sendTime) + 1;
    	if(planets.at(i).sendAmount == PlanetNormalAmount) {
	        // 计算值;
	        iCount += 1;
			if(planets.at(i).confirmcount >= 1){
				info.uiNorPlanetCount += 1;
			 	info.totalResource += PlanetNormalAmount;
				info.dTotalInCome += (double)(PlanetNormalAmount * juejinValue * uiDays) * IncomeCoinsPerYear * (1+(double)info.uiPlanetLevel*0.01) / DaysPerYear;
				tempvalue += PlanetNormalValue;
			}
    	} else if(planets.at(i).sendAmount == PlanetSupperAmount){
			iCount += 1;
			if(planets.at(i).confirmcount >= 1){
				info.uiSupperPlanetCount += 1;
				info.totalResource += PlanetSupperAmount;
				info.dTotalInCome += (double)(PlanetSupperAmount * juejinValue * uiDays) * IncomeCoinsPerYear * (1+(double)info.uiPlanetLevel*0.01)/ DaysPerYear;
				tempvalue += PlanetSupperValue;
			}
    	} else if(planets.at(i).sendAmount == PlanetTopAmount){
			iCount += 1;
			if(planets.at(i).confirmcount >= 1){
				info.uiTopPlanetCount += 1;
				info.totalResource += PlanetTopAmount;
				info.dTotalInCome += (double)(PlanetTopAmount * juejinValue * uiDays) * IncomeCoinsPerYear * (1+(double)info.uiPlanetLevel*0.01) / DaysPerYear;
				tempvalue += PlanetTopValue;
			}
    	}
    }
	if(iCount >= 10){
		info.IsAbleBuyMore = false;
		// 计算USDT分红 ，每个是要单独算的
		//info.dTotalFenhong = (double)(juejinValue) * tempvalue * (1+info.uiPlanetLevel) / DaysPerYear;
		double allTotalFenhong = 1.0 ;
		for (unsigned int i = 0; i < planets.size(); i++)
    	{
			int uiDays = getPlanetOwnTime(planets.at(i).sendTime) + 1;
			if(planets.at(i).sendAmount == PlanetNormalAmount) {
				// 计算值;
				if(planets.at(i).confirmcount >= 1){
					allTotalFenhong += (double)(juejinValue)* (1+(double)info.uiPlanetLevel * 0.01)  * PlanetNormalValue*uiDays ;
				}
			} else if(planets.at(i).sendAmount == PlanetSupperAmount){
				if(planets.at(i).confirmcount >= 1){
					
					allTotalFenhong += (double)(juejinValue)* (1+(double)info.uiPlanetLevel * 0.01)  * PlanetSupperValue*uiDays;

				}
			} else if(planets.at(i).sendAmount == PlanetTopAmount){
				if(planets.at(i).confirmcount >= 1){
					allTotalFenhong += (double)(juejinValue)* (1+(double)info.uiPlanetLevel * 0.01)  * PlanetTopValue*uiDays ;
				}
			}
		}
		info.dTotalFenhong = allTotalFenhong / DaysPerYear;
	} else {
		info.dTotalFenhong = 0.0;
		info.IsAbleBuyMore = true;
	}
}

void PetPlanetDlg::ListSendToPlanetAddr(const CWalletTx& wtx, const string& strAccount, int nMinDepth,
                    const set<string>& destAddresses, CAmount desAmount, Array& ret, vector<CTx4Pet>& ret4pet)
{
    CAmount nFee;
    string strSentAccount;
    list<COutputEntry> listSent;

    isminefilter filter = ISMINE_SPENDABLE;

    wtx.GetSendAmounts(listSent, nFee, strSentAccount, filter);

    bool fAllAccounts = (strAccount == string("*"));

    // Sent
    if ((!listSent.empty() || nFee != 0) && (fAllAccounts || strAccount == strSentAccount))
    {
        BOOST_FOREACH(const COutputEntry& soutEntry, listSent)
        {
            Object entry;
            //MaybePushAddress(entry, s.destination);
            CAliencoinAddress addr;

            if (addr.Set(soutEntry.destination)
                    && (destAddresses.find(addr.ToString()) != destAddresses.end()))
            {
                 entry.push_back(Pair("address", addr.ToString()));
            }
            else
                continue;

            int confirms = wtx.GetDepthInMainChain();
            CAmount txAmount = soutEntry.amount;
            if (confirms < nMinDepth ||  txAmount < (desAmount * COIN))
                continue;

            entry.push_back(Pair("time", wtx.GetTxTime()));
            entry.push_back(Pair("confirmations", confirms));
            entry.push_back(Pair("amount", ValueFromAmount(txAmount)));
			
            //WalletTxToJSON(wtx, entry);

            uint256 hash = wtx.GetHash();
            entry.push_back(Pair("txid", hash.GetHex()));
            entry.push_back(Pair("vout", soutEntry.vout));


            CTx4Pet tx4pet;
            tx4pet.sendTime = wtx.GetTxTime();
            tx4pet.sendAmount = txAmount / COIN;
            tx4pet.sendTxid = hash.ToString();
			tx4pet.confirmcount = confirms;
            ret4pet.push_back(tx4pet);

            ret.push_back(entry);
        }
    }
}

