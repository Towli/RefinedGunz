#pragma once

#include <vector>
#include <list>
#include <map>

#define WORLDITEM_EXTRAVALUE_NUM		2

struct MMatchWorldItem
{
	unsigned short		nUID;
	unsigned short		nItemID;
	short				nStaticSpawnIndex;
	v3					Origin;
	int					nLifeTime;

	union {
		struct {
		    int			nDropItemID;
			int			nRentPeriodHour;
		};
		int				nExtraValue[WORLDITEM_EXTRAVALUE_NUM];
	};
};

struct MMatchWorldItemSpawnInfo
{
	unsigned short		nItemID;
	unsigned long int	nCoolTime;
	unsigned long int	nElapsedTime;
	float x;
	float y;
	float z;
	bool				bExist;
	bool				bUsed;
};


using MMatchWorldItemMap = std::unordered_map<unsigned short, MMatchWorldItem>;

class MMatchWorldItemManager
{
private:
	class MMatchStage*					m_pMatchStage = nullptr;
	MMatchWorldItemMap					m_ItemMap;

	std::vector<MMatchWorldItemSpawnInfo> m_SpawnInfos;
	u64									m_nLastTime = 0;

	short								m_nUIDGenerate = 0;
	bool								m_bStarted = false;

	void AddItem(const unsigned short nItemID, short nSpawnIndex, 
				 const float x, const float y, const float z);
	void AddItem(const unsigned short nItemID, short nSpawnIndex, 
				 const float x, const float y, const float z, int nLifeTime, int* pnExtraValues);
	void DelItem(short nUID);
	void DelItem(MMatchWorldItemMap::iterator it);
	void Spawn(int nSpawnIndex);
	void Clear();
	void SpawnInfoInit();
	void ClearItems();

	void RouteSpawnWorldItem(MMatchWorldItem* pWorldItem);
	void RouteObtainWorldItem(const MUID& uidPlayer, int nWorldItemUID);
	void RouteRemoveWorldItem(int nWorldItemUID);
public:
	MMatchWorldItemManager(MMatchStage* Stage) : m_pMatchStage(Stage) {}

	void OnRoundBegin();
	void OnStageBegin(class MMatchStageSetting* pStageSetting);
	void OnStageEnd();
	void Update();

	bool Obtain(MMatchObject* pObj, short nItemUID);
	void SpawnDynamicItem(const int nItemID, const float x, const float y, const float z);
	void SpawnDynamicItem(const int nItemID, const float x, const float y, const float z, 
						  int nLifeTime, int* pnExtraValues );
	void RouteAllItems(MMatchObject* pObj);
};