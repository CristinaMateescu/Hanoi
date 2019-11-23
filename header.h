  //Mateescu Cristina-Ramona, 311CB

  typedef struct celulag
  {
	void *info;
	struct celulag *urm;

  } Celula, *TLista, **ALista;


  typedef struct
  { 	
	size_t 	dime; 		// dimensiunea unui element din coada
	TLista 	ic; 		// adresa primului element din coada
	TLista 	sc; 		// adresa de sfarsit a cozii

  } TCoada, *AQ;


  typedef struct
  {  	
	size_t 	dime; 		// dimensiunea unui element al stivei			
	TLista 	vf; 		// varful stivei

  } TStiva, *ASt;


  typedef struct sistem_hanoi
  { 	
	ASt A,B,C;		//cele 3 stive
	AQ mutari;    		//coada de mutari
	char *culoare;		//culoarea sistemului
	int n;			//nr de discuri din sistem 

  }TSistem, *TSH;
	
  typedef struct muta
  { char sursa;
    char destinatie;
  }TMuta, *TM;





