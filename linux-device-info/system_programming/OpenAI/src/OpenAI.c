#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON.h"

#define API_KEY "your_openai_api_key"
#define API_URL "https://api.openai.com/v1/completions"

struct string {
    char *ptr;
    size_t len;
};

void init_string(struct string *s) {
    s->len = 0;
    s->ptr = malloc(s->len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s) {
    size_t new_len = s->len + size * nmemb;
    s->ptr = realloc(s->ptr, new_len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "realloc() failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(s->ptr + s->len, ptr, size * nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;

    return size * nmemb;
}

void make_openai_request(const char *prompt) {
    CURL *curl;
    CURLcode res;

    struct string s;
    init_string(&s);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        // Setup headers
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", API_KEY);
        headers = curl_slist_append(headers, auth_header);

        // Create JSON payload
        cJSON *json = cJSON_CreateObject();
        cJSON_AddStringToObject(json, "model", "text-davinci-003");
        cJSON_AddStringToObject(json, "prompt", prompt);
        cJSON_AddNumberToObject(json, "max_tokens", 100);

        char *post_data = cJSON_PrintUnformatted(json);

        // Set CURL options
        curl_easy_setopt(curl, CURLOPT_URL, API_URL);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // Parse JSON response
            cJSON *response_json = cJSON_Parse(s.ptr);
            if (response_json == NULL) {
                fprintf(stderr, "Failed to parse JSON response\n");
            } else {
                cJSON *choices = cJSON_GetObjectItem(response_json, "choices");
                if (choices != NULL) {
                    cJSON *choice = cJSON_GetArrayItem(choices, 0);
                    if (choice != NULL) {
                        cJSON *text = cJSON_GetObjectItem(choice, "text");
                        if (text != NULL) {
                            printf("Response: %s\n", text->valuestring);
                        }
                    }
                }
                cJSON_Delete(response_json);
            }
        }

        // Cleanup
        free(post_data);
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    free(s.ptr);
    curl_global_cleanup();
   // cJSON_Delete(json);
}

int main() {
    const char *prompt = "What is the capital of France?";
    make_openai_request(prompt);
    return 0;
}

