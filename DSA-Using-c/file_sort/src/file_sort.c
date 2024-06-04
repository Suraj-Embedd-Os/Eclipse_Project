
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_ROW 510
struct file
{
	char col0[50];
	char col1[50];
	char col2[50];
	char col3[50];
	char col4[50];
	char col5[50];
	char col6[50];
	char col7[50];
	char col8[50];
	char col9[50];
	char col10[50];
	char col11[50];
	char col12[50];
};

void sort_file(struct file row[], int count)
{
	for (int i=1;i<count;i++)
	{
		for (int j=i+1;j<count;j++)
		{
			int cmp = strcmp(row[i].col2,row[j].col2);
			if (cmp > 0 || (cmp == 0 && strcmp(row[i].col0,row[j].col0) > 0))
			{
				struct file temp = row[i];
				row[i] = row[j];
				row[j] = temp;
			}
		}
	}
}

int main()
{
	struct file row[MAX_ROW];
	int count = 0;
	char line[1000];
	FILE *fp;
	fp = fopen("./file.csv","r");
	if(fp==NULL){
		printf("Error!!File not found");
		exit(1);
	}

	while(fgets(line,sizeof(line),fp)){
		sscanf(line, " %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,\n]", row[count].col0, row[count].col1, row[count].col2,row[count].col3, row[count].col4, row[count].col5, row[count].col6, row[count].col7, row[count].col8, row[count].col9, row[count].col10, row[count].col11, row[count].col12);
		count++;
	}
	fclose(fp);

	sort_file(row,count);

	FILE *new;
	new = fopen("./today.csv","w");
	if(new == NULL){
		printf("Error!!File not found");
		exit(1);
	}
	for(int i=0;i<count;i++){
		fprintf(new,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",row[i].col0, row[i].col1, row[i].col2, row[i].col3, row[i].col4, row[i].col5, row[i].col6, row[i].col7, row[i].col8, row[i].col9, row[i].col10, row[i].col11, row[i].col12);
	}
	fclose(new);
	printf("Data saved to new file");

	return 0;
}
