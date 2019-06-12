// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        ( 0, uint256("0x0000002eae47d863d9b706a35cfe86a934bf0bfe7ade81ae8e5749587553e631"))
//         (53700, uint256("0x00000000e4dc88f4e2aae3bcb4cf8cd7757b020c31a720e118b76bdd4b6c0f1d"))
//         ( 53785, uint256("0x000000002dd5588a74784eaa7ab0507a18ad16a236e7b1ce69f00d7ddfb5d0a6"))
        // ( 74000, uint256("0x0000000000573993a3c9e41ce34471c079dcf5f52a0e824a81e7f953b8661a20"))
        // (105000, uint256("0x00000000000291ce28027faea320c8d2b054b2e0fe44a773f3eefb151d6bdc97"))
        // (134444, uint256("0x00000000000005b12ffd4cd315cd34ffd4a594f430ac814c91184a0d42d2b0fe"))
        // (168000, uint256("0x000000000000099e61ea72015e79632f216fe6cb33d7899acb35b75c8303b763"))
        // (193000, uint256("0x000000000000059f452a5f7340de6682a977387c17010ff6e6c3bd83ca8b1317"))
        // (210000, uint256("0x000000000000048b95347e83192f69cf0366076336c639f9b7228e9ba171342e"))
        // (216116, uint256("0x00000000000001b4f4b433e81ee46494af945cf96014816a4e2370f11b23df4e"))
        // (225430, uint256("0x00000000000001c108384350f74090433e7fcf79a606b8e797f065b130575932"))
        // (250000, uint256("0x000000000000003887df1f29024b06fc2200b55f8af8f35453d7be294df2d214"))
        // (279000, uint256("0x0000000000000001ae8c72a0b0c301f67e3afca10e819efa9041e458e9bd7e40"))
        // (295000, uint256("0x00000000000000004d9b4ef50f0f9d686fd69db2e03af35a100370c64632a983"))
        ;
static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        1397080064, // * UNIX timestamp of last checkpoint block
        36544669,   // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        60000.0     // * estimated number of transactions per day after checkpoint
    };

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0, uint256("0x0000002eae47d863d9b706a35cfe86a934bf0bfe7ade81ae8e5749587553e631"))
    //    ( 546, uint256("000000002a936ca763904c3c35fce2f3556c559c0214345d31b1bcebf76acb70"))
        ;
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1337966069,
        1488,
        300
    };

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of
        ( 0, uint256("0x0000002eae47d863d9b706a35cfe86a934bf0bfe7ade81ae8e5749587553e631"))
    //   ( 0, uint256("0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206"))
        ;
static const Checkpoints::CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        0,
        0,
        0
    };

class CMainParams : public CChainParams {
public:
    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /** 
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x96;
        pchMessageStart[1] = 0x6d;
        pchMessageStart[2] = 0x86;
        pchMessageStart[3] = 0x69;
        vAlertPubKey = ParseHex("0487b8d7d43c77d4f6e89751a83aa88163fee30a2a2ecf4eea35f31afee41be4a1cf9e6e53d21f68ac840b1fd1afc966d17f25b7b5322bd92ae5a4d9026a88df07");
        nDefaultPort = 9969;
        bnProofOfWorkLimit = ~uint256(0) >> 16;
        nSubsidyHalvingInterval = 100000000;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 60 * 60; 
        nTargetSpacing = 1 * 60;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         * 
         * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
         *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
         *   vMerkleTree: 4a5e1e
         */
        //const char* pszTimestamp = "we are all aliens,2018/03/03!";
        const char* pszTimestamp = "we are all aliens,2018/04/22!";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
         txNew.vout[0].nValue = 100 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0432cb798ab0bc87fa88dd045c8ac317df12c7d882a354e2cd0c93fdb58d87f9f33c6f5783bde5712804975b317794a146d2071e8d050658827ca1e86b1359f615") << OP_CHECKSIG;
	    genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1524381213;
        genesis.nBits    = 0x1e00ffff;
        genesis.nNonce   = 10798126;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000002eae47d863d9b706a35cfe86a934bf0bfe7ade81ae8e5749587553e631"));
        assert(genesis.hashMerkleRoot == uint256("0x1897fe6b745f4b2138acda454fcb731fca274f8ef4ebb806b594ca152016f1c1"));

        vSeeds.push_back(CDNSSeedData("aliencoin.sipa.be", "119.3.24.111"));
        vSeeds.push_back(CDNSSeedData("59.110.240.15", "59.110.240.15"));
        vSeeds.push_back(CDNSSeedData("47.52.16.146", "47.52.16.146"));
        vSeeds.push_back(CDNSSeedData("119.23.108.118", "119.23.108.118"));
        vSeeds.push_back(CDNSSeedData("123.56.88.217", "123.56.88.217"));
       
	// #ifdef WIN32
        base58Prefixes[PUBKEY_ADDRESS] = {23};
        base58Prefixes[SCRIPT_ADDRESS] = {48};
        base58Prefixes[SECRET_KEY] =     {46};
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x86, 0xE6, 0x36};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x89, 0xE9, 0x49};
	// #else
		// base58Prefixes[PUBKEY_ADDRESS] = list_of(23) ;
        // base58Prefixes[SCRIPT_ADDRESS] = list_of(48) ;
        // base58Prefixes[SECRET_KEY] =     list_of(46) ;
        // base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x86)(0xE6)(0x36) ;
        // base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x89)(0xE9)(0x49) ;
	// #endif

 
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultCheckMemPool = false;
        fAllowMinDifficultyBlocks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x6b;
        pchMessageStart[1] = 0x61;
        pchMessageStart[2] = 0x99;
        pchMessageStart[3] = 0x97;
        vAlertPubKey = ParseHex("04302390343f91cc401d56d68b123028bf52e5fca1939df127f63c6467cdf9c8e2c14b61104cf817d0b780da337893ecc4aaff1309e536162dabbdb45200ca2b0a");
       
        nDefaultPort = 19969;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 14 * 24 * 60 * 60; //! two weeks
        nTargetSpacing = 10 * 60;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1296688602;
        genesis.nNonce = 414098458;
        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x000000000933ea01ad0ee984209779baaec3ced90fa3f408719526f8d77f4943"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // vSeeds.push_back(CDNSSeedData("alexykot.me", "testnet-seed.alexykot.me"));
        // vSeeds.push_back(CDNSSeedData("aliencoin.petertodd.org", "testnet-seed.aliencoin.petertodd.org"));
        // vSeeds.push_back(CDNSSeedData("bluematt.me", "testnet-seed.bluematt.me"));
        // vSeeds.push_back(CDNSSeedData("aliencoin.schildbach.de", "testnet-seed.aliencoin.schildbach.de"));

        //vSeeds.push_back(CDNSSeedData("aliencoin1.waixingdun.com", "114.115.162.4"));
        //vSeeds.push_back(CDNSSeedData("aliencoin2.waixingdun.com", "114.115.143.144"));
        vSeeds.push_back(CDNSSeedData("aliencoin.sipa.be", "119.3.24.111"));
        // vSeeds.push_back(CDNSSeedData("aliencoin3.waixingdun.com", "114.115.143.47"));
        // vSeeds.push_back(CDNSSeedData("aliencoin4.waixingdun.com", "122.112.211.209"));
        // vSeeds.push_back(CDNSSeedData("aliencoin5.waixingdun.com", "119.3.4.111"));
        // vSeeds.push_back(CDNSSeedData("aliencoin6.waixingdun.com", "119.3.5.145"));
        // vSeeds.push_back(CDNSSeedData("aliencoin7.waixingdun.com", "59.110.240.15"));
       
	// #ifdef WIN32
        base58Prefixes[PUBKEY_ADDRESS] = {116};
        base58Prefixes[SCRIPT_ADDRESS] = {196};
        base58Prefixes[SECRET_KEY]     = {239};
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x36, 0x86, 0xC6};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x39, 0x89, 0x99};
	// #else
		// base58Prefixes[PUBKEY_ADDRESS] = list_of(116) ;
        // base58Prefixes[SCRIPT_ADDRESS] = list_of(196) ;
        // base58Prefixes[SECRET_KEY] =     list_of(239) ;
        // base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x36)(0x86)(0xC6) ;
        // base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x39)(0x89)(0x99) ;
	// #endif
	
        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultCheckMemPool = false;
        fAllowMinDifficultyBlocks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x6a;
        pchMessageStart[1] = 0x6f;
        pchMessageStart[2] = 0x95;
        pchMessageStart[3] = 0x9a;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 14 * 24 * 60 * 60; //! two weeks
        nTargetSpacing = 10 * 60;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1296688602;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 2;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        //assert(hashGenesisBlock == uint256("0x0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultCheckMemPool = true;
        fAllowMinDifficultyBlocks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:
    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 18445;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultCheckMemPool = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval)  { nSubsidyHalvingInterval=anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority)  { nEnforceBlockUpgradeMajority=anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority)  { nRejectBlockOutdatedMajority=anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority)  { nToCheckBlockUpgradeMajority=anToCheckBlockUpgradeMajority; }
    virtual void setDefaultCheckMemPool(bool afDefaultCheckMemPool)  { fDefaultCheckMemPool=afDefaultCheckMemPool; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {  fAllowMinDifficultyBlocks=afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams *pCurrentParams = 0;

CModifiableParams *ModifiableParams()
{
   assert(pCurrentParams);
   assert(pCurrentParams==&unitTestParams);
   return (CModifiableParams*)&unitTestParams;
}

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        case CBaseChainParams::UNITTEST:
            return unitTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
