# grid frequency model.
#
# Copyright (C) 2017  Ken-ichi Kondo.
#
# This file is part of SGFM.
# 
# SGFM is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# SGFM is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with SGFM.  If not, see <http://www.gnu.org/licenses/>.

CC=g++

BINDIR := bin
SRCDIR := src 
INCDIR := include

TARGET := $(BINDIR)/main
SRCFILES := $(wildcard src/*.cpp)
OBJFILES := $(SRCFILES:%.cpp=%.o)

all : $(TARGET)

clean : 
	rm -f $(OBJFILES) $(TARGET)

run:all
	./sample/main.sh

src/%.o : src/%.cpp include/%.hpp
	$(CC) -std=c++11 -Wall -Werror -O2 -c -I$(INCDIR) -o $@ $<

$(BINDIR)/main: sample/main.cpp $(OBJFILES)
	$(CC) -std=c++11 -Wall -Werror -O2 -I$(INCDIR) -o $@ $^

