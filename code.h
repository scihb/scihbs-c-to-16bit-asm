#pragma once
#include <stdio.h>
#include <string.h>

#define START_PROGRAM init(); clear_screen();
#define END_PROGRAM halt(); end();


// copyright (c) 2026 scihb - licensed under the MIT license


static int msgnmb = 0; // num of message



void init(){
	printf(";made with scihb's c to asm transpiler\n");
	printf(";copyright (c) 2026 scihb - MIT license\n");
	printf("bits 16\n");
	printf("org 0x7E00\n");
}







//////////////////// PRINT FUNCTIONS ////////////////////
void print_str(const char *c) {
	printf("mov si, %zu\n", strlen(c));
	printf("mov bx, 0\n");
	printf("msg_%d:\n" , msgnmb);
	printf("	mov ah, 0x0e\n");
	printf("	mov al, [msg_%d_message + bx]\n", msgnmb);
	printf("	int 0x10\n");
	printf("	inc bx\n");
	printf("	dec si\n");
	printf("	jnz msg_%d\n", msgnmb);
	printf("	jmp msg_%d_end\n", msgnmb);
	printf("msg_%d_message:\n ", msgnmb);
	printf("	db \"%s\", 0\n", c);
	printf("msg_%d_end:\n", msgnmb);
	msgnmb += 1;
}
void print_stack() {
    printf("pop ax\n");
    printf("mov cx, 0\n");
    printf("mov bx, 10\n");
    printf("print_stack_loop:\n");
    printf("xor dx, dx\n");
    printf("div bx\n");
    printf("push dx\n");
    printf("inc cx\n");
    printf("test ax, ax\n");
    printf("jnz print_stack_loop\n");
    printf("print_stack_digits:\n");
    printf("pop ax\n");
    printf("add al, '0'\n");
    printf("mov ah, 0x0e\n");
    printf("int 0x10\n");
    printf("loop print_stack_digits\n");
}

void print_num(int n) {
	char buffer[12]; // works
	snprintf(buffer, sizeof(buffer), "%d", n);
	print_str(buffer);
}
//////////////////////////////////////// 





//////////////////// STACK FUNC ////////////////////

void addstack(int val) {
	printf("mov di, %d\n", val);
	printf("push di\n");
}


void freestack() {
	printf("pop di\n");
}
//////////////////////////////////////// 



////////////// LABELS AND ADDING INTO REGISTERS //////////////////////


void addlabel(const char* name) {
	printf("%s:\n", name);
}

void regadd(const char* reg1, const char* reg2, bool inlabel) {
	if(inlabel == true) {
		printf("	add %s, %s\n", reg1, reg2);
	} else {
		printf("add %s, %s\n", reg1, reg2);
	}
}
void regmov(const char* reg1, const char* whattomov, bool inlabel) {
	if(inlabel == true) {
		printf("	mov %s, %s\n", reg1, whattomov);
	} else {
		printf("mov %s, %s\n", reg1, whattomov);
	}
}
void regsub(const char* reg1, const char* reg2, bool inlabel) {
	if(inlabel == true) {
		printf("	sub %s, %s\n", reg1, reg2);
	} else {
		printf("sub %s, %s\n", reg1, reg2);
	}
}
void regint(const char* interrupt, bool inlabel){
	if(inlabel == true) {
		printf("	int %s\n", interrupt);
	} else {
		printf("int %s\n", interrupt);
	}
}


////////////////////////////////////////////






/////////////// FOR LOOP //////////////////


// TODO: add for loops


///////////////////////////////////////////


//////////////////// MISC ////////////////////
void new_line(){
	printf("mov ah, 0x0e\n");
	printf("mov al, 0x0A\n");
	printf("int 0x10\n");
	printf("mov al, 0x0D\n");
	printf("int 0x10\n");
}
void clear_screen(){
	printf("mov ah, 0x00\n");
	printf("mov al, 0x03\n");
	printf("int 0x10\n");
}
void init_vga() {
	printf("mov ah, 0x00\n");
	printf("mov al, 0x13\n");
	printf("int 0x10\n");
}

void draw_pixel_vga(int x, int y, const char* color, const char* page) {

	printf("mov ah, 0x0C\n");
	printf("mov al, %s\n", color);
	printf("mov bh, %s\n", page);
	printf("mov cx, %d\n", x);
	printf("mov dx, %d\n", y);
	printf("int 0x10\n");
	
}


void halt() {
	printf("halt:\n");
	printf("	cli\n");
	printf("	hlt\n");
	printf("	jmp halt\n");
}
void end() {
	printf("times 7680 - ($ - $$) db 0\n ");
}
//////////////////////////////////////////////////////////// 
