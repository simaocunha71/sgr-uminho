#include <stdio.h>
#include "../includes/controller/sgr.h"
#include "../includes/model/glibWarningAvoid.h"
#include <time.h>

int main(){
    TABLE t,t2,t3; t = t2 = t3 = NULL; int q = 0;
    double time_spent, time_spent2, time_spent3;
    clock_t begin, begin2, begin3, end, end2, end3;

    SGR sgr = NULL;
    begin = clock();
    sgr = load_sgr("./input_files/users_full.csv","./input_files/business_full.csv","./input_files/reviews_1M.csv");
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time spend loading files: %0.2f\n", time_spent);
    printf("Type a number to do the performance test of a query [2-9]: \n");
        while(q != -1){
            if (scanf("%d", &q) <= 9){
                switch (q){
                case 2:
                    begin = clock();
                    t = businesses_started_by_letter(sgr, 'w');
                    end = clock();
                    begin2 = clock();
                    t2 = businesses_started_by_letter(sgr, 't');
                    end2 = clock();
                    begin3 = clock();
                    t3 = businesses_started_by_letter(sgr, 'a');
                    end3 = clock();
                    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                    time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
                    time_spent3 = (double)(end3 - begin3) / CLOCKS_PER_SEC;
                    printf("Time spend on query 2\n");
                    printf(" -> businesses_started_by_letter(sgr, 'w') -> %0.5f ms\n", time_spent*1000);
                    printf(" -> businesses_started_by_letter(sgr, 't') -> %0.5f ms\n", time_spent2*1000);
                    printf(" -> businesses_started_by_letter(sgr, 'a') -> %0.5f ms\n", time_spent3*1000);
                    free_table(t);
                    free_table(t2);
                    free_table(t3);

                    break;
                case 3:
                    begin = clock();
                    t = business_info(sgr, "N3_Gs3DnX4k9SgpwJxdEfw");
                    end = clock();
                    begin2 = clock();
                    t2 = business_info(sgr, "-l5w8_vwKDSUlpr9FSQoqA");
                    end2 = clock();
                    begin3 = clock();
                    t3 = business_info(sgr, "6fT0lYr_UgWSCZs_w1PBTQ");
                    end3 = clock();
                    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                    time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
                    time_spent3 = (double)(end3 - begin3) / CLOCKS_PER_SEC;
                    printf("Time spend on query 3:\n");
                    printf(" -> business_info(sgr,\"N3_Gs3DnX4k9SgpwJxdEfw\") -> %0.5f ms\n", time_spent * 1000);
                    printf(" -> business_info(sgr,\"-l5w8_vwKDSUlpr9FSQoqA\") -> %0.5f ms\n", time_spent2 * 1000);
                    printf(" -> business_info(sgr,\"6fT0lYr_UgWSCZs_w1PBTQ\") -> %0.5f ms\n", time_spent3 * 1000);
                    free_table(t);
                    free_table(t2);
                    free_table(t3);

                    break;
                case 4:
                    begin = clock();
                    t = businesses_reviewed(sgr, "q_QQ5kBBwlCcbL1s4NVK3g");
                    end = clock();
                    begin2 = clock();
                    t2 = businesses_reviewed(sgr, "RNm_RWkcd02Li2mKPRe7Eg");
                    end2 = clock();
                    begin3 = clock();
                    t3 = businesses_reviewed(sgr, "bUHweiErUJ36WGeNrPmEbA");
                    end3 = clock();
                    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                    time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
                    time_spent3 = (double)(end3 - begin3) / CLOCKS_PER_SEC;
                    printf("Time spend query 4:\n");
                    printf(" -> businesses_reviewed(sgr, \"q_QQ5kBBwlCcbL1s4NVK3g\") -> %0.5f ms\n", time_spent*1000);
                    printf(" -> businesses_reviewed(sgr, \"RNm_RWkcd02Li2mKPRe7Eg\") -> %0.5f ms\n", time_spent2*1000);
                    printf(" -> businesses_reviewed(sgr, \"bUHweiErUJ36WGeNrPmEbA\") -> %0.5f ms\n", time_spent3*1000);
                    free_table(t);
                    free_table(t2);
                    free_table(t3);

                    break;
                case 5:
                    begin = clock();
                    t = businesses_with_stars_and_city(sgr, 4, "Portland");
                    end = clock();
                    begin2 = clock();
                    t2 = businesses_with_stars_and_city(sgr, 1, "Portland");
                    end2 = clock();
                    begin3 = clock();
                    t3 = businesses_with_stars_and_city(sgr, 4, "Atlanta");
                    end3 = clock();
                    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                    time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
                    time_spent3 = (double)(end3 - begin3) / CLOCKS_PER_SEC;
                    printf("Time spend on query 5:\n");
                    printf(" -> businesses_with_stars_and_city(sgr, 4, \"Portland\") -> %0.5f ms\n", time_spent*1000);
                    printf(" -> businesses_with_stars_and_city(sgr, 1, \"Portland\") -> %0.5f ms\n", time_spent2 * 1000);
                    printf(" -> businesses_with_stars_and_city(sgr, 4, \"Atlanta\") -> %0.5f ms\n", time_spent3*1000);
                    free_table(t);
                    free_table(t2);
                    free_table(t3);


                    break;
                case 6:
                    begin = clock();
                    t = top_businesses_by_city(sgr, 10);
                    end = clock();
                    begin2 = clock();
                    t2 = top_businesses_by_city(sgr, 50);
                    end2 = clock();
                    begin3 = clock();
                    t3 = top_businesses_by_city(sgr, 100);
                    end3 = clock();
                    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                    time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
                    time_spent3 = (double)(end3 - begin3) / CLOCKS_PER_SEC;
                    printf("Time spend on query 6:\n");
                    printf(" -> top_businesses_by_city(sgr, 10) -> %0.5f ms\n", time_spent*1000);
                    printf(" -> top_businesses_by_city(sgr, 50) -> %0.5f ms\n", time_spent2*1000);
                    printf(" -> top_businesses_by_city(sgr, 100) -> %0.5f ms\n", time_spent3*1000);
                    free_table(t);
                    free_table(t2);
                    free_table(t3);

                    break;

                case 7:
                    begin = clock();
                    t = international_users(sgr);
                    end = clock();
                    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                    printf("Time spend query 7: %0.5f ms\n", time_spent*1000);
                    free_table(t);

                    break;
                case 8:
                    begin = clock();
                    t = top_businesses_with_category(sgr, 4, "Restaurants");
                    end = clock();
                    begin2 = clock();
                    t2= top_businesses_with_category(sgr, 1, "Restaurants");
                    end2 = clock();
                    begin3 = clock();
                    t3 = top_businesses_with_category(sgr, 4, "Pet");
                    end3 = clock();
                    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                    time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
                    time_spent3 = (double)(end3 - begin3) / CLOCKS_PER_SEC;
                    printf("Time spend on query 8:\n");
                    printf(" -> top_businesses_with_category(sgr, 4,\"Restaurants\") -> %0.5f ms\n", time_spent * 1000);
                    printf(" -> top_businesses_with_category(sgr, 1,\"Restaurants\") -> %0.5f ms\n", time_spent2 * 1000);
                    printf(" -> top_businesses_with_category(sgr, 4, \"Pet\") -> %0.5f ms\n", time_spent3*1000);

                    free_table(t);
                    free_table(t2);
                    free_table(t3);

                    break;

                case 9:
                    begin = clock();
                    t = reviews_with_word(sgr, "and");
                    end = clock();
                    begin2 = clock();
                    t2 = reviews_with_word(sgr, "well");
                    end2 = clock();
                    begin3 = clock();
                    t3 = reviews_with_word(sgr, "cook");
                    end3 = clock();
                    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
                    time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
                    time_spent3 = (double)(end3 - begin3) / CLOCKS_PER_SEC;
                    printf("Time spend on query 9:\n");
                    printf(" -> reviews_with_word(sgr,\"and\") -> %0.5f ms\n", time_spent*1000);
                    printf(" -> reviews_with_word(sgr,\"well\") -> %0.5f ms\n", time_spent2*1000);
                    printf(" -> reviews_with_word(sgr,\"cook\") -> %0.5f ms\n", time_spent3*1000);
                    free_table(t);
                    free_table(t2);
                    free_table(t3);

                    break;
                default:
                    break;
                }
                printf("End of test query %d\n",q);
            }
        }

    return 0;
}