#include<string.h>
#include<stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 128
#define MAXNAME 30
#define MAXSURNAME 30


struct dbdata
{
    char name[MAXNAME], surname[MAXSURNAME];
}data;

struct dbinfo {
	char name[127];
	FILE* rec;
	int recsize;
}db;

int dbopen(char* fname, int recsize){
    if((db.rec = fopen(fname,"r+")) == NULL) // Если файл не открывается
		       db.rec = fopen(fname,"w+"); // Тогда создаем
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

int dbread(int string_number){
	dbgoto(string_number);
	char buffer[BUFFER_SIZE];
	
	if(fread(buffer, db.recsize, 1, db.rec)){
		if(buffer[0] == '#'){
			strcpy(data.name, "#DELETED");
			strcpy(data.surname, "#DELETED");
			return 0;
		}
		else{
			sscanf(buffer, "%s %s", data.name, data.surname);
		}
	}
	return 1;
}

int dbwrite(int string_number, char* src){
	char str[BUFFER_SIZE] = {};
	strcpy(str, src);
	dbgoto(string_number);
	if(fwrite(str, db.recsize, 1, db.rec)) return 1;
    
	return 0;
}

int dbadd(char* src){
	if(dbwrite(0, src)) return 1;
	
    return 0;
}

int dbdelete(int string_number){
    dbgoto(string_number);
	if(fwrite("#", 1, 1, db.rec)) return 1;
		
	return 0;
}

int dbcompress(void){
	char buffer[BUFFER_SIZE];
	int i, dbsize;
	int dest = 0, src = 0, deleted=0;

	dbsize = dbreccount();

	i = 1;
	while (i<=dbsize){
		fseek(db.rec, db.recsize * (i-1), SEEK_SET);
		if (fread(buffer, 1, 1, db.rec)){ 
			if ((buffer[0] == '#') && (dest == 0)) { // поиск удаленной строки
				dest = i;
			} else if ((buffer[0] !='#') && (dest != 0)) { 
				src = i;
			}
			if ((dest != 0) && (src != 0)){ // перенос
				fseek(db.rec, db.recsize * (src-1), SEEK_SET);
				if (fread(buffer, db.recsize, 1, db.rec)){

					fseek(db.rec, db.recsize * (src-1), SEEK_SET);
					fwrite("#", 1, 1, db.rec);

					fseek(db.rec, db.recsize * (dest-1), SEEK_SET);
					fwrite(buffer, db.recsize, 1, db.rec);
					i = dest;
					dest = 0;
					src = 0;
				}
			}
		}
		i++;
	}
	i=0;
	fseek(db.rec, 0L, SEEK_SET);
	if (fread(buffer, 1, 1, db.rec))
		while (buffer[0] != '#'){
			i++;
			fseek(db.rec, db.recsize-1, SEEK_CUR);
			if (!fread(buffer, 1, 1, db.rec)) return 0;
		}
	truncate(db.name, i*db.recsize);
	return 1;
}

int dbclose(void){
	dbcompress();

	if (dbreccount() == 0) remove(db.name);
	fclose(db.rec);
}