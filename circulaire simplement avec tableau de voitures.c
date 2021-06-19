#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nnn 100

 typedef struct persone {
  char cin[15] ;
  char name[20];
  char prenom[20];
  }persone;

typedef struct voiture {
  char matricule[25];
  char marque[50];
  int prix_du_jour;
  int duree_location;
}voiture;

typedef struct location {
char Identifiacteur_location[25];
  voiture voiture_louee[nnn] ;
  persone client;
  struct location *next;
 }location;



//debut calcule de prix
int Calculer_prix_total(location *Lc){

  int i=0;
 location *Fa =Lc;
 if(Fa->voiture_louee[i].prix_du_jour =='\0'){
 printf("Fc->voiture_louee == \\0 ");
 }else {

 int a=0 ,i=0;
 while ( Fa->voiture_louee[i].prix_du_jour !='\0'){

 int dd=Fa->voiture_louee[i].prix_du_jour;
 int bd =Fa->voiture_louee[i].duree_location;
 a = a + (dd)*(bd);
 ++i;}
return a;
}
}
//fin fonction de calculer le prix


//rechercher une location

location *Rechercher_location(location *Lc){
location *Fa =Lc;
 char c[15];
 
 if (Fa == NULL ){
 printf("Fa == NULL"); 
 }
 else {
 printf("\nEntrer CIN :");
 scanf("%s",c);}
 
 while (strcmp(Fa->client.cin,c)!= 0){
 Fa =Fa->next; 
}

do
{
  printf("\nla location que vouz chercher est :\n");
  printf("%s \n Informations sur le client : \n CIN du client : %s \n Nom du client : %s \n Prenom du client : %s \n \n Informations sur les voitures louées :\n Matricule de la voiture\tMarque de la voiture\tPrix par jour\tDurée de la location \n",Fa->Identifiacteur_location,Fa->client.cin,Fa->client.name,Fa->client.prenom);
 int i=0;
   while ( Fa->voiture_louee[i].prix_du_jour != '\0')
   {
   printf("%s\t%s\t%d\t%d\n",Fa->voiture_louee[i].matricule,Fa->voiture_louee[i].marque,Fa->voiture_louee[i].prix_du_jour,Fa->voiture_louee[i].duree_location);
++i;
   }
   int fn= Calculer_prix_total(Fa);
  printf("Prix total a payer par le client : %d DH \n\n",fn);


} while (Fa != Lc);

return Fa;
}


// Afficher_liste_locations
void Afficher_liste_locations(location *Lc){
location *ff = Lc;

do
{
  printf("%s \n Informations sur le client : \n CIN du client : %s \n Nom du client : %s \n Prenom du client : %s \n \n Informations sur les voitures louées :\n Matricule de la voiture\tMarque de la voiture\tPrix par jour\tDurée de la location \n",ff->Identifiacteur_location,ff->client.cin,ff->client.name,ff->client.prenom);
 int i=0;
   while ( ff->voiture_louee[i].prix_du_jour != '\0')
   {
   printf("%s\t%s\t%d\t%d\n",ff->voiture_louee[i].matricule,ff->voiture_louee[i].marque,ff->voiture_louee[i].prix_du_jour,ff->voiture_louee[i].duree_location);
++i;
   }
  printf("Prix total a payer par le client : %d DH \n\n",Calculer_prix_total(ff));

  ff=ff->next;
} while (ff != Lc);
}
//fin afficher

// Ajouter_location
location *Ajouter_location(location *Lc ,int N){
int i=0;
  location *t = malloc(sizeof(location));

printf("\n Entrer un indentificateur pour cette location  \"un referance de 25 character au maximum\" :");
scanf("%s",t->Identifiacteur_location);

printf("\n Entrer le nom du client :");
scanf("%s",t->client.name);

printf("\n Entrer le prenom du client :");
scanf("%s",t->client.prenom);

printf("\n Entrer le CIN du client :");
scanf("%s",t->client.cin);


for (i=0;i<N;i++){
//
printf("\n Entrer la matricule de la voiture N%d :",i+1);
scanf("%s",t->voiture_louee[i].matricule);
printf("\n Entrer la marque de la voiture N%d :",i+1);
scanf("%s",t->voiture_louee[i].marque);
printf("\n Entrer le prix du jours de la voiture N%d :",i+1);
scanf("%d",&(t->voiture_louee[i].prix_du_jour) );
printf("\n Entrer Combien ce client va louer la voiture N%d :",i+1);
scanf("%d",&(t->voiture_louee[i].duree_location) );
}

if (Lc == NULL){
t->next = t;
  Lc = t;
}
else {
  location *s=Lc;
while (s->next != Lc)
{
  s=s->next;
}
t->next = Lc;
s->next = t;
}
return Lc;//Lc est le head du list
}
//Menu

location *returnLo(location *Lc){

 location *Fc =Lc;
 char c[15];
 
 if (Fc == NULL ){
 printf("Fc == NULL");
 
 }
 else {
 printf("entrer CIN :");
 scanf("%s",c);
 
 
 while (strcmp(Fc->client.cin,c)!= 0){
 Fc =Fc->next; 
}
}
return Fc;
}


//enregistrer
FILE *Enregistrer_location(location *Lc){

location *ff =returnLo(Lc) ;

char n[20];
    printf("\nwrite the file name with the extention .txt");
    scanf("%s",n);

    FILE *regularTxt = NULL;
    regularTxt = fopen(n, "a");
    if (!regularTxt){
        printf("****error with regtxt");
     }
    
   
    fprintf(regularTxt,"Identificateur de la location: %s \n Informations sur le client : \n CIN du client : %s \n Nom du client : %s \n Prenom du client : %s \n \n Informations sur les voitures louées :\n Matricule de la voiture\tMarque de la voiture\tPrix par jour\tDurée de la location \n",ff->Identifiacteur_location,ff->client.cin,ff->client.name,ff->client.prenom);
  
  int i=0;
   while ( ff->voiture_louee[i].prix_du_jour != '\0')
   {
   fprintf(regularTxt,"%s\t%s\t%d\t%d\n",ff->voiture_louee[i].matricule,ff->voiture_louee[i].marque,ff->voiture_louee[i].prix_du_jour,ff->voiture_louee[i].duree_location);
++i;
   }
  fprintf(regularTxt,"\n\nPrix total a payer par le client : %d DH \n\n",Calculer_prix_total(ff));
    
  fclose(regularTxt);
    return regularTxt;
}
//
void Menu_general(){
  printf("1. Ajouter une location\n");
  printf("2. Afficher locations.\n");
  printf("3. Rechercher location.\n");
  printf("4. Supprimer location.\n ");
  printf("5. Enregistrer location.\n ");
 
}



//supprimer
location *Supprimer_location(location *Lc){
printf("veuillez entrer le CIN d'utilisateur a supprimer ci-dessous:\n");
location *sp = returnLo(Lc);

if (sp==Lc)
{
location *p= Lc;
while (p->next != Lc)
{
p=p->next;
   
}

p->next = p->next->next;

Lc=p->next; 
free(sp);

 }else{
location *p = sp;

while (p->next != sp)
{
  p=p->next;
  
}

p->next =p->next->next;

free(sp);
}

return Lc;
}



int main(){
   
int N,r;
location *Lc =NULL;

FILE *fl;

while (1){  
 Menu_general();
scanf("%d",&r);
switch (r){
case 1:

printf("\n Combier de voiture ce client veut louer :");
scanf("%d",&N);
if (N>100)
{
    printf("ce code accepte maximum 100 voiture a enregistrer par client !\n");
    printf("\n reshoisisez Combier de voiture ce client veut louer :");
scanf("%d",&N);
}
Lc =Ajouter_location(Lc,N);
break;

case 2:
Afficher_liste_locations(Lc);
break;

case 3:
Rechercher_location(Lc);
break;

case 4:
Lc=Supprimer_location(Lc);
break;

case 5:
fl = Enregistrer_location(Lc);
break;

default:
printf("\n \n ****invalid choice***** \n \n"); 
}

}

return 0;
}