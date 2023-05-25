internal void
CreateHUD(int32 X,int32 Y,int32 HUDLayer,int32 HUDTarget,real32 Width,real32 Height,uint8 GroupRot,real64 Degrees,uint8 HUDTextureLayer,uint8 HUDType,int32 HUDID,uint8 AttachedValueDataType,void* AttachedValue,real32 IncrementValue,char* AttachedString,game_state* GameState,debug_struct* DebugStruct)
{
    int32 Index = HUDID;
    for(int32 i = 0; i < DebugStruct->DebugHUDElements.HUDElementsCreated; ++i)
    {
        if(DebugStruct->DebugHUDElements.HUDID[i] == Index)
        {
            Assert(!"Duplicate HUD ID detected.");
        }
    }
    DebugStruct->DebugHUDElements.HUDType[Index]= HUDType;
    DebugStruct->DebugHUDElements.AttachedValueDataType[Index] = AttachedValueDataType;
    DebugStruct->DebugHUDElements.IsActive[Index] = 1;
    DebugStruct->DebugHUDElements.IsVisible[Index] = 0;
    DebugStruct->DebugHUDElements.HUDTextureLayer[Index] = HUDTextureLayer;
    DebugStruct->DebugHUDElements.GroupRot[Index] = GroupRot;
    DebugStruct->DebugHUDElements.HUDID[Index] = HUDID;
    DebugStruct->DebugHUDElements.Width[Index] = Width; 
    DebugStruct->DebugHUDElements.Height[Index] = Height;
    DebugStruct->DebugHUDElements.IncrementValue[Index] = IncrementValue;
    DebugStruct->DebugHUDElements.AttachedValue[Index] = AttachedValue;
    real64 Rads = Degrees + 90; // 0 degrees is unit vector pointing straight north
    Rads*= 0.01745329251994329576923690768489; // turn to rads
    DebugStruct->DebugHUDElements.LocalYBasis[Index] ={Cosine(Rads),Sine(Rads)};
    DebugStruct->DebugHUDElements.GroupOffset[Index].x = (real64)X;
    DebugStruct->DebugHUDElements.GroupOffset[Index].y = (real64)Y;
    DebugStruct->DebugHUDElements.GroupOffset[Index].z = HUDLayer; //(.99) - (.01 * HUDLayer); opengl ndc is left handed system so further back increases in value
    if(AttachedString != 0)
    {
        DebugStruct->DebugHUDElements.NumOfChar[Index] = sprintf(DebugStruct->DebugHUDElements.AttachedString[Index],"%s",AttachedString);
    }
    ++DebugStruct->DebugHUDElements.HUDElementsCreated;
}

internal void
RegisterHUDGroup(int32 HUDGroupID,
                 int32* Elements,
                 int32 NumOfElements,
                 real64 Degrees,
                 real64 X,real64 Y,real64 Z,
                 debug_struct* DebugStruct)
{
    int32 Index = DebugStruct->DebugHUDGroups.HUDGroupsCreated;
    DebugStruct->DebugHUDGroups.ElementsContained[Index] = NumOfElements;
    for(int32 i = 0;i<NumOfElements;++i)
    {
        int32 CurrentElement = Elements[i];
        DebugStruct->DebugHUDGroups.ElementIndex[Index][i] = CurrentElement;
    }
    real64 Rads = Degrees + 90; // 0 degrees is unit vector pointing straight north
    Rads*= 0.01745329251994329576923690768489; // turn to rads
    DebugStruct->DebugHUDGroups.YBasis[Index] ={Cosine(Rads),Sine(Rads)};
    DebugStruct->DebugHUDGroups.ScreenPosition[Index] ={X,Y,Z};
    ++DebugStruct->DebugHUDGroups.HUDGroupsCreated;
}

internal void 
SetDebugHUD(game_state* GameState,debug_struct* DebugStruct)
{
    //----------debug move group
    
    {
        CreateHUD(27,27,// screen pos/tracking offset
                  0,// hud layer
                  0,// hud target entity
                  64,64,// scale
                  0,180,// rotation
                  TEXTURENAME_ROTATEAXIS,// texture layer
                  HUDTYPE_TRACKINGBUTTON,// hud type
                  HUDID_DEBUGMOVEXY,// hud id
                  0,// hud datatype
                  0,// hud data
                  0,// increment value
                  0,// hud string
                  GameState,DebugStruct);
        CreateHUD(60,0,// screen pos/trackingoffset
                  1,// hud layer
                  0,// hud target entity
                  100,32,// scale
                  0,0,// rotation
                  TEXTURENAME_XAXISMOVE,// texture layer
                  HUDTYPE_TRACKINGBUTTON,// hud type
                  HUDID_DEBUGMOVEX,// hud id
                  0,// hud datatype
                  0,// hud data
                  0,// increment value
                  0,// hud string
                  GameState,DebugStruct);
        CreateHUD(0,60,// screen pos/tracking offset
                  1,// hud layer
                  0,// hud target entity
                  100,32,// scale
                  0,90,// rotation
                  TEXTURENAME_YAXISMOVE,// texture layer
                  HUDTYPE_TRACKINGBUTTON,// hud type
                  HUDID_DEBUGMOVEY,// hud id
                  0,// hud datatype
                  0,// hud data
                  0,// increment value
                  0,// hud string
                  GameState,DebugStruct);
        CreateHUD(0,0,// screen pos/tracking offset
                  1,// hud layer
                  0,// hud target entity
                  32,32,// scale
                  0,0,// rotation
                  TEXTURENAME_ZAXISMOVE,// texture layer
                  HUDTYPE_TRACKINGBUTTON,// hud type
                  HUDID_DEBUGMOVEZ,// hud id
                  0,// hud datatype
                  0,// hud data
                  0,// increment value
                  0,// hud string
                  GameState,DebugStruct);
        //----------pos values
        CreateHUD(75,-50,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  150,32,// scale
                  0,0,// rotation
                  0,// texture layer
                  HUDTYPE_TRACKING,// hud type
                  HUDID_DEBUGXPOS,// hud id
                  HUDDATATYPE_REAL64,// hud datatype
                  &DebugStruct->ActiveGroupCenter.x,// hud data
                  0,// increment value
                  "XPos : ",// hud string
                  GameState,DebugStruct);
        CreateHUD(75,-50-32,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  150,32,// scale
                  0,0,// rotation
                  0,// texture layer
                  HUDTYPE_TRACKING,// hud type
                  HUDID_DEBUGYPOS,// hud id
                  HUDDATATYPE_REAL64,// hud datatype
                  &DebugStruct->ActiveGroupCenter.y,// hud data
                  0,// increment value
                  "YPos : ",// hud string
                  GameState,DebugStruct);
        CreateHUD(75,-50-32-32,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  150,32,// scale
                  0,0,// rotation
                  0,// texture layer
                  HUDTYPE_TRACKING,// hud type
                  HUDID_DEBUGZPOS,// hud id
                  HUDDATATYPE_REAL64,// hud datatype
                  &DebugStruct->ActiveGroupCenter.z,// hud data
                  0,// increment value
                  "ZPos : ",// hud string
                  GameState,DebugStruct);
        CreateHUD(0,-30,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  120,32,// scale
                  0,0,// rotation
                  0,// texture layer
                  HUDTYPE_TRACKING,// hud type
                  HUDID_DEBUGINDEXNUMBER,// hud id
                  HUDDATATYPE_INT32,// hud datatype
                  &DebugStruct->ActiveGroupIndex[0],// hud data
                  0,// increment value
                  "EntIndex : ",// hud string
                  GameState,DebugStruct);
        int32 Elements[] =
        {
            HUDID_DEBUGMOVEXY,
            HUDID_DEBUGMOVEX,
            HUDID_DEBUGMOVEY,
            HUDID_DEBUGMOVEZ,
            HUDID_DEBUGXPOS,
            HUDID_DEBUGYPOS,
            HUDID_DEBUGZPOS,
            HUDID_DEBUGINDEXNUMBER
        };
        RegisterHUDGroup(GROUPHUDID_DEBUGGROUPMOVE,Elements,ArrayCount(Elements),
                         0,
                         0,0,0,
                         DebugStruct);
    }
    
    //----------debug rotate button
    
    {
        CreateHUD(0,0,// screen pos/tracking offset
                  0,// hud layer
                  0,// hud target entity
                  128,128,// scale
                  1,0,// rotation
                  TEXTURENAME_ROTATEAXIS,// texture layer
                  HUDTYPE_TRACKINGBUTTON,// hud type
                  HUDID_DEBUGROTATEAXIS,// hud id
                  0,// hud datatype
                  0,// hud data
                  0,// increment value
                  0,// hud string
                  GameState,DebugStruct);
        CreateHUD(0,16,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  90,32,// scale
                  0,0,// rotation
                  0,// texture layer
                  HUDTYPE_TRACKING,// hud type
                  HUDID_DEBUGBASISVALUEX,// hud id
                  HUDDATATYPE_REAL64,// hud datatype
                  &DebugStruct->ActiveGroupYBasis.x,// hud data
                  0,// increment value
                  "X : ",// hud string
                  GameState,DebugStruct);
        CreateHUD(0,-16,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  90,32,// scale
                  0,0,// rotation
                  0,// texture layer
                  HUDTYPE_TRACKING,// hud type
                  HUDID_DEBUGBASISVALUEY,// hud id
                  HUDDATATYPE_REAL64,// hud datatype
                  &DebugStruct->ActiveGroupYBasis.y,// hud data
                  0,// increment value
                  "Y : ",// hud string
                  GameState,DebugStruct);
        int32 Elements[] =
        {
            HUDID_DEBUGROTATEAXIS,
            HUDID_DEBUGBASISVALUEX,
            HUDID_DEBUGBASISVALUEY
        };
        RegisterHUDGroup(GROUPHUDID_DEBUGGROUPROTATE,Elements,ArrayCount(Elements),
                         0,
                         0,0,0,
                         DebugStruct);
    }
    
    //----------texture edit
    
    {
        CreateHUD(0,0,// screen pos/tracking offset
                  0,// hud layer
                  0,// hud target entity
                  128,128,// scale
                  0,0,// rotation
                  TEXTURENAME_SELECTED,// texture layer
                  HUDTYPE_TRACKINGBUTTON,// hud type
                  HUDID_DEBUGTEXTUREEDIT,// hud id
                  0,// hud datatype
                  0,// hud data
                  0,// increment value
                  0,// hud string
                  GameState,DebugStruct);
        CreateHUD(0,32,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  150,32,// scale
                  0,0,// rotation
                  0,// texture layer
                  HUDTYPE_TRACKING,// hud type
                  HUDID_DEBUGTEXTUREOFFSETX,// hud id
                  HUDDATATYPE_REAL32,// hud datatype
                  0,// hud data
                  0,// increment value
                  "XOffset : ",// hud string
                  GameState,DebugStruct);
        CreateHUD(0,0,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  150,32,// scale
                  0,0,// rotation
                  0,// texture layer
                  HUDTYPE_TRACKING,// hud type
                  HUDID_DEBUGTEXTUREOFFSETY,// hud id
                  HUDDATATYPE_REAL32,// hud datatype
                  0,// hud data
                  0,// increment value
                  "YOffset : ",// hud string
                  GameState,DebugStruct);
        CreateHUD(0,-32,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  150,32,// scale
                  0,0,// rotation
                  0,// texture layer
                  HUDTYPE_TRACKING,// hud type
                  HUDID_DEBUGTEXTUREREPEATSCALE,// hud id
                  HUDDATATYPE_REAL32,// hud datatype
                  0,// hud data
                  0,// increment value
                  "RepeatFactor : ",// hud string
                  GameState,DebugStruct);
        int32 Elements[] =
        {
            HUDID_DEBUGTEXTUREEDIT,
            HUDID_DEBUGTEXTUREOFFSETX,
            HUDID_DEBUGTEXTUREOFFSETY,
            HUDID_DEBUGTEXTUREREPEATSCALE
        };
        RegisterHUDGroup(GROUPHUDID_DEBUGGROUPTEXTURE,Elements,ArrayCount(Elements),
                         0,
                         0,0,0,
                         DebugStruct);
    }
    
    //----------scale edit
    
    {
        CreateHUD(27,27,// screen pos/tracking offset
                  0,// hud layer
                  0,// hud target entity
                  64,64,// scale
                  1,180,// rotation
                  TEXTURENAME_OUTLINE,// texture layer
                  HUDTYPE_TRACKINGBUTTON,// hud type
                  HUDID_DEBUGSCALEXY,// hud id
                  0,// hud datatype
                  0,// hud data
                  0,// increment value
                  0,// hud string
                  GameState,DebugStruct);
        CreateHUD(60,0,// screen pos/trackingoffset
                  1,// hud layer
                  0,// hud target entity
                  100,32,// scale
                  1,0,// rotation
                  TEXTURENAME_XAXISSCALE,// texture layer
                  HUDTYPE_TRACKINGBUTTON,// hud type
                  HUDID_DEBUGSCALEX,// hud id
                  0,// hud datatype
                  0,// hud data
                  0,// increment value
                  0,// hud string
                  GameState,DebugStruct);
        CreateHUD(0,60,// screen pos/tracking offset
                  1,// hud layer
                  0,// hud target entity
                  100,32,// scale
                  1,90,// rotation
                  TEXTURENAME_YAXISSCALE,// texture layer
                  HUDTYPE_TRACKINGBUTTON,// hud type
                  HUDID_DEBUGSCALEY,// hud id
                  0,// hud datatype
                  0,// hud data
                  0,// increment value
                  0,// hud string
                  GameState,DebugStruct);
        CreateHUD(0,0,// screen pos/tracking offset
                  1,// hud layer
                  0,// hud target entity
                  32,32,// scale
                  1,0,// rotation
                  TEXTURENAME_ZAXISSCALE,// texture layer
                  HUDTYPE_TRACKINGBUTTON,// hud type
                  HUDID_DEBUGSCALEZ,// hud id
                  0,// hud datatype
                  0,// hud data
                  0,// increment value
                  0,// hud string
                  GameState,DebugStruct);
        CreateHUD(75,-50,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  150,32,// scale
                  0,0,// rotation
                  0,// texture layer
                  HUDTYPE_TRACKING,// hud type
                  HUDID_DEBUGHALFWIDTH,// hud id
                  HUDDATATYPE_REAL64,// hud datatype
                  0,// hud data
                  0,// increment value
                  "HalfWidth : ",// hud string
                  GameState,DebugStruct);
        CreateHUD(75,-50-32,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  150,32,// scale
                  0,0,// rotation
                  0,// texture layer
                  HUDTYPE_TRACKING,// hud type
                  HUDID_DEBUGHALFHEIGHT,// hud id
                  HUDDATATYPE_REAL64,// hud datatype
                  0,// hud data
                  0,// increment value
                  "HalfHeight : ",// hud string
                  GameState,DebugStruct);
        CreateHUD(75,-50-32-32,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  150,32,// scale
                  0,0,// rotation
                  0,// texture layer
                  HUDTYPE_TRACKING,// hud type
                  HUDID_DEBUGHALFDEPTH,// hud id
                  HUDDATATYPE_REAL64,// hud datatype
                  0,// hud data
                  0,// increment value
                  "HalfDepth : ",// hud string
                  GameState,DebugStruct);
        int32 Elements[] =
        {
            HUDID_DEBUGSCALEXY,
            HUDID_DEBUGSCALEX,
            HUDID_DEBUGSCALEY,
            HUDID_DEBUGSCALEZ,
            HUDID_DEBUGHALFWIDTH,
            HUDID_DEBUGHALFHEIGHT,
            HUDID_DEBUGHALFDEPTH
        };
        RegisterHUDGroup(GROUPHUDID_DEBUGGROUPTEXTURE,Elements,ArrayCount(Elements),
                         0,
                         0,0,0,
                         DebugStruct);
    }
    
    //----------edit type
    
    {
        CreateHUD(0,0,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  150,32,// scale
                  0,0,// rotation
                  0,// texture layer
                  HUDTYPE_TRACKING,// hud type
                  HUDID_DEBUGENTITYTYPE,// hud id
                  0,// hud datatype
                  0,// hud data
                  0,// increment value
                  0,// hud string
                  GameState,DebugStruct);
        int32 Elements[] =
        {
            HUDID_DEBUGENTITYTYPE
        };
        RegisterHUDGroup(GROUPHUDID_DEBUGGROUPTYPE,Elements,ArrayCount(Elements),
                         0,
                         0,0,0,
                         DebugStruct);
    }
    
    //----------debug grid buttons
    
    {
        CreateHUD(0,0,// screen pos/tracking offset
                  2,// hud layer
                  0,// hud target entity
                  150,48,// scale
                  0,0,// rotation
                  TEXTURENAME_RED,// texture layer
                  HUDTYPE_BUTTON,// hud type
                  HUDID_DEBUGGRIDMOVE,// hud id
                  HUDDATATYPE_INT16,// hud datatype
                  &DebugStruct->EditPositionValue,// hud data
                  5,// increment value
                  "GridMove : ",// hud string
                  GameState,DebugStruct);
        CreateHUD(160,0,// screen pos/tracking offset
                  2,// hud layer
                  0,// hud target entity
                  150,48,// scale
                  0,0,// rotation
                  TEXTURENAME_RED,// texture layer
                  HUDTYPE_BUTTON,// hud type
                  HUDID_DEBUGGRIDROTATE,// hud id
                  HUDDATATYPE_INT16,// hud datatype
                  &DebugStruct->EditRotationValue,// hud data
                  5,// increment value
                  "GridRotate : ",// hud string
                  GameState,DebugStruct);
        CreateHUD(160+160,0,// screen pos/tracking offset
                  2,// hud layer
                  0,// hud target entity
                  150,48,// scale
                  0,0,// rotation
                  TEXTURENAME_RED,// texture layer
                  HUDTYPE_BUTTON,// hud type
                  HUDID_DEBUGGRIDSCALE,// hud id
                  HUDDATATYPE_INT16,// hud datatype
                  &DebugStruct->EditScaleValue,// hud data
                  5,// increment value
                  "GridScale : ",// hud string
                  GameState,DebugStruct);
        int32 Elements[] =
        {
            HUDID_DEBUGGRIDMOVE,
            HUDID_DEBUGGRIDROTATE,
            HUDID_DEBUGGRIDSCALE
        };
        RegisterHUDGroup(GROUPHUDID_DEBUGGROUPGRIDBUTTONS,Elements,ArrayCount(Elements),
                         0,
                         1920-320-75,1080-24,0,
                         DebugStruct);
    }
    
    //----------create entity
    
    {
        CreateHUD(0,0,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  300,64,// scale
                  0,0,// rotation
                  TEXTURENAME_GREEN,// texture layer
                  HUDTYPE_BUTTON,// hud type
                  HUDID_CREATEENTITY,// hud id
                  0,// hud datatype
                  0,// hud data
                  0,// increment value
                  "CreateEntity",// hud string
                  GameState,DebugStruct);
        int32 Elements[] =
        {
            HUDID_CREATEENTITY
        };
        RegisterHUDGroup(GROUPHUDID_DEBUGGROUPCREATEENTITY,Elements,ArrayCount(Elements),
                         0,
                         150,1080-32,0,
                         DebugStruct);
    }
    
    //----------debug values
    
    {
        CreateHUD(0,0,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  300,64,// scale
                  0,0,// rotation
                  0,// texture layer
                  HUDTYPE_TEXT,// hud type
                  HUDID_DEBUGVALUEDISPLAY1,// hud id
                  0,// hud datatype
                  0,// hud data
                  0,// increment value
                  0,// hud string
                  GameState,DebugStruct);
        CreateHUD(0,64,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  300,64,// scale
                  0,0,// rotation
                  0,// texture layer
                  HUDTYPE_TEXT,// hud type
                  HUDID_DEBUGVALUEDISPLAY2,// hud id
                  0,// hud datatype
                  0,// hud data
                  0,// increment value
                  0,// hud string
                  GameState,DebugStruct);
        CreateHUD(0,64+64,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  300,64,// scale
                  0,0,// rotation
                  0,// texture layer
                  HUDTYPE_TEXT,// hud type
                  HUDID_DEBUGVALUEDISPLAY3,// hud id
                  0,// hud datatype
                  0,// hud data
                  0,// increment value
                  0,// hud string
                  GameState,DebugStruct);
        CreateHUD(0,64+64+64,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  300,64,// scale
                  0,0,// rotation
                  0,// texture layer
                  HUDTYPE_TEXT,// hud type
                  HUDID_DEBUGVALUEDISPLAY4,// hud id
                  0,// hud datatype
                  0,// hud data
                  0,// increment value
                  0,// hud string
                  GameState,DebugStruct);
        CreateHUD(0,64+64+64+64,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  300,64,// scale
                  0,0,// rotation
                  0,// texture layer
                  HUDTYPE_TEXT,// hud type
                  HUDID_DEBUGVALUEDISPLAY5,// hud id
                  0,// hud datatype
                  0,// hud data
                  0,// increment value
                  0,// hud string
                  GameState,DebugStruct);
        CreateHUD(0,64+64+64+64+64,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  300,64,// scale
                  0,0,// rotation
                  0,// texture layer
                  HUDTYPE_TEXT,// hud type
                  HUDID_DEBUGVALUEDISPLAY6,// hud id
                  0,// hud datatype
                  0,// hud data
                  0,// increment value
                  0,// hud string
                  GameState,DebugStruct);
        CreateHUD(0,64+64+64+64+64+64,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  300,64,// scale
                  0,0,// rotation
                  0,// texture layer
                  HUDTYPE_TEXT,// hud type
                  HUDID_DEBUGVALUEDISPLAY7,// hud id
                  0,// hud datatype
                  0,// hud data
                  0,// increment value
                  0,// hud string
                  GameState,DebugStruct);
        CreateHUD(0,64+64+64+64+64+64+64,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  300,64,// scale
                  0,0,// rotation
                  0,// texture layer
                  HUDTYPE_TEXT,// hud type
                  HUDID_DEBUGVALUEDISPLAY8,// hud id
                  0,// hud datatype
                  0,// hud data
                  0,// increment value
                  0,// hud string
                  GameState,DebugStruct);
        CreateHUD(0,64+64+64+64+64+64+64+64,// screen pos/tracking offset
                  3,// hud layer
                  0,// hud target entity
                  300,64,// scale
                  0,0,// rotation
                  0,// texture layer
                  HUDTYPE_TEXT,// hud type
                  HUDID_DEBUGVALUEDISPLAY9,// hud id
                  0,// hud datatype
                  0,// hud data
                  0,// increment value
                  0,// hud string
                  GameState,DebugStruct);
        int32 Elements[] =
        {
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
        RegisterHUDGroup(GROUPHUDID_DEBUGGROUPVALUES,Elements,ArrayCount(Elements),
                         0,
                         150,32,0,
                         DebugStruct);
    }
    //----------
    DebugStruct->DebugHUDGroups.TrackingPosition[GROUPHUDID_DEBUGGROUPMOVE] = &DebugStruct->ActiveGroupCenter;
    DebugStruct->DebugHUDGroups.TrackingPosition[GROUPHUDID_DEBUGGROUPROTATE] = &DebugStruct->ActiveGroupCenter;
    DebugStruct->DebugHUDGroups.TrackingPosition[GROUPHUDID_DEBUGGROUPTEXTURE] = &DebugStruct->ActiveGroupCenter;
    DebugStruct->DebugHUDGroups.TrackingPosition[GROUPHUDID_DEBUGGROUPSCALE] = &DebugStruct->ActiveGroupCenter;
    DebugStruct->DebugHUDGroups.TrackingPosition[GROUPHUDID_DEBUGGROUPTYPE] = &DebugStruct->ActiveGroupCenter;
    //----------
    DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGXPOS] = &DebugStruct->ActiveGroupCenter.x;
    DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGYPOS] = &DebugStruct->ActiveGroupCenter.y;
    DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGZPOS] = &DebugStruct->ActiveGroupCenter.z;
    DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGBASISVALUEX] = &DebugStruct->ActiveGroupYBasis.x;
    DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGBASISVALUEY] = &DebugStruct->ActiveGroupYBasis.y;
}