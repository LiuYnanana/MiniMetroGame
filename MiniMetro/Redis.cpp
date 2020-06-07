#include "redis.h"
Redis::Redis() {

}

bool Redis::connect(std::string host, int port)
{
    this->m_redis = redisConnect(host.c_str(), port);
    if (this->m_redis != NULL && this->m_redis->err)
    {
        printf("connect error: %s\n", this->m_redis->errstr);
        return false;
    }
    return true;
}


std::vector<std::string> Redis::GetList(std::string key)
{
    redisReply* reply;
    reply = (redisReply*)redisCommand(m_redis, "LLEN %s", key.c_str());
    int valueSize = reply->integer;
    std::cout << "List size is :" << reply->integer << std::endl;

    reply = (redisReply*)redisCommand(m_redis, "LRANGE %s %d %d", key.c_str(), 0, valueSize - 1);
    std::cout << "get list type = " << reply->type << std::endl;
    std::cout << "get list size = " << reply->elements << std::endl;//对于数组类型可以用elements元素获取数组长度

    redisReply** replyVector = reply->element;//获取数组指针
    std::vector<std::string> result;
    for (int i = 0; i < valueSize; i++)
    {
        std::string temp = (*replyVector)->str;//遍历redisReply*数组,存入vector向量
        //int a = atoi(temp.c_str());
        result.push_back(temp);
        replyVector++;
    }

    std::cout << "result size:" << result.size() << std::endl;
    return result;

}

void Redis::PushList(std::string list_name, std::string data)
{
    redisReply* reply;
    std::cout << list_name.c_str() << std::endl;
    reply = (redisReply*)redisCommand(m_redis, "rpush %s %s", list_name.c_str(), data.c_str());
}

Redis::~Redis()
{
    this->m_redis = NULL;
}