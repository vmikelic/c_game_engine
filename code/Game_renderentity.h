internal void
RenderDebugCube(v3 Position,
                v3real32 Dimensions,
                v3 Orientation,
                real32 Texture,
                game_state* GameState)
{
    Normalize(Orientation);
    v3real32 YBasis32 = 
    {
        (real32)Orientation.x,
        (real32)Orientation.y,
        (real32)Orientation.z
    };
    
    v3real32 XBasis32;
    if(YBasis32.x != 0 || YBasis32.y != 0)
    {
        real32 XYBasisInvLength = 1.0f / SquareRoot(YBasis32.x*YBasis32.x + YBasis32.y*YBasis32.y);
        XBasis32 = 
        {
            (YBasis32.y * XYBasisInvLength),
            -(YBasis32.x * XYBasisInvLength),
            0
        };
    }
    else
    {
        XBasis32 = 
        {
            1,
            0,
            0
        };
    }
    
    real32 ScreenWidthScaleFactor = 2.0f/VIDEO_BUFFER_WIDTH;
    real32 ScreenHeightScaleFactor = 2.0f/VIDEO_BUFFER_HEIGHT;
    v3real32 RenderArea = 
    {
        (real32)GameState->RenderArea.Left,
        (real32)GameState->RenderArea.Bottom,
        (real32)GameState->RenderArea.TargetPos.z,
    };
    v3real32* Vertices = (v3real32*)((real32*)&GameState->OpenGLVertices + GameState->VerticeCount);
    v3real32 ZBasis32 = 
    {
        (XBasis32.y * YBasis32.z) - (XBasis32.z * YBasis32.y),
        (XBasis32.z * YBasis32.x) - (XBasis32.x * YBasis32.z),
        (XBasis32.x * YBasis32.y) - (XBasis32.y * YBasis32.x)
    };
    
    XBasis32 =
    {
        XBasis32.x * Dimensions.x,
        XBasis32.y * Dimensions.x,
        XBasis32.z * Dimensions.x
    };
    YBasis32 =
    {
        YBasis32.x * Dimensions.y,
        YBasis32.y * Dimensions.y,
        YBasis32.z * Dimensions.y
    };
    ZBasis32 =
    {
        ZBasis32.x * Dimensions.z,
        ZBasis32.y * Dimensions.z,
        ZBasis32.z * Dimensions.z
    };
    //MaxZ Origin
    Dimensions = 
    {
        (ZBasis32.x - XBasis32.x - YBasis32.x)*0.5f,
        (ZBasis32.y - XBasis32.y - YBasis32.y)*0.5f,
        (ZBasis32.z - XBasis32.z - YBasis32.z)*0.5f
    };
    v3real32 CurrentVertice = 
    {
        (real32)Position.x + Dimensions.x,
        (real32)Position.y + Dimensions.y,
        (real32)Position.z + Dimensions.z
    };
    v3real32 TransformedVertice =
    {
        ( (CurrentVertice.x - RenderArea.x) * ScreenWidthScaleFactor ) - 1.0f,
        ( (CurrentVertice.y - RenderArea.y) * ScreenHeightScaleFactor ) - 1.0f,
        (RenderArea.z - CurrentVertice.z) * .001f
    };
    *Vertices = TransformedVertice;
    *(Vertices+1) = {0,1,Texture};
    *(Vertices+40) = TransformedVertice;
    *(Vertices+41) = {1,1,Texture};
    *(Vertices+46) = TransformedVertice;
    *(Vertices+47) = {1,1,Texture};
    *(Vertices+50) = TransformedVertice;
    *(Vertices+51) = {0,0,Texture};
    *(Vertices+54) = TransformedVertice;
    *(Vertices+55) = {0,0,Texture};
    //OriginZ Origin
    CurrentVertice = 
    {
        CurrentVertice.x - (ZBasis32.x),
        CurrentVertice.y - (ZBasis32.y),
        CurrentVertice.z - (ZBasis32.z)
    };
    TransformedVertice =
    {
        ( (CurrentVertice.x - RenderArea.x) * ScreenWidthScaleFactor ) - 1.0f,
        ( (CurrentVertice.y - RenderArea.y) * ScreenHeightScaleFactor ) - 1.0f,
        (RenderArea.z - CurrentVertice.z) * .001f
    };
    *(Vertices+2) = TransformedVertice;
    *(Vertices+3) = {0,0,Texture};
    *(Vertices+6) = TransformedVertice;
    *(Vertices+7) = {0,0,Texture};
    *(Vertices+44) = TransformedVertice;
    *(Vertices+45) = {1,0,Texture};
    //OriginZ MaxX
    CurrentVertice = 
    {
        CurrentVertice.x + (XBasis32.x),
        CurrentVertice.y + (XBasis32.y),
        CurrentVertice.z + (XBasis32.z)
    };
    TransformedVertice =
    {
        ( (CurrentVertice.x - RenderArea.x) * ScreenWidthScaleFactor ) - 1.0f,
        ( (CurrentVertice.y - RenderArea.y) * ScreenHeightScaleFactor ) - 1.0f,
        (RenderArea.z - CurrentVertice.z) * .001f
    };
    *(Vertices+8) = TransformedVertice;
    *(Vertices+9) = {1,0,Texture};
    *(Vertices+14) = TransformedVertice;
    *(Vertices+15) = {0,0,Texture};
    *(Vertices+18) = TransformedVertice;
    *(Vertices+19) = {0,0,Texture};
    //MaxZ MaxX
    CurrentVertice = 
    {
        CurrentVertice.x + (ZBasis32.x),
        CurrentVertice.y + (ZBasis32.y),
        CurrentVertice.z + (ZBasis32.z)
    };
    TransformedVertice =
    {
        ( (CurrentVertice.x - RenderArea.x) * ScreenWidthScaleFactor ) - 1.0f,
        ( (CurrentVertice.y - RenderArea.y) * ScreenHeightScaleFactor ) - 1.0f,
        (RenderArea.z - CurrentVertice.z) * .001f
    };
    *(Vertices+4) = TransformedVertice;
    *(Vertices+5) = {1,1,Texture};
    *(Vertices+10) = TransformedVertice;
    *(Vertices+11) = {1,1,Texture};
    *(Vertices+12) = TransformedVertice;
    *(Vertices+13) = {0,1,Texture};
    *(Vertices+56) = TransformedVertice;
    *(Vertices+57) = {1,0,Texture};
    //MaxZ MaxXY
    CurrentVertice = 
    {
        CurrentVertice.x + (YBasis32.x),
        CurrentVertice.y + (YBasis32.y),
        CurrentVertice.z + (YBasis32.z)
    };
    TransformedVertice =
    {
        ( (CurrentVertice.x - RenderArea.x) * ScreenWidthScaleFactor ) - 1.0f,
        ( (CurrentVertice.y - RenderArea.y) * ScreenHeightScaleFactor ) - 1.0f,
        (RenderArea.z - CurrentVertice.z) * .001f
    };
    *(Vertices+16) = TransformedVertice;
    *(Vertices+17) = {1,1,Texture};
    *(Vertices+22) = TransformedVertice;
    *(Vertices+23) = {1,1,Texture};
    *(Vertices+24) = TransformedVertice;
    *(Vertices+25) = {0,1,Texture};
    *(Vertices+52) = TransformedVertice;
    *(Vertices+53) = {1,1,Texture};
    *(Vertices+58) = TransformedVertice;
    *(Vertices+59) = {1,1,Texture};
    //OriginZ MaxXY
    CurrentVertice = 
    {
        CurrentVertice.x - (ZBasis32.x),
        CurrentVertice.y - (ZBasis32.y),
        CurrentVertice.z - (ZBasis32.z)
    };
    TransformedVertice =
    {
        ( (CurrentVertice.x - RenderArea.x) * ScreenWidthScaleFactor ) - 1.0f,
        ( (CurrentVertice.y - RenderArea.y) * ScreenHeightScaleFactor ) - 1.0f,
        (RenderArea.z - CurrentVertice.z) * .001f
    };
    *(Vertices+20) = TransformedVertice;
    *(Vertices+21) = {1,0,Texture};
    *(Vertices+26) = TransformedVertice;
    *(Vertices+27) = {0,0,Texture};
    *(Vertices+30) = TransformedVertice;
    *(Vertices+31) = {0,0,Texture};
    //OriginZ MaxY
    CurrentVertice = 
    {
        CurrentVertice.x - (XBasis32.x),
        CurrentVertice.y - (XBasis32.y),
        CurrentVertice.z - (XBasis32.z)
    };
    TransformedVertice =
    {
        ( (CurrentVertice.x - RenderArea.x) * ScreenWidthScaleFactor ) - 1.0f,
        ( (CurrentVertice.y - RenderArea.y) * ScreenHeightScaleFactor ) - 1.0f,
        (RenderArea.z - CurrentVertice.z) * .001f
    };
    *(Vertices+32) = TransformedVertice;
    *(Vertices+33) = {1,0,Texture};
    *(Vertices+38) = TransformedVertice;
    *(Vertices+39) = {0,0,Texture};
    *(Vertices+42) = TransformedVertice;
    *(Vertices+43) = {0,0,Texture};
    //MaxZ MaxY
    CurrentVertice = 
    {
        CurrentVertice.x + (ZBasis32.x),
        CurrentVertice.y + (ZBasis32.y),
        CurrentVertice.z + (ZBasis32.z)
    };
    TransformedVertice =
    {
        ( (CurrentVertice.x - RenderArea.x) * ScreenWidthScaleFactor ) - 1.0f,
        ( (CurrentVertice.y - RenderArea.y) * ScreenHeightScaleFactor ) - 1.0f,
        (RenderArea.z - CurrentVertice.z) * .001f
    };
    *(Vertices+28) = TransformedVertice;
    *(Vertices+29) = {1,1,Texture};
    *(Vertices+34) = TransformedVertice;
    *(Vertices+35) = {1,1,Texture};
    *(Vertices+36) = TransformedVertice;
    *(Vertices+37) = {0,1,Texture};
    *(Vertices+48) = TransformedVertice;
    *(Vertices+49) = {0,1,Texture};
    
    GameState->VerticeCount += 180;
}

//----------

internal void
RenderLevelEntities(game_state* GameState)
{
    real32 ScreenWidthScaleFactor = 2.0f/VIDEO_BUFFER_WIDTH;
    real32 ScreenHeightScaleFactor = 2.0f/VIDEO_BUFFER_HEIGHT;
    v3real32 RenderArea = 
    {
        (real32)GameState->RenderArea.Left,
        (real32)GameState->RenderArea.Bottom,
        (real32)GameState->RenderArea.TargetPos.z,
    };
    v3real32* Vertices = (v3real32*)((real32*)&GameState->OpenGLVertices + GameState->VerticeCount);
    
    for (uint32 i = 0 ; i < GameState->LevelEntitiesCreated; ++i)
    {
        v3real32 XBasis32;
        v3real32 YBasis32;
        v3real32 ZBasis32;
        v3real32 CurrentVertice;
        v3real32 TransformedVertice;
        real32 MinXTexture = 0;
        real32 MinYTexture = 0;
        real32 MaxXTexture;
        real32 TopMaxYTexture;
        real32 SideMaxYTexture;
        real32 MaxZTexture;
        real32 TextureLayer;
        //----------
        {
            uint32 Index = i;
            texture_index TextureIndex = GameState->LevelEntities.TextureIndex[Index];
            TextureLayer = TextureIndex.TextureLayer;
            YBasis32 = 
            {
                (real32)GameState->LevelEntities.YBasis[Index].x,
                (real32)GameState->LevelEntities.YBasis[Index].y,
                0
            };
            XBasis32 =
            {
                YBasis32.y,
                -YBasis32.x,
                0
            };
            
            v3real32 Dimensions = 
            {
                2.0f*(real32)GameState->LevelEntities.HalfWidth[Index],
                2.0f*(real32)GameState->LevelEntities.HalfHeight[Index],
                2.0f*(real32)GameState->LevelEntities.HalfDepth[Index]
            };
            if(GameState->LevelEntities.LevelType[Index] == LEVELTYPE_COLLIDESLOPE)
            {
                YBasis32.x = YBasis32.x*Dimensions.y;
                YBasis32.y = YBasis32.y*Dimensions.y;
                YBasis32.z = Dimensions.z;
                real32 NewHeight = SquareRoot(YBasis32.x*YBasis32.x + YBasis32.y*YBasis32.y + YBasis32.z*YBasis32.z);
                SideMaxYTexture = (NewHeight / 64.0f) * TextureIndex.TextureRepeatScale;
                TopMaxYTexture = SideMaxYTexture;
                Dimensions.y = NewHeight;
                NewHeight = 1.0f/NewHeight;
                YBasis32.x = YBasis32.x*NewHeight;
                YBasis32.y = YBasis32.y*NewHeight;
                YBasis32.z = YBasis32.z*NewHeight;
                Dimensions.z = 0;
                ZBasis32 = Cross(XBasis32,YBasis32);
            }
            else
            {
                SideMaxYTexture = (Dimensions.y / 64.0f) * TextureIndex.TextureRepeatScale;
                TopMaxYTexture = SideMaxYTexture;
                ZBasis32 = {0,0,1};
            }
            MaxXTexture = (Dimensions.x / 64.0f) * TextureIndex.TextureRepeatScale;
            MaxZTexture = (Dimensions.z / 64.0f) * TextureIndex.TextureRepeatScale;
            MinXTexture += TextureIndex.TextureOffsetX;
            MaxXTexture += TextureIndex.TextureOffsetX;
            MinYTexture += TextureIndex.TextureOffsetY;
            SideMaxYTexture += TextureIndex.TextureOffsetX;
            TopMaxYTexture += TextureIndex.TextureOffsetY;
            MaxZTexture += TextureIndex.TextureOffsetY;
            if(TextureIndex.TextureRepeatScale == 0)
            {
                MinXTexture = 0;
                MinYTexture = 0;
                MaxXTexture = 1;
                TopMaxYTexture = 1;
                SideMaxYTexture = 1;
                MaxZTexture = 1;
            }
            if(GameState->LevelEntities.LevelType[Index] > LEVELTYPE_COLLIDESLOPE)
            {
                MinXTexture = 0;
                MinYTexture = 0;
                MaxXTexture = 1;
                TopMaxYTexture = 1;
                SideMaxYTexture = 1;
                MaxZTexture = 1;
                TextureLayer = TEXTURENAME_OUTLINE;
            }
            XBasis32 =
            {
                XBasis32.x * Dimensions.x,
                XBasis32.y * Dimensions.x,
                XBasis32.z * Dimensions.x
            };
            YBasis32 =
            {
                YBasis32.x * Dimensions.y,
                YBasis32.y * Dimensions.y,
                YBasis32.z * Dimensions.y
            };
            ZBasis32 =
            {
                ZBasis32.x * Dimensions.z,
                ZBasis32.y * Dimensions.z,
                ZBasis32.z * Dimensions.z
            };
            //MaxZ Origin
            Dimensions = 
            {
                (ZBasis32.x - XBasis32.x - YBasis32.x)*0.5f,
                (ZBasis32.y - XBasis32.y - YBasis32.y)*0.5f,
                (ZBasis32.z - XBasis32.z - YBasis32.z)*0.5f
            };
            CurrentVertice = 
            {
                (real32)GameState->LevelEntities.Position[Index].x + Dimensions.x,
                (real32)GameState->LevelEntities.Position[Index].y + Dimensions.y,
                (real32)GameState->LevelEntities.Position[Index].z + Dimensions.z
            };
        }
        //----------
        //MaxZ Origin
        TransformedVertice =
        {
            ( (CurrentVertice.x - RenderArea.x) * ScreenWidthScaleFactor ) - 1.0f,
            ( (CurrentVertice.y - RenderArea.y) * ScreenHeightScaleFactor ) - 1.0f,
            (RenderArea.z - CurrentVertice.z) * .001f
        };
        *Vertices = TransformedVertice;
        *(Vertices+1) = {MinXTexture,MaxZTexture,TextureLayer};
        *(Vertices+40) = TransformedVertice;
        *(Vertices+41) = {SideMaxYTexture,MaxZTexture,TextureLayer};
        *(Vertices+46) = TransformedVertice;
        *(Vertices+47) = {SideMaxYTexture,MaxZTexture,TextureLayer};
        *(Vertices+50) = TransformedVertice;
        *(Vertices+51) = {MinXTexture,MinYTexture,TextureLayer};
        *(Vertices+54) = TransformedVertice;
        *(Vertices+55) = {MinXTexture,MinYTexture,TextureLayer};
        //OriginZ Origin
        CurrentVertice = 
        {
            CurrentVertice.x - (ZBasis32.x),
            CurrentVertice.y - (ZBasis32.y),
            CurrentVertice.z - (ZBasis32.z)
        };
        TransformedVertice =
        {
            ( (CurrentVertice.x - RenderArea.x) * ScreenWidthScaleFactor ) - 1.0f,
            ( (CurrentVertice.y - RenderArea.y) * ScreenHeightScaleFactor ) - 1.0f,
            (RenderArea.z - CurrentVertice.z) * .001f
        };
        *(Vertices+2) = TransformedVertice;
        *(Vertices+3) = {MinXTexture,MinYTexture,TextureLayer};
        *(Vertices+6) = TransformedVertice;
        *(Vertices+7) = {MinXTexture,MinYTexture,TextureLayer};
        *(Vertices+44) = TransformedVertice;
        *(Vertices+45) = {SideMaxYTexture,MinYTexture,TextureLayer};
        //OriginZ MaxX
        CurrentVertice = 
        {
            CurrentVertice.x + (XBasis32.x),
            CurrentVertice.y + (XBasis32.y),
            CurrentVertice.z + (XBasis32.z)
        };
        TransformedVertice =
        {
            ( (CurrentVertice.x - RenderArea.x) * ScreenWidthScaleFactor ) - 1.0f,
            ( (CurrentVertice.y - RenderArea.y) * ScreenHeightScaleFactor ) - 1.0f,
            (RenderArea.z - CurrentVertice.z) * .001f
        };
        *(Vertices+8) = TransformedVertice;
        *(Vertices+9) = {MaxXTexture,MinYTexture,TextureLayer};
        *(Vertices+14) = TransformedVertice;
        *(Vertices+15) = {MinXTexture,MinYTexture,TextureLayer};
        *(Vertices+18) = TransformedVertice;
        *(Vertices+19) = {MinXTexture,MinYTexture,TextureLayer};
        //MaxZ MaxX
        CurrentVertice = 
        {
            CurrentVertice.x + (ZBasis32.x),
            CurrentVertice.y + (ZBasis32.y),
            CurrentVertice.z + (ZBasis32.z)
        };
        TransformedVertice =
        {
            ( (CurrentVertice.x - RenderArea.x) * ScreenWidthScaleFactor ) - 1.0f,
            ( (CurrentVertice.y - RenderArea.y) * ScreenHeightScaleFactor ) - 1.0f,
            (RenderArea.z - CurrentVertice.z) * .001f
        };
        *(Vertices+4) = TransformedVertice;
        *(Vertices+5) = {MaxXTexture,MaxZTexture,TextureLayer};
        *(Vertices+10) = TransformedVertice;
        *(Vertices+11) = {MaxXTexture,MaxZTexture,TextureLayer};
        *(Vertices+12) = TransformedVertice;
        *(Vertices+13) = {MinXTexture,MaxZTexture,TextureLayer};
        *(Vertices+56) = TransformedVertice;
        *(Vertices+57) = {MaxXTexture,MinYTexture,TextureLayer};
        //MaxZ MaxXY
        CurrentVertice = 
        {
            CurrentVertice.x + (YBasis32.x),
            CurrentVertice.y + (YBasis32.y),
            CurrentVertice.z + (YBasis32.z)
        };
        TransformedVertice =
        {
            ( (CurrentVertice.x - RenderArea.x) * ScreenWidthScaleFactor ) - 1.0f,
            ( (CurrentVertice.y - RenderArea.y) * ScreenHeightScaleFactor ) - 1.0f,
            (RenderArea.z - CurrentVertice.z) * .001f
        };
        *(Vertices+16) = TransformedVertice;
        *(Vertices+17) = {SideMaxYTexture,MaxZTexture,TextureLayer};
        *(Vertices+22) = TransformedVertice;
        *(Vertices+23) = {SideMaxYTexture,MaxZTexture,TextureLayer};
        *(Vertices+24) = TransformedVertice;
        *(Vertices+25) = {MinXTexture,MaxZTexture,TextureLayer};
        *(Vertices+52) = TransformedVertice;
        *(Vertices+53) = {MaxXTexture,TopMaxYTexture,TextureLayer};
        *(Vertices+58) = TransformedVertice;
        *(Vertices+59) = {MaxXTexture,TopMaxYTexture,TextureLayer};
        //OriginZ MaxXY
        CurrentVertice = 
        {
            CurrentVertice.x - (ZBasis32.x),
            CurrentVertice.y - (ZBasis32.y),
            CurrentVertice.z - (ZBasis32.z)
        };
        TransformedVertice =
        {
            ( (CurrentVertice.x - RenderArea.x) * ScreenWidthScaleFactor ) - 1.0f,
            ( (CurrentVertice.y - RenderArea.y) * ScreenHeightScaleFactor ) - 1.0f,
            (RenderArea.z - CurrentVertice.z) * .001f
        };
        *(Vertices+20) = TransformedVertice;
        *(Vertices+21) = {SideMaxYTexture,MinYTexture,TextureLayer};
        *(Vertices+26) = TransformedVertice;
        *(Vertices+27) = {MinXTexture,MinYTexture,TextureLayer};
        *(Vertices+30) = TransformedVertice;
        *(Vertices+31) = {MinXTexture,MinYTexture,TextureLayer};
        //OriginZ MaxY
        CurrentVertice = 
        {
            CurrentVertice.x - (XBasis32.x),
            CurrentVertice.y - (XBasis32.y),
            CurrentVertice.z - (XBasis32.z)
        };
        TransformedVertice =
        {
            ( (CurrentVertice.x - RenderArea.x) * ScreenWidthScaleFactor ) - 1.0f,
            ( (CurrentVertice.y - RenderArea.y) * ScreenHeightScaleFactor ) - 1.0f,
            (RenderArea.z - CurrentVertice.z) * .001f
        };
        *(Vertices+32) = TransformedVertice;
        *(Vertices+33) = {MaxXTexture,MinYTexture,TextureLayer};
        *(Vertices+38) = TransformedVertice;
        *(Vertices+39) = {MinXTexture,MinYTexture,TextureLayer};
        *(Vertices+42) = TransformedVertice;
        *(Vertices+43) = {MinXTexture,MinYTexture,TextureLayer};
        //MaxZ MaxY
        CurrentVertice = 
        {
            CurrentVertice.x + (ZBasis32.x),
            CurrentVertice.y + (ZBasis32.y),
            CurrentVertice.z + (ZBasis32.z)
        };
        TransformedVertice =
        {
            ( (CurrentVertice.x - RenderArea.x) * ScreenWidthScaleFactor ) - 1.0f,
            ( (CurrentVertice.y - RenderArea.y) * ScreenHeightScaleFactor ) - 1.0f,
            (RenderArea.z - CurrentVertice.z) * .001f
        };
        *(Vertices+28) = TransformedVertice;
        *(Vertices+29) = {MaxXTexture,MaxZTexture,TextureLayer};
        *(Vertices+34) = TransformedVertice;
        *(Vertices+35) = {MaxXTexture,MaxZTexture,TextureLayer};
        *(Vertices+36) = TransformedVertice;
        *(Vertices+37) = {MinXTexture,MaxZTexture,TextureLayer};
        *(Vertices+48) = TransformedVertice;
        *(Vertices+49) = {MinXTexture,TopMaxYTexture,TextureLayer};
        
        Vertices = (v3real32*)((real32*)Vertices + 180);
    }
    
    GameState->VerticeCount += 180*GameState->LevelEntitiesCreated;
}