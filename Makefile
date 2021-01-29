# boost on lonestar /opt/apps/intel18/boost/1.64/include 
# boost on wrangler /opt/apps/intel15/boost/1.55.0/x86_64/include
# boost on stampede2 /opt/apps/intel18/boost/1.68/include -- intel/18.0.2 and impi/18.0.2 loaded by default

CXX = mpicxx

INC = -I . \
  -I /opt/apps/intel18/boost/1.68/include \
  -I /home1/02076/abacolla/include
LDLIBS = 
LDFLAGS = 
CXXFLAGS = -std=c++17 -Wall -Wextra -O3 # -qopt-report=4 -qopt-report-phase ipo

TARGET = vga_spotLight

BUILD_DIR = ./build
SRCS = $(wildcard *.cpp)
OBJ = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
DEPS = $(OBJ:%.o=%.d)

$(TARGET) : $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET) : $(OBJ)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

-include $(DEPS)

$(BUILD_DIR)/%.o : %.cpp
	mkdir -p $(@D)
	$(CXX) -static $(CXXFLAGS) -MMD -c $< -o $@ $(INC)

.PHONY: all clean tests

all: clean $(TARGET)

clean:
	rm -fr $(BUILD_DIR)

tests: $(TARGET)
	$(BUILD_DIR)/$(TARGET)
