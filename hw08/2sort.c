#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TItem
{
  struct TItem *m_Next;
  char *m_Name;
  char m_Secret[24];
} TITEM;

int cmpName(const TITEM *a,
            const TITEM *b)
{
  return strcmp(a->m_Name, b->m_Name);
}

int cmpNameInsensitive(const TITEM *a,
                       const TITEM *b)
{
  return strcasecmp(a->m_Name, b->m_Name);
}

int cmpNameLen(const TITEM *a,
               const TITEM *b)
{
  size_t la = strlen(a->m_Name), lb = strlen(b->m_Name);
  return (lb < la) - (la < lb);
}
#endif /* __PROGTEST__ */

TITEM *newItem(const char *name,
               TITEM *next)
{
  TITEM *l = (TITEM *)malloc(sizeof(TITEM));
  l->m_Name = (char *)malloc(strlen(name) + 1);
  for (int i = 0; i < 24; i++)
  {
    l->m_Secret[i] = '\0';
  }
  strcpy(l->m_Name, name);
  l->m_Next = next;
  return l;
}

TITEM *reverse(TITEM *l)
{
  TITEM *x = NULL, *i = l, *p = NULL;
  while (i != NULL)
  {
    x = i->m_Next;
    i->m_Next = p;
    p = i;
    i = x;
  }
  l = p;
  return l;
}
TITEM *sortListCmp(TITEM *l,
                   int ascending,
                   int (*cmpFn)(const TITEM *, const TITEM *))
{
  TITEM *i, *x, *p, *tmp;
  int swap = 1;

  if (l == NULL || l->m_Next == NULL)
    return l;
  if (ascending != 0)
  {
    while (swap == 1)
    {
      swap = 0;
      p = NULL;
      i = l;
      while (i->m_Next)
      {
        x = i->m_Next;
        if ((cmpFn)(i, x) > 0)
        {
         
          if (p == NULL)
          {
            p = i->m_Next;
            x = x->m_Next;
            p->m_Next = i;
            i->m_Next = x;
            l = p;
            swap = 1;
          }
          else
          {
            tmp = x;
            x = x->m_Next;
            p->m_Next = i->m_Next;
            p = tmp;
            tmp->m_Next = i;
            i->m_Next = x;
            swap = 1;
          }
        }
        else
        {
          p = i;
          i = x;
          x = x->m_Next;
        }
      }
    }
  }
  if (ascending == 0)
  {

    while (swap == 1)
    {
      swap = 0;
      p = NULL;
      i = l;
      while (i->m_Next)
      {
        x = i->m_Next;
        if ((cmpFn)(i, x) < 0)
        {
         
          if (p == NULL)
          {
            p = i->m_Next;
            x = x->m_Next;
            p->m_Next = i;
            i->m_Next = x;
            l=p;
            swap = 1;
          }
          else
          {
            tmp = x;
            x = x->m_Next;
            p->m_Next = i->m_Next;
            p = tmp;
            tmp->m_Next = i;
            i->m_Next = x;
            swap = 1;
          }
        }
        else
        {
          p = i;
          i = x;
          x = x->m_Next;
        }
      }
    }
  }

  return l;
}
void freeList(TITEM *src)
{
  TITEM *tmp;
  while (src != NULL)
  {
    tmp = src;
    src = src->m_Next;

    free(tmp->m_Name);
    free(tmp);
  }

  return;
}
void printNode(TITEM *l)
{

  if (l == NULL)
  {

    printf("\n");
    return;
  }
  printf("%s", l->m_Name);
  printNode(l->m_Next);
}
#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
  TITEM *l;
  char tmp[50];

  assert(sizeof(TITEM) == sizeof(TITEM *) + sizeof(char *) + 24 * sizeof(char));
  l = NULL;
  l = newItem("BI-PA1", l);
  l = newItem("BIE-PA2", l);
  l = newItem("NI-PAR", l);
  l = newItem("lin", l);
  l = newItem("AG1", l);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpName);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpNameInsensitive);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpNameLen);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = newItem("AAG.3", l);
  assert(l && !strcmp(l->m_Name, "AAG.3"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "AG1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
 
  l = sortListCmp(l, 0, cmpNameLen);

  assert(l && !strcmp(l->m_Name, "BIE-PA2"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "AAG.3"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "AG1"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  freeList(l);
  l = NULL;
  strncpy(tmp, "BI-PA1", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  strncpy(tmp, "BIE-PA2", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  strncpy(tmp, "NI-PAR", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  strncpy(tmp, "lin", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  strncpy(tmp, "AG1", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpName);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpNameInsensitive);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 1, cmpNameLen);
  assert(l && !strcmp(l->m_Name, "AG1"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  strncpy(tmp, "AAG.3", sizeof(tmp) - 1);
  tmp[sizeof(tmp) - 1] = '\0';
  l = newItem(tmp, l);
  assert(l && !strcmp(l->m_Name, "AAG.3"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "AG1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "BIE-PA2"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  l = sortListCmp(l, 0, cmpNameLen);
  assert(l && !strcmp(l->m_Name, "BIE-PA2"));
  assert(l->m_Next && !strcmp(l->m_Next->m_Name, "BI-PA1"));
  assert(l->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Name, "NI-PAR"));
  assert(l->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Name, "AAG.3"));
  assert(l->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Name, "AG1"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next && !strcmp(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Name, "lin"));
  assert(l->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
  freeList(l);
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
