UNAME := $(shell uname)

ifndef ARCH
  ARCH := $(shell uname -m)
endif

ifeq ($(UNAME), Darwin)							# OS X
    PLATFORM=darwin
else ifeq ($(UNAME), Linux)						# linux on PC
	PLATFORM=linux
else ifeq ($(OS) $(ARCH), Windows_NT i686)		# Windows 32
	PLATFORM=windows
else ifeq ($(OS) $(ARCH), Windows_NT x86_64)	# Windows 64
	PLATFORM=windows
endif

        CXX := g++
        CC := gcc
        AS := as
        AR := ar
        OPT ?= -ggdb3 -O2
MAKEDEPEND = -MP -MD -MF $(patsubst %.o,%.d,$(OBJDIR).deps/$(@F))
  WARNINGS := -Wall -W -Winline -Wshadow -Wstrict-overflow=5 -Wno-shadow -Wno-unused-parameter #-Werror #-Wno-error=strict-aliasing
    CFLAGS := $(OPT)
  CXXFLAGS = $(CFLAGS) -fpermissive
   ARFLAGS := rcsv
  INCLUDES = -I$(srcdir).. -I$(srcdir)../include -I$(srcdir)../dllinclude
srcdir := libcef_dll/
   DEPENDS := libcef_dll.a
   libdir := libcef_dll libcef_dll/cpptoc libcef_dll/ctocpp libcef_dll/wrapper libcef_dll/base

   OBJDIR := target-libcef_dll/

LIBUTIL_OBJS :=

define sublibdir_TEMPLATE
 tmp := $$(subst /,_,$1)
 objpath := $(OBJDIR)$$(tmp)%.o
 depend = -MP -MD -MF $$(patsubst %.o,%.d,$(OBJDIR).deps/$$(@F))

 LIBUTIL_OBJS += $$(patsubst %.cc,$$(objpath),$$(notdir $(wildcard $(1)/*.cc)))
 LIBUTIL_OBJS += $$(patsubst %.cpp,$$(objpath),$$(notdir $(wildcard $(1)/*.cpp)))

 $$(objpath): $(1)/%.cc
	$(CXX) $$(CXXFLAGS) -DUSING_CEF_SHARED=1 $(WARNINGS) $(INCLUDES) $$(depend) -c $$< -o $$@

 $$(objpath): $(1)/%.cpp
	$(CXX) $$(CXXFLAGS) -DUSING_CEF_SHARED=1 $(WARNINGS) $(INCLUDES) $$(depend) -c $$< -o $$@
endef

$(foreach tgt,$(libdir),$(eval $(call sublibdir_TEMPLATE,$(tgt))))

DLLTOOL := dlltool

all: prepare $(OBJDIR)libcef_dll.a

PHONY += all 

OBJDEPS := $(OBJS:%.o=$(OBJDIR).deps/%.d) $(LIBUTIL_OBJS:$(OBJDIR)%.o=$(OBJDIR).deps/%.d)
override OBJS := $(OBJS:%=$(OBJDIR)%)
override DEPENDS := $(DEPENDS:%=$(OBJDIR)%)

ifeq ($(PLATFORM), windows)
    override CFLAGS += -mms-bitfields -DUNICODE -DMINGW_HAS_SECURE_API=1
endif

$(OBJDIR)%.o: $(srcdir)%.c
	$(CC) $(CFLAGS) $(WARNINGS) $(INCLUDES) $(MAKEDEPEND) -c $< -o $@

$(OBJDIR)%.o: $(srcdir)%.cc
	$(CXX) $(CXXFLAGS) $(WARNINGS) $(INCLUDES) $(MAKEDEPEND) -c $< -o $@

$(OBJDIR)%.o: $(srcdir)%.cpp
	$(CXX) $(CXXFLAGS) $(WARNINGS) $(INCLUDES) $(MAKEDEPEND) -c $< -o $@
	
$(OBJDIR)libcef_dll.a: $(LIBUTIL_OBJS)
	$(AR) $(ARFLAGS) $@ $?

-include $(OBJDEPS)

clean:
	rm -f $(addprefix $(OBJDIR)*.,dll exp def a o)

prepare:
	@mkdir -p $(OBJDIR).deps

PHONY += clean prepare
.PHONY := $(PHONY)
