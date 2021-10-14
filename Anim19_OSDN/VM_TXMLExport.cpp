// TXMLExport.cpp: implementation of the TXMLExport class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GD19_App.h"
#include "VM_TXMLExport.h"
#pragma warning (disable : 4996)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VM_XMLExport::VM_XMLExport()
{
	TextureNum=0;
	DoSkell=0;

}

VM_XMLExport::~VM_XMLExport()
{

}

// *************************************************************************
// *			DecomPileTextures  30/03/04   					   	   	   *
// *************************************************************************
bool VM_XMLExport::DecompileTextures(int LFormat)
{

	//geBitmap* Bitmap;
	//geBitmap* Lock;
	//geBitmap_Info Info;
	//char PathAndFile[1024];
	//int Count=0;
	//float R,G,B=0;
	//const char *MatName;

	//
	//C_ProgBar->SetMainText("Decompiling Textures");

	//if(C_Render->SelectedTexture==-1)
	//{
	//	Count=geBody_GetMaterialCount(At->ActorDef_Memory->Body);

	//	int Loop=0;
	//	while (Loop<Count)
	//	{
	//		geBody_GetMaterial(At->ActorDef_Memory->Body,Loop,&MatName,&Bitmap,&R,&G,&B);
	//		C_ProgBar->Nudge();
	//		
	//		if(Bitmap)
	//		{
	//			
	//			
	//			if(geBitmap_HasAlpha(Bitmap))
	//			{
	//				
	//				strcpy(PathAndFile,MatName);
	//				strcat(PathAndFile,".tga");
	//				

	//			}
	//			else
	//			{
	//				
	//				strcpy(PathAndFile,MatName);
	//				strcat(PathAndFile,".bmp");
	//			}
	//			
	//			
	//			if(geBitmap_HasAlpha(Bitmap))
	//			{
	//				C_TetureLib->WriteTGA(PathAndFile,Bitmap);

	//				if(LFormat==0) //bmp
	//				{
	//					C_Convert->ExportTGAToPNG(PathAndFile);
	//				}

	//				if(LFormat==1) //dds
	//				{
	//					C_Convert->ExportTGAToDDS(PathAndFile);
	//				}

	//				if(LFormat==2) //png
	//				{
	//					C_Convert->ExportTGAToPNG(PathAndFile);;	
	//				}

	//				if(LFormat==3)//
	//				{
	//					C_Convert->ExportTGAToPNG(PathAndFile);;
	//				}
	//				if(LFormat==4)//tga
	//				{
	//					// tga by default
	//				}
	//				if(LFormat==5)//tga
	//				{
	//					C_Convert->ExportTGAToTIF(PathAndFile);
	//				}

	//			}
	//			else
	//			{
	//				geBitmap_LockForReadNative(Bitmap,&Lock,0,0);
	//				geBitmap_GetInfo(Lock,&Info,NULL);
	//					
	//					At->WriteToBmp(Lock,PathAndFile);
	//					
	//					geBitmap_UnLock(Lock);
	//					geBitmap_RefreshMips(Bitmap);

	//				if(LFormat==1)//dds
	//				{
	//					C_Convert->ExportBmpToDDS(PathAndFile);
	//				}
	//				if(LFormat==2)//png
	//				{
	//					C_Convert->ExportBmpToPNG(PathAndFile);
	//				}
	//				if(LFormat==3)//jpg
	//				{
	//					C_Convert->ExportBmpToJPG(PathAndFile);
	//				}
	//				if(LFormat==4)//tga
	//				{
	//					C_Convert->ExportBmpToTGA(PathAndFile);
	//				}
	//				if(LFormat==5)//tif
	//				{
	//					C_Convert->ExportBmpToTIF(PathAndFile);
	//				}
	//				
	//			}
	//			
	//		}

	//		Loop++;
	//		
	//	}
	//	
	//}
	//else
	//{
	//	C_ProgBar->Nudge();
	//	geBody_GetMaterial(At->ActorDef_Memory->Body,C_Render->SelectedTexture,&MatName,&Bitmap,&R,&G,&B);
	//		if(Bitmap)
	//		{
	//			
	//			
	//			if(geBitmap_HasAlpha(Bitmap))
	//			{
	//				
	//				strcpy(PathAndFile,MatName);
	//				strcat(PathAndFile,".tga");
	//			}
	//			else
	//			{
	//				
	//				strcpy(PathAndFile,MatName);
	//				strcat(PathAndFile,".bmp");
	//			}
	//			
	//			
	//			if(geBitmap_HasAlpha(Bitmap))
	//			{
	//				C_TetureLib->WriteTGA(PathAndFile,Bitmap);
	//				if(LFormat==0)// bmp
	//				{
	//					C_Convert->ExportTGAToPNG(PathAndFile);
	//				}

	//				if(LFormat==1) //dds
	//				{
	//					C_Convert->ExportTGAToDDS(PathAndFile);
	//				}
	//				if(LFormat==2) //png
	//				{
	//					C_Convert->ExportTGAToPNG(PathAndFile);	
	//				}

	//				if(LFormat==3)//jpg
	//				{
	//					C_Convert->ExportTGAToPNG(PathAndFile);
	//				}
	//				if(LFormat==4)//tga
	//				{
	//					// tga by default
	//				}
	//				if(LFormat==5)//tiff
	//				{
	//					C_Convert->ExportTGAToTIF(PathAndFile);
	//				}

	//				
	//			}
	//			else
	//			{
	//				geBitmap_LockForReadNative(Bitmap,&Lock,0,0);
	//				geBitmap_GetInfo(Lock,&Info,NULL);
	//					
	//					At->WriteToBmp(Lock,PathAndFile);
	//					
	//					geBitmap_UnLock(Lock);
	//					geBitmap_RefreshMips(Bitmap);
	//				if(LFormat==1)
	//				{
	//					C_Convert->ExportBmpToDDS(PathAndFile);
	//				}
	//				if(LFormat==2)
	//				{
	//					C_Convert->ExportBmpToPNG(PathAndFile);
	//				}
	//				if(LFormat==3)
	//				{
	//					C_Convert->ExportBmpToJPG(PathAndFile);
	//				}
	//				if(LFormat==4)
	//				{
	//					C_Convert->ExportBmpToTGA(PathAndFile);
	//				}
	//				if(LFormat==5)
	//				{
	//					C_Convert->ExportBmpToTIF(PathAndFile);
	//				}
	//			}
	//			
	//		}
	//}
 	
return 1;
}


// *************************************************************************
// *							GetTexure						   	   	   *
// *************************************************************************
char* VM_XMLExport::GetTexture(int Index)
{
	char Texture[256];
	/*geBitmap* Bitmap;

	float R,G,B=0;
	const char *MatName;

	int MatIndex=0;
	MatIndex = At->ActorDef_Memory->Body->SkinFaces[GE_BODY_HIGHEST_LOD].FaceArray[Index].MaterialIndex;

	if (MatIndex == -1)
	{
		strcpy(Texture,"-failed");
	}
	else
	{
		geBoolean test = geBody_GetMaterial(At->ActorDef_Memory->Body,MatIndex,&MatName,&Bitmap,&R,&G,&B);
		strcpy(Texture,MatName);
	}*/

	return Texture;
}

// *************************************************************************
// *							StartRenderToMesh			   		   	   *
// *************************************************************************
bool VM_XMLExport::StartRenderToMesh(int LTextureFormat)
{
	
//	int test=0;
//	test=CreateDirectoryMesh();
//	if (test==0)
//	{
//		return 0;
//	}
//
//	S_XMLStore[0]= new XMLStore_Type;
//	S_XMLStore[0]->SortedPolyCount=0;
//	
//
//	
//
//	C_ProgBar->StartNewProgressBar();
//	
//	
//	C_ProgBar->SetMainText("Decompiling Textures");
//
//
//	DecompileTextures(LTextureFormat);
//
//	char XmlFileName[256];
//	char XFIle[256];
//
//
//	strcpy(XmlFileName,S_File[0]->ActorFileName);
//
//	int Len=strlen(XmlFileName);
//	XmlFileName[Len-4]=0;
//
//
//
//	strcpy(XmlMeshFileName,XmlFileName);
//	strcpy(XmlScriptFileName,XmlFileName);
//	strcpy(XmlSkellFileName,XmlFileName);
//	strcpy(XmlSkellTagName,XmlFileName);
//
//
//	strcpy(XFIle,XmlFileName);
//
//	if(C_Render->SelectedTexture==-1)
//	{
//		strcat(XmlMeshFileName,".mesh.xml");
//		strcat(XmlSkellFileName,".skeleton.xml");
//		strcat(XmlSkellTagName,".skeleton");
//		
//		strcat(XmlScriptFileName,".material");
//	}
//	else
//	{
//		geBitmap* Bitmap;
//		int Count=0;
//		float R,G,B=0;
//		const char *MatName;
//		geBody_GetMaterial(At->ActorDef_Memory->Body,C_Render->SelectedTexture,&MatName,&Bitmap,&R,&G,&B);
//		
//		strcat(XmlMeshFileName,"_");
//		strcat(XmlScriptFileName,"_");
//		strcat(XmlSkellTagName,"_");
//
//		strcat(XmlMeshFileName,MatName);
//		strcat(XmlScriptFileName,MatName);
//		strcat(XmlSkellTagName,MatName);
//
//		strcpy(XFIle,XmlMeshFileName);
//
//		strcat(XmlMeshFileName,".mesh.xml");
//		strcat(XmlScriptFileName,".material");
//		strcat(XmlSkellFileName,".skeleton.xml");
//		strcat(XmlSkellTagName,".skeleton");
//	}
//
//
//	WritePolyFile = fopen(XmlMeshFileName, "wt");
//	if(!WritePolyFile) 
//	{
//		return 0;
//	}
//
//	fprintf(WritePolyFile, "%s\n","<mesh>");
//	fprintf(WritePolyFile,"%s\n","    <submeshes>");
//
//	if(C_Render->SelectedTexture==-1)
//	{
//		
//
//	//	int texturecount=geBody_GetMaterialCount(At->ActorDef_Memory->Body);
//		int texturecount=Texture[0]->UsedTextureCount;
//		int Count=0;
//		while (Count<texturecount)
//		{
//			TextureNum=Count;
//			RenderToXML();
//			WriteNewXML();
//			Count++;
//		}
//	
//	}
//	else
//	{
//		
//		TextureNum=C_Render->SelectedTexture;
//		RenderToXML();
//		WriteNewXML();
//	}
//
//
//	fprintf(WritePolyFile, "%s\n","    </submeshes>");
//	if(DoSkell==1)
//	{
//	fprintf(WritePolyFile, "%s%s%s\n","    <skeletonlink name=\"",XmlSkellTagName,"\" />");
//	}
//	fprintf(WritePolyFile, "%s\n","</mesh>");
//
//
//	fclose(WritePolyFile);
//
//	char SaveName[256];
//	strcpy(SaveName,XFIle);
//	char tran[256];
//	strcpy(tran,RootDirectory);
//	strcat(tran,"\\");
//	strcat(tran,XFIle);
//	strcat(tran,".mesh.xml");
//
//	strcat(XFIle,".mesh.xml");
//
//	CopyFile(XFIle,tran,0);
//
//	char Texe[256];
//	strcpy(Texe,RootDirectory);
//	strcat(Texe,"\\");
//	strcat(Texe,"OgreXmlConverter.exe");
//	strcat(Texe," ");
//	strcat(Texe,XFIle);
//	
//
//	C_ProgBar->SetMainText("Creating .mesh File");
//	C_ProgBar->SetProcessText(XmlMeshFileName);
//
//	C_ProgBar->Nudge();
//	STARTUPINFO si;
//    PROCESS_INFORMATION pi;
//
//    ZeroMemory( &si, sizeof(si) );
//    si.cb = sizeof(si);
//	si.dwFlags=STARTF_USESHOWWINDOW;
//	si.wShowWindow=SW_HIDE;
//
//
//	if( !CreateProcess(NULL, // No module name (use command line). 
//        Texe, // Command line. 
//        NULL,             // Process handle not inheritable. 
//        NULL,             // Thread handle not inheritable. 
//        FALSE,            // Set handle inheritance to FALSE. 
//        0,                // No creation flags. 
//        NULL,             // Use parent's environment block. 
//        NULL,             // Use parent's starting directory. 
//        &si,              // Pointer to STARTUPINFO structure.
//        &pi )             // Pointer to PROCESS_INFORMATION structure.
//    ) 
//    {
//        App->Say( "Cant find Ogre.dll" );
//    }
//	else
//	{
//
//	WaitForSingleObject( pi.hProcess, INFINITE );
//
//    // Close process and thread handles. 
//    CloseHandle( pi.hProcess );
//    CloseHandle( pi.hThread );
//	}
//	
//	WriteScript(LTextureFormat);
//	if(DoSkell==1)
//	{
//		WriteSkellFile();
//	}
//	C_ProgBar->Nudge();
//	strcpy(XFIle,SaveName);
//	char Stran[256];
//	strcpy(Stran,RootDirectory);
//	strcat(Stran,"\\");
//	strcat(Stran,XFIle);
//	strcat(Stran,".skeleton.xml");
//
//	strcat(XFIle,".skeleton.xml");
//
//	CopyFile(XFIle,Stran,0);
//
//	char STexe[256];
//	strcpy(STexe,RootDirectory);
//	strcat(STexe,"\\");
//	strcat(STexe,"OgreXmlConverter.exe");
//	strcat(STexe," ");
//	strcat(STexe,XFIle);
//
//	
//	C_ProgBar->SetMainText("Creating .skeleton File");
//	C_ProgBar->SetProcessText(XmlSkellTagName);
//
//	C_ProgBar->Nudge();
//	STARTUPINFO Ssi;
//    PROCESS_INFORMATION Spi;
//
//    ZeroMemory( &Ssi, sizeof(Ssi) );
//    Ssi.cb = sizeof(Ssi);
//	Ssi.dwFlags=STARTF_USESHOWWINDOW;
//	Ssi.wShowWindow=SW_HIDE;
//
//
//	if( !CreateProcess( NULL, // No module name (use command line). 
//        STexe, // Command line. 
//        NULL,             // Process handle not inheritable. 
//        NULL,             // Thread handle not inheritable. 
//        FALSE,            // Set handle inheritance to FALSE. 
//        IDLE_PRIORITY_CLASS,                // No creation flags. 
//        NULL,             // Use parent's environment block. 
//        NULL,             // Use parent's starting directory. 
//        &Ssi,              // Pointer to STARTUPINFO structure.
//        &Spi )             // Pointer to PROCESS_INFORMATION structure.
//    ) 
//    {
//         App->Say( "Cant find Ogre.dll" );
//    }
//	else
//	{
//
//	
//	C_ProgBar->Nudge();
//	MSG msg; 
//	int wait=1;
//	int cc=0;
//	while (wait==1)	
//	{
//		if (WaitForSingleObject( Spi.hProcess,100 )==WAIT_TIMEOUT)
//		{
//			C_ProgBar->Nudge();
//			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//			{
//				TranslateMessage(&msg);
//				DispatchMessage(&msg);
//			}
//			
//			wait=1;
//		}
//		else
//		{
//			wait =0;
//		}
//	}		
//
//
//    // Close process and thread handles. 
//    CloseHandle( Spi.hProcess );
//    CloseHandle( Spi.hThread );
//	}
//	
////	DestroyWindow(ProgressBarHwnd);	
////	ShellExecute (0, "open", "OgreXmlConverter.exe",XFIle,RootDirectory, SW_SHOW);
//
//	C_ProgBar->Nudge();
//	if(S_XMLStore[0])
//	{ 
//		delete S_XMLStore[0];
//		S_XMLStore[0]=NULL;
//		
//	}
//
//	char Back[256];
//	strcpy(Back,RootDirectory);
//	strcat(Back,"\\");
//	strcat(Back,SaveName);
//	strcat(Back,".mesh");
//
//	char origBack[256];
//	strcpy(origBack,SaveName);
//	strcat(origBack,".mesh");
//
//	strcpy(OgreMeshFileName,origBack);
//
//	char TempFileName[256];
//	strcpy(TempFileName,OgreSkellMeshDir);
//	strcat(TempFileName,"\\");
//	strcat(TempFileName,OgreMeshFileName);
//
////	CopyFile(Back,origBack,0);
//	C_ProgBar->Nudge();
//	remove(tran);
//	remove(Stran);
//	remove(XmlMeshFileName);
//	remove(XmlSkellFileName);
//	remove("OgreXMLConverter.log");
//	if (DontCopy==1)
//	{
//		
//		test = App->WinCheckForFile(OgreSkellMeshDir,origBack);
//	
//		if (test==1)
//		{
//			test=MessageBox(Fdlg,"mesh and skeleton files already exsist in selected Orge Folders\n( do you want to Overwrite them )","File Exsists",MB_OKCANCEL|MB_ICONWARNING);
//			
//			if (test==IDCANCEL)
//			{
//				DontCopy=0;
//			}
//			
//			if (test==IDOK)
//			{
//			remove(TempFileName);
//	
//			C_ProgBar->SetMainText("Copying .mesh to Orge folder");
//			CopyFile(OgreMeshFileName,TempFileName,0);
//
//			}
//		}
//		else
//		{
//	
//			C_ProgBar->SetMainText("Copying .mesh to Orge folder");
//			CopyFile(OgreMeshFileName,TempFileName,0);
//		}
//		
//			
//	}
//
//	C_ProgBar->Nudge();
//	strcpy(Back,RootDirectory);
//	strcat(Back,"\\");
//	strcat(Back,SaveName);
//	strcat(Back,".skeleton");
//
//	
//	strcpy(origBack,SaveName);
//	strcat(origBack,".skeleton");
//
//	strcpy(OgreMeshFileName,origBack);
//
//
//	strcpy(TempFileName,OgreSkellMeshDir);
//	strcat(TempFileName,"\\");
//	strcat(TempFileName,OgreMeshFileName);
//	//------------------------------------------------
//	if (DontCopy==1)
//	{
//		C_ProgBar->SetMainText("Copying .skeleton to Orge folder");
//		remove(TempFileName);
//		CopyFile(OgreMeshFileName,TempFileName,0);
//
//	}
//	C_ProgBar->Nudge();
//	strcpy(Back,RootDirectory);
//	strcat(Back,"\\");
//	strcat(Back,SaveName);
//	strcat(Back,".material");
//
//	
//	strcpy(origBack,SaveName);
//	strcat(origBack,".material");
//
//	strcpy(OgreScriptFileName,origBack);
//
//
//	strcpy(TempFileName,OgreScriptDir);
//	strcat(TempFileName,"\\");
//	strcat(TempFileName,OgreScriptFileName);
//	C_ProgBar->Nudge();
//	if (DontCopy==1)
//	{
//		C_ProgBar->SetMainText("Copying .script to Orge folder");
//		CopyFile(OgreScriptFileName,TempFileName,0);
//
//	}
//	C_ProgBar->Nudge();
//	if (DontCopy==1)
//	{
//		C_ProgBar->SetMainText("Copying .textures to Orge folder");
//		_chdir(OgreTextureDir);
//		DecompileTextures(LTextureFormat);
//
//	}
//	
//	C_ProgBar->Close();
//
//	strcpy(AnswerText,"Your Actor has been converted to the Ogre Format");
//	App->Say("Converted");
	return 1;
}


// *************************************************************************
// *							StartRenderToXML			   		   	   *
// *************************************************************************
bool VM_XMLExport::StartRenderToXML(int LTextureFormat)
{
	
	//int test=0;
	//test=CreateDirectory();
	//if (test==0)
	//{
	//	return 0;
	//}

	S_XMLStore[0]= new XMLStore_Type;
	S_XMLStore[0]->SortedPolyCount=0;
	
	//DecompileTextures(LTextureFormat);

	char XmlFileName[256];
	char XFIle[256];


	strcpy(XmlFileName,App->CL_Vm_Model->FileName);

	int Len=strlen(XmlFileName);
	XmlFileName[Len-4]=0;



	strcpy(XmlMeshFileName,XmlFileName);
	strcpy(XmlScriptFileName,XmlFileName);
	strcpy(XmlSkellFileName,XmlFileName);
	strcpy(XmlSkellTagName,XmlFileName);


	strcpy(XFIle,XmlFileName);

	//if(C_Render->SelectedTexture==-1)
	//{
	//	strcat(XmlMeshFileName,".mesh.xml");
	//	strcat(XmlSkellFileName,".skeleton.xml");
	//	strcat(XmlSkellTagName,".skeleton");
	//	
	//	strcat(XmlScriptFileName,".material");
	//}
	//else
	//{
		/*geBitmap* Bitmap;
		int Count=0;
		float R,G,B=0;
		const char *MatName;
		geBody_GetMaterial(At->ActorDef_Memory->Body,C_Render->SelectedTexture,&MatName,&Bitmap,&R,&G,&B);*/
		
		strcat(XmlMeshFileName,"_");
		strcat(XmlScriptFileName,"_");
		strcat(XmlSkellTagName,"_");

		//strcat(XmlMeshFileName,MatName);
		//strcat(XmlScriptFileName,MatName);
		//strcat(XmlSkellTagName,MatName);

		strcpy(XFIle,XmlMeshFileName);

		strcat(XmlMeshFileName,".mesh.xml");
		strcat(XmlScriptFileName,".material");
		strcat(XmlSkellFileName,".skeleton.xml");
		strcat(XmlSkellTagName,".skeleton");
	//}


	WritePolyFile = fopen(XmlMeshFileName, "wt");
	if(!WritePolyFile) 
	{
		return 0;
	}

	fprintf(WritePolyFile, "%s\n", "<mesh>");
	fprintf(WritePolyFile, "%s\n", "    <submeshes>");

	int Count = 0;
	while (Count < App->CL_Vm_Model->GroupCount)
	{
		RenderToXML(Count);
		WriteNewXML(Count);
		Count++;
	}


	fprintf(WritePolyFile, "%s\n","    </submeshes>");
	if(DoSkell==1)
	{
	fprintf(WritePolyFile, "%s%s%s\n","    <skeletonlink name=\"",XmlSkellTagName,"\" />");
	}
	fprintf(WritePolyFile, "%s\n","</mesh>");


	fclose(WritePolyFile);

	//WriteScript(LTextureFormat);
	//if(DoSkell==1)
	//{
	//	WriteSkellFile();
	//}
	

	if(S_XMLStore[0])
	{ 
		delete S_XMLStore[0];
		S_XMLStore[0]=NULL;
		
	}
	//remove("OgreXMLConverter.log");
	
	App->Say("Converted");
	return 1;
}
// *************************************************************************
// *							RenderToXML					   		   	   *
// *************************************************************************
bool VM_XMLExport::RenderToXML(int GroupIndex)
{
	int FaceCount = 0;
	int XMLCount=0;
	int Face=0;

	int A = 0;
	int B = 0;
	int C = 0;
	
	while (FaceCount < App->CL_Vm_Model->S_MeshGroup[GroupIndex]->GroupFaceCount)
	{
		A = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Face_Data[FaceCount].a;
		B = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Face_Data[FaceCount].b;
		C = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Face_Data[FaceCount].c;

		// first vector in face and vertic + normal and uv 
		S_XMLStore[0]->XMLvertex[XMLCount].x = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->vertex_Data[A].x;
		S_XMLStore[0]->XMLvertex[XMLCount].y = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->vertex_Data[A].y;
		S_XMLStore[0]->XMLvertex[XMLCount].z = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->vertex_Data[A].z;

		S_XMLStore[0]->mapcoord[XMLCount].u = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->MapCord_Data[A].u;
		S_XMLStore[0]->mapcoord[XMLCount].v = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->MapCord_Data[A].v;

		S_XMLStore[0]->XMLnormal[XMLCount].x = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Normal_Data[A].x;
		S_XMLStore[0]->XMLnormal[XMLCount].y = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Normal_Data[A].y;
		S_XMLStore[0]->XMLnormal[XMLCount].z = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Normal_Data[A].z;

		S_XMLStore[0]->BoneIndex[XMLCount] = 0;// SN[cube.polygon[Count].a].BoneIndex;
		S_XMLStore[0]->XMLpolygon[Face].a = XMLCount;
		XMLCount++;

		// second vector in face and vertic + normal and uv 
		S_XMLStore[0]->XMLvertex[XMLCount].x = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->vertex_Data[B].x;
		S_XMLStore[0]->XMLvertex[XMLCount].y = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->vertex_Data[B].y;
		S_XMLStore[0]->XMLvertex[XMLCount].z = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->vertex_Data[B].z;

		S_XMLStore[0]->mapcoord[XMLCount].u = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->MapCord_Data[B].u;
		S_XMLStore[0]->mapcoord[XMLCount].v = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->MapCord_Data[B].v;

		S_XMLStore[0]->XMLnormal[XMLCount].x = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Normal_Data[B].x;
		S_XMLStore[0]->XMLnormal[XMLCount].y = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Normal_Data[B].y;
		S_XMLStore[0]->XMLnormal[XMLCount].z = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Normal_Data[B].z;

		S_XMLStore[0]->BoneIndex[XMLCount] = 0;// SN[cube.polygon[Count].a].BoneIndex;
		S_XMLStore[0]->XMLpolygon[Face].b = XMLCount;
		XMLCount++;

		// third vector in face and vertic + normal and uv 
		S_XMLStore[0]->XMLvertex[XMLCount].x = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->vertex_Data[C].x;
		S_XMLStore[0]->XMLvertex[XMLCount].y = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->vertex_Data[C].y;
		S_XMLStore[0]->XMLvertex[XMLCount].z = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->vertex_Data[C].z;

		S_XMLStore[0]->mapcoord[XMLCount].u = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->MapCord_Data[C].u;
		S_XMLStore[0]->mapcoord[XMLCount].v = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->MapCord_Data[C].v;

		S_XMLStore[0]->XMLnormal[XMLCount].x = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Normal_Data[C].x;
		S_XMLStore[0]->XMLnormal[XMLCount].y = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Normal_Data[C].y;
		S_XMLStore[0]->XMLnormal[XMLCount].z = App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Normal_Data[C].z;

		S_XMLStore[0]->BoneIndex[XMLCount] = 0;// SN[cube.polygon[Count].a].BoneIndex;
		S_XMLStore[0]->XMLpolygon[Face].c = XMLCount;
		XMLCount++;
		Face++;

		FaceCount++;
	}

	S_XMLStore[0]->SXMLCount = XMLCount;

	return 1;
}

// *************************************************************************
// *							WriteNewXML					   		   	   *
// *************************************************************************
bool VM_XMLExport::WriteNewXML(int GroupIndex)
{
	WriteSubMesh(GroupIndex);

	fprintf(WritePolyFile, "%s\n","                </vertexbuffer>");
	fprintf(WritePolyFile, "%s\n","            </geometry>");
	fprintf(WritePolyFile, "%s\n","        </submesh>");

	return 1;
}

// *************************************************************************
// *							WriteSubMesh				   		   	   *
// *************************************************************************
bool VM_XMLExport::WriteSubMesh(int GroupIndex)
{
	float x=0;
	float y=0;
	float z=0;
	
	int a=0;
	int b=0;
	int c=0;

	char MatName[256];
	
	float V=0;
	int NewCount=S_XMLStore[0]->SXMLCount;
	int PolyCount=S_XMLStore[0]->SXMLCount/3;
	int VertCount=S_XMLStore[0]->SXMLCount;
	int Count=0;


	//------------------------------- texture

	char SubMesh[256];
	strcpy(SubMesh,"        <submesh material=\"");
	strcpy(MatName,App->CL_Vm_Model->S_MeshGroup[GroupIndex]->MaterialName);
	
	fprintf(WritePolyFile,"%s%s%s %s\n",SubMesh,MatName,"\" usesharedvertices=\"false\"","use32bitindexes=\"false\" operationtype=\"triangle_list\">");
	
	//------------------------------- PolyGons
	fprintf(WritePolyFile, "%s%i%s\n","            <faces count=\"",PolyCount,"\">");
	
	while (Count<NewCount/3)
	{
		a =S_XMLStore[0]->XMLpolygon[Count].a;
		b =S_XMLStore[0]->XMLpolygon[Count].b;
		c =S_XMLStore[0]->XMLpolygon[Count].c;
		
		fprintf(WritePolyFile, "%s%i%s%i%s%i%s\n","                <face v1=\"",a,"\" v2=\"",b,"\" v3=\"",c,"\" />");
		Count++;
	}
	
	fprintf(WritePolyFile, "%s\n","            </faces>");
	
	//------------------------------- Vertices
	fprintf(WritePolyFile, "%s%i%s\n","            <geometry vertexcount=\"",VertCount,"\">");
	fprintf(WritePolyFile, "%s\n","                <vertexbuffer positions=\"true\" normals=\"true\" texture_coord_dimensions_0=\"2\" texture_coords=\"1\">");
	
	Count=0;
	while (Count<NewCount)
	{
		fprintf(WritePolyFile, "%s\n","                    <vertex>");
		x=S_XMLStore[0]->XMLvertex[Count].x;
		y=S_XMLStore[0]->XMLvertex[Count].y;
		z=S_XMLStore[0]->XMLvertex[Count].z;
		
		u=S_XMLStore[0]->mapcoord[Count].u;
		V=S_XMLStore[0]->mapcoord[Count].v;
		
		v=1-V; // Swop V From RF to Ogre format
		
		nx=S_XMLStore[0]->XMLnormal[Count].x;
		ny=S_XMLStore[0]->XMLnormal[Count].y;
		nz=S_XMLStore[0]->XMLnormal[Count].z;
		
		fprintf(WritePolyFile, "%s%f%s%f%s%f%s\n","                        <position x=\"",x,"\" y=\"",y,"\" z=\"",z,"\" />");	
		fprintf(WritePolyFile, "%s%f%s%f%s%f%s\n","                        <normal x=\"",nx,"\" y=\"",ny,"\" z=\"",nz,"\" />");
		fprintf(WritePolyFile, "%s%f%s%f%s\n","                        <texcoord u=\"",u,"\" v=\"",v,"\" />");
		
		fprintf(WritePolyFile, "%s\n","                    </vertex>");
		Count++;
		
	}

	return 1;
}

// *************************************************************************
// *						WriteBoneAssigenment			   		   	   *
// *************************************************************************
bool VM_XMLExport::WriteBoneAssigenment()
{
	//fprintf(WritePolyFile, "%s\n","                </vertexbuffer>");
	//fprintf(WritePolyFile, "%s\n","             </geometry>");
	//fprintf(WritePolyFile, "%s\n","             <boneassignments>");

	//int Bone=0;
	//int w=1;
	//int VertCount=S_XMLStore[0]->SXMLCount;
	//int Count=0;
	//while (Count<VertCount)
	//{
	//	//AnimateProgressBar();
	//	Bone=S_XMLStore[0]->BoneIndex[Count];
	//	fprintf(WritePolyFile, "%s%i%s%i%s%i%s\n","                <vertexboneassignment vertexindex=\"",Count,"\" boneindex=\"",Bone,"\" weight=\"",w,"\" />");	
	//	Count++;
	//}

	//fprintf(WritePolyFile, "%s\n","              </boneassignments>");
	
	return 1;
}

// *************************************************************************
// *							CreateDirectory				   		   	   *
// *************************************************************************
bool VM_XMLExport::CreateDirectory()
{
	/*char NewDirectory[200];
	strcpy(NewDirectory,S_File[0]->ActorFileName);
	
	int Len=strlen(NewDirectory);
	NewDirectory[Len-4]=0;

	if(C_Render->SelectedTexture==-1)
	{
		
	}
	else
	{
		geBitmap* Bitmap;
		int Count=0;
		float R,G,B=0;
		const char *MatName;
		geBody_GetMaterial(At->ActorDef_Memory->Body,C_Render->SelectedTexture,&MatName,&Bitmap,&R,&G,&B);
				
		strcat(NewDirectory,"_");
		strcat(NewDirectory,MatName);
	}


	strcat(NewDirectory,"_XML");
	
	strcat(szSelectedDir,"\\");
	strcat(szSelectedDir,NewDirectory);
	
	if(_mkdir(szSelectedDir)==0)
	{
		strcat(DecompileFolder,"\\");
		strcat(DecompileFolder,szSelectedDir);
		_chdir(szSelectedDir);
		
	}
	else
	{
		int test=0;
		test=DirectoryControl();
		if (test==0)
		{
			return 0;
		}
	}*/
	
	return 1;
}

// *************************************************************************
// *							CreateDirectoryMesh			   		   	   *
// *************************************************************************
bool VM_XMLExport::CreateDirectoryMesh()
{
	/*char NewDirectory[200];
	strcpy(NewDirectory,S_File[0]->ActorFileName);
	
	int Len=strlen(NewDirectory);
	NewDirectory[Len-4]=0;

	if(C_Render->SelectedTexture==-1)
	{
		
	}
	else
	{
		geBitmap* Bitmap;
		int Count=0;
		float R,G,B=0;
		const char *MatName;
		geBody_GetMaterial(At->ActorDef_Memory->Body,C_Render->SelectedTexture,&MatName,&Bitmap,&R,&G,&B);
				
		strcat(NewDirectory,"_");
		strcat(NewDirectory,MatName);
	}


	strcat(NewDirectory,"_Mesh");
	
	strcat(szSelectedDir,"\\");
	strcat(szSelectedDir,NewDirectory);
	
	if(_mkdir(szSelectedDir)==0)
	{
		strcat(DecompileFolder,"\\");
		strcat(DecompileFolder,szSelectedDir);
		_chdir(szSelectedDir);
		
	}
	else
	{
		int test=0;
		test=DirectoryControl();
		if (test==0)
		{
			return 0;
		}
	}*/
	
	return 1;
}

// *************************************************************************
// *						DirectoryControl				   		   	   *
// *************************************************************************
bool VM_XMLExport::DirectoryControl()
{
	/*int test=0;
	test=MessageBox(Fdlg,"   Directory exsists ovewrite \n( All previous data will be lost )","Directory Exsists",MB_OKCANCEL|MB_ICONWARNING);
	
	if (test==IDCANCEL)
	{
		return 0;
	}

	if (test==IDOK)
	{
		strcat(DecompileFolder,"\\");
		strcat(DecompileFolder,szSelectedDir);
		_chdir(szSelectedDir);
		
		WIN32_FIND_DATA ffd;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		
		hFind = FindFirstFile("*.*",&ffd);
		remove(ffd.cFileName);
		
		while (FindNextFile(hFind, &ffd) != 0)
		{
			
			remove(ffd.cFileName);
		}
		
		FindClose(hFind);
		
		return 1;
	}*/
	return 1;
}

// *************************************************************************
// *							WriteScript					   		   	   *
// *************************************************************************
bool VM_XMLExport::WriteScript(int LFormat)
{
//	WriteSFile = fopen(XmlScriptFileName, "wt");
//	if(!WritePolyFile) 
//	{
//		return 0;
//	}
//
//	int IsItAlpha=0;
//	char File[256];
//	geBitmap* Bitmap;
//	int Count=0;
//	float R,G,B=0;
//	const char *MatName;
//	char Indextexture[256];
//	int index=0;
////	int texturecount=geBody_GetMaterialCount(At->ActorDef_Memory->Body);
//	int texturecount=Texture[0]->UsedTextureCount;;
//
//	if(C_Render->SelectedTexture==-1)
//	{
//		while (Count<texturecount)
//		{
//			//AnimateProgressBar();
//			geBody_GetMaterial(At->ActorDef_Memory->Body,Count,&MatName,&Bitmap,&R,&G,&B);
//
//			strcpy(Indextexture,MatName);
//			index=GetTexureInfoIndex(Indextexture);
//
//			fprintf(WritePolyFile, "%s %s\n","material",MatName);
//
//			if(geBitmap_HasAlpha(Bitmap))
//			{ 
//					IsItAlpha=1;
//					if (LFormat==0)
//					{
//						strcpy(File,MatName);
//						strcat(File,".png");	
//					}
//
//					if (LFormat==1)
//					{
//						strcpy(File,MatName);
//						strcat(File,".dds");
//					}
//					if (LFormat==2)
//					{
//						strcpy(File,MatName);
//						strcat(File,".png");
//					}
//
//					if (LFormat==3)
//					{
//						strcpy(File,MatName);
//						strcat(File,".png");
//					}
//					if (LFormat==4)
//					{
//						strcpy(File,MatName);
//						strcat(File,".tga");
//					}
//					if (LFormat==5)
//					{
//						strcpy(File,MatName);
//						strcat(File,".tif");
//					}
//					
//				}
//				else
//				{
//					
//					strcpy(File,MatName);
//
//					if (LFormat==0)
//					{
//						strcat(File,".bmp");
//					}
//					if (LFormat==1)
//					{
//						strcat(File,".dds");
//					}
//
//					if (LFormat==2)
//					{
//						strcat(File,".png");
//					}
//					if (LFormat==3)
//					{
//						strcat(File,".jpg");
//					}
//					if (LFormat==4)
//					{
//						strcat(File,".tga");
//					}
//					if (LFormat==5)
//					{
//						strcat(File,".tif");
//					}
//				}
//			
//			fprintf(WritePolyFile, "%s\n",   "{");
//			fprintf(WritePolyFile, "%s\n",   "    technique");
//			fprintf(WritePolyFile, "%s\n",   "    {");
//
//			fprintf(WritePolyFile, "%s\n",   "         pass");
//			fprintf(WritePolyFile, "%s\n",   "         {");
//
//			if (S_AllTexturesInfo[index]->CullNone==1)
//			{
//			fprintf(WritePolyFile, "%s\n",   "                cull_hardware none");
//			fprintf(WritePolyFile, "%s\n",   "                cull_software none");
//
//			}
//			if (IsItAlpha==1)
//			{
//			int num=0;
//			num=S_AllTexturesInfo[index]->AlphaRejection;
//			fprintf(WritePolyFile, "%s %i\n",   "                alpha_rejection greater",num);
//			IsItAlpha=0;
//			}
//
//			fprintf(WritePolyFile, "%s\n",   "             texture_unit");
//			fprintf(WritePolyFile, "%s\n",   "             {");
//
//
//			fprintf(WritePolyFile, "%s %s\n","                 texture",File);
//
//			fprintf(WritePolyFile, "%s\n",   "             }");		
//			fprintf(WritePolyFile, "%s\n",   "         }");
//			fprintf(WritePolyFile, "%s\n",   "    }");
//			fprintf(WritePolyFile, "%s\n",   "}");
//
//			Count++;
//		}
//
//		
//	}
//	else
//	{
//		C_ProgBar->Nudge();
//		geBody_GetMaterial(At->ActorDef_Memory->Body,TextureNum,&MatName,&Bitmap,&R,&G,&B);
//
//			fprintf(WritePolyFile, "%s %s\n","material",MatName);
//
//			if(geBitmap_HasAlpha(Bitmap))
//				{
//					
//					IsItAlpha=1;
//					if (LFormat==0)
//					{
//						strcpy(File,MatName);
//						strcat(File,".png");	
//					}
//
//					if (LFormat==1)
//					{
//						strcpy(File,MatName);
//						strcat(File,".dds");
//					}
//					if (LFormat==2)
//					{
//						strcpy(File,MatName);
//						strcat(File,".png");
//					}
//
//					if (LFormat==3)
//					{
//						strcpy(File,MatName);
//						strcat(File,".png");
//					}
//					if (LFormat==4)
//					{
//						strcpy(File,MatName);
//						strcat(File,".tga");
//					}
//					if (LFormat==5)
//					{
//						strcpy(File,MatName);
//						strcat(File,".tif");
//					}
//				}
//				else
//				{
//					
//					strcpy(File,MatName);
//
//					if (LFormat==0)
//					{
//						strcat(File,".bmp");
//					}
//					if (LFormat==1)
//					{
//						strcat(File,".dds");
//					}
//
//					if (LFormat==2)
//					{
//						strcat(File,".png");
//					}
//					if (LFormat==3)
//					{
//						strcat(File,".jpg");
//					}
//					if (LFormat==4)
//					{
//						strcat(File,".tga");
//					}
//					if (LFormat==5)
//					{
//						strcat(File,".tif");
//					}
//				}
//			
//			fprintf(WritePolyFile, "%s\n",   "{");
//			fprintf(WritePolyFile, "%s\n",   "    technique");
//			fprintf(WritePolyFile, "%s\n",   "    {");
//
//			fprintf(WritePolyFile, "%s\n",   "         pass");
//			fprintf(WritePolyFile, "%s\n",   "         {");
//
//			if (S_AllTexturesInfo[index]->CullNone==1)
//			{
//			fprintf(WritePolyFile, "%s\n",   "                cull_hardware none");
//			fprintf(WritePolyFile, "%s\n",   "                cull_software none");
//
//			}
//			if (IsItAlpha==1)
//			{
//			int num=0;
//			num=S_AllTexturesInfo[index]->AlphaRejection;
//			fprintf(WritePolyFile, "%s %i\n",   "                alpha_rejection greater",num);
//			IsItAlpha=0;
//			}
//
//			fprintf(WritePolyFile, "%s\n",   "             texture_unit");
//			fprintf(WritePolyFile, "%s\n",   "             {");
//
//
//			fprintf(WritePolyFile, "%s %s\n","                 texture",File);
//
//			fprintf(WritePolyFile, "%s\n",   "             }");		
//			fprintf(WritePolyFile, "%s\n",   "         }");
//			fprintf(WritePolyFile, "%s\n",   "    }");
//			fprintf(WritePolyFile, "%s\n",   "}");
//		
//	}
//		
//	fclose(WriteSFile);

	return 1;
}

// *************************************************************************
// *							WriteScript					   		   	   *
// *************************************************************************
bool VM_XMLExport::GetTexureInfoIndex(char *LTexture)
{
	/*geBitmap* Bitmap;
	float R,G,B=0;
	const char *MatName;
	int Count=0;
	int test=0;
	int textcount=geBody_GetMaterialCount(At->ActorDef_Memory->Body);
	char Temp[256];
	while (Count<textcount)
	{
		C_ProgBar->Nudge();
		geBody_GetMaterial(At->ActorDef_Memory->Body,Count,&MatName,&Bitmap,&R,&G,&B);
		strcpy(Temp,MatName);
		test=strcmp(LTexture,Temp);

		if (test==0)
			{
			
				return Count;
				break;
				
			}
		Count++;

	}*/
	return 1;
}

// *************************************************************************
// *							WriteSkellFile				   		   	   *
// *************************************************************************
bool VM_XMLExport::WriteSkellFile()
{
	//WriteSkFile = fopen(XmlSkellFileName, "wt");
	//if(!WritePolyFile) 
	//{
	//	return 0;
	//}

	//C_ProgBar->SetMainText("Writing XML Skeleton File");
	//fprintf(WriteSkFile,"%s\n","<skeleton>");
	//fprintf(WriteSkFile,"%s\n","    <bones>");

	//WriteBoneMatrix();

	//fprintf(WriteSkFile,"%s\n","    </bones>");

	//fprintf(WriteSkFile,"%s\n","    <bonehierarchy>");

	//WriteHiracy();

	//fprintf(WriteSkFile,"%s\n","    </bonehierarchy>");


	//if (DoMotion==1)
	//{
	//	const char *LTempMotionName;
	//	fprintf(WriteSkFile,"%s\n","    <animations>");
	//	
	//
	//int MotionCount=0;
	//
	//int ClockTime=0;
	//while(MotionCount<Counters[0]->MotionCount)
	//	{
	//		ClockTime++;
	//		if (ClockTime==2)
	//			{
	//				C_ProgBar->Nudge();
	//				ClockTime=0;

	//			}
	//		LTempMotionName=geActor_GetMotionName(At->ActorDef_Memory,MotionCount);
	//		
	//		strcpy(App->CL_Motions->Selected_MotionName,LTempMotionName);
	//		strcpy(bufferFile,LTempMotionName);
	//		App->CL_Motions->R_DetectMax();
	//		MotionCount++;
	//		SendMessage(PB,PBM_DELTAPOS,(WPARAM) 1,0);
	//	}
	//	MotionCount=0;
	//
	//	ClockTime=0;
	//	while(MotionCount<Counters[0]->MotionCount)
	//	{
	//		ClockTime++;
	//		if (ClockTime==2)
	//			{
	//				C_ProgBar->Nudge();
	//				ClockTime=0;

	//			}
	//		
	//		WriteMotion(MotionCount);
	//		MotionCount++;
	//		SendMessage(PB,PBM_DELTAPOS,(WPARAM) 1,0);
	//	}
	//	
	//	fprintf(WriteSkFile,"%s\n","    </animations>");
	//}

	//fprintf(WriteSkFile,"%s\n","</skeleton>"); //end

	//fclose(WriteSkFile);
	return 1;
}
// *************************************************************************
// *							WriteMotion					   		   	   *
// *************************************************************************
bool VM_XMLExport::WriteMotion(int lMotionCount)
{
	
//	if (Counters[0]->MotionCount==0)
//	{
//		return 0;
//	}
//
//	C_ProgBar->SetMainText("Writing Motions to file");
//
//	float x=0;
//	float y=0;
//	float z=0;
//
//	float Ax=1;
//	float Ay=0;
//	float Az=0;
//
//
//	float Angle=0;
//	
//	const char *TempMotionName;
//	const char *PathName;
//	char LMotionName[256];
//	geMotion *XmlMotion;
//	gePath* XMLPath;
//	float StartTime=0;
//	float EndTime=0;
//	float time=0;
//	int Count=0;
//	
//	
//	geXForm3d  A;
//	int pb=0;
//	int DoRoot=0;
//	
//
//	TempMotionName=geActor_GetMotionName(At->ActorDef_Memory,lMotionCount);
//
//
//	strcpy(LMotionName,TempMotionName);
//
//
//	C_ProgBar->SetProcessText(LMotionName);
//
//	XmlMotion=geActor_GetMotionByName(At->ActorDef_Memory,LMotionName);
//	geMotion_GetTimeExtents(XmlMotion,&StartTime,&EndTime);
//
//	
//fprintf(WriteSkFile,"%s%s%s%f%s\n","        <animation name=\"",LMotionName,"\" length=\"",EndTime,"\">");
//fprintf(WriteSkFile,"%s\n","            <tracks>");	
//
//	int PathCount=geMotion_GetPathCount(XmlMotion);
//
//	
//	while (Count<PathCount)
//	{
//	//	AnimateProgressBar();
//		XMLPath=geMotion_GetPath(XmlMotion,Count);
//		PathName=geMotion_GetNameOfPath(XmlMotion,Count);
//		geBody_GetBone(At->ActorDef_Memory->Body,Count,&PathName,&A,&pb);
//		if (pb == -1)
//		{
//		//	char tbuf[256];
//		//	strcpy(tbuf,PathName);
//		//	Say(tbuf);
//			DoRoot=1;
//		}
//
//fprintf(WriteSkFile,"%s%s%s\n","                 <track bone=\"",PathName,"\">");
//fprintf(WriteSkFile,"%s\n","                     <keyframes>");	
//
//		
//		int FrameLoop=0;
//		int TotalKeyFrames=gePath_GetKeyframeCount(XMLPath,GE_PATH_TRANSLATION_CHANNEL);
//		while (FrameLoop<TotalKeyFrames)
//		{
//			
//			gePath_GetKeyframe(XMLPath,FrameLoop,GE_PATH_TRANSLATION_CHANNEL ,&time,&SPosNewMatric);
//			gePath_GetKeyframe(XMLPath,FrameLoop,GE_PATH_ROTATION_CHANNEL ,&time,&SRotNewMatric);
//			
//			if(DoRoot==1)
//			{
//				GetRootMatrix();
//				
//			}
//			else
//			{
//				GetFrameMatrix();
//			}
//				;
//			
//			x=S_XMLJoint[0]->position[0];
//			y=S_XMLJoint[0]->position[1];
//			z=S_XMLJoint[0]->position[2];
//
//			Ax=S_XMLJoint[0]->rotation[0];
//			Ay=S_XMLJoint[0]->rotation[1];
//			Az=S_XMLJoint[0]->rotation[2];
//
//			Angle=S_XMLJoint[0]->Angle;
//
//fprintf(WriteSkFile,"%s%f%s\n","                         <keyframe time=\"",time,"\">");
//
//fprintf(WriteSkFile, "%s%f%s%f%s%f%s\n","                              <translate x=\"",x,"\" y=\"",y,"\" z=\"",z,"\" />");	
//
//fprintf(WriteSkFile,"%s%f%s\n","                              <rotate angle=\"",Angle,"\">");
//fprintf(WriteSkFile, "%s%f%s%f%s%f%s\n","                                  <axis x=\"",Ax,"\" y=\"",Ay,"\" z=\"",Az,"\" />");	
//fprintf(WriteSkFile,"%s\n","                              </rotate>");	
//
//
//	
//fprintf(WriteSkFile,"%s\n","                         </keyframe>");
//	
//		
//
//			FrameLoop++;
//		}
//		DoRoot=0;
//fprintf(WriteSkFile,"%s\n","                     </keyframes>");	
//fprintf(WriteSkFile,"%s\n","                 </track>");	
//		
//		Count++;
//	}
//
//
//	
//fprintf(WriteSkFile,"%s\n","            </tracks>");	
//fprintf(WriteSkFile,"%s\n","        </animation>");

	return 1;
}

// *************************************************************************
// *							GetFrameMatrix				   		   	   *
// *************************************************************************
bool VM_XMLExport::GetFrameMatrix()
{
//	geQuaternion  gQ;
//	geVec3d v;
//
//	geVec3d Angles;
//	geVec3d XMLAngles;
//	float Theta=0;
//	float Tx=0;
//	float Ty=0;
//	float Tz=0;
//	
//
//	
//		//v = A.Translation;
//		v =SPosNewMatric.Translation;
//		geQuaternion_FromMatrix(&SPosNewMatric, &gQ);
//
//		
//		geQuaternion_ToMatrix(&gQ, &SPosNewMatric);
//		SPosNewMatric.Translation = v;
//
//		geXForm3d_Orthonormalize(&SPosNewMatric);
//		
//		geXForm3d_GetEulerAngles(&SPosNewMatric,&Angles);
//	//	Angles.Z = - Angles.Z;
//
//		if (C_XMLExport->XMLScale < 1)
//		{
//		
//			int Lone=1;
//			float result=(float)Lone/Scale;
//
//		//	sprintf(buf,"%f %i %f",Scale,Lone,result);
//		//	Say(buf);
//		
//			if (SPosNewMatric.Translation.X!=0)
//			{
//				Tx=SPosNewMatric.Translation.X/result;
//			}
//			if (SPosNewMatric.Translation.Y!=0)
//			{
//				Ty=SPosNewMatric.Translation.Y/result;
//			}
//
//			if (SPosNewMatric.Translation.Z!=0)
//			{
//				Tz=SPosNewMatric.Translation.Z/result;
//			}
//
//			SPosNewMatric.Translation.X=Tx;
//			SPosNewMatric.Translation.Y=Ty;
//			SPosNewMatric.Translation.Z=Tz;
//		}
//		else
//		{
//			Tx=C_XMLExport->XMLScale*SPosNewMatric.Translation.X;
//			Ty=C_XMLExport->XMLScale*SPosNewMatric.Translation.Y;
//			Tz=C_XMLExport->XMLScale*SPosNewMatric.Translation.Z;
//
//			SPosNewMatric.Translation.X=Tx;
//			SPosNewMatric.Translation.Y=Ty;
//			SPosNewMatric.Translation.Z=Tz;
//			
//		}
//
//		S_XMLJoint[0]->position[0]=SPosNewMatric.Translation.X;
//		S_XMLJoint[0]->position[1]=SPosNewMatric.Translation.Y;
//		S_XMLJoint[0]->position[2]=SPosNewMatric.Translation.Z;
//
//geQuaternion_FromMatrix(&SRotNewMatric, &gQ);
//
//
// geQuaternion_GetAxisAngle(&gQ,&XMLAngles,&Theta);
//
//		S_XMLJoint[0]->rotation[0]=XMLAngles.X;
//		S_XMLJoint[0]->rotation[1]=XMLAngles.Y;
//		S_XMLJoint[0]->rotation[2]=XMLAngles.Z;
//
//		S_XMLJoint[0]->Angle=Theta;
			
	return 1;
}

// *************************************************************************
// *							GetRootMatrix				   		   	   *
// *************************************************************************
bool VM_XMLExport::GetRootMatrix()
{
//	geQuaternion  gQ;
//	geVec3d v;
//
////	int pb;
//	
////	const char *ParentBoneName;
//
//	float Tx=0;
//	float Ty=0;
//	float Tz=0;
//
//	
////	geXForm3d  B;
//	geVec3d Angles;
//	geVec3d XMLAngles;
//	float Theta=0;
//	
//		//v = A.Translation;
//		v =SPosNewMatric.Translation;
//		geQuaternion_FromMatrix(&SPosNewMatric, &gQ);
//
//		
//		geQuaternion_ToMatrix(&gQ, &SPosNewMatric);
//		SPosNewMatric.Translation = v;
//
//		geXForm3d_Orthonormalize(&SPosNewMatric);
//		
//		geXForm3d_GetEulerAngles(&SPosNewMatric,&Angles);
//	//	Angles.Z = - Angles.Z;
//
//		if (C_XMLExport->XMLScale < 1)
//		{
//		
//			int Lone=1;
//			float result=(float)Lone/Scale;
//
//		//	sprintf(buf,"%f %i %f",Scale,Lone,result);
//		//	Say(buf);
//		
//			if (SPosNewMatric.Translation.X!=0)
//			{
//				Tx=SPosNewMatric.Translation.X/result;
//			}
//			if (SPosNewMatric.Translation.Y!=0)
//			{
//				Ty=SPosNewMatric.Translation.Y/result;
//			}
//
//			if (SPosNewMatric.Translation.Z!=0)
//			{
//				Tz=SPosNewMatric.Translation.Z/result;
//			}
//
//			SPosNewMatric.Translation.X=Tx;
//			SPosNewMatric.Translation.Y=Ty;
//			SPosNewMatric.Translation.Z=Tz;
//		}
//		else
//		{
//			Tx=C_XMLExport->XMLScale*SPosNewMatric.Translation.X;
//			Ty=C_XMLExport->XMLScale*SPosNewMatric.Translation.Y;
//			Tz=C_XMLExport->XMLScale*SPosNewMatric.Translation.Z;
//
//			SPosNewMatric.Translation.X=Tx;
//			SPosNewMatric.Translation.Y=Ty;
//			SPosNewMatric.Translation.Z=Tz;
//			
//		}
//
//
//		S_XMLJoint[0]->position[0]=SPosNewMatric.Translation.Y;
//		S_XMLJoint[0]->position[1]=SPosNewMatric.Translation.Z;
//		S_XMLJoint[0]->position[2]=SPosNewMatric.Translation.X;
//		//Say("root");
//
//geQuaternion_FromMatrix(&SRotNewMatric, &gQ);
//
//
// geQuaternion_GetAxisAngle(&gQ,&XMLAngles,&Theta);
//
//		S_XMLJoint[0]->rotation[0]=XMLAngles.X;
//		S_XMLJoint[0]->rotation[1]=XMLAngles.Y;
//		S_XMLJoint[0]->rotation[2]=XMLAngles.Z;
//
//		S_XMLJoint[0]->Angle=Theta;
			
	return 1;
}

// *************************************************************************
// *							WtiteBoneMatrix				   		   	   *
// *************************************************************************
bool VM_XMLExport::WriteBoneMatrix()
{
//	float x=0;
//	float y=0;
//	float z=0;
//
//	float Ax=1;
//	float Ay=0;
//	float Az=0;
//
//	float Angle=0;
//
//	char BoneName[256];
//
//	int Count=0;
//	int BoneCount=Counters[0]->BoneCount;
//
//	S_XMLJoint[0] = new XMLJoint_Type;
//
//	while (Count<BoneCount)
//	{
//	//	AnimateProgressBar();
//	 GetBoneMatrix(Count);
//	 strcpy(BoneName,S_XMLJoint[0]->name);
//
//	x=S_XMLJoint[0]->position[0];
//	y=S_XMLJoint[0]->position[1];
//	z=S_XMLJoint[0]->position[2];
//
//	Ax=S_XMLJoint[0]->rotation[0];
//	Ay=S_XMLJoint[0]->rotation[1];
//	Az=S_XMLJoint[0]->rotation[2];
//
//	Angle=S_XMLJoint[0]->Angle;
//
//	
//fprintf(WriteSkFile,"%s%i%s%s%s%s\n","        <bone id=\"",Count,"\" ","name=\"",BoneName,"\">");
//
//fprintf(WriteSkFile, "%s%f%s%f%s%f%s\n","            <position x=\"",x,"\" y=\"",y,"\" z=\"",z,"\" />");	
//
//fprintf(WriteSkFile,"%s%f%s\n","            <rotation angle=\"",Angle,"\">");
//fprintf(WriteSkFile, "%s%f%s%f%s%f%s\n","                <axis x=\"",Ax,"\" y=\"",Ay,"\" z=\"",Az,"\" />");	
//fprintf(WriteSkFile,"%s\n","            </rotation>");
//fprintf(WriteSkFile,"%s\n","        </bone>");
//	 
//		Count++;
//	}

	return 1;
}

// *************************************************************************
// *							GetBoneMatrix				   		   	   *
// *************************************************************************
bool VM_XMLExport::GetBoneMatrix(int Count)
{
	//geQuaternion  gQ;
	//geVec3d v;

	//int pb;
	//const char *BoneNameQ;
	//const char *ParentBoneName;

	//
	//
	//geXForm3d  A;
	//
	//geVec3d Angles;
	//geVec3d XMLAngles;
	//float Theta=0;
	//
	//geBody_GetBone(At->ActorDef_Memory->Body,Count,&BoneNameQ,&A,&pb);

	//	  
	//strcpy(S_XMLJoint[0]->name,BoneNameQ);
	//
	//geActor_GetBoneTransform(At->TestActor,BoneNameQ,&A);
	//if (pb == -1)
	//{
	//
	//	v = A.Translation;
	//	
	//	geQuaternion_FromMatrix(&A, &gQ);
	////	gQ.Z = -gQ.Z;
	//	
	//	geQuaternion_ToMatrix(&gQ, &A);
	//	A.Translation = v;

	//	geXForm3d_Orthonormalize(&A);
	//	
	//	geXForm3d_GetEulerAngles(&A,&Angles);
	//	Angles.Z = - Angles.Z;

	//	
	//	S_XMLJoint[0]->position[0]=A.Translation.X;
	//	S_XMLJoint[0]->position[1]=A.Translation.Y;
	//	S_XMLJoint[0]->position[2]=A.Translation.Z;

 //geQuaternion_GetAxisAngle(&gQ,&XMLAngles,&Theta);

	//	S_XMLJoint[0]->rotation[0]=XMLAngles.X;
	//	S_XMLJoint[0]->rotation[1]=XMLAngles.Y;
	//	S_XMLJoint[0]->rotation[2]=XMLAngles.Z;

	//	S_XMLJoint[0]->Angle=Theta;
	//	
	//	
	//	
	//	strcpy(S_XMLJoint[0]->parentName,"");
	//	
	//}
	//else
	//{
	//	geBody_GetBone(At->ActorDef_Memory->Body,pb,&ParentBoneName,&A,&pb);
	//	
	//	strcpy(S_XMLJoint[0]->parentName,ParentBoneName);
	//	geBody_GetBone(At->ActorDef_Memory->Body,Count,&ParentBoneName,&A,&pb);
	//	v = A.Translation;
	//	
	//	geQuaternion_FromMatrix(&A, &gQ);
	////	gQ.Z = -gQ.Z;
	//	
	//	geQuaternion_ToMatrix(&gQ, &A);
	//	A.Translation = v;
	//	
	//	geXForm3d_GetEulerAngles(&A,&Angles);
	//	Angles.Z = - Angles.Z;
	//	
	//	S_XMLJoint[0]->position[0]=A.Translation.X;
	//	S_XMLJoint[0]->position[1]=A.Translation.Y;
	//	S_XMLJoint[0]->position[2]=A.Translation.Z;

 //geQuaternion_GetAxisAngle(&gQ,&XMLAngles,&Theta);

	//	S_XMLJoint[0]->rotation[0]=XMLAngles.X;
	//	S_XMLJoint[0]->rotation[1]=XMLAngles.Y;
	//	S_XMLJoint[0]->rotation[2]=XMLAngles.Z;

	//	S_XMLJoint[0]->Angle=Theta;
	//}
	
	return 1;
}

// *************************************************************************
// *							WriteHiracy					   		   	   *
// *************************************************************************
bool VM_XMLExport::WriteHiracy()
{
//	S_XMLImortHRCY[0] = new XMLImportHiracy_Type;
//	CreateHiracyLists();
//	int Count=1;
//	char BoneName[256];
//	char ParentBoneName[256];
//
//	while (Count<S_XMLImortHRCY[0]->HiracyCount)
//	{
////		AnimateProgressBar();
//		strcpy(BoneName,S_XMLImortHRCY[0]->FirstList[Count].Name);
//		strcpy(ParentBoneName,S_XMLImortHRCY[0]->SecondList[Count].Name);
//		int test=strcmp(ParentBoneName,"poo");
//		if (test==0)
//		{
//		}
//		else
//		{
//
//fprintf(WriteSkFile, "%s%s%s%s%s\n","        <boneparent bone=\"",BoneName,"\" parent=\"",ParentBoneName,"\" />");
//		}		
//Count++;
//	}

	return 1;
}

// *************************************************************************
// *						CreateHiracyLists				   		   	   *
// *************************************************************************
bool VM_XMLExport::CreateHiracyLists()
{
//	int pb;
//	const char *BoneName;
//	const char *ParentBoneName;
//	geXForm3d  A;
//
//
//	S_XMLImortHRCY[0]->HiracyCount=0;
//	int Count=0;
//	int BoneCount=Counters[0]->BoneCount;
//	while (Count<BoneCount)
//	{
////		AnimateProgressBar();
//		geBody_GetBone(At->ActorDef_Memory->Body,Count,&BoneName,&A,&pb);
//		if (pb == -1)
//		{
//			strcpy(S_XMLImortHRCY[0]->FirstList[Count].Name,BoneName);
//			strcpy(S_XMLImortHRCY[0]->SecondList[Count].Name,"poo");
//			S_XMLImortHRCY[0]->HiracyCount++;
//
//		}
//		else
//		{
//			geBody_GetBone(At->ActorDef_Memory->Body,pb,&ParentBoneName,&A,&pb);
//			strcpy(S_XMLImortHRCY[0]->FirstList[Count].Name,BoneName);
//			strcpy(S_XMLImortHRCY[0]->SecondList[Count].Name,ParentBoneName);
//			S_XMLImortHRCY[0]->HiracyCount++;
//		}
//
//
//		Count++;
//	}
	return 1;
}





		