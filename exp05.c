#include &lt;lpc21xx.h&gt;
#include<lpc214x.h>
#define LCD (0xff&lt;&lt;8)
#define RS (1&lt;&lt;16)
#define RW (1&lt;&lt;17)
#define EN (1&lt;&lt;18)

#define r1 (1&lt;&lt;16)
#define r2 (1&lt;&lt;17)
#define r3 (1&lt;&lt;18)
#define r4 (1&lt;&lt;19)
#define c1 (1&lt;&lt;20)
#define c2 (1&lt;&lt;21)
#define c3 (1&lt;&lt;22)
#define c4 (1&lt;&lt;23)

void delay(unsigned int time);         //variable delay function
void lcd_ini(void);
void lcd_print(char *str);
void lcd_cmd(unsigned char command);
void lcd_dat(unsigned int data);

unsigned char keypad (void);
void keypad_delay(void);

int main (void)
{
	PINSEL0 = 0x00000000;
	IODIR0 = 0xffffffff;
	PINSEL1 = 0x00000000;
	IODIR1 = 0x00f00000;
	
	lcd_ini();
	lcd_print("Press any key");
	lcd_cmd(0xc0);
	
	while(1)
	{
		lcd_dat(keypad());
	}
	return 0;
}
void keypad_delay(void)
{
	unsigned int t1,t2;
	for(t1=0;t1&lt;300;t1++)
		for(t2=0;t2&lt;1275;t2++);
}
unsigned char keypad (void)
{
	unsigned char key;
	IOCLR1|=(c1|c2|c3|c4|r1|r2|r3|r4);
	while(1)
	{
		IOCLR1| = c1;
		IOSET1| = (c2|c3|c4);                      //first column
		
		if((IOPIN1&amp;r1)==0)
		{
			key = '7';
			keypad_delay();
			return key;
		}
		else if((IOPIN1&amp;r2)==0)
		{
			key = '8';
			keypad_delay();
			return key;
		}
		else if((IOPIN1&amp;r3)==0)
		{
			key = '9';
			keypad_delay();
			return key;
		}
		else if((IOPIN1&amp;r4)==0)
		{
			key = '/';
			keypad_delay();
			return key;
		}
		
		IOCLR1| = c2;
		IOSET1| = (c1|c3|c4);           //second column

		if((IOPIN1&amp;r1)==0)
		{
			key = '4';
			keypad_delay();
			return key;
		}
		else if((IOPIN1&amp;r2)==0)
		{
			key = '5';
			keypad_delay();
			return key;
		}
		else if((IOPIN1&amp;r3)==0)
		{
			key = '6';
			keypad_delay();
			return key;
		}
		else if((IOPIN1&amp;r4)==0)
		{
			key = '*';
			keypad_delay();
			return key;
		}
		
		IOCLR1| = c3;
		IOSET1| = (c1|c2|c4);           //third column

		if((IOPIN1&amp;r1)==0)
		{
			key = '1';
			keypad_delay();
			return key;
		}
		else if((IOPIN1&amp;r2)==0)
		{
			key = '2';
			keypad_delay();
			return key;
		}
		else if((IOPIN1&amp;r3)==0)
		{
			key = '3';
			keypad_delay();
			return key;
		}
		else if((IOPIN1&amp;r4)==0)
		{
			key = '-';
			keypad_delay();
			return key;
	  }
		
		IOCLR1| = c4;
		IOSET1| = (c1|c2|c3);           //fourth column

		if((IOPIN1&amp;r1)==0)
		{
			lcd_cmd(0x01);
			keypad_delay();
		}
		else if((IOPIN1&amp;r2)==0)
		{
			key = '0';
			keypad_delay();
			return key;
		}
		else if((IOPIN1&amp;r3)==0)
		{
			key = '=';
			keypad_delay();
			return key;
		}
		else if((IOPIN1&amp;r4)==0)
		{
			key = '+';
			keypad_delay();
			return key;
    }
}
}
void lcd_cmd(unsigned char command)
{
	IO0CLR| = (RS|RW|EN|LCD);
	IO0SET| = (command&lt;&lt;8);
	IO0CLR| = RS;
	IO0CLR| = RW;
	IO0SET| = EN;
	delay(2);
	IO0CLR|=EN;
	delay(3);
}
void lcd_dat(unsigned int data)
{
	IO0CLR| = (RS|RW|EN|LCD);
	IO0SET| = (data&lt;&lt;8);
	IO0SET| = RS;
	IO0CLR| = RW;
	IO0SET| = EN;
	delay(2);
	IO0CLR|=EN;
	delay(3);	
}	
void lcd_print(char *str)
{
	while(*str!='\0')
	{
		lcd_dat(*str);
		str++;
	}
}

void lcd_ini(void)
{
	delay(5);
	lcd_cmd(0x38);
	lcd_cmd(0x0f);
	lcd_cmd(0x06);
	lcd_cmd(0x01);
	delay(5);
	lcd_cmd(0x80);
}
void delay(unsigned int time)         //variable delay function
{
	unsigned int t1,t2;
	for(t1=0;t1&lt;time;t1++)
	for(t2=0;t2&lt;1275;t2++);
}
}