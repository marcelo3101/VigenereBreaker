/*
    Trabalho 1 de segurança computacional
*/
#include <stdio.h>
#include <string.h>


// Cifrador
void cifrador(char keyword[20], char message[20]) {
    char extkeyword[20], encripted[20];
    // Montar Keystream
    for(int i = 0, j = 0; i < strlen(message); i++, j++) {
        if(j == strlen(keyword)) j = 0;

        extkeyword[i] = keyword[j];

        if(i == strlen(message)-1) extkeyword[i+1] = '\0';
    }

    printf("%s\n", extkeyword);

    for( int i = 0; i < strlen(message); i++) {
        char x = ((message[i] + extkeyword[i]) % 26) + 'A';
        encripted[i] = x;
    }
    
    printf("%s\n", encripted);
}

int main(){
    // Receber keyword e mensagem
    char message[20], keyword[20];
    printf("Digite a keyword: ");
    scanf("%s", &keyword);
    printf("Digite a mensagem: ");
    scanf("%s", &message);
    cifrador(keyword, message);

    return 0;
}