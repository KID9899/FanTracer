LIB_NAME = tracer
CXXFLAGS = -fopenmp
LDFLAGS = -fopenmp

SRCS = $(wildcard */*.cpp)
SRCS += $(wildcard c_api/*/*.cpp)

HDRS = $(wildcard c_api/*.h)
HDRS += $(wildcard c_api/*/*.h)
HDRS += $(wildcard *.h)
HDRS += $(wildcard */*.h)
HDRS += $(wildcard */*.hpp)

include ../Template.mk
