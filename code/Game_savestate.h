internal void
SaveLevel(game_memory* GameMemory,game_state* GameState)
{
    uint32 BytesPerEntity = 0;
    uint32 LevelEntityCount  = 0;
    BytesPerEntity += sizeof(uint8);
    BytesPerEntity += sizeof(real64);
    BytesPerEntity += sizeof(real64);
    BytesPerEntity += sizeof(real64);
    BytesPerEntity += sizeof(real64);
    BytesPerEntity += sizeof(partition_indices_info*);
    BytesPerEntity += sizeof(v2);
    BytesPerEntity += sizeof(v3);
    BytesPerEntity += sizeof(texture_index);
    BytesPerEntity += sizeof(AABB);
    
    uint8* DataMover = (uint8*)ScratchMemoryBuffer;
    DataMover += sizeof(LevelEntityCount);//leave room at begin for level entity count
    for(uint32 i = 0;i<GameState->LevelEntitiesCreated;++i)
    {
        *DataMover = GameState->LevelEntities.LevelType[i];
        DataMover += sizeof(uint8);
        *(real64*)DataMover = GameState->LevelEntities.HalfWidth[i];
        DataMover += sizeof(real64);
        *(real64*)DataMover = GameState->LevelEntities.HalfHeight[i];
        DataMover += sizeof(real64);
        *(real64*)DataMover = GameState->LevelEntities.HalfDepth[i];
        DataMover += sizeof(real64);
        *(real64*)DataMover = GameState->LevelEntities.AABBHalfLength[i];
        DataMover += sizeof(real64);
        *(partition_indices_info*)DataMover = {};
        DataMover += sizeof(partition_indices_info*);
        *(v2*)DataMover = GameState->LevelEntities.YBasis[i];
        DataMover += sizeof(v2);
        *(v3*)DataMover = GameState->LevelEntities.Position[i];
        DataMover += sizeof(v3);
        *(texture_index*)DataMover = GameState->LevelEntities.TextureIndex[i];
        DataMover += sizeof(texture_index);
        *(AABB*)DataMover = GameState->LevelEntities.BoundingBox[i];
        DataMover += sizeof(AABB);
        ++LevelEntityCount;
    }
    *(uint32*)ScratchMemoryBuffer = LevelEntityCount;
    PlatformWriteFile("test.level",(BytesPerEntity*LevelEntityCount)+sizeof(LevelEntityCount),ScratchMemoryBuffer);
}

//------------------------------

internal void
LoadLevel(game_memory* GameMemory,game_state* GameState,stretchy_buffer_list* StretchyBuffers)
{
    ClearPartition(GameState,GameMemory);
    if(PlatformLoadFile("test.level",ScratchMemoryBuffer))
    {
        uint8* DataMover = (uint8*)ScratchMemoryBuffer;
        uint32 LevelEntityCount = *(uint32*)DataMover;
        DataMover += sizeof(LevelEntityCount);
        for(uint32 i = 0;i<LevelEntityCount;++i)
        {
            GameState->LevelEntities.LevelType[i] = *DataMover;
            DataMover += sizeof(uint8);
            GameState->LevelEntities.HalfWidth[i] = *(real64*)DataMover;
            DataMover += sizeof(real64);
            GameState->LevelEntities.HalfHeight[i] = *(real64*)DataMover;
            DataMover += sizeof(real64);
            GameState->LevelEntities.HalfDepth[i] = *(real64*)DataMover;
            DataMover += sizeof(real64);
            GameState->LevelEntities.AABBHalfLength[i] = *(real64*)DataMover;
            DataMover += sizeof(real64);
            GameState->LevelEntities.LevelPartitionIndices[i] = {};
            DataMover += sizeof(partition_indices_info*);
            GameState->LevelEntities.YBasis[i] = *(v2*)DataMover;
            DataMover += sizeof(v2);
            GameState->LevelEntities.Position[i] = *(v3*)DataMover;
            DataMover += sizeof(v3);
            GameState->LevelEntities.TextureIndex[i] = *(texture_index*)DataMover;
            DataMover += sizeof(texture_index);
            GameState->LevelEntities.BoundingBox[i] = *(AABB*)DataMover;
            DataMover += sizeof(AABB);
            AddEntityToPartition({PARTITIONTYPE_LEVEL,i},GameState,GameMemory);
        }
        GameState->ActivePlayers = 0;
        GameState->LevelEntitiesCreated = LevelEntityCount;
    }
}