#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;
#define NODEOPT 0
#define NODENUM 1
int add(int a,int b){
    return a+b;
}
int sub(int a,int b){
    return a-b;
}
int mul(int a,int b){
    return a*b;
}
int dev(int a,int b){
    return a/b;
}
typedef int (*func)(int,int);
struct entry{
    char *key;
    func funptr;
}optkv[4]={{"add",add},{"sub",sub},{"mul",mul},{"dev",dev}};
char *highlevel[2]={"mul","dev"};
char *lowlevel[2]={"add","sub"};
char *myopt[4]={"add","sub","mul","dev"};
struct entryarr{
    char *str[50];
    int len;
};
struct expr{
    expr *left;//如果是opt则有左右表达式，如果不是opt则这两个属性是null
    expr *right;
    char *str;
    bool isopt;
};
void createTreeStr(char *str,entryarr* entryarr1){
    char *nodeopt=(char *)malloc(50);
    char *nodenum=(char *)malloc(50);
    memset(nodenum,0,50);
    memset(nodeopt,0,50);
    int flag=NODENUM;
    int k=0;
    for(int i=0;i<strlen(str);i++){
        char tmp[2]={str[i]};
        if(tmp[0]>47&&tmp[0]<60){
            if(flag==NODEOPT){
                flag=NODENUM;
                memset(nodenum,0,50);
                entryarr1->str[k]=(char *)malloc(strlen(nodeopt));
                strcpy(entryarr1->str[k],nodeopt);
                k++;
            }
            strcat(nodenum,tmp);
        }else{
            if(flag==NODENUM){
                flag=NODEOPT;
                memset(nodeopt,0,50);
                entryarr1->str[k]=(char *)malloc(strlen(nodenum));
                strcpy(entryarr1->str[k],nodenum);
                k++;
            }
            strcat(nodeopt,tmp);
            flag=0;
        }

    }
    if(flag==NODENUM){
        flag=NODEOPT;
        memset(nodeopt,0,50);
        entryarr1->str[k]=(char *)malloc(strlen(nodenum));
        strcpy(entryarr1->str[k],nodenum);
        k++;
    } else{
        flag=NODENUM;
        memset(nodenum,0,50);
        entryarr1->str[k]=(char *)malloc(strlen(nodeopt));
        strcpy(entryarr1->str[k],nodeopt);
        k++;
    }
    entryarr1->len=k;
    free(nodeopt);
    free(nodenum);
}

expr* createTree(char **exprstrs,int len){
    cout<<"============================================"<<endl;
    cout<<"接收到的数据";
    for(int i=0;i<len;i++){
        cout<<exprstrs[i]<<" ";
    }
    cout<<"　总共："<<len<<"个元素"<<endl;
    cout<<"============================================"<<endl;
    expr *myexpr=(expr *)malloc(sizeof(expr));
    int hasopt=0;//0表示没有，１表示１优先级别，２表示２优先级别（优先级１－>n）
    int lowlevelindex=-1;
    int highlevelindex=-1;
    for(int i=0;i<len;i++){
        if(strcmp(exprstrs[i],lowlevel[0])==0||strcmp(exprstrs[i],lowlevel[1])==0){
            hasopt=1;
            lowlevelindex=i;
        }else if(strcmp(exprstrs[i],highlevel[0])==0||strcmp(exprstrs[i],highlevel[1])==0){
            hasopt=2;
            highlevelindex=i;
        }
    }
    if(hasopt!=0&&lowlevelindex!=-1){
        myexpr->str=(char *)malloc(strlen(exprstrs[lowlevelindex]));
        memset(myexpr->str,0,strlen(exprstrs[lowlevelindex]));
        strcpy(myexpr->str,exprstrs[lowlevelindex]);
        myexpr->isopt=true;
        char *exprleft[50];
        char *exprright[50];
        memset(exprleft,0,50);
        memset(exprright,0,50);
        for(int i=0;i<lowlevelindex;i++){
            exprleft[i]=(char *)malloc(strlen(exprstrs[i]));
            strcpy(exprleft[i],exprstrs[i]);
        }
        int rlen=0;
        for(int i=lowlevelindex+1,j=0;i<len;i++,j++){
            exprright[j]=(char *)malloc(strlen(exprstrs[i]));
            strcpy(exprright[j],exprstrs[i]);
            rlen++;
        }
        cout<<"============================================"<<endl;
        cout<<"左树：";
        for(int i=0;i<lowlevelindex;i++){
            cout<<exprleft[i]<<endl;
        }
        cout<<"右树：";
        for(int i=0;i<rlen;i++){
            cout<<exprright[i]<<"　";
        }
        cout<<endl;
        cout<<"节点："<<myexpr->str<<endl;
        cout<<"============================================"<<endl;
        myexpr->left=createTree(exprleft,lowlevelindex);
        myexpr->right=createTree(exprright,rlen);
    }else if(hasopt!=0&&highlevelindex!=-1){
        myexpr->str=exprstrs[highlevelindex];
        myexpr->isopt=true;
        char *exprleft[50];
        char *exprright[50];
        memset(exprleft,0,50);
        memset(exprright,0,50);
        for(int i=0;i<highlevelindex;i++){
            exprleft[i]=(char *)malloc(strlen(exprstrs[i]));
            strcpy(exprleft[i],exprstrs[i]);
        }
        int rlen=0;
        for(int i=highlevelindex+1,j=0;i<len;i++,j++){
            exprright[j]=(char *)malloc(strlen(exprstrs[i]));
            strcpy(exprright[j],exprstrs[i]);
            rlen++;
        }
        cout<<"============================================"<<endl;
        cout<<"左树：";
        for(int i=0;i<highlevelindex;i++){
            cout<<exprleft[i]<<endl;
        }
        cout<<"右树：";
        for(int i=0;i<rlen;i++){
            cout<<exprright[i]<<"　";
        }
        cout<<endl;
        cout<<"节点："<<myexpr->str<<endl;
        cout<<"============================================"<<endl;
        myexpr->left=createTree(exprleft,highlevelindex);
        myexpr->right=createTree(exprright,rlen);
    }else{
        myexpr->str=(char *)malloc(strlen(exprstrs[0]));
        memset(myexpr->str,0,strlen(exprstrs[0]));
        strcpy(myexpr->str,exprstrs[0]);
        myexpr->isopt=false;
        myexpr->left=NULL;
        myexpr->right=NULL;
        cout<<"============================================"<<endl;
        cout<<"节点："<<myexpr->str<<endl;
        cout<<"============================================"<<endl;
    }
    return myexpr;

}
int compile(expr *myexpr){

    int a=0;
    int b=0;
    if(myexpr!=NULL){
        if(myexpr->isopt) {
            a=compile(myexpr->left);
            b=compile(myexpr->right);
            cout<<a<<myexpr->str<<b<<endl;
            for(int i=0;i<4;i++){
                if(strcmp(optkv[i].key,myexpr->str)==0){
                    return optkv[i].funptr(a,b);
                }
            }
        }else{
            int c=0;
            stringstream ss;
            string tmp=myexpr->str;
            ss<<tmp;
            ss>>c;
            cout<<"操作数"<<c<<endl;
            ss.clear();
            return c;
        }
    }

}

expr *createExpr(char *str){
    cout<<"---------------------构建语法树-----------------------"<<endl;
    entryarr entryarr1;
    createTreeStr(str,&entryarr1);
    char *exprstrs[50];
    for(int i=0;i<entryarr1.len;i++){
        exprstrs[i]=entryarr1.str[i];
    }
    expr *myexpr=createTree(exprstrs,entryarr1.len);
    cout<<"-----------------------------------------------"<<endl;
    return myexpr;
}
int countExpr(expr *myexpr){
    int res;
    cout<<"---------------------计算语法树-----------------------"<<endl;
    res=compile(myexpr);
    cout<<"-----------------------------------------------"<<endl;
    return res;
}
int mycounter() {
//    char *str="1add12mul3sub8dev2";
    //输入计算表达式
    cout<<"请输入计算表达式,输入后按回车确认："<<endl;
    string str;
    cin>>str;
    char *strexpr=(char *)malloc(str.length());
    strcpy(strexpr,str.c_str());

    //构建计算表达式语法树
    expr *myexpr=createExpr(strexpr);

    //计算语法树
    int res=countExpr(myexpr);

    //输出结果
    cout<<"最终结果是："<<res<<endl;
    return 0;
}