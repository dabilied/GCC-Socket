# FILE        : Makefile
# DESCRIPTION : Makefile for visual search library.
# AUTHOR      : Shusheng Cen <censhusheng@gamil.com>
# DATE        : Oct 30, 2013

#EXTERN_LIB = ./lib/libopencv_core.so.2.4 \
			 ./lib/libopencv_highgui.so.2.4 \
			 ./lib/libopencv_imgproc.so.2.4 \
			 ./lib/libflann_cpp.so.1.8

BIN_DIR = ./bin
SRC_DIR = ./src
LIB_DIR = ./lib
INC_DIR = ./include

CC = g++
CFLAGS = -Wall -O3 -std=c++98 -fopenmp -I$(INC_DIR)
LDFLAGS = -Wl,--rpath,'$$ORIGIN/../lib/'
LDFLAGS += $(EXTERN_LIB)

bin_src := $(wildcard ./src/*.cpp)
bin_tgt := $(addprefix $(BIN_DIR)/, $(patsubst %.cpp,%,$(notdir $(bin_src))))
bin_dep := $(addsuffix .d, $(bin_tgt))
deps += $(bin_dep)

# --------------------------------------------------------------------
#                                                                Build
# --------------------------------------------------------------------
.PHONY : all build-bin make-dir
all: make-dir build-bin

# generate the directory
make-dir:
	@mkdir -p $(BIN_DIR) $(OBJ_DIR)

build-bin: $(bin_tgt)

$(BIN_DIR)/% : $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) "$<" -o "$@"

$(BIN_DIR)/%.d : $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -MM -MT '$(BIN_DIR)/$*' "$<" -MF "$@"

no_dep_targets += clean bin-clean dep-clean

clean: bin-clean dep-clean
bin-clean:
	rm -f $(bin_tgt);
dep-clean:
	rm -f $(deps);
# --------------------------------------------------------------------
#                                                 Include dependencies
# --------------------------------------------------------------------
ifeq ($(filter $(no_dep_targets), $(MAKECMDGOALS)),)
-include $(deps)
endif
