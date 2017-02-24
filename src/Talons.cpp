/*
55 * Talons.cpp
 *
 *  Created on: Feb 12, 2017
 *      Author: Ian
 */

#include "Talons.h"

Talons::Talons(string jsonPath, string schemaPath) {
   ifstream jsonStream;
   ifstream schemaStream;

   m_default = "{\"speed\": {"
         "\"p\": 0,"
         "\"i\": 0,"
         "\"d\": 0,"
         "\"izone\": 0,"
         "\"ff\": 0,"
         "\"rr\": 0"
      "},"
      "\"distance\": {"
         "\"p\": 0,"
         "\"i\": 0,"
         "\"d\": 0,"
         "\"izone\": 0,"
         "\"ff\": 0,"
         "\"rr\": 0"
      "},"
      "\"maxfvel\": 0,"
      "\"maxrvel\": 0,"
      "\"inverted\": false}"_json;
   m_status = true;

   initTalons();

}

void Talons::initTalons() {
   try
      {
         if(!valijson::utils::loadDocument("/home/lvuser/schemas/talons.schema",
                                           m_schemaJson))
         {
            SmartDashboard::PutString("DB/String 2", "LOAD FAILED talons.schema");
            throw std::runtime_error("Failed to load schema document");
         }

         Schema schema;
         SchemaParser parser;
         NlohmannJsonAdapter schemaAdapter(m_schemaJson);
         parser.populateSchema(schemaAdapter, schema);

         if(!valijson::utils::loadDocument("/home/lvuser/config/talons_validated.json",
                                           m_talonJson))
         {
            SmartDashboard::PutString("DB/String 2", "LOAD FAILED talons.json");
            throw std::runtime_error("Failed to load json document");
         }

         Validator validator;
         NlohmannJsonAdapter jsonAdapter(m_talonJson);

         if(!validator.validate(schema, jsonAdapter, NULL))
         {
            SmartDashboard::PutString("DB/String 2", "VALIDATE FAILED talons.json");
            throw std::runtime_error("Failed to validate json document.");
         }
      }
      catch(runtime_error& runtime)
      {
         cout << runtime.what() << endl;

         m_status = false;

         return;
      }
}

json Talons::getTalonConfig(int talonId) {
   try {
      if(m_status)
         return m_talonJson[talonId - 1];
      else
         return m_default;
   } catch(out_of_range& error) {
      cout << error.what() << endl;
      return m_default;
   }
}

Talons::~Talons() {

}

