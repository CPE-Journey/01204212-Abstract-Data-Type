#include <stdio.h>

int len(char *str){
    int l = 0;
    while(*str){
        l++;
        str++;
    }
    return l;
}

int main(){
    char a[50000];
    char b[50000];
    char res[50000];
    int r = 0,i,j,diff;
    int hasCarry = 0;

    scanf("%s",a);
    scanf("%s",b);

    int uniLen,la = len(a),lb = len(b);
    if(la>lb){
        uniLen = la;
        diff = la-lb;
    }
    else{
        uniLen = lb;   
        diff = lb-la; 
    }

    for(i=uniLen-1;i>=0;i--){
        int digit;
        
        if(i>=diff){
            if(la>lb){digit = (int)a[i]+(int)b[i-diff]-96;}
            else{digit = (int)b[i]+(int)a[i-diff]-96;}
        }
        else{
            if(la>lb){digit = (int)a[i]-48;}
            else{digit = (int)b[i]-48;}
        }
        

        if(hasCarry){digit++;}
        
        if(digit>=10){
            hasCarry = 1;
            digit -= 10;
        }
        else{hasCarry = 0;}
        
        res[r] = (char)digit+48;
        r++;
        // break;
    }
    if(hasCarry){
        res[r] = '1';
        res[r+1] = '\0';
    }
    
    for(i=len(res)-1;i>=0;i--){
        if(48 <= (int)res[i] && (int)res[i] <= 57){
            printf("%c",res[i]);
        }
    }
}