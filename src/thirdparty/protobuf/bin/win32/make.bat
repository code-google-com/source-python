@SET GAME=%1
@IF "%1"=="" (
@	SET /P GAME=Enter the game name: 
)

@SET SRC_DIR=F:\sourcepython\src
@SET CORE_DIR=%SRC_DIR%\core
@SET MODULE_DIR=%CORE_DIR%\modules
@SET PROTOBUF_DIR=%SRC_DIR%\thirdparty\protobuf
@SET PROTOBUF_SRC_DIR=%PROTOBUF_DIR%\protobuf-2.3.0\src
@SET PROTOFILE_DIR=%PROTOBUF_SRC_DIR%

@echo -----------------------------------------------------
@echo GAME:			%GAME%
@echo SRC_DIR:		%SRC_DIR%
@echo CORE_DIR:		%CORE_DIR%
@echo MODULE_DIR:	%MODULE_DIR%
@echo PROTOBUF_DIR		%PROTOBUF_DIR%
@echo PROTOBUF_SRC_DIR	%PROTOBUF_SRC_DIR%
@echo PROTOFILE_DIR 		%PROTOFILE_DIR%
@echo -----------------------------------------------------

@echo Creating Directories
@if not exist %MODULE_DIR%\usermessages mkdir %MODULE_DIR%\usermessages
@if not exist %MODULE_DIR%\usermessages\%GAME% mkdir %MODULE_DIR%\usermessages\%GAME%

@echo Running boost generation code on %GAME%\usermessages.proto...
@.\protoc.exe --proto_path=%PROTOBUF_SRC_DIR% --bplbindings_out=%MODULE_DIR%\usermessages %PROTOFILE_DIR%\%GAME%\usermessages.proto

@echo Renaming file as the boost python exporter doesn't name them correctly
@xcopy %MODULE_DIR%\usermessages\_%GAME%\usermessages.cpp %MODULE_DIR%\usermessages\%GAME%\bindings.cpp /y /i /v
@rd %MODULE_DIR%\usermessages\_%GAME% /S /Q


pause
