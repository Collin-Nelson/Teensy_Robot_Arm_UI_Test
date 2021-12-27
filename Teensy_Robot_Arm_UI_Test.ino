
#define inputSize 48            //Maximum size of the gcode serial input string

bool LS1 = 0;
bool LS2 = 0;
bool LS3 = 0;
bool LS4 = 0;
bool LS5 = 0;
bool LS6 = 0;

int pos1 = 0;
int pos2 = 0;
int pos3 = 0;
int pos4 = 0;
int pos5 = 0;
int pos6 = 0;
int pos7 = 0;

int accel1 = 10;
int accel2 = 0;
int accel3 = 0;
int accel4 = 0;
int accel5 = 0;
int accel6 = 0;

int vel1 = 0;
int vel2 = 0;
int vel3 = 0;
int vel4 = 0;
int vel5 = 0;
int vel6 = 0;

int minAngle1 = 0;
int minAngle2 = 0;
int minAngle3 = 0;
int minAngle4 = 0;
int minAngle5 = 0;
int minAngle6 = 0;

int maxAngle1 = 0;
int maxAngle2 = 0;
int maxAngle3 = 0;
int maxAngle4 = 0;
int maxAngle5 = 0;
int maxAngle6 = 0;

char input[inputSize+1];

void setup(){
  Serial.begin(57600);
  delay(1000);
  Serial.println("Move?");
  
  Serial.println("Current Acccelerations are: ");
      Serial.print("Accel 1: "); Serial.println(accel1);
      Serial.print("Accel 2: "); Serial.println(accel2);
      Serial.print("Accel 3: "); Serial.println(accel3);
      Serial.print("Accel 4: "); Serial.println(accel4);
      Serial.print("Accel 5: "); Serial.println(accel5);
      Serial.print("Accel 6: "); Serial.println(accel6);

  Serial.println("Current Velocities are: ");
      Serial.print("Ve1 l: "); Serial.println(vel1);
      Serial.print("Vel 2: "); Serial.println(vel2);
      Serial.print("Vel 3: "); Serial.println(vel3);
      Serial.print("Vel 4: "); Serial.println(vel4);
      Serial.print("Vel 5: "); Serial.println(vel5);
      Serial.print("Vel 6: "); Serial.println(vel6);

  Serial.println("Current Min Angles are: ");
      Serial.print("Min 1: "); Serial.println(minAngle1);
      Serial.print("Min 2: "); Serial.println(minAngle2);
      Serial.print("Min 3: "); Serial.println(minAngle3);
      Serial.print("Min 4: "); Serial.println(minAngle4);
      Serial.print("Min 5: "); Serial.println(minAngle5);
      Serial.print("Min 6: "); Serial.println(minAngle6);

  Serial.println("Current Max Angles are: ");
      Serial.print("Max 1: "); Serial.println(maxAngle1);
      Serial.print("Max 2: "); Serial.println(maxAngle2);
      Serial.print("Max 3: "); Serial.println(maxAngle3);
      Serial.print("Max 4: "); Serial.println(maxAngle4);
      Serial.print("Max 5: "); Serial.println(maxAngle5);
      Serial.print("Max 6: "); Serial.println(maxAngle6);
}

void loop(){
  if(Serial.available()){
    getSerial();
    Serial.println("Move?");
  }
  delay(100);
  
  Serial.println("Current motor positions are: ");
      Serial.print("Stepper 1: "); Serial.println(pos1);
      Serial.print("Stepper 2: "); Serial.println(pos2);
      Serial.print("Stepper 3: "); Serial.println(pos3);
      Serial.print("Stepper 4: "); Serial.println(pos4);
      Serial.print("Stepper 5: "); Serial.println(pos5);
      Serial.print("Stepper 6: "); Serial.println(pos6);
      Serial.print("Gripper 7: "); Serial.println(pos7);

  Serial.println("Current LS statuses are: ");
      Serial.print("LS1: "); Serial.println(LS1);
      Serial.print("LS2: "); Serial.println(LS2);
      Serial.print("LS3: "); Serial.println(LS3);
      Serial.print("LS4: "); Serial.println(LS4);
      Serial.print("LS5: "); Serial.println(LS5);
      Serial.print("LS6: "); Serial.println(LS6);
      
}


void getSerial(){
  //Read in serial data
  byte size = Serial.readBytes(input, inputSize);   //in format: 1:10.2:20.3:30.4:40.5:50.6:60 (J1 to 10, J2 to 20, etc)
  input[size] = 0;

  //split serial data by axis
  char* command = strtok(input, ".");

  //if recieve "home" with or without newline char, run the homing function
  if (strcmp(command, "home\n") == 0 || strcmp(command, "home") == 0){
    
    delay(500);
    pos1 = -90; pos2 = -90; pos3 = -90; pos4 = -90; pos5 = -90; pos6 = -90;
    LS1 = 1; LS2 = 1; LS3 = 1; LS4 = 1; LS5 = 1; LS6 = 1;
  }
  
  //if recieve "print pos" with or without newline char, run the homing function
  if (strcmp(command, "print pos\n") == 0 || strcmp(command, "print pos") == 0){
    
      Serial.println("Current motor positions are: ");
      Serial.print("Stepper 1: "); Serial.println(pos1);
      Serial.print("Stepper 2: "); Serial.println(pos2);
      Serial.print("Stepper 3: "); Serial.println(pos3);
      Serial.print("Stepper 4: "); Serial.println(pos4);
      Serial.print("Stepper 5: "); Serial.println(pos5);
      Serial.print("Stepper 6: "); Serial.println(pos6);
      Serial.print("Gripper 7: "); Serial.println(pos7);
  }
  
  //if recieve "zero" with or without newline char, move each joint to zero
  if (strcmp(command, "zero\n") == 0 || strcmp(command, "zero") == 0){
    delay(500);
    pos1 = 0; pos2 = 0; pos3 = 0; pos4 = 0; pos5 = 0; pos6 = 0; pos7 = 0;
    LS1 = 0; LS2 = 0; LS3 = 0; LS4 = 0; LS5 = 0; LS6 = 0;
  }

  //if recieve "LS status" with or without newline char, move each joint to zero
  if (strcmp(command, "LS status\n") == 0 || strcmp(command, "LS status") == 0){
    
      Serial.println("Current LS statuses are: ");
      Serial.print("LS1: "); Serial.println(LS1);
      Serial.print("LS2: "); Serial.println(LS2);
      Serial.print("LS3: "); Serial.println(LS3);
      Serial.print("LS4: "); Serial.println(LS4);
      Serial.print("LS5: "); Serial.println(LS5);
      Serial.print("LS6: "); Serial.println(LS6);
      
  }

  //loop through the command to each axis
  while (command != 0){
    
      // Split the command into the axis number and position commanded
      char* separator = strchr(command, ':');

      if (separator != 0){
        
          // Actually split the string in 2: replace ':' with 0
          *separator = 0;
          String servoId = command;
          ++separator;
          int position = atoi(separator);
          
          // Print out what was commanded with servoId and position
          Serial.print("\nServo ID: "); 
          Serial.println(servoId);      
          Serial.print("Target Position (deg): ");
          Serial.println(position);
          
          // Call function to check that positions are valid and set the position to move to
          if (servoId == "1"){ pos1 = position; LS1 = 0; }
          if (servoId == "2"){ pos2 = position; LS2 = 0; }
          if (servoId == "3"){ pos3 = position; LS3 = 0; }
          if (servoId == "4"){ pos4 = position; LS4 = 0; }
          if (servoId == "5"){ pos5 = position; LS5 = 0; }
          if (servoId == "6"){ pos6 = position; LS6 = 0; }
          if (servoId == "7"){ pos7 = position; }
          if (servoId == "A1"){ accel1 = position; Serial.print("Accel 1: "); Serial.println(accel1); }
          if (servoId == "A2"){ accel2 = position; Serial.print("Accel 2: "); Serial.println(accel2); }
          if (servoId == "A3"){ accel3 = position; Serial.print("Accel 3: "); Serial.println(accel3); }
          if (servoId == "A4"){ accel4 = position; Serial.print("Accel 4: "); Serial.println(accel4); }
          if (servoId == "A5"){ accel5 = position; Serial.print("Accel 5: "); Serial.println(accel5); }
          if (servoId == "A6"){ accel6 = position; Serial.print("Accel 6: "); Serial.println(accel6); }
          if (servoId == "V1"){ vel1 = position; Serial.print("Vel 1: "); Serial.println(vel1); }
          if (servoId == "V2"){ vel2 = position; Serial.print("Vel 2: "); Serial.println(vel2); }
          if (servoId == "V3"){ vel3 = position; Serial.print("Vel 3: "); Serial.println(vel3); }
          if (servoId == "V4"){ vel4 = position; Serial.print("Vel 4: "); Serial.println(vel4); }
          if (servoId == "V5"){ vel5 = position; Serial.print("Vel 5: "); Serial.println(vel5); }
          if (servoId == "V6"){ vel6 = position; Serial.print("Vel 6: "); Serial.println(vel6); }
          if (servoId == "m1"){ minAngle1 = position; Serial.print("Min 1: "); Serial.println(minAngle1); }
          if (servoId == "m2"){ minAngle2 = position; Serial.print("Min 2: "); Serial.println(minAngle2); }
          if (servoId == "m3"){ minAngle3 = position; Serial.print("Min 3: "); Serial.println(minAngle3); }
          if (servoId == "m4"){ minAngle4 = position; Serial.print("Min 4: "); Serial.println(minAngle4); }
          if (servoId == "m5"){ minAngle5 = position; Serial.print("Min 5: "); Serial.println(minAngle5); }
          if (servoId == "m6"){ minAngle6 = position; Serial.print("Min 6: "); Serial.println(minAngle6); }
          if (servoId == "M1"){ maxAngle1 = position; Serial.print("Max 1: "); Serial.println(maxAngle1); }
          if (servoId == "M2"){ maxAngle2 = position; Serial.print("Max 2: "); Serial.println(maxAngle2); }
          if (servoId == "M3"){ maxAngle3 = position; Serial.print("Max 3: "); Serial.println(maxAngle3); }
          if (servoId == "M4"){ maxAngle4 = position; Serial.print("Max 4: "); Serial.println(maxAngle4); }
          if (servoId == "M5"){ maxAngle5 = position; Serial.print("Max 5: "); Serial.println(maxAngle5); }
          if (servoId == "M6"){ maxAngle6 = position; Serial.print("Max 6: "); Serial.println(maxAngle6); }
         
      }
      // Find the next command in input string
      command = strtok(0, ".");
  }
}
