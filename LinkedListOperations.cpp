#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
    int data;
    Node *next;

    // Constructor
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }

    // Destructor
    ~Node()
    {
        if (this->next != NULL)
        {
            delete next;
            this->next = NULL;
        }
        cout << "Memory is free from the value " << data << endl;
    }
};

// Insert at head
void insertAtHead(Node *&head, Node *&tail, int data)
{
    Node *newNode = new Node(data);
    newNode->next = head;
    head = newNode;

    // If list was empty, update tail as well
    if (tail == NULL)
    {
        tail = newNode;
    }
}

// Insert at tail with tail pointer optimization
void insertAtTail(Node *&head, Node *&tail, int data)
{
    Node *newNode = new Node(data);
    if (head == NULL)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}

// Insert at a specific position
void insertAtPosition(Node *&head, Node *&tail, int position, int data)
{
    if (position == 1)
    {
        insertAtHead(head, tail, data);
        return;
    }

    int cnt = 1;
    Node *temp = head;

    // Traverse to the position before the desired position
    while (cnt < position - 1 && temp != NULL)
    {
        temp = temp->next;
        cnt++;
    }

    // If the position is at the end, insert at tail
    if (temp == NULL || temp->next == NULL)
    {
        insertAtTail(head, tail, data);
        return;
    }

    // Insert in the middle
    Node *newNode = new Node(data);
    newNode->next = temp->next;
    temp->next = newNode;
}

// Print the list
void print(Node *head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        cout << "->" << temp->data;
        temp = temp->next;
    }
    cout << endl;
}

// Delete a node at a specific position
void deleteNode(Node *&head, Node *&tail, int position)
{
    if (head == NULL)
    {
        cout << "List is empty. Nothing to delete." << endl;
        return;
    }

    // If deleting the head node
    if (position == 1)
    {
        Node *temp = head;
        head = head->next;
        temp->next = NULL;
        delete temp;

        // If the list becomes empty after deletion, update tail
        if (head == NULL)
        {
            tail = NULL;
        }
    }
    else
    {
        Node *prev = NULL;
        Node *curr = head;
        int cnt = 1;

        // Traverse to the node before the node to be deleted
        while (cnt < position && curr != NULL)
        {
            prev = curr;
            curr = curr->next;
            cnt++;
        }

        if (curr == NULL)
        {
            cout << "Position out of bounds." << endl;
            return;
        }

        prev->next = curr->next;
        curr->next = NULL;
        delete curr;

        // If the deleted node was the tail, update the tail pointer
        if (prev->next == NULL)
        {
            tail = prev;
        }
    }
}

// Delete node by value
void deleteByValue(Node *&head, Node *&tail, int val)
{
    if (head == NULL)
    {
        cout << "List is empty. Nothing to delete." << endl;
        return;
    }

    // If the head contains the value
    if (head->data == val)
    {
        Node *temp = head;
        head = head->next;
        temp->next = NULL;
        delete temp;
        cout << "Deleted node with value " << val << endl;

        // Update tail if list becomes empty
        if (head == NULL)
        {
            tail = NULL;
        }
        return;
    }

    Node *temp = head;
    while (temp->next != NULL && temp->next->data != val)
    {
        temp = temp->next;
    }

    if (temp->next == NULL)
    {
        cout << "Value " << val << " not found in the list." << endl;
        return;
    }

    Node *toDelete = temp->next;
    temp->next = temp->next->next;
    toDelete->next = NULL;
    delete toDelete;
    cout << "Deleted node with value " << val << endl;

    // If the deleted node was the tail, update the tail pointer
    if (temp->next == NULL)
    {
        tail = temp;
    }
}

// Find the length of the list
int findLength(Node *head)
{
    Node *temp = head;
    int cnt = 0;
    while (temp != NULL)
    {
        temp = temp->next;
        cnt++;
    }
    return cnt;
}

// Reverse the list
Node *reverseList(Node *&head)
{
    Node *prev = NULL;
    Node *curr = head;
    Node *forward = NULL;
    while (curr != NULL)
    {
        forward = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forward;
    }
    return prev;
}

// Find the middle node using length
Node *findingMiddleNode(Node *&head)
{
    int len = findLength(head);
    int ans = (len / 2);
    int cnt = 0;
    Node *temp = head;
    while (cnt < ans)
    {
        temp = temp->next;
        cnt++;
    }
    return temp;
}

// Find the middle node using Fast and Slow Pointers
Node *MiddleByFastSlowMethod(Node *&head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    Node *fast = head;
    Node *slow = head;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Check if a list is a palindrome by comparing elements
int checkPalindrome(vector<int> arr)
{
    int size = arr.size();
    int start = 0;
    int end = size - 1;
    while (start <= end)
    {
        if (arr[start] != arr[end])
        {
            return 0;
        }
        start++;
        end--;
    }
    return 1;
}

// Check if the linked list is a palindrome
int isPalindrome(Node *head)
{
    vector<int> arr;
    Node *temp = head;
    while (temp != NULL)
    {
        arr.push_back(temp->data);
        temp = temp->next;
    }
    return checkPalindrome(arr);
}

// Check if linked list is palindrome by reversing half after the middle
bool PalindromeByReversingHalfAfterMid(Node *&head)
{
    if (head == NULL || head->next == NULL)
    {
        return true;
    }
    Node *middle = MiddleByFastSlowMethod(head);

    Node *temp = middle->next;
    middle->next = reverseList(temp);

    Node *head1 = head;
    Node *head2 = middle->next;

    while (head2 != NULL)
    {
        if (head1->data != head2->data)
        {
            return false;
        }
        head1 = head1->next;
        head2 = head2->next;
    }
    return true;
}

// Merge two sorted linked lists
Node *merge(Node *&head1, Node *&head2)
{
    Node *p1 = head1;
    Node *p2 = head2;
    Node *dummyList = new Node(-1);
    Node *p3 = dummyList;

    while (p1 != NULL && p2 != NULL)
    {
        if (p1->data < p2->data)
        {
            p3->next = p1;
            p1 = p1->next;
        }
        else
        {
            p3->next = p2;
            p2 = p2->next;
        }
        p3 = p3->next;
    }

    while (p1 != NULL)
    {
        p3->next = p1;
        p1 = p1->next;
        p3 = p3->next;
    }

    while (p2 != NULL)
    {
        p3->next = p2;
        p2 = p2->next;
        p3 = p3->next;
    }
    return dummyList->next;
}

// Reverse the linked list by group of k nodes
Node *reverseListByKGroup(Node *&head, int k)
{
    int cnt = 0;
    Node *prev = NULL;
    Node *curr = head;
    Node *forward = NULL;
    while (curr != NULL && cnt < k)
    {
        forward = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forward;
        cnt++;
    }
    if (forward != NULL)
    {
        head->next = reverseListByKGroup(forward, k);
    }
    return prev;
}

// Remove duplicate values from the sorted list
void removeDuplicates(Node *head)
{
    if (head == NULL)
    {
        return;
    }

    Node *current = head;
    while (current->next != NULL)
    {
        if (current->data == current->next->data)
        {
            Node *temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
        else
        {
            current = current->next;
        }
    }
}


void removeDuplicatesofUnsortedList(Node* &head){
   Node* curr = head;

   while(curr != NULL){

         Node* temp = curr;
         while(temp != NULL && temp->next != NULL){

            if(curr->data == temp->next->data){
               Node* next = temp->next;
               temp->next = temp->next->next;
               delete next;
            }
            else{
                  temp = temp->next;
            }
         }
   
         curr = curr -> next;
   }
}


int main()
{
    Node *head = NULL;
    Node *tail = NULL;
    int choice;
    do
    {
        cout << "\n1. Insert at Head\n2. Insert at Tail\n3. Insert at Position\n4. Delete Node at Position\n5. Delete Node by Value\n6. Print List\n7. Find Length\n8. Reverse List\n9. Find Middle Node\n10. Check if Palindrome\n11. Reverse k Group\n12. Find Middle Node by Fast-Slow Pointer\n13. Merge Two Sorted Lists\n14. Remove Duplicates from Sorted List\n15.Remove duplicates from unsorted List\n0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            int data;
            cout << "Enter data: ";
            cin >> data;
            insertAtHead(head, tail, data);
            break;
        }
        case 2:
        {
            int data;
            cout << "Enter data: ";
            cin >> data;
            insertAtTail(head, tail, data);
            break;
        }
        case 3:
        {
            int position, data;
            cout << "Enter position and data: ";
            cin >> position >> data;
            insertAtPosition(head, tail, position, data);
            break;
        }
        case 4:
        {
            int position;
            cout << "Enter position: ";
            cin >> position;
            deleteNode(head, tail, position);
            break;
        }
        case 5:
        {
            int val;
            cout << "Enter value to delete: ";
            cin >> val;
            deleteByValue(head, tail, val);
            break;
        }
        case 6:
        {
            print(head);
            break;
        }
        case 7:
        {
            int length = findLength(head);
            cout << "Length of list: " << length << endl;
            break;
        }
        case 8:
        {
            head = reverseList(head);
            print(head);
            break;
        }
        case 9:
        {
            Node *middle = findingMiddleNode(head);
            cout << "Middle node: " << middle->data << endl;
            break;
        }
        case 10:
        {
            if (isPalindrome(head))
            {
                cout << "The list is a palindrome." << endl;
            }
            else
            {
                cout << "The list is not a palindrome." << endl;
            }
            break;
        }
        case 11:
        {
            int k;
            cout << "Enter value of k: ";
            cin >> k;
            head = reverseListByKGroup(head, k);
            print(head);
            break;
        }
        case 12:
        {
            Node *middle = MiddleByFastSlowMethod(head);
            cout << "Middle node by fast-slow pointer: " << middle->data << endl;
            break;
        }
        case 13:
        {
            Node *head1 = NULL;
            Node *tail1 = NULL;
            Node *head2 = NULL;
            Node *tail2 = NULL;
            int n1;
            cout << "Enter linked list 1 size: ";
            cin >> n1;
            int n2;
            cout << "Enter linked list 2 size: ";
            cin >> n2;
            int arr1[n1], arr2[n2];
            cout << "Enter " << n1 << " elements: ";
            for (int i = 0; i < n1; i++)
            {
                cin >> arr1[i];
            }
            cout << endl;
            cout << "Enter " << n2 << " elements: ";
            for (int i = 0; i < n2; i++)
            {
                cin >> arr2[i];
            }
            for (int i = 0; i < n1; i++)
            {
                insertAtTail(head1, tail1, arr1[i]);
            }
            for (int i = 0; i < n2; i++)
            {
                insertAtTail(head2, tail2, arr2[i]);
            }
            Node *newhead = merge(head1, head2);
            print(newhead);
            break;
        }
        case 14:
        {
            removeDuplicates(head);
            print(head);
            break;
        }
         case 15:
        {
            removeDuplicatesofUnsortedList(head);
            print(head);
            break;
        }
        case 0:
        {
            cout << "Exiting..." << endl;
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}
