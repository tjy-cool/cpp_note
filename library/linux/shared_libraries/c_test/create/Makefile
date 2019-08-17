# 编译器
CC		= gcc

# 汇编生成的目标文件 .o
OBJS 	= ./objs/Caluator.o

# 最终目标文件
TARGET 	= libCaluator.a

# 源文件
SRCS	= Caluator.c

# 生成最终的目标文件
$(TARGET) : $(OBJS)
	# 打包生成静态库
	ar cr $(TARGET) $(OBJS)

$(OBJS) : $(SRCS)
	$(shell if [-d "objs"]; then echo ; else mkdir objs; fi;)
	# 编译生成目标文件文件(机器代码),只编译不链接
	$(CC) -c -g $(SRCS) -o $(OBJS)

# 伪目标
.PHONY: clean all
all :
	make clean && make

clean:
	-rm $(OBJS) $(TARGET)
	-rm -rf objs