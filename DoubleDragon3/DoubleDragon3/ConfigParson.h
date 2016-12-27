#ifndef __CONFIGPARSON_H__
#define __CONFIGPARSON_H__

#include "parson.h"

#define CONFIG_OBJECT JSON_Object*

#define GET_CONFIG(v) json_value_get_object(json_parse_file(v))

#define CONFIG_STRING(o, s) json_object_get_string(o, s)

#endif //CONFIGPARSON
