#define _XOPEN_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
//#include <cs50.h>

int main(int argc, char *argv[])
{
    char const *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int alphabet_len = 52;
    char const *hash;
    if(argc == 2) {
      hash = argv[1];
    } else {
      hash = "abFZSxKKdq5s6";
    }

    char password[6] = "\0\0\0\0\0\0";
    char salt[3];
    //memcpy(salt, hash, 2);
    salt[0] = hash[0];
    salt[1] = hash[1];
    salt[2] = '\0';

    bool flag = false;

    for(int i = 0; i < alphabet_len; i++)
    {
        password[0] = alphabet[i];
        password[1] = password[2] = password[3] = password[4] = '\0';
        if(!strcmp(hash, crypt(password, salt)))
        {
            flag = true;
            break;
        }
        for(int j = 0; j < alphabet_len; j++)
        {
            password[1] = alphabet[j];
            password[2] = password[3] = password[4] = '\0';
            if(!strcmp(hash, crypt(password, salt)))
            {
                flag = true;
                break;
            }
            for(int k = 0; k < alphabet_len; k++)
            {
                password[2] = alphabet[k];
                password[3] = password[4] = '\0';
                if(!strcmp(hash, crypt(password, salt)))
                {
                    flag = true;
                    break;
                }
                for(int l = 0; l < alphabet_len; l++)
                {
                    password[3] = alphabet[l];
                    password[4] = '\0';
                    if(!strcmp(hash, crypt(password, salt)))
                    {
                        flag = true;
                        break;
                    }
                    for(int m = 0; m < alphabet_len; m++)
                    {
                        password[4] = alphabet[m];
                        if(!strcmp(hash, crypt(password, salt)))
                        {
                            flag = true;
                            break;
                        }
                    }
                    if(flag)
                        break;
                }
                if(flag)
                    break;
            }
            if(flag)
                break;
        }
        if(flag)
            break;
    }

    if(flag)
        printf("Password: %s\n", password);
    else
        printf("Password not found\n");
}
