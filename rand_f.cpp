#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 

using namespace std;

struct point
{
  int x1, x2;
  //конструктор по умолчанию строит null_point = (-1, -1)
  point() 
  {
    x1 = x2 = -1;
  } 
  
  //конструктор копирования
  point(int a, int b)
  {
    x1 = a; x2 = b;
  }
  //проверка равенства
  bool operator==(const point& rv)
  {
    return((x1==rv.x1)&&(x2==rv.x2));
  }
};

const point Null_point; // константа для нулевой точки

//проверка на равенство по модулю k заданного значения fi значению
//функции f(x) = a + b*x1 + c*x2 в точке cur
bool check(int a, int b, int c, point cur, int k, int fi)
{
  return ((a+b*cur.x1+c*cur.x2)%k == fi);
}

//печать результатов проверки для функции с координатами (a, b, c)
//в файл "out.txt", точки A, B, C - точки, найденные во время проверки
void print_point(int a, int b, int c, point A, point B, point C, bool err)
{
  ofstream f;
  f.open("out.txt", ios::app);
  f << "(" << a << ", " << b << ", " << c << ")  ";
  f << A.x1 << " " << A.x2 << endl;
  f << "           ";
  f << B.x1 << " " << B.x2 << endl;
  f << "           ";
  f << C.x1 << " " << C.x2 << endl;
  if (!err) f << "ERROR!!!" << endl;
  f.close();
}


//проверка принадлежности точек одной прямой в R^2
bool one_line(point A,  point B, point C, int k)
{
  if (A==Null_point) return true;
  if (B==Null_point) return true;
  return ((C.x1 - A.x1)*(B.x2 - A.x2) == (B.x1 - A.x1)*(C.x2 - A.x2));
}

//отладочная функция - проверка правильности считывания
void print_fi(vector <int> fi, int n)
{
    ofstream f;
    f.open("out_fi.txt", ios::app);
    f << endl << n;
    //for (int i = 0; i < k; i++)
        for (int j = 0; j < n; j++)
        {
            f << endl;
            for (int k = 0; k < n; k++)
            if (fi[j*n + k] != -1) f << fi[j*n + k] << ' ';
            else f << "- ";
        }
    f << endl << endl;
    f.close();
}

//проверка функции fi на универсальность
bool check_fi(vector<int> fi, int k, int n)
{
    int l1, l2, l0;
    bool rez_of_check = true;
    vector<int> save_rez(k*k, 0);
//    ifstream f;
//    f.open("out.txt");
//    f.close();
//  ofstream out_debug_wtf;
//  out_debug_wtf.open("out_wtf.txt");
  bool find = false;
  for (l0 = 0; l0 < k; l0++)
  for (l1 = 0; l1 < k; l1++)
  for (l2 = 0; l2 < k; l2++) //Проверка для произвольных функций
  {
    find = false;
    point A, B, C;
    for (int i = 0; (i < (k*k))&&(!find); i++)
    {
      point current1(i/k, i%k);
      if (check(l0, l1, l2, current1, k, fi[i]))
      {A = current1;
      for (int j = i+1; (j < (k*k))&&(!find); j++)
      {
        point current2(j/k, j%k);
        if (check(l0, l1, l2, current2, k, fi[j]))
        {B = current2;
        for (int l = j+1; (l < (k*k))&&(!find); l++)
        {
          point current3(l/k, l%k);
          if ((check(l0, l1, l2, current3, k, fi[l]))&&(!one_line(A, B, current3, k)))
          {C = current3;
//            print_point(l0, l1, l2, A, B, C, true);
            find = true;
            save_rez[i]++; save_rez[j]++; save_rez[l]++;// save_rez[t]++;
            }
          }
        }}}}

    if ((A.x1==-1)||(B.x1==-1)||(C.x1==-1))
    {
//      print_point(l0, l1, l2, A, B, C, false);
      //cout << "ERROR: " << l0 << " " << l1 << " " << l2 << endl;
//      out_debug_wtf.close();
      rez_of_check = false;
    }

  }
  //print_fi(save_rez, k);
//  out_debug_wtf.close();
    return rez_of_check;
}

vector<int> gen_rand_fi(int k)
{
  vector<int> fi(k*k, 0);
  for (int i = 0; i < fi.size(); ++i)
  {  
    fi[i] = rand()%k;
  }
  return fi;
}


int main()
{
  srand(time(NULL));
  int k;// = 4;
  int number_of_tryes;
  cin >> k >> number_of_tryes;
  int n = 2;
  int d = 2;
  vector <int> fi(k*k, 0);//k^n
  vector <int> consts(k, 0);
  ofstream out;
//  out.open("out_lin.txt");
  //bool flag = false;
  int sucsess = -1;
  for (int i = 0; i < number_of_tryes; ++i)
  {
  fi = gen_rand_fi(k);
    if (check_fi(fi, k, n)) 
    { 
    cout << "YES!!!" << endl; 
    if (sucsess < 0)
      print_fi(fi, k); 
    sucsess = i;
  }
    else 
    {
//    out << endl << "NO :(";
    cout << "NO" << endl; 
    }
  }
  if (sucsess >= 0)
    cout << "SUCSESS" << endl;
  else
    cout << "NO SUCSESS" << endl;
  //in.close();
  out.close();
  return 0;
}
