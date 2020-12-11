# Default optimization level
O ?= 2

all: snake_game

-include build/rules.mk

%.o: src/%.cpp $(BUILDSTAMP)
	$(call run,$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c,COMPILE,$<)

snake_game: test.o snake_map.o snake.o food.o
	$(call run,$(CXX) $(CXXFLAGS) $(O) -o $@ $^ $(LDFLAGS) $(LIBS),LINK $@)
	#$(call run,rm -f *.o *~ *.bak core *.core)
	#$(call run,rm -rf out *.dSYM $(DEPSDIR))

#sleep61: sleep61.cc
#	$(call run,$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ $^ $(LDFLAGS) $(LIBS),BUILD $@)

ifneq ($(filter -fsanitize=leak,$(CXXFLAGS)),)
LEAKCHECK = --leak
endif

clean: clean-main
clean-main:
	$(call run,rm -f snake_game *.o *~ *.bak core *.core,CLEAN)
	$(call run,rm -rf out *.dSYM $(DEPSDIR))

.PRECIOUS: %.o
.PHONY: all clean clean-main distclean check check-%
