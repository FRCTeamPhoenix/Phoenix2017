/*
 * Talons.h
 *
 *  Created on: Feb 12, 2017
 *      Author: Ian
 */

#ifndef SRC_TALONS_H_
#define SRC_TALONS_H_

#include "json.hpp"
#include "WPILib.h"
#include <iostream>
#include "valijson/adapters/nlohmann_json_adapter.hpp"
#include "valijson/utils/nlohmann_json_utils.hpp"
#include "valijson/schema.hpp"
#include "valijson/schema_parser.hpp"
#include "valijson/validator.hpp"
#include "WPILib.h"

#include "plog/Log.h"

using valijson::Schema;
using valijson::SchemaParser;
using valijson::Validator;
using valijson::adapters::NlohmannJsonAdapter;

using namespace nlohmann;
using namespace std;

class Talons {

   json m_talonJson;
   json m_schemaJson;

   json m_default;

   public:
      Talons(string jsonPath, string schemaPath);
      json getTalonConfig(int talonId);
      void initTalons();
      virtual ~Talons();
      bool m_status;
};

#endif /* SRC_TALONS_H_ */
