#pragma once



#define NO_MORE_GROUPS	(-1)

typedef struct tag_GroupListType GroupListType;
typedef struct tag_Group Group;
typedef struct tag_Group* GroupIterator;

class CGroup
{

public:
	CGroup();
	~CGroup();

	GroupListType* Group_CreateList(void);
	Group* Group_Create(int id, char const* pName);
	void GroupList_Add(GroupListType* Groups, Group* pGroup);
	const char* Group_GetName(const Group* pGroup);
	int Group_GetFirstId(GroupListType const* pList, GroupIterator* gi);
};

