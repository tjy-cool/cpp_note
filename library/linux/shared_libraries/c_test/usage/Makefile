# 编译器
CC		= gcc
OBJDIR	= ./objs
# 汇编生成的目标文件 .o
OBJS 	= $(OBJDIR)/main.o
# 最终目标文件
TARGET 	= main
# 源文件
SRCS	= main.c

SLIBDIR = ../create/
SLIBS	= -lCaluator
# 生成最终的目标文件
$(TARGET) : $(OBJS)
	# 先生成静态库
	@cd $(SLIBDIR) && make && cd -
	$(CC) -L$(SLIBDIR) $(SLIBS) $(OBJS) -o $(TARGET)
	
$(OBJS) : $(SRCS)
	$(shell if [-d $(OBJDIR)]; then echo ; else mkdir $(OBJDIR); fi;)
	$(CC) -c $(SRCS) -o $(OBJS)

# 伪目标
.PHONY: clean all
all :
	@cd $(SLIBDIR) && make clean && make && cd -
	make clean && make

clean:
	# 先删除静态库及其目标文件
	@cd $(SLIBDIR) && make clean && cd -
	-rm $(TARGET)
	-rm -rf $(OBJDIR)