//------------------------------------------------------------------------------ general real32 math operations

inline real32
Lerp(real32 A, real32 t, real32 B)
{
    real32 Result = (1.0f - t)*A + t*B;
    return(Result);
}
inline real32
Square(real32 A)
{
    return(A*A);
}
inline real32
AbsoluteValue(real32 A)
{
    return(fabsf(A));
}
inline real64
AbsoluteValue(real64 A)
{
    return(fabs(A));
}
inline real32
SquareRoot(real32 A)
{
    return(sqrt(A));
}
inline real32
Sine(real32 A)
{
    real32 Result = sinf(A);
    if(Result > -REAL32Epsilon &&
       Result < REAL32Epsilon)
    {
        Result = 0;
    }
    return(Result);
}
inline real32
Cosine(real32 A)
{
    real32 Result = cosf(A);
    if(Result > -REAL32Epsilon &&
       Result < REAL32Epsilon)
    {
        Result = 0;
    }
    return(Result);
}
inline real32
Tangent(real32 A)
{  
    real32 Result = tanf(A);
    if(Result > -REAL32Epsilon &&
       Result < REAL32Epsilon)
    {
        Result = 0;
    }
    return(Result);
}
inline real32
ArcSine(real32 A)
{  
    real32 Result = asinf(A);
    if(Result > -REAL32Epsilon &&
       Result < REAL32Epsilon)
    {
        Result = 0;
    }
    return(Result);
}
inline real32
ArcCosine(real32 A)
{
    real32 Result = acosf(A);
    if(Result > -REAL32Epsilon &&
       Result < REAL32Epsilon)
    {
        Result = 0;
    }
    return(Result);
}

//------------------------------Utilities

inline real64
MetersToPixels(real64 Meters)
{
    return (Meters*100.0);
}
inline real32
MetersToPixels(real32 Meters)
{
    return (Meters*100.0f);
}
inline real64
HammerUnits(real64 Centimeters)
{
    return (Centimeters*1.904);
}
inline int32
GetCharacterWidth(char* CurrentLetter)
{
    int32 CharacterWidth[] = 
    {
        10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
        10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,4,5,
        6,8,8,12,10,3,5,5,5,8,4,5,4,4,8,8,8,
        8,8,8,8,8,8,8,5,5,8,8,8,8,13,10,10,10,
        10,9,8,11,10,4,8,10,8,11,10,11,9,11,10,9,8,
        10,9,13,9,9,8,5,4,5,8,8,5,8,8,8,8,8,
        5,8,8,4,4,8,4,12,8,8,8,8,5,8,5,8,8,
        11,8,8,7,5,4,5,8,10,8,10,4,8,7,14,8,8,
        5,14,9,5,14,10,8,10,10,4,4,7,7,5,8,14,5,
        14,8,5,13,10,7,9,4,5,8,8,8,8,4,8,5,10,
        5,8,8,5,10,8,5,7,5,5,5,8,8,5,5,5,5,
        8,11,11,11,8,10,10,10,10,10,10,14,10,9,9,9,9,
        4,4,4,4,10,10,11,11,11,11,11,8,11,10,10,10,10,
        9,9,8,8,8,8,8,8,8,12,8,8,8,8,8,4,4,
        4,4,8,8,8,8,8,8,8,7,8,8,8,8,8,8,8,8
    };
    return(CharacterWidth[*CurrentLetter]);
}
inline int32
GetStringWidth(char* Name)
{
    int32 StringLength = 0;
    char* CurrentLetter = &Name[0];
    if(CurrentLetter != 0)
    {
        while(*CurrentLetter != 0)
        {
            StringLength += GetCharacterWidth(CurrentLetter);
            ++CurrentLetter;
        }
    }
    return(StringLength);
}
inline bool
IsInRange(real64 Value, real64 Range1,real64 Range2) 
{
    if(!((Value < Range1) && (Value < Range2)))
    {
        if(!((Value > Range1) && (Value > Range2)))
        {
            return(true);
        }
    }
    return(false);
}

//------------------------------------------------------------------------------ general 64 bit math operations

inline real64
Lerp(real64 A, real64 t, real64 B)
{
    real64 Result = (1.0 - t)*A + t*B;
    return(Result);
}
inline real64
Square(real64 A)
{
    return(A*A);
}
inline real64
SquareRoot(real64 A)
{
    return(sqrt(A));
}
inline real64
Sine(real64 A)
{
    real64 Result = sin(A);
    if(Result > -REAL64Epsilon &&
       Result < REAL64Epsilon)
    {
        Result = 0;
    }
    return(Result);
}
inline real64
Cosine(real64 A)
{
    real64 Result = cos(A);
    if(Result > -REAL64Epsilon &&
       Result < REAL64Epsilon)
    {
        Result = 0;
    }
    return(Result);
}
inline real64
Tangent(real64 A)
{  
    real64 Result = tan(A);
    if(Result > -REAL64Epsilon &&
       Result < REAL64Epsilon)
    {
        Result = 0;
    }
    return(Result);
}
inline real64
ArcSine(real64 A)
{  
    real64 Result = asin(A);
    if(Result > -REAL64Epsilon &&
       Result < REAL64Epsilon)
    {
        Result = 0;
    }
    return(Result);
}
inline real64
ArcCosine(real64 A)
{
    real64 Result = acos(A);
    if(Result > -REAL64Epsilon &&
       Result < REAL64Epsilon)
    {
        Result = 0;
    }
    return(Result);
}

//-------------------------------------- 3d real vector operations

struct v3real32 // use real32 for opengl stuff
{
    real32 x, y, z;
};
inline v3real32
Normalize(v3real32 &A)
{
    real32 InverseLength = SquareRoot(A.x*A.x + A.y*A.y + A.z*A.z);
    if(InverseLength > 0)
    {
        InverseLength = 1/InverseLength;
        A.x = A.x*InverseLength;
        A.y = A.y*InverseLength;
        A.z = A.z*InverseLength;
    }
    else
    {
        A = {};
    }
    return(A);
}
inline v3real32
Cross(v3real32 A, v3real32 B)
{
    v3real32 Result;
    Result.x = (A.y * B.z) - (A.z * B.y);
    Result.y = (A.z * B.x) - (A.x * B.z);
    Result.z = (A.x * B.y) - (A.y * B.x);
    return Result;
}

//----------real64

struct v3
{
    real64 x, y, z;
};
inline v3
operator*(real64 A,v3 B)
{
    v3 Result;
    Result.x = A * B.x;
    Result.y = A * B.y;
    Result.z = A * B.z;
    return(Result);
}
inline v3
operator*(v3 B,real64 A)
{  
    v3 Result;
    Result.x = A * B.x;
    Result.y = A * B.y;
    Result.z = A * B.z;
    return(Result);
}
inline v3 &
operator*=(v3 &A, real64 B)
{
    A = B * A;
    return(A);
}
inline v3
operator/(real64 A,v3 B)
{
    v3 Result;
    Result.x = B.x / A;
    Result.y = B.y / A;
    Result.z = B.z / A;
    return(Result);
}
inline v3
operator/(v3 B,real64 A)
{  
    v3 Result;
    Result.x = B.x / A;
    Result.y = B.y / A;
    Result.z = B.z / A;
    return(Result);
}
inline v3 &
operator/=(v3 &A, real64 B)
{
    A = A / B;
    return(A);
}
inline v3
operator+(v3 A, real64 B)
{
    v3 Result;
    Result.x = A.x + B;
    Result.y = A.y + B;
    Result.z = A.z + B;
    return(Result);
}
inline v3
operator+(v3 A, v3 B)
{
    v3 Result;
    Result.x = A.x + B.x;
    Result.y = A.y + B.y;
    Result.z = A.z + B.z;
    return(Result);
}
inline v3 &
operator+=(v3 &A, v3 B)
{
    A = A + B;
    return(A);
}
inline v3
operator-(v3 A, real64 B)
{
    v3 Result;
    Result.x = A.x - B;
    Result.y = A.y - B;
    Result.z = A.z - B;
    return(Result);
}
inline v3
operator-(v3 A, v3 B)
{
    v3 Result;
    Result.x = A.x - B.x;
    Result.y = A.y - B.y;
    Result.z = A.z - B.z;
    return(Result);
}
inline v3 &
operator-=(v3 &A, real64 B)
{
    A = A - B;
    return(A);
}
inline v3 &
operator-=(v3 &A, v3 B)
{
    A = A - B;
    return(A);
}
inline v3
operator-(v3 A)
{
    v3 Result;
    Result.x = -A.x;
    Result.y = -A.y;
    Result.z = -A.z;
    return(Result);  
}
inline real64
Inner(v3 A, v3 B)
{
    return( (A.x*B.x) + (A.y*B.y) + (A.z*B.z) );
}
inline v3 
Cross(v3 A, v3 B)
{
    v3 Result;
    Result.x = (A.y * B.z) - (A.z * B.y);
    Result.y = (A.z * B.x) - (A.x * B.z);
    Result.z = (A.x * B.y) - (A.y * B.x);
    return Result;
}
inline real64
Length(v3 A)
{
    return( SquareRoot( ( Square(A.x) + Square(A.y) + Square(A.z) ) ) );
}
inline v3
Normalize(v3 &A)
{
    real64 InverseLength = SquareRoot(A.x*A.x + A.y*A.y + A.z*A.z);
    if(InverseLength > 0)
    {
        InverseLength = 1/InverseLength;
        A.x = A.x*InverseLength;
        A.y = A.y*InverseLength;
        A.z = A.z*InverseLength;
    }
    else
    {
        A = {};
    }
    return(A);
}
inline v3
Perp(v3 A)
{
    v3 Result;
    Result.x = -A.y;
    Result.y = A.x;
    Result.z = A.z;
    return(Result);
}
inline v3
Lerp(v3 A, real64 t, v3 B)
{
    v3 Result = (1.0 - t)*A + t*B;
    return(Result);
}

//----------AABB

struct AABB
{
    real64 MaxX;
    real64 MaxY;
    real64 MaxZ;
    v3 Origin;  
};

//-------------------------------------- 3d integer vector operations

struct p3
{
    int32 x,y,z;
};
inline p3
operator*(int32 A,p3 B)
{
    p3 Result;
    Result.x = A * B.x;
    Result.y = A * B.y;
    Result.z = A * B.z;
    return(Result);
}
inline p3
operator*(p3 B,int32 A)
{  
    p3 Result;
    Result.x = A * B.x;
    Result.y = A * B.y;
    Result.z = A * B.z;
    return(Result);
}
inline p3 &
operator*=(p3 &A, int32 B)
{
    A = B * A;
    return(A);
}
inline p3
operator+(p3 A, p3 B)
{
    p3 Result;
    Result.x = A.x + B.x;
    Result.y = A.y + B.y;
    Result.z = A.z + B.z;
    return(Result);
}
inline p3 &
operator+=(p3 &A, p3 B)
{
    A = A + B;
    return(A);
}
inline p3
operator-(p3 A, p3 B)
{
    p3 Result;
    Result.x = A.x - B.x;
    Result.y = A.y - B.y;
    Result.z = A.z - B.z;
    return(Result);
}
inline p3 &
operator-=(p3 &A, p3 B)
{
    A = A - B;
    return(A);
}
inline p3
operator-(p3 A)
{
    p3 Result;
    Result.x = -A.x;
    Result.y = -A.y;
    Result.z = -A.z;
    return(Result);  
}

//--------------------------------------v3 to p3 vice versa

inline p3
v3top3(v3 A)
{
    p3 Result;
    Result.x = (int32)A.x;
    Result.y = (int32)A.y;
    Result.z = (int32)A.z;
    return(Result);
}
inline v3
p3tov3(p3 A)
{
    v3 Result;
    Result.x = (real64)A.x;
    Result.y = (real64)A.y;
    Result.z = (real64)A.z;
    return(Result);
}

//-------------------------------------- 2d real vector operations

struct v2
{
    real64 x, y;
};
inline v2
operator*(real64 A,v2 B)
{
    v2 Result;
    Result.x = A * B.x;
    Result.y = A * B.y;
    return(Result);
}
inline v2
operator*(v2 B,real64 A)
{  
    v2 Result;
    Result.x = A * B.x;
    Result.y = A * B.y;
    return(Result);
}
inline v2 &
operator*=(v2 &A, real64 B)
{
    A = B * A;
    return(A);
}
inline v2
operator/(real64 A,v2 B)
{
    v2 Result;
    Result.x = B.x / A;
    Result.y = B.y / A;
    return(Result);
}
inline v2
operator/(v2 B,real64 A)
{  
    v2 Result;
    Result.x = B.x / A;
    Result.y = B.y / A;
    return(Result);
}
inline v2 &
operator/=(v2 &A, real64 B)
{
    A = A / B;
    return(A);
}
inline v2
operator+(v2 A, v2 B)
{
    v2 Result;
    Result.x = A.x + B.x;
    Result.y = A.y + B.y;
    return(Result);
}
inline v2 &
operator+=(v2 &A, v2 B)
{
    A = A + B;
    return(A);
}
inline v2
operator-(v2 A, v2 B)
{
    v2 Result;
    Result.x = A.x - B.x;
    Result.y = A.y - B.y;
    return(Result);
}
inline v2 &
operator-=(v2 &A, v2 B)
{
    A = A - B;
    return(A);
}
inline v2
operator-(v2 A)
{
    v2 Result;
    Result.x = -A.x;
    Result.y = -A.y;
    return(Result);  
}
inline real64
Inner(v2 A, v2 B)
{
    return( (A.x*B.x) + (A.y*B.y) );
}
inline real64
Length(v2 A)
{
    return( SquareRoot( (Square(A.x) + Square(A.y)) ) );
}
inline v2
Normalize(v2 &A)
{
    real64 InverseLength = SquareRoot(A.x*A.x + A.y*A.y);
    if(InverseLength > 0)
    {
        InverseLength = 1/InverseLength;
        A.x = A.x*InverseLength;
        A.y = A.y*InverseLength;
    }
    else
    {
        A = {};
    }
    return(A);
}
inline v2
Perp(v2 A)
{
    v2 Result;
    Result.x = -A.y;
    Result.y = A.x;
    return(Result);
}
inline v2
Lerp(v2 A, real64 t, v2 B)
{
    v2 Result = (1.0 - t)*A + t*B;
    return(Result);
}

//-------------------------------------- 2d integer vector operations

struct p2
{
    int32 x,y;
};
inline p2
operator*(int32 A,p2 B)
{
    p2 Result;
    Result.x = A * B.x;
    Result.y = A * B.y;
    return(Result);
}
inline p2
operator*(p2 B,int32 A)
{  
    p2 Result;
    Result.x = A * B.x;
    Result.y = A * B.y;
    return(Result);
}
inline p2 &
operator*=(p2 &A, int32 B)
{
    A = B * A;
    return(A);
}
inline p2
operator/(p2 B,int32 A)
{  
    p2 Result;
    Result.x = B.x / A;
    Result.y = B.y / A;
    return(Result);
}
inline p2 &
operator/=(p2 &A, int32 B)
{
    A = A / B;
    return(A);
}
inline p2
operator+(p2 A, p2 B)
{
    p2 Result;
    Result.x = A.x + B.x;
    Result.y = A.y + B.y;
    return(Result);
}
inline p2 &
operator+=(p2 &A, p2 B)
{
    A = A + B;
    return(A);
}
inline p2
operator-(p2 A, p2 B)
{
    p2 Result;
    Result.x = A.x - B.x;
    Result.y = A.y - B.y;
    return(Result);
}
inline p2 &
operator-=(p2 &A, p2 B)
{
    A = A - B;
    return(A);
}
inline p2
operator-(p2 A)
{
    p2 Result;
    Result.x = -A.x;
    Result.y = -A.y;
    return(Result);  
}

//--------------------------------------v2 to p2 vice versa

inline p2
v2top2(v2 A)
{
    p2 Result;
    Result.x = (int32)A.x;
    Result.y = (int32)A.y;
    return(Result);
}
inline v2
p2tov2(p2 A)
{
    v2 Result;
    Result.x = (real64)A.x;
    Result.y = (real64)A.y;
    return(Result);
}

//------------------------------ vector conversion

inline v2
V2(v3 A)
{
    v2 Result;
    Result.x = A.x;
    Result.y = A.y;
    return(Result);
}
inline v3
V3(v2 A)
{
    v3 Result;
    Result.x = A.x;
    Result.y = A.y;
    Result.z = 0;
    return(Result);
}
