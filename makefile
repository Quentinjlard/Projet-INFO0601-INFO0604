#
# MAIN CONFIGURATION
#

EXEC = menu
OBJECTS = functions.o item.o publisher.o fileMap.o playingField.o menu.o
PROJECT_NAME = Projet_L3

OBJECTS_DIR = obj
INCLUDE_DIR = includes
BIN_DIR = bin

#
# SUFFIXES (must not change it)
#

.SUFFIXES: .c .o

#
# OBJECTS (must not change it)
#

EXEC_O = $(EXEC:=.o)
OBJECTS_O = $(OBJECTS) $(EXEC_O)

#
# ARGUMENTS AND COMPILER (to configure)
#

CC = gcc
CCFLAGS_STD = -Wall -O3 
CCFLAGS_DEBUG = -D _DEBUG_
CCFLAGS = $(CCFLAGS_STD)
CCLIBS = -lcurses

#
# RULES (must not change it)
#

all: msg $(OBJECTS) $(EXEC_O)
	@echo "Create executables..."
	@for i in $(EXEC); do \
	$(CC) -o $(BIN_DIR)/$$i $(OBJECTS_DIR)/$$i.o $(OBJECTS_DIR)/$(OBJECTS) $(CCLIBS) -I../$(INCLUDE_DIR)/; \
	done
	@echo "Done."

msg:
	@echo "Create objects..."

debug: CCFLAGS = $(CCFLAGS_STD) $(CCFLAGS_DEBUG)
debug: all

#
# DEFAULT RULES (must not change it)
#

%.o : src/%.c
	@cd $(dir $<) && ${CC} ${CCFLAGS} -c $(notdir $<) -o ../$(OBJECTS_DIR)/$(notdir $@) -I../$(INCLUDE_DIR)/

#
# MAIN RULES (must not change it)
#

# You can add your own commands
clean:
	@echo "Delete objects, temporary files..."
	@rm -f $(OBJECTS_DIR)/$(OBJECTS_O) $(OBJECTS_DIR)/$(EXEC_O)
	@rm -f $(INCLUDE_DIR)/*~ $(INCLUDE_DIR)/*# src/*~ src/*#
	@rm -f $(BIN_DIR)/$(EXEC)
	@rm -f dependancies
	@echo "Done."

depend:
	@echo "Create dependancies..."
	@sed -e "/^# DEPENDANCIES/,$$ d" makefile > dependancies
	@echo "# DEPENDANCIES" >> dependancies
	@for i in $(OBJECTS_O); do \
	$(CC) -MM -MT src/$$i $(CCFLAGS) src/`echo $$i | sed "s/\(.*\)\\.o$$/\1.c/"` -I$(INCLUDE_DIR)/ >> dependancies; \
	done
	@cat dependancies > makefile
	@rm dependancies
	@echo "Done."

#
# CREATE ARCHIVE (must not modify)
#

ARCHIVE_FILES = *

archive: clean
	@echo "Create archive $(PROJECT_NAME)_$(shell date '+%y%m%d.tar.gz')..."
	@REP=`basename "$$PWD"`; cd .. && tar zcf $(PROJECT_NAME)_$(shell date '+%y%m%d.tar.gz') $(addprefix "$$REP"/,$(ARCHIVE_FILES))
	@echo "Done."

# DEPENDANCIES
src/functions.o: src/functions.c includes/functions.h \
 includes/includeAll.h includes/functions.h includes/publisher.h \
 includes/item.h includes/fileMap.h includes/playingField.h
src/item.o: src/item.c includes/item.h includes/includeAll.h \
 includes/functions.h includes/publisher.h includes/item.h \
 includes/fileMap.h includes/playingField.h
src/publisher.o: src/publisher.c includes/publisher.h \
 includes/includeAll.h includes/functions.h includes/publisher.h \
 includes/item.h includes/fileMap.h includes/playingField.h
src/fileMap.o: src/fileMap.c includes/fileMap.h includes/includeAll.h \
 includes/functions.h includes/publisher.h includes/item.h \
 includes/fileMap.h includes/playingField.h
src/playingField.o: src/playingField.c includes/playingField.h \
 includes/includeAll.h includes/functions.h includes/publisher.h \
 includes/item.h includes/fileMap.h includes/playingField.h
src/menu.o: src/menu.c includes/includeAll.h includes/functions.h \
 includes/includeAll.h includes/publisher.h includes/item.h \
 includes/fileMap.h includes/playingField.h
src/menu.o: src/menu.c includes/includeAll.h includes/functions.h \
 includes/includeAll.h includes/publisher.h includes/item.h \
 includes/fileMap.h includes/playingField.h
