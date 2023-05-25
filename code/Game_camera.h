internal void
UpdateCamera(game_timers* GameTimers,
             game_player_input* PlayerInput,
             game_state* GameState)
{
    if(PlayerInput->InputInit & F3KEY_INPUT)
    {
        GameState->RenderArea.CameraMode = CAMMODE_STATIONARY;
    }
    if(PlayerInput->InputInit & F4KEY_INPUT)
    {
        if(GameState->RenderArea.CameraMode == CAMMODE_FOLLOWPLAYER)
        {
            GameState->RenderArea.CameraMode = CAMMODE_FREE;
        }
        else
        {
            GameState->RenderArea.CameraMode = CAMMODE_FOLLOWPLAYER;
        }
    }
    
    //----------Compile simulation list
    
    
    //----------
    
    v3 CameraDelta = {};
    
    switch(GameState->RenderArea.CameraMode)
    {
        case CAMMODE_FREE:
        {
            real32 CameraSpeed = 1000.0f;
            if( PlayerInput->InputInstant & SHIFTKEY_INPUT )
            {
                CameraSpeed *= 0.1f;
            }
            else if( PlayerInput->InputInstant & CONTROLKEY_INPUT )
            {
                CameraSpeed *= 0.001f;
            }
            if( PlayerInput->InputInstant & DKEY_INPUT )
            {
                CameraDelta.x += CameraSpeed * GameTimers->SecondsElapsed;
            }
            if( PlayerInput->InputInstant & AKEY_INPUT )
            {
                CameraDelta.x += -CameraSpeed * GameTimers->SecondsElapsed;	  
            }
            if( PlayerInput->InputInstant & WKEY_INPUT )
            {
                CameraDelta.y += CameraSpeed * GameTimers->SecondsElapsed;	  
            }
            if( PlayerInput->InputInstant & SKEY_INPUT )
            {
                CameraDelta.y += -CameraSpeed * GameTimers->SecondsElapsed;
            }
            //----------
            if( PlayerInput->InputInit & WHEELDOWNMOUSE_INPUT )
            {
                CameraDelta.z += CameraSpeed;
            }
            else if( PlayerInput->InputInit & WHEELUPMOUSE_INPUT)
            {
                CameraDelta.z -= CameraSpeed;
            }
        } break;
        
        //----------
        
        case CAMMODE_FOLLOWPLAYER:
        {
            GameState->RenderArea.TargetPos = 
            {
                GameState->PlayerEntities.Position[GameState->UserInformation.PlayerIndex].x,
                GameState->PlayerEntities.Position[GameState->UserInformation.PlayerIndex].y,
                GameState->PlayerEntities.Position[GameState->UserInformation.PlayerIndex].z + DEFAULT_CAMERA_HEIGHT
            };
        } break;
    }
    
    //----------
    
    GameState->RenderArea.TargetPos += CameraDelta;
    
    GameState->RenderArea.Left = GameState->RenderArea.TargetPos.x - VIDEO_BUFFER_HALFWIDTH;
    GameState->RenderArea.Right = GameState->RenderArea.TargetPos.x + VIDEO_BUFFER_HALFWIDTH;
    GameState->RenderArea.Bottom = GameState->RenderArea.TargetPos.y - VIDEO_BUFFER_HALFHEIGHT;
    GameState->RenderArea.Top = GameState->RenderArea.TargetPos.y + VIDEO_BUFFER_HALFHEIGHT;
    
}