#include "company.hpp"
using namespace std;

CompanyTracker::CompanyTracker (int n)
  // initializes the tracker with n students and their 1-person companies
{
  numCompanies = n;
  companies = new Company* [numCompanies];
  for (int i = 0; i < numCompanies; ++i)
      companies[i] = new Company ();

}
void CompanyTracker::cleand(int i){
  //splitting until down to the base
  while(companies[i]->parent != nullptr)
    split(i);
}



CompanyTracker::~CompanyTracker ()
  // deallocates all dynamically allocated memory
{
  for(int i = 0; i<numCompanies; i++){
    cleand(i);
  }

  for (int i = 0; i < numCompanies; ++i)
    delete companies[i];
  delete [] companies;
}

void CompanyTracker::merge (int i, int j)
  /* Merges the largest companies containing students i and j,
     according to the rules described above.
     That is, it generates a new Company object which will
     become the parent company of the largest companies currently
     containing students i and j.
     If i and j already belong to the same company (or are the same),
     merge doesn't do anything.
     If either i or j are out of range, merge doesn't do anything. */
{
  //same company
  if(i == j)
    return;
  //out of range
  if(i < 0 || j < 0 || i > numCompanies || j > numCompanies) 
    return;

  Company* tempi = companies[i];
  Company* tempj = companies[j];
  while(tempi->parent != nullptr){
    tempi= tempi->parent;
  }
  while(tempj->parent != nullptr){
    tempj = tempj->parent;
  }
  //in same company (wrote before finished bool)
  if(tempj == tempi) return;
  //setting the new company
  Company* x = new Company(tempi, tempj);
  //making the biggest company inside the newest
  tempi->parent = x;
  tempj->parent = x;
  //says it is in the same company
}

void CompanyTracker::split (int i)
  /* Splits the largest company that student i belongs to,
     according to the rules described above.
     That is, it deletes that Company object, and makes sure that
     the two subcompanies have no parent afterwards.
     If i's largest company is a 1-person company, split doesn't do anything.
     If i is out of range, split doesn't do anything. */
{
  //1 man company
  if(companies[i]->parent == nullptr) return;
  //i is out of range
  if(i < 0 || i > numCompanies) return;
  //find biggest company
  Company * temp = companies[i];
  while(temp->parent != nullptr){
    temp = temp->parent;
  }
  //reorganize pointers to split
  temp->merge1->parent = nullptr;
  temp->merge2->parent = nullptr;
  delete temp;
}

bool CompanyTracker::inSameCompany (int i, int j)
  /* Returns whether students i and j are currently in the same company.
     Returns true if i==j.
     Returns false if i or j (or both) is out of range. */
{
  //if pointing to the same company
  if(i == j) return true;
  //if i is out of range
  if(i < 0 || j < 0 || i > numCompanies || j > numCompanies)  
    return false;
  //finding top of both
  Company* tempi = companies[i];
  Company* tempj = companies[j];
  while(tempi->parent != nullptr){
    tempi= tempi->parent;
  }
  while(tempj->parent != nullptr){
    tempj = tempj->parent;
  }
  //searching down to see if it is inside
  if(tempj == tempi){
    return true;
  }
  return false;
}
