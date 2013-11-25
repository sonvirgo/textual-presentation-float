@echo off
@cls
@color 17
@set prompt=$
@echo on
@c:
@cd "C:\Program Files\SGA Source"
@del "C:\Program Files\SGA Source\*.*" /F /S /Q
@cd c:\
@rmdir "C:\Program Files\SGA Source" /s /q
@echo The software have been completely uninstalled 
@echo Thank you for using product from SGA!
@pause