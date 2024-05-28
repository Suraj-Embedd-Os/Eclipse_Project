#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

// Function to create a sample JSON object
cJSON* create_sample_json() {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "name", "John Doe");
    cJSON_AddNumberToObject(json, "age", 30);
    cJSON_AddBoolToObject(json, "is_student", 0);
    return json;
}

void json_to_xml_recursive(cJSON *item, FILE *fp) {
    switch (item->type) {
        case cJSON_Object: {
            cJSON *child = item->child;
            while (child) {
                fprintf(fp, "<%s>", child->string);
                json_to_xml_recursive(child, fp);
                fprintf(fp, "</%s>", child->string);
                child = child->next;
            }
            break;
        }
        case cJSON_Array: {
            cJSON *child = item->child;
            while (child) {
                fprintf(fp, "<item>");
                json_to_xml_recursive(child, fp);
                fprintf(fp, "</item>");
                child = child->next;
            }
            break;
        }
        case cJSON_String:
            fprintf(fp, "%s", item->valuestring);
            break;
        case cJSON_Number:
            if (item->valuedouble == item->valueint) {
                fprintf(fp, "%d", item->valueint);
            } else {
                fprintf(fp, "%lf", item->valuedouble);
            }
            break;
        case cJSON_False:
            fprintf(fp, "false");
            break;
        case cJSON_True:
            fprintf(fp, "true");
            break;
        case cJSON_NULL:
            fprintf(fp, "null");
            break;
        default:
            break;
    }
}
void save_json_to_xml_file(cJSON *json, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("File opening failed");
        return;
    }
    fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    json_to_xml_recursive(json, fp);
    fclose(fp);
}

int main() {
    // Create sample JSON object
    cJSON *json = create_sample_json();

    // Save JSON to XML file
    save_json_to_xml_file(json, "output.xml");

    // Clean up
    cJSON_Delete(json);

    return 0;
}

