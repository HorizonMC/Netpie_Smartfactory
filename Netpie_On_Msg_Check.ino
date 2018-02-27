void On_Msg_Check(char *topic,String stateStr){
  //เช็คคำสั่งจากที่ได้รับจาก NETPIE Freeboard
  String ck_str;
  bool ReCheck = false;
if (strcmp (topic,"/SmartFactoryPilot/Factory/SW/Chanel1") == 0)
  {
    if(stateStr == "1"){
      if(digitalRead(D2)!= 1)
      {
        digitalWrite(D2, HIGH);
        Serial.println("On Toggle1");
        Ck_chanel[0] = "1";
        //microgear.chat("/Factory/SW/Chanel1", "1");
      }
    
    }else if(stateStr == "0")
    {
      if(digitalRead(D2)!= 0)
      {
        digitalWrite(D2, LOW);
        Serial.println("Off Toggle1");
        Ck_chanel[1] = "0";
        //microgear.chat("/Factory/SW/Chanel1", "0");
      }
    }else if(stateStr == "?"){
    S_Toggle1 = digitalRead(D2);
    Serial.println(S_Toggle1);
    ck_str = String(S_Toggle1);
    Serial.println("Check Toggle1");
    microgear.publish("/Factory/SW/Chanel1",ck_str);

    ReCheck = true;
    }
  }
  if (strcmp (topic,"/SmartFactoryPilot/Factory/SW/Chanel2") == 0)
  {
    if(stateStr == "1"){
      if(digitalRead(D5)!= 1)
      {
        digitalWrite(D5, HIGH);
        Serial.println("On Toggle2");
        Ck_chanel[2] = "1";
//    microgear.chat("/Factory/SW/Chanel2", "1");
      }
    
    }else if(stateStr == "0"){
      if(digitalRead(D5)!= 0)
      {
        digitalWrite(D5, LOW);
        Serial.println("Off Toggle2");
        Ck_chanel[2] = "0";
//        microgear.chat("/Factory/SW/Chanel2", "0");
      }
    
    }else if(stateStr == "?"){
    S_Toggle2 = digitalRead(D5);
    Serial.println(S_Toggle2);
    ck_str = String(S_Toggle2);
    Serial.println("Check Toggle2");
    microgear.publish("/Factory/SW/Chanel2",ck_str);

    ReCheck = true;
    }
  }
  
  if (strcmp (topic,"/SmartFactoryPilot/Factory/SW/Chanel3") == 0)
  {
    if(stateStr == "1"){
      if(digitalRead(D6)!= 1)
       {
        digitalWrite(D6, HIGH);
        Serial.println("On Toggle3");
        Ck_chanel[3] = "1";
        //microgear.chat("/Factory/SW/Chanel3", "1");
       }
    }else if(stateStr == "0"){
      if(digitalRead(D6)!= 0)
       {
        digitalWrite(D6, LOW);
        Serial.println("Off Toggle3");
        Ck_chanel[3] = "0";
        //microgear.chat("/Factory/SW/Chanel3", "0");
       }
    
    }else if(stateStr == "?"){
    S_Toggle3 = digitalRead(D6);
    Serial.println(S_Toggle3);
    ck_str = String(S_Toggle3);
    Serial.println("Check Toggle3");
    microgear.publish("/Factory/SW/Chanel3",ck_str);

    ReCheck = true;
    }
  }
  if (strcmp (topic,"/SmartFactoryPilot/Factory/SW/Chanel4") == 0)
  {
    if(stateStr == "1"){
      if(digitalRead(D8)!= 1)
       {
        digitalWrite(D8, HIGH);
        Serial.println("On Toggle4");
        Ck_chanel[4] = "1";
        //microgear.chat("/Factory/SW/Chanel4", "1");
       }
    
    }else if(stateStr == "0"){
      if(digitalRead(D8)!= 0)
       {
        digitalWrite(D8, LOW);
        Serial.println("Off Toggle4");
        Ck_chanel[4] = "0";
        //microgear.chat("/Factory/SW/Chanel4", "0");
       }
    
    }else if(stateStr == "?"){
    S_Toggle4 = digitalRead(D8);
    Serial.println(S_Toggle4);
    ck_str = String(S_Toggle4);
    Serial.println("Check Toggle4");
    
    microgear.publish("/Factory/SW/Chanel4",ck_str);

    ReCheck = true;
    
    }
  }
  if (strcmp (topic,"/SmartFactoryPilot/Blower") == 0)
  {
    if(stateStr == "1"){
      if(digitalRead(D7)!= 1)
       {
        digitalWrite(D7, HIGH);
        Serial.println("On Blower");
        Ck_chanel[5] = "0";
        //microgear.chat("/Blower", "1");
       }
    
    }else if(stateStr == "0"){
      if(digitalRead(D7)!= 0)
       {
        digitalWrite(D7, LOW);
        Serial.println("Off Blower");
        Ck_chanel[5] = "0";
        //microgear.chat("/Blower", "0");
       }
    }
  }
  if (ReCheck == true){
    S_Blower = digitalRead(D7);
    Serial.println(S_Blower);
    ck_str = String(S_Blower);
    Serial.println("Check Blower");
    microgear.publish("/Blower",ck_str);
  }
  
  
}

