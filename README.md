# Bunny
C++, OpenGL, Glew: recover legacy computer graphics project. The project was originally written in Visual C++. Recently, I found it is not difficult to port to Ubuntu/Eclipse environment, so I take this weekend to do it.

History
----
The setup was a Windows XP, Visual C++ environment in around 2010.
Due to well known reason, such setting is very difficult to keep a sustainable product line. 
In early 2014, I bought/DIY a AMD box with a HD6500 card. I also install the proprietory graphical card driver. I found my project Friends Torus can not run in such environment. So we know there is new version of OpenGL et al.
So I started the project GlChemstry. In GlChemstry, my first thinking to find/reuse the famous Gear example in Jogl. Unfortunately, there is not an exact GL4 implementation. So task changed to write a GL4 Gear.

Around the time of 2009 and 2010, I spent much effort on studying GTS, GNU triangulated surface for short. The goal was to achieve smooth shading. There was the problem to compute vertices normals. One triangle's normal is easy to compute. But a vertex may belong to multiple triangles, we can average the normals, or further average with weighing in the areas of triangles. But the result achieved is still coarse. Further research brought in Phong shading. This is the mission of GLEW, programming with shaders.

So Bunny at the very begginning was a mock of GTS, plus smooth shading, plus GLEW Phone shading. After these achieved, I implemented depth peeling transparency in this project.

In 2015, I ported this project to Ubuntu/Linux environment.
