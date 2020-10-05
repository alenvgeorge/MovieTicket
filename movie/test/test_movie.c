#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include<string.h>

/* Modify these two lines according to the project */
#include <movie.h>
#define PROJECT_NAME    "Movie"

/* Prototypes for all the test functions */
void test_admin(void);
void test_addM(void);
void test_userReg(void);
void test_userLogin(void);
void test_searchM(void);
void test_viewM(void);
void test_book(void);
void test_viewB(void);

/* Start of the application test */
int main() {
/* Note: Do not edit START*/
  /*Initialize and setup the Test Framework */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();
  CU_pSuite suite = CU_add_suite(PROJECT_NAME, 0, 0);
/* Note: Do not edit END */


  /* Add your test functions in this format for testing*/
  CU_add_test(suite,"admin",test_admin);
  CU_add_test(suite,"addM",test_addM);
  CU_add_test(suite,"userReg",test_userReg);
  CU_add_test(suite,"userLogin",test_userLogin);
  CU_add_test(suite,"searchMovie",test_searchM);
  CU_add_test(suite,"viewMovie",test_viewM);
  CU_add_test(suite,"BookTicket",test_book);
  CU_add_test(suite,"ViewBooked",test_viewB);


/* Note: Do not edit START*/
  /* Setup Test Framework to output the result to Screen */
  CU_basic_set_mode(CU_BRM_VERBOSE);

  /* run the unit test framework*/
  CU_basic_run_tests();

  /* Cleaning the Resources used by Unit test framework */
  CU_cleanup_registry();
/* Note: Do not edit END */
  return 0;
}

/* Write all the test functions */

void test_admin(void)
{
    CU_ASSERT(1==admin_login("admin","admin24"));

}
void test_addM(void)
{
  CU_ASSERT(0==strcmp("Movie Details Added Successfully",add_movies(1,"onward","7:30PM","24 September, 2020", 200,60)));
}
void test_userReg(void)
{
  CU_ASSERT(0==strcmp("User Registration Successful", user_reg("Alen V George", "alen", "123", "9388094648")));
}

void test_userLogin(void)
{
  CU_ASSERT(0==strcmp("Not a registered user", user_login("alsfaafasfen","1234")));
  CU_ASSERT(0==strcmp("Login successful", user_login("alen","123")));
}
void test_searchM(void)
{
  CU_ASSERT(0==strcmp("Movie Found", search("onward")));
}  
void test_viewM(void)
{ 
  CU_ASSERT(0==view_movies());
}
void test_book(void)
{
  CU_ASSERT(0==strcmp("Details Successfully Saved", book_tickets("onward", 2)));                     
}

void test_viewB(void)
{
  CU_ASSERT(0==strcmp("Showing Booked tickets", view_booked());    
}
  
