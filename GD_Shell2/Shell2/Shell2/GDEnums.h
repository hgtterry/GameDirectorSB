

namespace Enums
{
	enum Usage
	{
		Useage_None = 0,
		Usage_Object = 1,
		Usage_Ammo = 2,
		Usage_Weapon = 3,
		Usage_Teleport = 4,
		Usage_ChangeLevel = 5,
		Usage_MediKit = 6,
		Usage_Recevier = 7,
		Usage_Particle = 8,
		Usage_Light = 9,
		Usage_Colectable = 10,
		Usage_Message = 11,
		Usage_Door = 12,
		Usage_Sound = 13,
		Usage_PlayerDeath = 14
	};
	enum Camera
	{
		CamNone = 0,
		CamFirst = 1,
		CamDetached = 2,
		CamThird = 3
	};
	enum SpaceBar
	{
		SB_SelectionNone = 0,
		SB_SelectionJump = 1,
		SB_SelectionObject = 2
	};
	enum Folders
	{
		None = 0,
		Objects = 1,
		Buildings = 2,
		Characters = 3,
		Vegitation = 4,
		Tools = 5,
		Micellaneous = 6,
		Player_Setup = 7,
		Player_Start =8,
		Planes = 9,
		ChangeLevel = 10,
		TelePort = 11,
		TeleTarget = 12,
		Particles = 13,
		Lights = 14,
		Folder_Medikit = 15,
		Folder_Collectables = 16,
		Folder_Ammo = 17,
		Folder_Weapons = 18
	};

	enum Mode
	{
		GD = 0,
		VRD = 1
	};

	enum Attribute
	{
		Attribute_NO_Weapon = 0,
		Attribute_Ammo = 1,
		Attribute_Weapon = 2,
		Attribute_Medikit = 3,
		Attribute_Collectable = 4
	};

	enum Shape
	{
		NoShape = 0,
		Box = 1,
		Capsule = 2,
		Cylinder = 3,
		Sphere = 4,
		VolumeBox = 5
	};
	enum Type
	{
		Type_NoType = 0,
		Type_BasicStatic = 1,
		Type_BasicBody = 2,
		Type_NXS_Triangle = 3,
		Type_NXS_Convex = 4,
		Type_JustOgre = 5,
		Type_Volume = 6
	};
	enum Light_Type
	{
		LightType_Point = 0,
		LightType_Spot = 1,
		LightType_Direction = 2
	};
	enum Vector_Type
	{
		NoVector = 0,
		Vector_X = 1,
		Vector_Y = 2,
		Vector_Z = 3
	};
	enum FreeSpeed_Type
	{
		Slow = 0,
		Mid = 1,
		Fast = 2
	};
	enum Debug_Type
	{
		Debug_Off = 0,
		Debug_On= 1,
	};
	enum DropList_Type
	{
		DropList_None = 0,
		DropList_FreeSpeeds = 1,
		DropList_FlySpeeds = 2
	};
	enum OptionsProperties_Type
	{
		Options_None = 0,
		Options_Speeds = 1,
		Options_Debug = 2
	};
	enum FXList_Type
	{
		FXList_None = 0,
		FXList_General = 1,
		FXList_Scale = 2,
		FXList_Position = 3,
		FXList_Rotation = 4
	};
	enum Axis
	{
		Axis_None = 0,
		Axis_x = 1,
		Axis_y = 2,
		Axis_z = 3
	};
}