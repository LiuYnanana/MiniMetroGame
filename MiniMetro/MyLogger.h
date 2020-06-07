#pragma once
#include <string>
#include <windows.h>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h> 
#include <log4cplus/layout.h> 
#include <log4cplus/loggingmacros.h> 
#include <log4cplus/helpers/stringhelper.h> 
#include <iostream>

#define MY_LOG_FILE_PATH "E:\\MiniMetro\\MiniMetroGame\\log\\logconfig.property"
extern bool end;
class MyLogger
{
public:
	MyLogger();
	static MyLogger* GetInstance();
	~MyLogger();
	log4cplus::Logger rootLog;
	log4cplus::Logger logger_1;
private:
	static MyLogger* m_logger;
};


