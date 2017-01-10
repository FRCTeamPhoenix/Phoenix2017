/*
 * LoggerController.h
 *
 *  Created on: Oct 17, 2016
 *      Author: connortess
 */

#ifndef SRC_PLOG_LOGGERCONTROLLER_H_
#define SRC_PLOG_LOGGERCONTROLLER_H_

#include "plog/Record.h"
#include "plog/Severity.h"
#include "plog/Util.h"
#include "plog/Init.h"
#include "plog/Log.h"
#include "plog/Logger.h"

class LoggerController
{
public:
    LoggerController();
    virtual ~LoggerController();

    void updateSeverity();
};

#endif /* SRC_PLOG_LOGGERCONTROLLER_H_ */
