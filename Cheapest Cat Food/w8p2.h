// ----------------------------------------------------------------------------
// defines/macros
#define Productno 3
#define Gram 64
#define TEST_LBSKG 2.20462
#define TEST_LBSG 2494
#define TEST_LBS 5.5
// ---------------------------------------
// Function prototypes
// ---------------------------------------
int testIntFunction(void);
int testDoubleFunction(void);
int testConvertLbsKg(void);
int testConvertLbsG(void);
int testConvertLbs(void);
// ----------------------------------------------------------------------------
// structures
struct CatFoodInfo
{
	int sku;
	double price;
	double weight;
	int calories;
};
struct ReportData
{
	int skus;
	double prices;
	int sugCal;
	double wLbs;
	double wKgs;
	int wgs;
	double totolServ;
	double costServ;
	double calServ;
};

// ----------------------------------------------------------------------------
// function prototypes
// PART-1
// 1. Get user input of int type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)
int getIntPositive(int* i);

// 2. Get user input of double type and validate for a positive non-zero number
//    (return the number while also assigning it to the pointer argument)
double getDoublePositive(double* d);

// 3. Opening Message (include the number of products that need entering)
void openingMessage(const int pdno);  //product number

// 4. Get user input for the details of cat food product
struct CatFoodInfo getCatFoodInfo(const int sku);  //increase the readability, and make it look clean.

// 5. Display the formatted table header
void displayCatFoodHeader(void);
// 6. Display a formatted record of cat food data
void displayCatFoodData(int Sku, double* Price, double* Weight, int Calories);

// ----------------------------------------------------------------------------
// PART-2
// 8. convert lbs: kg
double convertLbsKg(const double* pound, double* kg);

// 9. convert lbs: g
int convertLbsG(const double* pounds, int* kgs);

// 10. convert lbs: kg / g
void convertLbs(const double* Pounds, double* Kgs, int* Gms);

// 11. calculate: servings based on gPerServ
double calculateServings(const int ServGms, const int TotalGms, double* NoServ);

// 12. calculate: cost per serving
double calculateCostPerServing(const double* productPrice, const double* totalServ, double* costServ);

// 13. calculate: cost per calorie
double calculateCostPerCal(const double* productPrice, const double* TotalCal, double* costCal);
// 14. Derive a reporting detail record based on the cat food product data
struct ReportData calculateReportData(const struct CatFoodInfo catfoodinfo);

// 15. Display the formatted table header for the analysis results
void displayReportHeader(void);
// 16. Display the formatted data row in the analysis table
void displayReportData(const struct ReportData reportdata, const int Cheapone);

// 17. Display the findings (cheapest)
void displayFinalAnalysis(const struct CatFoodInfo Catfoodinfo);

// ----------------------------------------------------------------------------
// 7. Logic entry point
void start(void);
