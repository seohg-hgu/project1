#include "student.h"
#include <malloc.h>

STUDENT* students[MAX_STUDENTS]; //학생 정보 데이터


int _count=0;
int sCount=0;
int grade[5];

void s_init(){
        //모든 레코드 제거
        int i;
        for(i=0;i<MAX_STUDENTS;i++){
                if(students[i]!=NULL){
                        free(students[i]);
                }
                students[i]=NULL;
        }
        _count=0;
        sCount=0;
#ifdef DEBUG
        printf("[DEBUG]Initializing Records _count: %d sCount: %d\n",_count, sCount);
#endif
}

int s_is_available(){
        int i;
        for (i=0;i<MAX_STUDENTS;i++){
                if(students[i]==NULL) return 1;
        }
        return 0;
}

STUDENT* s_search_by_name(char* n){
        int i;
        for (i=0;i<_count;i++){
                if (students[i]!= NULL&&strcmp(students[i]->name,n)==0) return students[i];
        }
        return NULL;
}


void s_create(char* n, char* num, char a, int s){
        int index=s_first_available();
#ifdef DEBUG
        printf("[DEBUG]first available index: %d\n ", index);
#endif
        students[index]=(STUDENT*)malloc(sizeof(STUDENT));
        STUDENT* p=students[index];
#ifdef DEBUG
        printf("[DEBUG]memory allocate %lu byte \n", malloc_usable_size(p));
#endif
        strcpy(p->name,n);
        strcpy(p->number,num);
        p->assignment = a;
        if (p->assignment=='Y'){
                sCount++;
        }
        p->score = s;
        _count++;

#ifdef DEBUG
    printf("[DEBUG]new  record is created: %s %s %c %d\n ",s_getname(p),s_getnumber(p),s_getassignment(p), s_getscore(p));
#endif
}

int s_first_available(){
        int i;
        for(i=0;i<MAX_STUDENTS;i++){
                if(students[i]==NULL) return i;
        }
        return -1;
}

char* s_getname(STUDENT* p){
        return p->name;
}

char* s_getnumber(STUDENT* p){
        return p->number;
}

char s_getassignment(STUDENT* p){
        return p->assignment;
}

int s_getscore(STUDENT* p){
        return p->score;
}
int s_count(){
        return _count;
}

int s_count_submitStudent(){
        return sCount;
}
void s_get_all(STUDENT* a[]){
        int i, c = 0;
        for (i=0;i<MAX_STUDENTS;i++){
                if (students[i]!=NULL) {
                        a[c]=students[i];
                        c++;
                }
        }
#ifdef DEBUG
        printf("[DEBUG]get %d records\n",c);
#endif
}

char* s_to_string(STUDENT* p){
        static char str[80];
        sprintf(str, "%s \t%s\t%c\t%d", p->name, p->number, p->assignment, p->score);
#ifdef DEBUG
        printf("[DEBUG]string: %s\t%s\t%c\t%d\n", p->name, p->number, p->assignment, p->score);
#endif

        return str;

}

double s_getAveragScore(){
  // 과제를 제출한 학생들의 평균 점수를 계산하여 리턴한다.
        int sum=0;
        double average;
        for(int i=0;i<MAX_STUDENTS;i++){
                if (students[i]!= NULL&&students[i]->assignment=='Y'){
                        sum+=students[i]->score;
                }
        }
        average=(double)sum/(double)sCount;
#ifdef DEBUG
        printf("[DEBUG]return average(%.1f)\n", average);
#endif
        return average;
}


int s_get_all_by_number(STUDENT* a[], char* n){
        // 학번 앞 3자리가 일치하는 모든 레코드 포인터의 배열 만들기
        int i, c = 0;
        for(i=0;i<_count;i++){
                if (students[i]!= NULL&&students[i]->number[0]==n[0]&&students[i]->number[1]==n[1]&&students[i]->number[2]==n[2]){
                        a[c] = students[i];
                        c++;
                }
        }
#ifdef DEBUG
        printf("[DEBUG]get %d correspoding  records\n",c);
#endif
        return c;

}


char* s_to_string_save(STUDENT* p){
        static char str[80];
        sprintf(str, "%s %s %c %d", p->name, p->number, p->assignment, p->score);

#ifdef DEBUG
        printf("[DEBUG]string(for save): %s\t%s\t%c\t%d\n", p->name, p->number, p->assignment, p->score);
#endif
        return str;


}

int s_get_submitStudent(STUDENT* a[]){
        int c=0;
        for(int i=0;i<_count;i++){
                if(students[i]!=NULL&&students[i]->assignment=='Y'){
                        a[c]=students[i];
                        c++;
                }
        }
#ifdef DEBUG
        printf("[DEBUG]get %d submit student\n", c);
#endif
        return c;
}

char* s_to_string_stats_save(){
        static char str[200];
        sprintf(str, "%d students submitted\nscore average: %.1lf\n",s_count_submitStudent(),s_getAveragScore());
#ifdef DEBUG
        printf("[DEBUG]string(for save stats): %d students submitted\nscore average: %.1lf\n",s_count_submitStudent(),s_getAveragScore());
#endif
        return str;
}

void s_update(STUDENT* p, char* num,  char a, int s){
        strcpy(p->number, num);
        p->assignment=a;
        p->score=s;

#ifdef DEBUG
        printf("[DEBUG]%s %s %c %d\n",p->name, p->number, p->assignment, p->score);
#endif
}

void s_sort_by_name(STUDENT* a[]){
        STUDENT* temp;
        int c=0, idx;
        for(int i=0;i<MAX_STUDENTS;i++){
                if(students[i]!=NULL){
                        a[c]=students[i];
                        c++;
                }
        }


        for(int i=0;i<c-1;i++){
                idx=i;
                for(int j=i;j<c;j++){
                        if(strcmp(a[idx]->name,a[j]->name)>0){
                                idx=j;
                        }
                }

        temp=a[i];
        a[i]=a[idx];
        a[idx]=temp;
        }


}
void s_delete(STUDENT* p){
        int i, index;
        for(i=0;i<MAX_STUDENTS;i++){
                if(students[i]==p){
                        index=i;
                        if(p->assignment=='Y'){
                                sCount--;
                        }

                        break;
                }
        }
        free(p);
        students[index]=NULL;
        _count--;

#ifdef DEBUG
        printf("[DEBUG]sCount= %d , _count= %d\n",sCount,_count);
#endif
}
void arrange(){
        int c=0;
        for(int i=0;i<MAX_STUDENTS;i++){
                if(students[i]==NULL){
                        continue;
                }else{
                  if((students[c]->name!=students[i]->name)&&(students[c]->number!=students[i]->number)){
                    students[c]=students[i];
                    students[i]=NULL;
                  }
                  c++;
                }
        }
}


void print_debug(){
#ifdef DEBUG
        for (int i=0;i<MAX_STUDENTS;i++){
                if(students[i]==NULL){
                        printf("[DEBUG]%d. NULL\n",i);
                }else{
                        printf("[DEBUG]%d. %s\t%s\t%c\t%d\n", i, students[i]->name, students[i]->number, students[i]->assignment, students[i]->score);
                }
        }
#endif
}
int* s_get_grade(){
        for(int i=0;i<5;i++){
          grade[i]=0;
        }
        for(int i=0;i<MAX_STUDENTS;i++){
              if (students[i]!= NULL&&students[i]->assignment=='Y'){
                      if(students[i]->score>8){
                        grade[0]++;
                      }else if(students[i]->score>6){
                        grade[1]++;
                      }else if(students[i]->score>4){
                        grade[2]++;
                      }else if(students[i]->score>2){
                        grade[3]++;
                      }else{
                        grade[4]++;
                      }
              }
        }
        return grade;
}
