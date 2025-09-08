#include <jansson.h>
#include <stdio.h>

int main() {
    char* string = "{ \"key\": \"value\" }";

    json_error_t error;
    json_t* root = json_loads(string, 0, &error); //obtaining a pointer
    json_t* value = json_object_get(root, "key"); //obtaining a pointer
    printf("\"%s\" is the value field.\n", json_string_value(value)); //use value

    json_decref(value); //Do I free this pointer?
    json_decref(root);  //What about this one? Does the order matter?
    return 0;
}
