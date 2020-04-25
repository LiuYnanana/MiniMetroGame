#include "MyLogger.h"

MyLogger* MyLogger::m_logger = nullptr;

MyLogger::MyLogger() {
	log4cplus::initialize();
	log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(MY_LOG_FILE_PATH));
	rootLog = log4cplus::Logger::getRoot();
	logger_1 = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("test"));
	std::cout << "!!!" << std::endl;
}

MyLogger* MyLogger::GetInstance() {
	if (m_logger == nullptr) {
		m_logger = new MyLogger();
		std::cout << "GetInstance" << std::endl;
	}
	std::cout << "~~~~" << std::endl;
	return m_logger;
}

MyLogger::~MyLogger() {
	if (m_logger) {
		delete m_logger;
	}
}

