#define Assert(Expression) if(!(Expression)){ *(int*)0 = 0;}// TODO(NAME): remove assert
#define KiloBytes(Value) ((Value) * 1024LL)
#define MegaBytes(Value) ((KiloBytes(Value)) * 1024LL)
#define GigaBytes(Value) ((MegaBytes(Value)) * 1024LL)
#define TeraBytes(Value) ((GigaBytes(Value)) * 1024LL)
#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))
//----------
#define internal static
#define global_variable static
#define local_persist static
#define Pi 3.14159265359f
#define MAX_ENTITIES 10000 // // TODO(NAME): abritrary. make solid. if i increase this i gotta increse the vertice memory too in glBufferData, the VBOs.
#define MAX_PLAYERS 1000
#define MAX_TRANSIENT 1000
//----------
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef int32 bool32;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef float real32;
typedef double real64;
#define INT32Min ((int32)0x80000000)
#define INT32Max ((int32)0x7fffffff)
#define UINT32Min 0
#define UINT32Max ((uint32)-1)
#define UINT64Min 0
#define UINT64Max ((uint64)-1)
#define REAL32Max FLT_MAX
#define REAL32Min -FLT_MAX
#define REAL64Max DBL_MAX
#define REAL64Min -DBL_MAX
#define REAL32Epsilon 0.00034526698300124393f //not real machine epsilons. just small values that are close to the epsilon
#define REAL64Epsilon 1.4901161193847656e-08
//----------
#define VIDEO_BUFFER_WIDTH 1920
#define VIDEO_BUFFER_HEIGHT 1080
#define VIDEO_BUFFER_HALFWIDTH 960
#define VIDEO_BUFFER_HALFHEIGHT 540
//----------important type defines in these headers
#include "Game_math.h"
#include "Game_memory.h"
//----------dummy variables area

//----------texture
enum DebugTextureName
{
    TEXTURENAME_NONE = 0,
    TEXTURENAME_DEFAULT,
    TEXTURENAME_WATER,
    TEXTURENAME_SOLDIER,
    TEXTURENAME_FONT1,
    TEXTURENAME_FONT2,
    TEXTURENAME_BLACK,
    TEXTURENAME_GRAY,
    TEXTURENAME_WHITE,
    TEXTURENAME_BLUE,
    TEXTURENAME_GREEN,
    TEXTURENAME_RED,
    TEXTURENAME_XAXISMOVE,
    TEXTURENAME_YAXISMOVE,
    TEXTURENAME_ZAXISMOVE,
    TEXTURENAME_XAXISSCALE,
    TEXTURENAME_YAXISSCALE,
    TEXTURENAME_ZAXISSCALE,
    TEXTURENAME_ROTATEAXIS,
    TEXTURENAME_OUTLINE,
    TEXTURENAME_SELECTED,
    TEXTURENAME_DAMAGE,
    TEXTURENAME_GRADIENT,
    TEXTURENAME_GREENOUTLINE
};
struct texture_index
{
    uint8 TextureLayer;
    real32 TextureOffsetX;
    real32 TextureOffsetY;
    real32 TextureRepeatScale;
};

//----------HUD
enum HUDType
{
    HUDTYPE_TEXT = 1,
    HUDTYPE_BUTTON,
    HUDTYPE_BOX,
    HUDTYPE_EDITTEXT,
    HUDTYPE_EDITVALUE,
    HUDTYPE_TRACKING,
    HUDTYPE_TRACKINGBUTTON
};
enum HUDID
{
    HUDID_DEBUGMOVEXY = 1,
    HUDID_DEBUGMOVEX,
    HUDID_DEBUGMOVEY,
    HUDID_DEBUGMOVEZ,
    HUDID_DEBUGXPOS,
    HUDID_DEBUGYPOS,
    HUDID_DEBUGZPOS,
    HUDID_DEBUGINDEXNUMBER,
    HUDID_DEBUGROTATEAXIS,
    HUDID_DEBUGBASISVALUEX,
    HUDID_DEBUGBASISVALUEY,
    HUDID_DEBUGTEXTUREEDIT,
    HUDID_DEBUGTEXTUREOFFSETX,
    HUDID_DEBUGTEXTUREOFFSETY,
    HUDID_DEBUGTEXTUREREPEATSCALE,
    HUDID_DEBUGSCALEXY,
    HUDID_DEBUGSCALEX,
    HUDID_DEBUGSCALEY,
    HUDID_DEBUGSCALEZ,
    HUDID_DEBUGHALFWIDTH,
    HUDID_DEBUGHALFHEIGHT,
    HUDID_DEBUGHALFDEPTH,
    HUDID_DEBUGENTITYTYPE,
    HUDID_DEBUGGRIDMOVE,
    HUDID_DEBUGGRIDROTATE,
    HUDID_DEBUGGRIDSCALE,
    HUDID_CREATEENTITY,
    HUDID_DEBUGVALUEDISPLAY1,
    HUDID_DEBUGVALUEDISPLAY2,
    HUDID_DEBUGVALUEDISPLAY3,
    HUDID_DEBUGVALUEDISPLAY4,
    HUDID_DEBUGVALUEDISPLAY5,
    HUDID_DEBUGVALUEDISPLAY6,
    HUDID_DEBUGVALUEDISPLAY7,
    HUDID_DEBUGVALUEDISPLAY8,
    HUDID_DEBUGVALUEDISPLAY9
};
enum HUDDataType
{
    HUDDATATYPE_UINT8 = 1,
    HUDDATATYPE_UINT16,
    HUDDATATYPE_UINT32,
    HUDDATATYPE_UINT64,
    HUDDATATYPE_INT8,
    HUDDATATYPE_INT16,
    HUDDATATYPE_INT32,
    HUDDATATYPE_REAL32,
    HUDDATATYPE_REAL64
};
enum GROUPHUDID
{
    GROUPHUDID_DEBUGGROUPMOVE,
    GROUPHUDID_DEBUGGROUPROTATE,
    GROUPHUDID_DEBUGGROUPTEXTURE,
    GROUPHUDID_DEBUGGROUPSCALE,
    GROUPHUDID_DEBUGGROUPTYPE,
    GROUPHUDID_DEBUGGROUPGRIDBUTTONS,
    GROUPHUDID_DEBUGGROUPCREATEENTITY,
    GROUPHUDID_DEBUGGROUPVALUES
};
char* HUDEntityTypeStrings[255] = 
{
    "NONE",
    "COLLIDE",
    "WATER",
    "COLLIDESLOPE",
    "PLAYERSPAWN"
};
struct debug_hud_elements
{
    int32 HUDElementsCreated;
    uint8 HUDType[1024];
    uint8 AttachedValueDataType[1024];
    uint8 IsActive[1024];
    uint8 IsVisible[1024];
    uint8 HUDTextureLayer[1024];
    uint8 GroupRot[1024];
    int32 HUDID[1024];
    int32 NumOfChar[1024];
    real32 Width[1024];
    real32 Height[1024];
    real32 IncrementValue[1024];
    void* AttachedValue[1024];
    v2 LocalYBasis[1024];
    v3 GroupOffset[1024];
    char AttachedString[1024][128];
};
struct debug_hud_groups
{
    int32 HUDGroupsCreated;
    int32 ElementsContained[1024];
    v3* TrackingPosition[1024];
    v2 YBasis[1024];
    v3 ScreenPosition[1024];
    int32 ElementIndex[1024][256];
};

//----------undo
enum UNDOTYPE
{
    UNDOTYPE_MOVE=1,
    UNDOTYPE_ROTATE,
    UNDOTYPE_SCALE,
    UNDOTYPE_SCALEUNIFORM
};
struct undo_info
{
    uint8 NumOfUndo;
    uint8 CurrentUndo;
    uint8 AddUndo;
    uint8 UndoType[100];
    v3 UndoChange[100];
};

//----------debug
#define DEBUG_SHOW_ACTIVE_ENTITY 0x1
#define DEBUG_EDIT_ENTITY_POSITION 0x2
#define DEBUG_EDIT_ENTITY_ROTATION 0x4
#define DEBUG_EDIT_ENTITY_TEXTURE 0x8
#define DEBUG_EDIT_ENTITY_SCALE 0x10
#define DEBUG_EDIT_ENTITY_TYPE 0x20
struct debug_struct// TODO(NAME): probably should rename all this to something that isnt "debug"
{
    uint64 DebugState;
    int16 EditPositionValue;
    int16 EditRotationValue;
    int16 EditScaleValue;
    int32 ClickAcumulationX;
    int32 ClickAcumulationY;
    int32 ClickAcumulationActivationX;
    int32 ClickAcumulationActivationY;
    int32 ClickedButtonIndex;
    int32 NumOfActiveEntities;
    v3 UnitWorldMouseRay;
    v2 ActiveGroupYBasis;
    v3 ActiveGroupCenter;
    uint32 ActiveGroupIndex[100];
    v3 ActiveGroupOffsets[100];
    undo_info UndoInfo;
    debug_hud_groups DebugHUDGroups;
    debug_hud_elements DebugHUDElements;
};

//----------audio
struct game_audio_buffer
{
    uint16 AudioFramesToRender;
    uint16 LeftSample;
    uint16 RightSample;
    void* AudioMemory;
    uint16* WriteCursor;
};

//----------input
//bits for inputstate
#define WKEY_INPUT 0x1
#define AKEY_INPUT 0x2
#define SKEY_INPUT 0x4
#define DKEY_INPUT 0x8
#define SPACEKEY_INPUT 0x10
#define SHIFTKEY_INPUT 0x20
#define CONTROLKEY_INPUT 0x40
#define WHEELUPMOUSE_INPUT 0x80
#define WHEELDOWNMOUSE_INPUT 0x100
#define LEFTCLICKMOUSE_INPUT 0x200
#define RIGHTCLICKMOUSE_INPUT 0x400
#define ESCAPEKEY_INPUT 0x800
#define UPKEY_INPUT 0x1000
#define DOWNKEY_INPUT 0x2000
#define LEFTKEY_INPUT 0x4000
#define RIGHTKEY_INPUT 0x8000
#define NKEY_INPUT 0x10000
#define LKEY_INPUT 0x20000
#define PKEY_INPUT 0x40000
#define F4KEY_INPUT 0x80000
#define F5KEY_INPUT 0x100000
#define EKEY_INPUT 0x200000
#define RKEY_INPUT 0x400000
#define TKEY_INPUT 0x800000
#define YKEY_INPUT 0x1000000
#define MIDDLECLICKMOUSE_INPUT 0x2000000
#define F1KEY_INPUT 0x4000000
#define F2KEY_INPUT 0x8000000
#define F3KEY_INPUT 0x10000000
#define UKEY_INPUT 0x20000000
#define F11KEY_INPUT 0x40000000
#define ZKEY_INPUT 0x80000000
#define CKEY_INPUT 0x100000000
#define VKEY_INPUT 0x200000000
#define ENDKEY_INPUT 0x400000000
//0x8000000000000000 is the last bit in input state
struct game_player_input
{
    uint64 InputInstant;
    uint64 InputInit;
    uint64 InputToggle;
    int32 MouseDeltaX;
    int32 MouseDeltaY;
    real64 ScreenMouseX;
    real64 ScreenMouseY;  
}; 

//----------timing
struct game_timers
{
    real64 MilliSecondsElapsed;
    real64 SecondsElapsed;
};

//----------partition
#define MAX_MAP_WIDTH 59999 // these should all be divisible evenly (-1 to not pass parition indexing)
#define MAX_MAP_HEIGHT 59999
#define MAX_MAP_DEPTH 59999
#define PARTITION_DIMENSION 500
#define ONE_OVER_PARTITION_DIMENSION 0.002
#define PARTITION_STRIDE 120
#define PARTITION_HEIGHT 120
#define PARTITION_DEPTH 120
#define PARTITION_MAXX_INDEX 119
#define PARTITION_MAXY_INDEX 119
#define PARTITION_MAXZ_INDEX 119
enum PartitionTypes
{
    PARTITIONTYPE_LEVEL,
    PARTITIONTYPE_PLAYER
};
struct spatial_partition_index
{
    uint8 PartitionType;
    uint32 EntityIndexInArray;
};
struct spatial_partition_grid
{
    uint32 Capacity;
    uint32 Size;
    spatial_partition_index* IndexStart;
    spatial_partition_grid** SpatialGridPointer;
};
struct spatial_grid_hole
{
    spatial_partition_grid* GridHoleStart;
    spatial_partition_index* IndexHoleStart;
};
struct spatial_partition
{
    uint16 NumOfGridHoles;
    spatial_partition_grid* LastSpatialGrid;
    spatial_grid_hole SpatialMemoryHoles[NUM_OF_BUFFER_HOLES];
    spatial_partition_grid* SpatialGrid[PARTITION_DEPTH][PARTITION_HEIGHT][PARTITION_STRIDE];
    //[Z][Y][X] position indexing to allow easy index arithmetic
    //MaxX index + 1 = Next row, (MaxX+MaxY)+1 = next depth layer
};
struct partition_indices_info
{
    uint32 Capacity;
    uint32 Size;
    uint32* IndicesInPartition;
    partition_indices_info** IndicesInfoPointer;//Points to entity indices_info*
};
struct partition_indices_hole
{
    partition_indices_info* IndicesInfoHoleStart;
    uint32* IndicesDataHoleStart;
};
struct partition_indices_list
{
    uint16 NumOfIndicesInfoHoles;
    partition_indices_info* LastIndicesInfo;
    partition_indices_hole PartitionIndicesHoles[NUM_OF_BUFFER_HOLES];
};

//----------camera
#define DEFAULT_CAMERA_HEIGHT 1000
enum CameraMode
{
    CAMMODE_STATIONARY,
    CAMMODE_FOLLOWPLAYER,
    CAMMODE_FREE
};
struct render_area
{
    uint8 CameraMode;
    real64 Left;
    real64 Right;
    real64 Bottom;
    real64 Top;
    v3 TargetPos;
};

//----------level
enum LevelType
{
    LEVELTYPE_COLLIDE = 1,
    LEVELTYPE_WATER,
    LEVELTYPE_COLLIDESLOPE,//anything <= collidedslope is subject to player collision-above is not
    LEVELTYPE_PLAYERSPAWN
};
struct level_entities
{  
    uint8 LevelType [MAX_ENTITIES];
    real64 HalfWidth [MAX_ENTITIES];
    real64 HalfHeight [MAX_ENTITIES];
    real64 HalfDepth [MAX_ENTITIES];
    real64 AABBHalfLength [MAX_ENTITIES];
    partition_indices_info* LevelPartitionIndices [MAX_ENTITIES];
    v2 YBasis [MAX_ENTITIES];
    v3 Position [MAX_ENTITIES];
    texture_index TextureIndex [MAX_ENTITIES];
    AABB BoundingBox [MAX_ENTITIES];
};

//----------player
/*------------------------------
#define PLAYER_STEPHEIGHT 34.272
#define PLAYER_SQUISHHEIGHT 19.04
#define PLAYER_HALFWIDTH 45.696
#define PLAYER_HALFHEIGHT 45.696
#define PLAYER_HALFDEPTH 78.064
------------------------------*/
#define PLAYER_STEPHEIGHT 50
#define PLAYER_SQUISHHEIGHT 10
#define PLAYER_HALFWIDTH 50
#define PLAYER_HALFHEIGHT 50
#define PLAYER_HALFDEPTH 50
// various bit state of player
#define PLAYERSTATE_TOUCHEDGROUND 0x1
#define PLAYERSTATE_GROUNDED 0x2
#define PLAYERSTATE_DUCKING 0x4
#define PLAYERSTATE_SWIMMING 0x8
#define PLAYERSTATE_WATERJUMP 0x10
enum PlayerClass
{
    PLAYERCLASS_SCOUT= 1,
    PLAYERCLASS_SOLDIER,
    PLAYERCLASS_DEMO,
    PLAYERCLASS_MEDIC
};
struct player_entities
{
    uint8 Class [MAX_PLAYERS];
    uint8 TextureLayer [MAX_PLAYERS];
    real64 Speed [MAX_PLAYERS];
    real64 HalfWidth [MAX_PLAYERS];
    real64 HalfHeight [MAX_PLAYERS];
    real64 HalfDepth [MAX_PLAYERS];
    real64 AABBHalfLength [MAX_PLAYERS];
    partition_indices_info* PlayerPartitionIndices [MAX_PLAYERS];
    uint64 PlayerState [MAX_PLAYERS];
    v2 YBasis [MAX_PLAYERS];
    v3 Velocity [MAX_PLAYERS];
    v3 Position [MAX_PLAYERS];
    AABB BoundingBox [MAX_PLAYERS];
};

//----------local user info
struct user_info
{
    uint32 PlayerIndex;
};

//----------transient entities
enum TransientType
{
    TRANSIENTTYPE_ROCKET = 1,
    TRANSIENTTYPE_GRENADE,
    TRANSIENTTYPE_HEALTHPACKSMALL,
    TRANSIENTTYPE_HEALTHPACKMEDIUM,
    TRANSIENTTYPE_HEALTHPACKFULL,
    TRANSIENTTYPE_AMMOPACKSMALL,
    TRANSIENTTYPE_AMMOPACKMEDIUM,
    TRANSIENTTYPE_AMMOPACKFULL,
};
struct transient_entities
{
    uint8 TransientType [MAX_TRANSIENT];
    uint8 TextureLayer [MAX_TRANSIENT];
    real64 HalfWidth [MAX_TRANSIENT];
    real64 HalfHeight [MAX_TRANSIENT];
    real64 HalfDepth [MAX_TRANSIENT];
    real64 AABBHalfLength [MAX_TRANSIENT];
    partition_indices_info* TransientPartitionIndices [MAX_TRANSIENT];
    v3 TransientData [MAX_TRANSIENT];// i know this makes no sense but i like it
    v2 YBasis [MAX_TRANSIENT];
    v3 Position [MAX_TRANSIENT];
    AABB BoundingBox [MAX_TRANSIENT];
};

//----------
struct game_state
{
    uint32 LevelEntitiesCreated;
    uint32 ActivePlayers;
    uint32 VerticeCount;
    uint32 HUDVerticeCount;
    uint32 RandomState;
    user_info UserInformation;
    render_area RenderArea;
    real32 OpenGLHUDVertices[180000]; // 1k HUD 
    real32 OpenGLVertices[1800000]; // 10k entites 
    player_entities PlayerEntities;
    transient_entities TransientEntities;
    level_entities LevelEntities;
    spatial_partition SpatialPartition;
    partition_indices_list PartitionIndices;
};