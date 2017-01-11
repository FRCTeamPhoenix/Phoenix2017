/*
 * ConfigEditor.h
 *
 *  Created on: Jan 23, 2016
 *      Author: ben
 */

#ifndef SRC_CONFIGEDITOR_H_
#define SRC_CONFIGEDITOR_H_

#include <iostream>

#include "constants.h"
#include "WPILib.h"

using namespace std;

class ConfigEditor {
public:
   ConfigEditor();
   virtual ~ConfigEditor();
   void update();

   void saveConfig();
   void getConfig();
   bool isType(std::string str, std::string type);
   void showAllKeys();

   int getInt(std::string key, int defaultValue = 0);
   float getFloat(std::string key, float defaultValue = 0.0f);
   double getDouble(std::string key, double defaultValue = 0.0);
   std::string getString(std::string key, std::string defaultValue = "");
};

#endif /* SRC_CONFIGEDITOR_H_ */
