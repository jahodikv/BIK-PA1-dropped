#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <assert.h>
#endif /* __PROGTEST__ */
int strLenght(char ConvertedNum[66])
{
  int strlen;
  for (strlen = 0; ConvertedNum[strlen] != '\0'; strlen++)
  {
  };
  return strlen;
}
char baseConverter(unsigned long long from, int radix, char ConvertedNum[66])
{

  char baseChar[36] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  char ConvertedNumReversed[66] = {'\0'};


  unsigned long long originalNumCopy = from;
  
  int i = 0, x = 0, z = 0;
  if (radix > 36 || radix < 2)
  {

    return 0;
  }

  while (originalNumCopy > 0)
  {
    z = originalNumCopy % radix;
    ConvertedNumReversed[i] = baseChar[z];
    originalNumCopy = originalNumCopy / radix;
    i++;

  }
  
  i--;
  while (i >= 0)
  {
    ConvertedNum[x] = ConvertedNumReversed[i];
    i--;
    x++;
  }
  if (strLenght(ConvertedNum) >= 66)
  {
    return 0;
  }


//printf("%s",ConvertedNum);

  return ConvertedNum[66];
}

int palindromeCheck(char ConvertedNum[66])
{

  int strlen = strLenght(ConvertedNum);

  for (int i = 0; i < strlen / 2; i++)
  {
    if (ConvertedNum[i] != ConvertedNum[strlen - 1 - i])
    {
      return 0;
    }
  }
  return 1;
}
int AllLastCheck(char ConvertedNum[66], int radix)
{
  char baseChar[36] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  int strlen = strLenght(ConvertedNum);

  for (int i = 0; i < strlen; i++)
  {
    if (ConvertedNum[i] != baseChar[radix - 1])
    {
      return 0;
    }
  }

  return 1;
}

char halfReverse(char ConvertedNum[66])
{
  int i = strLenght(ConvertedNum)-1;

  int x = 0;

  while (x<strLenght(ConvertedNum))
  {
    ConvertedNum[i] = ConvertedNum[x];
    i--;
    x++;
  }

  // printf("%s", ConvertedNum);
  return ConvertedNum[66];
}

int decToBaseChar(int radix, char ConvertedNum[66], int i)
{
  char baseChar[36] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

  for (int q = 0; q < radix; q++)
  {
    if (baseChar[q] == ConvertedNum[i])
    {
      return q;
    }
  }
  return 0;
}

unsigned long long decimalConverter(int radix, char ConvertedNum[66])
{

  int pow = 1, i;
  unsigned long long decNum = 0;

  for (i = strLenght(ConvertedNum) - 1; i >= 0; i--)
  {

    decNum += decToBaseChar(radix, ConvertedNum, i) * pow;
    pow = radix * pow;
  }
if (decNum==18446744073709551614LLu)
{
  decNum++;
 
}
 
  return decNum;
}

unsigned long long IfAllLast(char ConvertedNum[66], int radix)
{
  unsigned long long q;

  for (int x = 0; x < strLenght(ConvertedNum); x++)
  {
    ConvertedNum[x] = '0';
  }
  ConvertedNum[0] = '1';
  ConvertedNum[strLenght(ConvertedNum)] = '1';
  q = decimalConverter(radix, ConvertedNum);
  return q;
}

int nextPalindrome(unsigned long long from,
                   int radix,
                   unsigned long long *next)
{

  
  char baseChar[36] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

  char ConvertedNum[66] = {'\0'};

  
 

if (radix>36)
{
 return 0;
}
if (radix<2)
{
 return 0;
}

 if (from>=ULLONG_MAX) 
 {
   
  return 0;
 }
 
 baseConverter(from, radix, ConvertedNum);

if (strLenght(ConvertedNum)>66)
{
  return 0;

}


  if (palindromeCheck(ConvertedNum) == 1)
  {
    if (strLenght(ConvertedNum) == 1 && ConvertedNum[0] < baseChar[radix - 1])
    {
      ConvertedNum[0] = baseChar[decToBaseChar(radix, ConvertedNum, 0) + 1];
      *next = decimalConverter(radix, ConvertedNum);
 
    }
    if ((AllLastCheck(ConvertedNum, radix)) == 1)
    {
      *next = IfAllLast(ConvertedNum, radix);
  
    }
    if (strLenght(ConvertedNum) % 2 == 0)
    {

      if (ConvertedNum[strLenght(ConvertedNum) / 2] == baseChar[radix - 1])
      {
        int x = 0, y = 0;

        while (x == 0)
        {
          if (ConvertedNum[strLenght(ConvertedNum) / 2 - y] == baseChar[radix - 1])
          {

            ConvertedNum[(strLenght(ConvertedNum) / 2) - y] = '0';
          }
          else
          {

            ConvertedNum[(strLenght(ConvertedNum) / 2) - y] = baseChar[decToBaseChar(radix, ConvertedNum, (strLenght(ConvertedNum) / 2) - y) + 1];
            ConvertedNum[(strLenght(ConvertedNum) / 2) + y - 1] = ConvertedNum[(strLenght(ConvertedNum) / 2) - y];
            x = 1;
          }
          y++;
        }

        *next = decimalConverter(radix, ConvertedNum);
      
        return 1;
      }
      else
      {

        ConvertedNum[(strLenght(ConvertedNum) / 2)] = baseChar[decToBaseChar(radix, ConvertedNum, (strLenght(ConvertedNum) / 2)) + 1];
        ConvertedNum[(strLenght(ConvertedNum) / 2) - 1] = ConvertedNum[(strLenght(ConvertedNum) / 2)];

        *next = decimalConverter(radix, ConvertedNum);
      
        return 1;
      }
    }
    else
    {
      if (ConvertedNum[(strLenght(ConvertedNum) / 2)] == baseChar[radix - 1])
      {

        int x = 0, y = 0;
        while (x == 0)
        {
          if (ConvertedNum[strLenght(ConvertedNum) / 2 - y] == baseChar[radix - 1])
          {

            ConvertedNum[(strLenght(ConvertedNum) / 2) - y] = '0';
          }
          else
          {

            ConvertedNum[(strLenght(ConvertedNum) / 2) - y] = baseChar[decToBaseChar(radix, ConvertedNum, (strLenght(ConvertedNum) / 2) - y) + 1];

            x = 1;
          }
          y++;
        }
        halfReverse(ConvertedNum);

        *next = decimalConverter(radix, ConvertedNum);
      
        return 1;
      }
      else
      {
        ConvertedNum[(strLenght(ConvertedNum) / 2)] = baseChar[decToBaseChar(radix, ConvertedNum, (strLenght(ConvertedNum) / 2)) + 1];

        *next = decimalConverter(radix, ConvertedNum);
        
        return 1;
      }
    }
  }
  else
  {
    
    char q[66]={'\0'};
    for (int i = 0; i < strLenght(ConvertedNum); i++)
    {
      q[i] = ConvertedNum[i];
    }

    halfReverse(q);
  

 if (decimalConverter(radix, q) == 18446744073709551615LLu)
    {
      

      *next = decimalConverter(radix, ConvertedNum);
      
      return 1;
    }




    if (decimalConverter(radix, q) > decimalConverter(radix, ConvertedNum))
    {
   
      *next = decimalConverter(radix, q);
      
      return 1;
    }

    if (strLenght(ConvertedNum) % 2 == 0)
    {
      if (ConvertedNum[strLenght(ConvertedNum) / 2 - 1] == baseChar[radix - 1])
      {
        int x = 0, y = 0;

        while (x == 0)
        {
          if (ConvertedNum[strLenght(ConvertedNum) / 2 - y - 1] == baseChar[radix - 1])
          {

            ConvertedNum[(strLenght(ConvertedNum) / 2) - y - 1] = '0';
          }
          else
          {

            ConvertedNum[(strLenght(ConvertedNum) / 2) - y - 1] = baseChar[decToBaseChar(radix, ConvertedNum, (strLenght(ConvertedNum) / 2 - y - 1)) + 1];
            halfReverse(ConvertedNum);
            x = 1;
          }
          y++;
        }

        *next = decimalConverter(radix, ConvertedNum);
       
        return 1;
      }
      else
      {

        ConvertedNum[(strLenght(ConvertedNum) / 2) - 1] = baseChar[decToBaseChar(radix, ConvertedNum, (strLenght(ConvertedNum) / 2 - 1)) + 1];
        halfReverse(ConvertedNum);

        *next = decimalConverter(radix, ConvertedNum);
    
        return 1;
      }
    }
    else
    {

      if (ConvertedNum[(strLenght(ConvertedNum) / 2)] == baseChar[radix - 1])
      {
        int x = 0, y = 0;
        while (x == 0)
        {
          if (ConvertedNum[strLenght(ConvertedNum) / 2 - y] == baseChar[radix - 1])
          {

            ConvertedNum[(strLenght(ConvertedNum) / 2) - y] = '0';
          }
          else
          {

            ConvertedNum[(strLenght(ConvertedNum) / 2) - y] = baseChar[decToBaseChar(radix, ConvertedNum, (strLenght(ConvertedNum) / 2) - y) + 1];
            x = 1;
          }
          y++;
        }

        halfReverse(ConvertedNum);
        *next = decimalConverter(radix, ConvertedNum);
        
        return 1;
      }
      else
      {

        ConvertedNum[(strLenght(ConvertedNum) / 2)] = baseChar[decToBaseChar(radix, ConvertedNum, (strLenght(ConvertedNum) / 2)) + 1];
        halfReverse(ConvertedNum);

        *next = decimalConverter(radix, ConvertedNum);
        
        return 1;
      }
    }
  }
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
  
  unsigned long long next;
 


 

 
    assert(nextPalindrome(123, 10, &next) == 1 && next == 131);
    assert(nextPalindrome(188, 10, &next) == 1 && next == 191);
    assert(nextPalindrome(1441, 10, &next) == 1 && next == 1551);
    assert(nextPalindrome(95, 15, &next) == 1 && next == 96);       /* 96 = 66 (radix 15) */
   assert(nextPalindrome(45395, 36, &next) == 1 && next == 45431); /* 45431 = z1z (radix 36) */
    assert(nextPalindrome(1027, 2, &next) == 1 && next == 1057);    /* 1057 = 10000100001 (radix 2) */
    assert(nextPalindrome(1000, 100, &next) == 0 && next == 1057);
   assert(nextPalindrome(18446744073709551614LLu, 2, &next) == 1 && next == 18446744073709551615LLu); /* 18446744073709551615 = 1111111111111111111111111111111111111111111111111111111111111111 (radix 2) */
   assert(nextPalindrome(18446744073709551615LLu, 2, &next) == 0 && next == 18446744073709551615LLu);

  return 0;
}

#endif /* __PROGTEST__ */
