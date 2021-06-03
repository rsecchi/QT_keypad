uint16_t index1, index2;     // 16-bit fixed point variable
uint32_t counter;
uint16_t step1, step2;
uint8_t wave[256];           // Look up table

uint16_t dtmf_freq[] = {697, 770, 852, 941, 1209, 1336, 1477, 1644};
uint16_t dtmf_step[] = {457, 505, 558, 617,  792,  876,  968, 1077};
uint8_t  key_row[]   = {3, 0, 0, 0, 1, 1, 1, 2, 2, 2};
uint8_t  key_col[]   = {5, 4, 5, 6, 4, 5, 6, 4, 5, 6};

char buffer[256];
volatile uint8_t done;

void getstring(char* buffer)
{
char c = 0;
int i = 0;
    while (c != '\r')
    {
        if (Serial.available()) {
            c = Serial.read();
            buffer[i] = c;
            i++;
        }
    }
    buffer[i-1] = 0;
}

void lut_setup_sine(uint8_t* wave) 
{
    for(uint16_t i=0; i<256; i++)
        wave[i] = 127*(1+0.5*sin((2*M_PI*i)/256));
}

void setup_irq_100k_timer0() 
{  
     cli();
     // Fast PWM, no prescaler
     TCCR0A = 0x02;
     TCCR0B = 0x01;

     // 160 ticks at 16MHz = 100kHz 
     OCR0A = 160;
     DDRD = (1<<PD5);
     sei();
}



ISR(TIMER0_COMPA_vect)
{
    counter++;
    uint16_t out;
    index1 += step1;
    index2 += step2;

    out = wave[index1>>8]+wave[index2>>8];
    bitWrite(PORTD, PD5, out>>8);

    if ((counter & 0x1FFF) == 0) {
      if (step1 == 0) {
          TIMSK0 &= ~(1<<OCIE0A);
          done = 1;
      }
      step1 = step2 = 0;
      counter = 0;
    }
        
}


void setup() {

  Serial.begin(9600);
  lut_setup_sine(wave);
  setup_irq_100k_timer0();
  step1 = 617;
  step2 = 792;
  
}

void play_key(uint8_t key) 
{
  step1 = dtmf_step[key_row[key]];
  step2 = dtmf_step[key_col[key]];
  counter = 0;
  done = 0;
  TIMSK0 = (1<<OCIE0A);  // enable timer;
  while(!done);
}

void loop() 
{
    uint8_t i = 0;
    uint8_t key;
  
    getstring(buffer);
    Serial.println(buffer);

    while(buffer[i] != 0) {
      
      key = buffer[i] - '0';

      if (key <= 9)
          play_key(key);
      i++;
  
    }
  
}
