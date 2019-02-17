CC 			= g++
CXX_CFLAGS 	= -std=c++11
TARGET		= TEST

# 动态库路径及动态库
SLIBDIR = -L../../lib
SLIB	= -lgtest

# 源文件路径
SUBDIR  = .	\
		  ./source \
		  ./testsrc 

# 头文件路径
INCLDER = 	-I./source	 \
			-I./testsrc \
			-I../../include

# 搜索所有源文件
CXX_SOURCES  = $(foreach src, $(SUBDIR), $(wildcard $(src)/*.cpp))

# 所有object文件
OBJDIR	= obj/
OBJS_TEMP 	= $(patsubst  %.cpp, %.o, $(CXX_SOURCES))
CXX_OBJECTS = $(addprefix $(OBJDIR), $(notdir $(OBJS_TEMP)))

# 所有依赖文件
DEP_FILES   = $(patsubst  %.o,  %.d, $(CXX_OBJECTS))

# 所有cpp文件的搜索路径
vpath %.cpp $(SUBDIR)

# 生成目标文件 
$(TARGET) : $(CXX_OBJECTS)
	$(CC) $(CXX_CFLAGS) $(SLIBDIR) $(SLIB) -o $@ $^

# 生成object文件
$(OBJDIR)%.o : %.cpp
	@mkdir -p $(OBJDIR)
	$(CC) -MMD -c $< $(CXX_CFLAGS) $(INCLDER) -o $@

# 加入依赖文件
-include $(DEP_FILES)

# 伪目标，all, clean, install, print, tar, dist, TAGS, check/test
.PHONY : print clean 
print :
	@echo $(CXX_SOURCES)
	@echo $(OBJS_TEMP)
	@echo $(CXX_OBJECTS)
clean :
	-rm -rf $(OBJDIR)
	-rm -rf $(TARGET)