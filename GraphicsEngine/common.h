/******************************************************************************
Author:Rich Davison
Description: Some random variables and functions, for lack of a better place 
to put them.

-_-_-_-_-_-_-_,------,   
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""   

*//////////////////////////////////////////////////////////////////////////////

#pragma once

#define WEEK_2_CODE
#define USE_MD5MESH
#define WEEK_3_CODE

#define OUT_OF_RANGE -1

enum State_enum { PATROL, PURSUE, PURSUE_CHASE, PURSUE_FIND };




#define SHADERDIR	"../../Data/Shaders/"
#define MESHDIR		"../../Data/Meshes/"
#define TEXTUREDIR  "../../Data/Textures/"
#define SOUNDSDIR	"../../Data/Sounds/"

#define SAFE_DELETE(x) if(x) { delete x; x = NULL; }