#pragma once
#include <iostream>
#include <string>
#include <hiredis.h> 
#include <vector>
class Redis
{
public: 
    Redis();
    bool connect(std::string, int port);
    std::vector<std::string> GetList(std::string);
    void PushList(std::string, std::string);
    ~Redis();
    

private:
    redisContext* m_redis;

};

