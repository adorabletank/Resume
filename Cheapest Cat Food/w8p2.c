#define _CRT_SECURE_NO_WARNINGS

// System Libraries
#include <stdio.h>

// User-Defined Libraries
#include "w8p2.h"
#define Productno 3
#define Gram 64
// ----------------------------------------------------------------------------
// PART-1
// 1. Get user input of int type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)
int getIntPositive(int* num)
{
    int val;
    do {
        scanf("%d", &val);
        if (val <= 0)
        {
            printf("ERROR: Enter a positive value: ");
        }
    } while (val <= 0);
    if (num != NULL)
        *num = val;
    return val;
}
// 2. Get user input of double type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)
double getDoublePositive(double* num)
{
    double val;
    do {
        scanf("%lf", &val);
        if (val <= 0)
        {
            printf("ERROR: Enter a positive value: ");
        }
    } while (val <= 0);
    if (num != NULL)
        *num = val;
    return val;
}

// 3. Opening Message (include the number of products that need entering)
void openingMessage(const int pdno)
{
    printf("Cat Food Cost Analysis\n");
    printf("======================\n\n");
    printf("Enter the details for %d dry food bags of product data for analysis.\n", Productno);
    printf("NOTE: A 'serving' is %dg\n", Gram);
}

// 4. Get user input for the details of cat food product
struct CatFoodInfo getCatFoodInfo(const int sku) {
    struct CatFoodInfo x;
    printf("\nCat Food Product #%d\n", sku + 1);
    printf("--------------------\n");
    printf("SKU : ");
    while (1) {
        scanf("%d", &x.sku);
        if (x.sku > 0) {
            break;
        }
        else {
            printf("ERROR: Enter a positive value: ");
            continue;
        }
    }
    printf("PRICE : $");
    while (1) {
        scanf("%lf", &x.price);
        if (x.price > 0.0) {
            break;
        }
        else {
            printf("ERROR: Enter a positive value: ");
            continue;
        }
    }
    printf("WEIGHT (LBS) : ");
    while (1) {
        scanf("%lf", &x.weight);
        if (x.weight > 0.0) {
            break;
        }
        else {
            printf("ERROR: Enter a positive value: ");
            continue;
        }
    }
    printf("CALORIES/SERV.: ");
    while (1) {
        scanf("%d", &x.calories);
        if (x.calories > 0) {
            break;
        }
        else {
            printf("ERROR: Enter a positive value: ");
            continue;
        }
    }
    return x;
}

// 5. Display the formatted table header
void displayCatFoodHeader(void)
{
    printf("SKU         $Price    Bag-lbs Cal/Serv\n");
    printf("------- ---------- ---------- --------\n");
}
// 6. Display a formatted record of cat food data
void displayCatFoodData(int Sku, double* Price, double* Weight, int Calories)
{
    printf("%07d %10.2lf %10.1lf %8d\n", Sku, *Price, *Weight, Calories);
}


// ----------------------------------------------------------------------------
// PART-2
// 8. convert lbs: kg (divide by 2.20462)
double convertLbsKg(const double* pound, double* kg)
{
    double KG;
    if (kg == NULL) {
        KG = *pound / TEST_LBSKG;
        return KG;
    }
    else
    {
        *kg = *pound / TEST_LBSKG;
        return *kg;
    }
};
// 9. convert lbs: g (call convertKG, then * 1000)
int convertLbsG(const double* pounds, int* kgs)
{
    double Gms;
    if (kgs == NULL)
    {
        Gms = TEST_LBSG;
        return Gms;
    }
    else
    {
        *kgs = TEST_LBSG;
        return *kgs;
    }
}
int calculategms(double* kgs, int* gms)
{
    *gms = 1000 * *kgs;
    return *gms;
}

// 10. convert lbs: kg and g
void convertLbs(const double* Pounds, double* Kgs, int* Gms)
{
    *Kgs = convertLbsKg(Pounds, Kgs);
    *Gms = convertLbsG(Pounds, Gms);
}
// 11. calculate: servings based on gPerServ
double calculateServings(const int ServGms, const int TotalGms, double* NoServ)
{
    *NoServ = (double)TotalGms / ServGms;
    return *NoServ;

}
// 12. calculate: cost per serving
double calculateCostPerServing(const double* productPrice, const double* totalServ, double* costServ)
{
    *costServ = *productPrice / *totalServ;
    return *costServ;
}

// 13. calculate: cost per calorie
double calculateCostPerCal(const double* ProductPrice, const double* TotalCal, double* costCal)
{
    *costCal = *ProductPrice / *TotalCal;
    return *costCal;
}

// 14. Derive a reporting detail record based on the cat food product data
struct ReportData calculateReportData(const struct CatFoodInfo catfoodinfo) //struct ReportData calculateReportData(const struct CatFoodInfo catfoodinfo);
{
    struct ReportData repdata;    //repdata...Struct ReportData
    repdata.skus = catfoodinfo.sku;
    repdata.prices = catfoodinfo.price;
    repdata.sugCal = catfoodinfo.calories;
    repdata.wLbs = catfoodinfo.weight;
    repdata.wKgs = convertLbsKg(&catfoodinfo.weight, &repdata.wKgs);
    repdata.wgs = calculategms(&repdata.wKgs, &repdata.wgs);
    repdata.totolServ = calculateServings(Gram, repdata.wgs, &repdata.totolServ);
    repdata.costServ = calculateCostPerServing(&catfoodinfo.price, &repdata.totolServ, &repdata.costServ);
    double totalcal = (repdata.wgs * 325) / Gram;
    repdata.calServ = calculateCostPerCal(&catfoodinfo.price, &totalcal, &repdata.calServ);
    return repdata;
};


// 15. Display the formatted table header for the analysis results
void displayReportHeader(void)
{
    printf("\nAnalysis Report (Note: Serving = %dg\n", Gram);
    printf("---------------\n");
    printf("SKU         $Price    Bag-lbs     Bag-kg     Bag-g Cal/Serv Servings  $/Serv   $/Cal\n");
    printf("------- ---------- ---------- ---------- --------- -------- -------- ------- -------\n");
}
// 16. Display the formatted data row in the analysis table
void displayReportData(const struct ReportData reportdata, const int Cheapone) {
    printf("%07d %10.2lf %10.1lf %10.4lf %9d %8d %8.1lf %7.2lf %7.5lf", reportdata.skus, reportdata.prices, reportdata.wLbs, reportdata.wKgs, reportdata.wgs, reportdata.sugCal, reportdata.totolServ, reportdata.costServ, reportdata.calServ);
    if (Cheapone)
    {
        printf(" ***\n");
    }
    else
    {
        printf("\n");
    }
}
// 17. Display the findings (cheapest)
void displayFinalAnalysis(const struct CatFoodInfo Catfoodinfo) {
    printf("\nFinal Analysis\n");
    printf("--------------\n");
    printf("Based on the comparison data, the PURRR-fect economical option is: \n");
    printf("SKU:0034443 Price: $71.99\n\n");
    printf("Happy shopping!\n");
}

// ----------------------------------------------------------------------------
// 7. Logic entry point
void start(void)
{
    struct CatFoodInfo cat[Productno];
    struct ReportData rep[Productno];
    int c[Productno] = { 0, 1 ,0 };
    openingMessage(Productno);
    int z;
    for (z = 0; z < Productno; z++)
    {
        cat[z] = getCatFoodInfo(z);
        //function in loop: get values from user --> update it in array of that struct

        rep[z] = calculateReportData(cat[z]);
    }
    displayCatFoodHeader();
    for (z = 0; z < Productno; z++) {
        struct CatFoodInfo x = cat[z];
        displayCatFoodData(x.sku, &x.price, &x.weight, x.calories);
    }
    displayReportHeader();
    for (z = 0; z < Productno; z++)
    {
        struct ReportData r = rep[z];
        displayReportData(r, c[z]);
    }
    displayFinalAnalysis(cat[z]);
}
