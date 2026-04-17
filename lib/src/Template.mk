ifndef LIB_NAME
    $(error LIB_NAME is not defined in library Makefile!)
endif
ifndef SRCS
    $(error SRCS is not defined in library Makefile!)
endif

CXX = g++
CXXFLAGS = -fPIC -Wall -O2

BUILD_DIR = ../../builds
INCLUDES_DIR = ../../includes/$(LIB_NAME)

LIB_EXT = so
LDFLAGS = -shared
SONAME_FLAG = -Wl,-soname,lib$(LIB_NAME).$(LIB_EXT)

TARGET = $(BUILD_DIR)/lib$(LIB_NAME).$(LIB_EXT)

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET) copy_headers


$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(LDFLAGS) $(SONAME_FLAG) -o $@ $^
	@echo "Library $(TARGET) was built"

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

copy_headers:
	mkdir -p $(INCLUDES_DIR)
	find . -type f \( -name '*.h' -o -name '*.hpp' -o -name '*.hh' \) -exec sh -c 'for f; do d="$(INCLUDES_DIR)/$$(dirname "$$f")"; mkdir -p "$$d"; cp "$$f" "$$d/"; done' sh {} +

clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf $(INCLUDES_DIR)

.PHONY: all clean copy_headers