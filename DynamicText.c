/*******************************************************************************************/
/*                           Willkommen zur 4.Aufgabe                                      */
/*            Dieses Programm zielt darauf ab den Umgang mit fopen zu erlernen             */
/*******************************************************************************************/


/*******************************************************************************************/
/*                               Author: Stefan Hermeter                                   */
/*                                  Klasse:5/6 ABETI                                       */
/*                                 Datum:  07.03.2016                                      */
/*******************************************************************************************/


/*****************************************/
/*      Die verwendeten Libaries         */
/* bzw. die maximale Anzahl der Vektoren */
/*****************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define N 300

int main(int argc, char *argv[])
{
  // zähler für Fehler und Argumenteneingabe
  int stderr = 0;
  int opt;
  //  extern char *optarg;
  extern int optopt;
  
  while ((opt = getopt(argc, argv, "h")) != -1) {
    switch (opt) {

      /* Aufruf der Hilfe mit '-h'*/
    case 'h':
      printf("Dies ist die Hilfe des Programmes.\nDieses Programm liest \'uebtext.txt\'ein.\nSie werden danach abgefragt welche Zeile sie auf der Commandozeile ausgeben möchten.\n\t-h\t...\tgibt die Hilfe des Programms aus.\nDas Programm beendet sich nach der Ausgabe.\n");
      return 0;

      /* Wenn ein falsches Argument aufgerufen wurde */
      case'?':
      if (isprint (optopt)){
	printf ("Please Type %s, -h for more information.\n", argv[0]);
      }
      stderr++;
      break;
    }
  }

  long length;
  FILE *fp = fopen ("uebtext.txt", "rb");
  char *buffer = 0; 

  if (fp)
    {
      fseek (fp, 0, SEEK_END);
      length = ftell (fp);
      fseek (fp, 0, SEEK_SET);
      buffer = malloc (length);
      if (buffer)
	{
	  fread (buffer, 1, length, fp);
	}
      fclose (fp);
    }

  printf("Bitte geben sie die Zeilennummer an, welche Sie sich anzeigen lassen wollen:");
  int a = 0;
  while(1){
    scanf("%d", &a);
    if(a > 2)break;
    printf("\nDie Zahl muss größer als 2 sein:");
    
  }
    
  fflush(stdin);
  
  int j = 0;
  char *buff2;
  
  for(; *buffer != '\0' ; buffer++){
    if(*buffer == '\n')j++;
    if(j == a - 3){
      buffer++;
      buff2 = buffer;
      break;
    }
  }
  //  printf("j = %d",j);
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
  
  printf("\n");
  
  return 0;
}
