#include<avr/io.h>
#include<avr/interrupt.h>

 int flag=0,flag1=0;
 int current=360;
char ch;
 void initADC()
{
  ADMUX=(1<<REFS0);
  ADCSRA|=(1<<ADEN)|(1<<ADPS1)|(1<<ADPS2)|(1<<ADPS0);
  }

  uint16_t ReadADC(uint8_t ch)
  {
    ch=ch&0b00000111;
    ADMUX|=ch;
    ADCSRA|=(1<<ADSC);
    while(!(ADCSRA&(1<<ADIF)));
    ADCSRA|=(1<<ADIF);
    return (ADC);
    }

    void usart_send(int ch )

{
  
  while(UCSR0A!=(UCSR0A|(1<<UDRE0)));//waiting for UDRE to become high
  
  UDR0= ch;

}
void dis(char a[100])
{int i=0;
  while(a[i])
  {usart_send(a[i]);
  i++;
}
}


 

int main()
{
  DDRB=0x0F;
  DDRD=0b01000000;
 
  initADC();
  sei();
   TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
   TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)

   ICR1=4999;  //fPWM=50Hz (Period = 20ms Standard).
TCCR0A |= (1<<COM0A1)|(1<<WGM01)|(1<<WGM00);
  TCCR0B |= (1<<CS00) ;
  Serial.begin(9600);
dis("\nPress 'n' for normal mode\nPress 's' for smart mode");
while(UCSR0A!= (UCSR0A|(1<<RXC0)));
     ch=UDR0;
     _delay_ms(1000);
  EIMSK=0b00000000;
  EICRA=0b00000000;
  while(1)
  {
   
    if(ch=='n')
   { dis("Fan working in Normalmode\n");
   OCR0A=200;
   }
    else if(ch=='s')
    {
     dis("Fan working in smartmode\n");
  // Serial.println(flag);
      
      
    float adc=ReadADC(2);
    // float adc=550;
    // Serial.println(adc);
      OCR0A=230;
      OCR1A=current;
      if((PIND&0b00100000)==0b00100000)//right
     {
      OCR1A=550;
      _delay_ms(1000);
      current=550;
      }
     
    else if((PIND&0b00010000)==0b00010000)//str
     {
       OCR1A=360;
      _delay_ms(1000);
     current=360;
      }
    else if((PIND&0b10000000)==0b10000000)//left
     {
       OCR1A=180;
      _delay_ms(1000);
     current=180;
      
      }
    }
    }
}
  
  

