#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
   int data;
   Node *next1;
   Node *next2;
   Node(int x)
   {
      data = x;
   }
};
void print1(Node *head)
{
   Node *curr = head;
   while (curr)
   {
      cout << curr->data << " ";
      curr = curr->next1;
   }
}
void print2(Node *head)
{
   Node *curr = head;
   while (curr)
   {
      cout << curr->data << " ";
      if (curr->next2 != NULL)
         curr = curr->next2;
      else
         curr = curr->next1;
   }
}

// creating linkrd list 1
Node *makeL(int n, int limit)
{
   Node *head = new Node(n);
   Node *curr = head;
   int x = n + n;
   while (x <= limit)
   {
      curr->next1 = new Node(x);
      x = x + n;
      curr = curr->next1;
   }
   return head;
}

// creating linkrd list 2
Node *makeC(int b, int n, int c, Node *head1)
{
   Node *head2 = NULL;
   Node *curr2 = head2;
   int x = b;
   int y1 = c;
   Node *curr1 = head1;
   if (b == c)
   {
      while (curr1->data != c)
      {
         curr1 = curr1->next1;
      }
      b += x;
      c += y1;
      head2 = curr1;
      curr2 = head2;
   }
   else
   {
      head2 = new Node(b);
      curr2 = head2;
      b += x;
   }
   int flag = 0;
   while (b <= n)
   {
      if (b == c)
      {
         while (curr1->data != c)
         {
            curr1 = curr1->next1;
         }
         curr2->next1 = curr1;
         curr2 = curr2->next1;
         b += x;
         c += y1;
         flag = 1;
      }
      else
      {

         if (flag == 1)
         {
            // cout<<"hi"<<endl;
            curr2->next2 = new Node(b);
            curr2 = curr2->next2;
            flag = 0;
            b += b;
         }
         else
         {

            curr2->next1 = new Node(b);
            b += b;
         }
      }
   }

   return head2;
}

//  printing the list in merged fashion
void merge(Node *head1, Node *head2)
{
   Node *curr1 = head1;
   Node *curr2 = head2;

   while (curr1 != NULL && curr2 != NULL)
   {
      if (curr1->data < curr2->data)
      {
         cout << curr1->data << " ";
         curr1 = curr1->next1;
      }
      else if (curr2->data < curr1->data)
      {
         cout << curr2->data << " ";
         curr2 = curr2->next1;
      }
      else if (curr1 == curr2)
      {
         cout << curr1->data << " ";
         curr1 = curr1->next1;
         curr2 = curr2->next2;
      }
   }

   while (curr1 != NULL)
   {
      cout << curr1->data << " ";
      curr1 = curr1->next1;
   }
   while (curr2 != NULL)
   {
      cout << curr2->data << " ";
      if (curr2->next2 != NULL)
      {
         curr2 = curr2->next2;
      }
      else
      {
         curr2 = curr2->next1;
      }
   }
}
int main(void)
{
   int a, b, n;
   cin >> a >> b >> n;

   Node *head1 = makeL(a, n);
   int c = __gcd(a, b);
   if (c == 1)
   {
      c = a * b;
   }
   cout << c << endl;
   print1(head1);
   cout << endl;
   Node *head2 = makeC(b, n, c, head1);

   print2(head2);
   cout << endl;
   merge(head1, head2);
   return 0;
}
