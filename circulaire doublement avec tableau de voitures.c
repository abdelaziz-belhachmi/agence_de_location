#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*circulaire doublement*/
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
  struct location *pre;
 }location;



//debut calcule de prix
int Calculer_prix_total(location *Lr){

  int i=0;
 location *Fa =Lr;
 if(Fa->voiture_louee[i].prix_du_jour =='\0'){
 printf("Fc->voiture_louee == \\0 ");
 }else {

 int a=0 ,i=0;
 while ( Fa->voiture_louee[i].prix_du_jour !='\0'){

 int fp=Fa->voiture_louee[i].prix_du_jour;
 int fd =Fa->voiture_louee[i].duree_location;
 a = a + (fp)*(fd);
 ++i;}
return a;
}
}
//fin fonction de calculer le prix


//rechercher une location

location *Rechercher_location(location *Lr){
location *Fa =Lr;
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


} while (Fa != Lr);

return Fa;
}


// Afficher_liste_locations
void Afficher_liste_locations(location *Lr){
location *ff = Lr;

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
} while (ff != Lr);
}
//fin afficher

// Ajouter_location
location *Ajouter_location(location *Lr ,int N){
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

if (Lr == NULL){
t->next =t;
t->pre =t;
  Lr = t;
}

else {
  location *s=Lr;

s=s->pre;

t->next = Lr;
Lr->pre = t;
s->next = t;
t->pre = s;
}
return Lr;//Lr est le head du list
}
//Menu

location *returnLo(location *Lr){

 location *Fc =Lr;
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
FILE *Enregistrer_location(location *Lr){

location *ff =returnLo(Lr) ;

char n[20];
    printf("\nchoisir le nom de fichier");
    scanf("%s",n);

    FILE *nvfichier = NULL;
    nvfichier = fopen(n, "a");
    if (!nvfichier){
        printf("erreur pendant la creation du fichier ");
     }
    
   
    fprintf(nvfichier,"Identificateur de la location: %s \n Informations sur le client : \n CIN du client : %s \n Nom du client : %s \n Prenom du client : %s \n \n Informations sur les voitures louées :\n Matricule de la voiture\tMarque de la voiture\tPrix par jour\tDurée de la location \n",ff->Identifiacteur_location,ff->client.cin,ff->client.name,ff->client.prenom);
  
  int i=0;
   while ( ff->voiture_louee[i].prix_du_jour != '\0')
   {
   fprintf(nvfichier,"%s\t%s\t%d\t%d\n",ff->voiture_louee[i].matricule,ff->voiture_louee[i].marque,ff->voiture_louee[i].prix_du_jour,ff->voiture_louee[i].duree_location);
++i;
   }
  fprintf(nvfichier,"\n\nPrix total a payer par le client : %d DH \n\n",Calculer_prix_total(ff));
    
  fclose(nvfichier);
    return nvfichier;
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
location *Supprimer_location(location *Lr){
printf("veuillez entrer le CIN d'utilisateur a supprimer ci-dessous:\n");
location *sp = returnLo(Lr);

if (sp==Lr)
{
location *p= Lr->pre;

p->next = p->next->next;
p=p->next;
p->pre = Lr->pre;

Lr=p; 
free(sp);

 }else{
location *p = sp->pre;
p->next =p->next->next;
p=p->next;
p->pre=sp->pre;
free(sp);
}

return Lr;
}



int main(){
   
int N,r;
location *Lr =NULL;

FILE *fl;

while (1){  
 Menu_general();
scanf("%d",&r);
switch (r){
case 1:

do {
printf("\n Combier de voiture ce client veut louer :");
scanf("%d",&N);
}while(N>100);

Lr =Ajouter_location(Lr,N);
break;

case 2:
Afficher_liste_locations(Lr);
break;

case 3:
Rechercher_location(Lr);
break;

case 4:
Lr=Supprimer_location(Lr);
break;

case 5:
fl = Enregistrer_location(Lr);
break;

default:
printf("\n \n ****choix invalid ***** \n \n"); 
}

}

return 0;
}