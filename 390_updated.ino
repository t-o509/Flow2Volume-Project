  /* AUTOMATIVE LIQUID LEVEL AND VOLUME SYSTEM
      - Developed by Deniz KARADAYI and Kaan TOYAKSİ.
      - Fall, 2019
  */
  
  unsigned long t_speed1; 
  unsigned long t_speed2; 
  double t_speed_avg; 
  unsigned long t_volume1;  
  unsigned long t_volume2;

  double t_volume_avg;
  double flowSpeed;
  double volume;
  double pipeLength = 6.3; //variable
  double crossArea = 0.1; //variable
  double totalVolume = 0;


  int gone = 0;   // indicate a calculation is available to be done
  int head = 0;   // head of the FIFO array keeps successive liquid come
  int tail = 0;   // tail of the FIFO array keeps successive liquid come
  
  const int sizee = 15;       // size of the FIFO array
  unsigned long t_1[sizee];   // first existence of the liquid on the first sensor
  unsigned long t_3[sizee];   // flew out of the liquid from the first sensor
  unsigned long t2;           // first existence of the liquid on the second sensor 
  unsigned long t4;           // flew out of the liquid from the second sensor

  
  void setup() {
    attachInterrupt(digitalPinToInterrupt(2), liquidCome1, RISING);   // Interrupt Rouitine for first sensor
    attachInterrupt(digitalPinToInterrupt(3), liquidCome2, RISING);   // Interrupt Rouitine for secondc sensor
   
    Serial.begin(9600);
    Serial.println("System begins!");
  }
  
  //INTERRUPT SERVICE ROUTINES
  void liquidCome1() {
    t_1[head] = millis(); 
    Serial.print("T1 is written to i= ");
    Serial.println(head);   
    attachInterrupt(digitalPinToInterrupt(2), liquidGone1, FALLING);
  
  }
  void liquidCome2() {
      t2 = millis();
      Serial.println("T2...");
      attachInterrupt(digitalPinToInterrupt(3), liquidGone2, FALLING);
  } 
  void liquidGone1() {
    t_3[head] = millis(); 
    Serial.print("...T3 is written to i= ");   
    Serial.println(head);
    if(head == sizee-1){
      head==0;
    }else{
      head++;
    }
    attachInterrupt(digitalPinToInterrupt(2), liquidCome1, RISING);   
  }
  void liquidGone2() {
      Serial.println("...T4");
      t4 = millis();          
      gone=1;
      attachInterrupt(digitalPinToInterrupt(3), liquidCome2, RISING);
  }
  
  //MAIN LOOP
  void loop() {
      
      if(gone!=0){
          // TIME INTERVALS
          t_speed1  = t2  -  t_1[tail];   // t2-t1
          t_volume1 = t_3[tail]  -  t_1[tail];   // t3-t1
          t_speed2  = t4  -  t_3[tail];   // t4-t3
          t_volume2 = t4  -  t2;   // t4-t2
          // DATA CALCULATION 
          t_speed_avg = (t_speed2 + t_speed1) / 2000.0 ;
          t_volume_avg = (t_volume2 + t_volume1) / 2000.0 ;
              
          flowSpeed = pipeLength/t_speed_avg; // flow speed of the liquid
          volume = flowSpeed * t_volume_avg * crossArea; //volume passing through
          
          Serial.print("Passed volume: ");
          Serial.println(volume);
          totalVolume = totalVolume + volume;
          Serial.print("Total volume: ");
          Serial.println(totalVolume);
          Serial.print("");  
          Serial.print("Data stored. Read tail is ");
          Serial.println(tail);  
          
              // EXTRACTION OF THE DATA....
                  //codes..
                  //codes..
                  //codes..
              // EXTRACTION OF THE DATA...
              
          gone=0;    
          if(tail==sizee-1){
              tail=0;
          }else{
              tail++;
          }       
      }
  }
