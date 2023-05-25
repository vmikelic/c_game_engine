
inline uint32 NextRandomNumber(uint32* State)
{
    uint32 Result = *State;
    Result ^= Result << 13;
    Result ^= Result >> 17;
    Result ^= Result << 5;
    *State = Result;
    return(Result);
}

inline uint32 RandomChoice(uint32* State, uint32 ChoiceCount)
{
    uint32 Result = (NextRandomNumber(State) % ChoiceCount);
    return(Result);
}

inline real32 RandomUnilateral(uint32* State)
{
    real32 Divisor = 1.0f / (real32)UINT32Max;
    real32 Result = Divisor*(real32)NextRandomNumber(State);
    return(Result);
}

inline real32 RandomBilateral(uint32* State)
{
    real32 Result = 2.0f*RandomUnilateral(State) - 1.0f;
    return(Result);
}

inline real32 RandomRealBetween(uint32* State,real32 Min, real32 Max)
{
    real32 Result = Lerp(Min,RandomUnilateral(State),Max);
    return(Result);
}

inline int32 RandomIntBetween(uint32* State, int32 Min, int32 Max)
{
    int32 Result = Min + (int32)(NextRandomNumber(State)%( (Max + 1) - Min) );
    return(Result);
}