/*
 * ConfigEditor.cpp
 *
 *  Created on: Jan 23, 2016
 *      Author: ben
 */

#include "ConfigEditor.h"

ConfigEditor::ConfigEditor()
{
   // TODO Auto-generated constructor stub
}

ConfigEditor::~ConfigEditor() {
   // TODO Auto-generated destructor stub
}

void ConfigEditor::getConfig() {
   std::string keyName = SmartDashboard::GetString(DriveStationConstants::textBoxNames[10],"");

   int pos = -1;
   for(int i=0;i<ConfigVariables::numberOfVars;i++) {
      if(keyName == ConfigVariables::variables[i]) {
         pos = i;
         break;
      }
   }

   if(pos == -1) {
      std::cout << "Key entered was not a valid variables" << std::endl;
      return;
   }

   std::string type = ConfigVariables::types[pos];

   if(type == "int") {
      std::ostringstream ss;
      ss << Preferences::GetInstance()->GetInt(keyName, 0);
      SmartDashboard::PutString(DriveStationConstants::textBoxNames[11], ss.str());
   } else if(type == "float") {
      std::stringstream ss;
      ss << Preferences::GetInstance()->GetFloat(keyName, 0);
      SmartDashboard::PutString(DriveStationConstants::textBoxNames[11], ss.str());
   } else if(type == "double") {
      std::stringstream ss;
      ss << Preferences::GetInstance()->GetDouble(keyName, 0);
      SmartDashboard::PutString(DriveStationConstants::textBoxNames[11], ss.str());
   } else {
      SmartDashboard::PutString(DriveStationConstants::textBoxNames[11], Preferences::GetInstance()->GetString(keyName, 0));
   }
}

int ConfigEditor::getInt(std::string key, int defaultValue) {
   return Preferences::GetInstance()->GetInt(key, defaultValue);
}

float ConfigEditor::getFloat(std::string key, float defaultValue) {
   return Preferences::GetInstance()->GetFloat(key, defaultValue);
}

double ConfigEditor::getDouble(std::string key, double defaultValue) {
   return Preferences::GetInstance()->GetDouble(key, defaultValue);
}

std::string ConfigEditor::getString(std::string key, std::string defaultValue) {
   return Preferences::GetInstance()->GetString(key, defaultValue);
}

void ConfigEditor::saveConfig() {
   std::string keyName = Preferences::GetInstance()->GetString(DriveStationConstants::textBoxNames[10], "");
   std::string newValue = Preferences::GetInstance()->GetString(DriveStationConstants::textBoxNames[12], "");

   int pos = -1;
   for(int i=0;i<ConfigVariables::numberOfVars;i++) {
      if(keyName == ConfigVariables::variables[i]) {
         pos = i;
         break;
      }
   }

   if(pos == -1) {
      std::cout << "Key entered was not a valid variable" << std::endl;
      return;
   }

   std::string type = ConfigVariables::types[pos];

   if(! isType(newValue,type))
      return;

   if(type == "int") {
      Preferences::GetInstance()->PutInt(keyName, std::stoi(newValue));
   } else if(type == "float") {
      Preferences::GetInstance()->PutFloat(keyName, std::stof(newValue));
   } else if(type == "double") {
      Preferences::GetInstance()->PutDouble(keyName, std::stod(newValue));
   } else {
      Preferences::GetInstance()->PutString(keyName, newValue);
   }
}

bool ConfigEditor::isType(std::string str, std::string type){
   if(type == "int"){
      try{
         std::stoi(str);
      }
      catch(std::invalid_argument& e){
         return false;
      }
   }
   else if(type == "float"){
         try{
            std::stof(str);
         }
         catch(std::invalid_argument& e){
            return false;
         }
      }

   else if(type == "double"){
         try{
            std::stod(str);
         }
         catch(std::invalid_argument& e){
            return false;
         }
      }
return true;
}

void ConfigEditor::showAllKeys(){
   std::string final = "";
   for(int i=0; i<ConfigVariables::numberOfVars; i++){
      final+=ConfigVariables::variables[i]+"     "+ConfigVariables::types[i]+"\n";
   }
   std::cout<<final<<std::endl;
   SmartDashboard::PutString("Keys",final);
}

void ConfigEditor::update() {
   for (int i = 0; i < 6; i++) {
      if (SmartDashboard::GetBoolean(DriveStationConstants::dashButtonNames[i], false)) {
         SmartDashboard::PutBoolean(DriveStationConstants::dashButtonNames[i], false);
         std::cout << "Button was pressed" << std::endl;

         if(i==5) {
            std::cout << "reached stage one" << std::endl;
            saveConfig();
            std::cout << "reached stage two with " << Preferences::GetInstance()->GetInt("teamNumber",481516) << std::endl;
         }
         if(i==4) {
            getConfig();
         }
      }
   }

}
