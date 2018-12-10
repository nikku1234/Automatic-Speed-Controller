
int flag=0,remotevalue,voltage,v;
char c='z';
 int echopin1=12; 	//initializing senosr’s echo pin to Arduino’s 12th pin 
int trigpin1= 11;         //initializing senosr’s trig pin to Arduino’s 11th pin 
 int echopin2=7;        //initializing senosr’s echo pin to Arduino’s 7th pin 
int trigpin2= 6;           //initializing senosr’s trig pin to Arduino’s 6h pin 
long duration1,duration2;
void setup()
{
  pinmode(2, output);
  serial.begin(9600);
}
void loop()
{ 
if(((ir1()==1)||(ir2()==1))&&flag==0)	//to check whether car entered  the zone
  {
    c='d';
    flag=1;    
  }
 else if(((ir1()==1)||(ir2()==1))&&flag==1)     //to check whether car outside the zone
  {
    c='z';
    rf_send(c);
    flag=0;
  }
    else if(flag==1)
  {
    rf_send(c);
  } 
 else
  {
    rf_send('z');		//maximum speed is allotted
  }    
}
void rf_send(byte input)		//sending function 
{
  int i;
  serial.println(c); 
  for(i=0; i<20; i++)
  {
  digitalwrite(2, high);
  delaymicroseconds(500);
  digitalwrite(2, low);
  delaymicroseconds(500);
}
  digitalwrite(2, high);
  delaymicroseconds(3000);
  digitalwrite(2, low);
  delaymicroseconds(500);
   for(i=0; i<8; i++)
  {
  if(bitread(input,i)==1)
  digitalwrite(2, high);
  else
  digitalwrite(2, low);
  delaymicroseconds(500);  
  if(bitread(input,i)==1)
  digitalwrite(2, low);
  else
  digitalwrite(2, high);
  delaymicroseconds(500);
  }  
  digitalwrite(2, low);
}

int ir1()				//code to detect the output of first sensor
{
  digitalwrite(trigpin1,low);
  delaymicroseconds(5);
    digitalwrite(trigpin1,high);
  delaymicroseconds(10);
    digitalwrite(trigpin1,low);
    pinmode(echopin1,input);
    duration1=pulsein(echopin1,high);
    duration1=duration1/58.2;
    if(duration1<15&&duration1 >0)
    {
      return 1;
    }
    else
    return 1;
}
int ir2()				//code to detect the output of second sensor
{
 digitalwrite(trigpin2,low);
  delaymicroseconds(5);
    digitalwrite(trigpin2,high);
  delaymicroseconds(10);
    digitalwrite(trigpin2,low);
    pinmode(echopin2,input);
    duration2=pulsein(echopin2,high);
    duration2=duration2/58.2;
    if(duration2<15&&duration2 >0)
    {
      return 1;
    }
    else
    return 0;
    }
