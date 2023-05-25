internal int32
CreateLevel(real64 X, real64 Y, real64 Z,real64 Width, real64 Height, real64 Depth,real64 Degrees,real32 TextureOffsetX,real32 TextureOffsetY,uint8 TextureLayer,real32 TextureRepeatScale,uint8 LevelType,game_state* GameState,game_memory* GameMemory)
{
    uint32 Index = GameState->LevelEntitiesCreated;
    GameState->LevelEntities.LevelType[Index] = LevelType;
    GameState->LevelEntities.HalfWidth[Index] = Width/2;
    GameState->LevelEntities.HalfHeight[Index] = Height/2;
    GameState->LevelEntities.HalfDepth[Index] = Depth/2;
    GameState->LevelEntities.TextureIndex[Index].TextureOffsetX = TextureOffsetX / 128.0f;
    GameState->LevelEntities.TextureIndex[Index].TextureOffsetY = TextureOffsetY / 128.0f;
    GameState->LevelEntities.TextureIndex[Index].TextureLayer = TextureLayer;
    GameState->LevelEntities.TextureIndex[Index].TextureRepeatScale = TextureRepeatScale;
    v3 Position = {};
    Position.x = X;
    Position.y = Y;
    Position.z = Z;
    real64 Rads = Degrees + 90; // 0 degrees is unit vector pointing straight north
    Rads*= 0.01745329251994329576923690768489; // turn to rads
    v2 YBasis ={Cosine(Rads),Sine(Rads)};
    real64 AABBHalfLength;
    if(GameState->LevelEntities.HalfHeight[Index] >= GameState->LevelEntities.HalfWidth[Index])
    {
        AABBHalfLength = GameState->LevelEntities.HalfHeight[Index] * 1.4142135623730950488016887242097;
    }
    else
    {
        AABBHalfLength = GameState->LevelEntities.HalfWidth[Index] * 1.4142135623730950488016887242097;
    }
    GameState->LevelEntities.AABBHalfLength[Index] = AABBHalfLength;
    GameState->LevelEntities.BoundingBox[Index].Origin.x = Position.x - AABBHalfLength;
    GameState->LevelEntities.BoundingBox[Index].Origin.y = Position.y - AABBHalfLength;
    GameState->LevelEntities.BoundingBox[Index].Origin.z = Position.z - GameState->LevelEntities.HalfDepth[Index];
    GameState->LevelEntities.BoundingBox[Index].MaxX = Position.x + AABBHalfLength;
    GameState->LevelEntities.BoundingBox[Index].MaxY = Position.y + AABBHalfLength;
    GameState->LevelEntities.BoundingBox[Index].MaxZ = Position.z + GameState->LevelEntities.HalfDepth[Index];
    GameState->LevelEntities.Position[Index] = Position;
    GameState->LevelEntities.YBasis[Index] = YBasis;
    AddEntityToPartition({PARTITIONTYPE_LEVEL,Index},GameState,GameMemory);
    ++GameState->LevelEntitiesCreated;
    return(Index);
}