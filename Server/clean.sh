#Script to remove trash bevor commiting
FILE=Makefile
if test -f "$FILE"; then
    rm Makefile
fi

FILE=cmake_install.cmake
if test -f "$FILE"; then
    rm cmake_install.cmake
fi

FILE=CmakeFiles
if test -f "$FILE"; then
    rm -rf CmakeFiles
fi

FILE=_deps
if test -f "$FILE"; then
    rm -rf _deps
fi

FILE=CmakeCache.txt
if test -f "$FILE"; then
    rm CmakeCache.txt
fi

FILE=CPackConfig.cmake
if test -f "$FILE"; then
    rm CPackConfig.cmake
fi

FILE=CPackSourceConfig.cmake
if test -f "$FILE"; then
    rm CPackSourceConfig.cmake
fi

FILE=r-type_server
if test -f "$FILE"; then
    rm r-type_server
fi
