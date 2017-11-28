#-------------------------------------------------------
# BCC Developer 1.2.21
# Copyright (C) 2003 jun_miura@hi-ho.ne.jp
#-------------------------------------------------------
.autodepend
CC=bcc32
RC=brc32
CFLAG=-W  -3 -Od -w- -AT -pc -H- -k -b -v -y  -DDEBUG
OUTDIR=-nDebug
CINCS=
TARGET=Debug\action2017.exe
SRC1=D:\others\BCC\program\action2017\Scroll.cpp
OBJ1=Debug\Scroll.obj
SRC2=D:\others\BCC\program\action2017\KeyInputs.cpp
OBJ2=Debug\KeyInputs.obj
SRC3=D:\others\BCC\program\action2017\CheckHit.cpp
OBJ3=Debug\CheckHit.obj
SRC4=D:\others\BCC\program\action2017\Options.cpp
OBJ4=Debug\Options.obj
SRC5=D:\others\BCC\program\action2017\DataReader.cpp
OBJ5=Debug\DataReader.obj
SRC6=D:\others\BCC\program\action2017\Load.cpp
OBJ6=Debug\Load.obj

TARGET: $(TARGET)

$(TARGET): $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5) $(OBJ6)
    $(CC) $(CFLAG) -e$(TARGET) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5) $(OBJ6)

$(OBJ1): $(SRC1)
    $(CC) $(CFLAG) $(OUTDIR) $(CINCS) -c $(SRC1)

$(OBJ2): $(SRC2)
    $(CC) $(CFLAG) $(OUTDIR) $(CINCS) -c $(SRC2)

$(OBJ3): $(SRC3)
    $(CC) $(CFLAG) $(OUTDIR) $(CINCS) -c $(SRC3)

$(OBJ4): $(SRC4)
    $(CC) $(CFLAG) $(OUTDIR) $(CINCS) -c $(SRC4)

$(OBJ5): $(SRC5)
    $(CC) $(CFLAG) $(OUTDIR) $(CINCS) -c $(SRC5)

$(OBJ6): $(SRC6)
    $(CC) $(CFLAG) $(OUTDIR) $(CINCS) -c $(SRC6)
