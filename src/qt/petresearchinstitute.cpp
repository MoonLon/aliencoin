#include "petresearchinstitute.h"
#include "aliencoinunits.h"
#include "ui_petresearchinstitute.h"
#include <QGridLayout>
#include <QPushButton> 
#include <QDateTime>
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


#include <boost/assign/list_of.hpp>
#include "json/json_spirit_utils.h"
#include "json/json_spirit_value.h"

using namespace std;
using namespace boost;
using namespace boost::assign;
using namespace json_spirit;

static QWidget* makePetFrameSpacer()
{
    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    spacer->setStyleSheet("QWidget { background: rgb(30,32,36); }");
    return spacer;
}

PetResearchInstitute::PetResearchInstitute(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PetResearchInstitute),
	walletModel(0),
    leftPetWidget(0)
{
    ui->setupUi(this);
	
	// 在此出加入界面设计代码;
	// 水平布局;
	auto vgirdLayout = new QGridLayout();
	// 将主要显示的数据放置于中心;

	auto centerWidget = new QWidget(this);
	InitPetMainFrame(centerWidget);
	// 设置子窗口;
	// 添加一个空白;
	QSpacerItem* verticalSpacer1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
	QSpacerItem* verticalSpacer2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    // fix app crash when closing, think hSpacer1 was deleted twice.
    QSpacerItem* hSpacer1 = new QSpacerItem(40, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
	QSpacerItem* hSpacer2 = new QSpacerItem(40, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
	vgirdLayout->addItem(verticalSpacer1,0,0,1,3);
	vgirdLayout->addItem(hSpacer1,1,0,1,1);
	// 第二行第二列为主显示界面;
	vgirdLayout->addWidget(centerWidget, 1, 1, 1, 1);
    vgirdLayout->addItem(hSpacer2,1,2,1,1);
	vgirdLayout->addItem(verticalSpacer2,2,0,1,3);

	setLayout(vgirdLayout);
}

PetResearchInstitute::~PetResearchInstitute()
{
    delete ui;
}

void PetResearchInstitute::InitPetMainLeftWidget(QWidget* pLeftWidget)
{
	// 增加一个带图片的widget即可;
	if(pLeftWidget)
	{
		pLeftWidget->setMinimumSize(344,530);
		pLeftWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		pLeftWidget->setStyleSheet("QWidget { border-image:url(:/images/gen0);}");
		
		auto righthLayout = new QHBoxLayout(pLeftWidget);
	}
		
}
void PetResearchInstitute::InitPetMainRightWidget(QWidget* pRightWidget)
{
	// 左侧是一个StackWidget;
	pRightWidget->setMinimumSize(408,480);
	pRightWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	pRightWidget->setStyleSheet("QWidget { background-color: rgba(255, 255, 255, 0); }");
	auto righthLayout = new QHBoxLayout(pRightWidget);
	righthLayout->setContentsMargins(3,0,3,0);
	righthLayout->setSpacing(0);
	attrWidget = new QStackedWidget(pRightWidget);
	attrWidget->setMinimumSize(408,480);
	// 设置Attr的相关属性;
	petAttrWidget = new PetAttrDialog(attrWidget);
	attrWidget->addWidget(petAttrWidget);
	petAttrWidget->setMinimumSize(408,480);
	petPowerWidget = new CombatPowerDialog(attrWidget);
	attrWidget->addWidget(petPowerWidget);
	petPowerWidget->setMinimumSize(408,480);
	petFeedWidget = new PetFeedDialog(attrWidget);
	attrWidget->addWidget(petFeedWidget);
	petFeedWidget->setMinimumSize(408,480);
	petHowtoplay = new HowToPlayDialog(attrWidget);
	attrWidget->addWidget(petHowtoplay);
	petHowtoplay->setMinimumSize(408,480);
	// 右侧是一个Actions;
	auto boxLayout = new QVBoxLayout(pRightWidget);
	QButtonGroup* btnGroup = new QButtonGroup(pRightWidget);
	// 设置两个Actor之间的间隔;
	btnAttr = new QPushButton(tr("属\n性"), pRightWidget);
	SetTabPushButtonSheet(btnAttr);
	btnGroup->addButton(btnAttr);
	boxLayout->addWidget(btnAttr);
	btnAttr->setChecked(true);
    connect(btnAttr, SIGNAL(toggled(bool)), this, SLOT(gotoPetAttr(bool)));
	
	// 添加到group中;
	btnPower = new QPushButton(tr("战\n力"), pRightWidget);
	SetTabPushButtonSheet(btnPower);
	btnGroup->addButton(btnPower);
	boxLayout->addWidget(btnPower);
    connect(btnPower, SIGNAL(toggled(bool)), this, SLOT(gotoPetPower(bool)));
	// 设置信号和槽

	auto btnFeed = new QPushButton(tr("喂\n养"), pRightWidget);
	SetTabPushButtonSheet(btnFeed);
	btnGroup->addButton(btnFeed);
	boxLayout->addWidget(btnFeed);
	connect(btnFeed, SIGNAL(toggled(bool)), this, SLOT(gotoPetFeed(bool)));
	// 设置信号和槽

	auto btnPlay = new QPushButton(tr("玩\n法"), pRightWidget);
	SetTabPushButtonSheet(btnPlay);
	btnGroup->addButton(btnPlay);
	boxLayout->addWidget(btnPlay);
	connect(btnPlay, SIGNAL(toggled(bool)), this, SLOT(gotoPetPlay(bool)));
	// 设置信号和槽
	// 将4个按钮放置到boxlayout;
	righthLayout->addWidget(attrWidget);
	// 添加子layout;
	righthLayout->addLayout(boxLayout);
}

void PetResearchInstitute::InitPetMainFrame(QWidget *pSubFrame)
{
	// 设置中心窗口的大小;
	pSubFrame->setMinimumSize(830, 530);
	pSubFrame->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	// 设置水平的layout;
	auto hLayOut = new QHBoxLayout(pSubFrame);
	hLayOut->setContentsMargins(3,0,3,0);
	// 中间设置28px的间隔;
    hLayOut->setSpacing(0);
	// 设置左侧的窗口;
	leftPetWidget = new QWidget(pSubFrame);
	InitPetMainLeftWidget(leftPetWidget);
	hLayOut->addWidget(leftPetWidget);
	rightPetWidget = new QWidget(pSubFrame);
	InitPetMainRightWidget(rightPetWidget);
	// 设计右侧的窗口;
	hLayOut->addWidget(rightPetWidget);
	
}

void PetResearchInstitute::ListSendToBoss(const CWalletTx& wtx, const string& strAccount, int nMinDepth,
                    const set<string>& destAddresses, CAmount desAmount, Array& ret, vector<CTx4Pet>& ret4pet)
{
    CAmount nFee;
    string strSentAccount;
    list<COutputEntry> listSent;

    isminefilter filter = ISMINE_SPENDABLE;

    wtx.GetSendAmounts(listSent, nFee, strSentAccount, filter);

    bool fAllAccounts = (strAccount == string("*"));
//    bool involvesWatchonly = wtx.IsFromMe(ISMINE_WATCH_ONLY);

    // Sent
    if ((!listSent.empty() || nFee != 0) && (fAllAccounts || strAccount == strSentAccount))
    {
        BOOST_FOREACH(const COutputEntry& soutEntry, listSent)
        {
            Object entry;
//            if(involvesWatchonly || (::IsMine(*pwalletMain, s.destination) & ISMINE_WATCH_ONLY))
//                entry.push_back(Pair("involvesWatchonly", true));
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

            //entry.push_back(Pair("account", strSentAccount));
            //entry.push_back(Pair("category", "send"));
            //WalletTxToJSON(wtx, entry);

            uint256 hash = wtx.GetHash();
            entry.push_back(Pair("txid", hash.GetHex()));
            entry.push_back(Pair("vout", soutEntry.vout));


            CTx4Pet tx4pet;
            tx4pet.sendTime = wtx.GetTxTime();
            tx4pet.sendAmount = txAmount / COIN;
            tx4pet.sendTxid = hash.ToString();
            ret4pet.push_back(tx4pet);

            ret.push_back(entry);
            if (ret.size() > 0)
                break;
        }
    }
}

void PetResearchInstitute::ListSendToSeed(const CWalletTx& wtx, const string& strAccount, int nMinDepth,
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
//            if(involvesWatchonly || (::IsMine(*pwalletMain, s.destination) & ISMINE_WATCH_ONLY))
//                entry.push_back(Pair("involvesWatchonly", true));
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
            if (confirms < nMinDepth ||  txAmount != (desAmount * COIN))
                continue;

            entry.push_back(Pair("time", wtx.GetTxTime()));
            entry.push_back(Pair("confirmations", confirms));
            entry.push_back(Pair("amount", ValueFromAmount(txAmount)));

            //entry.push_back(Pair("account", strSentAccount));
            //entry.push_back(Pair("category", "send"));
            //WalletTxToJSON(wtx, entry);

            uint256 hash = wtx.GetHash();
            entry.push_back(Pair("txid", hash.GetHex()));
            entry.push_back(Pair("vout", soutEntry.vout));


            CTx4Pet tx4pet;
            int txtime = wtx.GetTxTime();
            tx4pet.sendTime = txtime;
            tx4pet.sendAmount = txAmount / COIN;
            tx4pet.sendTxid = hash.ToString();

            if (ret4pet.size() > 0 && (txtime - ret4pet.back().sendTime) < vaid_interval)
                continue;

            ret4pet.push_back(tx4pet);
            ret.push_back(entry);

        }
    }
}


void PetResearchInstitute::ListSendToXiaohui(const CWalletTx& wtx, const string& strAccount, int nMinDepth,
                    const set<string>& destAddresses, CAmount desAmount, Array& ret, vector<CTx4Pet>& ret4pet)
{
    CAmount nFee;
    string strSentAccount;
    list<COutputEntry> listSent;
    isminefilter filter = ISMINE_SPENDABLE;
    wtx.GetSendAmounts(listSent, nFee, strSentAccount, filter);
    bool fAllAccounts = (strAccount == string("*"));

    if ((!listSent.empty() || nFee != 0) && (fAllAccounts || strAccount == strSentAccount))
    {
        BOOST_FOREACH(const COutputEntry& soutEntry, listSent)
        {
            Object entry;
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
            if (confirms < nMinDepth ||  txAmount != (desAmount * COIN))
                continue;

            entry.push_back(Pair("time", wtx.GetTxTime()));
            entry.push_back(Pair("confirmations", confirms));
            entry.push_back(Pair("amount", ValueFromAmount(txAmount)));

            uint256 hash = wtx.GetHash();
            entry.push_back(Pair("txid", hash.GetHex()));
            entry.push_back(Pair("vout", soutEntry.vout));


            CTx4Pet tx4pet;
            tx4pet.sendTime = wtx.GetTxTime();
            tx4pet.sendAmount = txAmount / COIN;
            tx4pet.sendTxid = hash.ToString();
            ret4pet.push_back(tx4pet);

            ret.push_back(entry);
            if (ret.size() > 0)
                break;
        }
    }
}


void PetResearchInstitute::setBalance(const CAmount& balance, const CAmount& unconfirmedBalance, const CAmount& immatureBalance, const CAmount& watchOnlyBalance, const CAmount& watchUnconfBalance, const CAmount& watchImmatureBalance)
{

	string strAccount = "*";

    Array ret4cli;
    vector<CTx4Pet> ret4pet;
    std::list<CAccountingEntry> acentries;
    CWallet::TxItems txOrdered;

    //查看宠物是否销毁
    //---------------------------------------------------------------------------------------//
    txOrdered = pwalletMain->OrderedTxItems(acentries, strAccount);

    for (CWallet::TxItems::iterator it = txOrdered.begin(); it != txOrdered.end(); ++it)
    {
        CWalletTx *const pwtx = (*it).second.first;
        if (pwtx != 0)
            ListSendToXiaohui(*pwtx, strAccount, confirms, xiaohuiAddress, xiaohuiAmount, ret4cli, ret4pet);
    }

    if (ret4pet.size() > 0)
    {
        string strDebugMsg = strprintf("debug,listsendtoxiaohui: %s, %s, %s ",
                                       ret4pet.front().sendTxid,
                                       ret4pet.front().sendTime,
                                       ret4pet.front().sendAmount);
        //LogPrintf(" : %s\n", strDebugMsg);
        petBorn = 444;
        this->leftPetWidget->setStyleSheet("QWidget { border-image:url(:/images/pet444);}");
        return;
    }

    //获取几代接口
    //---------------------------------------------------------------------------------------//
    ret4cli.clear();
    ret4pet.clear();
    acentries.clear();
    txOrdered.clear();

    txOrdered = pwalletMain->OrderedTxItems(acentries, strAccount);
    for (CWallet::TxItems::iterator it = txOrdered.begin(); it != txOrdered.end(); ++it)
    {
        CWalletTx *const pwtx = (*it).second.first;
        if (pwtx != 0)
            ListSendToBoss(*pwtx, strAccount, confirms, bossAddress, firstAmount, ret4cli, ret4pet);
        if (ret4cli.size() > 0)
            break;
    }

    CAmount hitAmount = 0;
    if (ret4pet.size() > 0)
    {
        hitAmount = ret4pet.front().sendAmount;
        string strDebugMsg = strprintf("debug,listsendtoboss: %s, %s, %s ",
                                       ret4pet.front().sendTxid,
                                       ret4pet.front().sendTime,
                                       ret4pet.front().sendAmount);
       // LogPrintf(" : %s\n", strDebugMsg);
    }

    //根据计算几代结果，设置对应的图片
    //把图片放入对应目录，然后修改aliencoin.qrc文件
    //如下设置未领养的图片
    // TODO: for test, should be 100000
    switch (hitAmount)
    {
        case 1000000000:
            petBorn = -1;
            this->leftPetWidget->setStyleSheet("QWidget { border-image:url(:/images/pet-1);}");
            break;
        case 100000000:
            petBorn = 0;
            this->leftPetWidget->setStyleSheet("QWidget { border-image:url(:/images/pet0);}");
            break;
        case 10000000:
            petBorn = 1;
            this->leftPetWidget->setStyleSheet("QWidget { border-image:url(:/images/pet1);}");
            break;
        case 1000000:
            petBorn = 2;
            this->leftPetWidget->setStyleSheet("QWidget { border-image:url(:/images/pet2);}");
            break;
        case 100000:
            petBorn = 3;
            this->leftPetWidget->setStyleSheet("QWidget { border-image:url(:/images/pet3);}");
            break;
        default:
            petBorn = 99;
            this->leftPetWidget->setStyleSheet("QWidget { border-image:url(:/images/pet100);}");
    }


    //获取属性接口
    //---------------------------------------------------------------------------------------//
    ret4cli.clear();
    ret4pet.clear();
    acentries.clear();
    txOrdered.clear();

    txOrdered = pwalletMain->OrderedTxItems(acentries, strAccount);
    for (CWallet::TxItems::iterator it = txOrdered.begin(); it != txOrdered.end(); ++it)
    {
        CWalletTx *const pwtx = (*it).second.first;
        if (pwtx != 0)
            ListSendToSeed(*pwtx, strAccount, confirms, feedAddresses, eachFeedAmount, ret4cli, ret4pet);
    }

    for (unsigned int i = 0; i < ret4pet.size(); i++)
    {
        string strDebugMsg = strprintf("debug,listsendtoseed: %d, %s, %s, %s ",
                                       i,
                                       ret4pet.at(i).sendTxid,
                                       ret4pet.at(i).sendTime,
                                       ret4pet.at(i).sendAmount);
        //LogPrintf(" : %s\n", strDebugMsg);
    }

    feedCount = ret4pet.size();
    if (petBorn != 99)
    {
        if (feedCount > 0)
        {
            int lastfeedtime = ret4pet.back().sendTime;
            nextfeedtime = lastfeedtime + vaid_interval + 60;
            QDateTime dtime = QDateTime::fromTime_t(nextfeedtime);
            QString strtime = dtime.toString("yyyy-MM-dd hh:mm:ss");

            petFeedWidget->setAttr(QString("下次可喂养时间: ") + strtime);
        }
        else
        {

            petFeedWidget->setAttr(QString("随时可以喂养"));
        }
    }
    else
    {

    }

    zhanli = 0;
    if(petBorn != 99)
    {
        dengji = feedCount;
    }

    std::map<std::string, int>::iterator iter;
    for (iter = petPropetyResult.begin(); iter != petPropetyResult.end(); ++iter)
    {
        iter->second = petPropetyNumber[iter->first][petBorn] * feedCount;
        zhanli += iter->second;
    }
    // 综合评估：
    // 战斗力=力量+敏捷+智力+格挡+暴击+移动+跳距+攻距+瞬发+科技熟练+超能力+团战指挥+统帅 (除去战力之外的其他相加)
    zhanli -= petPropetyResult["juejin"];


	//根据计算结果，setAttr设置对应的属性，目前只设置了两个属性，可以扩展该函数设置所有属性
	//setAttr 在petattrdialog.h定义
	//petattrdialog.cpp 实现，根据ui设置属性
//    {"liliang"  , 0},
//    {"minjie"   , 0},
//    {"zhili"    , 0},
//    {"tongshuai", 0},
//    {"gedang"   , 0},
//    {"baoji"    , 0},
//    {"yidong"   , 0},
//    {"tiaoju"   , 0},
//    {"gongju"   , 0},
//    {"shunfa"   , 0},
//    {"keji"     , 0},
//    {"chaonengli", 0},
//    {"tuanzhan" , 0},
//    {"juejin"   , 0},
    petAttrWidget->setAttr(petPropetyResult["liliang"], petPropetyResult["minjie"], petPropetyResult["zhili"],
            petPropetyResult["tongshuai"], petPropetyResult["gedang"], petPropetyResult["baoji"],
            petPropetyResult["yidong"], petPropetyResult["tiaoju"], petPropetyResult["gongju"],
            petPropetyResult["shunfa"], petPropetyResult["keji"], petPropetyResult["chaonengli"],
            petPropetyResult["tuanzhan"], petPropetyResult["juejin"],
            dengji);

    petPowerWidget->setAttr(zhanli);

	
    //LogPrintf("###监听事件, listen event!!!\n");

    ret4cli.clear();
    ret4pet.clear();
}

void PetResearchInstitute::setWalletModel(WalletModel *model)
{
    this->walletModel = model;
    if(model && model->getOptionsModel())
    {
        // Set up transaction list
		/*
        filter = new TransactionFilterProxy();
        filter->setSourceModel(model->getTransactionTableModel());
        filter->setLimit(NUM_ITEMS);
        filter->setDynamicSortFilter(true);
        filter->setSortRole(Qt::EditRole);
        filter->setShowInactive(false);
        filter->sort(TransactionTableModel::Status, Qt::DescendingOrder);

        ui->listTransactions->setModel(filter);
        ui->listTransactions->setModelColumn(TransactionTableModel::ToAddress);
        */
        // Keep up to date with wallet
		
		
        setBalance(model->getBalance(), model->getUnconfirmedBalance(), model->getImmatureBalance(),
                   model->getWatchBalance(), model->getWatchUnconfirmedBalance(), model->getWatchImmatureBalance());
        connect(model, SIGNAL(balanceChanged(CAmount,CAmount,CAmount,CAmount,CAmount,CAmount)), this, SLOT(setBalance(CAmount,CAmount,CAmount,CAmount,CAmount,CAmount)));

        //connect(model->getOptionsModel(), SIGNAL(displayUnitChanged(int)), this, SLOT(updateDisplayUnit()));

        //updateWatchOnlyLabels(model->haveWatchOnly());
        //connect(model, SIGNAL(notifyWatchonlyChanged(bool)), this, SLOT(updateWatchOnlyLabels(bool)));
		
    }

    // update the display unit, to not use the default ("ALC")
    //updateDisplayUnit();
}

void PetResearchInstitute::SetTabPushButtonSheet(QPushButton* pPushButton)
{
	if(!pPushButton) return;

	// 设置大小;
	pPushButton->setFixedWidth(56);
	
	pPushButton->setFixedHeight(99);
	//添加状态;
	
	pPushButton->setStyleSheet("QPushButton{border-image:url(:/images/btnnor);color: rgb(255, 255, 255);font: 20pt \"Arial\";}"
							   "QPushButton:hover{border-image:url(:/images/btnsel);color: rgb(132, 146, 166); font: 20pt \"Arial\";}"
							   "QPushButton:checked{border-image:url(:/images/btnsel);color: rgb(132, 146, 166); font: 20pt \"Arial\";}"
							   "QPushButton:pressed{border-image:url(:/images/btnsel);color: rgb(132, 146, 166); font: 20pt \"Arial\";}");
	pPushButton->setCheckable(true);
	
}

void PetResearchInstitute::gotoPetAttr(bool flag)
{
    if (attrWidget) attrWidget->setCurrentWidget(petAttrWidget);
}

void PetResearchInstitute::gotoPetPower(bool flag)
{
    if (attrWidget) attrWidget->setCurrentWidget(petPowerWidget);
}

void PetResearchInstitute::gotoPetFeed(bool flag)
{
    if (petFeedWidget) attrWidget->setCurrentWidget(petFeedWidget);
}
void PetResearchInstitute::gotoPetPlay(bool flag)
{
    if (attrWidget) attrWidget->setCurrentWidget(petHowtoplay);
}
