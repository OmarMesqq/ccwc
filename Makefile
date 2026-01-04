OUT:=ccwc

release:
	gcc -Wall -Wextra -Winline main.c -o $(OUT)

debug:
	gcc -g -Wall -Wextra -Winline main.c -o $(OUT)
