#pragma once

#define TPACKERROR_OK                0    
#define TPACKERROR_UNKNOWN           (TPACKERROR_OK - 1)    
#define TPACKERROR_WRITE             (TPACKERROR_OK - 2)
#define TPACKERROR_MEMORYALLOCATION  (TPACKERROR_OK - 3)
#define TPACKERROR_CREATEFILE        (TPACKERROR_OK - 4)

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

class ME_Textures
{
public:
	ME_Textures();
	~ME_Textures();

	bool HBITMAP_TO_BmpFile(HBITMAP Bitmap, char* Filename, char* SaveFolder);
	bool Jpg_To_Tga24(char* File);
	bool Jpg_To_png24(char* File);
	bool Bmp_To_Jpg(char* File);

	bool Soil_DecodeTextures(int TextureID);
	bool Soil_Load_Texture(UINT textureArray[], LPSTR strFileName, int textureID);
	bool TexureToWinPreviewFullPath(int Index, char* FullPath);
	void Strip_JustFileName(char *pString, char *FileName);

	bool DecompileTextures(char* Path);

	bool LoadDummyTexture(int Index);
	bool ChangeTexture_Model(void);
	bool Texture_To_Bmp(char* File);

	int Genesis_WriteTGA(const char * pszFile, geBitmap *pBitmap);
	int Genesis_WriteToBmp(geBitmap *bmp, char *filename);

	char JustFileName[MAX_PATH];
	char TextureFileName[MAX_PATH];
	UINT  g_Texture[300];

private:

};

