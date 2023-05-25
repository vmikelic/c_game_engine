internal void 
IncrementHUDValue(int32 Index,real32 Increment,debug_struct* DebugStruct)
{
    if(DebugStruct->DebugHUDElements.AttachedValue[Index] != 0)
    {
        switch(DebugStruct->DebugHUDElements.AttachedValueDataType[Index])
        {
            case HUDDATATYPE_UINT8:{*(uint8*)DebugStruct->DebugHUDElements.AttachedValue[Index] += (uint8)(DebugStruct->DebugHUDElements.IncrementValue[Index] * Increment);
                if(*(uint8*)DebugStruct->DebugHUDElements.AttachedValue[Index] < 0) 
                { *(uint8*)DebugStruct->DebugHUDElements.AttachedValue[Index] = 0;}
            } break;
            case HUDDATATYPE_UINT16:{*(uint16*)DebugStruct->DebugHUDElements.AttachedValue[Index] += (uint16)(DebugStruct->DebugHUDElements.IncrementValue[Index] * Increment);
                if(*(uint16*)DebugStruct->DebugHUDElements.AttachedValue[Index] < 0) 
                { *(uint16*)DebugStruct->DebugHUDElements.AttachedValue[Index] = 0;}
            } break;
            case HUDDATATYPE_UINT32:{*(uint32*)DebugStruct->DebugHUDElements.AttachedValue[Index] += (uint32)(DebugStruct->DebugHUDElements.IncrementValue[Index] * Increment);
                if(*(uint32*)DebugStruct->DebugHUDElements.AttachedValue[Index] < 0) 
                { *(uint32*)DebugStruct->DebugHUDElements.AttachedValue[Index] = 0;}
            } break;
            case HUDDATATYPE_UINT64:{*(uint64*)DebugStruct->DebugHUDElements.AttachedValue[Index] += (uint64)(DebugStruct->DebugHUDElements.IncrementValue[Index] * Increment);
                if(*(uint64*)DebugStruct->DebugHUDElements.AttachedValue[Index] < 0) 
                { *(uint64*)DebugStruct->DebugHUDElements.AttachedValue[Index] = 0;}
            } break;
            case HUDDATATYPE_INT8:{*(int8*)DebugStruct->DebugHUDElements.AttachedValue[Index] += (int8)(DebugStruct->DebugHUDElements.IncrementValue[Index] * Increment);
                if(*(int8*)DebugStruct->DebugHUDElements.AttachedValue[Index] < 0) 
                { *(int8*)DebugStruct->DebugHUDElements.AttachedValue[Index] = 0;}
            } break;
            case HUDDATATYPE_INT16:{*(int16*)DebugStruct->DebugHUDElements.AttachedValue[Index] += (int16)(DebugStruct->DebugHUDElements.IncrementValue[Index] * Increment);
                if(*(int16*)DebugStruct->DebugHUDElements.AttachedValue[Index] < 0) 
                { *(int16*)DebugStruct->DebugHUDElements.AttachedValue[Index] = 0;}
            } break;
            case HUDDATATYPE_INT32:{*(int32*)DebugStruct->DebugHUDElements.AttachedValue[Index] += (int32)(DebugStruct->DebugHUDElements.IncrementValue[Index] * Increment);
                if(*(int32*)DebugStruct->DebugHUDElements.AttachedValue[Index] < 0) 
                { *(int32*)DebugStruct->DebugHUDElements.AttachedValue[Index] = 0;}
            } break;
            case HUDDATATYPE_REAL32:{*(real32*)DebugStruct->DebugHUDElements.AttachedValue[Index] += (real32)(DebugStruct->DebugHUDElements.IncrementValue[Index] * Increment);
                if(*(real32*)DebugStruct->DebugHUDElements.AttachedValue[Index] < 0) 
                { *(real32*)DebugStruct->DebugHUDElements.AttachedValue[Index] = 0;}
            } break;
            case HUDDATATYPE_REAL64:{*(real64*)DebugStruct->DebugHUDElements.AttachedValue[Index] += (real64)(DebugStruct->DebugHUDElements.IncrementValue[Index] * Increment);
                if(*(real64*)DebugStruct->DebugHUDElements.AttachedValue[Index] < 0) 
                { *(real64*)DebugStruct->DebugHUDElements.AttachedValue[Index] = 0;}
            } break;
        }
    }
}

internal bool32
ButtonWasClicked(int32 HUDID,debug_struct* DebugStruct)
{
    Assert(DebugStruct->DebugHUDElements.HUDType[HUDID] == HUDTYPE_BUTTON ||
           DebugStruct->DebugHUDElements.HUDType[HUDID] == HUDTYPE_TRACKINGBUTTON);
    return(DebugStruct->ClickedButtonIndex == HUDID);
}

internal void
SetHUDVisibility(int32 HUDID,uint8 Visibility,debug_struct* DebugStruct)
{
    DebugStruct->DebugHUDElements.IsVisible[HUDID] = Visibility;
}

internal void
SetGroupHUDVisibility(int32 GroupHUDID,uint8 Visibility,debug_struct* DebugStruct)
{
    for(int32 i = 0; i < DebugStruct->DebugHUDGroups.ElementsContained[GroupHUDID]; ++i)
    {
        DebugStruct->DebugHUDElements.IsVisible[DebugStruct->DebugHUDGroups.ElementIndex[GroupHUDID][i]] = Visibility;
    }
}

internal void
SetAllHUDVisibility(uint8 Visibility,debug_struct* DebugStruct)
{
    for(int32 i = 0;i< DebugStruct->DebugHUDElements.HUDElementsCreated;++i)
    {
        DebugStruct->DebugHUDElements.IsVisible[i] = Visibility;
    }
}

internal void
ChangeGroupHUDRotation(int32 GroupHUDID,real64 Degrees,debug_struct* DebugStruct)
{
    Degrees *= 0.01745329251994329576923690768489;
    DebugStruct->DebugHUDGroups.YBasis[GroupHUDID] = {Cosine(Degrees),Sine(Degrees)};
}

internal void
DebugValue(uint8 DataType,void* Value,char* Name,debug_struct* DebugStruct)
{
    int32 Index = 0;
    for(int32 i = 0;i<DebugStruct->DebugHUDGroups.ElementsContained[GROUPHUDID_DEBUGGROUPVALUES];++i)
    {
        Index = DebugStruct->DebugHUDGroups.ElementIndex[GROUPHUDID_DEBUGGROUPVALUES][i];
        if(DebugStruct->DebugHUDElements.AttachedValue[Index] == 0 || DebugStruct->DebugHUDElements.AttachedValue[Index] == Value)
        {
            break;
        }
    }
    DebugStruct->DebugHUDElements.AttachedValueDataType[Index] = DataType;
    DebugStruct->DebugHUDElements.AttachedValue[Index] = Value;
    DebugStruct->DebugHUDElements.NumOfChar[Index] = sprintf(DebugStruct->DebugHUDElements.AttachedString[Index],"%s",Name);
    DebugStruct->DebugHUDElements.IsVisible[Index] = 1;
}

internal void
UpdateAndRenderHUD(game_state* GameState,debug_struct* DebugStruct,game_player_input* PlayerInput)
{
    v3real32* Vertices = (v3real32*)&GameState->OpenGLHUDVertices;
    int32 VerticeCount = 0;
    render_area RenderArea = GameState->RenderArea;
    real32 ScreenWidthScaleFactor = 2.0f/VIDEO_BUFFER_WIDTH;
    real32 ScreenHeightScaleFactor = 2.0f/VIDEO_BUFFER_HEIGHT;
    
    for(int32 x = 0; x < DebugStruct->DebugHUDGroups.HUDGroupsCreated; ++x)
    {
        v2 GroupYBasis = DebugStruct->DebugHUDGroups.YBasis[x];
        v2 GroupXBasis = -Perp(GroupYBasis);
        for(int32 y = 0; y < DebugStruct->DebugHUDGroups.ElementsContained[x]; ++y)
        {
            
            //----------
            
            int32 Index = DebugStruct->DebugHUDGroups.ElementIndex[x][y];
            if(DebugStruct->DebugHUDElements.IsVisible[Index])
            {
                real32 Width = DebugStruct->DebugHUDElements.Width[Index];
                real32 Height = DebugStruct->DebugHUDElements.Height[Index];
                v2 ElementYBasis = DebugStruct->DebugHUDElements.LocalYBasis[Index];
                v3 Offsets = DebugStruct->DebugHUDElements.GroupOffset[Index];
                v3 ScreenPosition =
                {
                    DebugStruct->DebugHUDGroups.ScreenPosition[x].x + Offsets.x,
                    DebugStruct->DebugHUDGroups.ScreenPosition[x].y + Offsets.y,
                    Offsets.z
                };
                if(DebugStruct->DebugHUDElements.GroupRot[Index])//should element inherit group rotation?
                {
                    ElementYBasis =
                    {//left multiply by inv mat for basis change. wiki=good
                        (ElementYBasis.x*GroupYBasis.y)+(ElementYBasis.y*-GroupXBasis.y),
                        (ElementYBasis.x*-GroupYBasis.x)+(ElementYBasis.y*GroupXBasis.x)
                    };
                    ScreenPosition =
                    {//left multiply by inv mat for basis change. wiki=good
                        (Offsets.x*GroupYBasis.y)+(Offsets.y*-GroupXBasis.y) + DebugStruct->DebugHUDGroups.ScreenPosition[x].x,
                        (Offsets.x*-GroupYBasis.x)+(Offsets.y*GroupXBasis.x) + DebugStruct->DebugHUDGroups.ScreenPosition[x].y,
                        Offsets.z
                    };
                }
                v2 ElementXBasis = -Perp(ElementYBasis);
                v2 HalfHeight = ElementYBasis * ( Height / 2.0);
                v2 HalfWidth = ElementXBasis * ( Width / 2.0);
                
                //----------
                
                if(DebugStruct->DebugHUDElements.HUDType[Index] == HUDTYPE_TRACKING ||
                   DebugStruct->DebugHUDElements.HUDType[Index] == HUDTYPE_TRACKINGBUTTON)
                {
                    v3 Position = *DebugStruct->DebugHUDGroups.TrackingPosition[x];
                    if(RenderArea.TargetPos.z - Position.z > 0)
                    {
                        v2 ScreenVector = 
                        {
                            Position.x - RenderArea.TargetPos.x,
                            Position.y - RenderArea.TargetPos.y
                        };
                        ScreenVector *= (1000/(RenderArea.TargetPos.z - Position.z));//scaling vector based on perspective(making screen space)
                        ScreenPosition =
                        {
                            (VIDEO_BUFFER_HALFWIDTH + ScreenVector.x) + ScreenPosition.x,
                            (VIDEO_BUFFER_HALFHEIGHT + ScreenVector.y) + ScreenPosition.y,
                            ScreenPosition.z
                        };
                    }
                    else
                    {
                        goto NEXTHUDELEMENT;
                    }
                }
                
                //----------
                
                v2 MaxXY = V2(ScreenPosition) + (HalfWidth + HalfHeight);
                v2 MaxX = V2(ScreenPosition) + (HalfWidth + -HalfHeight);
                v2 MaxY = V2(ScreenPosition) + (-HalfWidth + HalfHeight);
                v2 Origin = V2(ScreenPosition) + (-HalfWidth + -HalfHeight);
                
                //----------
                
                if(DebugStruct->DebugHUDElements.HUDType[Index] == HUDTYPE_BUTTON ||
                   DebugStruct->DebugHUDElements.HUDType[Index] == HUDTYPE_TRACKINGBUTTON)
                {
                    v2 ScreenMouse = 
                    {
                        PlayerInput->ScreenMouseX * VIDEO_BUFFER_WIDTH,
                        PlayerInput->ScreenMouseY * VIDEO_BUFFER_HEIGHT
                    };
                    if(Inner((ScreenMouse - Origin),ElementXBasis) >= 0)
                    {
                        if(Inner((ScreenMouse - MaxXY),-ElementXBasis) >= 0)
                        {
                            if(Inner((ScreenMouse - MaxX),ElementYBasis) >= 0)
                            {
                                if(Inner((ScreenMouse - MaxY),-ElementYBasis) >= 0)
                                {
                                    if(DebugStruct->DebugHUDElements.IsActive[Index])
                                    {
                                        if(PlayerInput->InputInit & LEFTCLICKMOUSE_INPUT)
                                        {
                                            IncrementHUDValue(Index,1,DebugStruct);
                                            DebugStruct->ClickedButtonIndex = Index;
                                        }
                                        else if(PlayerInput->InputInit & RIGHTCLICKMOUSE_INPUT)
                                        {
                                            IncrementHUDValue(Index,-1,DebugStruct);
                                        }
                                    }
                                    if(DebugStruct->DebugHUDElements.HUDType[Index] == HUDTYPE_BUTTON)
                                    {
                                        if(PlayerInput->InputInit & MIDDLECLICKMOUSE_INPUT)
                                        {
                                            DebugStruct->DebugHUDElements.IsActive[Index] ^= 0x1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                
                //----------
                
                if(DebugStruct->DebugHUDElements.AttachedValue[Index] != 0)
                {
                    char* CurrentLetter = &DebugStruct->DebugHUDElements.AttachedString[Index][DebugStruct->DebugHUDElements.NumOfChar[Index]];
                    switch(DebugStruct->DebugHUDElements.AttachedValueDataType[Index])
                    {
                        case HUDDATATYPE_UINT8:{ sprintf(CurrentLetter,"%u",*(uint8*)DebugStruct->DebugHUDElements.AttachedValue[Index]);
                        } break;
                        case HUDDATATYPE_UINT16:{ sprintf(CurrentLetter,"%u",*(uint16*)DebugStruct->DebugHUDElements.AttachedValue[Index]);
                        } break;
                        case HUDDATATYPE_UINT32:{ sprintf(CurrentLetter,"%u",*(uint32*)DebugStruct->DebugHUDElements.AttachedValue[Index]);
                        } break;
                        case HUDDATATYPE_UINT64:{ sprintf(CurrentLetter,"%llu",*(uint64*)DebugStruct->DebugHUDElements.AttachedValue[Index]);
                        } break;
                        case HUDDATATYPE_INT8:{ sprintf(CurrentLetter,"%i",*(int8*)DebugStruct->DebugHUDElements.AttachedValue[Index]);
                        } break;
                        case HUDDATATYPE_INT16:{ sprintf(CurrentLetter,"%i",*(int16*)DebugStruct->DebugHUDElements.AttachedValue[Index]);
                        } break;
                        case HUDDATATYPE_INT32:{ sprintf(CurrentLetter,"%i",*(int32*)DebugStruct->DebugHUDElements.AttachedValue[Index]);
                        } break;
                        case HUDDATATYPE_REAL32:{ sprintf(CurrentLetter,"%.9g",*(real32*)DebugStruct->DebugHUDElements.AttachedValue[Index]);
                        } break;
                        case HUDDATATYPE_REAL64:{ sprintf(CurrentLetter,"%.17g",*(real64*)DebugStruct->DebugHUDElements.AttachedValue[Index]);
                        } break;
                    }
                }
                else
                {
                    DebugStruct->DebugHUDElements.AttachedString[Index][DebugStruct->DebugHUDElements.NumOfChar[Index]] = 0;
                }
                
                //----------
                
                if(DebugStruct->DebugHUDElements.AttachedString[Index][0] != 0)
                {
                    char* CurrentLetter = &DebugStruct->DebugHUDElements.AttachedString[Index][0];
                    real32 TextToRectWidthRatio = DebugStruct->DebugHUDElements.Width[Index] / GetStringWidth(CurrentLetter);
                    real32 TextToRectHeightRatio = DebugStruct->DebugHUDElements.Height[Index] / 16;
                    v2 CharecterOrigin = V2(ScreenPosition) + (-HalfWidth + -HalfHeight);
                    
                    //----------
                    
                    while(*CurrentLetter != 0)
                    {
                        int32 CurrentCharacterWidth = GetCharacterWidth(CurrentLetter);
                        real32 FontWidth = CurrentCharacterWidth / 128.0f;
                        int32 Offset = *CurrentLetter - 32;
                        real32 TextureLayer;
                        if(*CurrentLetter < 96)
                        {
                            TextureLayer = TEXTURENAME_FONT1;
                        }
                        else
                        {
                            TextureLayer = TEXTURENAME_FONT2;
                            Offset -= 64;
                        }
                        int32 CellOffsetX = Offset % 8;
                        int32 CellOffsetY = Offset / 8;
                        real32 CellWidth = 16.0f / 128.0f;
                        real32 StartXTex = 0;
                        real32 StartYTex = 0.875;
                        real32 MinX = StartXTex + CellWidth * CellOffsetX;
                        real32 MinY = StartYTex - CellWidth * CellOffsetY;
                        
                        //----------
                        
                        v3real32 LowerLeft = {
                            (real32)( CharecterOrigin.x * ScreenWidthScaleFactor) - 1.0f,
                            (real32)( CharecterOrigin.y * ScreenHeightScaleFactor) - 1.0f,
                            (.99f) - (real32)(.01f * (ScreenPosition.z+.5))// +.5 because text goes over other stuff
                        };
                        v3real32 LowerRight = {
                            (real32)( CharecterOrigin.x + (CurrentCharacterWidth * TextToRectWidthRatio * ElementXBasis.x) ) * ScreenWidthScaleFactor - 1.0f,
                            (real32)( CharecterOrigin.y + (CurrentCharacterWidth * TextToRectWidthRatio * ElementXBasis.y) ) * ScreenHeightScaleFactor - 1.0f,
                            (.99f) - (real32)(.01f * (ScreenPosition.z+.5))
                        };
                        v3real32 TopRight = {
                            (real32)( CharecterOrigin.x + (CurrentCharacterWidth * TextToRectWidthRatio * ElementXBasis.x) + (ElementYBasis.x * Height) ) * ScreenWidthScaleFactor - 1.0f,
                            (real32)( CharecterOrigin.y + (CurrentCharacterWidth * TextToRectWidthRatio * ElementXBasis.y) + (ElementYBasis.y * Height) ) * ScreenHeightScaleFactor - 1.0f,
                            (.99f) - (real32)(.01f * (ScreenPosition.z+.5))
                        };
                        v3real32 TopLeft = {
                            (real32)( CharecterOrigin.x + (ElementYBasis.x * Height) ) * ScreenWidthScaleFactor - 1.0f,
                            (real32)( CharecterOrigin.y + (ElementYBasis.y * Height) ) * ScreenHeightScaleFactor - 1.0f,
                            (.99f) - (real32)(.01f * (ScreenPosition.z+.5))
                        };
                        
                        //---------- first triangle
                        
                        *Vertices = LowerLeft;
                        ++Vertices;
                        VerticeCount += 3;
                        *Vertices = {MinX,MinY,TextureLayer};
                        ++Vertices;
                        VerticeCount += 3;
                        *Vertices = LowerRight;
                        ++Vertices;
                        VerticeCount += 3;
                        *Vertices = {MinX + FontWidth,MinY,TextureLayer};
                        ++Vertices;
                        VerticeCount += 3;
                        *Vertices = TopLeft;
                        ++Vertices;
                        VerticeCount += 3;
                        *Vertices = {MinX,MinY + CellWidth,TextureLayer};
                        ++Vertices;
                        VerticeCount += 3;
                        
                        //---------- second triangle
                        
                        *Vertices = TopRight;
                        ++Vertices;
                        VerticeCount += 3;
                        *Vertices = {MinX + FontWidth,MinY + CellWidth,TextureLayer};
                        ++Vertices;
                        VerticeCount += 3;
                        *Vertices = TopLeft;
                        ++Vertices;
                        VerticeCount += 3;
                        *Vertices = {MinX,MinY + CellWidth,TextureLayer};
                        ++Vertices;
                        VerticeCount += 3;
                        *Vertices = LowerRight;
                        ++Vertices;
                        VerticeCount += 3;
                        *Vertices = {MinX + FontWidth,MinY,TextureLayer};
                        ++Vertices;
                        VerticeCount += 3;
                        
                        //----------
                        
                        CharecterOrigin.x += (CurrentCharacterWidth * TextToRectWidthRatio * ElementXBasis.x);
                        CharecterOrigin.y += (CurrentCharacterWidth * TextToRectWidthRatio * ElementXBasis.y);
                        ++CurrentLetter;
                    }
                }
                
                //------------------------------render string end
                
                if(DebugStruct->DebugHUDElements.HUDType[Index] != HUDTYPE_TEXT)
                {
                    real32 TextureLayer = DebugStruct->DebugHUDElements.HUDTextureLayer[Index];
                    if(DebugStruct->DebugHUDElements.IsActive[Index] == 0)
                    {
                        TextureLayer = TEXTURENAME_GRAY;
                    }
                    
                    //----------
                    
                    v3real32 LowerLeft = {
                        ( (real32)(Origin.x) * ScreenWidthScaleFactor) - 1.0f,
                        ( (real32)(Origin.y) * ScreenHeightScaleFactor) - 1.0f,
                        (.99f) - (real32)(.01f * (ScreenPosition.z))
                    };
                    v3real32 LowerRight = {
                        ( (real32)(MaxX.x) * ScreenWidthScaleFactor) - 1.0f,
                        ( (real32)(MaxX.y) * ScreenHeightScaleFactor) - 1.0f,
                        (.99f) - (real32)(.01f * (ScreenPosition.z))
                    };
                    v3real32 TopRight = {
                        ( (real32)(MaxXY.x) * ScreenWidthScaleFactor) - 1.0f,
                        ( (real32)(MaxXY.y) * ScreenHeightScaleFactor) - 1.0f,
                        (.99f) - (real32)(.01f * (ScreenPosition.z))
                    };
                    v3real32 TopLeft = {
                        ( (real32)(MaxY.x) * ScreenWidthScaleFactor) - 1.0f,
                        ( (real32)(MaxY.y) * ScreenHeightScaleFactor) - 1.0f,
                        (.99f) - (real32)(.01f * (ScreenPosition.z))
                    };
                    
                    //---------- first triangle
                    
                    *Vertices = LowerLeft;
                    ++Vertices;
                    VerticeCount += 3;
                    *Vertices = {0,0,TextureLayer};
                    ++Vertices;
                    VerticeCount += 3;
                    *Vertices = LowerRight;
                    ++Vertices;
                    VerticeCount += 3;
                    *Vertices = {1,0,TextureLayer};
                    ++Vertices;
                    VerticeCount += 3;
                    *Vertices = TopLeft;
                    ++Vertices;
                    VerticeCount += 3;
                    *Vertices = {0,1,TextureLayer};
                    ++Vertices;
                    VerticeCount += 3;
                    
                    //---------- second triangle
                    
                    *Vertices = TopRight;
                    ++Vertices;
                    VerticeCount += 3;
                    *Vertices = {1,1,TextureLayer};
                    ++Vertices;
                    VerticeCount += 3;
                    *Vertices = TopLeft;
                    ++Vertices;
                    VerticeCount += 3;
                    *Vertices = {0,1,TextureLayer};
                    ++Vertices;
                    VerticeCount += 3;
                    *Vertices = LowerRight;
                    ++Vertices;
                    VerticeCount += 3;
                    *Vertices = {1,0,TextureLayer};
                    ++Vertices;
                    VerticeCount += 3;
                }
            }
            NEXTHUDELEMENT:;
        }
    }
    GameState->HUDVerticeCount += VerticeCount;
    SetAllHUDVisibility(0,DebugStruct);
}