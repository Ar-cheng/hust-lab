rem 装好masm32,修改默认路径
d:\masm32\bin\ml  /c  /coff  /I"d:\masm32\include" demo.asm
d:\masm32\bin\rc  demo.rc
d:\masm32\bin\link /subsystem:windows  /libpath"d:\masm32\lib" demo.obj demo.res