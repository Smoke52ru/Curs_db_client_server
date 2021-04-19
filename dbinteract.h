//TODO DBDELETE
#include <string.h>
#include <stdio.h>
struct dbinfo {
     char name[127];
     FILE* rec;
     int recsize;
  } db;
static fpos_t f_ptr;
static int cur_record;

//Открываем базу для записи(если ее не существует - создаем)
int dbuse(char* fname,int recsize) 
{
    if((db.rec = fopen(fname,"r+")) == NULL)
		       db.rec = fopen(fname,"w+");
    if(db.rec == NULL) return 0;
    strcpy(db.name,fname);
    db.recsize = recsize;
    return 1;
}
//Возвращает количество записей в базе
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
//Установка указателя на n-ную запись
int dbgoto(int number)
{
	if(number >= dbreccount())  return 0;
	if(number ==0) {
		fseek(db.rec,0L,SEEK_END);
		return 1;
	}
	fseek(db.rec,db.recsize*(number-1),SEEK_SET);
	return 1;
}
//Запись из src в текущее место в базе
int dbwrite(void*src)
{
    if(!fwrite(src,db.recsize,1,db.rec)) return 0;
    return 1;
}
//Чтение текущей записи из базы
int dbread(void* dest)
{
	if(!fread(dest,db.recsize,1,db.rec)) return 0;
	return 1;
}
//Закрытие базы (удаление, если она пустая)
void dbclose(void)
{
  if(!dbreccount()){
     remove(db.name);
     return;
   }
  fclose(db.rec);
  return;
}
//Запись в начало базы
int dbappend(void*src)
{
   dbgoto(0);
   return dbwrite(src);
}
//TODO Удаление базы
int dbdelete(void)
{
  int end = dbreccount();
}
