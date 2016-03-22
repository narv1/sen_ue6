#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char *ptr,*temp;
  ptr = malloc(sizeof(char));

  int c;
  int i;

  FILE *fp;

  fp = fopen("uebtext.txt","r");
  
  for (i = 0; ; i++) {
    c = fgetc(fp);
    if (c == EOF)break;
    ptr[i] = c;
    temp = realloc(ptr,(i+10)*sizeof(int));

    if ( temp != NULL ) {
      ptr = temp;
    }else{
      free(ptr);
      printf("Error speicher initialisierung.\n");
      return 1;
    }
  }

  for (i = 0; ;i++){
    if(ptr[i] == '\0')break;
    putchar(ptr[i]);
  }
  
  int j = 0;
  int a = 0;

  printf("Bitte geben sie die Zeile an welche sei ausgeben möchten:");
  while(1){
    scanf("%d", &a);
    if(a > 2)break;
    printf("\nDie Zahl muss größer als 2 sein:");  
  }

  fflush(stdin);

  for(i = 0;;i++){
    if(ptr[i] == '\n')j++;
    if(ptr[i] == '\0')break;
  }
  
  if(a >j){
    printf("Soviele Zeilen sind nicht vorhanden!\nDas Programm beendet sich jetzt.\n");
    return 1;
  }

  char *buff2;
  j=0;
  for(i = 0; ptr[i] != '\0' ; ptr++){
    if(ptr[i] == '\n')j++;
    if(j == a - 3){
      ptr++;
      buff2 = ptr;
      break;
    }
  }

  free(ptr);
  
  j = 0;
  char tr[] = "\n";

  buff2 = strtok( buff2, tr);

  while(buff2 != NULL) {
    if(j == 2){
      printf("\033[31m%s\n", buff2);
      buff2 = strtok(NULL, tr);
    }else{
      printf("\033[m%s\n", buff2);
      buff2 = strtok(NULL, tr);
    }
    j++;
    if(j == 5)break;
  }
  
  return 0;
}
