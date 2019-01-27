CC 		= g++
CFLAGS 	= -std=c++11
TARGET	= TEST

SLIBDIR = -L../../lib
SLIB	= -lgtest

SRC_DIR	= .	\
		  ./source \
		  ./testsrc 

INCLDER = 	-I./source	 \
			-I./testsrc \
			-I../../include

SRCS 	= $(foreach src, $(SRC_DIR), $(wildcard $(src)/*.cpp))
vpath %.h $(SRC_DIR)

OBJDIR	= obj
OBJS1   = $(patsubst %.cpp, %.o, $(SRCS))
OBJS	= $(addprefix $(OBJDIR), $(notdir $(OBJS1)))

$(TARGET) : $(OBJS)
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(SLIBDIR) $(SLIB) -o $@ $^

$(OBJS) : $(SRCS)
	$(CC)  $(CFLAGS) $(INCLDER) -o $@ -c $<

.PHONY : print clean
print :
	echo $(SRCS)
	echo $(OBJS)
clean :
	-rm -rf $(OBJDIR)
	-rm -rf $(TARGET)