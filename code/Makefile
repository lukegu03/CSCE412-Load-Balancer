# ---- Compiler settings ----
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g

# ---- Output executable ----
TARGET := load_balancer_simulation

# ---- Source / object files ----
SRCS := main.cpp \
        load_balancer.cpp \
        server_handler.cpp \
        server.cpp \
        request.cpp \
        firewall.cpp

OBJS := $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile step (pattern rule)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Convenience: run the program
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Force a full rebuild
rebuild: clean all

.PHONY: all run clean rebuild