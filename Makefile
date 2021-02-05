tests: md5.c tests.c
	gcc -std=c99 -Wall -Werror=format-security -Werror=implicit-function-declaration tests.c md5.c -O2 -o tests