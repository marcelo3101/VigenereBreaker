#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_KEY_LENGTH_GUESS 20
#define ALPHABET_LENGTH 26

void remove_spaces(char* s) {
  const char* d = s;
  do {
      while (*d == ' ') {
          ++d;
      }
  } while (*s++ = *d++);
}

void lower_case(char* s) {
  for(int i = 0; s[i]; i++){
    s[i] = tolower(s[i]);
  } 
}

int numberOfOcurrences(char letter, char * string) {
  int counter = 0;
  for(int i = 0; i < strlen(string); i++) {
    if (string[i] == letter) {
      counter++;
    }
  }
    return counter;
}

float get_ic(char * sequence) {
  float sequenceLength = strlen(sequence);
  float frequencySum = 0.0;

  for(int i = 'a'; i < 'a' + ALPHABET_LENGTH; i++) {
    char test = (char*) i;
    frequencySum += numberOfOcurrences((char*) i, sequence) * (numberOfOcurrences((char*) i, sequence) - 1);
  }
  return frequencySum / (sequenceLength * (sequenceLength - 1));
}

void guessKeyLength (char * cipherText) {
  float icSum = 0.0;
  for(int i = 1; i <= MAX_KEY_LENGTH_GUESS; i++){
    char * sequence = malloc(sizeof(char) * 200);
    int counter = 0;
    for(int j = 0; j < strlen(cipherText); j=j+i){
      sequence[counter] = cipherText[j];
      counter++;
    }
    icSum += get_ic(sequence);
    // printf("%f", get_ic(sequence));
    printf("%i %f\n", i, icSum/i);
  }
}

int main(){
  char * cipherText = malloc(sizeof(char) * 200);

  printf("Digite a mensagem cifrada: ");
  gets(cipherText);
  // printf("Informe a língua da mensagem \"es\" para inglês e \"pt\" para português: ");
  // gets(language);
  
  remove_spaces(cipherText);
  lower_case(cipherText);

  guessKeyLength(cipherText);
  return 0;
}
