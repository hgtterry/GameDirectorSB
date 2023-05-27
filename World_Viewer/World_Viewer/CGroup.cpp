#include "stdafx.h"
#include "WV_App.h"
#include "CGroup.h"
#include "ram.h"

CGroup::CGroup()
{
}

CGroup::~CGroup()
{
}

struct tag_Group
{
	BOOL		Visible;
	BOOL		Locked;
	int			GroupId;
	char*		GroupName;
	GE_RGBA		Color;
	tag_Group*	Next;
};

struct tag_GroupListType
{
	Group* First;
};

// *************************************************************************
// * 						Group_CreateList							   *
// *************************************************************************
GroupListType* CGroup::Group_CreateList(void)
{
	GroupListType* pList;

	pList = (GroupListType*)geRam_Allocate(sizeof(GroupListType));
	if (pList != NULL)
	{
		pList->First = NULL;
	}
	return pList;
}

// *************************************************************************
// * 							Group_Create							   *
// *************************************************************************
Group* CGroup::Group_Create(int id, char const* pName)
{
	Group* pGroup;

	assert(pName != NULL);

	pGroup = (Group*)geRam_Allocate(sizeof(Group));
	if (pGroup != NULL)
	{
		pGroup->Visible = TRUE;
		pGroup->Locked = FALSE;
		pGroup->GroupId = id;
		pGroup->GroupName = App->CL_CUtil->Util_Strdup(pName);
		pGroup->Color.r = 255.0;
		pGroup->Color.g = 255.0;
		pGroup->Color.b = 255.0;
		pGroup->Color.a = 255.0;
		pGroup->Next = NULL;
	}

	return pGroup;
}

// *************************************************************************
// * 							GroupList_Add							   *
// *************************************************************************
void CGroup::GroupList_Add(GroupListType* Groups, Group* pGroup)
{
	Group* p, * q;

	// find the insertion spot
	p = Groups->First;
	q = NULL;
	while (p != NULL)
	{
		if (p->GroupId > pGroup->GroupId)
		{
			break;
		}
		q = p;
		p = p->Next;
	}

	if (q == NULL)
	{
		Groups->First = pGroup;
	}
	else
	{
		pGroup->Next = q->Next;
		q->Next = pGroup;
	}
}

// *************************************************************************
// * 							Group_GetName							   *
// *************************************************************************
const char* CGroup::Group_GetName(const Group* pGroup)
{
	assert(pGroup != NULL);

	return pGroup->GroupName;
}

// *************************************************************************
// * 							Group_GetFirstId						   *
// *************************************************************************
int CGroup::Group_GetFirstId(GroupListType const* pList, GroupIterator* gi)
{
	assert(pList != NULL);
	assert(gi != NULL);

	*gi = pList->First;

	if (*gi != NULL)
	{
		return (*gi)->GroupId;
	}
	else
	{
		return NO_MORE_GROUPS;
	}
}
