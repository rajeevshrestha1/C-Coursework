#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* test_1_en(char a[])
 {
    int j, k = strlen(a);
    int x = 1;
    for (j = 0; j < k; j++)
        {
            a[j] = a[j] - x++;
            if (x > 5)
             {
                x = 1;
             }
        }
    return a;
}

char* test_1_de(char a[])
 {
    int j, k = strlen(a);
    int x = 1;
    for (j = 0; j < k; j++)
        {
            a[j] = a[j] + x++;
            if (x > 5)
              {
                x = 1;
              }
        }
    return a;
}

char* read_file(const char* fname, size_t* size) {
    FILE *file = fopen(fname, "rb");
    if (!file) {
        printf("\n File not found! \n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    rewind(file);

    char *content = (char*)malloc((*size + 1) * sizeof(char));
    if (!content) {
        printf("\n Memory allocation error! \n");
        fclose(file);
        return NULL;
    }

    fread(content, 1, *size, file);
    content[*size] = '\0';
    fclose(file);

    return content;
}

void write_file(const char* fname, const char* content) {
    FILE *file = fopen(fname, "wb");
    if (!file) {
        printf("Try again!\n");
        return;
    }
    fwrite(content, sizeof(char), strlen(content), file);
    fclose(file);
}

void encrypt_file(const char* fname)
{
    size_t size;
    char *content = read_file(fname, &size);
    if (!content)
        {
        return;
        }

    char *encrypted_content = test_1_en(content);
    write_file(fname, encrypted_content);

    free(content);
    printf("\n Successfully Encrypted. \n");
}

void decrypt_file(const char* fname)
{
    size_t size;
    char *content = read_file(fname, &size);
    if (!content)
        {
        return;
        }

    char *decrypted_content = test_1_de(content);
    write_file(fname, decrypted_content);

    free(content);
    printf("\n Successfully Decrypted. \n");
}

int main()
{
    while (1)
     {
        int choose = 0;
        printf("\n Welcome to the file encryption tools. \n\n\n");
        printf(" 1. Encrypt \n");
        printf(" 2. Decrypt \n");
        printf(" 3. Exit \n");
        printf("\n Please enter your option: ");
        scanf("%d", &choose);
        getchar();
        if (choose == 3)
        {
            break;
        }

        char fname[100];
        printf("Enter a filename: ");
        fgets(fname, sizeof(fname), stdin);
        fname[strcspn(fname, "\n")] = '\0';
        switch (choose)
        {
            case 1:
                encrypt_file(fname);
                break;
            case 2:
                decrypt_file(fname);
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
        break;
    }
    return 0;
}
