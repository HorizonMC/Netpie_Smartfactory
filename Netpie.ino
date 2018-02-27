void NetpieService(){
  //NPTService();
  float measurefire =  value[0];
  float measurefire_Digital =  value[1];
  float current_quality =  value[2];
  float Irms =  value[4];
  String data = Get_Temp();
  String Air_quality = "";
  String Power = "";
  if (microgear.connected())
    {
       microgear.loop();
       Serial.println("connected");
       data += "/";
       data +=  current_quality;
       microgear.chat("Factory/Sensor/Environment", data);
       
       //microgear.chat("Factory/Sensor/Measurefire", measurefire);
       if(measurefire_Digital == 0)measurefire_Digital =4;
       microgear.chat("Factory/Sensor/Measurefire_Digital", measurefire_Digital);
       
       if (Irms<= 0.36) Irms =0;
       Power += Irms;
       Power += "/";
       Power += 230.0*Irms;
       microgear.chat("Factory/Sensor/Power", Power);

       //microgear.chat("/Factory/SW/Chanel3", String(S_Toggle1));
       if(gettimestamp()!=0)
       {
       microgear.chat("Environment", data);
       
       }else{//Serial.println("GetTime Error");
        }
    }else 
   {
    Serial.println("connection lost, reconnect...");
    microgear.connect(APPID);
   }
}
