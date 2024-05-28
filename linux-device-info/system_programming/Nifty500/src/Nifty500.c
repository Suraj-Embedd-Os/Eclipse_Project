#include <stdio.h>
#include <stdlib.h>
#include <zip.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

void print_xml_content(const char *filename) {
    xmlDoc *doc = xmlReadFile(filename, NULL, 0);
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse %s\n", filename);
        return;
    }
    xmlNode *root_element = xmlDocGetRootElement(doc);
    xmlNode *node = root_element;
    while (node) {
        if (node->type == XML_ELEMENT_NODE) {
            printf("node type: Element, name: %s\n", node->name);
        }
        node = node->next;
    }
    xmlFreeDoc(doc);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename.ods>\n", argv[0]);
        return 1;
    }

    const char *ods_filename = argv[1];
    int err;
    struct zip *za = zip_open(ods_filename, 0, &err);
    if (za == NULL) {
        fprintf(stderr, "Error opening ZIP archive: %d\n", err);
        return 1;
    }

    struct zip_stat st;
    zip_stat_init(&st);
    zip_stat(za, "content.xml", 0, &st);

    char *contents = malloc(st.size);
    if (contents == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        zip_close(za);
        return 1;
    }

    struct zip_file *zf = zip_fopen(za, "content.xml", 0);
    if (zf == NULL) {
        fprintf(stderr, "Failed to open content.xml\n");
        free(contents);
        zip_close(za);
        return 1;
    }

    zip_fread(zf, contents, st.size);
    contents[st.size] = '\0';

    zip_fclose(zf);
    zip_close(za);

    FILE *fp = fopen("content.xml", "w");
    if (fp == NULL) {
        fprintf(stderr, "Failed to create temporary content.xml file\n");
        free(contents);
        return 1;
    }
    fwrite(contents, 1, st.size, fp);
    fclose(fp);

    print_xml_content("content.xml");

    free(contents);
    return 0;
}
