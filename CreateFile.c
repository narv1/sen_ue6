/*******************************************************************************************/
/*                              Willkommen zur 5.Aufgabe                                   */
/*            Dieses Programm zielt darauf ab den Umgang mit fopen zu erlernen             */
/*                       sowie eine besseres Handling mit strings                          */
/*                                    zu erreichen                                         */
/*******************************************************************************************/


/*******************************************************************************************/
/*                               Author: Stefan Hermeter                                   */
/*                                  Klasse:5/6 ABETI                                       */
/*                                 Datum:  07.03.2016                                      */
/*******************************************************************************************/


/*****************************************/
/*      Die verwendeten Libaries         */
/*****************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#define N 2048


/*************************************************/
/*              Funktion file_exist              */
/*  Kontrolle ob jene Datei schon vorhanden ist  */
/*************************************************/

int file_exist(){

  FILE *fp;
  int c;

  /* Öffnen des Files im Lesemodus */
  fp = fopen("uebtext.txt","r");
    

  /* Kontrolle ob die Datei geöffnet werden konnte */
  if(fp == NULL)
    {
      printf("Fehler beim Öffnen.\n");
      return -1;
    }

  /* einlesen und Ausgabe von Createfile.c */
  printf("Der Inhalt der Datei lautet:\n");
  while(1){
    c = fgetc(fp);
    printf("%c", c);
    if (feof(fp)){
      fclose(fp);
      return -2;
    }
  }
  fclose(fp);
  
}

/*****************************************/
/*         Das Hauptprogramm             */
/*****************************************/
int main(int argc, char *argv[])
{
  /* zähler für Fehler und Argumenteneingabe */
  int stderr = 0, count = 0;
  int opt;
  extern int optopt;
  
  while ((opt = getopt(argc, argv, "ha")) != -1) {
    switch (opt) {

      /* Aufruf der Hilfe mit '-h' */
    case 'h':
      printf("Dies ist die Hilfe des Programmes.\nDieses Programm wurde entwickelt um Zeilenweise, ueber die Eingabe stdin, ein File zuerstellen welches zeilenweise Saetze einliest wird.\nUm das Programm zu beenden bestätigen sie während der Zeileneingabe mit \'x\'.\n\n\t-h\t...\tzeigt die Hilfe des Programms an.\n\t-a\t...\tweitere Zeilen an das Dokument anfügen.\n\nDer Name der Datei lautet \'uebtext.txt\'.\n");
      return 0;

      /* Wenn ein Falsches Argument aufgerufen wurde */
    case'?':
      if (isprint (optopt)){
	printf ("Please Type %s, -h for more information.\n", argv[0]);
      }
      stderr++;
      break;
      
      /* im Falle von a wird der intwert count um 1 erhöht um später eine ifabfrage zumachen */
    case 'a':
      printf("Das Textdokument \'Readsource\' wird Zeilenweise ausgegeben.\nSie koennen die Ausgabe mit \'x\' abbrechen und mit enter wird jeweils die naechste Zeile ausgegeben.\n\n");
      count++;
      break;
    }
  }

  printf("Dieses Programm erstellt eine Datei.\nWenn sie mehr Informationen wünschen \'-h\'\n");
  
  /* Bei falscheingabe beendigung des Programms */
  if (stderr == 1){
    return 0;
  }

  /* initialisierung des filepointers */
  int f;
  char line[N]={0};
  FILE *fp;

  /* Aufruf der Funktion file_exist */
  f = file_exist();

  if(f == -1 || f == -2){
    if (f ==-1){
      printf("File wird erstellt:\n");
    }
    /* Zählerabfrage für Argumenteneingabe */
    if(count == 0 || count == 1){

      /* Hier wird das Dokument neu aufbereitet NULL */
      if(f == -2 && count == 0){
	fp = fopen("uebtext.txt","w");
	char str[]={0}; 
	fwrite(str, 0, 0, fp);
	fclose(fp);
      }

      /* Öffnen der Datei uebtext.txt in Appendix mode */
      fp = fopen("uebtext.txt","a+");

      /* Kontrolle ob die Datei geöffnet werden konnte */
      if(fp == NULL){
	printf("Fehler beim Öffnen.");
	exit(0);
      }
      int k;
      int i = 1;
      char c;

      /* die schon vorhanden zeilen zählen */ 
      if(count == 1){
	while( (c=fgetc(fp)) != EOF){
	  if(c=='\n')i++;
	}
      }
      k = i;

      /* "Endlos" Eingabe in die Datei */
      /* Abbruch der schleife mit x+\n */
      printf("\nBitte geben sie den gewuenschten Inhalt ein:\n");
      while(fgets(line, sizeof(line), stdin)) {
	if(line[0] == 'x' && line[1] == '\n')break;
	if(k < 10){
	  fprintf(fp,"line 0%d: %s", i, line);
	}else{
	  fprintf(fp,"line %d: %s", i, line);
	}
	i++;
	k++;
      }
      fclose(fp);
      int x;

      /* Ausgabe der Datei auf stdout */
      fp = fopen("uebtext.txt","r");
      if(fp != NULL){
	while((x = fgetc(fp)) != EOF){
	  
	  putchar(x);
	}
      }
      fclose(fp);
    }
  }

  /* ENDE */
  return 0;
}
