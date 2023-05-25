internal void
ResetUndo(debug_struct* DebugStruct)
{
    DebugStruct->UndoInfo.NumOfUndo = 0;
    DebugStruct->UndoInfo.CurrentUndo = 0;
    DebugStruct->UndoInfo.AddUndo = 0;
    for(uint32 i = 0;i<100;++i)
    {
        DebugStruct->UndoInfo.UndoType[i] = {};
        DebugStruct->UndoInfo.UndoChange[i] = {};
    }
}

//----------

internal int32
NearestLevelToRay(v3 RayOrigin,
                  v3 RayDir,
                  real64* Distance,
                  game_state* GameState,
                  stretchy_buffer_list* StretchyBuffers)
{
    int32 ClosestHitIndex = -1;
    real64 ClosestHit = REAL64Max;
    Normalize(RayDir);
    NormalRayGridIntersection(RayDir,RayOrigin,60000,GameState,StretchyBuffers);// TODO(NAME): arbitrary ray length
    stretchy_buffer* EntityList = GetEntitiesOfTypeFromGrid(PARTITIONTYPE_LEVEL,GameState,StretchyBuffers);
    for (uint32 i = 0 ; i < EntityList->Size; ++i)
    {
        uint32 Index = *((uint32*)EntityList->DataStart+i);
        real64 CollidedHalfWidth = GameState->LevelEntities.HalfWidth[Index];
        real64 CollidedHalfHeight = GameState->LevelEntities.HalfHeight[Index];
        real64 CollidedHalfDepth = GameState->LevelEntities.HalfDepth[Index];
        v3 YBasis = {
            GameState->LevelEntities.YBasis[Index].x,
            GameState->LevelEntities.YBasis[Index].y,
            0
        };
        v3 XBasis = -Perp(YBasis);
        v3 Position = GameState->LevelEntities.Position[Index];
        uint8 LevelType = GameState->LevelEntities.LevelType[Index];
        if(LevelType == LEVELTYPE_COLLIDESLOPE)
        {
            YBasis.x = YBasis.x*CollidedHalfHeight;
            YBasis.y = YBasis.y*CollidedHalfHeight;
            YBasis.z = CollidedHalfDepth;
            real64 NewHeight = SquareRoot(YBasis.x*YBasis.x + YBasis.y*YBasis.y + YBasis.z*YBasis.z);
            CollidedHalfHeight = NewHeight;
            NewHeight = 1/NewHeight;
            YBasis.x = YBasis.x*NewHeight;
            YBasis.y = YBasis.y*NewHeight;
            YBasis.z = YBasis.z*NewHeight;
            CollidedHalfDepth = 0;
        }
        v3 ZBasis = Cross(XBasis,YBasis);
        v3 Delta = Position - RayOrigin;
        real64 TMin = 0;
        real64 TMax = REAL64Max;
        
        //----------XAxis
        
        real64 E = Inner(XBasis,Delta);
        real64 F = Inner(RayDir,XBasis);
        real64 T1 = (E-CollidedHalfWidth)/F;
        real64 T2 = (E+CollidedHalfWidth)/F;
        if (T1>T2)
        {
            real64 w=T1;T1=T2;T2=w;
        }
        if ( T2 < TMax )
        {
            TMax = T2;
        }
        if ( T1 >= TMin )
        {
            TMin = T1;
        }
        if (TMax < TMin )
        {
            goto NEXTENTITYCLOSESTTORAY;
        }
        
        //----------YAxis
        
        E = Inner(YBasis,Delta);
        F = Inner(RayDir,YBasis);
        T1 = (E-CollidedHalfHeight)/F;
        T2 = (E+CollidedHalfHeight)/F;
        if (T1>T2)
        {
            real64 w=T1;T1=T2;T2=w;
        }
        if ( T2 < TMax )
        {
            TMax = T2;
        }
        if ( T1 >= TMin )
        {
            TMin = T1;
        }
        if (TMax < TMin )
        {
            goto NEXTENTITYCLOSESTTORAY;
        }
        
        //----------ZAxis
        
        E = Inner(ZBasis,Delta);
        F = Inner(RayDir,ZBasis);
        T1 = (E-CollidedHalfDepth)/F;
        T2 = (E+CollidedHalfDepth)/F;
        if (T1>T2)
        {
            real64 w=T1;T1=T2;T2=w;
        }
        if ( T2 < TMax )
        {
            TMax = T2;
        }
        if ( T1 >= TMin )
        {
            TMin = T1;
        }
        if (TMax < TMin )
        {
            goto NEXTENTITYCLOSESTTORAY;
        }
        
        //----------
        
        if(TMin != 0)
        {
            if(TMin < ClosestHit)
            {
                ClosestHit = TMin;
                if(Distance)
                {
                    *Distance = TMin;
                }
                ClosestHitIndex = Index;
            }
        }
        NEXTENTITYCLOSESTTORAY:;
    }
    return(ClosestHitIndex);
}

//----------
//----------
//----------
//----------

//----------

internal int32
NearestLevelToRayChungus(v3 RayOrigin,
                         v3 RayDir,
                         real64* Distance,
                         game_state* GameState,
                         stretchy_buffer_list* StretchyBuffers)
{
    int32 ClosestHitIndex = -1;
    real64 ClosestHit = REAL64Max;
    Normalize(RayDir);
    for (uint32 i = 0 ; i < GameState->LevelEntitiesCreated; ++i)
    {
        uint32 Index = i;
        real64 CollidedHalfWidth = GameState->LevelEntities.HalfWidth[Index];
        real64 CollidedHalfHeight = GameState->LevelEntities.HalfHeight[Index];
        real64 CollidedHalfDepth = GameState->LevelEntities.HalfDepth[Index];
        v3 YBasis = {
            GameState->LevelEntities.YBasis[Index].x,
            GameState->LevelEntities.YBasis[Index].y,
            0
        };
        v3 XBasis = -Perp(YBasis);
        v3 Position = GameState->LevelEntities.Position[Index];
        uint8 LevelType = GameState->LevelEntities.LevelType[Index];
        if(LevelType == LEVELTYPE_COLLIDESLOPE)
        {
            YBasis.x = YBasis.x*CollidedHalfHeight;
            YBasis.y = YBasis.y*CollidedHalfHeight;
            YBasis.z = CollidedHalfDepth;
            real64 NewHeight = SquareRoot(YBasis.x*YBasis.x + YBasis.y*YBasis.y + YBasis.z*YBasis.z);
            CollidedHalfHeight = NewHeight;
            NewHeight = 1/NewHeight;
            YBasis.x = YBasis.x*NewHeight;
            YBasis.y = YBasis.y*NewHeight;
            YBasis.z = YBasis.z*NewHeight;
            CollidedHalfDepth = 0;
        }
        v3 ZBasis = Cross(XBasis,YBasis);
        v3 Delta = Position - RayOrigin;
        real64 TMin = 0;
        real64 TMax = REAL64Max;
        
        //----------XAxis
        
        real64 E = Inner(XBasis,Delta);
        real64 F = Inner(RayDir,XBasis);
        real64 T1 = (E-CollidedHalfWidth)/F;
        real64 T2 = (E+CollidedHalfWidth)/F;
        if (T1>T2)
        {
            real64 w=T1;T1=T2;T2=w;
        }
        if ( T2 < TMax )
        {
            TMax = T2;
        }
        if ( T1 >= TMin )
        {
            TMin = T1;
        }
        if (TMax < TMin )
        {
            goto NEXTENTITYCLOSESTTORAYDAFTCUNT;
        }
        
        //----------YAxis
        
        E = Inner(YBasis,Delta);
        F = Inner(RayDir,YBasis);
        T1 = (E-CollidedHalfHeight)/F;
        T2 = (E+CollidedHalfHeight)/F;
        if (T1>T2)
        {
            real64 w=T1;T1=T2;T2=w;
        }
        if ( T2 < TMax )
        {
            TMax = T2;
        }
        if ( T1 >= TMin )
        {
            TMin = T1;
        }
        if (TMax < TMin )
        {
            goto NEXTENTITYCLOSESTTORAYDAFTCUNT;
        }
        
        //----------ZAxis
        
        E = Inner(ZBasis,Delta);
        F = Inner(RayDir,ZBasis);
        T1 = (E-CollidedHalfDepth)/F;
        T2 = (E+CollidedHalfDepth)/F;
        if (T1>T2)
        {
            real64 w=T1;T1=T2;T2=w;
        }
        if ( T2 < TMax )
        {
            TMax = T2;
        }
        if ( T1 >= TMin )
        {
            TMin = T1;
        }
        if (TMax < TMin )
        {
            goto NEXTENTITYCLOSESTTORAYDAFTCUNT;
        }
        
        //----------
        
        if(TMin != 0)
        {
            if(TMin < ClosestHit)
            {
                ClosestHit = TMin;
                if(Distance)
                {
                    *Distance = TMin;
                }
                ClosestHitIndex = Index;
            }
        }
        NEXTENTITYCLOSESTTORAYDAFTCUNT:;
    }
    return(ClosestHitIndex);
}

//----------
//----------
//----------
//----------


//------------------------------

internal bool32 GetActiveEntity(game_state* GameState,game_player_input* PlayerInput,debug_struct* DebugStruct,stretchy_buffer_list* StretchyBuffers)
{
    render_area RenderArea = GameState->RenderArea;
    uint32 LevelIndexHit = NearestLevelToRay(RenderArea.TargetPos,DebugStruct->UnitWorldMouseRay,0,GameState,StretchyBuffers);
    //----------
    ResetUndo(DebugStruct);
    if(LevelIndexHit != -1)
    {
        if(PlayerInput->InputInstant & CONTROLKEY_INPUT)
        {
            for(int32 i = 0;i<DebugStruct->NumOfActiveEntities;++i)
            {
                if(DebugStruct->ActiveGroupIndex[i] == LevelIndexHit)
                {
                    for(int32 x = i;x<DebugStruct->NumOfActiveEntities;++x)
                    {
                        DebugStruct->ActiveGroupIndex[x] = DebugStruct->ActiveGroupIndex[x+1];
                    }
                    --DebugStruct->NumOfActiveEntities;
                    goto DUPLICATEHITINDEX;
                }
            }
            DebugStruct->ActiveGroupIndex[DebugStruct->NumOfActiveEntities] = LevelIndexHit;
            ++DebugStruct->NumOfActiveEntities;
            DUPLICATEHITINDEX:;
            v3 ActiveGroupCenter = {};
            for(int32 i = 0;i<DebugStruct->NumOfActiveEntities;++i)
            {
                ActiveGroupCenter.x += GameState->LevelEntities.Position[DebugStruct->ActiveGroupIndex[i]].x;
                ActiveGroupCenter.y += GameState->LevelEntities.Position[DebugStruct->ActiveGroupIndex[i]].y;
                ActiveGroupCenter.z += GameState->LevelEntities.Position[DebugStruct->ActiveGroupIndex[i]].z;
            }
            ActiveGroupCenter /= DebugStruct->NumOfActiveEntities;
            DebugStruct->ActiveGroupCenter = ActiveGroupCenter;
            for(int32 i = 0;i<DebugStruct->NumOfActiveEntities;++i)
            {
                DebugStruct->ActiveGroupOffsets[i] = GameState->LevelEntities.Position[DebugStruct->ActiveGroupIndex[i]] - ActiveGroupCenter;
            }
            DebugStruct->ActiveGroupYBasis = {0,1};
        }
        else
        {
            DebugStruct->NumOfActiveEntities = 1;
            DebugStruct->ActiveGroupIndex[0] = LevelIndexHit;
            DebugStruct->ActiveGroupCenter = GameState->LevelEntities.Position[LevelIndexHit];
            DebugStruct->ActiveGroupYBasis = GameState->LevelEntities.YBasis[LevelIndexHit];
            DebugStruct->ActiveGroupOffsets[0] = {0,0,0};
        }
        return(1);
    }
    else
    {
        DebugStruct->DebugState &= ~DEBUG_SHOW_ACTIVE_ENTITY;
        DebugStruct->NumOfActiveEntities = 0;
        return(0);
    }
}

//------------------------------

internal void
CopyActiveEntity(game_state* GameState,debug_struct* DebugStruct,game_memory* GameMemory)
{
    for(int32 i = 0; i<DebugStruct->NumOfActiveEntities;++i)
    {
        int32 Source = DebugStruct->ActiveGroupIndex[i];
        uint32 Dest = GameState->LevelEntitiesCreated;
        GameState->LevelEntities.LevelType[Dest] = GameState->LevelEntities.LevelType[Source];
        GameState->LevelEntities.TextureIndex[Dest] = GameState->LevelEntities.TextureIndex[Source];
        GameState->LevelEntities.HalfWidth[Dest] = GameState->LevelEntities.HalfWidth[Source];
        GameState->LevelEntities.HalfHeight[Dest] = GameState->LevelEntities.HalfHeight[Source];
        GameState->LevelEntities.HalfDepth[Dest] = GameState->LevelEntities.HalfDepth[Source];
        GameState->LevelEntities.AABBHalfLength[Dest] = GameState->LevelEntities.AABBHalfLength[Source];
        GameState->LevelEntities.Position[Dest] = GameState->LevelEntities.Position[Source];
        GameState->LevelEntities.BoundingBox[Dest] = GameState->LevelEntities.BoundingBox[Source];
        GameState->LevelEntities.YBasis[Dest] = GameState->LevelEntities.YBasis[Source];
        AddEntityToPartition({PARTITIONTYPE_LEVEL,Dest},GameState,GameMemory);
        ++GameState->LevelEntitiesCreated;
    }
}

//------------------------------

internal real64
SnapActiveToFloor(game_state* GameState,debug_struct* DebugStruct,stretchy_buffer_list* StretchyBuffers)
{
    real64 LowestPointInActive = REAL64Max;
    int32 LowestIndex = -1;
    for(int32 i = 0;i<DebugStruct->NumOfActiveEntities;++i)
    {
        if((GameState->LevelEntities.Position[DebugStruct->ActiveGroupIndex[i]].z - GameState->LevelEntities.HalfDepth[DebugStruct->ActiveGroupIndex[i]]) < LowestPointInActive)
        {
            LowestPointInActive = (GameState->LevelEntities.Position[DebugStruct->ActiveGroupIndex[i]].z - GameState->LevelEntities.HalfDepth[DebugStruct->ActiveGroupIndex[i]]);
            LowestIndex = DebugStruct->ActiveGroupIndex[i];
        }
    }
    if(LowestIndex != -1)
    {
        real64 Distance = 0;
        int32 NearestLevel = NearestLevelToRay({GameState->LevelEntities.Position[LowestIndex].x,
                                               GameState->LevelEntities.Position[LowestIndex].y,
                                               LowestPointInActive},
                                               {0,0,-1},
                                               &Distance,
                                               GameState,StretchyBuffers);
        if(NearestLevel != -1)
        {
            DebugStruct->UndoInfo.AddUndo=UNDOTYPE_MOVE;
            return(-Distance);
        }
    }
    return(0);
}

//----------

internal void
HandleDebugInput(game_player_input* PlayerInput,debug_struct* DebugStruct)
{
    DebugStruct->UnitWorldMouseRay =
    {
        (PlayerInput->ScreenMouseX-0.5)*VIDEO_BUFFER_WIDTH,
        (PlayerInput->ScreenMouseY-0.5)*VIDEO_BUFFER_HEIGHT,
        -1000
    };
    Normalize(DebugStruct->UnitWorldMouseRay);
    //----------
    
    if(PlayerInput->InputInit & EKEY_INPUT)
    {
        DebugStruct->DebugState &= ~(DEBUG_EDIT_ENTITY_ROTATION|DEBUG_EDIT_ENTITY_TEXTURE|DEBUG_EDIT_ENTITY_SCALE|DEBUG_EDIT_ENTITY_TYPE);
        DebugStruct->DebugState ^= DEBUG_EDIT_ENTITY_POSITION;
    }
    else if(PlayerInput->InputInit & RKEY_INPUT)
    {
        DebugStruct->DebugState &= ~(DEBUG_EDIT_ENTITY_POSITION|DEBUG_EDIT_ENTITY_TEXTURE|DEBUG_EDIT_ENTITY_SCALE|DEBUG_EDIT_ENTITY_TYPE);
        DebugStruct->DebugState ^= DEBUG_EDIT_ENTITY_ROTATION;
    }
    else if(PlayerInput->InputInit & TKEY_INPUT)
    {
        DebugStruct->DebugState &= ~(DEBUG_EDIT_ENTITY_POSITION|DEBUG_EDIT_ENTITY_ROTATION|DEBUG_EDIT_ENTITY_SCALE|DEBUG_EDIT_ENTITY_TYPE);
        DebugStruct->DebugState ^= DEBUG_EDIT_ENTITY_TEXTURE;
    }
    else if(PlayerInput->InputInit & YKEY_INPUT)
    {
        DebugStruct->DebugState &= ~(DEBUG_EDIT_ENTITY_POSITION|DEBUG_EDIT_ENTITY_ROTATION|DEBUG_EDIT_ENTITY_TEXTURE|DEBUG_EDIT_ENTITY_TYPE);
        DebugStruct->DebugState ^= DEBUG_EDIT_ENTITY_SCALE;
    }
    else if(PlayerInput->InputInit & UKEY_INPUT)
    {
        DebugStruct->DebugState &= ~(DEBUG_EDIT_ENTITY_POSITION|DEBUG_EDIT_ENTITY_ROTATION|DEBUG_EDIT_ENTITY_TEXTURE|DEBUG_EDIT_ENTITY_SCALE);
        DebugStruct->DebugState ^= DEBUG_EDIT_ENTITY_TYPE;
    }
    //----------
    
    if(PlayerInput->InputInit & ESCAPEKEY_INPUT)
    {
        DebugStruct->DebugState &= ~DEBUG_SHOW_ACTIVE_ENTITY;
        DebugStruct->NumOfActiveEntities = 0;
    }
    //----------
    
    if(PlayerInput->InputInstant & LEFTCLICKMOUSE_INPUT)
    {
        DebugStruct->ClickAcumulationX += PlayerInput->MouseDeltaX;
        DebugStruct->ClickAcumulationY += PlayerInput->MouseDeltaY;
    }
    else
    {
        DebugStruct->ClickedButtonIndex = 0;
        DebugStruct->ClickAcumulationX = 0;
        DebugStruct->ClickAcumulationY = 0;
        DebugStruct->ClickAcumulationActivationX = 0;
        DebugStruct->ClickAcumulationActivationY = 0;
        if(DebugStruct->UndoInfo.AddUndo)
        {
            DebugStruct->UndoInfo.AddUndo = 0;
            DebugStruct->UndoInfo.UndoType[DebugStruct->UndoInfo.CurrentUndo] = DebugStruct->UndoInfo.UndoType[DebugStruct->UndoInfo.NumOfUndo];
            DebugStruct->UndoInfo.UndoChange[DebugStruct->UndoInfo.CurrentUndo] = DebugStruct->UndoInfo.UndoChange[DebugStruct->UndoInfo.NumOfUndo];
            ++DebugStruct->UndoInfo.CurrentUndo;
            DebugStruct->UndoInfo.NumOfUndo = DebugStruct->UndoInfo.CurrentUndo;
            for(uint32 i = DebugStruct->UndoInfo.CurrentUndo;i<100;++i)
            {
                DebugStruct->UndoInfo.UndoType[i] = {};
                DebugStruct->UndoInfo.UndoChange[i] = {};
            }
        }
    }
}

//------------------------------

internal void
DebugPass(game_memory* GameMemory,
          game_player_input* PlayerInput,
          game_state* GameState,
          debug_struct* DebugStruct,
          stretchy_buffer_list* StretchyBuffers,
          game_timers* GameTimers)
{
    /*------------------------------
    if(NearestLevelToRay(GameState->RenderArea.TargetPos,DebugStruct->UnitWorldMouseRay,0,GameState,StretchyBuffers) != NearestLevelToRayChungus(GameState->RenderArea.TargetPos,DebugStruct->UnitWorldMouseRay,0,GameState,StretchyBuffers))
    {
        GameTimers->MilliSecondsElapsed = 0;
        GameTimers->SecondsElapsed = 0;
        NearestLevelToRay(GameState->RenderArea.TargetPos,DebugStruct->UnitWorldMouseRay,0,GameState,StretchyBuffers);
        NearestLevelToRayChungus(GameState->RenderArea.TargetPos,DebugStruct->UnitWorldMouseRay,0,GameState,StretchyBuffers);
        HandleDebugInput(PlayerInput,DebugStruct);
    }
    ------------------------------*/
    SetGroupHUDVisibility(GROUPHUDID_DEBUGGROUPGRIDBUTTONS,1,DebugStruct);
    SetGroupHUDVisibility(GROUPHUDID_DEBUGGROUPCREATEENTITY,1,DebugStruct);
    
    /*------------------------------
    DebugValue(HUDDATATYPE_UINT64,&GameState->PlayerEntities.PlayerState[GameState->UserInformation.PlayerIndex],"State : ",DebugStruct);
    DebugValue(HUDDATATYPE_REAL64,&GameState->PlayerEntities.Velocity[GameState->UserInformation.PlayerIndex].y,"VelocityY : ",DebugStruct);
    DebugValue(HUDDATATYPE_REAL64,&GameState->PlayerEntities.Velocity[GameState->UserInformation.PlayerIndex].z,"VelocityZ : ",DebugStruct);
    ------------------------------*/
    DebugValue(HUDDATATYPE_REAL64,&GameState->PlayerEntities.Position[GameState->UserInformation.PlayerIndex].z,"PosZ : ",DebugStruct);
    DebugValue(HUDDATATYPE_REAL64,&GameState->PlayerEntities.Position[GameState->UserInformation.PlayerIndex].y,"PosY : ",DebugStruct);
    DebugValue(HUDDATATYPE_REAL64,&GameState->PlayerEntities.Position[GameState->UserInformation.PlayerIndex].x,"PosX : ",DebugStruct);
    DebugValue(HUDDATATYPE_REAL64,&GameState->PlayerEntities.Velocity[GameState->UserInformation.PlayerIndex].z,"MovZ : ",DebugStruct);
    DebugValue(HUDDATATYPE_REAL64,&GameState->PlayerEntities.Velocity[GameState->UserInformation.PlayerIndex].y,"MovY : ",DebugStruct);
    DebugValue(HUDDATATYPE_REAL64,&GameState->PlayerEntities.Velocity[GameState->UserInformation.PlayerIndex].x,"MovX : ",DebugStruct);
    DebugValue(HUDDATATYPE_REAL64,&GameTimers->MilliSecondsElapsed,"MS/f : ",DebugStruct);
    //----------
    HandleDebugInput(PlayerInput,DebugStruct);
    
    //----------
    if(PlayerInput->InputInit & LEFTCLICKMOUSE_INPUT)
    {
        if(ButtonWasClicked(HUDID_CREATEENTITY,DebugStruct))//----------create an Entity?
        {
            uint32 Index = CreateLevel(GameState->RenderArea.TargetPos.x, GameState->RenderArea.TargetPos.y, (GameState->RenderArea.TargetPos.z-1000),// pos
                                       MetersToPixels(1.28f),MetersToPixels(1.28f),MetersToPixels(1.28f),// dimensions
                                       0,// rotation
                                       0,0,// texture offset x,y
                                       TEXTURENAME_DEFAULT,// texture name
                                       1,// texture repeat scale
                                       LEVELTYPE_COLLIDE,// entity type
                                       GameState,GameMemory);
            DebugStruct->ActiveGroupCenter = GameState->LevelEntities.Position[Index];
            DebugStruct->ActiveGroupOffsets[0] = {0,0,0};
            DebugStruct->ActiveGroupIndex[0] = Index;
            DebugStruct->ActiveGroupYBasis = GameState->LevelEntities.YBasis[Index];
            DebugStruct->NumOfActiveEntities = 1;
            ResetUndo(DebugStruct);
            DebugStruct->DebugState |= DEBUG_SHOW_ACTIVE_ENTITY;
            DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGHALFWIDTH] = &GameState->LevelEntities.HalfWidth[Index];
            DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGHALFHEIGHT] = &GameState->LevelEntities.HalfHeight[Index];
            DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGHALFDEPTH] = &GameState->LevelEntities.HalfDepth[Index];
            DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGTEXTUREOFFSETX] = &GameState->LevelEntities.TextureIndex[Index].TextureOffsetX;
            DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGTEXTUREOFFSETY] = &GameState->LevelEntities.TextureIndex[Index].TextureOffsetY;
            DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGTEXTUREREPEATSCALE] = &GameState->LevelEntities.TextureIndex[Index].TextureRepeatScale;
            DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGENTITYTYPE] = &GameState->LevelEntities.LevelType[Index];
        }
        
        else if(DebugStruct->ClickedButtonIndex == 0)//----------was an entity selected?
        {
            if(GetActiveEntity(GameState,PlayerInput,DebugStruct,StretchyBuffers))
            {
                DebugStruct->DebugState |= DEBUG_SHOW_ACTIVE_ENTITY;
                if(DebugStruct->NumOfActiveEntities > 1)
                {
                    DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGHALFWIDTH] = 0;
                    DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGHALFHEIGHT] = 0;
                    DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGHALFDEPTH] = 0;
                    DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGTEXTUREOFFSETX] = 0;
                    DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGTEXTUREOFFSETY] = 0;
                    DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGTEXTUREREPEATSCALE] = 0;
                    DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGENTITYTYPE] = 0;
                    DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGINDEXNUMBER] = 0;
                }
                else
                {
                    uint32 Index = DebugStruct->ActiveGroupIndex[0];
                    DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGHALFWIDTH] = &GameState->LevelEntities.HalfWidth[Index];
                    DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGHALFHEIGHT] = &GameState->LevelEntities.HalfHeight[Index];
                    DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGHALFDEPTH] = &GameState->LevelEntities.HalfDepth[Index];
                    DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGTEXTUREOFFSETX] = &GameState->LevelEntities.TextureIndex[Index].TextureOffsetX;
                    DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGTEXTUREOFFSETY] = &GameState->LevelEntities.TextureIndex[Index].TextureOffsetY;
                    DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGTEXTUREREPEATSCALE] = &GameState->LevelEntities.TextureIndex[Index].TextureRepeatScale;
                    DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGENTITYTYPE] = &GameState->LevelEntities.LevelType[Index];
                    DebugStruct->DebugHUDElements.AttachedValue[HUDID_DEBUGINDEXNUMBER] = &DebugStruct->ActiveGroupIndex[0];
                }
            }
        }
    }
    //------------------------------
    
    if(DebugStruct->DebugState & DEBUG_SHOW_ACTIVE_ENTITY)
    {
        for(int32 i = 0;i<DebugStruct->NumOfActiveEntities;++i)
        {
            int32 Index = DebugStruct->ActiveGroupIndex[i];
            RenderDebugCube(GameState->LevelEntities.Position[Index],
                            {(real32)GameState->LevelEntities.HalfWidth[Index]*2.1f+10,
                            (real32)GameState->LevelEntities.HalfHeight[Index]*2.1f+10,
                            (real32)GameState->LevelEntities.HalfDepth[Index]*2.1f+10},
                            {GameState->LevelEntities.YBasis[Index].x,
                            GameState->LevelEntities.YBasis[Index].y,
                            0},
                            TEXTURENAME_SELECTED,
                            GameState);
        }
        if(PlayerInput->InputInstant & CONTROLKEY_INPUT && PlayerInput->InputInit & VKEY_INPUT)
        {
            CopyActiveEntity(GameState,DebugStruct,GameMemory);
        }
        else
        {
            real64 ActiveEntityOriginZScaleFactor = (GameState->RenderArea.TargetPos.z - DebugStruct->ActiveGroupCenter.z)/1000.0;
            v3 PosChange = {};
            v3 ScaleChange = {};
            real64 IncreaseMultiplier = 1;
            real64 Degrees = (ArcSine(DebugStruct->ActiveGroupYBasis.y) * 57.295779513082320876798154814105);real64 DegreeDelta = 0;
            if(DebugStruct->ActiveGroupYBasis.x < 0)
            {
                Degrees = 180 - Degrees;
            }
            
            //----------edit pos
            
            if(DebugStruct->DebugState & DEBUG_EDIT_ENTITY_POSITION)
            {
                SetGroupHUDVisibility(GROUPHUDID_DEBUGGROUPMOVE,1,DebugStruct);
                if(PlayerInput->InputInit & ENDKEY_INPUT)
                {
                    PosChange.z = SnapActiveToFloor(GameState,DebugStruct,StretchyBuffers);
                }
                else
                {
                    v3 Change = {PlayerInput->MouseDeltaX * ActiveEntityOriginZScaleFactor,
                        PlayerInput->MouseDeltaY * ActiveEntityOriginZScaleFactor,PlayerInput->MouseDeltaY * ActiveEntityOriginZScaleFactor};
                    if(DebugStruct->DebugHUDElements.IsActive[HUDID_DEBUGGRIDMOVE])
                    {
                        Change = {};
                        if(DebugStruct->EditPositionValue > 0)
                        {
                            if( DebugStruct->ClickAcumulationX - DebugStruct->ClickAcumulationActivationX > DebugStruct->EditPositionValue)
                            {
                                Change.x = DebugStruct->EditPositionValue;
                            }
                            else if( DebugStruct->ClickAcumulationX - DebugStruct->ClickAcumulationActivationX < -DebugStruct->EditPositionValue)
                            {
                                Change.x = -DebugStruct->EditPositionValue;
                            }
                            if(Change.x)
                            {
                                Change.x -= (int32)DebugStruct->ActiveGroupCenter.x % DebugStruct->EditPositionValue;
                                Change.x -= DebugStruct->ActiveGroupCenter.x - (int32)DebugStruct->ActiveGroupCenter.x;
                                DebugStruct->ClickAcumulationActivationX = DebugStruct->ClickAcumulationX;
                            }
                            if( DebugStruct->ClickAcumulationY - DebugStruct->ClickAcumulationActivationY > DebugStruct->EditPositionValue)
                            {
                                Change.y = DebugStruct->EditPositionValue;
                            }
                            else if( DebugStruct->ClickAcumulationY - DebugStruct->ClickAcumulationActivationY < -DebugStruct->EditPositionValue)
                            {
                                Change.y = -DebugStruct->EditPositionValue;
                            }
                            if(Change.y)
                            {
                                Change.z = -Change.y;
                                Change.y -= (int32)DebugStruct->ActiveGroupCenter.y % DebugStruct->EditPositionValue;
                                Change.y -= DebugStruct->ActiveGroupCenter.y - (int32)DebugStruct->ActiveGroupCenter.y;
                                Change.z -= (int32)DebugStruct->ActiveGroupCenter.z % DebugStruct->EditPositionValue;
                                Change.z -= DebugStruct->ActiveGroupCenter.z - (int32)DebugStruct->ActiveGroupCenter.z;
                                DebugStruct->ClickAcumulationActivationY = DebugStruct->ClickAcumulationY;
                            }
                        }
                    }
                    if(ButtonWasClicked(HUDID_DEBUGMOVEX,DebugStruct))
                    {
                        PosChange.x = Change.x;DebugStruct->UndoInfo.AddUndo=UNDOTYPE_MOVE;
                    }
                    else if(ButtonWasClicked(HUDID_DEBUGMOVEY,DebugStruct))
                    {
                        PosChange.y = Change.y;DebugStruct->UndoInfo.AddUndo=UNDOTYPE_MOVE;
                    }
                    else if(ButtonWasClicked(HUDID_DEBUGMOVEZ,DebugStruct))
                    {
                        PosChange.z = Change.z;DebugStruct->UndoInfo.AddUndo=UNDOTYPE_MOVE;
                    }
                    else if(ButtonWasClicked(HUDID_DEBUGMOVEXY,DebugStruct))
                    {
                        PosChange.x = Change.x;PosChange.y = Change.y;DebugStruct->UndoInfo.AddUndo=UNDOTYPE_MOVE;
                    }
                }
            }
            
            //----------edit rot
            
            else if(DebugStruct->DebugState & DEBUG_EDIT_ENTITY_ROTATION)
            {
                DegreeDelta = Degrees;
                SetGroupHUDVisibility(GROUPHUDID_DEBUGGROUPROTATE,1,DebugStruct);
                if(DebugStruct->DebugHUDElements.IsActive[HUDID_DEBUGGRIDROTATE])
                {
                    if(DebugStruct->EditRotationValue > 0)
                    {
                        if( DebugStruct->ClickAcumulationX - DebugStruct->ClickAcumulationActivationX > DebugStruct->EditRotationValue)
                        {
                            DegreeDelta = (DegreeDelta-DebugStruct->EditRotationValue);
                            DebugStruct->ClickAcumulationActivationX = DebugStruct->ClickAcumulationX;
                        }
                        else if( DebugStruct->ClickAcumulationX - DebugStruct->ClickAcumulationActivationX < -DebugStruct->EditRotationValue)
                        {
                            DegreeDelta = (DegreeDelta+DebugStruct->EditRotationValue);
                            DebugStruct->ClickAcumulationActivationX = DebugStruct->ClickAcumulationX;
                        }
                    }
                }
                else
                {
                    DegreeDelta += (real64)-PlayerInput->MouseDeltaX;
                }
                if(ButtonWasClicked(HUDID_DEBUGROTATEAXIS,DebugStruct))
                {
                    DebugStruct->UndoInfo.AddUndo=UNDOTYPE_ROTATE;
                    DegreeDelta = DegreeDelta - Degrees;
                }
                else
                {
                    DegreeDelta = 0;
                }
                if(DebugStruct->NumOfActiveEntities > 1)
                {
                    DebugStruct->DebugHUDGroups.YBasis[GROUPHUDID_DEBUGGROUPROTATE] = DebugStruct->ActiveGroupYBasis;
                }
                else
                {
                    DebugStruct->DebugHUDGroups.YBasis[GROUPHUDID_DEBUGGROUPROTATE] = GameState->LevelEntities.YBasis[DebugStruct->ActiveGroupIndex[0]];
                }
            }
            
            //----------edit texture
            
            else if(DebugStruct->DebugState & DEBUG_EDIT_ENTITY_TEXTURE)
            {
                SetGroupHUDVisibility(GROUPHUDID_DEBUGGROUPTEXTURE,1,DebugStruct);
                real64 TextureScaleValueX = 1.0/128.0 * (-PlayerInput->MouseDeltaX);
                real64 TextureScaleValueY = 1.0/128.0 * (-PlayerInput->MouseDeltaY);
                int8 TextureChange = 0;
                real32 RepeatChange = 0;
                if(PlayerInput->InputInit & LEFTKEY_INPUT)
                {
                    TextureChange -= 1;
                }
                else if(PlayerInput->InputInit & RIGHTKEY_INPUT)
                {
                    TextureChange += 1;
                }
                else if( PlayerInput->InputInit & UPKEY_INPUT)
                {
                    RepeatChange += 0.25;
                }
                else if( PlayerInput->InputInit & DOWNKEY_INPUT)
                {
                    RepeatChange -= 0.25;
                }
                for(int32 i = 0;i<DebugStruct->NumOfActiveEntities;++i)
                {
                    int32 Index = DebugStruct->ActiveGroupIndex[i];
                    GameState->LevelEntities.TextureIndex[Index].TextureLayer += TextureChange;
                    GameState->LevelEntities.TextureIndex[Index].TextureRepeatScale += RepeatChange;
                    if(GameState->LevelEntities.TextureIndex[Index].TextureRepeatScale < 0)
                    {
                        GameState->LevelEntities.TextureIndex[Index].TextureRepeatScale = 0;
                    }
                }
                if(ButtonWasClicked(HUDID_DEBUGTEXTUREEDIT,DebugStruct))
                {
                    for(int32 i = 0;i<DebugStruct->NumOfActiveEntities;++i)
                    {
                        int32 Index = DebugStruct->ActiveGroupIndex[i];
                        GameState->LevelEntities.TextureIndex[Index].TextureOffsetX += (real32)TextureScaleValueX;
                        GameState->LevelEntities.TextureIndex[Index].TextureOffsetY += (real32)TextureScaleValueY;
                    }
                }
            }
            
            //----------edit scale
            
            else if(DebugStruct->DebugState & DEBUG_EDIT_ENTITY_SCALE)
            {
                v3 Change = {PlayerInput->MouseDeltaX * ActiveEntityOriginZScaleFactor,
                    PlayerInput->MouseDeltaY * ActiveEntityOriginZScaleFactor,PlayerInput->MouseDeltaY * ActiveEntityOriginZScaleFactor};
                if(DebugStruct->NumOfActiveEntities > 1)
                {
                    SetHUDVisibility(HUDID_DEBUGSCALEXY,1,DebugStruct);
                    if(ButtonWasClicked(HUDID_DEBUGSCALEXY,DebugStruct))
                    {
                        IncreaseMultiplier = ((PlayerInput->MouseDeltaX * ActiveEntityOriginZScaleFactor)/1000) + 1;
                        DebugStruct->UndoInfo.AddUndo=UNDOTYPE_SCALEUNIFORM;
                    }
                }
                else
                {
                    SetGroupHUDVisibility(GROUPHUDID_DEBUGGROUPSCALE,1,DebugStruct);
                    DebugStruct->DebugHUDGroups.YBasis[GROUPHUDID_DEBUGGROUPSCALE] = GameState->LevelEntities.YBasis[DebugStruct->ActiveGroupIndex[0]];
                    if(DebugStruct->DebugHUDElements.IsActive[HUDID_DEBUGGRIDSCALE])
                    {
                        int32 Index = DebugStruct->ActiveGroupIndex[0];
                        real64 HalfHeight = GameState->LevelEntities.HalfHeight[Index];
                        real64 HalfWidth = GameState->LevelEntities.HalfWidth[Index];
                        real64 HalfDepth = GameState->LevelEntities.HalfDepth[Index];
                        Change = {};
                        if(DebugStruct->EditScaleValue > 0)
                        {
                            if( DebugStruct->ClickAcumulationX - DebugStruct->ClickAcumulationActivationX > DebugStruct->EditScaleValue)
                            {
                                Change.x = DebugStruct->EditScaleValue;
                            }
                            else if( DebugStruct->ClickAcumulationX - DebugStruct->ClickAcumulationActivationX < -DebugStruct->EditScaleValue)
                            {
                                Change.x = -DebugStruct->EditScaleValue;
                            }
                            if(Change.x)
                            {
                                Change.x -= (int32)HalfWidth % DebugStruct->EditScaleValue;
                                Change.x -= HalfWidth - (int32)HalfWidth;
                                DebugStruct->ClickAcumulationActivationX = DebugStruct->ClickAcumulationX;
                            }
                            if( DebugStruct->ClickAcumulationY - DebugStruct->ClickAcumulationActivationY > DebugStruct->EditScaleValue)
                            {
                                Change.y = DebugStruct->EditScaleValue;
                            }
                            else if( DebugStruct->ClickAcumulationY - DebugStruct->ClickAcumulationActivationY < -DebugStruct->EditScaleValue)
                            {
                                Change.y = -DebugStruct->EditScaleValue;
                            }
                            if(Change.y)
                            {
                                Change.z = -Change.y;
                                Change.y -= (int32)HalfHeight % DebugStruct->EditScaleValue;
                                Change.y -= HalfHeight - (int32)HalfHeight;
                                Change.z -= (int32)HalfDepth % DebugStruct->EditScaleValue;
                                Change.z -= HalfDepth - (int32)HalfDepth;
                                DebugStruct->ClickAcumulationActivationY = DebugStruct->ClickAcumulationY;
                            }
                        }
                    }
                    if(ButtonWasClicked(HUDID_DEBUGSCALEX,DebugStruct))
                    {
                        ScaleChange.x = Change.x;DebugStruct->UndoInfo.AddUndo=UNDOTYPE_SCALE;
                    }
                    else if(ButtonWasClicked(HUDID_DEBUGSCALEY,DebugStruct))
                    {
                        ScaleChange.y = Change.y;DebugStruct->UndoInfo.AddUndo=UNDOTYPE_SCALE;
                    }
                    else if(ButtonWasClicked(HUDID_DEBUGSCALEZ,DebugStruct))
                    {
                        ScaleChange.z = Change.z;DebugStruct->UndoInfo.AddUndo=UNDOTYPE_SCALE;
                    }
                    else if(ButtonWasClicked(HUDID_DEBUGSCALEXY,DebugStruct))
                    {
                        ScaleChange.x = Change.x;ScaleChange.y = Change.y;DebugStruct->UndoInfo.AddUndo=UNDOTYPE_SCALE;
                    }
                }
            }
            
            //----------edit type
            
            else if(DebugStruct->DebugState & DEBUG_EDIT_ENTITY_TYPE)
            {
                if(DebugStruct->NumOfActiveEntities == 1)
                {
                    SetGroupHUDVisibility(GROUPHUDID_DEBUGGROUPTYPE,1,DebugStruct);
                    int32 Index = DebugStruct->ActiveGroupIndex[0];
                    if(PlayerInput->InputInit & LEFTKEY_INPUT)
                    {
                        GameState->LevelEntities.LevelType[Index] -= 1;
                    }
                    else if(PlayerInput->InputInit & RIGHTKEY_INPUT)
                    {
                        GameState->LevelEntities.LevelType[Index] += 1;
                    }
                    if(GameState->LevelEntities.LevelType[Index] < 1)
                    {
                        GameState->LevelEntities.LevelType[Index] = 1;
                    }
                    else if(GameState->LevelEntities.LevelType[Index] > 255)
                    {
                        GameState->LevelEntities.LevelType[Index] = 255;
                    }
                    sprintf(DebugStruct->DebugHUDElements.AttachedString[HUDID_DEBUGENTITYTYPE],"%s",HUDEntityTypeStrings[GameState->LevelEntities.LevelType[DebugStruct->ActiveGroupIndex[0]]]);
                }
            }
            
            //----------
            
            if(!DebugStruct->UndoInfo.AddUndo)
            {
                if(PlayerInput->InputInstant & CONTROLKEY_INPUT && PlayerInput->InputInit & ZKEY_INPUT||
                   PlayerInput->InputInstant & CONTROLKEY_INPUT && PlayerInput->InputInit & YKEY_INPUT)
                {
                    int8 Multiplier = 0;
                    int32 TargetUndoIndex = 0;
                    PosChange = {};
                    ScaleChange = {};
                    IncreaseMultiplier = 1;
                    DegreeDelta = 0;
                    if(PlayerInput->InputInit & ZKEY_INPUT)
                    {
                        if(DebugStruct->UndoInfo.CurrentUndo > 0)
                        {
                            Multiplier = -1;
                            --DebugStruct->UndoInfo.CurrentUndo;
                            TargetUndoIndex = DebugStruct->UndoInfo.CurrentUndo;
                        }
                    }
                    else if(PlayerInput->InputInit & YKEY_INPUT)
                    {
                        if(DebugStruct->UndoInfo.CurrentUndo < DebugStruct->UndoInfo.NumOfUndo)
                        {
                            Multiplier = 1;
                            TargetUndoIndex = DebugStruct->UndoInfo.CurrentUndo;
                            ++DebugStruct->UndoInfo.CurrentUndo;
                        }
                    }
                    if(Multiplier)
                    {
                        if(DebugStruct->UndoInfo.UndoType[TargetUndoIndex] == UNDOTYPE_MOVE)
                        {
                            PosChange = DebugStruct->UndoInfo.UndoChange[TargetUndoIndex] * Multiplier;
                        }
                        else if(DebugStruct->UndoInfo.UndoType[TargetUndoIndex] == UNDOTYPE_ROTATE)
                        {
                            DegreeDelta = DebugStruct->UndoInfo.UndoChange[TargetUndoIndex].x * Multiplier;
                        }
                        else if(DebugStruct->UndoInfo.UndoType[TargetUndoIndex] == UNDOTYPE_SCALE)
                        {
                            ScaleChange = DebugStruct->UndoInfo.UndoChange[TargetUndoIndex] * Multiplier;
                        }
                        else if(DebugStruct->UndoInfo.UndoType[TargetUndoIndex] == UNDOTYPE_SCALEUNIFORM)
                        {
                            if(Multiplier == -1)
                            {
                                IncreaseMultiplier = 1/DebugStruct->UndoInfo.UndoChange[TargetUndoIndex].x;
                            }
                            else
                            {
                                IncreaseMultiplier = DebugStruct->UndoInfo.UndoChange[TargetUndoIndex].x;
                            }
                        }
                    }
                }
            }
            
            //------------------------------
            
            Degrees += DegreeDelta;
            DebugStruct->ActiveGroupCenter += PosChange;
            DebugStruct->ActiveGroupYBasis = 
            {
                Cosine(Degrees*0.01745329251994329576923690768489),
                Sine(Degrees*0.01745329251994329576923690768489)
            };
            v2 GroupYBasis = DebugStruct->ActiveGroupYBasis;
            v2 GroupXBasis = -Perp(GroupYBasis);
            for(int32 i = 0;i<DebugStruct->NumOfActiveEntities;++i)
            {
                uint32 Index = DebugStruct->ActiveGroupIndex[i];
                if(GameState->LevelEntities.HalfWidth[Index] + ScaleChange.x < 0)
                {
                    ScaleChange.x = -GameState->LevelEntities.HalfWidth[Index];IncreaseMultiplier = 1;
                }
                GameState->LevelEntities.HalfWidth[Index] = (GameState->LevelEntities.HalfWidth[Index] + ScaleChange.x)*IncreaseMultiplier;
                if(GameState->LevelEntities.HalfHeight[Index] + ScaleChange.y < 0)
                {
                    ScaleChange.y = -GameState->LevelEntities.HalfHeight[Index];IncreaseMultiplier = 1;
                }
                GameState->LevelEntities.HalfHeight[Index] = (GameState->LevelEntities.HalfHeight[Index] + ScaleChange.y)*IncreaseMultiplier;
                if(GameState->LevelEntities.HalfDepth[Index] + ScaleChange.z < 0)
                {
                    ScaleChange.z = -GameState->LevelEntities.HalfDepth[Index];IncreaseMultiplier = 1;
                }
                GameState->LevelEntities.HalfDepth[Index] = (GameState->LevelEntities.HalfDepth[Index] + ScaleChange.z)*IncreaseMultiplier;
                real64 EntityDegrees = (ArcSine(GameState->LevelEntities.YBasis[Index].y) * 57.295779513082320876798154814105);
                if(GameState->LevelEntities.YBasis[Index].x < 0)
                {
                    EntityDegrees = 180 - EntityDegrees;
                }
                EntityDegrees += DegreeDelta;
                GameState->LevelEntities.YBasis[Index] = 
                {
                    Cosine(EntityDegrees*0.01745329251994329576923690768489),
                    Sine(EntityDegrees*0.01745329251994329576923690768489)
                };
                v3 Offsets = DebugStruct->ActiveGroupOffsets[i];
                Offsets =
                {//left multiply by inv mat for basis change. wiki=good
                    (Offsets.x*GroupYBasis.y)+(Offsets.y*-GroupXBasis.y),
                    (Offsets.x*-GroupYBasis.x)+(Offsets.y*GroupXBasis.x),
                    Offsets.z
                };
                DebugStruct->ActiveGroupOffsets[i] *= IncreaseMultiplier;
                GameState->LevelEntities.TextureIndex[Index].TextureRepeatScale *= (real32)(1.0/IncreaseMultiplier);
                real64 AABBHalfLength = {};
                if(GameState->LevelEntities.HalfHeight[Index] >= GameState->LevelEntities.HalfWidth[Index])
                {
                    AABBHalfLength = GameState->LevelEntities.HalfHeight[Index] * 1.4142135623730950488016887242097;
                }
                else
                {
                    AABBHalfLength = GameState->LevelEntities.HalfWidth[Index] * 1.4142135623730950488016887242097;
                }
                v3 Position = DebugStruct->ActiveGroupCenter + Offsets;
                GameState->LevelEntities.Position[Index] = Position;
                GameState->LevelEntities.AABBHalfLength[Index] = AABBHalfLength;
                AABB OldBounds = GameState->LevelEntities.BoundingBox[Index];
                AABB NewBounds = {};
                NewBounds.Origin.x = Position.x - AABBHalfLength;
                NewBounds.Origin.y = Position.y - AABBHalfLength;
                NewBounds.Origin.z = Position.z - GameState->LevelEntities.HalfDepth[Index];
                NewBounds.MaxX = Position.x + AABBHalfLength;
                NewBounds.MaxY = Position.y + AABBHalfLength;
                NewBounds.MaxZ = Position.z + GameState->LevelEntities.HalfDepth[Index];
                //----------Handling if spatial partition changes with move
                if((int32)OldBounds.Origin.x/PARTITION_DIMENSION != (int32)NewBounds.Origin.x/PARTITION_DIMENSION||
                   (int32)OldBounds.Origin.y/PARTITION_DIMENSION != (int32)NewBounds.Origin.y/PARTITION_DIMENSION||
                   (int32)OldBounds.Origin.z/PARTITION_DIMENSION != (int32)NewBounds.Origin.z/PARTITION_DIMENSION||
                   (int32)OldBounds.MaxX/PARTITION_DIMENSION != (int32)NewBounds.MaxX/PARTITION_DIMENSION||
                   (int32)OldBounds.MaxY/PARTITION_DIMENSION != (int32)NewBounds.MaxY/PARTITION_DIMENSION||
                   (int32)OldBounds.MaxZ/PARTITION_DIMENSION != (int32)NewBounds.MaxZ/PARTITION_DIMENSION)
                {
                    RemoveEntityFromPartition({PARTITIONTYPE_LEVEL,Index},GameState,GameMemory);
                    GameState->LevelEntities.BoundingBox[Index] = NewBounds;
                    AddEntityToPartition({PARTITIONTYPE_LEVEL,Index},GameState,GameMemory);
                }
                else
                {
                    GameState->LevelEntities.BoundingBox[Index] = NewBounds;
                }
            }
            
            //----------
            
            if(DebugStruct->UndoInfo.AddUndo)
            {
                DebugStruct->UndoInfo.UndoType[DebugStruct->UndoInfo.NumOfUndo] = DebugStruct->UndoInfo.AddUndo;
                if(DebugStruct->UndoInfo.AddUndo == UNDOTYPE_MOVE)
                {
                    DebugStruct->UndoInfo.UndoChange[DebugStruct->UndoInfo.NumOfUndo] += PosChange;
                }
                else if(DebugStruct->UndoInfo.AddUndo == UNDOTYPE_ROTATE)
                {
                    DebugStruct->UndoInfo.UndoChange[DebugStruct->UndoInfo.NumOfUndo].x += DegreeDelta;
                }
                else if(DebugStruct->UndoInfo.AddUndo == UNDOTYPE_SCALE)
                {
                    DebugStruct->UndoInfo.UndoChange[DebugStruct->UndoInfo.NumOfUndo] += ScaleChange;
                }
                else if(DebugStruct->UndoInfo.AddUndo == UNDOTYPE_SCALEUNIFORM)
                {
                    if(!DebugStruct->UndoInfo.UndoChange[DebugStruct->UndoInfo.NumOfUndo].x)
                    {
                        DebugStruct->UndoInfo.UndoChange[DebugStruct->UndoInfo.NumOfUndo].x = 1;
                    }
                    DebugStruct->UndoInfo.UndoChange[DebugStruct->UndoInfo.NumOfUndo].x *= IncreaseMultiplier;
                }
            }
        }
    }
    
    //----------level loading
    
    if(PlayerInput->InputInit & F1KEY_INPUT)
    {
        SaveLevel(GameMemory,GameState);
    }
    else if(PlayerInput->InputInit & F2KEY_INPUT)
    {
        DebugStruct->DebugState = 0;
        LoadLevel(GameMemory,GameState,StretchyBuffers);
    }
}