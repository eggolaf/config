XX := clang++
LLVM_CONFIG := llvm-config
CXXFLAGS := -std=c++11 -MMD -MP $(shell $(LLVM_CONFIG) --cxxflags)
LIBS := -lm $(shell $(LLVM_CONFIG) --system-libs --ldflags --libs all)

PROG := kry
SRCS := $(wildcard src/*.cc)
OBJS := $(SRCS:%.cc=%.o)
DEPS := $(SRCS:%.cc=%.d)

.PHONY: $(PROG) clean

$(PROG): $(OBJS)
		$(CXX) $(CXXFLAGS) -o $@ -rdynamic $(OBJS) $(LIBS)

clean:
		-$(RM) $(PROG) $(OBJS) $(DEPS) $(TESTS:%=%.bc) $(TESTS:%=%.s) $(TESTS:%=%.bin)

-include $(DEPS)

