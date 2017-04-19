/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 22:25:27 by lwang             #+#    #+#             */
/*   Updated: 2017/04/18 17:05:30 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
   struct stat sb;

   if (argc != 2) {
       fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
       exit(EXIT_FAILURE);
   }

   if (stat(argv[1], &sb) == -1) {
       perror("stat");
       exit(EXIT_FAILURE);
   }

   printf("Last status change:       %s", ctime(&sb.st_ctime));
   printf("ID of containing device:  [%lx,%lx]\n",
       (long) major(sb.st_dev), (long) minor(sb.st_dev));

   printf("File type:                ");

   switch (sb.st_mode & S_IFMT) {
   case S_IFBLK:  printf("block device\n");            break;
   case S_IFCHR:  printf("character device\n");        break;
   case S_IFDIR:  printf("directory\n");               break;
   case S_IFIFO:  printf("FIFO/pipe\n");               break;
   case S_IFLNK:  printf("symlink\n");                 break;
   case S_IFREG:  printf("regular file\n");            break;
   case S_IFSOCK: printf("socket\n");                  break;
   default:       printf("unknown?\n");                break;
   }

   printf("I-node number:            %ld\n", (long) sb.st_ino);

   printf("Mode:                     %lo (octal)\n",
           (unsigned long) sb.st_mode);

   printf("Link count:               %ld\n", (long) sb.st_nlink);
   printf("Ownership:                UID=%ld   GID=%ld\n",
           (long) sb.st_uid, (long) sb.st_gid);

   printf("Preferred I/O block size: %ld bytes\n",
           (long) sb.st_blksize);
   printf("File size:                %lld bytes\n",
           (long long) sb.st_size);
   printf("Blocks allocated:         %lld\n",
           (long long) sb.st_blocks);

   printf("Last status change:       %s", ctime(&sb.st_ctime));
   printf("Last file access:         %s", ctime(&sb.st_atime));
   printf("Last file modification:   %s", ctime(&sb.st_mtime));

   exit(EXIT_SUCCESS);
}


// #include<stdio.h>
// #include<stdlib.h>
  
// /* Link list node */
// struct node
// {
//     int data;
//     struct node* next;
// };
 
// /* function prototypes */
// struct node* SortedMerge(struct node* a, struct node* b);
// void FrontBackSplit(struct node* source,
//           struct node** frontRef, struct node** backRef);
 
// /* sorts the linked list by changing next pointers (not data) */
// void MergeSort(struct node** headRef)
// {
//   struct node* head = *headRef;
//   struct node* a;
//   struct node* b;
 
//   /* Base case -- length 0 or 1 */
//   if ((head == NULL) || (head->next == NULL))
//   {
//     return;
//   }
 
//   /* Split head into 'a' and 'b' sublists */
//   FrontBackSplit(head, &a, &b); 
 
//    Recursively sort the sublists 
//   MergeSort(&a);
//   MergeSort(&b);
 
//   /* answer = merge the two sorted lists together */
//   *headRef = SortedMerge(a, b);
// }
 
// /* See http://geeksforgeeks.org/?p=3622 for details of this 
//    function */
// struct node* SortedMerge(struct node* a, struct node* b)// (int)(*f)(char *)
// {
//   struct node* result = NULL;
 
//   /* Base cases */
//   if (a == NULL)
//      return(b);
//   else if (b==NULL)
//      return(a);
 
//   /* Pick either a or b, and recur */
//   if (a->data <= b->data)
//   {
//      result = a;
//      result->next = SortedMerge(a->next, b);
//   }
//   else
//   {
//      result = b;
//      result->next = SortedMerge(a, b->next);
//   }
//   return(result);
// }
 
// /* UTILITY FUNCTIONS */
// /* Split the nodes of the given list into front and back halves,
//      and return the two lists using the reference parameters.
//      If the length is odd, the extra node should go in the front list.
//      Uses the fast/slow pointer strategy.  */
// void FrontBackSplit(struct node* source,
//           struct node** frontRef, struct node** backRef)
// {
//   struct node* fast;
//   struct node* slow;
//   if (source==NULL || source->next==NULL)
//   {
//     /* length < 2 cases */
//     *frontRef = source;
//     *backRef = NULL;
//   }
//   else
//   {
//     slow = source;
//     fast = source->next;
 
//     /* Advance 'fast' two nodes, and advance 'slow' one node */
//     while (fast != NULL)
//     {
//       fast = fast->next;
//       if (fast != NULL)
//       {
//         slow = slow->next;
//         fast = fast->next;
//       }
//     }
 
//     /* 'slow' is before the midpoint in the list, so split it in two
//       at that point. */
//     *frontRef = source;
//     *backRef = slow->next;
//     slow->next = NULL;
//   }
// }
 
// /* Function to print nodes in a given linked list */
// void printList(struct node *node)
// {
//   while(node!=NULL)
//   {
//    printf("%d\n", node->data);
//    node = node->next;
//   }
// }
 
// /* Function to insert a node at the beginging of the linked list */
// void push(struct node** head_ref, int new_data)
// {
//   /* allocate node */
//   struct node* new_node =
//             (struct node*) malloc(sizeof(struct node));
  
//   /* put in the data  */
//   new_node->data  = new_data;
  
//   /* link the old list off the new node */
//   new_node->next = (*head_ref);    
  
//   /* move the head to point to the new node */
//   (*head_ref)    = new_node;
// } 
  
// /* Drier program to test above functions*/
// int main()
// {
//   /* Start with the empty list */
//   // struct node* res = NULL;
//   struct node* a = NULL;
  
//   /* Let us create a unsorted linked lists to test the functions
//    Created lists shall be a: 2->3->20->5->10->15 */
//   push(&a, 15);
//   push(&a, 10);
//   push(&a, 5); 
//   push(&a, 20);
//   push(&a, 3);
//   push(&a, 2); 
  
//   /* Sort the above created Linked List */
//   MergeSort(&a);
  
//   // printf("\n Sorted Linked List is: \n");
//   printList(a);           
  
//   // getchar();
//   return 0;
// }


