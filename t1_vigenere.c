/*
    Trabalho 1 de segurança computacional
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Gerador de Keystream
char * keystream_generator(char secret_word[1000], char message[1000]) {
    char * extkeyword = malloc(sizeof(char)*1000);
    for(int i = 0, j = 0; i < strlen(message); i++, j++) {
        if(j == strlen(secret_word)) j = 0;
        extkeyword[i] = secret_word[j];
        // Adiciona null byte
        if(i == strlen(message)-1) extkeyword[i+1] = '\0';
    }

    return extkeyword;
}

// Cifrador
char * cifrador(char keystream[1000], char message[1000]) {
    char * encripted = malloc(sizeof(char)*1000);
    int j = 0;
    for( int i = 0; i < strlen(message); i++) {
        if(message[i] != ' ') {
            encripted[j] = ((message[i] + keystream[j]) % 26) + 'A';
            j++;
        }
    }
    
    return encripted;
}

// Decifrador
char * decifrador(char keystream[1000], char encripted_message[1000]){
    char * decripted = malloc(sizeof(char)*1000);
    int j = 0;
    for( int i = 0; i < strlen(encripted_message); i++) {
        if(encripted_message[i] != ' ') {
            decripted[j] = ((encripted_message[i] - keystream[j] + 26) % 26) + 'A';
            j++;
        }
    }
    
    return decripted;
}

char * capitalize(char string[1000]) {
    for (int i = 0; i < strlen(string); i++) {
      if(string[i] >= 'a' && string[i] <= 'z') {
         string[i] = string[i] -32;
      }
      if(!isalpha(string[i])){
          string[i] = ' ';
      }
   }
   return string;
}

int main(){
    char * message = malloc(sizeof(char) * 1000),* keyword = malloc(sizeof(char) * 1000), * keystream = malloc(sizeof(char) * 1000), * encriptedmessage = malloc(sizeof(char) * 1000), * decriptedmessage = malloc(sizeof(char) * 1000);
    char * option = malloc(sizeof(char));
    // Receber keyword e mensagem
    printf("Digite a keyword: ");
    gets(keyword);
    printf("Digite a mensagem: ");
    gets(message);
    keyword = capitalize(keyword);
    message = capitalize(message);
    keystream = keystream_generator(keyword, message);
    printf("Digite 'e' para encriptar e 'd' para decriptar ");
    scanf("%c", option);

    if(*option == 'e'){
        encriptedmessage = cifrador(keystream, message);
        printf("%s\n", encriptedmessage);
    }
    else if(*option == 'd') {
        decriptedmessage = decifrador(keystream, message);
        printf("%s\n", decriptedmessage);
    }

    return 0;
}
