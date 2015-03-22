varying vec3 N;varying vec3 v;
void main(void)  
{     
   v = vec3(gl_ModelViewMatrix * gl_Vertex);       
   N = normalize(gl_NormalMatrix * gl_Normal);

   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;  
// Note gl_Vertex is the same as in main program glvertex*()
//   gl_Position = gl_ModelViewProjectionMatrix * gp4;  
//   vec3 gp3 = gl_Vertex.xyz + vec3( 2.5,0,0);
//   vec4 gp4 = vec4(gp3.x,gp3.y,gp3.z,1);

}

