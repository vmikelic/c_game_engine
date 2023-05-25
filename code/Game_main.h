#include "Game.h"
#include "Game_random.h"
#include "Game_partition.h"
#include "Game_hudcreate.h"
#include "Game_hudupdaterender.h"
#include "Game_rendersound.h"
#include "Game_savestate.h"
#include "Game_camera.h"
#include "Game_entitycreate.h"
#include "Game_renderentity.h"
#include "Game_entityupdate.h"
#include "Game_playerupdate.h"
#include "Game_debug.h"

//----------
internal void 
GameUpdateAndRender(game_timers* GameTimers,game_memory* GameMemory,game_audio_buffer* AudioBuffer,game_state* GameState,debug_struct* DebugStruct,game_player_input* PlayerInput,stretchy_buffer_list* StretchyBuffers)
{ 
    UpdateAndRenderHUD(GameState,DebugStruct,PlayerInput);
    UpdateEntities(GameTimers,GameState);
    UpdatePlayer(GameTimers,PlayerInput,GameState,GameMemory,StretchyBuffers);
    UpdateCamera(GameTimers,PlayerInput,GameState);
    
    //----------render player
    for(uint32 i = 0;i<GameState->ActivePlayers;++i)
    {
        RenderDebugCube(GameState->PlayerEntities.Position[i],
                        {(real32)GameState->PlayerEntities.HalfWidth[i]*2,
                        (real32)GameState->PlayerEntities.HalfHeight[i]*2,
                        (real32)GameState->PlayerEntities.HalfDepth[i]*2},
                        {GameState->PlayerEntities.YBasis[i].x,
                        GameState->PlayerEntities.YBasis[i].y,
                        0},
                        TEXTURENAME_SOLDIER,
                        GameState);
    }
    //----------
    
    DebugPass(GameMemory,PlayerInput,GameState,DebugStruct,StretchyBuffers,GameTimers);
    AdvanceSpatialGridHoles(GameState);
    AdvanceIndicesInfoHoles(GameState);
    AdvanceStretchyBufferHoles(StretchyBuffers);
    RenderLevelEntities(GameState);
}
