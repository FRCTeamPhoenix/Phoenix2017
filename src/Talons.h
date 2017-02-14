/*
 * Talons.h
 *
 *  Created on: Feb 12, 2017
 *      Author: Ian
 */

#ifndef SRC_TALONS_H_
#define SRC_TALONS_H_

#include "json.hpp"
#include <iostream>
#include "valijson/adapters/nlohmann_json_adapter.hpp"
#include "valijson/utils/nlohmann_json_utils.hpp"
#include "valijson/schema.hpp"
#include "valijson/schema_parser.hpp"
#include "valijson/validator.hpp"

using valijson::Schema;
using valijson::SchemaParser;
using valijson::Validator;
using valijson::adapters::NlohmannJsonAdapter;

using json=nlohmann::json;
using namespace std;

class Talons {

   json m_talonJson;
   json m_schemaJson;

   bool m_status;

   public:
      Talons(string jsonPath, string schemaPath);
      json getTalonConfig(int talonId);
      virtual ~Talons();
};

#endif /* SRC_TALONS_H_ */
