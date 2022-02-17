//
//  Containers.cpp
//  CS2-Homework4.2
//
//  Created by Shawn Davidson on 11/7/21.
//

#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>


using namespace std;

// Remove the odd integers from li.
// It is acceptable if the order of the remaining even integers is not
// the same as in the original list.
void removeOdds(list<int>& li)
{
    size_t len = li.size();
    
    for (size_t i = 0; i < len; i++) {
        int item = li.front();
        li.pop_front();
        if (item % 2 == 0)
        {
            li.push_back(item);
        }
    }
}

void test1()
{
    int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
    list<int> x(a, a+8);  // construct x from the array
    assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
    removeOdds(x);
    assert(x.size() == 4);
    vector<int> v(x.begin(), x.end());  // construct v from x
    sort(v.begin(), v.end());
    int expect[4] = { 2, 4, 6, 8 };
    for (int k = 0; k < 4; k++)
        assert(v[k] == expect[k]);
}

// Remove the odd integers from v.
// It is acceptable if the order of the remaining even integers is not
// the same as in the original vector.
void removeOdds(vector<int>& v)
{
    vector<int>::iterator iter = v.begin();
    
    while (iter != v.end()) {
        if (*iter % 2 != 0) {
            iter = v.erase(iter);
            continue;
        }
        iter++;
    }
}

void test2()
{
  int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
  vector<int> x(a, a+8);  // construct x from the array
  assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
  removeOdds(x);
  assert(x.size() == 4);
  sort(x.begin(), x.end());
  int expect[4] = { 2, 4, 6, 8 };
  for (int k = 0; k < 4; k++)
      assert(x[k] == expect[k]);
}


vector<int> destroyedOnes3;

class Movie3
{
  public:
    Movie3(int r) : m_rating(r) {}
    ~Movie3() { destroyedOnes3.push_back(m_rating); }
    int rating() const { return m_rating; }
  private:
    int m_rating;
};

  // Remove the movies in li with a rating below 50 and destroy them.
  // It is acceptable if the order of the remaining movies is not
  // the same as in the original list.
void removeBad(list<Movie3*>& li)
{
    size_t len = li.size();
    
    for (size_t i = 0; i < len; i++) {
        Movie3* item = li.front();
        li.pop_front();
        if (item->rating() >= 50)
        {
            li.push_back(item);
        }else {
            delete item;
        }
    }
}

void test3()
{
    int a[8] = { 85, 80, 30, 70, 20, 15, 90, 10 };
    list<Movie3*> x;
    for (int k = 0; k < 8; k++)
        x.push_back(new Movie3(a[k]));
    assert(x.size() == 8 && x.front()->rating() == 85 && x.back()->rating() == 10);
    removeBad(x);
    assert(x.size() == 4 && destroyedOnes3.size() == 4);
    vector<int> v;
    for (list<Movie3*>::iterator p = x.begin(); p != x.end(); p++)
    {
        Movie3* mp = *p;
        v.push_back(mp->rating());
    }
    sort(v.begin(), v.end());
    int expect[4] = { 70, 80, 85, 90 };
    for (int k = 0; k < 4; k++)
        assert(v[k] == expect[k]);
    sort(destroyedOnes3.begin(), destroyedOnes3.end());
    int expectGone[4] = { 10, 15, 20, 30 };
    for (int k = 0; k < 4; k++)
        assert(destroyedOnes3[k] == expectGone[k]);
}


vector<int> destroyedOnes4;

class Movie
{
  public:
    Movie(int r) : m_rating(r) {}
    ~Movie() { destroyedOnes4.push_back(m_rating); }
    int rating() const { return m_rating; }
  private:
    int m_rating;
};

  // Remove the movies in v with a rating below 50 and destroy them.
  // It is acceptable if the order of the remaining movies is not
  // the same as in the original vector.
void removeBad(vector<Movie*>& v)
{
    vector<Movie*>::iterator iter = v.begin();
    
    while (iter != v.end()) {
        if ((*iter)->rating() < 50) {
            delete *iter;
            iter = v.erase(iter);
            continue;
        }
        iter++;
    }
}

void test4()
{
    int a[8] = { 85, 80, 30, 70, 20, 15, 90, 10 };
    vector<Movie*> x;
    for (int k = 0; k < 8; k++)
        x.push_back(new Movie(a[k]));
    assert(x.size() == 8 && x.front()->rating() == 85 && x.back()->rating() == 10);
    removeBad(x);
    assert(x.size() == 4 && destroyedOnes4.size() == 4);
    vector<int> v;
    for (int k = 0; k < 4; k++)
        v.push_back(x[k]->rating());
    sort(v.begin(), v.end());
    int expect[4] = { 70, 80, 85, 90 };
    for (int k = 0; k < 4; k++)
        assert(v[k] == expect[k]);
    sort(destroyedOnes4.begin(), destroyedOnes4.end());
    int expectGone[4] = { 10, 15, 20, 30 };
    for (int k = 0; k < 4; k++)
        assert(destroyedOnes4[k] == expectGone[k]);
}
