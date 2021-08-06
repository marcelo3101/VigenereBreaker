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
        encripted[i] = ((message[i] + keystream[i]) % 26) + 'A';
    }
    
    return encripted;
}

// Decifrador
char * decifrador(char keystream[20], char encripted_message[20]){
    char * decripted = malloc(sizeof(char)*20);

    for( int i = 0; i < strlen(encripted_message); i++) {
        decripted[i] = ((encripted_message[i] - keystream[i] + 26) % 26) + 'A';
    }
    
    return decripted;
}

int main(){
    char message[20], keyword[20], * keystream = malloc(sizeof(char) * 20), * encriptedmessage = malloc(sizeof(char) * 20), * decriptedmessage = malloc(sizeof(char) * 20);
    // Receber keyword e mensagem
    printf("Digite a keyword: ");
    scanf("%s", &keyword);
    printf("Digite a mensagem: ");
    scanf("%s", &message);
    
    // Montar a Keystream
    keystream = keystream_generator(keyword, message);

    // Encriptar e decriptar
    encriptedmessage = cifrador(keystream, message);
    decriptedmessage = decifrador(keystream, encriptedmessage);
    printf("%s\n", encriptedmessage);
    printf("%s\n", decriptedmessage);

    return 0;
}
