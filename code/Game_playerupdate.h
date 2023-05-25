internal void
PlayerCreate(real64 X,real64 Y,real64 Z,v2 YBasis,uint8 PlayerClass,game_state* GameState,game_memory* GameMemory)
{
    GameState->PlayerEntities.Class[GameState->ActivePlayers] = PlayerClass;
    GameState->PlayerEntities.TextureLayer[GameState->ActivePlayers] = TEXTURENAME_SOLDIER;
    if(PlayerClass == PLAYERCLASS_SOLDIER)
    {
        GameState->PlayerEntities.Speed[GameState->ActivePlayers] = HammerUnits(240);
    }
    GameState->PlayerEntities.HalfWidth[GameState->ActivePlayers] = PLAYER_HALFWIDTH;
    GameState->PlayerEntities.HalfHeight[GameState->ActivePlayers] = PLAYER_HALFHEIGHT;
    GameState->PlayerEntities.HalfDepth[GameState->ActivePlayers] = PLAYER_HALFDEPTH;
    v3 Position = {};
    Position.x = X;
    Position.y = Y;
    Position.z = Z;
    real64 AABBHalfLength;
    if(GameState->PlayerEntities.HalfHeight[GameState->ActivePlayers] >= GameState->PlayerEntities.HalfWidth[GameState->ActivePlayers])
    {
        AABBHalfLength = GameState->PlayerEntities.HalfHeight[GameState->ActivePlayers] * 1.4142135623730950488016887242097;
    }
    else
    {
        AABBHalfLength = GameState->PlayerEntities.HalfWidth[GameState->ActivePlayers] * 1.4142135623730950488016887242097;
    }
    GameState->PlayerEntities.AABBHalfLength[GameState->ActivePlayers] = AABBHalfLength;
    GameState->PlayerEntities.BoundingBox[GameState->ActivePlayers].Origin.x = Position.x - AABBHalfLength;
    GameState->PlayerEntities.BoundingBox[GameState->ActivePlayers].Origin.y = Position.y - AABBHalfLength;
    GameState->PlayerEntities.BoundingBox[GameState->ActivePlayers].Origin.z = Position.z - PLAYER_HALFDEPTH;
    GameState->PlayerEntities.BoundingBox[GameState->ActivePlayers].MaxX = Position.x + AABBHalfLength;
    GameState->PlayerEntities.BoundingBox[GameState->ActivePlayers].MaxY = Position.y + AABBHalfLength;
    GameState->PlayerEntities.BoundingBox[GameState->ActivePlayers].MaxZ = Position.z + PLAYER_HALFDEPTH;
    GameState->PlayerEntities.Position[GameState->ActivePlayers] = Position;
    GameState->PlayerEntities.YBasis[GameState->ActivePlayers] = YBasis;
    GameState->PlayerEntities.PlayerState[GameState->ActivePlayers] = {};
    GameState->PlayerEntities.Velocity[GameState->ActivePlayers] = {};
    if(!GameState->ActivePlayers)//dont follow on multiple spawns
    {
        GameState->UserInformation.PlayerIndex = GameState->ActivePlayers;
        GameState->RenderArea.CameraMode = CAMMODE_FOLLOWPLAYER;
        GameState->RenderArea.TargetPos = 
        {
            Position.x,
            Position.y,
            Position.z + DEFAULT_CAMERA_HEIGHT
        };
    }
    AddEntityToPartition({PARTITIONTYPE_PLAYER,GameState->ActivePlayers},GameState,GameMemory);
    ++GameState->ActivePlayers;
}

//----------

internal void
PlayerSpawn(uint8 PlayerClass,game_state* GameState,game_memory* GameMemory)
{
    uint32 RespawnIndex[64] = {};// TODO(NAME): This should be stretchy buffer (dont know how many spawn points will be on a level)
    uint8 NumOfSpawnPoints = 0;
    for(uint32 i = 0;i<GameState->LevelEntitiesCreated;++i)
    {
        if(GameState->LevelEntities.LevelType[i] == LEVELTYPE_PLAYERSPAWN)
        {
            RespawnIndex[NumOfSpawnPoints] = i;
            ++NumOfSpawnPoints;
        }
    }
    if(NumOfSpawnPoints != 0)
    {
        uint32 ChosenSpawnIndex = RespawnIndex[RandomChoice(&GameState->RandomState,NumOfSpawnPoints)];
        PlayerCreate(GameState->LevelEntities.Position[ChosenSpawnIndex].x,
                     GameState->LevelEntities.Position[ChosenSpawnIndex].y,
                     GameState->LevelEntities.Position[ChosenSpawnIndex].z,
                     GameState->LevelEntities.YBasis[ChosenSpawnIndex],
                     PlayerClass,
                     GameState,
                     GameMemory);
    }
}

//----------

internal bool32
TryUnduck(stretchy_buffer* HitIndex,
          v3 PlayerPos,
          real64 PlayerHalfWidth,
          real64 PlayerHalfDepth,
          v3 RayDir,
          game_state* GameState)
{
    real64 ClosestHit = REAL64Max;
    PlayerPos.z += PLAYER_SQUISHHEIGHT;
    for (uint32 i = 0 ; i < HitIndex->Size; ++i)
    {
        uint32 Index = *((uint32*)HitIndex->DataStart+i);
        v3 YBasis = {
            GameState->LevelEntities.YBasis[Index].x,
            GameState->LevelEntities.YBasis[Index].y,
            0
        };
        v3 XBasis = -Perp(YBasis);
        v3 CollidedPosition = GameState->LevelEntities.Position[Index];
        real64 CollidedHalfWidth = GameState->LevelEntities.HalfWidth[Index];
        real64 CollidedHalfHeight = GameState->LevelEntities.HalfHeight[Index];
        real64 CollidedHalfDepth = GameState->LevelEntities.HalfDepth[Index];
        uint8 LevelType = GameState->LevelEntities.LevelType[Index];
        if(LevelType == LEVELTYPE_WATER)
        {
            goto NEXTENTITYUNDUCK;
        }
        else if(LevelType == LEVELTYPE_COLLIDESLOPE)
        {
            CollidedPosition -= YBasis*PlayerHalfWidth;
            YBasis.x = YBasis.x*CollidedHalfHeight;
            YBasis.y = YBasis.y*CollidedHalfHeight;
            YBasis.z = CollidedHalfDepth;
            real64 NewHeight = SquareRoot(YBasis.x*YBasis.x + YBasis.y*YBasis.y + YBasis.z*YBasis.z);
            CollidedHalfHeight = NewHeight;
            NewHeight = 1/NewHeight;
            YBasis.x = YBasis.x*NewHeight;
            YBasis.y = YBasis.y*NewHeight;
            YBasis.z = YBasis.z*NewHeight;
        }
        v3 ZBasis = Cross(XBasis,YBasis);
        if(LevelType == LEVELTYPE_COLLIDESLOPE)
        {
            CollidedPosition.z += PlayerHalfDepth;
            CollidedHalfWidth += PlayerHalfWidth;
            CollidedHalfDepth = PlayerHalfDepth;
            CollidedPosition -= ZBasis*PlayerHalfDepth;
        }
        else
        {
            CollidedHalfWidth += PlayerHalfWidth;
            CollidedHalfHeight += PlayerHalfWidth;
            CollidedHalfDepth += PlayerHalfDepth;
        }
        v3 Delta = CollidedPosition - PlayerPos;
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
            goto NEXTENTITYUNDUCK;
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
            goto NEXTENTITYUNDUCK;
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
            goto NEXTENTITYUNDUCK;
        }
        
        if(T2 > 0)
        {
            if(T1 < 0)
            {
                return(false);
            }
        }
        NEXTENTITYUNDUCK:;
    }
    return(true);
}

//----------

internal void
UpdatePlayer(game_timers* GameTimers,
             game_player_input* PlayerInput,
             game_state* GameState,
             game_memory* GameMemory,
             stretchy_buffer_list* StretchyBuffers)
{
    if(PlayerInput->InputInit & F5KEY_INPUT &&
       GameState->ActivePlayers < 1000)
    {
        PlayerSpawn(PLAYERCLASS_SOLDIER,GameState,GameMemory);
    }
    uint32 CurrentPlayer = 0;
    uint32 LastPlayer = GameState->ActivePlayers;
    real64 RandomSecs = {};
    v3 RandomVel = {};
    
    for(CurrentPlayer;CurrentPlayer<LastPlayer;++CurrentPlayer)//lol this is dumb
    {
        v3 PlayerPosition = GameState->PlayerEntities.Position[CurrentPlayer];
        real64 PlayerHalfWidth = GameState->PlayerEntities.HalfWidth[CurrentPlayer];
        real64 PlayerHalfDepth = GameState->PlayerEntities.HalfDepth[CurrentPlayer];
        uint64 PlayerState = GameState->PlayerEntities.PlayerState[CurrentPlayer];
        v3 Velocity  = GameState->PlayerEntities.Velocity[CurrentPlayer];
        
        //----------accel
        v2 Acceleration = {};
        if( PlayerInput->InputInstant & DKEY_INPUT )
        {
            Acceleration.x = 1.0;
        }
        if( PlayerInput->InputInstant & AKEY_INPUT )
        {
            Acceleration.x = -1.0;
        }
        if( PlayerInput->InputInstant & WKEY_INPUT )
        {
            Acceleration.y = 1.0;
        }
        if( PlayerInput->InputInstant & SKEY_INPUT )
        {
            Acceleration.y = -1.0;
        }
        if(Acceleration.y != 0)
        {
            if(Acceleration.x != 0)
            {
                Acceleration *= 0.70710678118654752440084436210485;
            }
        }
        
        //----------friction
        if(PlayerState & PLAYERSTATE_GROUNDED && !(PlayerState & PLAYERSTATE_SWIMMING))
        {
            real64 Speed = Length(Velocity);
            real64 Friction = 4;
            real64 Drop = 0;
            real64 Control = 0;
            Control = (Speed < 100) ? 100 : Speed;
            Drop += (Control*Friction*GameTimers->SecondsElapsed);
            real64 NewSpeed = Speed - Drop;
            if(NewSpeed < 0 )
            {
                NewSpeed = 0;
            }
            if(NewSpeed != Speed)
            {
                NewSpeed /= Speed;
            }
            Velocity *= NewSpeed;
            Velocity -= (1-NewSpeed) * Velocity;
        }
        
        //----------add velocity
        real64 ForwardSpeed  = GameState->PlayerEntities.Speed[CurrentPlayer];
        if(PlayerState & PLAYERSTATE_GROUNDED && !(PlayerState & PLAYERSTATE_SWIMMING))
        {
            if(PlayerState & PLAYERSTATE_DUCKING)
            {
                ForwardSpeed /= 3;
            }
        }
        v2 Forward = Acceleration;
        Forward *= ForwardSpeed;
        v2 WishVel = {};
        WishVel += Forward;
        v2 WishDir = WishVel;
        real64 WishSpeed = Length(WishDir);
        if(WishSpeed)
        {
            WishDir /= WishSpeed;
        }
        real64 CurrentSpeed = Inner(V2(Velocity),WishDir);
        real64 AddSpeed = WishSpeed - CurrentSpeed;
        if (AddSpeed > 0)
        {
            real64 Accel = 10;
            real64 AccelSpeed = (Accel * GameTimers->SecondsElapsed * WishSpeed);
            if (AccelSpeed > AddSpeed)
            {
                AccelSpeed = AddSpeed;
            }
            WishDir *= AccelSpeed;
            Velocity.x += WishDir.x;
            Velocity.y += WishDir.y;
        }
        if(PlayerState & PLAYERSTATE_SWIMMING)
        {
            real64 ZAccel = 0;
            if(PlayerInput->InputInstant & SPACEKEY_INPUT)
            {
                ZAccel = ForwardSpeed;
            }
            else if(PlayerInput->InputInstant & SHIFTKEY_INPUT)
            {
                ZAccel = -ForwardSpeed;
            }
            Forward.x += -2.0f*Velocity.x;
            Forward.y += -2.0f*Velocity.y;
            ZAccel += -2.0f*Velocity.z;
            Velocity.x += (Forward.x) * GameTimers->SecondsElapsed;
            Velocity.y += (Forward.y) * GameTimers->SecondsElapsed;
            Velocity.z += (ZAccel) * GameTimers->SecondsElapsed;
        }
        
        //----------amount to move
        v3 CentimetersToMove = (Velocity * GameTimers->SecondsElapsed);
        
        //----------free move
        if(PlayerInput->InputToggle & NKEY_INPUT)
        {
            CentimetersToMove = {};
            real64 FreeMoveSpeed = 250;
            if( PlayerInput->InputInstant & DKEY_INPUT )
            {
                CentimetersToMove.x = FreeMoveSpeed * (GameTimers->SecondsElapsed);
            }
            if( PlayerInput->InputInstant & AKEY_INPUT )
            {
                CentimetersToMove.x = -FreeMoveSpeed * (GameTimers->SecondsElapsed);
            }
            if( PlayerInput->InputInstant & WKEY_INPUT )
            {
                CentimetersToMove.y = FreeMoveSpeed * (GameTimers->SecondsElapsed);
            }
            if( PlayerInput->InputInstant & SKEY_INPUT )
            {
                CentimetersToMove.y = -FreeMoveSpeed * (GameTimers->SecondsElapsed);
            }
            if( PlayerInput->InputInstant & SPACEKEY_INPUT )
            {
                CentimetersToMove.z = FreeMoveSpeed * (GameTimers->SecondsElapsed);
            }
            if( PlayerInput->InputInstant & SHIFTKEY_INPUT )
            {
                CentimetersToMove.z = -FreeMoveSpeed * (GameTimers->SecondsElapsed);
            }
            Velocity = (CentimetersToMove / GameTimers->SecondsElapsed);
        }
        
        //----------collision start
        v3 UnitMoveRay = CentimetersToMove;
        Normalize(UnitMoveRay);
        real64 MoveStep = Length(CentimetersToMove);
        MoveStep += PLAYER_STEPHEIGHT;//to account for step glide
        real64 VolumeGridSize = GameState->PlayerEntities.AABBHalfLength[CurrentPlayer] > PlayerHalfDepth + PLAYER_SQUISHHEIGHT ? GameState->PlayerEntities.AABBHalfLength[CurrentPlayer] : PlayerHalfDepth + PLAYER_SQUISHHEIGHT;
        VolumeGridSize += MoveStep;
        stretchy_buffer* SelectedGrids = BoxGridIntersection(PlayerPosition,VolumeGridSize,GameState,StretchyBuffers);
        stretchy_buffer* EntityList = GetEntitiesOfTypeFromGrid(PARTITIONTYPE_LEVEL,GameState,StretchyBuffers);
        ClearStretchyBuffer(STRETCHY_BUFFER_COLLISION_HIT_INDEX,StretchyBuffers);
        
        //----------sweep and prune
        AABB CollisionVolume = GameState->PlayerEntities.BoundingBox[CurrentPlayer];
        CollisionVolume.MaxX += (MoveStep);
        CollisionVolume.Origin.x -= (MoveStep);
        CollisionVolume.MaxY += (MoveStep);
        CollisionVolume.Origin.y -= (MoveStep);
        CollisionVolume.MaxZ += (MoveStep);
        CollisionVolume.Origin.z -= (MoveStep);
        for (uint32 i = 0 ; i < EntityList->Size; ++i)
        {
            uint32 Index = *((uint32*)EntityList->DataStart+i);
            AABB TestingForCollision = GameState->LevelEntities.BoundingBox[Index];
            if(CollisionVolume.MaxZ >= TestingForCollision.Origin.z &&
               CollisionVolume.Origin.z <= TestingForCollision.MaxZ &&
               CollisionVolume.MaxX >= TestingForCollision.Origin.x &&
               CollisionVolume.Origin.x <= TestingForCollision.MaxX &&
               CollisionVolume.MaxY >= TestingForCollision.Origin.y &&
               CollisionVolume.Origin.y <= TestingForCollision.MaxY)
            {
                uint8 LevelType = GameState->LevelEntities.LevelType[Index];
                if(LevelType <= LEVELTYPE_COLLIDESLOPE)
                {
                    PushStretchyBuffer(STRETCHY_BUFFER_COLLISION_HIT_INDEX,&Index,StretchyBuffers);
                }
            }
        }
        MoveStep -= PLAYER_STEPHEIGHT;
        
        //----------
        stretchy_buffer* HitIndex = StretchyBuffers->StretchyBufferInfo[STRETCHY_BUFFER_COLLISION_HIT_INDEX];
        v3 GravityVector = {0,0,-1};
        uint32 CollisionBits = 0;
        //0x1 = CEILING
        //0x2 = FLOOR
        //0x4 = WATER
        real64 ClosestHit;
        uint8 NumOfLoops = 0;
        uint8 ClosestSideHit;
        uint8 ClosestLevelType;
        int32 ClosestIndex;
        int32 GlideIndex;
        real64 GlideMove = 0;
        v3 ClosestXBasis;
        v3 ClosestYBasis;
        v3 ClosestZBasis;
        ClearStretchyBuffer(STRETCHY_BUFFER_COLLISION_INDEX_HISTORY,StretchyBuffers);
        ClearStretchyBuffer(STRETCHY_BUFFER_COLLISION_REFLECTION_HISTORY,StretchyBuffers);
        
        //----------re-test point
        RETESTCOLLISION:;
        ClosestHit = REAL64Max;
        ClosestSideHit = 0;
        ClosestLevelType = 0;
        ClosestIndex = -1;
        GlideIndex = -2;
        ClosestXBasis = {};
        ClosestYBasis = {};
        ClosestZBasis = {};
        for (uint32 i = 0 ; i < HitIndex->Size; ++i)
        {
            uint8 SideHit = 0;
            uint32 Index = *((uint32*)HitIndex->DataStart+i);
            v3 YBasis = {
                GameState->LevelEntities.YBasis[Index].x,
                GameState->LevelEntities.YBasis[Index].y,
                0
            };
            v3 XBasis = -Perp(YBasis);
            v3 CollidedPosition = GameState->LevelEntities.Position[Index];
            v3 Delta = CollidedPosition - PlayerPosition;
            real64 CollidedHalfWidth = GameState->LevelEntities.HalfWidth[Index];
            real64 CollidedHalfHeight = GameState->LevelEntities.HalfHeight[Index];
            real64 CollidedHalfDepth = GameState->LevelEntities.HalfDepth[Index];
            uint8 LevelType = GameState->LevelEntities.LevelType[Index];
            v3 ZBasis;
            
            //----------in water?
            if(LevelType == LEVELTYPE_WATER)
            {
                CollidedHalfDepth += PlayerHalfDepth;
                CollidedHalfHeight += PlayerHalfWidth;
                CollidedHalfWidth += PlayerHalfWidth;
                real64 E = Inner(XBasis,Delta);
                if((E>-CollidedHalfWidth)&&(E<CollidedHalfWidth))
                {
                    E = Inner(YBasis,Delta);
                    if((E>-CollidedHalfHeight)&&(E<CollidedHalfHeight))
                    {
                        ZBasis = Cross(XBasis,YBasis);
                        E = Inner(ZBasis,Delta);
                        if((E>-CollidedHalfDepth)&&(E<CollidedHalfDepth))
                        {
                            if(E-(-CollidedHalfDepth) > PlayerHalfDepth)
                            {
                                PlayerState |= PLAYERSTATE_SWIMMING;
                                PlayerState &= ~PLAYERSTATE_WATERJUMP;
                            }
                            else
                            {
                                if(!(CollisionBits & 0x4))
                                {
                                    if(PlayerState & PLAYERSTATE_SWIMMING)
                                    {
                                        PlayerState |= PLAYERSTATE_WATERJUMP;
                                    }
                                    PlayerState &= ~PLAYERSTATE_SWIMMING;
                                }
                            }
                            CollisionBits |= 0x4;
                        }
                    }
                }
                goto NEXTENTITYCOLLIDE;
            }
            
            else if(LevelType == LEVELTYPE_COLLIDESLOPE)
            {
                if(CollidedHalfHeight)
                {
                    real64 NewHeight = SquareRoot(CollidedHalfHeight*CollidedHalfHeight + CollidedHalfDepth*CollidedHalfDepth);
                    NewHeight = 1.0/NewHeight;
                    YBasis.x = YBasis.x*CollidedHalfHeight;
                    YBasis.y = YBasis.y*CollidedHalfHeight;
                    YBasis.z = CollidedHalfDepth;
                    YBasis *= NewHeight;
                    ZBasis = Cross(XBasis,YBasis);
                    YBasis = {
                        GameState->LevelEntities.YBasis[Index].x,
                        GameState->LevelEntities.YBasis[Index].y,
                        0
                    };
                    CollidedHalfDepth = (PlayerHalfDepth*(CollidedHalfHeight*NewHeight))+(PlayerHalfWidth*(CollidedHalfDepth*NewHeight));
                    CollidedHalfHeight += PlayerHalfWidth;
                    CollidedHalfWidth += PlayerHalfWidth;
                }
                else
                {
                    ZBasis = Cross(XBasis,YBasis);
                    CollidedHalfDepth += PlayerHalfDepth;
                    CollidedHalfHeight += PlayerHalfWidth;
                    CollidedHalfWidth += PlayerHalfWidth;
                }
            }
            
            else
            {
                ZBasis = Cross(XBasis,YBasis);
                CollidedHalfWidth += PlayerHalfWidth;
                CollidedHalfHeight += PlayerHalfWidth;
                CollidedHalfDepth += PlayerHalfDepth;
            }
            
            //----------
            real64 TMin = 0;
            real64 TMax = REAL64Max;
            
            //----------XAxis
            // help: https://www.opengl-tutorial.org/miscellaneous/clicking-on-objects/picking-with-custom-ray-obb-function/
            real64 E = Inner(XBasis,Delta);
            real64 F = Inner(UnitMoveRay,XBasis);
            real64 T1 = (E-CollidedHalfWidth)/F;
            real64 T2 = (E+CollidedHalfWidth)/F;
            if (T1>T2)
            {
                real64 w=T1;T1=T2;T2=w;
            }
            if ( T1 >= TMin )
            {
                TMin = T1;
                if(F < 0)
                {
                    SideHit |= 0x2;
                    SideHit |= 0x4;//XAxis is min bit
                }
                else if(F > 0)
                {
                    SideHit |= 0x1;
                    SideHit |= 0x4;//XAxis is min bit
                }
            }
            if ( T2 < TMax )
            {
                TMax = T2;
            }
            if (TMax < TMin )
            {
                goto NEXTENTITYCOLLIDE;
            }
            
            //----------YAxis
            E = Inner(YBasis,Delta);
            F = Inner(UnitMoveRay,YBasis);
            T1 = (E-CollidedHalfHeight)/F;
            T2 = (E+CollidedHalfHeight)/F;
            if (T1>T2)
            {
                real64 w=T1;T1=T2;T2=w;
            }
            if ( T1 >= TMin )
            {
                TMin = T1;
                if(F < 0)
                {
                    SideHit |= 0x10;
                    SideHit |= 0x20;//YAxis is min bit
                    SideHit &= ~0x4;
                }
                else if(F > 0)
                {
                    SideHit |= 0x8;
                    SideHit |= 0x20;//YAxis is min bit
                    SideHit &= ~0x4;
                }
            }
            if ( T2 < TMax )
            {
                TMax = T2;
            }
            if (TMax < TMin )
            {
                goto NEXTENTITYCOLLIDE;
            }
            
            //----------
            
            if(LevelType == LEVELTYPE_COLLIDESLOPE)
            {
                if(E-PlayerHalfWidth-PlayerHalfWidth <= -CollidedHalfHeight)
                {
                    if(Inner(ZBasis,Delta)<=CollidedHalfDepth)
                    {
                        ZBasis = {0,0,1};
                        CollidedHalfDepth = GameState->LevelEntities.HalfDepth[Index]+PlayerHalfDepth;
                    }
                }
                if(E+PlayerHalfWidth+PlayerHalfWidth >= CollidedHalfHeight)
                {
                    if(Inner(ZBasis,Delta)>=-CollidedHalfDepth)
                    {
                        ZBasis = {0,0,1};
                        CollidedHalfDepth = GameState->LevelEntities.HalfDepth[Index]+PlayerHalfDepth;
                    }
                }
            }
            
            //----------ZAxis
            E = Inner(ZBasis,Delta);
            F = Inner(UnitMoveRay,ZBasis);
            T1 = (E-CollidedHalfDepth)/F;
            T2 = (E+CollidedHalfDepth)/F;
            if (T1>T2)
            {
                real64 w=T1;T1=T2;T2=w;
            }
            if ( T1 >= TMin )
            {
                TMin = T1;
                if(F < 0)
                {
                    SideHit |= 0x80;
                    SideHit &= ~0x20;
                    SideHit &= ~0x4;
                }
                else if(F > 0)
                {
                    SideHit |= 0x40;
                    SideHit &= ~0x20;
                    SideHit &= ~0x4;
                }
            }
            if ( T2 < TMax )
            {
                TMax = T2;
            }
            if (TMax < TMin )
            {
                goto NEXTENTITYCOLLIDE;
            }
            
            //----------is closest collide?
            if(TMin < MoveStep)
            {
                if(TMin < ClosestHit)
                {
                    if(SideHit)
                    {
                        //----------glide over small steps
                        if(ZBasis.z == 1)
                        {
                            if((E-(-CollidedHalfDepth)) > 0)
                            {
                                if((E-(-CollidedHalfDepth))*1.05 < PLAYER_STEPHEIGHT)
                                {
                                    GlideIndex = Index;
                                    GlideMove = (E-(-CollidedHalfDepth))*1.05;//5% more because exact value isnt enough to go above ledge
                                }
                            }
                        }
                        
                        ClosestHit = TMin;
                        ClosestSideHit = SideHit;
                        ClosestLevelType = LevelType;
                        ClosestIndex = Index;
                        ClosestXBasis = XBasis;
                        ClosestYBasis = YBasis;
                        ClosestZBasis = ZBasis;
                    }
                }
            }
            NEXTENTITYCOLLIDE:;
        }
        
        //----------collision occured
        if(ClosestSideHit)
        {
            ++NumOfLoops;
            if(NumOfLoops>16)
            {
                CentimetersToMove = {};
                Velocity = {};
                goto PLAYERSTATEBEGIN;
            }
            
            v3 ReflectionNormal = {};
            if(ClosestSideHit & 0x4)
            {
                if(ClosestSideHit & 0x1)//left
                {
                    ReflectionNormal  = -ClosestXBasis;
                }
                else if(ClosestSideHit & 0x2)//right
                {
                    ReflectionNormal  = ClosestXBasis;
                }
            }
            else if(ClosestSideHit & 0x20)
            {
                if(ClosestSideHit & 0x8)//bottom
                {
                    ReflectionNormal  = -ClosestYBasis;
                }
                else if(ClosestSideHit & 0x10)//top
                {
                    ReflectionNormal  = ClosestYBasis;
                }
            }
            else
            {
                if(ClosestSideHit & 0x40)//floor
                {
                    ReflectionNormal = -ClosestZBasis;
                    CollisionBits |= 0x2;
                }
                else if(ClosestSideHit & 0x80)//ceiling
                {
                    GravityVector = -ClosestZBasis;
                    ReflectionNormal = ClosestZBasis;
                    if(ClosestLevelType == LEVELTYPE_COLLIDESLOPE)
                    {
                        if(Length(Velocity)<GameState->PlayerEntities.Speed[CurrentPlayer]*2)
                        {
                            CollisionBits |= 0x1;
                        }
                    }
                    else
                    {
                        CollisionBits |= 0x1;
                    }
                }
            }
            
            if(ClosestIndex == GlideIndex)
            {
                CentimetersToMove.z = GlideMove;
                Velocity.z = 0;
                GravityVector = {0,0,-1};
                CollisionBits = 0;
                CentimetersToMove -= Inner(CentimetersToMove,ReflectionNormal)*(ReflectionNormal);
                CentimetersToMove += REAL64Epsilon*ReflectionNormal;
                NumOfLoops = 0;
                ClearStretchyBuffer(STRETCHY_BUFFER_COLLISION_INDEX_HISTORY,StretchyBuffers);
                ClearStretchyBuffer(STRETCHY_BUFFER_COLLISION_REFLECTION_HISTORY,StretchyBuffers);
                MoveStep = Length(CentimetersToMove);
                UnitMoveRay = CentimetersToMove;
                Normalize(UnitMoveRay);
                goto RETESTCOLLISION;
            }
            
            PushStretchyBuffer(STRETCHY_BUFFER_COLLISION_REFLECTION_HISTORY,&ReflectionNormal,StretchyBuffers);
            PushStretchyBuffer(STRETCHY_BUFFER_COLLISION_INDEX_HISTORY,&ClosestIndex,StretchyBuffers);
            
            v3* ReflectHistory = (v3*)StretchyBuffers->StretchyBufferInfo[STRETCHY_BUFFER_COLLISION_REFLECTION_HISTORY]->DataStart;
            stretchy_buffer* IndexBuffer = StretchyBuffers->StretchyBufferInfo[STRETCHY_BUFFER_COLLISION_INDEX_HISTORY];
            uint32* IndexHistory = (uint32*)IndexBuffer->DataStart;
            
            if(IndexBuffer->Size>2 &&
               *(IndexHistory+(IndexBuffer->Size-3)) == *(IndexHistory+(IndexBuffer->Size-1)))
            {
                ReflectionNormal = *(ReflectHistory+(IndexBuffer->Size-3));
                CentimetersToMove -= Inner(CentimetersToMove,ReflectionNormal)*(ReflectionNormal);
                Velocity -= Inner(Velocity,ReflectionNormal)*(ReflectionNormal);
                CentimetersToMove += REAL64Epsilon*ReflectionNormal;
                
                v3 CombinedReflect = {};
                CombinedReflect = *(ReflectHistory+(IndexBuffer->Size-3))+*(ReflectHistory+(IndexBuffer->Size-2));
                Normalize(CombinedReflect);
                CentimetersToMove -= Inner(CentimetersToMove,CombinedReflect)*(CombinedReflect);
                Velocity -= Inner(Velocity,CombinedReflect)*(CombinedReflect);
                CentimetersToMove += REAL64Epsilon*CombinedReflect;
                
                ReflectionNormal = *(ReflectHistory+(IndexBuffer->Size-2));
                CentimetersToMove -= Inner(CentimetersToMove,ReflectionNormal)*(ReflectionNormal);
                Velocity -= Inner(Velocity,ReflectionNormal)*(ReflectionNormal);
                CentimetersToMove += REAL64Epsilon*ReflectionNormal;
                
                ClearStretchyBuffer(STRETCHY_BUFFER_COLLISION_INDEX_HISTORY,StretchyBuffers);
                ClearStretchyBuffer(STRETCHY_BUFFER_COLLISION_REFLECTION_HISTORY,StretchyBuffers);
                MoveStep = Length(CentimetersToMove);
                UnitMoveRay = CentimetersToMove;
                Normalize(UnitMoveRay);
                goto RETESTCOLLISION;
            }
            
            CentimetersToMove -= Inner(CentimetersToMove,ReflectionNormal)*(ReflectionNormal);
            CentimetersToMove += REAL64Epsilon*ReflectionNormal;
            Velocity -= Inner(Velocity,ReflectionNormal)*(ReflectionNormal);
            MoveStep = Length(CentimetersToMove);
            UnitMoveRay = CentimetersToMove;
            Normalize(UnitMoveRay);
            goto RETESTCOLLISION;
        }
        
        //----------misc playerstate shenanigans
        PLAYERSTATEBEGIN:;
        
        if(!(PlayerInput->InputToggle & NKEY_INPUT))
        {
            if(CollisionBits & 0x1)//----------grounded?
            {
                if(PlayerState & PLAYERSTATE_TOUCHEDGROUND)
                {
                    PlayerState |= PLAYERSTATE_GROUNDED;
                }
                PlayerState |= PLAYERSTATE_TOUCHEDGROUND;
            }
            else
            {
                PlayerState &= ~PLAYERSTATE_GROUNDED;
                PlayerState &= ~PLAYERSTATE_TOUCHEDGROUND;
            }
            if(!(CollisionBits & 0x4))//----------swim
            {
                PlayerState &= ~PLAYERSTATE_SWIMMING;
                PlayerState &= ~PLAYERSTATE_WATERJUMP;
            }
            
            /*------------------------------
            if(!(PlayerState & PLAYERSTATE_DUCKING))//----------duck
            {
                if(PlayerInput->InputInit & SHIFTKEY_INPUT)
                {
                    PlayerState |= PLAYERSTATE_DUCKING;
                    PlayerHalfDepth -= PLAYER_SQUISHHEIGHT;
                    PlayerPosition.z -= PLAYER_SQUISHHEIGHT;
                }
            }
            
            else if(PlayerState & PLAYERSTATE_DUCKING)//----------resolve un-duck
            {
                if(!(PlayerInput->InputInstant & SHIFTKEY_INPUT))
                {
                    if(TryUnduck(HitIndex,
                                 PlayerPosition + CentimetersToMove,
                                 PlayerHalfWidth,
                                 PlayerHalfDepth + PLAYER_SQUISHHEIGHT,
                                 {0,0,1},
                                 GameState))
                    {
                        PlayerHalfDepth += PLAYER_SQUISHHEIGHT;
                        PlayerPosition.z += PLAYER_SQUISHHEIGHT;
                        PlayerState &= ~PLAYERSTATE_DUCKING;
                        PlayerState &= ~PLAYERSTATE_WATERJUMP;
                    }
                }
            }
            ------------------------------*/
            
            if( PlayerInput->InputInstant & SPACEKEY_INPUT )//----------jump
            {
                if(!(PlayerState & PLAYERSTATE_DUCKING)&&!(PlayerState & PLAYERSTATE_SWIMMING))
                {
                    if(PlayerState & PLAYERSTATE_WATERJUMP)
                    {
                        Velocity += (-GravityVector*515);
                        PlayerState &= ~PLAYERSTATE_WATERJUMP;
                    }
                    else if(PlayerState & PLAYERSTATE_TOUCHEDGROUND)
                    {
                        Velocity += (-GravityVector*515);
                    }
                }
            }
            
            //----------rotation based on velocity
            if(!(PlayerInput->InputToggle & NKEY_INPUT))
            {
                real64 UnitLengthRatio = Length(V2(Velocity));
                if (UnitLengthRatio > 20)
                {
                    GameState->PlayerEntities.YBasis[CurrentPlayer] = {(Velocity.x / UnitLengthRatio),
                        (Velocity.y / UnitLengthRatio)};
                }
            }
            
            //----------gravity
            
            if(!(PlayerState & PLAYERSTATE_SWIMMING))
            {
                if(Velocity.z > -6700)
                {
                    Velocity += ( (GravityVector*1523.2) * (GameTimers->SecondsElapsed) );
                }
            }
            
        }
        
        //------------------------------player update pos
        PlayerPosition.x += CentimetersToMove.x;
        PlayerPosition.y += CentimetersToMove.y;
        PlayerPosition.z += CentimetersToMove.z;
        //----------Handling if spatial partition changes with move
        AABB OldBounds = GameState->PlayerEntities.BoundingBox[CurrentPlayer];
        AABB NewBounds = {};
        real64 AABBHalfLength = GameState->PlayerEntities.AABBHalfLength[CurrentPlayer];
        NewBounds.Origin.x = PlayerPosition.x - AABBHalfLength;
        NewBounds.Origin.y = PlayerPosition.y - AABBHalfLength;
        NewBounds.Origin.z = PlayerPosition.z - PLAYER_HALFDEPTH;
        NewBounds.MaxX = PlayerPosition.x + AABBHalfLength;
        NewBounds.MaxY = PlayerPosition.y + AABBHalfLength;
        NewBounds.MaxZ = PlayerPosition.z + PLAYER_HALFDEPTH;
        if((int32)OldBounds.Origin.x/PARTITION_DIMENSION != (int32)NewBounds.Origin.x/PARTITION_DIMENSION||
           (int32)OldBounds.Origin.y/PARTITION_DIMENSION != (int32)NewBounds.Origin.y/PARTITION_DIMENSION||
           (int32)OldBounds.Origin.z/PARTITION_DIMENSION != (int32)NewBounds.Origin.z/PARTITION_DIMENSION||
           (int32)OldBounds.MaxX/PARTITION_DIMENSION != (int32)NewBounds.MaxX/PARTITION_DIMENSION||
           (int32)OldBounds.MaxY/PARTITION_DIMENSION != (int32)NewBounds.MaxY/PARTITION_DIMENSION||
           (int32)OldBounds.MaxZ/PARTITION_DIMENSION != (int32)NewBounds.MaxZ/PARTITION_DIMENSION)
        {
            RemoveEntityFromPartition({PARTITIONTYPE_PLAYER,CurrentPlayer},GameState,GameMemory);
            GameState->PlayerEntities.BoundingBox[CurrentPlayer] = NewBounds;
            AddEntityToPartition({PARTITIONTYPE_PLAYER,CurrentPlayer},GameState,GameMemory);
        }
        else
        {
            GameState->PlayerEntities.BoundingBox[CurrentPlayer] = NewBounds;
        }
        
        //----------
        GameState->PlayerEntities.PlayerState[CurrentPlayer] = PlayerState;
        GameState->PlayerEntities.Velocity[CurrentPlayer] = Velocity;
        GameState->PlayerEntities.Position[CurrentPlayer] = PlayerPosition;
        GameState->PlayerEntities.HalfDepth[CurrentPlayer] = PlayerHalfDepth;
    }
}