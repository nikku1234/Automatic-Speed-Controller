#define e1 10 	 // enable pin for motor 1
#define i1 8 		 // control pin 1 for motor 1
#define i2 9  		// control pin 2 for motor 1
int i, good, k,maxspeed;
byte data_in;
void setup()
{
  //attachinterrupt(1,data_incoming,rising);
  pinmode(3, input); 				//for receiver
  pinmode(4,output);				// led
  pinmode(5,output);				//led
  pinmode(e1, output);			//motor driver
  pinmode(i1, output);
  pinmode(i2, output);
  serial.begin(115200);			//assigning baud rate
}//setup
void loop()	//to assign maximum speed for vehicle  based on   incoming value
{
  data_incoming();
  if(char(data_in)=='a')
  {
    maxspeed=15;
    ledon();
  }
  else if(char(data_in)=='b')
  {
    maxspeed=45;
    ledon();
 }
  else if(char(data_in)=='c')
  {
     maxspeed=75;
     ledon();
  }
  else if(char(data_in)=='d')
  {
     maxspeed=105;
     ledon();
  }

  else
  {
    digitalwrite(4,low);                 //for all other conditions assigning maximum speed
    digitalwrite(5,low);
    maxspeed=255; 
  }
  //for remote
  int remotevalue;
  remotevalue=analogread(0);
  int voltage=remotevalue/4;
 // serial.println(voltage);
  if(voltage>maxspeed)
  {
  analogwrite(e1,maxspeed);     // run in needed speed
  digitalwrite(i1, high);                // to make the motor run in clockwise direction
  digitalwrite(i2, low);
  if(voltage<50&&voltage>40)     //giving a small torque for car
   {
     analogwrite(e1,200);
     delay(300);
   }
  }
  else
  {
    analogwrite(e1,voltage);
    digitalwrite(i1, high);
     digitalwrite(i2, low);
     if(voltage<50&&voltage>40)
   {
     analogwrite(e1,200);
     delay(300);
   }
  }
}//loop
void ledon()				// to switch on led’s present inside the car
{
   digitalwrite(4,high);
   digitalwrite(5,high);
}
void data_incoming()
{    
    for(i=0; i<100; i++)
    {
      delaymicroseconds(20);
      good=1;
      if(digitalread(3)==low)
      {
      good=0;
      i=100;
      }
    }//for

    if(good==1){
    detachinterrupt(1);
    while(1)
    {
      if(digitalread(3)==low)
      {
        delaymicroseconds(750);
        for(i=0; i<8; i++)
        {
          if(digitalread(3)==high)
          bitwrite(data_in, i, 1);
          else
          bitwrite(data_in, i, 0);
          delaymicroseconds(1000);
        }
        serial.println("");
        serial.print(char(data_in));
        break;
      }      
    }

    }

}
