struct HNode { 
    int key; 
    HNode* next;
};
struct LHTable {
    HNode* pn; 
    int n; 
};

LHTable* ILH_Create(int n);
void ILH_Free(LHTable* pt);
bool ILH_InsKey(LHTable* pt, int x);
bool ILH_FindKey(LHTable* pt, int x);
bool ILH_DelKey(LHTable* pt, int x);
void ILH_Print(LHTable *pt);
