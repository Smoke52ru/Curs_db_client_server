
#include <string.h>
#include <db.h>
static struct dbinfo db;
static fpos_t f_ptr;
static int cur_record;

int dbuse(char* fname,int recsize)
{
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
	if(number ==0) {
		fseek(db.rec,0L,SEEK_END);
		return 1;
	}
	fseek(db.rec,db.recsize*(number-1),SEEK_SET);
	return 1;
}


int dbwrite(void*src)
{
    if(!fwrite(src,db.recsize,1,db.rec)) return 0;
    return 1;
}

int dbread(void* dest)
{
	if(!fread(dest,db.recsize,1,db.rec)) return 0;
	return 1;
}

void dbclose(void)
{
  if(!dbreccount()){
     remove(db.name);
     return;
   }
  fclose(db.rec);
  return;
}

int dbappend(void*src)
{
   dbgoto(0);
   return dbwrite(src);
}

int dbdelete(void)
{

}
