## SCIHB C TO 16 BIT ASSEMBLY FOR CREATING SMALL OSES EASILY


##### hello eveyone, today i finally sent you all my transpiler because i think it is alright and somewhat "polished"

it is very easy to use it, here is an exemple code you can see in the exemple_code directory:

```c
#include "code.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
	START_PROGRAM
	print_str("Hello world!");
	END_PROGRAM
	return 0;
}

```


---

here is the full code explication:

```c
#include "code.h"
#include <stdio.h>
#include <stdbool.h>
```


both libraries are needed to work.

---
```c
START_PROGRAM
```
and
```c
END_PROGRAM
```

are needed, you can also use
```c 
start();
```

to start up without clearing the screen, and for END_PROGRAM you can use:

```c
halt();
end();
// ! both are needed to be put at this exact order !
```
---
after that,

```c
print_str("Hello world!");
```

is used to show "Hello world!" on the screen, for all the functions, scroll to the end.


---


### FUNCTIONS:

#### PRINT FUNCTIONS:

```c
print_str(const char* string);
```

used to print a string


```c
print_num(int num);
```


prints a number (might be removed)


```c
print_stack(const char* string);
```

prints the latest element in the stack.

```c
new_line();
```

creates a newline

```c
clear_screen();
```

clears the screen



---

#### STACK FUNCTIONS


```c
addstack(int value);
```

adds a value to the stack


```c
freestack();
```

frees the last element on the stack.

---


#### LABELS AND REGISTERS:

```c
addlabel(const char* name);
```

creates a label 

```c
addlabel("label1");
```

is equivalent of 

```asm
label1:
```


```c
regadd(const char* reg1, const char* reg2, bool inlabel);
```

adds two registers together, the bool "inlabel" is basically if the instruction is in a label, if it is, it will just add a tab.




```c
regmov(const char* reg1, const char* whattomov, bool inlabel);
```

moves a value inside a register.


```c
regsub(const char* reg1, const char* reg2, bool inlabel);
```

substracts a value inside a register.


```c
regint(const char* interrupt, bool inlabel);
```


used for calling interupts (for exemple 0x10 for showing to the screen.)


---


### DRAWING TO THE SCREEN




```c
init_vga();
```
initializes vga to use for drawing pixels, needs to be called to work.


```c
draw_pixel_vga(int x, int y, const char* color, const char* page);
```


draws a pixel with vga,x and y are the cordinates, color is for the color (use very basic color palette), and page what page it should use

---


### MISC

```c
start();
```

start the program
```c
halt();
```
halt the program
```c
end();
```
end the program





---




## HOW TO USE:

### TOOLS NEEDED:

* a c compiler
* nasm
* qemu (for testing)




---


### HOW TO BOOT OS


you will need to use a very small assembly program to connect the code

here is an working exemple:
```asm

; boot.asm

bits 16
org 0x7C00

xor ax, ax
mov es, ax          ; ES = 0x0000
mov bx, 0x7E00      ; load destination = 0x0000:0x7E00

mov ah, 0x02        ; BIOS read sectors function
mov al, 15          ; number of sectors to read (15 * 512 = 7,680 bytes)
mov ch, 0           ; cylinder 0
mov cl, 2           ; start at Sector 2 (right after boot sector)
mov dh, 0           ; head 0

int 0x13            ; read sectors into RAM

jmp 0x0000:0x7E00   ; jump straight to c code

times 510 - ($ - $$) db 0
dw 0xAA55
```


by default, the c code will output directly into the screen, if you want to output it to a file directly, you can use:

```bash
./transpiler > main.asm
```


after outputing to a main.asm file, you can compile both the boot.asm and main.asm file with nasm

```bash
nasm boot.asm -o boot.bin
nasm main.asm -o main.bin
```

now there is one problem, you have two different files, and you want a singular file to boot from. in that case, you can use cat to combine the two binaries:

```bash
cat boot.bin main.bin > os.img # or os.bin, your call.
```

after all of this, you can use qemu to boot into it:
```bash
qemu-system-i386 -fda os.img (or whatever you called it.)
```


and it works finally works!


---


































sadly this is a very basic project and i have not done the best transpiler but it is enough to work for very basic ones.