# Project Name, Path and type
# TYPE either:
# 	EXEC	:= executable
# 	SHARED	:= shared object
TYPE 	:= EXEC
NAME 	:= screw
PREFIX 	:=
SUFFIX 	:= .out
ODIR 	:= .
OPATH	:= $(ODIR)/$(PREFIX)$(NAME)$(SUFFIX)

# Source, include directory and files
SDIR	:= ./src
HDIR	:= ./include
BDIR 	:= ./bin
TDIR	:= ./.temp
SOURCE	:= $(wildcard $(SDIR)/*)
BINARY	:= $(SOURCE:$(SDIR)/%=$(BDIR)/%.o)

LIBS	:=
CFLAGS	:= -std=c++17
LFLAGS	:=
CFLAGS	+= -I$(HDIR)
LFLAGS	+= $(addprefix -l, $(LIBS))

# Files to be removed while cleaning
RMFILES	:=

# Settings & Commands
.PHONY: $(NAME) clean build
.SECONDARY:

build $(NAME): $(OPATH)
	@:
clean:
	@echo -e "\e[1;31m[RM] $(OPATH) $(RMFILES) $(BDIR) $(TDIR)\e[0m"
	@rm -rf --preserve-root $(OPATH) $(BDIR) $(TDIR) $(RMFILES)

# Top File
$(OPATH): $(BINARY)
	@echo -e "\e[1;36m[LD]\t$@\e[0m"
	@mkdir -p $(dir $@)
ifeq ($(TYPE), EXEC)
	@$(CXX) $^ -o $@ $(LFLAGS)
else ifeq ($(TYPE), SHARED)
	@$(CXX) $^ -o $@ $(LFLAGS) -shared
endif

# C++ Object Files
$(BDIR)/%.cpp.o: $(SDIR)/%.cpp
	@echo -e "\e[1;34m[CXX]\t$@\e[0m"
	@mkdir -p $(dir $@)
	@$(CXX) -c $< -o $@ $(CFLAGS) -fPIC

# BISON
$(BDIR)/%.y.o: $(TDIR)/%.y.cpp
	@echo -e "\e[1;34m[CXX]\t$@\e[0m"
	@mkdir -p $(dir $@)
	@$(CXX) -c $< -o $@ $(CFLAGS) -fPIC
$(TDIR)/%.y.h $(TDIR)/%.y.cpp: $(SDIR)/%.y
	@echo -e "\e[1;32m[BISON]\t$*.y\e[0m"
	@mkdir -p $(dir $@)
	@bison $< --defines=$(TDIR)/$*.y.h -o $(TDIR)/$*.y.cpp

#FLEX
$(BDIR)/%.l.o: $(TDIR)/%.l.cpp $(TDIR)/%.y.h
	@echo -e "\e[1;34m[CXX]\t$@\e[0m"
	@mkdir -p $(dir $@)
	@$(CXX) -c $< -o $@ $(CFLAGS) -fPIC -include $(TDIR)/$*.y.h
$(TDIR)/%.l.cpp: $(SDIR)/%.l
	@echo -e "\e[1;32m[FLEX]\t$*.l\e[0m"
	@mkdir -p $(dir $@)
	@flex -o $@ $<
