//
//  main.c
//  KuCoin Bot Estimator
//
//  Created by Kevin Ramos on 9/15/21.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    float investment = 0;
    float interestRate = 0;
    int flag = 1;
    int ans = 0;
    
    while(flag){
        printf("Beginning total and interest rate: %f %f\n", investment, interestRate);
        
        printf("Enter starting investment.\n");
        scanf("%f", &investment);
        
        printf("Enter interest rate in percentage\n");
        scanf("%f", &interestRate);
        interestRate/=100;
        
        printf("\nYou entered: %f\n", interestRate);
        
        printf("compounding...\n");
        
        for(int i = 0; i < 365; i++){
            investment= investment + investment*interestRate;
            if(i == 6){
                printf("after one week: %f\n", investment);
            } else if(i==31){
                printf("after one month: %f \n", investment);
            } else if(i==132){
                printf("after 1/2 year: %f\n", investment);
            } else if(i==354){
                printf("after one year: %f\n", investment);
            }
        }
        printf("Would you like to draw a different investment?\n1 for yes 2 for no.\n");
        scanf("%d", &ans);
        if(ans == 2){
            flag = 0;
        } else if(ans != 1 && ans != 2){
            printf("existing...\n");
        }
    }
    return 0;
}
