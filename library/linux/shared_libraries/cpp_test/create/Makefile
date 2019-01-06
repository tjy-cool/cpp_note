CC 		= g++
TARGET 	= Caluator.a
INCLUDE_DIR	= ./
vpath %.h INCLUDE_DIR

SRC_DIR	= .
SRCS	= $(foreach src, $(SRC_DIR), $(wildcard $(src)/*.cpp))

OBJ_DIR = ./objs/
OBJS1	= $(patsubst %.cpp, %.o, $(SRCS))
OBJS	= $(addprefix $(OBJ_DIR), $(notdir $(OBJS1)))

$(TARGET) : $(OBJS)
	ar cr $(TARGET) $(OBJS)

$(OBJS) : $(SRCS)
	$(shell if [-d $(OBJ_DIR)]; then echo ; else mkdir $(OBJ_DIR); fi;)
	$(CC) -o $(OBJS) -c $(SRCS)

.PHONY : clean all
all :
	make clean && make $(TARGET)

clean :
	-rm $(TARGET)
	-rm -rf objs