TARGET_FILE=fungi_ai
PROD_OBJ=main.o
TEST_OBJ=test.o
BOTH_OBJ=cards.o game_state.o debug.o game_runner.o pile.o structured_pile.o\
         hand_structured_pile.o player_view.o action.o nn_encoding.o\
		 nn_game_simulator.o nn_train.o number_logger.o
SRC_DIR=src/
BUILD_DIR=build/

##########################################

ifeq ($(DEBUG), 1)
DEBUGFLAGS=-fsanitize=address -fsanitize=undefined -g -DDEBUG
BUILD_DIR:=$(BUILD_DIR)debug/
endif

DEPDIR := $(BUILD_DIR).d/
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)$*.Td

CC=g++
CFLAGS=-Wall -Werror -Wstrict-aliasing=0 -std=c++14 -O3 -fopenmp
LDFLAGS=-fopenmp -lubsan -lfloatfann
POSTCOMPILE = mv -f $(DEPDIR)$*.Td $(DEPDIR)$*.d

OBJ=$(PROD_OBJ) $(TEST_OBJ) $(BOTH_OBJ)
PROD_OBJ += $(BOTH_OBJ)
TEST_OBJ += $(BOTH_OBJ)

all: $(TARGET_FILE)

$(TARGET_FILE): $(addprefix $(BUILD_DIR),$(PROD_OBJ))
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(TARGET_FILE) $(addprefix $(BUILD_DIR),$(PROD_OBJ)) $(LDFLAGS)

test: $(addprefix $(BUILD_DIR), $(TEST_OBJ))
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(TARGET_FILE)_test $(addprefix $(BUILD_DIR),$(TEST_OBJ)) $(LDFLAGS)
	./$(TARGET_FILE)_test

$(BUILD_DIR)%.o: $(SRC_DIR)%.cpp $(SRC_DIR)%.h $(DEPDIR)%.d
$(BUILD_DIR)%.o: $(SRC_DIR)%.cpp $(SRC_DIR)%.h
$(BUILD_DIR)%.o: $(SRC_DIR)%.cpp $(DEPDIR)%.d
$(BUILD_DIR)%.o: $(SRC_DIR)%.cpp
	$(CC) $(DEPFLAGS) $(CFLAGS) $(DEBUGFLAGS) -c $< -o $@
	$(POSTCOMPILE)

$(DEPDIR)%.d: ;
.PRECIOUS: $(DEPDIR)%.d

include $(wildcard $(DEPDIR)*.d)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET_FILE) $(TARGET_FILE)_test
