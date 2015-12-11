#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char** argv) {
  int i, n;
  char plaintext[10000], otpkey[10000], encrypted[10000];
  FILE* file;

  //open the plaintext file with read priveleges
  file = fopen(argv[1], "r");
  //get the first 10000 characters in the file and put them in plaintext
  fgets(plaintext, 10000, file);
  //close the file
  fclose(file);

  //open the key file with read priveleges
  file = fopen(argv[2], "r");
  //get the first 10000 characters in the file and put them in otpkey
  fgets(otpkey, 10000, file);
  //close the file
  fclose(file);

  //formatting
  printf("\n================ENCRYPTING================\n");

  //now we have the contents of the plaintext and key files to play around with
  //print the contents of the plaintext file
  printf("plaintext file contents: %s", plaintext);
  printf("      key file contents: %s", otpkey);

  //formatting
  printf("\n\n");

  //now lets print the plaintext and key as ascii values
  //first, plaintext
  printf("plaintext as ascii: ");
  //print out each letter as a number
  for(i=0; i<10000; i++) {
    //if the character is a newline character, we have reached the end of the
    //file, so we want to print a newline character and break out of the loop
    if(plaintext[i] == '\n') {
      printf("\n");
      break;
    }
    //prints out the i-th element in the array followed by a space
    printf("%d ", plaintext[i]);
  }

  //next, the key
  printf("      key as ascii: ");
  //print out each letter as a number
  for(i=0; i<10000; i++) {
    //if the character is a newline character, we have reached the end of the
    //file, so we want to print a newline character and break out of the loop
    if(otpkey[i] == '\n') {
      printf("\n");
      break;
    }
    //prints out the i-th element in the array followed by a space
    printf("%d ", otpkey[i]);
  }

  //formatting
  printf("\n\n");

  //to make the encryption process easier, lets convert each letter to 0-25 and
  //the space character to 26
  //lets print the new numbers as we go too

  printf("plaintext shifted: ");
  //starting with the plaintext, lets loop through the characters
  for(i=0; i<10000; i++) {
    //if the character is a newline character, we have reached the end of the
    //file, so we want to print a newline character and break out of the loop
    if(plaintext[i] == '\n') {
      printf("\n");
      break;
    }
    //if the character is a space, make it the number 26
    else if(plaintext[i] == ' ') {
      plaintext[i] = 26;
      printf("26 ");
    }
    //if the character is a letter, convert it to 0-25
    //in this example we are using all-caps, so the letters will be between 65
    //and 90 (inclusive)
    else {
      plaintext[i] = plaintext[i] - 65;
      printf("%d ", plaintext[i]);
    }
  }

  printf("      key shifted: ");
  //next with otpkey, lets loop through the characters
  for(i=0; i<10000; i++) {
    //if the character is a newline character, we have reached the end of the
    //file, so we want to print a newline character and break out of the loop
    if(otpkey[i] == '\n') {
      printf("\n");
      break;
    }
    //if the character is a space, make it the number 26
    else if(otpkey[i] == ' ') {
      otpkey[i] = 26;
      printf("26 ");
    }
    //if the character is a letter, convert it to 0-25
    //in this example we are using all-caps, so the letters will be between 65
    //and 90 (inclusive)
    else {
      otpkey[i] = otpkey[i] - 65;
      printf("%d ", otpkey[i]);
    }
  }

  //formatting
  printf("\n\n");

  //print the addition operation
  printf("   ");
  for(i=0; i<10000; i++) {
    if(plaintext[i] == '\n') {
      printf("\n");
      break;
    }
    if(plaintext[i] < 10) {
      printf(" %d ", plaintext[i]);
    }
    else {
      printf("%d ", plaintext[i]);
    }
  }
  printf(" + ");
  for(i=0; i<10000; i++) {
    if(otpkey[i] == '\n') {
      printf("\n");
      break;
    }
    if(otpkey[i] < 10) {
      printf(" %d ", otpkey[i]);
    }
    else {
      printf("%d ", otpkey[i]);
    }
  }

  //now we are going to add the plaintext and the key together
  //this is almost the encrypted text, but we still have to shift the numbers 
  //back to real letters
  printf(" = ");
  for(i=0; i<10000; i++) {
    if(plaintext[i] == '\n') {
      encrypted[i] = '\n';
      printf("\n");
      break;
    }

    encrypted[i] = plaintext[i] + otpkey[i];
    if(encrypted[i] < 10) {
      printf(" %d ", encrypted[i]);
    }
    else {
      printf("%d ", encrypted[i]);
    }
  }

  printf("   ");
  for(i=0; i<10000; i++) {
    if(encrypted[i] == '\n') {
      printf("\n");
      break;
    }

    if(encrypted[i] > 26) {
      encrypted[i] = encrypted[i] - 27;
      if(encrypted[i] < 10) {
        printf(" ");
      }
      printf("%d ", encrypted[i]);
    }
    else {
      printf("   ");
    }
  }

  //formatting
  printf("\n");

  printf("encrypted text as ascii: ");
  for(i=0; i<10000; i++) {
    if(encrypted[i] == '\n') {
      printf("\n");
      break;
    }

    if(encrypted[i] == 27) {
      encrypted[i] = 32;
    }
    else {
      encrypted[i] = encrypted[i] + 65;
    }
    printf("%d ", encrypted[i]);
  }

  printf("\nencrypted text: %s", encrypted);

  //formatting
  printf("\n\n");
  printf("\n================DECRYPTING================\n");


  return 0;
}
