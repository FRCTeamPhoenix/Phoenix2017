/*
 * UndecoratedFormatter.cpp
 *
 *  Created on: Jan 1, 2017
 *      Author: Will
 */

#include "UndecoratedFormatter.h"

namespace plog
{
    util::nstring UndecoratedFormatter::header()
    {
        return util::nstring();
    }

    util::nstring UndecoratedFormatter::format(const Record& record)
    {
        util::nstringstream ss;
        ss << record.getMessage() << "\n";

        return ss.str();
    }

} /* namespace plog */
