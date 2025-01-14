#version 400 

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cameraPos;

out vec3 FragPos;  
out vec3 gCameraWorldPos;


void main()
{
    
    vec4 vPos4 = model * vec4(aPos , 1.0);
        
    //vPos4.x += cameraPos.x;
    //vPos4.z += cameraPos.z;
    vPos4.y -= 2.0; 

    gl_Position = projection * view *  vPos4;
    FragPos = aPos;
    gCameraWorldPos = cameraPos;
}