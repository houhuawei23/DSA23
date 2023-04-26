/*bm匹配算法*/
int bm(char *s, char *p)
{
    int i, j, k, m, n, *bc, *gs;
    m = strlen(s);
    n = strlen(p);
    bc = (int *)malloc(256 * sizeof(int));
    gs = (int *)malloc(n * sizeof(int));
    preBmBc(p, n, bc);
    preBmGs(p, n, gs);
    i = 0;
    while (i <= m - n) {
        j = n - 1;
        while (j >= 0 && p[j] == s[i + j])
            j--;
        if (j < 0) {
            free(bc);
            free(gs);
            return i;
        }
        k = bc[s[i + j]];
        i += (j - k) > gs[j] ? (j - k) : gs[j];
    }
    free(bc);
    free(gs);
    return -1;
}

/*bm算法预处理*/
void preBmBc(char *p, int m, int *bc)
{
    int i;
    for (i = 0; i < 256; i++)
        bc[i] = -1;
    for (i = 0; i < m; i++)
        bc[p[i]] = i;
}
/**/
void preBmGs(char *p, int m, int *gs)
{
    int i, j, *suffix;
    suffix = (int *)malloc(m * sizeof(int));
    suffix = (int *)malloc(m * sizeof(int));
    /*计算后缀数组*/
    for (i = 0; i < m; i++)
        suffix[i] = -1;
    for (i = 0; i < m - 1; i++) {
        j = i;
        int k = 0;
        while (j >= 0 && p[j] == p[m - 1 - k]) {
            j--;
            k++;
            suffix[k] = j + 1;
        }
    }
    /*计算gs数组*/
    for (i = 0; i < m; i++)
        gs[i] = m;
    j = 0;
    for (i = m - 1; i >= 0; i--) {
        if (suffix[i] == i + 1) {
            for (; j < m - 1 - i; j++) {
                if (gs[j] == m)
                    gs[j] = m - 1 - i;
            }
        }
    }
    for (i = 0; i <= m - 2; i++)
        gs[m - 1 - suffix[i]] = m - 1 - i;
    free(suffix);
}

/*测试*/

int main(){
    char *s = "abab"
}