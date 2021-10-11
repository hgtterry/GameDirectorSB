#pragma once

// Error codes
#define TPACKERROR_OK                0    
#define TPACKERROR_UNKNOWN           (TPACKERROR_OK - 1)    
#define TPACKERROR_WRITE             (TPACKERROR_OK - 2)
#define TPACKERROR_MEMORYALLOCATION  (TPACKERROR_OK - 3)
#define TPACKERROR_CREATEFILE        (TPACKERROR_OK - 4)

#pragma pack(1)

typedef struct TGAHEADER
{
	char	IDLength;
	char	ColorMapType;
	char	ImageType;
	Ogre::uint16	CMFirstEntry;
	Ogre::uint16	CMLength;
	char	CMEntrySize;
	Ogre::uint16	Xorigin;
	Ogre::uint16	Yorigin;
	Ogre::uint16	Width;
	Ogre::uint16	Height;
	char	PixelDepth;
	char	ImageDescriptor;
} TGAHEADER;

#pragma pack()

class VM_Textures
{
public:
	VM_Textures();
	~VM_Textures();

	int Genesis_WriteTGA(const char * pszFile, geBitmap *pBitmap);
	int Genesis_WriteToBmp(geBitmap *bmp, char *filename);
	bool Soil_Load_Texture(UINT textureArray[], LPSTR strFileName, int textureID);
	bool TexureToWinPreviewFullPath(int Index, char* FullPath);
	bool GetFormat(int cformat);
	void Strip_JustFileName(char *pString, char *FileName);
	bool CreateDummyTexture(void);
	bool Soil_DecodeTextures(int TextureID);
	void CreateTextureInfo(void);
	bool HBITMAP_TO_BmpFile(HBITMAP Bitmap, char* Filename, char* SaveFolder);

	bool Jpg_To_Tga24(char* File);
	bool Jpg_To_png24(char* File);

	//HBITMAP GetHBITMAPFromImageFile(const WCHAR* pFilePath);

	bool Ogre_LoadImage(const Ogre::String& tex_ext, const Ogre::String& texture_path, int Index);

	bool RemoveFile(char* Filename, char* Folder);

	char JustFileName[255];
	char GEFormatString[255];

	char TextureFileName[255];

	UINT  g_Texture[300];

protected:

	
};

