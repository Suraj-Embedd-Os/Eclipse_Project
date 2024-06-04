#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE  256  // Increase buffer size to handle larger fields

struct nifty_filed {
    char name[BUF_SIZE];
    char nse_code[BUF_SIZE];
    char industries[BUF_SIZE];
    char cmp_to_iv[BUF_SIZE];
    char price_to_book[BUF_SIZE];
    char market_capitalizations[BUF_SIZE];
    char pe[BUF_SIZE];
    char industry_pe[BUF_SIZE];
    char peg[BUF_SIZE];
    char current_price[BUF_SIZE];
};

const char *file_name = "./nifty-500.csv";

int main(int argc, char *argv[]) {
    FILE *fp = fopen(file_name, "r");

    if (fp == NULL) {
        perror("Unable to open file");
        return -1;
    }

    char buff[1024];
    struct nifty_filed nifty;

    // Skip the header line if your CSV has one
    if (fgets(buff, sizeof(buff), fp) == NULL) {
        perror("Unable to read the header line");
        fclose(fp);
        return -1;
    }

    while (fgets(buff, sizeof(buff), fp) != NULL) {
        // Initialize all buffers to zero
        memset(&nifty, 0, sizeof(nifty));

        // Adjust sscanf format to match the CSV fields correctly
        int fields = sscanf(buff, " %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,\n]",
                            nifty.name, nifty.nse_code, nifty.industries, nifty.current_price, nifty.cmp_to_iv,
                            nifty.price_to_book, nifty.market_capitalizations, nifty.pe, nifty.industry_pe, nifty.peg);

        // Print fields only if the correct number of fields are read
        if (fields == 11) {
            printf("Name: %s\nNSE Code: %s\nIndustries: %s\nCurrent Price: %s\nCMP to IV: %s\nPrice to Book: %s\nMarket Capitalizations: %s\nPE: %s\nIndustry PE: %s\nPEG: %s\n\n",
                   nifty.name, nifty.nse_code, nifty.industries, nifty.current_price, nifty.cmp_to_iv,
                   nifty.price_to_book, nifty.market_capitalizations, nifty.pe, nifty.industry_pe, nifty.peg);
        } else {
            printf("Error parsing line: %s\n", buff);
        }
    }

    fclose(fp);
    return 0;
}
