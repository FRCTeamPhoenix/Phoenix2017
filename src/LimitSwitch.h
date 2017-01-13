#pragma once

#include "WPILib.h"

class LimitSwitch : public DigitalInput
{
public:
  LimitSwitch(uint32_t channel);
  ~LimitSwitch(void);
  bool get(void);
};
