/*
    Trabalho 1 de segurança computacional
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Gerador de Keystream
char * keystream_generator(char secret_word[20], char message[20]) {
    char * extkeyword = malloc(sizeof(char)*20);
    for(int i = 0, j = 0; i < strlen(message); i++, j++) {
        if(j == strlen(secret_word)) j = 0;
        extkeyword[i] = secret_word[j];
        // Adiciona null byte
        if(i == strlen(message)-1) extkeyword[i+1] = '\0';
    }

    return extkeyword;
}

// Cifrador
char * cifrador(char keystream[20], char message[20]) {
    char * encripted = malloc(sizeof(char)*20);

    for( int i = 0; i < strlen(message); i++) {
        if(message[i] == ' ') {
            encripted[i] = ' ';
        }
        else {
        encripted[i] = ((message[i] + keystream[i]) % 26) + 'A';
        }
    }
    
    return encripted;
}

// Decifrador
char * decifrador(char keystream[20], char encripted_message[20]){
    char * decripted = malloc(sizeof(char)*20);

    for( int i = 0; i < strlen(encripted_message); i++) {
        if(encripted_message[i] == ' ') {
            decripted[i] = ' ';
        }
        else {
        decripted[i] = ((encripted_message[i] - keystream[i] + 26) % 26) + 'A';
        }
    }
    
    return decripted;
}

char * capitalize(char string[20]) {
    for (int i = 0; i < strlen(string); i++) {
      if(string[i] >= 'a' && string[i] <= 'z') {
         string[i] = string[i] -32;
      }
   }
   return string;
}

int main(){
    char * message = malloc(sizeof(char) * 20),* keyword = malloc(sizeof(char) * 20), * keystream = malloc(sizeof(char) * 20), * encriptedmessage = malloc(sizeof(char) * 20), * decriptedmessage = malloc(sizeof(char) * 20);
    // Receber keyword e mensagem
    printf("Digite a keyword: ");
    gets(keyword);
    printf("Digite a mensagem: ");
    gets(message);

    keyword = capitalize(keyword);
    message = capitalize(message);
    
    // Montar a Keystream
    keystream = keystream_generator(keyword, message);

    printf("%s\n", keystream);

    // Encriptar e decriptar
    encriptedmessage = cifrador(keystream, message);
    decriptedmessage = decifrador(keystream, encriptedmessage);
    printf("%s\n", encriptedmessage);
    printf("%s\n", decriptedmessage);

    return 0;
}
