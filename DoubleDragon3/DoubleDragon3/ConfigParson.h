#ifndef __CONFIGPARSON_H__
#define __CONFIGPARSON_H__

#include "parson.h"

#define CONFIG_OBJECT JSON_Object*
#define CONFIG_ARRAY JSON_Array*

#define GET_CONFIG(v) json_value_get_object(json_parse_file(v))

#define CONFIG_OBJECT_OBJECT(o, s) json_object_get_object(o, s)
#define CONFIG_OBJECT_STRING(o, s) json_object_get_string(o, s)
#define CONFIG_OBJECT_ARRAY(o, s) json_object_get_array(o, s)
#define CONFIG_OBJECT_NUMBER(o, s) json_object_get_number(o, s)
#define CONFIG_OBJECT_BOOL(o, s) json_object_get_boolean(o, s)

#define CONFIG_ARRAY_NUMBER(a, i) json_array_get_number(a, i)

#endif //CONFIGPARSON
