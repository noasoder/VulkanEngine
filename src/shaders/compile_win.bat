@REM C:/VulkanSDK/1.2.182.0/Bin/glslc.exe shader.vert -o vert.spv
@REM C:/VulkanSDK/1.2.182.0/Bin/glslc.exe shader.frag -o frag.spv

@echo off

@FOR %%i IN ( *.vert ) DO (
    C:/VulkanSDK/1.2.182.0/Bin/glslc.exe %%i -o %%~ni_vert.spv
	@echo compiled %%i
)
@FOR %%i IN ( *.frag ) DO (
    C:/VulkanSDK/1.2.182.0/Bin/glslc.exe %%i -o %%~ni_frag.spv
	@echo compiled %%i
)
@set dir=../../bin/Assets/Shaders

@FOR %%i IN ( *.spv ) DO (
    move "%%i" "%dir%"
	@echo moved %%i to %dir%
)

pause