#include <stdio.h>
#include <stdlib.h>
#include <time.h>


unsigned long int cmp=0,mvs=0;
double T;


typedef struct st
{
    double a;
    unsigned long int c;
} p;


struct bin_tree{
    int data;
    struct bin_tree *right,*left;
};


typedef struct bin_tree mod;
int int_search(int a, int n, p *pack){
    int q =0,w=(n-1);
    while (q<=w&&a>=pack[q].c&&a<=pack[w].c){
        int qwe=(int)(q+(((double)(w-q)/(pack[w].c-pack[q].c))*(a-pack[q].c)));
            if (pack[qwe].c==a){
                cmp++;
                return qwe;
            }
                        if (pack[qwe].c < a){
                            q=qwe+1;
                            cmp++;
                        }
                        else {
                            w=qwe-1;
                            cmp++;
                        }
            mvs++;
    }
    return 3;
}

void insert(mod ** tree, int val){
    mod *temp=NULL;
    if(!(*tree)){
        temp=(mod*)malloc(sizeof(mod));
        temp->left=temp->right=NULL;
        temp->data=val;
        *tree=temp;
        cmp++;
        return;
    }
            if(val<=(*tree)->data){
                insert(&(*tree)->left,val);
                cmp++;
                mvs++;
            }
            else if(val>=(*tree)->data){
                insert(&(*tree)->right,val);
                cmp++;
                mvs++;
            }
}


void print_in(mod *tree){
    if (tree){
        print_in(tree->left);
        printf("[%d]",tree->data);
        print_in(tree->right);
    }
}


void delete_tree(mod *tree){
    if (tree) {
        delete_tree(tree->left);
        delete_tree(tree->right);
        free(tree);
    }
}
        mod* search(mod **tree,int val){
            if(!(*tree)){
                cmp++;
                return NULL;
            }

        if(val < (*tree)->data){
            cmp++;
            mvs++;
            search(&((*tree)->left),val);
        }
    else if(val>(*tree)->data){
        cmp++;
        mvs++;
        search(&((*tree)->right),val);
    }
        else if(val==(*tree)->data){
            cmp++;
            return *tree;
        }
    return *tree;
}


void sort_bubble(unsigned long int n,p *pack){
    unsigned long int i, j, tmp;
    for (i=0;i<n-1;i++){
        for (j=0;j<n-(1+i);j++){
            if(pack[j].c>pack[j+1].c){
                tmp=pack[j].c;
                pack[j].c=pack[j+1].c;
                pack[j+1].c=tmp;
                cmp++;
            }
            mvs++;

        }
    }
}


void insert_sort(unsigned long int n,p *pack){
    unsigned int num;
    int l,i;
    for (i=1;i<n;i++){
        num = pack[i].c;
        l=i-1;
        while(l>=0&&pack[l].c>num){
            pack[l+1].c=pack[l].c;
            l=l-1;
            mvs++;
            cmp++;
        }
        pack[l+1].c=num;
        mvs++;
    }
}


void quick_sort(p *pack, unsigned long int low, unsigned long int high){
    unsigned long int l=low,h=high;
    static unsigned long int i,sr,min,max;
    p temp;
    min=l;
    max=h;
    for (i=l;i<h;i++) {
        if (pack[i].c>pack[max].c) max=i;
        if (pack[i].c<pack[min].c) min=i;
    }
    sr=(pack[max].c+pack[min].c)/2;
    while (l<=h){
        while (pack[l].c<sr) {
            l++;
            mvs++;
        }
        while (pack[h].c>sr) {
            h--;
            mvs++;
        }
        if (l<=h) {
            temp=pack[l];
            pack[l]=pack[h];
            pack[h]=temp;
            h--;
            l++;
            cmp++;
        }
        mvs++;
    }
    if (low<h){
        quick_sort(pack,low,h);
        cmp++;
    }
    if (high > l){
        quick_sort(pack,l,high);
        cmp++;
    }
}


int linearSearch (unsigned int a,int n,p *pack){
    int i;
    unsigned int qwe;
    for (i=0;i<n;i++){
        qwe=pack[i].c;
        if (a==qwe){
            cmp++;
            return i;
        }
        mvs++;
    }
    return 3;
}


int main(int argc,char *argv[]){
    mod *root=NULL, *min;
    unsigned long int *massive;
    unsigned int key;
    long int k,i;
    double time1,time2;
    int ans1,ans2,ans3,value,m,s,exit=2;
    while (exit==2){
        printf("enter size of array:\n");
        scanf("%i",&s);
        p *pack;
        pack = (struct st *) malloc(s*sizeof(struct st));
        printf("enter:\n1 for read from a file.\n2 for keyboard input.\n3 for random data.\n");
        scanf("%d",&ans1);
        switch (ans1){
            case 1:{
                FILE *f;
                char rz[255];
                if (!(f=fopen(argv[1],"rb")) || (argc == 1)) {
                    printf("enter the file name\n");
                    scanf("%s", rz);
                    if ( !(f = fopen(rz, "rb"))) {
                        printf("can not open this file\n");
                        return 0;
                    }
                }
                fseek(f,0,SEEK_SET);
                for (i=0;i<s;i++){
                    fscanf(f, "%lf,%lu\n",&pack[i].a,&pack[i].c);
                }
                fclose(f);
                break;}
            case 2:{
                massive=(unsigned long int *)malloc(s*sizeof(unsigned long int));
                printf("enter your elements:\n");
                for (i = 0; i < s; i++) {
                    scanf("%lu", &massive[i]);
                    pack[i].c = massive[i];
                    pack[i].a = 1.1;
                }
                break;
            }
            case 3: {
                massive=(unsigned long int *) malloc(s * sizeof(unsigned long int));
                printf("enter your elements:\n");
                for (i = 0; i < s; i++) {
                    massive[i]=(unsigned long)(rand()%10000);
                    pack[i].c=massive[i];
                    pack[i].a=1.1;
                }
                break; }
            default:{
                printf("error entry\n");
                break; }
        }
        printf("choose a way of sort:\n 1 for bubble\n 2 for quick\n 3 for insertion\n 4 for tree\n");
        scanf("%d", &ans2);
        switch (ans2) {
            case 1: {
                time1 = clock();
                sort_bubble((unsigned long) s, pack);
                time2 = clock();
                T = (time2 - time1) / (double) CLOCKS_PER_SEC;
                printf("estimated time to sort:  %lf sec\n", T);
                printf("moves through array: [%lu]\n", mvs);
                printf("number of compare: [%lu]\n", cmp);
                mvs = 0;
                cmp = 0;
                T = 0;
                break; }
            default: {
                printf("error entry\n");
                break; }
            case 2: {
                time1 = clock();
                quick_sort(pack, 0, (unsigned long) (s - 1));
                time2 = clock();
                T = (time2 - time1) / (double) CLOCKS_PER_SEC;
                printf("estimated time to sort:  %lf sec\n", T);
                printf("moves through array: [%lu]\n", mvs);
                printf("number of compare: [%lu]\n", cmp);
                mvs = 0;
                cmp = 0;
                T = 0;
                break; }
            case 3: {
                time1 = clock();
                insert_sort((unsigned long) s, pack);
                time2 = clock();
                T = (time2 - time1) / (double) CLOCKS_PER_SEC;
                printf("time to sort:  %lf sec\n", T);
                printf("moves through array: [%lu]\n",mvs);
                printf("number of compare: [%lu]\n",cmp);
                mvs=0;
                cmp=0;
                T=0;
                break; }
            case 4: {
                time1 = clock();
                for (k = 0; k < s - 1; k++) {
                    value = (int) pack[k].c;
                    insert(&root, value); }
                time2 = clock();
                T = (time2 - time1) / (double) CLOCKS_PER_SEC;
                printf("estimated time to sort:  %lf sec\n", T);
                printf("moves through array: [%lu]\n", mvs);
                printf("number of compare: [%lu]\n", cmp);
                mvs = 0;
                cmp = 0;
                T = 0;
                printf("enter element to search: \n");
                scanf("%d", &key);
                time1 = clock();
                min = search(&root, key);
                time2 = clock();
                T = (time2 - time1) / (double) CLOCKS_PER_SEC;
                if ( min ) {
                    printf("estimated time to sort:  %lf sec\n", T);
                    printf("moves through array: [%lu]\n", mvs);
                    printf("number of compare: [%lu]\n", cmp);
                    mvs = 0;
                    cmp = 0;
                    T = 0;
                } else {
                    printf("element not found in tree.\n");
                    mvs = 0;
                    cmp = 0;
                    T = 0; }
                break; }
        }
        printf("do you want to see sort massive?:\n 1 for yes\n 2 for no\n");
        scanf("%d", &m);
        switch (m) {
            case 1: {
                printf("sort array:\n");
                for (i = 0; i < s; i++) {
                    printf("%lu ", pack[i].c); }
                break; }
            default:
                break; }
        printf("\nEnter element:\n");
        scanf("%d", &key);
        printf("choose a way of search:\n 1 for line\n 2 for interpol\n");
        scanf("%d", &ans3);
        switch (ans3) {
            case 1: {
                time1 = clock();
                k = linearSearch(key, s, pack);
                time2 = clock();
                T = (time2 - time1) / (double) CLOCKS_PER_SEC;
                if ( k != -1 ) {
                    printf("The index of the element is %ld\n", k);
                    printf("\nEstimated time to sort:  %lf sec\n", T);
                    printf("\nMoves through array: [%lu]", mvs);
                    printf("\nNumber of compare [%lu]", cmp);
                    mvs = 0;
                    cmp = 0;
                    T = 0; }
                else {
                    printf("element is not found\n");
                    mvs = 0;
                    cmp = 0;
                    T = 0; }
                break; }
            case 2: {
                time1 = clock();
                value = int_search(key, s, pack);
                time2 = clock();
                T = (time2 - time1) / (double) CLOCKS_PER_SEC;
                if ( value != -1 ) {
                    printf("index element is %d\n", value);
                    printf("estimated time to sort:  %lf sec\n", T);
                    printf("moves through array: [%lu]", mvs);
                    printf("number of compare:  [%lu]", cmp);
                    mvs = 0;
                    cmp = 0;
                    T = 0;
                } else
                    printf("element not found\n");
                break; }
            default: {
                printf("error entry\n");
                break; }
        }
        printf("\ndo you want exit?\n1 for yes\n2 for no\n");
    scanf("%d",&exit);}
    return 0;
}