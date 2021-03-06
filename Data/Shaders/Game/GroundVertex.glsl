
/*****************************************************************************
:;-"""-::::::::::::::::::::::::::::::::::::::::::::::::.::..:... ..  .
(      .)::::::::::::::::::::::::::::::::::::::::::::.::..:... ..  .
        )-:::::::::::::::::::::::::::::::::::::::::::::::.::..:... .. .
      -'   )-"-:::::::::::::::::::::::::::::::::::::::.::..:... ..  .
 ___________)______________          _____
|                         \          \ U \__      _______
|        Yesheng Su        \__________\   \/_______\___\_____________
|        10/02/2018        /          < /_/   ..................... ^`-._
|_________________________/            `-----------,----,--------------'
                      )                          _/____/_
-.                .    ):::::::::::::::::::::::::::::.::..:... ..  .
  )--.__..--"-.__,'---':::::::::::::::::::::::::::::::::.::..:... ..  .
-':::::::::::::::::::::::::::::::::::::::::::::.::..:... ..  .
:::::::::::::::::::::::::::::::::::::::::::::::::.::..:... ..  .
															
*****************************************************************************/
#version 330 core

uniform mat4 uProjViewMtx;
uniform mat4 uModelMtx;
uniform vec2 uGroundSize;

layout (location = 0) in  vec3 position;
layout (location = 2) in  vec2 texCoord;
layout (location = 3) in  vec3 normal;

out Vertex	{
	smooth vec3 	 worldPos;
	smooth vec2 	 texCoord;
	smooth vec3 	 normal;
	smooth vec2		 pathTexCoord;
} OUT;

void main(void)	{
	vec4 wp 		= uModelMtx * vec4(position, 1.0);
	gl_Position		= uProjViewMtx * wp;
	
	OUT.worldPos 	= wp.xyz; //Assumes no w component madness
	OUT.texCoord	= texCoord;
	
	//This is a much quicker way to calculate the rotated normal value, however it only works
	//  when the model matrix has the same scaling on all axis. If this is not the case, use the other method below.
	//OUT.normal		= mat3(uModelMtx) * normal;
	
	// Use this if your objects have different scaling values along the x,y,z axis
	OUT.normal		  = transpose(inverse(mat3(uModelMtx))) * normalize(normal);

	float uvx = mix(0.0f, 1.0f, (uGroundSize.x - wp.x) / (uGroundSize.x * 2));
	float uvy = mix(0.0f, 1.0f, (uGroundSize.y + wp.z) / (uGroundSize.y * 2));
	OUT.pathTexCoord = vec2(uvx, uvy);
}