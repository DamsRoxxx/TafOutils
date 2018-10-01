# Makefile

CC = g++

RTI_DDS_FLAGS = -DRTI_UNIX -DRTI_LINUX -DRTI_64BIT -DRTI_STATIC -I. -I../include -I../include/ndds
RTI_DDS_LIBS = -L../lib/ndds -lnddscppz -lnddscz -lnddscorez

QTSQL_FLAGS = -I../include/Qt/QtCore -I../include/Qt/QtSql
QTSQL_LIBS = -L../lib/Qt -lQtSql -lQtCore

CPPFLAGS = -Wall -m64 $(RTI_DDS_FLAGS) $(QTSQL_FLAGS)
LDFLAGS = -ldl -lnsl -lm -lpthread -lrt $(RTI_DDS_LIBS) $(QTSQL_LIBS)

BINDIR = ../bin
OBJDIR = ../obj
DEPDIR = ../dep

TARGET = $(BINDIR)/AGSDDSSpy

SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, $(OBJDIR)/%.o, $(SRC))

$(TARGET): $(OBJ)
	$(shell mkdir -p $(BINDIR))
	$(CC) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp
	$(shell mkdir -p $(OBJDIR) $(DEPDIR))
	$(CC) $(CPPFLAGS) -MMD -MF $(patsubst %.cpp, $(DEPDIR)/%.d, $<) -c $< -o $@

.PHONY: run
run: $(TARGET)
	$(TARGET)

.PHONY: gdb
gdb: $(TARGET)
	gdb -ex run $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJDIR)/*.o $(DEPDIR)/*.d .*.swp

-include $(wildcard $(DEPDIR)/*.d)
