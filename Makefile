TARGET_FILE=fungi_ai
OBJ=main.o cards.o game_state.o

##########################################

DEPDIR := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

CC=g++
CFLAGS=-Wall -Werror -Wstrict-aliasing=0 -std=c++14 -O3 -fopenmp
LDFLAGS=-fopenmp
DEBUGFLAGS=-fsanitize=address -fsanitize=undefined
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

all: $(TARGET_FILE)

$(TARGET_FILE): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET_FILE) $(OBJ) $(LDFLAGS)

debug: $(OBJ)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(TARGET_FILE) $(OBJ) $(LDFLAGS)

%.o: %.cpp %.h $(DEPDIR)/%.d
%.o: %.cpp %.h
%.o: %.cpp $(DEPDIR)/%.d
%.o: %.cpp
	$(CC) $(DEPFLAGS) $(CFLAGS) -c $<
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

include $(wildcard $(DEPDIR)/*.d)

.PHONY: clean
clean:
	rm -rf $(OBJ) $(DEPDIR) $(TARGET_FILE)
