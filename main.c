	//Mateescu Cristina-Ramona, 311CB
	//Tema2
	#include<stdio.h>
	#include<string.h>
	#include"header.h"
	#include<stdlib.h>

	void distruge_sisteme(TLista * sisteme)
	
	{ 
	  
	  while ( (*sisteme) != NULL )
		{  //Eliberez p - sistemul curent
		   TLista p=(*sisteme);
		   (*sisteme)=(*sisteme)->urm;
		
		   //Eliberare stiva A
		 
		     while ( ((TSH)(p->info))->A->vf!=NULL )
			{ TLista aux=((TSH)(p->info))->A->vf;
			   ((TSH)(p->info))->A->vf=((TSH)(p->info))->A->vf->urm;
			   free(aux->info);
			   free(aux);
			}
		     free(((TSH)(p->info))->A);


		   //Eliberare stiva B
		   
		     while ( ((TSH)(p->info))->B->vf!=NULL )
			{ TLista aux=((TSH)(p->info))->B->vf;
			   ((TSH)(p->info))->B->vf=((TSH)(p->info))->B->vf->urm;
			   free(aux->info);
			   free(aux);
			}
		     free(((TSH)(p->info))->B);


		  //Eliberare stiva C
		     while ( ((TSH)(p->info))->C->vf!=NULL )
			{ TLista aux=((TSH)(p->info))->C->vf;
			   ((TSH)(p->info))->C->vf=((TSH)(p->info))->C->vf->urm;
			   free(aux->info);
			   free(aux);
			}
		     free(((TSH)(p->info))->C);

		  //Eliberare coada de mutari
		      while ( ((TSH)(p->info))->mutari->ic!=NULL )
			{ TLista aux=((TSH)(p->info))->mutari->ic;
			   ((TSH)(p->info))->mutari->ic=((TSH)(p->info))->mutari->ic->urm;
			   free(aux->info);
			   free(aux);
			}
		    ((TSH)(p->info))->mutari->sc=NULL;
		    free(((TSH)(p->info))->mutari);

		//Eliberare culoare
		free(((TSH)(p->info))->culoare);
	
	 	free(p->info);
		//Eliberare sistem
		free(p); }


	}

	TLista InsCel ( void* info )

	{ TLista aux=(TLista)malloc(sizeof(Celula));
	  if( !aux ) return NULL;
	  aux->urm=NULL;
	  aux->info=info;
	  return aux;
	}
	
	TSH AlocSH ( size_t size,char* culoare ) 	

	{ TSH sistem = (TSH)malloc(sizeof(TSistem));
	  	if( sistem==NULL ) return NULL;

	  sistem->A=(ASt)malloc(sizeof(TStiva));
		if( sistem->A == NULL ) 
			{ free (sistem); 
			  return NULL;}

	  sistem->A->dime=sizeof(Celula);
	  sistem->A->vf=NULL;

	  sistem->B=(ASt)malloc(sizeof(TStiva));
		if ( sistem->B == NULL )
			{ free (sistem->A);
			  free (sistem); 
			  return NULL;}

	  sistem->B->dime=sizeof(Celula);
	  sistem->B->vf=NULL;

	  sistem->C=(ASt)malloc(sizeof(TStiva));
		if ( sistem->C ==NULL)
			{ free (sistem->B);
			  free (sistem->A);
			  free (sistem); 
			  return NULL;}

	  sistem->C->dime=sizeof(Celula);
	  sistem->C->vf=NULL;

	  sistem->mutari=(AQ)malloc(sizeof(TCoada));
		if ( sistem->mutari ==NULL )
			{ free (sistem->C);
			  free (sistem->B);
			  free (sistem->A);
			  free (sistem); 
			  return NULL;}

	  sistem->mutari->dime=sizeof(Celula);
	  sistem->mutari->sc=NULL;
	  sistem->mutari->ic=NULL;

	  sistem->culoare=(char*)malloc(size*sizeof(char));
		if( sistem->culoare == NULL) 
			{ free (sistem->mutari);
			  free (sistem->C);
			  free (sistem->B);
			  free (sistem->A);
			  free(sistem);
			  return NULL;
			}

	 strcpy(sistem->culoare, culoare);
	 sistem->n = 0;
	 return sistem;
	}

	
	void add ( TLista *sisteme, char *culoare, int dim )  
	
	{ TLista p=(*sisteme),ultim=NULL;
	  TSH sistem_nou;
	  TLista celula_sistem;
	  //1.Se cauta sistemul de culoare
	  while (p!=NULL && strcmp( culoare, ((TSH)(p->info))->culoare )!=0 )
		 {ultim=p; 
		  p=p->urm;}	 
	  
	  //2.Daca nu exista
	  if (!p ) 
		{ //2.1.alocare sistem nou
		  sistem_nou=AlocSH( strlen(culoare)+1, culoare );
		  if( sistem_nou == NULL){ 
				    	  printf("Nu se poate adauga un sistem nou");return;}
		  			
		  //2.2.alocare celula noua
		  celula_sistem=InsCel(sistem_nou);
		  if( celula_sistem == NULL) 	{free(sistem_nou->A);
						free(sistem_nou->B);
						free(sistem_nou->C);
						free(sistem_nou->mutari);
						free(sistem_nou->culoare);
						free(sistem_nou);
						printf("Nu se poate adauga un sistem nou");return;}
		  
		  //2.3.Inserare celula in lista de sisteme
		  if ( !(*sisteme) ) (*sisteme)=celula_sistem;
		  else 	ultim->urm=celula_sistem;
		  
		  p=celula_sistem;
	   	  
		}
	   
	  
	  //3.Adaug discul in stiva A din p
	  TLista A=((TSH)(p->info))->A->vf;
	
	  //3.1.Alocare celula disc
	  int *diametru=(int*)malloc(sizeof(int));
	  if (diametru == NULL )
			{ return;
			}
	(*diametru)=dim;

	TLista celula_disc=InsCel(diametru);
		  if( celula_disc == NULL) {free(diametru);
				      printf("Nu se poate adauga disc");return;}
		
	
          //3.2.Inserare celula disc    
	  if( A==NULL ) ((TSH)(p->info))->A->vf=celula_disc;
	  else { 
		 ASt saux=(ASt)malloc(sizeof(TStiva));
		 if( !saux) 
			{ free(diametru);
			  free(celula_disc);return;
			}
		 saux->dime=sizeof(Celula);
		 saux->vf=NULL;
		 
		 //Se muta in saux discurile cu diametru mai mic decat dim
	 	 while( ((TSH)(p->info))->A->vf!=NULL && (*((int*)(((TSH)(p->info))->A->vf->info)))<dim )
			{  
			   TLista aux=((TSH)(p->info))->A->vf;
			   ((TSH)(p->info))->A->vf=((TSH)(p->info))->A->vf->urm;
			   aux->urm=saux->vf;
			   saux->vf=aux;
			   
			}
		
		//Se insereaza in A discul celula_disc
		celula_disc->urm=((TSH)(p->info))->A->vf;
		((TSH)(p->info))->A->vf=celula_disc;

		//Se muta inapoi din saux toate discurile
		while ( saux->vf!=NULL )
			{ TLista aux=saux->vf;
			  saux->vf=saux->vf->urm;
			  aux->urm=((TSH)(p->info))->A->vf;
			  ((TSH)(p->info))->A->vf=aux;

			}
		free(saux);
		}
	//Se actualizeaza numarul de discuri din sistem
	((TSH)(p->info))->n++;
	
	}

	void show (TLista sisteme, char* culoare,FILE * out)
	
	{ //1.Cauta sistemul de culoare
	  
	  TLista p=sisteme;

	  //1.Se cauta sistemul de culoare
	  while (p!=NULL && strcmp( culoare, ((TSH)(p->info))->culoare )!=0 )
		 p=p->urm;
	
	  if(p==NULL)
		{ fprintf(out,"A_%s:\n",culoare);
		  fprintf(out,"B_%s:\n",culoare);
		  fprintf(out,"C_%s:\n",culoare);
		  return;}
	  
	  //2.1.Mutam toate elementele din A in saux
	  ASt saux=(ASt)malloc(sizeof(TStiva));
	  if ( !saux) return;
	  saux->dime=sizeof(Celula);
	  saux->vf=NULL;
	
	  while( ((TSH)(p->info))->A->vf!=NULL )
		{ TLista aux=((TSH)(p->info))->A->vf;
	          ((TSH)(p->info))->A->vf=((TSH)(p->info))->A->vf->urm;
		  aux->urm=saux->vf;
		  saux->vf=aux;

		} 
	  //2.2.Mutam elementele inapoi, in timp ce le afisam
	  fprintf(out,"A_%s:",culoare);
	  
	  while( saux->vf!=NULL )
		
		{ TLista aux=saux->vf;
		  fprintf(out," %d",(*((int*)(aux->info))) );
	          saux->vf=saux->vf->urm;
		  aux->urm=((TSH)(p->info))->A->vf;
		  ((TSH)(p->info))->A->vf=aux;

		}
	  fprintf(out,"\n"); 

	 //3.1.Mutam toate elementele din B in saux
	  
	  saux->vf=NULL;
	
	  while( ((TSH)(p->info))->B->vf!=NULL )
		{ TLista aux=((TSH)(p->info))->B->vf;
	          ((TSH)(p->info))->B->vf=((TSH)(p->info))->B->vf->urm;
		  aux->urm=saux->vf;
		  saux->vf=aux;

		} 
	  //3.2.Mutam elementele inapoi, in timp ce le afisam
	  fprintf(out,"B_%s:",culoare);
	  
	  while( saux->vf!=NULL )
		
		{ TLista aux=saux->vf;
		  fprintf(out," %d",(*((int*)(aux->info))) );
	          saux->vf=saux->vf->urm;
		  aux->urm=((TSH)(p->info))->B->vf;
		  ((TSH)(p->info))->B->vf=aux;

		}
	  fprintf(out,"\n"); 

	  //4.1.Mutam toate elementele din C in saux
	  saux->vf=NULL;
	
	  while( ((TSH)(p->info))->C->vf!=NULL )
		{ TLista aux=((TSH)(p->info))->C->vf;
	          ((TSH)(p->info))->C->vf=((TSH)(p->info))->C->vf->urm;
		  aux->urm=saux->vf;
		  saux->vf=aux;

		} 
	  //4.2.Mutam elementele inapoi, in timp ce le afisam
	  fprintf(out,"C_%s:",culoare);
	  
	  while( saux->vf!=NULL )
		
		{ TLista aux=saux->vf;
		  fprintf(out," %d",(*((int*)(aux->info))) );
	          saux->vf=saux->vf->urm;
		  aux->urm=((TSH)(p->info))->C->vf;
		  ((TSH)(p->info))->C->vf=aux;

		}
	  fprintf(out,"\n"); 
	  free(saux);	
	}
	
	void Hanoi ( int n, char sursa, char destinatie, char aux, AQ mutari)
	{ 
	 if( n==1 )
		{ TM muta=(TM)malloc(sizeof(TMuta));
		  muta->sursa=sursa;
		  muta->destinatie=destinatie;
		
		  TLista cel=InsCel(muta);
		  if(!cel) {printf("Nu se pot efectua mutarile");return;}
		  
		 if (mutari->sc==NULL) {mutari->ic=cel;
					mutari->sc=cel;}
		 else {mutari->sc->urm=cel;
		       mutari->sc=cel;}
		return;
		}
	 Hanoi ( n-1, sursa, aux, destinatie,mutari );
	 TM muta=(TM)malloc(sizeof(TMuta));
		  muta->sursa=sursa;
		  muta->destinatie=destinatie;
		
		  TLista cel=InsCel(muta);
		  if(!cel) {printf("Nu se pot efectua mutarile");return;}
		  
		 if (mutari->sc==NULL) {mutari->ic=cel;
					mutari->sc=cel;}
		 else {mutari->sc->urm=cel;
		       mutari->sc=cel;}
	Hanoi ( n-1,aux, destinatie, sursa,mutari );

	}


	void show_moves (TLista sisteme, char* culoare,FILE * out,int nr)
	{ 
	  TLista p=sisteme;
	  //1.Se cauta sistemul de culoare
	  while (p!=NULL && strcmp( culoare, ((TSH)(p->info))->culoare )!=0 )
		 p=p->urm;
	  
	  if(!p) {printf("Nu exista sistemul de culoare %s\n!",culoare);return;}

	  TSH sistem=(TSH)(p->info);
	  
	  
	  //2.Daca sistemul e in starea initiala
	  // Pun mutarile in coada de mutari
	  if( sistem->B->vf == NULL && sistem->C->vf==NULL && sistem->mutari->ic==NULL)
	       	
		Hanoi (sistem->n,'A','C','B', sistem->mutari);
		
	  
	  AQ caux=(AQ)malloc(sizeof(TCoada));
	  
 	  if(!caux) return;
	  caux->ic=NULL;
	  caux->sc=NULL;

		
	  fprintf(out, "M_%s:",culoare);
	  

	  //3.Extrag din coada maxim nr mutari
	  //pe care le pun in caux
	  while ( sistem->mutari->ic!=NULL && nr>0 )
		
		{ TLista aux=sistem->mutari->ic;
		  
		  //Afisare mutare
		  fprintf(out, " %c->%c", ((TM)(aux->info))->sursa, ((TM)(aux->info))->destinatie);
		  
		  //Eliminam celula din mutari
		  sistem->mutari->ic=sistem->mutari->ic->urm;

		  //Inseram mutarea in caux
		  if ( caux->ic == NULL ) {caux->ic=aux; 
					     caux->ic->urm=NULL;
					     caux->sc=aux; 
					     }
		  else {caux->sc->urm=aux;
			caux->sc=aux;
			aux->urm=NULL;}
		  
		  nr--;

		}
		
	 fprintf(out,"\n");

	 //4.Mut restul mutarilor in caux apoi mut intreaga coada inapoi
	 while ( sistem->mutari->ic!=NULL)
		{ TLista aux=sistem->mutari->ic;
		  sistem->mutari->ic=sistem->mutari->ic->urm;
		  if ( caux->ic == NULL ) {caux->ic=aux; 
					     caux->ic->urm=NULL;
					     caux->sc=aux; 
					     caux->sc->urm=NULL;}
		  else {caux->sc->urm=aux;
			aux->urm=NULL;
			caux->sc=aux;}
 
		}
	sistem->mutari->sc=NULL;
	
	//5.refac coada mutarilor
	while ( caux->ic!=NULL)
		{ 
		  TLista aux=caux->ic;
		  caux->ic=caux->ic->urm;
		
		  if( sistem->mutari->ic==NULL) { sistem->mutari->ic=aux;
						  sistem->mutari->ic->urm=NULL;
						  sistem->mutari->sc=aux;
						  sistem->mutari->sc->urm=NULL;
						}
		  else {sistem->mutari->sc->urm=aux;
			aux->urm=NULL;
			sistem->mutari->sc=aux;
			}
		}
	free(caux);
	}



	void play (TLista sisteme, char* culoare,FILE * out,int nr)
	
	{ TLista p=sisteme;

	  //1.Se cauta sistemul de culoare
	  while (p!=NULL && strcmp( culoare, ((TSH)(p->info))->culoare )!=0 )
		 p=p->urm;
	  
	  if(!p) {printf("Nu exista sistemul de culoare %s\n!",culoare);return;}

	  TSH sistem=(TSH)(p->info);
	  
	  
	  //2.Daca sistemul e in starea initiala
	  // Pun mutarile in coada de mutari
	  if( sistem->B->vf == NULL && sistem->C->vf==NULL && sistem->mutari->ic==NULL)
	       	
		Hanoi (sistem->n,'A','C','B', sistem->mutari);
	
	  while ( sistem->mutari->ic!=NULL && nr>0 )
		
		{ TLista aux=sistem->mutari->ic;
		
		  //Extrag mutarea din coada de mutari
		  sistem->mutari->ic=sistem->mutari->ic->urm;

		  //Extrag discul din stiva sursa
		  TLista disc;
		  if ( ((TM)(aux->info))->sursa == 'A' )
			
			{ disc=sistem->A->vf;
			  sistem->A->vf=sistem->A->vf->urm;
			}
		  else if ( ((TM)(aux->info))->sursa == 'B' )
			
			{ disc=sistem->B->vf;
			  sistem->B->vf=sistem->B->vf->urm;
			}
		  else	{ disc=sistem->C->vf;
			  sistem->C->vf=sistem->C->vf->urm; }
		 

		//Inserez discul in stiva destinatie 
	  	if ( ((TM)(aux->info))->destinatie == 'A' )
			
			{ disc->urm=sistem->A->vf;
			  sistem->A->vf=disc;
			}
		  else if ( ((TM)(aux->info))->destinatie == 'B' )
			
			{ disc->urm=sistem->B->vf;
			  sistem->B->vf=disc;
			}
		  else	{ disc->urm=sistem->C->vf;
			  sistem->C->vf=disc; }

		 nr--;
		
		//Eliberam aux
		free(aux->info);
		free(aux);
		 }

	}

	
 
	
	int main(int argc,char *argv[])
	
	{ int op; //numar operatii
 	  char operation[20],culoare[20];
	  int dim,nr;
	  FILE *in=fopen( argv[1],"rt" );
	  FILE *out=fopen( argv[2],"wt" );
	
	  TLista sisteme=NULL;
	  
  	  fscanf( in, "%d", &op);
	  while(op)
	     {
	      fscanf( in, "%s", operation );

	      if( !strcmp( operation,"add" ) )
		{ fscanf( in, "%s %d", culoare, &dim );
		  add ( &sisteme, culoare , dim );
		
		}

	      else if ( !strcmp( operation,"play" ) )
		{ fscanf( in, "%s %d", culoare, &nr );
		  play (sisteme,culoare,out,nr);
		}		

	      else if ( !strcmp( operation,"show" ) )
		{ fscanf( in, "%s", culoare );
		  show ( sisteme, culoare ,out);
		}

	      else if ( !strcmp( operation,"show_moves" ) )
		{ fscanf( in, "%s %d", culoare, &nr );
		  show_moves (sisteme,culoare,out,nr);
		}
	  	
	      op--;
	      }
	  
	  distruge_sisteme(&sisteme);
	  sisteme=NULL;
	  fclose(in);
  	  fclose(out);
	return 0;
	}

