#include "stdafx.h"
#include "Base_Object.h"

Base_Object::Base_Object(void)
{
}

Base_Object::~Base_Object(void)
{
	Object_Ent = nullptr;
	Object_Node = nullptr;

	Phys_Body = nullptr;
	Phys_Shape = nullptr;
}
