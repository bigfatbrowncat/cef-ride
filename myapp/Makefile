UNAME := $(shell uname)

ifndef ARCH
  ARCH := $(shell uname -m)
endif

ifeq ($(UNAME), Darwin)							# OS X
    PLATFORM=darwin
    EXT =
    LDFLAGS = -F$(CEF_BINARY_PATH) -framework Cocoa -framework "Chromium Embedded Framework" -L$(CEF_STATIC_LIB_PATH) -lcef_dll \
               -DUNICODE -rpath @executable_path/../Frameworks
    RES_TARGET_PATH = $(TARGET).app/Contents/MacOS/
    LINKED_RES = 
else ifeq ($(UNAME), Linux)						# linux on PC
	PLATFORM=linux
	EXT := 
    RES_TARGET_PATH := 
    LINKED_RES = 
else ifeq ($(OS) $(ARCH), Windows_NT i686)		# Windows 32
	PLATFORM=windows
	EXT = .exe
	LDFLAGS = -mwindows -mconsole -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic \
               -L$(CEF_BINARY_PATH) -lcef -L$(CEF_STATIC_LIB_PATH) -lcef_dll \
               -DUNICODE
    RES_TARGET_PATH = 
    WINDRES = windres
    LINKED_RES = $(OBJDIR)resources.o 
else ifeq ($(OS) $(ARCH), Windows_NT x86_64)	# Windows 64
	PLATFORM=windows
	EXT = .exe
	LDFLAGS = -mwindows -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic \
               -L$(CEF_BINARY_PATH) -lcef -L$(CEF_STATIC_LIB_PATH) -lcef_dll \
               -DUNICODE
    RES_TARGET_PATH = 
    WINDRES := windres
    LINKED_RES = $(OBJDIR)resources.o 
endif

CEF_BINARY_PATH = $(CEF_ROOT)/binary/$(PLATFORM)-$(ARCH)/Release/

CEF_ROOT := ../cef
CEF_STATIC_LIB_PATH := $(CEF_ROOT)/target-libcef_dll

ifeq ($(PLATFORM), darwin)
    OBJS := cefsimple_mac.o simple_app.o simple_handler.o simple_handler_mac.o LocalSchemeHandlerFactory.o BellardPiReadHandler.o bellard_pi.o
else ifeq ($(PLATFORM), windows)
    OBJS := cefsimple_win.o simple_app.o simple_handler.o simple_handler_win.o LocalSchemeHandlerFactory.o BellardPiReadHandler.o bellard_pi.o
endif

CC := gcc
CXX := g++
srcdir := ./
OBJDIR := target/
RESDIR := target/deploy/

INCLUDES := -I$(CEF_ROOT) -I$(srcdir)../
WARNINGS := -Wall -W -Winline -Wshadow -Wstrict-overflow=5 -Wno-shadow -Wno-unused-parameter
CFLAGS := -O0 -g2
CXXFLAGS := $(CFLAGS) -fpermissive

TARGET := cefsimple

OBJS := $(OBJS:%=$(OBJDIR)%)

all : $(RESDIR)$(RES_TARGET_PATH)$(TARGET)$(EXT) cefres

ifeq ($(PLATFORM), darwin)

cefres:
	mkdir -p $(RESDIR)
	mkdir -p $(RESDIR)$(TARGET).app/Contents/Frameworks/
	cp -rf $(CEF_BINARY_PATH)Chromium\ Embedded\ Framework.framework $(RESDIR)$(TARGET).app/Contents/Frameworks/
	cp -rf $(srcdir)res/osx/* $(RESDIR)$(TARGET).app/Contents

else

cefres:
	mkdir -p $(RESDIR)
	cp -rf $(CEF_ROOT)/Resources/* $(RESDIR)
	cp -rf $(CEF_BINARY_PATH)*.bin $(CEF_BINARY_PATH)*.dll $(RESDIR)

endif

$(RESDIR)$(RES_TARGET_PATH)$(TARGET)$(EXT) : $(OBJDIR)$(TARGET).long$(EXT)
	mkdir -p $(RESDIR)$(RES_TARGET_PATH)
ifeq ($(PLATFORM), darwin)
	strip -Sx $< -o $@
	install_name_tool -change "@executable_path/Chromium Embedded Framework" "@executable_path/../Frameworks/Chromium Embedded Framework.framework/Chromium Embedded Framework" $@
else
	strip -s $< -o $@
endif

$(OBJDIR)$(TARGET).long$(EXT) : $(OBJS) $(LINKED_RES)
	mkdir -p $(OBJDIR)
	$(CXX) $(CFLAGS) $(WARNINGS) -o $@ $(OBJS) $(LDFLAGS) $(LINKED_RES)

ifeq ($(PLATFORM), windows)
$(LINKED_RES): $(srcdir)cefsimple.rc $(srcdir)/res/win/cefsimple.ico
	mkdir -p $(OBJDIR)
	$(WINDRES) -I$(srcdir) -i $(srcdir)cefsimple.rc -o $@
endif

$(OBJDIR)%.o: $(srcdir)%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(WARNINGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)%.o: $(srcdir)%.mm
	mkdir -p $(OBJDIR)
	$(CXX) $(CFLAGS) $(WARNINGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)%.o: $(srcdir)%.cc
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(WARNINGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)%.o: $(srcdir)%.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(WARNINGS) $(INCLUDES) -c $< -o $@
