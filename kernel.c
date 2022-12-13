//kernel.c
//Connor Walsh working with James Evans

void printString(char*);
void printChar(char*);
void readString(char*);
void readSector(char*);
void handleInterrupt21(int,int,int,int);

void main() {

	int startVidMem = 0xb800;
	int vidMemOffset = 0x0;
	int white = 0x7;
	char* letters = "Hello World\0";

	//char input[80];
	//int counter=0;

/*	while(*letters != 0x0) {
		putInMemory(startVidMem, vidMemOffset, *letters);
	vidMemOffset++;
	putInMemory(startVidMem, vidMemOffset, white);
	vidMemOffset++;
	// advance letters pointer
	letters++;
	}
*/

//	int ah=0xE;
//	int al='C';
//	int ax=ah*0x100+al;
//	interrupt(0x10,ax, 0,0,0);
//	interrupt(number, ax, bx, cx, dx)

	//printString("Hello World");
	//printChar('c');

	//char input[80];
	//int counter;
	//printString("Hello World\n");
	//readString();
	//counter=0;
	char buffer[512];
	char line[80];

//	printString("Enter a line: ");
//	readString(line);
//	printString(line);


//read sector

//	readSector(buffer, 30);
//	printString(buffer);
//step 4
//	makeInterrupt21();
//	interrupt(0x21, 0, 0, 0);
//step 5
//	makeInterrupt21();
//	interrupt(0x21,1,line,0,0);
//	interrupt(0x21,0,line,0,0);


	while(1)
	{
	//char line[80];
	//printString("Enter a line: ");
	//readString(line);
	//printString(line);
	//printString("Hello World");
	//readString();
	/*	char x=interrupt(0x16,0,0,0,0);
		input[counter]=x;
		counter=counter+1;
		printChar(x);
		if(x==0xd){
			printChar('\n');
			break;
		}*/
	}
}

void printString(char* string){
	int c=0;
	int ah=0xE;
	//int al=string[c]
	while (string[c] != 0x0){
	int al=string[c];
	int ax=ah*0x100+al;
	interrupt(0x10,ax,0,0,0);
	c++;
	}
}

void printChar(char* letter){
	int ah=0xe;
	int al=letter;
	int ax=ah*0x100+al;
	interrupt(0x10,ax,0,0,0);
}

void readString(char* input){
	int counter;
	char x;
	counter=0;
	while(1){
		x=interrupt(0x16,0,0,0,0);
		if(x==0x8){
			if (counter == 0) {
				counter=0;
			}

			else{
				counter=counter-1;
				printChar('\b');
				printChar(' ');
				printChar('\b');
			}
	}
		else if(x== 0xd){
		input[counter]=0xa;
		printChar(0xa);
		counter=counter+1;
		input[counter]=0x0;
		printChar(0x0);
		return;
		}
		else{
		input[counter]=x;
		counter=counter+1;
		printChar(x);
		}

//		input[counter]=x;
//		counter=counter+1;
//		printChar(x);
/*		if(x==0xd)
		{
			input[counter]=0xa;
			printChar(input[counter]);
			counter=counter+1;
			input[counter]=0x0;
			printChar(input[counter]);
			counter=counter+1;
			//printChar(0xa);
			//printChar(0x0);
			break;
		}
		if(x==0x8)
		{
			if(counter>0){
			input[counter-1]=' ';
			counter=counter-1;
			//counter=counter-1;
			input[counter+1]=0x0;
			printChar(' ');
			printChar('\b');
			}
		}*/
	}
}

void readSector(char* buffer, int sector){
	int ah=2;
	int al=1;
	int bx=buffer;
	int ch=0;
	int cl=sector+1;
	int dh=0;
	int dl=0x80;

	int ax=ah*256+al;
	int cx=ch*256+cl;
	int dx=dh*256+dl;
	interrupt(0x13,ax,bx,cx,dx);
}

void handleInterrupt21(int ax, int bx, int cx, int dx){
	printString("Handle Interrupt 21 Test");

	if(ax==0){
		printString(bx);
	}
	if(ax==1){
		readString(bx);
	}
	if(ax==2){
		readSector(bx, cx);
	}
	if(ax>=3){
		printString("Something went wrong...");
	}
}
