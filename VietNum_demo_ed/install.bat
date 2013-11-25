@echo off
@cls
@color 17
@set prompt=$
@echo on
@md "C:\Program Files\SGA Source"
@xcopy *.* "C:\Program Files\SGA Source" /i /s
@echo The software have been installed to C:\Program Files\SGA Source
@echo Thank you for using product from SGA!
@pause