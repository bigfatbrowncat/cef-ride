CEF_ROOT := ../cef
CEF_STATIC_LIB_PATH := $(CEF_ROOT)/target-libcef_dll
CEF_BINARY_PATH := $(CEF_ROOT)/binary/windows-x86_64/Release

EXT := .exe

CC := gcc
CXX := g++
WINDRES := windres
srcdir := ./
OBJDIR := target/
RESDIR := target/deploy/
OBJS := cefsimple_win.o simple_app.o simple_handler_win.o simple_handler.o

INCLUDES := -I$(CEF_ROOT) -I$(srcdir)../
WARNINGS := -Wall -W -Winline -Wshadow -Wstrict-overflow=5 -Wno-shadow -Wno-unused-parameter
CFLAGS := -O2 -g0
CXXFLAGS := $(CFLAGS) -fpermissive
LDFLAGS := -mwindows -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic \
           -L$(CEF_BINARY_PATH) -lcef -L$(CEF_STATIC_LIB_PATH) -lcef_dll \
		   -DUNICODE
TARGET := cefsimple

override OBJS := $(OBJS:%=$(OBJDIR)%)

all : cefres $(RESDIR)$(TARGET)$(EXT)

cefres:
	mkdir -p $(RESDIR)
	cp -rf $(CEF_ROOT)/Resources/* $(RESDIR)
	cp -rf $(CEF_BINARY_PATH)/*.bin $(CEF_BINARY_PATH)/*.dll $(RESDIR)

$(RESDIR)$(TARGET)$(EXT) : $(OBJDIR)$(TARGET).long$(EXT)
	mkdir -p $(RESDIR)
	strip -s $< -o $@

$(OBJDIR)$(TARGET).long$(EXT) : $(OBJS) $(OBJDIR)resources.o
	mkdir -p $(OBJDIR)
	$(CXX) $(CFLAGS) $(WARNINGS) -o $@ $(OBJS) $(LDFLAGS) $(OBJDIR)resources.o

$(OBJDIR)resources.o: $(srcdir)cefsimple.rc $(srcdir)/res/cefsimple.ico
	mkdir -p $(OBJDIR)
	$(WINDRES) -I$(srcdir) -i $(srcdir)cefsimple.rc -o $@

$(OBJDIR)%.o: $(srcdir)%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(WARNINGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)%.o: $(srcdir)%.cc
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(WARNINGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)%.o: $(srcdir)%.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(WARNINGS) $(INCLUDES) -c $< -o $@
