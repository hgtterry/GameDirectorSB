#include "strblock.h"

typedef Gint16 geBodyInst_Index;
typedef Gint16 geBody_Index;

#include "Puppet.h"
typedef struct geActor { 
    Gint32                 RefCount; // this is the number of owners. 
    gePuppet*             Puppet;
    gePose*               Pose;
    geActor_BlendingType  BlendingType;
    geActor_Def*          ActorDefinition; // actor definition this is an instance of 
    geMotion*             CueMotion;
    geVec3d               BoundingBoxMinCorner;
    geVec3d               BoundingBoxMaxCorner;
    int                   BoundingBoxCenterBoneIndex;
    int                   StepBoneIndex; // used for single-bone motion optimization.
    void *                UserData;
    geExtBox              RenderHintExtBox;
    int                   RenderHintExtBoxCenterBoneIndex;
    geBoolean             RenderHintExtBoxEnabled;
	
} geActor; 

typedef struct geBodyInst_SkinVertex { 
      geVec3d        SVPoint; 
      geFloat          SVU,SVV; 
      int                  ReferenceBoneIndex; 
} geBodyInst_SkinVertex; 

typedef struct geBodyInst_Geometry { 
      geBodyInst_Index             SkinVertexCount; 
      geBodyInst_SkinVertex*   SkinVertexArray; 
      geBodyInst_Index             NormalCount; 
      geVec3d*                         NormalArray; 
      geBodyInst_Index             FaceCount; 
      Gint32                                 FaceListSize; 
      geBodyInst_Index*           FaceList; 
      geVec3d                           Maxs, Mins; 
} geBodyInst_Geometry; 


typedef struct geBodyInst
{
     const geBody*             BodyTemplate;
     geBodyInst_Geometry		ExportGeometry;
     int                        LastLevelOfDetail;
     geBodyInst_Index          FaceCount;
} geBodyInst;

typedef struct gePuppet_Color
{
     geFloat     Red,Green,Blue;
} gePuppet_Color;


typedef struct gePuppet_Material
{
     gePuppet_Color      Color;
     geBoolean               UseTexture;
     geBitmap*               Bitmap;
     const char*              TextureName;
     const char*              AlphaName;
} gePuppet_Material;


typedef struct gePuppet
{
	geVFile*                   TextureFileContext;
	geBodyInst*                BodyInstance;
	int                        MaterialCount;
	gePuppet_Material*     	   MaterialArray;
	int                        MaxDynamicLightsToUse;
	int                        LightReferenceBoneIndex;

	geVec3d                    FillLightNormal;
	gePuppet_Color             FillLightColor; // 0..255
	geBoolean                  UseFillLight; // use fill light normal

	gePuppet_Color             AmbientLightIntensity; // 0..1
	geBoolean                  AmbientLightFromFloor; // use local lighting from floor

	geBoolean                  PerBoneLighting;

	geBoolean                  DoShadow;
	geFloat                    ShadowScale;
	const geBitmap*            ShadowMap;
	int                        ShadowBoneIndex;

	geWorld*                   World;
} gePuppet;

typedef struct gePose_Joint
{
	int			 ParentJoint;		// parent of path
	geXForm3d    *Transform;		// matrix for path	(pointer into TransformArray)
	geQuaternion Rotation;			// quaternion representation for orientation of above Transform

	geVec3d		 UnscaledAttachmentTranslation;	
					// point of Attachment to parent (in parent frame of ref) **Unscaled
	geQuaternion AttachmentRotation;// rotation of attachement to parent (in parent frame of ref)
	geXForm3d    AttachmentTransform;	//------------

	geVec3d		 LocalTranslation;	// translation relative to attachment 
	geQuaternion LocalRotation;		// rotation relative to attachment 

	geBoolean    Touched;			// if this joint has been touched and needs recomputation
	geBoolean    NoAttachmentRotation; // GE_TRUE if there is no attachment rotation.
	int			 Covered;			// if joint has been 100% set (no blending)
} gePose_Joint;				

typedef struct gePose
{
	int				  JointCount;	// number of joints in the motion
	Gint32			  NameChecksum;	// checksum based on joint names and list order
	geBoolean		  Touched;		// if any joint has been touched & needs recomputation	
	geStrBlock		 *JointNames;
	geVec3d			  Scale;		// current scaling. Used for scaling motion samples

	geBoolean		  Slave;			// if pose is 'slaved' to parent -vs- attached.
	int				  SlaveJointIndex;	// index of 'slaved' joint
	gePose			 *Parent;		
	gePose_Joint	  RootJoint;		
	geXForm3d		  ParentsLastTransform;	// Compared to parent's transform to see if it changed: recompute is needed
	geXForm3d		  RootTransform;
	geXFArray		 *TransformArray;	
	gePose_Joint	 *JointArray;
	int				  OnlyThisJoint;		// update only this joint (and it's parents) if this is >0
} gePose;


typedef struct geBody_XSkinVertex
{
	geVec3d			XPoint;
	geFloat			XU,XV;
	Gint8			LevelOfDetailMask;
	geBody_Index	BoneIndex;
} geBody_XSkinVertex;

typedef struct geActor_Def
{
	geBody				*Body;
	geVFile *			 TextureFileContext;
	
	Gint32				 MotionCount;
	geMotion		   **MotionArray;

	Gint32				 RefCount;				// this is the number of owners.

	geActor_Def			*ValidityCheck;
} geActor_Def;

typedef struct geBody_Normal
{
	geVec3d			Normal;
	Gint8			LevelOfDetailMask;
	geBody_Index	BoneIndex;
} geBody_Normal;

typedef struct geBody_Bone
{
	geVec3d			BoundingBoxMin;
	geVec3d			BoundingBoxMax;
	geXForm3d       AttachmentMatrix;
	geBody_Index	ParentBoneIndex;
} geBody_Bone;
		
typedef struct geBody_Triangle
{
	geBody_Index	VtxIndex[3];
	geBody_Index	NormalIndex[3];
	geBody_Index	MaterialIndex;
	//geBody_Index    FaceNormal;
} geBody_Triangle;
			
typedef struct geBody_TriangleList
{
	geBody_Index	  FaceCount;
	geBody_Triangle  *FaceArray;		// Sorted by MaterialIndex
} geBody_TriangleList;

typedef struct geBody_Material
{
	geBitmap *Bitmap;
	geFloat Red,Green,Blue;
} geBody_Material;

typedef struct geBody
{
	geVec3d				  BoundingBoxMin;
	geVec3d				  BoundingBoxMax;

	geBody_Index		  XSkinVertexCount;
	geBody_XSkinVertex	 *XSkinVertexArray;		// Sorted by BoneIndex

	geBody_Index		  SkinNormalCount;
	geBody_Normal		 *SkinNormalArray;

	geBody_Index		  BoneCount;
	geBody_Bone			 *BoneArray;
	geStrBlock			 *BoneNames;

	geBody_Index		  MaterialCount;
	geBody_Material		 *MaterialArray;
	geStrBlock			 *MaterialNames;		

	int					  LevelsOfDetail;
	geBody_TriangleList	  SkinFaces[GE_BODY_NUMBER_OF_LOD];
	
	geBody				 *IsValid;
} geBody;
