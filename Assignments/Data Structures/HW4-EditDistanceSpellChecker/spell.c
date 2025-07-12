/* Miguel Cervantes 1002045172 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "spell.h"

#define MAX_CAPACITY  101

/*  Suggestions
- When you work with 2D arrays, be careful. Either manage the memory yourself, or
work with local 2D arrays. Note C99 allows parameters as array sizes as long as 
they are declared before the array in the parameter list. See: 
https://www.geeksforgeeks.org/pass-2d-array-parameter-c/

Worst case time complexity to compute the edit distance from T test words
 to D dictionary words where all words have length MAX_LEN:
Student answer:  Theta(T*D*MAX_LEN^2)

*/


/* Write helper functions here */
void printTable(char * first_string, char * second_string, int temp[MAX_CAPACITY][MAX_CAPACITY]) {
  int m = strlen(first_string);
  int n = strlen(second_string); 
  printf("\n  |   |  ");

  for(int k = 1; k <= n; k++) {
    printf("%c|  ", second_string[k-1]);
  }
  printf("\n");

  for(int p = 0; p < n + 1; p++) {
      printf("----");
  } 
  printf("---\n");

  for (int i = 0; i <= m; i++) {
    if (i == 0) {
      printf("  |");  
    }
    else {
      printf(" %c|", first_string[i - 1]);
    }
    
    for (int j = 0; j <= n; j++) {
      printf("%3d|", temp[i][j]);
    }
    printf("\n");

    for(int l = 0; l < n + 1; l++) {
      printf("----");
    } 
    printf("---\n");
  }
  printf("\n");
}

int min(int a, int b, int c) {
  if (a < b && a < c) {
    return a;
  }
  else if (b < c) {
    return b;
  }
  else {
    return c;
  }
}

int findMinEditDist(char *testString, char dict[][MAX_CAPACITY], int numDictWords) {
  int minDist = 9999;
  int temp;
  for(int i = 0; i < numDictWords; i++) {
    temp = edit_distance(testString, dict[i], 0);
    if(temp < minDist) {
      minDist = temp;
    }
  }

  return minDist;
}

int numEDChoices(char *testString, char dict[][MAX_CAPACITY], int numDictWords, int minED) {
  int temp;
  int count = 0;
  for(int i = 0; i < numDictWords; i++) {
    temp = edit_distance(testString, dict[i], 0);
    if(temp == minED) {
      count++;
    }
  }

  return count;
}

void findEDChoices(char *testString, char dict[][MAX_CAPACITY], int numDictWords, int minED, char dictChoices[][MAX_CAPACITY]) {
  int temp;
  int count = 0;
  for(int i = 0; i < numDictWords; i++) {
    temp = edit_distance(testString, dict[i], 0);
    if(temp == minED) {
      strcpy(dictChoices[count], dict[i]);
      count++;
    }
  }
}

void printMenu(int numDictChoices, int minEditDist,  char dictChoices[][MAX_CAPACITY]) {
  int choice;
  printf("%2d - type correction\n%2d - leave word as is (do not fix spelling)\n     "
  "Minimum distance: %d\n     Words that give minimum distance:\n", -1, 0, minEditDist);

  for(int i = 0; i < numDictChoices; i++) {
    printf("%2d - %s\n", i+1, dictChoices[i]);
  }
  printf("Enter your choice: ");
}
/*
Parameters:
  - first_string - pointer to the first string (displayed vertical in the table)
  - second_string - pointer to the second string (displayed horizontal in the table)
  - print_table - If 1, the table with the calculations for the edit distance will be printed.
                  If 0 (or any value other than 1)it will not print the table
Return:  the value of the edit distance
*/
int edit_distance(char * first_string, char * second_string, int print_table) {

  int m = strlen(first_string);
  int n = strlen(second_string);
  int temp[MAX_CAPACITY][MAX_CAPACITY];

  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
      if (i == 0) {
        temp[i][j] = j; 
      }
      else if (j == 0) {
        temp[i][j] = i;
      }
      else if (first_string[i - 1] == second_string[j - 1]) {
        temp[i][j] = temp[i - 1][j - 1];
      }
      else {
        temp[i][j] = 1 + min(temp[i][j - 1], temp[i - 1][j], temp[i - 1][j - 1]);
      }
    }
  }

  if(print_table == 1) {
    printTable(first_string, second_string, temp);
  }

  return temp[m][n];
}


/*
Parameters:
  - testname - string containing the name of the file with the paragraph to spell check, includes file extenssion e.g. "text1.txt" 
  - dictname - name of file with dictionary words. Includes file extenssion, e.g. "dsmall.txt"
Behavior: If any of the files cannot be open displays a message and returns. (Does not exit the program.)
*/
void spell_check(char * testname, char * dictname){
  FILE *testString = fopen(testname, "r");
  FILE *dictionary = fopen(dictname, "r");

  if(testString == NULL && dictionary == NULL) {
    printf("Could not open files %s and %s. Exiting...\n", dictname, testname);
    return;
  }
  
  else if (dictionary == NULL && testString != NULL) {
    fclose(testString);
    printf("Could not open file %s. Exiting...\n", dictname);
    return;
  }
  else if (testString == NULL && dictionary != NULL) {
    fclose(dictionary);
    printf("Could not open file %s. Exiting...\n", testname);
    return;
  }
  int numTestStrings;
  fscanf(testString, "%d", &numTestStrings);
  fgetc(testString);

  char testStrings[numTestStrings][MAX_CAPACITY];
  for (int i = 0; i < numTestStrings; i++) {
    fgets(testStrings[i], MAX_CAPACITY, testString);
    testStrings[i][strcspn(testStrings[i], "\n")] = '\0';
  }

  int numDictWords;
  fscanf(dictionary, "%d", &numDictWords);
  fgetc(dictionary);

  char dict[numDictWords][MAX_CAPACITY];
  for (int k = 0; k < numDictWords; k++) {
    fgets(dict[k], MAX_CAPACITY, dictionary);
    dict[k][strcspn(dict[k], "\n")] = '\0';
  }

  printf("\nLoaded dictionary %s has size: %d\n\n", dictname, numDictWords);

  int minEditDist;
  for (int i = 0; i < numTestStrings; i++) {
    minEditDist = findMinEditDist(testStrings[i], dict, numDictWords);
    int numDictChoices = numEDChoices(testStrings[i], dict, numDictWords, minEditDist);
    char dictChoices[numDictChoices][MAX_CAPACITY];
    findEDChoices(testStrings[i], dict, numDictWords, minEditDist, dictChoices);
    printf("---> |%s|\n", testStrings[i]);
    printMenu(numDictChoices, minEditDist, dictChoices);

    int choice;
    scanf("%d", &choice);
    if (choice == -1) {
      char newWord[MAX_CAPACITY];
      printf("Enter correct word: ");
      scanf("%s", newWord);
      strcpy(testStrings[i], newWord);
      printf("The corrected word is: %s\n\n", testStrings[i]);
    }
    else if(choice == 0) {
      printf("The corrected word is: %s\n\n", testStrings[i]);
    }
    else if(choice >= 1 && choice <= numDictChoices) {
      strcpy(testStrings[i], dictChoices[choice-1]);
      printf("The corrected word is: %s\n\n", testStrings[i]);
    }
    else {
      printf("Invalid choice. Original word will be kept.\nThe corrected word is: %s\n\n", testStrings[i]);
    }
  }

  fclose(testString);
  fclose(dictionary);
}

