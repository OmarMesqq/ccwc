OUT:=ccwc

release:
	gcc -O3 -Wall -Wextra -Winline main.c -o $(OUT)

debug:
	gcc -g -Wall -Wextra -Winline main.c -o $(OUT)
