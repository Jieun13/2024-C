#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct poly{
    double coef;  
    int xExpon; 
    int yExpon;  
};

void getPoly (struct poly list[], int size){
    for(int i=0; i<size; i++){
        printf("다항식의 %d번째 항을 계수, x의 차수, y의 차수 형식으로 하나씩 입력해주세요 : ", i+1);
        scanf("%lf %d %d", &list[i].coef, &list[i].xExpon, &list[i].yExpon);
    }
}

void prnPoly (struct poly list[], int size){ 

    for(int i=0; i<size; i++){
        if(i!=0){  
            if(list[i].coef>0) printf(" +"); 
            else printf(" "); 
        }
        if((list[i].xExpon==0)&&(list[i].yExpon==0)) { 
            printf("%.2lf", list[i].coef);
        }
        else{
            if(list[i].xExpon==0) { 
                printf("%.2lfy^%d", list[i].coef, list[i].yExpon);
            }
            else if(list[i].yExpon==0) { 
                printf("%.2lfx^%d", list[i].coef, list[i].xExpon);
            }
            else { 
                printf("%.2lfx^%dy^%d", list[i].coef, list[i].xExpon, list[i].yExpon);
            }
        }
    }
    printf("\n");
}

void multPoly(struct poly list1[], int size1, struct poly list2[], int size2, struct poly list3[]){
    int cnt1, cnt2, cnt3 = 0;
    for(cnt1=0; cnt1<size1; cnt1++){
        for(cnt2=0; cnt2<size2; cnt2++){
            list3[cnt3].coef = list1[cnt1].coef * list2[cnt2].coef;  
            list3[cnt3].xExpon = list1[cnt1].xExpon + list2[cnt2].xExpon; 
            list3[cnt3].yExpon = list1[cnt1].yExpon + list2[cnt2].yExpon; 
            cnt3 = cnt3 + 1;
        }
    }
}

int cmpExpon(const void *p1, const void *p2){
    int deltaX = ((struct poly *)p1)->xExpon - ((struct poly *)p2)->xExpon;
    if(deltaX==0){ 
        int deltaY = ((struct poly *)p1)->yExpon - ((struct poly *)p2)->yExpon; 
        return (deltaY>0)? -1 : ((deltaY<0)? 1: 0);    
    }
    else if(deltaX>0) return -1;  
    else return 1;                
}

int sortPoly(struct poly list[], struct poly result[], int size){
    int j=0, i=0;
    qsort(list, size, sizeof(*list), cmpExpon);     

    result[j]=list[0];                              
    for(i=1; i<size; i++){                          
        if (cmpExpon(&result[j], &list[i])==0){     
            result[j].coef += list[i].coef;         
        }
        else{                                       
            j++;                                    
            result[j] = list[i];                    
        }
    }
    return j+1;                                     
}

int main(){
    int size1, size2, size3, i;

    printf("size of A? : ");
    scanf("%d", &size1);
    struct poly list1[size1];
    getPoly (list1, size1);

    printf("\nsize of B? : ");
    scanf("%d", &size2);
    struct poly list2[size2];
    getPoly (list2, size2);

    printf("A : ");
    prnPoly(list1, size1);
    printf("B : ");
    prnPoly(list2, size2);

    printf("---------------------------\n");

    size3 = size1 * size2;
    struct poly list3[size3];
    multPoly(list1, size1, list2, size2, list3);

    size3 = (sizeof(list3)/sizeof(list3[0]));
    struct poly resultList[size3];
    
    size3 = sortPoly(list3, resultList, size3);

    printf("result : ");
    prnPoly(resultList, size3);
}