#define MAX_VERTICES 100000
#define MAX_POLYGONS 100000

enum LoadedFile
	{
		LoadedFile_None = 0,
		LoadedFile_Actor = 1,
		LoadedFile_Assimp = 2,
		LoadedFile_Ogre = 3,
		LoadedFile_STL = 4
	};

enum RenderMode
	{
		Render_As_None = 0,
		Render_As_Assimp = 1,
		Render_As_Actor = 2
	};

enum DisplayList
	{
		Display_None = 0,
		Display_Mesh = 1,
		Display_Faces = 2,
		Display_Cords = 3,
		Display_Normals = 4,
		Display_Keys = 5,
		Display_Bones = 6,
		Display_Memory = 7
	};

enum Buttons
{
	But1 = 300,// Crosshair
	But2 = 301,// Grid

	But3 = 402,
	But4 = 403,
	But5 = 404,
	But6 = 405,
	But7 = 406,
	But8 = 407,
	
	But9 = 400,
	But10 =401
};

typedef struct normal_type{float x,y,z;}normal_type;
typedef struct polygon_type{int a,b,c,Group;}polygon_type;
typedef struct Face_type{int a,b,c;}Face_type;
typedef struct Bone_Vert{float x,y,z;}Bone_Vert;
typedef struct Translation_Type{float X,Y,Z;}Translation_Type;
typedef struct rgb_Type{int Index;}rgb_Type;
typedef struct Char_type{char Name[256];}Char_type;
typedef struct mapcoord_type{float u,v;}mapcoord_type;
typedef struct int_type{int Index;}int_type;
typedef struct float_type{float Float1;}float_type;

typedef struct vertex_type
{
	float x,y,z;
}vertex_type;

typedef struct AABB_Type{ 
    vertex_type BB_Max[1];
	vertex_type BB_Min[1];
	vertex_type Size[1];
	vertex_type Centre[1];
	float radius;
} AABB_Type;

typedef	struct MeshGroup_Type									
{
	
	std::vector<vertex_type> vertex_Data;	// XYZ
	std::vector<polygon_type> Face_Data;	// ABC
	std::vector<normal_type> Normal_Data;
	std::vector<mapcoord_type> MapCord_Data;
	std::vector<int_type> FaceIndex_Data;

	std::vector<int_type> BoneIndex_Data;

	std::vector<int_type> BA_BoneIndex_Data;
	std::vector<int_type> BA_BoneVertexIndex_Data;
	std::vector<float_type> BA_Weight_Data;

	HBITMAP Base_Bitmap;					// Storage place for Mesh Group Main Image 
	HBITMAP Alpha_Bitmap;					// Storage place for Mesh Group Alpha Image 

	int BoneAssignMentCount;

	//------------------------------ 

	long BasePicWidth;
	long BasePicHeight;
	long AlphaPicWidth;
	long AlphaPicHeight;
	bool IsTextureValid;					// Has there been a good load of the texture Or is it Colour
	
	char GroupName[1024];					// Group Name
	char MaterialName[1024];				// Material File associated with this Mesh Group

	char Text_JustName[1024];			// Just Texture File Name ie Texture.bmp
	char Text_FileName[1024];			// Just Texture File Name ie Texture.bmp
	char Text_PathFileName[1024];		// Path and File Name ie c:/folder/Texture.bmp
	
	int GroupVertCount;						// Group Vertice Count 
	int GroupFaceCount;						// Group Face Count 
	int IndicesCount;						// Real Face indices count
	int MaterialIndex;
//	int EqIndex;
	bool HasAlpha;
	bool Bitmap_Loaded;
	int Soil_TextureIndex;

	bool HasBones;							// Does this Mesh Group Have Bones
	int BoneCount;							// How Many bones in this Mesh Group;

	bool IsDirty;							// Has this Mesh Group been altered in anyway

	// Bounding box Group
	vertex_type BB_Max[1];
	vertex_type BB_Min[1];
	vertex_type Size[1];
	vertex_type Centre[1];					// Centre of Bounding box XYZ
	
} MeshGroup_Type;


typedef struct test_type
{
	float x,y,z;
	char BoneName[200];
}test_type;


// *************************************************************************
// *							Bones		  					 		   *
// *************************************************************************
typedef struct Bone_Type { 
	int Parent;
	Bone_Vert Boneverts;
	char BoneName[200];
	Translation_Type TranslationStart;
}Bone_Type; 

// *************************************************************************
// *							Textures					  	 		   *
// *************************************************************************
typedef struct Texture_Type { 
	int TextureCount;
	int UsedTextureCount;
	rgb_Type MatIndex[100];
	Char_type TextureName[200];
}Texture_Type;

// *************************************************************************
// *							Open GL Textures			  	 		   *
// *************************************************************************
typedef	struct GLTextureInfo_Type									
{
	GLubyte	* imageData;									// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
	GLuint	type;	// Image Type (GL_RGB, GL_RGBA)
	unsigned char *data;
	geBitmap* Bitmap;                 
	char	MaterialName[200];
	int		ActorMaterialIndex;
	int		HasGEBitmap;
	int		GEWitdth;
	int		GEHeight;
	int		GEFormat;
	int		GEHasAlpha;
	int		GEHasColorKey;
	int		pSizeX;
	int		pSizeY;
	int		Tga;
	int		FileViewIndex;
	float	R;
	float	G;
	float	B;
} GLTextureInfo_Type;