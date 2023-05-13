CXX = g++
CXXFLAGS = -Wall -g -w -O1

SRCDIR = .
UTILS = ./utils

SRC = $(SRCDIR)/main.cpp

SELECTOR = ./utils/selector.cpp
PROCESS = ./utils/process.cpp
OFFSETS = ./bot/offsets.cpp
BOT = ./bot/bot.cpp
PIXEL = ./opencv/pixel.cpp

TARGET = bot

DEPS = $(SRC) $(SELECTOR) $(PROCESS) $(OFFSETS) $(BOT) 

$(TARGET): $(DEPS)
	$(CXX) $(CXXFLAGS) -o $@ $^
