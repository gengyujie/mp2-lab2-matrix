// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize()      { return Size;       } // размер вектора
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      out << v.pVector[i] << ' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
   this.Size=s;
   this.StartIndex=si;
} 

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
  Size=v.Size;
  StartIndex=v.StartIndex;
  pVector=v.pVector;
}

template <class ValType>
TVector<ValType>::~TVector()
{
  delete pVector;
} 

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
  if(pos>Size)
  {cout<<"out of bound"<<endl;
   return pVector[0];
  }
  return pVector[pos];
} 

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
  for(int i=v.StartIndex;i<v.Size;i++)
  {
    if(this.pVector[i]!=v.pVector[i])
      return false;
  }
  return true;
}

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
  for(int i=v.StartIndex;i<v.Size;i++)
  {
    if(this.pVector[i]==v.pVector[i])
      return false;
  }
  return true;
}
} 

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
  this.Size=v.Size;
  this.StartIndex=v.StartIndex;
  this.pVector=v.pVector;
} 

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
  TVector<ValType> tmp= new TVector<ValType>();
  for(int i=val.StartIndex;i<Size;i++)
  {
    tmp.pVector[i]=pVector[i]+val;
  }
  return tmp;
} 

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
  TVector<ValType> tmp= new TVector<ValType>();
  for(int i=val.StartIndex;i<Size;i++)
  {
    tmp.pVector[i]=pVector[i]-val; 
  }
  return tmp;
} 

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
  TVector<ValType> tmp= new TVector<ValType>();
  for(int i=val.StartIndex;i<Size;i++)
  {
    tmp.pVector[i]=pVector[i]*val; 
  }
  return tmp;
} 

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{TVector<ValType> tmp= new TVector<ValType>();
  for(int i=val.StartIndex;i<Size;i++)
  {
    tmp.pVector[i]=pVector[i]+val.pVector[i]; 
  }
  return tmp;
} 

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
  TVector<ValType> tmp= new TVector<ValType>();
  for(int i=val.StartIndex;i<Size;i++)
  {
    tmp.pVector[i]=pVector[i]-val.pVector[i]; 
  }
  return tmp;
} 

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
  ValType tmp;
  for(int i=val.StartIndex;i<Size;i++)
  {
    tmp+=pVector[i]*val.pVector[i]; 
  }
  return tmp;
} 


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType>>(s)
{
  int s.Size=s;
}

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
   for(int i=mt.StartIndex;i<Size;i++)
  {
      for(int j=mt.StartIndex;j<Size;j++)
     {
        if(this.pVector[i][j]!=mt.pVector[i][j])
          return false;
     }
  
  }
  return true;
}
template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
  
   for(int i=mt.StartIndex;i<Size;i++)
  {
      for(int j=mt.StartIndex;j<Size;j++)
     {
        if(this.pVector[i][j]==mt.pVector[i][j])
          return false;
     }
  
  }
  return true;
} 

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
  this.Size=mt.Size;
  this.StartIndex=mt.StartIndex;
   for(int i=mt.StartIndex;i<Size;i++)
  {
     for(int j=mt.StartIndex;j<Size;j++)
     {
       this.pVector[i][j]=mt.pVector[i][j]；
         
     }
  
  }
  return *this;
}

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
  TMatrix<ValType> tmp=new TMatrix<ValType>();
  for(int i=mt.StartIndex;i<Size;i++)
  {
     for(int j=mt.StartIndex;j<Size;j++)
     {
        tmp.pVector[i][j]=this.pVector[i][j]+mt.pVector[i][j]；
         
     }
  
  }
  return tmp;
}

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
  TMatrix<ValType> tmp=new TMatrix<ValType>();
  for(int i=mt.StartIndex;i<Size;i++)
  {
     for(int j=mt.StartIndex;j<Size;j++)
     {
        tmp.pVector[i][j]=this.pVector[i][j]-mt.pVector[i][j]；
         
     }
  
  }
  return tmp;
} 

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
