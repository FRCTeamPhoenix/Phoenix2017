/*
 * UndecoratedFormatter.h
 *
 *  Created on: Jan 1, 2017
 *      Author: Will
 */

#ifndef SRC_UNDECORATEDFORMATTER_H_
#define SRC_UNDECORATEDFORMATTER_H_

#include "plog/Log.h"

namespace plog
{

class UndecoratedFormatter
{
public:
    static util::nstring header();
    static util::nstring format(const Record& record);
};

} /* namespace plog */

#endif /* SRC_UNDECORATEDFORMATTER_H_ */
