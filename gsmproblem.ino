
#include <Servo.h>
Servo myservo;

int IR=8;
int led=12;

int flag=0;
char phone_no[] = "8086265488";


void setup() 
{
 Serial.begin(9600); 		// opens serial port, sets data rate to 9600 bps

 pinMode(IR, INPUT);
 pinMode(led, OUTPUT);

 delay(2000);
 Serial.println("AT+CMGF=1"); 	//set GSM to text mode
 delay(200);
}

void loop()
{
    Serial.println(“morning medicine”);
    delay(2000);
    medicineTray(45);

    Serial.println(“afternoon medicine”);
    delay(2000);
    medicineTray(90);
  
    Serial.println(“night medicine”);
    delay(2000);
    medicineTray(135);      

}

void medicineTray(int x)
{
  myservo.write(0);
  delay(1000);

  myservo.write(x);
  delay(1000);

  medicineTakenStatus();       
  
  myservo.write(0);
     
}

void medicineTakenStatus()
{
 // checks for 20 x 1000ms = 20,000ms (20s) for motion detection
 
 for ( int i=0; i<20 ; i++)
  {

   if ( digitalRead(IR) == LOW )
   {
    digitalWrite(led, HIGH);
    Serial.println(“Motion Detected”);
    digitalWrite(led, LOW);
    
    flag = 1;
    break;				// breaks from for loop
   }

   delay(1000); 			// comes here when no motion is detected

   }

   // if no motion is detected during period of 20sec, flag value remains at 0

  if ( flag == 0 )
  {
   Serial.println( “Medicine not taken, make call to caretaker”);

   gsmCall();
  }

}

void gsmCall()
{
 delay(3000);

 Serial.print("ATD");; //Dial the phone number using ATD command
 Serial.print(phone_no);
 Serial.println(";"); // Semicolon is a must at the end
 delay(25000);
 Serial.println("ATH"); // After a delay of 5 secs Hang the call
 delay(1000);

 Serial.print("AT+CMGS=\"");
 Serial.print(phone_no);
 Serial.println("\"");

 delay(1500); // delay is must it waits for > symbol

 Serial.print("CAUTION...INTRUDER ALERT ALARM !!!!!!!!!!"); //SMS body
 Serial.write(0x1A); // sends ctrl+z end of message
 delay(2000);

 flag = 0;  // Reset flag to 0, for next cycle of operation
}

    

