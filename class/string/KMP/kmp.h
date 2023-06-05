/*************************************************************
    date: 
    copyright: Zhu En
    DO NOT distribute this code without my permission.
**************************************************************/
void KmpGenNext(char* p, int* next);
//int KmpFindSub(char* t, char* p);
int KmpFindSubWithNext(char* t, char* p, int* next);
//void KmpFindAll(char* t, char* p, int* finds, int len, int& count);