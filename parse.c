#include "quiz.h"
#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>

extern int parse(char *json, quiz_t *quiz) {
struct json_object *parsed_json;
struct json_object *question; 
struct json_object *answer;
parsed_json = json_tokener_parse(json);
if(!json_object_object_get_ex(parsed_json, "text", &question)) return -1;
if(!json_object_object_get_ex(parsed_json, "number", &answer)) return -1;
quiz->text = (char*)json_object_get_string(question);
quiz->number = json_object_get_int(answer);
return 0;
}

