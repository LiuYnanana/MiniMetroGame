//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <hiredis.h> //头文件跟随文件存放路径改变
//#include <Win32_Interop\win32fixes.h> //头文件跟随文件存放路径改变
//#pragma comment(lib,"hiredis.lib")
//#pragma comment(lib,"Win32_Interop.lib")
//
//int main() {
//    redisContext* redis = redisConnect("127.0.0.1", 6379);
//    if (redis == NULL || redis->err) {
//        if (redis) {
//            printf("Error: %s\n", redis->errstr);
//            // handle error
//        }
//        else {
//            printf("Can't allocate redis context\n");
//        }
//    }
//    else {
//        printf("connect successed!");
//    }
//    redisReply* reply;
//
//    /* PING server */
//    reply = (redisReply*)redisCommand(redis, "PING");
//    printf("PING: %s\n", reply->str);
//    freeReplyObject(reply);
//
//    reply = (redisReply*)redisCommand(redis, "SET %b %b", "foo", (size_t)3, "ss", (size_t)2);
//    printf("foo: %s\n", reply->str);
//    freeReplyObject(reply);
//    redisFree(redis);
//    system("pause");
//    return 0;
//}
