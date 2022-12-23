all: gui gui2

gui: gui.c
	gcc `pkg-config --cflags gtk+-3.0` -o gui gui.c `pkg-config --libs gtk+-3.0`

gui2: gui2.c
	gcc `pkg-config --cflags gtk+-3.0` -o gui2 gui2.c `pkg-config --libs gtk+-3.0`

