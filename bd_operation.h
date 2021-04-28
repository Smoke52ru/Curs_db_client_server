#include<string.h>
#include<stdio.h>

#define COMLEN 3
#define MAXNAME 80
#define MAXINDEX 5
#define MAXSURNAME 50
#define INF #

struct dbdata
{
    char name[MAXNAME], surname[MAXSURNAME];
}data;

struct dbinfo {
	char name[127];
	FILE* rec;
	int recsize;
}db;

int bd_open(char* fname, int recsize){
    if((db.rec = fopen(fname,"r+")) == NULL)
		       db.rec = fopen(fname,"w+");
    if(db.rec == NULL) return 0;
	
    strcpy(db.name,fname);
    db.recsize = recsize;
    
	return 1;
}

int dbreccount(void)
{
	 int count;
	 long now,end;
	 now = ftell(db.rec);
	 fseek(db.rec,0L,SEEK_END);
	 end = ftell(db.rec);
	 end /= db.recsize;
	 count = end;
	 fseek(db.rec,now,SEEK_SET);
	 return count;
}

int dbgoto(int number)
{
	if(number >= dbreccount())  return 0;
	if(number == 0) {
		fseek(db.rec, 0L, SEEK_END);
		return 1;
	}
	fseek(db.rec, db.recsize * (number-1), SEEK_SET);
	return 1;
}

int bd_read(int string_number){
	dbgoto(string_number);
	char result[MAXNAME + MAXSURNAME + 1];
	
	if(!fread(result, db.recsize, 1, db.rec)){
		if(result[0] == '#'){
			strcpy(data.name, "EMPTY");
			strcpy(data.surname, "EMPTY");
		}
		else{
			sscanf(result, "%s %s", data.name, data.surname);
		}
		return 0;
	}
	return 1;
}

int bd_write_element(int string_number, char* src){
	dbgoto(string_number);
	if(!fwrite(src, db.recsize, 1, db.rec)) return 0;
    
	return 1;
}

int bd_element_add(char* src){
	if(!bd_write_element(0, src)) return 0;
	
    return 1;
}

int bd_element_delete(int string_number){
    dbgoto(string_number);
	//TODO dopisat
		
	return 0;
}

int bd_close(void){
	remove(db.name);
	fclose(db.rec);
}