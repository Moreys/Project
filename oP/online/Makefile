NC_DIR:= ./include ./include/cppjieba
SRC_DIR:= ./networklib
SRCS:= $(wildcard $(SRC_DIR)/*.cc)
LIBS:= -lboost_regex -lpthread -llog4cpp
CXXFLAGS:= -std=c++11 -g

$(EXE):$(SRCS)
	g++ -g -o $@ $^  $(LIBS) $(addprefix -I, $(INC_DIR)) $(CXXFLAGS)
#clean:
#rm main
