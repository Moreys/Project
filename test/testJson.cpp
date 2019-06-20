/*************************************************************************
  @FileName:  testJson.cc
  @Author:    morey
  @Email:     zymorey@gmail.com
  @Time:      2019年06月20日 星期四 10时16分48秒
 ************************************************************************/

#include <iostream>
#include <stdio.h>
#include <cJSON.hpp >

char *create_JSON()
{
    char *string = NULL;
    cJSON *resolutions = NULL;
    size_t index = 0;
    const unsigned int resolution_numbers[3][2] = {
        {1024, 768}, 
        {1280, 1024}, 
        {1920, 1080}

    };

    /*创建JSON对象monitor*/
    cJSON *monitor = cJSON_CreateObject();

    /*在monitor对象中添加第一个子条目("name": "MIUI 4K"), 该条目为string类型*/
    if(cJSON_AddStringToObject(monitor, "name", "MIUI 4K") == NULL){
        fprintf(stderr, "cJSON_AddStringToObject failed\n");
        cJSON_Delete(monitor);
        return NULL;

    }

    /*在monitor对象中添加第二个子条目(resolutions), 该条目为数组类型*/
    resolutions = cJSON_AddArrayToObject(monitor, "resolutions");
    if(resolutions == NULL){
        fprintf(stderr, "cJSON_AddArrayToObject failed.\n");
        cJSON_Delete(monitor);
        return NULL;

    }

    /*向resolutions数组对象中添加三个子条目*/
    for(index=0; index<3; ++index){
        /*1.创建JSON对象resolution*/
        cJSON *resolution = cJSON_CreateObject();

        /*2.向resolution对象中添加子条目("width": 1024)*/
        if(cJSON_AddNumberToObject(resolution, "width", resolution_numbers[index][0]) == NULL){
            fprintf(stderr, "cJSON_AddNumberToObject failed.\n");
            cJSON_Delete(monitor);
            return NULL;

        }
        /*3.向resolution对象中添加子条目("height": 768)*/
        if(cJSON_AddNumberToObject(resolution, "height", resolution_numbers[index][1]) == NULL){
            fprintf(stderr, "cJSON_AddNumberToObject failed.\n");
            cJSON_Delete(monitor);
            return NULL;

        }

        /*将resolution对象添加到数组resolutions中*/
        cJSON_AddItemToArray(resolutions, resolution);

    }

    /*将JSON对象写入string对象中*/
    string = cJSON_Print(monitor);
    if(string == NULL){
        fprintf(stderr, "Failed to print monitor.\n");
        cJSON_Delete(monitor);
        return NULL;

    }

    /*释放cJSON对象占用的资源*/
    cJSON_Delete(monitor);
    return string;

}

int main()
{
    char *string;
    string = create_JSON();
    printf("string=\n%s\n", string);

    return 0;

}
