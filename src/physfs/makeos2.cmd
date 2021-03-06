@echo off
rem this is a simple batch file to build PhysicsFS on OS/2. You need to have
rem  the EMX development tools installed for this to work.
rem
rem This script (and, indeed, our OS/2 support) could use some tweaking.
rem  Patches go to icculus@clutteredmind.org ...

set PHYSFSLANG=PHYSFS_LANG_ENGLISH
set DEBUGFLAGS=-D_NDEBUG -O2 -s
set CFLAGS=%DEBUGFLAGS% -Wall -Werror -Zomf -Zmt -Zmtd -I. -Izlib114 -c -D__ST_MT_ERRNO__ -DOS2 -DPHYSFS_SUPPORTS_ZIP -DPHYSFS_SUPPORTS_GRP -DPHYSFS_SUPPORTS_QPAK -DPHYSFS_SUPPORTS_HOG -DPHYSFS_SUPPORTS_MVL -DPHYSFS_LANG=%PHYSFSLANG% -DHAVE_ASSERT_H=1

@echo on
mkdir bin
erase /N bin\*.*

@echo ;don't edit this directly! It is rewritten by makeos2.cmd! > bin\test_physfs.def
@echo NAME TESTPHYSFS WINDOWCOMPAT >> bin\test_physfs.def
@echo DESCRIPTION 'PhysicsFS: http://icculus.org/physfs/' >> bin\test_physfs.def
@echo STACKSIZE 0x10000 >> bin\test_physfs.def
@echo BASE=0x10000 >> bin\test_physfs.def
@echo PROTMODE >> bin\test_physfs.def

@echo ;don't edit this directly! It is rewritten by makeos2.cmd! > bin\physfs.def
@echo LIBRARY 'physfs' INITINSTANCE TERMINSTANCE >> bin\physfs.def
@echo STACKSIZE 0x10000 >> bin\physfs.def
@echo CODE LOADONCALL >> bin\physfs.def
@echo DATA LOADONCALL NONSHARED MULTIPLE >> bin\physfs.def
@echo DESCRIPTION 'PhysicsFS: http://icculus.org/physfs/' >> bin\physfs.def
@echo EXPORTS >> bin\physfs.def
@echo  "PHYSFS_getLinkedVersion" >> bin\physfs.def
@echo  "PHYSFS_init" >> bin\physfs.def
@echo  "PHYSFS_deinit" >> bin\physfs.def
@echo  "PHYSFS_supportedArchiveTypes" >> bin\physfs.def
@echo  "PHYSFS_freeList" >> bin\physfs.def
@echo  "PHYSFS_getLastError" >> bin\physfs.def
@echo  "PHYSFS_getDirSeparator" >> bin\physfs.def
@echo  "PHYSFS_permitSymbolicLinks" >> bin\physfs.def
@echo  "PHYSFS_getCdRomDirs" >> bin\physfs.def
@echo  "PHYSFS_getBaseDir" >> bin\physfs.def
@echo  "PHYSFS_getUserDir" >> bin\physfs.def
@echo  "PHYSFS_getWriteDir" >> bin\physfs.def
@echo  "PHYSFS_setWriteDir" >> bin\physfs.def
@echo  "PHYSFS_addToSearchPath" >> bin\physfs.def
@echo  "PHYSFS_removeFromSearchPath" >> bin\physfs.def
@echo  "PHYSFS_getSearchPath" >> bin\physfs.def
@echo  "PHYSFS_setSaneConfig" >> bin\physfs.def
@echo  "PHYSFS_mkdir" >> bin\physfs.def
@echo  "PHYSFS_delete" >> bin\physfs.def
@echo  "PHYSFS_getRealDir" >> bin\physfs.def
@echo  "PHYSFS_enumerateFiles" >> bin\physfs.def
@echo  "PHYSFS_exists" >> bin\physfs.def
@echo  "PHYSFS_isDirectory" >> bin\physfs.def
@echo  "PHYSFS_isSymbolicLink" >> bin\physfs.def
@echo  "PHYSFS_openWrite" >> bin\physfs.def
@echo  "PHYSFS_openAppend" >> bin\physfs.def
@echo  "PHYSFS_openRead" >> bin\physfs.def
@echo  "PHYSFS_close" >> bin\physfs.def
@echo  "PHYSFS_read" >> bin\physfs.def
@echo  "PHYSFS_write" >> bin\physfs.def
@echo  "PHYSFS_eof" >> bin\physfs.def
@echo  "PHYSFS_tell" >> bin\physfs.def
@echo  "PHYSFS_seek" >> bin\physfs.def
@echo  "PHYSFS_fileLength" >> bin\physfs.def
@echo  "PHYSFS_swapSLE16" >> bin\physfs.def
@echo  "PHYSFS_swapULE16" >> bin\physfs.def
@echo  "PHYSFS_swapSLE32" >> bin\physfs.def
@echo  "PHYSFS_swapULE32" >> bin\physfs.def
@echo  "PHYSFS_swapSLE64" >> bin\physfs.def
@echo  "PHYSFS_swapULE64" >> bin\physfs.def
@echo  "PHYSFS_swapSBE16" >> bin\physfs.def
@echo  "PHYSFS_swapUBE16" >> bin\physfs.def
@echo  "PHYSFS_swapSBE32" >> bin\physfs.def
@echo  "PHYSFS_swapUBE32" >> bin\physfs.def
@echo  "PHYSFS_swapSBE64" >> bin\physfs.def
@echo  "PHYSFS_swapUBE64" >> bin\physfs.def
@echo  "PHYSFS_getLastModTime" >> bin\physfs.def
@echo  "PHYSFS_readSLE16" >> bin\physfs.def
@echo  "PHYSFS_readULE16" >> bin\physfs.def
@echo  "PHYSFS_readSLE32" >> bin\physfs.def
@echo  "PHYSFS_readULE32" >> bin\physfs.def
@echo  "PHYSFS_readSLE64" >> bin\physfs.def
@echo  "PHYSFS_readULE64" >> bin\physfs.def
@echo  "PHYSFS_readSBE16" >> bin\physfs.def
@echo  "PHYSFS_readUBE16" >> bin\physfs.def
@echo  "PHYSFS_readSBE32" >> bin\physfs.def
@echo  "PHYSFS_readUBE32" >> bin\physfs.def
@echo  "PHYSFS_readSBE64" >> bin\physfs.def
@echo  "PHYSFS_readUBE64" >> bin\physfs.def
@echo  "PHYSFS_writeSLE16" >> bin\physfs.def
@echo  "PHYSFS_writeULE16" >> bin\physfs.def
@echo  "PHYSFS_writeSLE32" >> bin\physfs.def
@echo  "PHYSFS_writeULE32" >> bin\physfs.def
@echo  "PHYSFS_writeSLE64" >> bin\physfs.def
@echo  "PHYSFS_writeULE64" >> bin\physfs.def
@echo  "PHYSFS_writeSBE16" >> bin\physfs.def
@echo  "PHYSFS_writeUBE16" >> bin\physfs.def
@echo  "PHYSFS_writeSBE32" >> bin\physfs.def
@echo  "PHYSFS_writeUBE32" >> bin\physfs.def
@echo  "PHYSFS_writeSBE64" >> bin\physfs.def
@echo  "PHYSFS_writeUBE64" >> bin\physfs.def
@echo  "PHYSFS_setBuffer" >> bin\physfs.def
@echo  "PHYSFS_flush" >> bin\physfs.def

emximp -o bin/physfs.lib bin/physfs.def

gcc %CFLAGS% -o bin/physfs.obj physfs.c
gcc %CFLAGS% -o bin/physfs_byteorder.obj physfs_byteorder.c
gcc %CFLAGS% -o bin/os2.obj platform/os2.c
gcc %CFLAGS% -o bin/dir.obj archivers/dir.c
gcc %CFLAGS% -o bin/grp.obj archivers/grp.c
gcc %CFLAGS% -o bin/zip.obj archivers/zip.c
gcc %CFLAGS% -o bin/qpak.obj archivers/qpak.c
gcc %CFLAGS% -o bin/hog.obj archivers/hog.c
gcc %CFLAGS% -o bin/mvl.obj archivers/mvl.c

gcc %CFLAGS% -o bin/adler32.obj zlib114/adler32.c
gcc %CFLAGS% -o bin/compress.obj zlib114/compress.c
gcc %CFLAGS% -o bin/crc32.obj zlib114/crc32.c
gcc %CFLAGS% -o bin/deflate.obj zlib114/deflate.c
gcc %CFLAGS% -o bin/infblock.obj zlib114/infblock.c
gcc %CFLAGS% -o bin/infcodes.obj zlib114/infcodes.c
gcc %CFLAGS% -o bin/inffast.obj zlib114/inffast.c
gcc %CFLAGS% -o bin/inflate.obj zlib114/inflate.c
gcc %CFLAGS% -o bin/inftrees.obj zlib114/inftrees.c
gcc %CFLAGS% -o bin/infutil.obj zlib114/infutil.c
gcc %CFLAGS% -o bin/trees.obj zlib114/trees.c
gcc %CFLAGS% -o bin/uncompr.obj zlib114/uncompr.c 
gcc %CFLAGS% -o bin/zutil.obj zlib114/zutil.c

gcc %DEBUGFLAGS% -Zdll -Zcrtdll -Zomf -Zmt -Zmtd -o bin/physfs.dll bin/*.obj bin/physfs.def

gcc %CFLAGS% -o bin/test_physfs.obj test/test_physfs.c
gcc %DEBUGFLAGS% -Zomf -Zcrtdll -Zmt -Zmtd -o bin/test_physfs.exe bin/test_physfs.obj bin/physfs.lib bin/test_physfs.def

