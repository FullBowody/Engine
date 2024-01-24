@echo Creating Engine directories ...
@rmdir /s /q .\Engine
@mkdir .\Engine
@mkdir .\Engine\lib
@mkdir .\Engine\include
@mkdir .\Engine\bin

@echo Copying lib files to Engine directory ...
@copy .\src\*.hpp .\Engine\include\
@copy .\src\EngineLoader.cpp .\Engine\include\
@copy .\build\Debug\*.lib .\Engine\lib\
@copy .\build\Debug\*.dll .\Engine\bin\

@echo Done.
