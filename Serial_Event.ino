void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    
    char inChar = (char)Serial.read();
//    Serial.print("available test :");
//    Serial.println(inChar);
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      Getdata();
    }
  }
}

void Getdata()
 {
  if (stringComplete) 
            {
              //################################เทสระบบ################################################
              
              int randNumber1 = random(0,5);
              int randNumber2 = random(0,4);
              int randNumber3 = random(0,5);

              int randNumber4 = random(0,25);
              int randNumber5 = random(0,50);
              int randNumber6 = random(0,70);

              int randNumber7 = random(230,240);
              int randNumber8 = random(230,240);
              int randNumber9 = random(230,240);

              int randNumber10 = random(0,25);
              int randNumber11 = random(0,25);
              int randNumber12 = random(0,25);

              String test1 = "";
              
//              test1 += randNumber1;
//              test1 += ".";
//              test1 += randNumber4;
//              test1 += ",";
//              test1 += randNumber2;
//              test1 += ".";
//              test1 += randNumber5;
//              test1 += ",";
//              test1 += randNumber3;
//              test1 += ".";
//              test1 += randNumber6;
//              test1 += ",";
//              test1 += randNumber7;
//              test1 += ".";
//              test1 += randNumber10;
//              test1 += ",";
//              test1 += randNumber8;
//              test1 += ".";
//              test1 += randNumber11;
//              test1 += ",";
//              test1 += randNumber9;
//              test1 += ".";
//              test1 += randNumber12;
//              inputString = test1;
//              
              //################################เทสระบบ################################################
              delay(100);
              Serial.print(">");
              Serial.println(inputString);

              

// Get Data 

//              int lastOpen = inputString.lastIndexOf('|');
//              Serial.println(lastOpen);
//              int SecondlastOpen = inputString.lastIndexOf('|', lastOpen -8);
//              Serial.println(SecondlastOpen);

for (int i = 0; i < inputString.length(); i++) {
        // Loop through each character and check if it's a comma
        if (inputString.substring(i, i+1) == ",") {
          // Grab the piece from the last index up to the current position and store it
          value[counter] = inputString.substring(lastIndex, i).toFloat();
          // Update the last position and add 1, so it starts from the next character
          lastIndex = i + 1;
          // Increase the position in the array that we store into
          counter++;
        }

        // If we're at the end of the string (no more commas to stop us)
        if (i == inputString.length() - 1) {
          // Grab the last part of the string from the lastIndex to the end
          value[counter] = inputString.substring(lastIndex, i).toFloat();
        }
      }
      NetpieService();
      // Clear out string and counters to get ready for the next incoming string
      inputString = "";
      counter = 0;
      lastIndex = 0;         
 }
}
