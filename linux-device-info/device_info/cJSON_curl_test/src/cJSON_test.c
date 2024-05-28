#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON.h"

void create_and_send_json() {
    // Create JSON object using cJSON
    cJSON *json = cJSON_CreateObject();
    if (json == NULL) {
        fprintf(stderr, "Failed to create JSON object\n");
        return;
    }

    // Add data to JSON object
    cJSON_AddStringToObject(json, "name", "John Doe");
    cJSON_AddNumberToObject(json, "age", 30);
    cJSON_AddBoolToObject(json, "is_student", 0);

    // Convert JSON object to string
    char *json_string = cJSON_Print(json);
    if (json_string == NULL) {
        fprintf(stderr, "Failed to print JSON object\n");
        cJSON_Delete(json);
        return;
    }

    // Initialize CURL
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to initialize CURL\n");
        free(json_string);
        cJSON_Delete(json);
        return;
    }

    // Set CURL options
    curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8080/");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_string);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, "Content-Type: application/json");

    // Perform the request, res will get the return code
    CURLcode res = curl_easy_perform(curl);

    // Check for errors
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else {
        printf("JSON data sent: %s\n", json_string);
    }

    // Clean up
    curl_easy_cleanup(curl);
    free(json_string);
    cJSON_Delete(json);
}

int main() {
    create_and_send_json();
    return 0;
}
