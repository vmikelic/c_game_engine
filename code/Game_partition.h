//----------
struct partition_bounds
{
    int32 MinXCell;
    int32 MinYCell;
    int32 MinZCell;
    int32 MaxXCell;
    int32 MaxYCell;
    int32 MaxZCell;
};
//----------

internal stretchy_buffer* NormalRayGridIntersection(v3 RayDir,v3 RayLoc,real64 RayLength,game_state* GameState,stretchy_buffer_list* StretchyBuffers)
{
    ClearStretchyBuffer(STRETCHY_BUFFER_GRID_NUMBERS,StretchyBuffers);
    if((RayLoc.x >= 0 && RayLoc.x <= MAX_MAP_WIDTH) &&
       (RayLoc.y >= 0 && RayLoc.y <= MAX_MAP_HEIGHT) &&
       (RayLoc.z >= 0 && RayLoc.z <= MAX_MAP_DEPTH))
    {
        {
            real64 InverseLength = SquareRoot(RayDir.x*RayDir.x + RayDir.y*RayDir.y + RayDir.z*RayDir.z);
            if(InverseLength > 0)
            {
                InverseLength = 1/InverseLength;
                RayDir.x = RayDir.x*InverseLength;
                RayDir.y = RayDir.y*InverseLength;
                RayDir.z = RayDir.z*InverseLength;
            }
            else
            {
                return(StretchyBuffers->StretchyBufferInfo[STRETCHY_BUFFER_GRID_NUMBERS]);
            }
        }
        v3 v = RayLoc + (RayDir*RayLength);
        real64 dx = (v.x - RayLoc.x);
        real64 dy = (v.y - RayLoc.y);
        real64 dz = (v.z - RayLoc.z);
        if(v.x < 0)
        {
            v.x = RayLoc.x/-dx;
            dx *= v.x;
            dy *= v.x;
            dz *= v.x;
            v.x = (RayLoc.x + dx);
            v.y = (RayLoc.y + dy);
            v.z = (RayLoc.z + dz);
        }
        else if(v.x > MAX_MAP_WIDTH)
        {
            v *= (MAX_MAP_WIDTH/v.x);
            dx = (v.x - RayLoc.x);
            dy = (v.y - RayLoc.y);
            dz = (v.z - RayLoc.z);
        }
        if(v.y < 0)
        {
            v.y = RayLoc.y/-dy;
            dx *= v.y;
            dy *= v.y;
            dz *= v.y;
            v.x = (RayLoc.x + dx);
            v.y = (RayLoc.y + dy);
            v.z = (RayLoc.z + dz);
        }
        else if(v.y > MAX_MAP_HEIGHT)
        {
            v *= (MAX_MAP_HEIGHT/v.y);
            dx = (v.x - RayLoc.x);
            dy = (v.y - RayLoc.y);
            dz = (v.z - RayLoc.z);
        }
        if(v.z < 0)
        {
            v.z = RayLoc.z/-dz;
            dx *= v.z;
            dy *= v.z;
            dz *= v.z;
            v.x = (RayLoc.x + dx);
            v.y = (RayLoc.y + dy);
            v.z = (RayLoc.z + dz);
        }
        else if(v.z > MAX_MAP_DEPTH)
        {
            v *= (MAX_MAP_DEPTH/v.z);
            dx = (v.x - RayLoc.x);
            dy = (v.y - RayLoc.y);
            dz = (v.z - RayLoc.z);
        }
        int32 steps = 0;
        real64 RemainderMul = 0;
        v.x = AbsoluteValue(dx);
        v.y = AbsoluteValue(dy);
        v.z = AbsoluteValue(dz);
        if(v.x >= v.y)
        {
            if(v.x >= v.z)
            {
                steps = (int32)(v.x*ONE_OVER_PARTITION_DIMENSION);
                RemainderMul = (v.x-(500*steps))/500;
                if(dy >= 0)
                {
                    dy = (v.y/v.x)*500;
                }
                else
                {
                    dy = (v.y/v.x)*-500;
                }
                if(dz >= 0)
                {
                    dz = (v.z/v.x)*500;
                }
                else
                {
                    dz = (v.z/v.x)*-500;
                }
                if(dx >= 0)
                {
                    dx = 500;
                }
                else
                {
                    dx = -500;
                }
                //x high
            }
            else
            {
                steps = (int32)(v.z*ONE_OVER_PARTITION_DIMENSION);
                RemainderMul = (v.z-(500*steps))/500;
                if(dy >= 0)
                {
                    dy = (v.y/v.z)*500;
                }
                else
                {
                    dy = (v.y/v.z)*-500;
                }
                if(dx >= 0)
                {
                    dx = (v.x/v.z)*500;
                }
                else
                {
                    dx = (v.x/v.z)*-500;
                }
                if(dz >= 0)
                {
                    dz = 500;
                }
                else
                {
                    dz = -500;
                }
                //z high
            }
        }
        else
        {
            if(v.y >= v.z)
            {
                steps = (int32)(v.y*ONE_OVER_PARTITION_DIMENSION);
                RemainderMul = (v.y-(500*steps))/500;
                if(dx >= 0)
                {
                    dx = (v.x/v.y)*500;
                }
                else
                {
                    dx = (v.x/v.y)*-500;
                }
                if(dz >= 0)
                {
                    dz = (v.z/v.y)*500;
                }
                else
                {
                    dz = (v.z/v.y)*-500;
                }
                if(dy >= 0)
                {
                    dy = 500;
                }
                else
                {
                    dy = -500;
                }
                //y high
            }
            else
            {
                steps = (int32)(v.z*ONE_OVER_PARTITION_DIMENSION);
                RemainderMul = (v.z-(500*steps))/500;
                if(dy >= 0)
                {
                    dy = (v.y/v.z)*500;
                }
                else
                {
                    dy = (v.y/v.z)*-500;
                }
                if(dx >= 0)
                {
                    dx = (v.x/v.z)*500;
                }
                else
                {
                    dx = (v.x/v.z)*-500;
                }
                if(dz >= 0)
                {
                    dz = 500;
                }
                else
                {
                    dz = -500;
                }
                //z high
            }
        }
        p3 GridStore;
        int32 Store;
        GridStore.x = (int32)(RayLoc.x*ONE_OVER_PARTITION_DIMENSION);
        GridStore.y = (int32)(RayLoc.y*ONE_OVER_PARTITION_DIMENSION);
        GridStore.z = (int32)(RayLoc.z*ONE_OVER_PARTITION_DIMENSION);
        PushStretchyBuffer(STRETCHY_BUFFER_GRID_NUMBERS,&GridStore,StretchyBuffers);
        for(int i = 0;i<steps;++i)
        {
            RayLoc.x+=dx;
            Store = (int32)(RayLoc.x*ONE_OVER_PARTITION_DIMENSION);
            if(GridStore.x != Store)
            {
                GridStore.x = Store;
                PushStretchyBuffer(STRETCHY_BUFFER_GRID_NUMBERS,&GridStore,StretchyBuffers);
            }
            RayLoc.y+=dy;
            Store = (int32)(RayLoc.y*ONE_OVER_PARTITION_DIMENSION);
            if(GridStore.y != Store)
            {
                GridStore.y = Store;
                PushStretchyBuffer(STRETCHY_BUFFER_GRID_NUMBERS,&GridStore,StretchyBuffers);
            }
            RayLoc.z+=dz;
            Store = (int32)(RayLoc.z*ONE_OVER_PARTITION_DIMENSION);
            if(GridStore.z != Store)
            {
                GridStore.z = Store;
                PushStretchyBuffer(STRETCHY_BUFFER_GRID_NUMBERS,&GridStore,StretchyBuffers);
            }
        }
        if(RemainderMul)
        {
            dx *= RemainderMul;
            dy *= RemainderMul;
            dz *= RemainderMul;
            RayLoc.x+=dx;
            Store = (int32)(RayLoc.x*ONE_OVER_PARTITION_DIMENSION);
            if(GridStore.x != Store)
            {
                GridStore.x = Store;
                PushStretchyBuffer(STRETCHY_BUFFER_GRID_NUMBERS,&GridStore,StretchyBuffers);
            }
            RayLoc.y+=dy;
            Store = (int32)(RayLoc.y*ONE_OVER_PARTITION_DIMENSION);
            if(GridStore.y != Store)
            {
                GridStore.y = Store;
                PushStretchyBuffer(STRETCHY_BUFFER_GRID_NUMBERS,&GridStore,StretchyBuffers);
            }
            RayLoc.z+=dz;
            Store = (int32)(RayLoc.z*ONE_OVER_PARTITION_DIMENSION);
            if(GridStore.z != Store)
            {
                GridStore.z = Store;
                PushStretchyBuffer(STRETCHY_BUFFER_GRID_NUMBERS,&GridStore,StretchyBuffers);
            }
        }
    }
    return(StretchyBuffers->StretchyBufferInfo[STRETCHY_BUFFER_GRID_NUMBERS]);
}

internal stretchy_buffer* VolumeGridIntersection(v3 RayDir,v3 RayLoc,real64 RayLength,real64 Size,
                                                 game_state* GameState,stretchy_buffer_list* StretchyBuffers)
{
    ClearStretchyBuffer(STRETCHY_BUFFER_GRID_NUMBERS,StretchyBuffers);
    Normalize(RayDir);
    v3 End = RayLoc + (RayDir*RayLength);
    int32 MinX = 0;
    int32 MaxX = 0;
    int32 MinY = 0;
    int32 MaxY = 0;
    int32 MinZ = 0;
    int32 MaxZ = 0;
    if(RayDir.x >= 0)
    {
        MinX = (int32)((RayLoc.x-Size)*ONE_OVER_PARTITION_DIMENSION);
        MaxX = (int32)((End.x+Size)*ONE_OVER_PARTITION_DIMENSION);
    }
    else
    {
        MinX = (int32)((End.x-Size)*ONE_OVER_PARTITION_DIMENSION);
        MaxX = (int32)((RayLoc.x+Size)*ONE_OVER_PARTITION_DIMENSION);
    }
    if(RayDir.y >= 0)
    {
        MinY = (int32)((RayLoc.y-Size)*ONE_OVER_PARTITION_DIMENSION);
        MaxY = (int32)((End.y+Size)*ONE_OVER_PARTITION_DIMENSION);
    }
    else
    {
        MinY = (int32)((End.y-Size)*ONE_OVER_PARTITION_DIMENSION);
        MaxY = (int32)((RayLoc.y+Size)*ONE_OVER_PARTITION_DIMENSION);
    }
    if(RayDir.z >= 0)
    {
        MinZ = (int32)((RayLoc.z-Size)*ONE_OVER_PARTITION_DIMENSION);
        MaxZ = (int32)((End.z+Size)*ONE_OVER_PARTITION_DIMENSION);
    }
    else
    {
        MinZ = (int32)((End.z-Size)*ONE_OVER_PARTITION_DIMENSION);
        MaxZ = (int32)((RayLoc.z+Size)*ONE_OVER_PARTITION_DIMENSION);
    }
    if(MinX < 0)
    {
        MinX = 0;
    }
    if(MaxX > PARTITION_MAXX_INDEX)
    {
        MaxX = PARTITION_MAXX_INDEX;
    }
    if(MinY < 0)
    {
        MinY = 0;
    }
    if(MaxY > PARTITION_MAXY_INDEX)
    {
        MaxY = PARTITION_MAXY_INDEX;
    }
    if(MinZ < 0)
    {
        MinZ = 0;
    }
    if(MaxZ > PARTITION_MAXZ_INDEX)
    {
        MaxZ = PARTITION_MAXZ_INDEX;
    }
    p3 GridStore = {};
    for(int z = MinZ;z<=MaxZ;++z)
    {
        GridStore.z = z;
        for(int y = MinY;y<=MaxY;++y)
        {
            GridStore.y = y;
            for(int x = MinX;x<=MaxX;++x)
            {
                GridStore.x = x;
                PushStretchyBuffer(STRETCHY_BUFFER_GRID_NUMBERS,&GridStore,StretchyBuffers);
            }
        }
    }
    return(StretchyBuffers->StretchyBufferInfo[STRETCHY_BUFFER_GRID_NUMBERS]);
}

internal stretchy_buffer* BoxGridIntersection(v3 RayLoc,real64 Size,
                                              game_state* GameState,stretchy_buffer_list* StretchyBuffers)
{
    ClearStretchyBuffer(STRETCHY_BUFFER_GRID_NUMBERS,StretchyBuffers);
    int32 MinX = 0;
    int32 MaxX = 0;
    int32 MinY = 0;
    int32 MaxY = 0;
    int32 MinZ = 0;
    int32 MaxZ = 0;
    MinX = (int32)((RayLoc.x-Size)*ONE_OVER_PARTITION_DIMENSION);
    MaxX = (int32)((RayLoc.x+Size)*ONE_OVER_PARTITION_DIMENSION);
    MinY = (int32)((RayLoc.y-Size)*ONE_OVER_PARTITION_DIMENSION);
    MaxY = (int32)((RayLoc.y+Size)*ONE_OVER_PARTITION_DIMENSION);
    MinZ = (int32)((RayLoc.z-Size)*ONE_OVER_PARTITION_DIMENSION);
    MaxZ = (int32)((RayLoc.z+Size)*ONE_OVER_PARTITION_DIMENSION);
    if(MinX < 0)
    {
        MinX = 0;
    }
    if(MaxX > PARTITION_MAXX_INDEX)
    {
        MaxX = PARTITION_MAXX_INDEX;
    }
    if(MinY < 0)
    {
        MinY = 0;
    }
    if(MaxY > PARTITION_MAXY_INDEX)
    {
        MaxY = PARTITION_MAXY_INDEX;
    }
    if(MinZ < 0)
    {
        MinZ = 0;
    }
    if(MaxZ > PARTITION_MAXZ_INDEX)
    {
        MaxZ = PARTITION_MAXZ_INDEX;
    }
    p3 GridStore = {};
    for(int z = MinZ;z<=MaxZ;++z)
    {
        GridStore.z = z;
        for(int y = MinY;y<=MaxY;++y)
        {
            GridStore.y = y;
            for(int x = MinX;x<=MaxX;++x)
            {
                GridStore.x = x;
                PushStretchyBuffer(STRETCHY_BUFFER_GRID_NUMBERS,&GridStore,StretchyBuffers);
            }
        }
    }
    return(StretchyBuffers->StretchyBufferInfo[STRETCHY_BUFFER_GRID_NUMBERS]);
}

//------------------------------

internal void RadixSortIndex(uint32 EntryCount,stretchy_buffer* EntityList)
{
    uint32* Source = (uint32*)EntityList->DataStart;
    uint32* Dest = (uint32*)ScratchMemoryBuffer;
    uint32* SwapTemp = {};
    for(uint32 ByteIndex = 0;ByteIndex < 32;ByteIndex += 8)
    {
        uint32 SortKeyOffsets[256] = {};
        for(uint32 Index = 0;Index < EntryCount;++Index)
        {
            uint32 RadixPiece = (*(Source+Index) >> ByteIndex) & 0xFF;
            ++SortKeyOffsets[RadixPiece];
        }
        uint32 Total = 0;
        for(uint32 SortKeyIndex = 0;SortKeyIndex < ArrayCount(SortKeyOffsets);++SortKeyIndex)
        {
            uint32 Count = SortKeyOffsets[SortKeyIndex];
            SortKeyOffsets[SortKeyIndex] = Total;
            Total += Count;
        }
        for(uint32 Index = 0;Index < EntryCount;++Index)
        {
            uint32 RadixPiece = (*(Source+Index) >> ByteIndex) & 0xFF;
            *(Dest+SortKeyOffsets[RadixPiece]++) = *(Source+Index);
        }
        SwapTemp = Dest;
        Dest = Source;
        Source = SwapTemp;
    }
}

internal stretchy_buffer* RemoveDuplicatesFromEntityList(stretchy_buffer* EntityList)
{
    if((uint32)EntityList->Size > 1)
    {
        RadixSortIndex((uint32)EntityList->Size,EntityList);
        uint32* StartIndex = (uint32*)EntityList->DataStart;
        uint32* EndIndex = (uint32*)EntityList->DataStart + 1;
        uint32* EndList = (uint32*)EntityList->DataStart + (uint32)EntityList->Size;
        while(EndIndex < EndList)
        {
            if(*StartIndex == *EndIndex)
            {
                ++EndIndex;
                while(*StartIndex == *EndIndex &&
                      EndIndex < EndList)
                {
                    ++EndIndex;
                }
                ++StartIndex;
                memmove(StartIndex,EndIndex,(EndList-EndIndex)*sizeof(uint32));
                uint32 SizeReduction = (uint32)(EndIndex - StartIndex);
                EndList -= SizeReduction;
                EntityList->Size -= SizeReduction;
                EndIndex = StartIndex + 1;
            }
            else
            {
                ++StartIndex;
                ++EndIndex;
            }
        }
        return(EntityList);
    }
    else
    {
        return(EntityList);
    }
}

internal stretchy_buffer* GetEntitiesOfTypeFromGrid(uint8 EntityType,game_state* GameState,stretchy_buffer_list* StretchyBuffers)
{
    ClearStretchyBuffer(STRETCHY_BUFFER_TEMP_INDEX,StretchyBuffers);
    stretchy_buffer* GridList = StretchyBuffers->StretchyBufferInfo[STRETCHY_BUFFER_GRID_NUMBERS];
    for(uint32 i = 0;i<GridList->Size;++i)
    {
        p3 GridNumber = *((p3*)GridList->DataStart+i);
        spatial_partition_grid* CurrentPartition = GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x];
        if(CurrentPartition)
        {
            for(uint32 j = 0;j<CurrentPartition->Size;++j)
            {
                if((CurrentPartition->IndexStart+j)->PartitionType == EntityType)
                {
                    PushStretchyBuffer(STRETCHY_BUFFER_TEMP_INDEX,&(CurrentPartition->IndexStart+j)->EntityIndexInArray,StretchyBuffers);
                }
            }
        }
    }
    return(RemoveDuplicatesFromEntityList(StretchyBuffers->StretchyBufferInfo[STRETCHY_BUFFER_TEMP_INDEX]));
}

//------------------------------

internal void ClearPartition(game_state* GameState,game_memory* GameMemory)// does not clear indice info for levels. probably the source of the rare jank that happens. this just needs more thought.
{
    GameState->SpatialPartition.NumOfGridHoles = 0;
    int i = 0;
    while(i < NUM_OF_BUFFER_HOLES)
    {
        GameState->SpatialPartition.SpatialMemoryHoles[i].GridHoleStart = 0;
        ++i;
    }
    GameState->SpatialPartition.LastSpatialGrid = 0;
    for(int z = 0;z<PARTITION_DEPTH;++z)
    {
        for(int y = 0;y<PARTITION_HEIGHT;++y)
        {
            for(int x = 0;x<PARTITION_STRIDE;++x)
            {
                GameState->SpatialPartition.SpatialGrid[z][y][x] = {};
            }
        }
    }
    GameState->PartitionIndices.NumOfIndicesInfoHoles = 0;
    i = 0;
    while(i < NUM_OF_BUFFER_HOLES)
    {
        GameState->PartitionIndices.PartitionIndicesHoles[i].IndicesInfoHoleStart = 0;
        ++i;
    }
    GameState->PartitionIndices.LastIndicesInfo = 0;
    //----------
    i = 0;
    while(i < MAX_ENTITIES)
    {
        GameState->LevelEntities.LevelPartitionIndices[i] = {};
        ++i;
    }
    i = 0;
    while(i < MAX_PLAYERS)
    {
        GameState->PlayerEntities.PlayerPartitionIndices[i] = {};
        ++i;
    }
}

internal partition_bounds GetEntityPartitionBounds(spatial_partition_index EntityIndex,game_state* GameState)
{
    AABB BoundingVolume = {};
    if(EntityIndex.PartitionType == PARTITIONTYPE_LEVEL)
    {
        BoundingVolume = GameState->LevelEntities.BoundingBox[EntityIndex.EntityIndexInArray];
    }
    else if(EntityIndex.PartitionType == PARTITIONTYPE_PLAYER)
    {
        BoundingVolume = GameState->PlayerEntities.BoundingBox[EntityIndex.EntityIndexInArray];
    }
    partition_bounds PartitionBounds = 
    {
        (int32)BoundingVolume.Origin.x/PARTITION_DIMENSION,
        (int32)BoundingVolume.Origin.y/PARTITION_DIMENSION,
        (int32)BoundingVolume.Origin.z/PARTITION_DIMENSION,
        (int32)BoundingVolume.MaxX/PARTITION_DIMENSION,
        (int32)BoundingVolume.MaxY/PARTITION_DIMENSION,
        (int32)BoundingVolume.MaxZ/PARTITION_DIMENSION
    };
    if(PartitionBounds.MinXCell < 0)
    {
        PartitionBounds.MinXCell = 0;
    }
    else if(PartitionBounds.MinXCell > PARTITION_MAXX_INDEX)
    {
        PartitionBounds.MinXCell = PARTITION_MAXX_INDEX;
    }
    //----------
    if(PartitionBounds.MinYCell < 0)
    {
        PartitionBounds.MinYCell = 0;
    }
    else if(PartitionBounds.MinYCell > PARTITION_MAXY_INDEX)
    {
        PartitionBounds.MinYCell = PARTITION_MAXY_INDEX;
    }
    //----------
    if(PartitionBounds.MinZCell < 0)
    {
        PartitionBounds.MinZCell = 0;
    }
    else if(PartitionBounds.MinZCell > PARTITION_MAXZ_INDEX)
    {
        PartitionBounds.MinZCell = PARTITION_MAXZ_INDEX;
    }
    //------------------------------
    if(PartitionBounds.MaxXCell < 0)
    {
        PartitionBounds.MaxXCell = 0;
    }
    else if(PartitionBounds.MaxXCell > PARTITION_MAXX_INDEX)
    {
        PartitionBounds.MaxXCell = PARTITION_MAXX_INDEX;
    }
    //----------
    if(PartitionBounds.MaxYCell < 0)
    {
        PartitionBounds.MaxYCell = 0;
    }
    else if(PartitionBounds.MaxYCell > PARTITION_MAXY_INDEX)
    {
        PartitionBounds.MaxYCell = PARTITION_MAXY_INDEX;
    }
    //----------
    if(PartitionBounds.MaxZCell < 0)
    {
        PartitionBounds.MaxZCell = 0;
    }
    else if(PartitionBounds.MaxZCell > PARTITION_MAXZ_INDEX)
    {
        PartitionBounds.MaxZCell = PARTITION_MAXZ_INDEX;
    }
    return(PartitionBounds);
}

//------------------------------

internal void InitializeGrid(spatial_partition_index EntityIndex,p3 GridNumber,game_state* GameState,game_memory* GameMemory)
{
    if(GameState->SpatialPartition.LastSpatialGrid == 0)
    {
        GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x] = (spatial_partition_grid*)GameMemory->SpatialGridMemory;
        GameState->SpatialPartition.LastSpatialGrid = GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x];
        GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->Size = 0;
        GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->Capacity = 1;
        GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->IndexStart = (spatial_partition_index*)GameMemory->SpatialIndexMemory;
        GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->SpatialGridPointer = &GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x];
    }
    else
    {
        GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x] = GameState->SpatialPartition.LastSpatialGrid + 1;
        GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->Size = 0;
        GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->Capacity = 1;
        GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->IndexStart = GameState->SpatialPartition.LastSpatialGrid->IndexStart + GameState->SpatialPartition.LastSpatialGrid->Capacity;
        GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->SpatialGridPointer = &GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x];
        GameState->SpatialPartition.LastSpatialGrid = GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x];
    }
}

internal void RemoveElementFromGrid(uint32 Slot,p3 GridNumber,game_state* GameState,game_memory* GameMemory)
{
    --GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->Size;
    if(Slot < GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->Size)
    {
        memmove(GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->IndexStart + Slot,GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->IndexStart + (Slot+1),sizeof(spatial_partition_index)*(GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->Size-Slot));
        //----------gotta subtract 1 from the partition index location for every entity after the removed.
        spatial_partition_index* TargetEntity = GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->IndexStart + Slot;
        partition_bounds TargetPartitionBounds = {};
        partition_indices_info* PartitionIndices = {};
        for(uint32 i = Slot;i<GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->Size;++i)
        {
            if((*TargetEntity).PartitionType == PARTITIONTYPE_LEVEL)
            {
                PartitionIndices = GameState->LevelEntities.LevelPartitionIndices[(*TargetEntity).EntityIndexInArray];
            }
            else if((*TargetEntity).PartitionType == PARTITIONTYPE_PLAYER)
            {
                PartitionIndices = GameState->PlayerEntities.PlayerPartitionIndices[(*TargetEntity).EntityIndexInArray];
            }
            TargetPartitionBounds = GetEntityPartitionBounds(*TargetEntity,GameState);
            uint32 PartitionWidth = (TargetPartitionBounds.MaxXCell - TargetPartitionBounds.MinXCell)+1;
            uint32 PartitionHeight = (TargetPartitionBounds.MaxYCell - TargetPartitionBounds.MinYCell)+1;
            uint32 PartitionIndicesSlotInEntity =
                (GridNumber.x - TargetPartitionBounds.MinXCell) +
                ( (GridNumber.y - TargetPartitionBounds.MinYCell) * (PartitionWidth) ) +
                ( (GridNumber.z - TargetPartitionBounds.MinZCell) * (PartitionWidth*PartitionHeight) );
            --*(PartitionIndices->IndicesInPartition+PartitionIndicesSlotInEntity);
            ++TargetEntity;
        }
    }
}

internal uint32 PushElementToGrid(spatial_partition_index EntityIndex,p3 GridNumber,game_state* GameState,game_memory* GameMemory)
{
    if(GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x] == 0)
    {
        InitializeGrid(EntityIndex,GridNumber,GameState,GameMemory);
    }
    if(GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->Size < GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->Capacity)
    {
        *(GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->IndexStart + GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->Size) = EntityIndex;
        ++GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->Size;
    }
    else
    {
        if(GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x] == GameState->SpatialPartition.LastSpatialGrid)
        {
            GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->Capacity *= 2;
            *(GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->IndexStart + GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->Size) = EntityIndex;
            ++GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->Size;
        }
        else
        {
            GameState->SpatialPartition.SpatialMemoryHoles[GameState->SpatialPartition.NumOfGridHoles].GridHoleStart = GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x];
            GameState->SpatialPartition.SpatialMemoryHoles[GameState->SpatialPartition.NumOfGridHoles].IndexHoleStart = GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->IndexStart;
            ++GameState->SpatialPartition.NumOfGridHoles;
            memmove(GameState->SpatialPartition.LastSpatialGrid+1,GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x],sizeof(spatial_partition_grid));
            memmove(GameState->SpatialPartition.LastSpatialGrid->IndexStart + GameState->SpatialPartition.LastSpatialGrid->Capacity,GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->IndexStart,sizeof(spatial_partition_index)*GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->Capacity);
            memset(GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x],0,sizeof(spatial_partition_grid));
            GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x] = GameState->SpatialPartition.LastSpatialGrid + 1;
            GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->Capacity *= 2;
            GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->IndexStart = GameState->SpatialPartition.LastSpatialGrid->IndexStart + GameState->SpatialPartition.LastSpatialGrid->Capacity;
            *(GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->IndexStart + GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->Size) = EntityIndex;
            ++GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->Size;
            GameState->SpatialPartition.LastSpatialGrid = GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x];
        }
    }
    return(GameState->SpatialPartition.SpatialGrid[GridNumber.z][GridNumber.y][GridNumber.x]->Size-1);
}

internal void AdvanceSpatialGridHoles(game_state* GameState)
{
    int i;
    ADVANCESPATIALHOLESAGAIN:;
    i = 0;
    for(i;i<GameState->SpatialPartition.NumOfGridHoles;++i)
    {
        if((GameState->SpatialPartition.SpatialMemoryHoles[i].GridHoleStart+1)->Capacity != 0)
        {
            memmove(GameState->SpatialPartition.SpatialMemoryHoles[i].GridHoleStart,GameState->SpatialPartition.SpatialMemoryHoles[i].GridHoleStart + 1,sizeof(spatial_partition_grid));
            GameState->SpatialPartition.SpatialMemoryHoles[i].GridHoleStart->IndexStart = (spatial_partition_index*)memmove(GameState->SpatialPartition.SpatialMemoryHoles[i].IndexHoleStart,GameState->SpatialPartition.SpatialMemoryHoles[i].GridHoleStart->IndexStart,sizeof(spatial_partition_index)*GameState->SpatialPartition.SpatialMemoryHoles[i].GridHoleStart->Capacity);
            *(GameState->SpatialPartition.SpatialMemoryHoles[i].GridHoleStart->SpatialGridPointer) = GameState->SpatialPartition.SpatialMemoryHoles[i].GridHoleStart;
            GameState->SpatialPartition.SpatialMemoryHoles[i].IndexHoleStart += GameState->SpatialPartition.SpatialMemoryHoles[i].GridHoleStart->Capacity;
            ++GameState->SpatialPartition.SpatialMemoryHoles[i].GridHoleStart;
            memset(GameState->SpatialPartition.SpatialMemoryHoles[i].GridHoleStart,0,sizeof(spatial_partition_grid));
        }
        if(GameState->SpatialPartition.SpatialMemoryHoles[i].GridHoleStart >= GameState->SpatialPartition.LastSpatialGrid)
        {
            GameState->SpatialPartition.LastSpatialGrid = (GameState->SpatialPartition.SpatialMemoryHoles[i].GridHoleStart-1);
            memmove(&GameState->SpatialPartition.SpatialMemoryHoles[i],&GameState->SpatialPartition.SpatialMemoryHoles[i+1],sizeof(spatial_grid_hole)*GameState->SpatialPartition.NumOfGridHoles-i);
            --GameState->SpatialPartition.NumOfGridHoles;
            goto ADVANCESPATIALHOLESAGAIN;
        }
    }
    if(GameState->SpatialPartition.NumOfGridHoles >= NUM_OF_BUFFER_HOLES-1)
    {
        goto ADVANCESPATIALHOLESAGAIN;
    }
    Assert(GameState->SpatialPartition.NumOfGridHoles < NUM_OF_BUFFER_HOLES);
}

//------------------------------

internal partition_indices_info* InitializeIndicesInfo(partition_indices_info** EntityIndiceInfo,partition_indices_info* IndicesInfoLocation,game_state* GameState,game_memory* GameMemory)
{
    if(GameState->PartitionIndices.LastIndicesInfo == 0)
    {
        IndicesInfoLocation = (partition_indices_info*)GameMemory->PartitionIndicesInfo;
        *EntityIndiceInfo = IndicesInfoLocation;
        GameState->PartitionIndices.LastIndicesInfo = IndicesInfoLocation;
        IndicesInfoLocation->Size = 0;
        IndicesInfoLocation->Capacity = 1;
        IndicesInfoLocation->IndicesInPartition = (uint32*)GameMemory->PartitionIndicesData;
        IndicesInfoLocation->IndicesInfoPointer = EntityIndiceInfo;
    }
    else
    {
        IndicesInfoLocation = GameState->PartitionIndices.LastIndicesInfo + 1;
        *EntityIndiceInfo = IndicesInfoLocation;
        IndicesInfoLocation->Size = 0;
        IndicesInfoLocation->Capacity = 1;
        IndicesInfoLocation->IndicesInPartition = GameState->PartitionIndices.LastIndicesInfo->IndicesInPartition + GameState->PartitionIndices.LastIndicesInfo->Capacity;
        GameState->PartitionIndices.LastIndicesInfo = IndicesInfoLocation;
        IndicesInfoLocation->IndicesInfoPointer = EntityIndiceInfo;
    }
    return(IndicesInfoLocation);
}

internal void PushPartitionIndexToEntity(spatial_partition_index EntityIndex,uint32 PartitionIndex,game_state* GameState,game_memory* GameMemory)
{
    partition_indices_info** EntityIndiceInfo = {};
    if(EntityIndex.PartitionType == PARTITIONTYPE_LEVEL)
    {
        EntityIndiceInfo = &GameState->LevelEntities.LevelPartitionIndices[EntityIndex.EntityIndexInArray];
    }
    else if(EntityIndex.PartitionType == PARTITIONTYPE_PLAYER)
    {
        EntityIndiceInfo = &GameState->PlayerEntities.PlayerPartitionIndices[EntityIndex.EntityIndexInArray];
    }
    partition_indices_info* IndicesInfoLocation = {};
    if(*EntityIndiceInfo == 0)
    {
        IndicesInfoLocation = InitializeIndicesInfo(EntityIndiceInfo,IndicesInfoLocation,GameState,GameMemory);
    }
    else
    {
        IndicesInfoLocation = *EntityIndiceInfo;
    }
    if(IndicesInfoLocation->Size < IndicesInfoLocation->Capacity)
    {
        *(IndicesInfoLocation->IndicesInPartition + IndicesInfoLocation->Size) = PartitionIndex;
        ++IndicesInfoLocation->Size;
    }
    else
    {
        if(IndicesInfoLocation == GameState->PartitionIndices.LastIndicesInfo)
        {
            IndicesInfoLocation->Capacity *= 2;
            *(IndicesInfoLocation->IndicesInPartition + IndicesInfoLocation->Size) = PartitionIndex;
            ++IndicesInfoLocation->Size;
        }
        else
        {
            GameState->PartitionIndices.PartitionIndicesHoles[GameState->PartitionIndices.NumOfIndicesInfoHoles].IndicesInfoHoleStart = IndicesInfoLocation;
            GameState->PartitionIndices.PartitionIndicesHoles[GameState->PartitionIndices.NumOfIndicesInfoHoles].IndicesDataHoleStart = IndicesInfoLocation->IndicesInPartition;
            ++GameState->PartitionIndices.NumOfIndicesInfoHoles;
            memmove(GameState->PartitionIndices.LastIndicesInfo+1,IndicesInfoLocation,sizeof(partition_indices_info));
            memmove(GameState->PartitionIndices.LastIndicesInfo->IndicesInPartition + GameState->PartitionIndices.LastIndicesInfo->Capacity,IndicesInfoLocation->IndicesInPartition,sizeof(uint32)*IndicesInfoLocation->Capacity);
            memset(IndicesInfoLocation,0,sizeof(partition_indices_info));
            IndicesInfoLocation = GameState->PartitionIndices.LastIndicesInfo+1;
            *IndicesInfoLocation->IndicesInfoPointer = IndicesInfoLocation;
            IndicesInfoLocation->Capacity *= 2;
            IndicesInfoLocation->IndicesInPartition = GameState->PartitionIndices.LastIndicesInfo->IndicesInPartition + GameState->PartitionIndices.LastIndicesInfo->Capacity;
            *(IndicesInfoLocation->IndicesInPartition + IndicesInfoLocation->Size) = PartitionIndex;
            ++IndicesInfoLocation->Size;
            GameState->PartitionIndices.LastIndicesInfo = IndicesInfoLocation;
        }
    }
}

internal void AdvanceIndicesInfoHoles(game_state* GameState)
{
    int i;
    ADVANCEINFOHOLESAGAIN:;
    i = 0;
    for(i;i<GameState->PartitionIndices.NumOfIndicesInfoHoles;++i)
    {
        if((GameState->PartitionIndices.PartitionIndicesHoles[i].IndicesInfoHoleStart+1)->Capacity != 0)
        {
            memmove(GameState->PartitionIndices.PartitionIndicesHoles[i].IndicesInfoHoleStart,GameState->PartitionIndices.PartitionIndicesHoles[i].IndicesInfoHoleStart + 1,sizeof(partition_indices_info));
            GameState->PartitionIndices.PartitionIndicesHoles[i].IndicesInfoHoleStart->IndicesInPartition = (uint32*)memmove(GameState->PartitionIndices.PartitionIndicesHoles[i].IndicesDataHoleStart,GameState->PartitionIndices.PartitionIndicesHoles[i].IndicesInfoHoleStart->IndicesInPartition,sizeof(uint32)*GameState->PartitionIndices.PartitionIndicesHoles[i].IndicesInfoHoleStart->Capacity);
            *(GameState->PartitionIndices.PartitionIndicesHoles[i].IndicesInfoHoleStart->IndicesInfoPointer) = GameState->PartitionIndices.PartitionIndicesHoles[i].IndicesInfoHoleStart;
            GameState->PartitionIndices.PartitionIndicesHoles[i].IndicesDataHoleStart += GameState->PartitionIndices.PartitionIndicesHoles[i].IndicesInfoHoleStart->Capacity;
            ++GameState->PartitionIndices.PartitionIndicesHoles[i].IndicesInfoHoleStart;
            memset(GameState->PartitionIndices.PartitionIndicesHoles[i].IndicesInfoHoleStart,0,sizeof(partition_indices_info));
        }
        if(GameState->PartitionIndices.PartitionIndicesHoles[i].IndicesInfoHoleStart >= GameState->PartitionIndices.LastIndicesInfo)
        {
            GameState->PartitionIndices.LastIndicesInfo = (GameState->PartitionIndices.PartitionIndicesHoles[i].IndicesInfoHoleStart-1);
            memmove(&GameState->PartitionIndices.PartitionIndicesHoles[i],&GameState->PartitionIndices.PartitionIndicesHoles[i+1],sizeof(partition_indices_hole)*GameState->PartitionIndices.NumOfIndicesInfoHoles-i);
            --GameState->PartitionIndices.NumOfIndicesInfoHoles;
        }
    }
    if(GameState->PartitionIndices.NumOfIndicesInfoHoles >= NUM_OF_BUFFER_HOLES-1)
    {
        goto ADVANCEINFOHOLESAGAIN;
    }
    Assert(GameState->PartitionIndices.NumOfIndicesInfoHoles < NUM_OF_BUFFER_HOLES);
}

//------------------------------

internal void RemoveEntityFromPartition(spatial_partition_index EntityIndex,game_state* GameState,game_memory* GameMemory)
{
    partition_indices_info* PartitionIndices = {};
    if(EntityIndex.PartitionType == PARTITIONTYPE_LEVEL)
    {
        PartitionIndices = GameState->LevelEntities.LevelPartitionIndices[EntityIndex.EntityIndexInArray];
    }
    else if(EntityIndex.PartitionType == PARTITIONTYPE_PLAYER)
    {
        PartitionIndices = GameState->PlayerEntities.PlayerPartitionIndices[EntityIndex.EntityIndexInArray];
    }
    partition_bounds EntityPartitionBounds = GetEntityPartitionBounds(EntityIndex,GameState);
    uint32* IndexInPartition = PartitionIndices->IndicesInPartition;
    for(int z = EntityPartitionBounds.MinZCell;z<=EntityPartitionBounds.MaxZCell;++z)
    {
        for(int y = EntityPartitionBounds.MinYCell;y<=EntityPartitionBounds.MaxYCell;++y)
        {
            for(int x = EntityPartitionBounds.MinXCell;x<=EntityPartitionBounds.MaxXCell;++x)
            {
                RemoveElementFromGrid(*IndexInPartition,{x,y,z},GameState,GameMemory);
                ++IndexInPartition;
            }
        }
    }
    PartitionIndices->Size = 0;
}

internal void AddEntityToPartition(spatial_partition_index EntityIndex,game_state* GameState,game_memory* GameMemory)
{
    partition_bounds EntityPartitionBounds = GetEntityPartitionBounds(EntityIndex,GameState);
    for(int z = EntityPartitionBounds.MinZCell;z<=EntityPartitionBounds.MaxZCell;++z)
    {
        for(int y = EntityPartitionBounds.MinYCell;y<=EntityPartitionBounds.MaxYCell;++y)
        {
            for(int x = EntityPartitionBounds.MinXCell;x<=EntityPartitionBounds.MaxXCell;++x)
            {
                uint32 PartitionIndex = PushElementToGrid(EntityIndex,{x,y,z},GameState,GameMemory);
                AdvanceSpatialGridHoles(GameState);
                PushPartitionIndexToEntity(EntityIndex,PartitionIndex,GameState,GameMemory);
                AdvanceIndicesInfoHoles(GameState);
            }
        }
    }
}