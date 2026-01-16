OUT:=ccwc

LIB_REPO = https://github.com/OmarMesqq/cutilities
LIB_PATH := libs/libcutilities

INCLUDES := -I$(LIB_PATH)
LDFLAGS  := -L$(LIB_PATH) -lcutilities -Wl,-rpath,$(shell pwd)/$(LIB_PATH)
$(LIB_PATH):
	mkdir -p libs
	git clone $(LIB_REPO) $(LIB_PATH)
	$(MAKE) -C $(LIB_PATH) release

release: $(LIB_PATH)
	gcc -O3 -Wall -Wextra -Winline main.c $(INCLUDES) $(LDFLAGS) -o $(OUT)

debug: $(LIB_PATH)
	gcc -g -Wall -Wextra -Winline main.c $(INCLUDES) $(LDFLAGS) -o $(OUT)
