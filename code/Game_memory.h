struct game_memory
{
    void* GameStateMemory;
    void* DebugStateMemory;
    void* SpatialGridMemory;
    void* SpatialIndexMemory;
    void* PartitionIndicesInfo;
    void* PartitionIndicesData;
    void* StretchyBuffers;
    void* StretchyBufferInfo;
    void* StretchyBufferData;
};
global_variable void* ScratchMemoryBuffer;

//----------stretchy buffers
enum StretchyBufferID
{
    STRETCHY_BUFFER_TEMP_INDEX,
    STRETCHY_BUFFER_GRID_NUMBERS,
    STRETCHY_BUFFER_COLLISION_HIT_INDEX,
    STRETCHY_BUFFER_COLLISION_REFLECTION_HISTORY,
    STRETCHY_BUFFER_COLLISION_INDEX_HISTORY,
    NUMBER_OF_STRETCHY_BUFFERS
};
struct stretchy_buffer
{
    uint32 Capacity;
    uint32 Size;
    uint32 SizeOfElement;
    void* DataStart;
    stretchy_buffer** StretchyBufferInfoPointer;
};
struct stretchy_buffer_hole
{
    stretchy_buffer* BufferHoleStart;
    void* DataHoleStart;
};
#define NUM_OF_BUFFER_HOLES 100// TODO(NAME): can increase to make level editing less choppy(more holes to resolve over time) 
struct stretchy_buffer_list
{
    uint16 NumOfStretchyBufferHoles;
    stretchy_buffer* LastStretchyBuffer;
    stretchy_buffer_hole StretchyBufferHoles[NUM_OF_BUFFER_HOLES];
    stretchy_buffer* StretchyBufferInfo[NUMBER_OF_STRETCHY_BUFFERS];
};
//----------

internal void
InitializeStretchyBuffers(game_memory* GameMemory,stretchy_buffer_list* StretchyBuffers)
{
    uint32 ElementSize[NUMBER_OF_STRETCHY_BUFFERS] =
    {
        sizeof(uint32),//TEMP_INDEX
        sizeof(p3),//GRID_NUMBERS
        sizeof(uint32),//COLLISION_HIT_INDEX
        sizeof(v3),//COLLISION_REFLECTION_HISTORY
        sizeof(uint32),//COLLISION_INDEX_HISTORY
    };
    uint8* DataPointer = (uint8*)GameMemory->StretchyBufferData;
    for(int i = 0; i < NUMBER_OF_STRETCHY_BUFFERS;++i)
    {
        StretchyBuffers->StretchyBufferInfo[i] = (stretchy_buffer*)GameMemory->StretchyBufferInfo + i;
        StretchyBuffers->StretchyBufferInfo[i]->Capacity = 1;
        StretchyBuffers->StretchyBufferInfo[i]->Size = 0;
        StretchyBuffers->StretchyBufferInfo[i]->SizeOfElement = ElementSize[i];
        StretchyBuffers->StretchyBufferInfo[i]->DataStart = DataPointer;
        StretchyBuffers->StretchyBufferInfo[i]->StretchyBufferInfoPointer = &StretchyBuffers->StretchyBufferInfo[i];
        DataPointer += ElementSize[i];
        StretchyBuffers->LastStretchyBuffer = StretchyBuffers->StretchyBufferInfo[i];
    }
}

internal void 
PushStretchyBuffer(uint8 BufferID,void* Data,stretchy_buffer_list* StretchyBuffers)
{
    if(StretchyBuffers->StretchyBufferInfo[BufferID]->Size < StretchyBuffers->StretchyBufferInfo[BufferID]->Capacity)
    {
        memmove((uint8*)StretchyBuffers->StretchyBufferInfo[BufferID]->DataStart + (StretchyBuffers->StretchyBufferInfo[BufferID]->SizeOfElement * StretchyBuffers->StretchyBufferInfo[BufferID]->Size),
                Data,StretchyBuffers->StretchyBufferInfo[BufferID]->SizeOfElement);
        ++StretchyBuffers->StretchyBufferInfo[BufferID]->Size;
    }
    else
    {
        if(StretchyBuffers->StretchyBufferInfo[BufferID] == StretchyBuffers->LastStretchyBuffer)
        {
            StretchyBuffers->StretchyBufferInfo[BufferID]->Capacity *= 2;
            memmove((uint8*)StretchyBuffers->StretchyBufferInfo[BufferID]->DataStart + (StretchyBuffers->StretchyBufferInfo[BufferID]->SizeOfElement * StretchyBuffers->StretchyBufferInfo[BufferID]->Size),
                    Data,StretchyBuffers->StretchyBufferInfo[BufferID]->SizeOfElement);
            ++StretchyBuffers->StretchyBufferInfo[BufferID]->Size;
        }
        else
        {
            StretchyBuffers->StretchyBufferHoles[StretchyBuffers->NumOfStretchyBufferHoles].BufferHoleStart = StretchyBuffers->StretchyBufferInfo[BufferID];
            StretchyBuffers->StretchyBufferHoles[StretchyBuffers->NumOfStretchyBufferHoles].DataHoleStart = StretchyBuffers->StretchyBufferInfo[BufferID]->DataStart;
            ++StretchyBuffers->NumOfStretchyBufferHoles;
            memmove(StretchyBuffers->LastStretchyBuffer+1,StretchyBuffers->StretchyBufferInfo[BufferID],sizeof(stretchy_buffer));
            memmove((uint8*)StretchyBuffers->LastStretchyBuffer->DataStart + (StretchyBuffers->LastStretchyBuffer->Capacity*StretchyBuffers->LastStretchyBuffer->SizeOfElement),StretchyBuffers->StretchyBufferInfo[BufferID]->DataStart,StretchyBuffers->StretchyBufferInfo[BufferID]->SizeOfElement*StretchyBuffers->StretchyBufferInfo[BufferID]->Capacity);
            memset(StretchyBuffers->StretchyBufferInfo[BufferID],0,sizeof(stretchy_buffer));
            StretchyBuffers->StretchyBufferInfo[BufferID] = StretchyBuffers->LastStretchyBuffer + 1;
            StretchyBuffers->StretchyBufferInfo[BufferID]->Capacity *= 2;
            StretchyBuffers->StretchyBufferInfo[BufferID]->DataStart = (uint8*)StretchyBuffers->LastStretchyBuffer->DataStart + (StretchyBuffers->LastStretchyBuffer->Capacity*StretchyBuffers->LastStretchyBuffer->SizeOfElement);
            memmove((uint8*)StretchyBuffers->StretchyBufferInfo[BufferID]->DataStart + (StretchyBuffers->StretchyBufferInfo[BufferID]->SizeOfElement * StretchyBuffers->StretchyBufferInfo[BufferID]->Size),
                    Data,StretchyBuffers->StretchyBufferInfo[BufferID]->SizeOfElement);
            ++StretchyBuffers->StretchyBufferInfo[BufferID]->Size;
            StretchyBuffers->LastStretchyBuffer = StretchyBuffers->StretchyBufferInfo[BufferID];
        }
    }
}

internal void 
ClearStretchyBuffer(uint8 BufferID,stretchy_buffer_list* StretchyBuffers)
{
    StretchyBuffers->StretchyBufferInfo[BufferID]->Size = 0;
}

internal void
AdvanceStretchyBufferHoles(stretchy_buffer_list* StretchyBuffers)
{
    int i;
    ADVANCESTRETCHYHOLESAGAIN:;
    i = 0;
    for(i;i<StretchyBuffers->NumOfStretchyBufferHoles;++i)
    {
        if((StretchyBuffers->StretchyBufferHoles[i].BufferHoleStart+1)->Capacity != 0)
        {
            memmove(StretchyBuffers->StretchyBufferHoles[i].BufferHoleStart,StretchyBuffers->StretchyBufferHoles[i].BufferHoleStart + 1,sizeof(stretchy_buffer));
            StretchyBuffers->StretchyBufferHoles[i].BufferHoleStart->DataStart = memmove(StretchyBuffers->StretchyBufferHoles[i].DataHoleStart,StretchyBuffers->StretchyBufferHoles[i].BufferHoleStart->DataStart,StretchyBuffers->StretchyBufferHoles[i].BufferHoleStart->SizeOfElement*StretchyBuffers->StretchyBufferHoles[i].BufferHoleStart->Capacity);
            *(StretchyBuffers->StretchyBufferHoles[i].BufferHoleStart->StretchyBufferInfoPointer) = StretchyBuffers->StretchyBufferHoles[i].BufferHoleStart;
            StretchyBuffers->StretchyBufferHoles[i].DataHoleStart =  (uint8*)StretchyBuffers->StretchyBufferHoles[i].DataHoleStart + (StretchyBuffers->StretchyBufferHoles[i].BufferHoleStart->SizeOfElement*StretchyBuffers->StretchyBufferHoles[i].BufferHoleStart->Capacity);
            ++StretchyBuffers->StretchyBufferHoles[i].BufferHoleStart;
            memset(StretchyBuffers->StretchyBufferHoles[i].BufferHoleStart,0,sizeof(stretchy_buffer));
        }
        if(StretchyBuffers->StretchyBufferHoles[i].BufferHoleStart >= StretchyBuffers->LastStretchyBuffer)
        {
            StretchyBuffers->LastStretchyBuffer = (StretchyBuffers->StretchyBufferHoles[i].BufferHoleStart-1);
            memmove(&StretchyBuffers->StretchyBufferHoles[i],&StretchyBuffers->StretchyBufferHoles[i+1],sizeof(stretchy_buffer_hole)*StretchyBuffers->NumOfStretchyBufferHoles-i);
            --StretchyBuffers->NumOfStretchyBufferHoles;
            goto ADVANCESTRETCHYHOLESAGAIN;
        }
    }
    if(StretchyBuffers->NumOfStretchyBufferHoles >= NUM_OF_BUFFER_HOLES-1)
    {
        goto ADVANCESTRETCHYHOLESAGAIN;
    }
    Assert(StretchyBuffers->NumOfStretchyBufferHoles < NUM_OF_BUFFER_HOLES);
}

//----------
#define PLATFORM_LOAD_FILE(name) int32 name(char* FileName, void *FileContents)
typedef PLATFORM_LOAD_FILE(platform_load_file);
#define PLATFORM_WRITE_FILE(name) bool32 name(char *Filename, uint32 FileBytesToWrite, void *FileContents)
typedef PLATFORM_WRITE_FILE(platform_write_file);
#define PLATFORM_LOAD_TEXTURE(name) int32 name(char* TextureName, void *TextureContents)
typedef PLATFORM_LOAD_TEXTURE(platform_load_texture);
//----------
platform_load_file* PlatformLoadFile;
platform_write_file* PlatformWriteFile;
platform_load_texture* PlatformLoadTexture;