typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef uint pde_t;

typedef struct _lock_t {
	volatile uint value; // feel free to change this; its a bad name, just go to uthread CK
	//struct spinlock * spinny;
} lock_t;
