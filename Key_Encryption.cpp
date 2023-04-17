
#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h>
#include<queue>
#include<stdio.h>
#include<chrono>
#include<thread>
#include<climits>
#include<bitset>
#include<fstream>
#include<map>
using namespace std;



//STRUCTURE FOR LINKED LIST
struct LL
{
	char data;
	struct LL* next;
	LL(int x)
	{
		data = x;
		next = NULL;
	}
};

 LL* head = NULL;   //global list


// Function to add node to the list
LL* insert (LL *head, int data)
{
	if (head == NULL)
		return new LL(data);
	head->next = insert(head->next, data);
	return head;
}


//function to convert string to linked list
LL* txt_to_ll (string s)
{
	LL* head = NULL;

	int n = s.size();
	int i=0;

	for(;i<n;i++)
	head = insert(head, s[i]);

	return head;
}


//Utility function for RLE
void runLengthEncode (LL* head)
{
	LL* temp = NULL;
	LL* ptr = NULL;
	int count = 0; 

	temp = head;
	while (temp != NULL)
	{
		ptr = temp;
		count = 1;

		//check if current data and next data is same.If same, then increment count
		while (temp->next != NULL && temp->data == temp->next->data)
		{
			count++;
			if (count > 2)
			{
				// delete only when the node value is repeated more than
				// twice.
				ptr->next = temp->next;
				free(temp);
				temp = ptr;
			}
			temp = temp->next;
		}

		// update only when the node value is repeated more than one time.
		if (count > 1)
			temp->data = count + '0';
		temp = temp->next;
	}
	return;
}

//structure for bt
class Node
{
    public:

    	Node *left;
    	char a;
    	Node *right;
};


//create new node
Node* newNode(char data)
{
    Node* node = new Node();

    node->a = data;
    node->left = node->right = NULL;

    return (node);
}


//insert node on level order
Node* insertLevelOrder(string name, Node* root,int i, int n)
{
    if (i < n)
    {
        Node* temp = newNode(name[i]);
        root = temp;


        root->left = insertLevelOrder(name,root->left, 2 * i + 1, n);


        root->right = insertLevelOrder(name,root->right, 2 * i + 2, n);
    }
    return root;

}


//decryption2 based on level order bt
string levelOrder(Node *root)
{
    string cipher_in = "";
    
    if (root == NULL) 
    	return cipher_in;

    queue<Node *> q;

    Node *curr;

    q.push(root);
    q.push(NULL);

    while (q.size() > 1)
    {
        curr = q.front();
        q.pop();

        if (curr == NULL)
        {
           q.push(NULL);

        }

        else 
        {

            if(curr->left)
            q.push(curr->left);

            if(curr->right)
            q.push(curr->right);

            cipher_in = cipher_in + curr->a;
        }
    }
}


//reverse children in bt
void reverselevel(Node *root,int level)
{
    if(root == NULL)
        return;

        reverselevel(root->left,level+1);
        reverselevel(root->right,level+1);

    if(root->left != NULL && root->right != NULL && level%2 == 0)
    {
        char n = root->left->a;
        root->left->a = root->right->a;
        root->right->a = n;
    }

}


//func to convert char to ASCII value
int char_to_ASCII(char s)
{
    int v = int(s);
    return v;
}


//func to convert ASCII to char value
char ASCII_to_char(int x)
{
	char v = char(x);
	return v;
}


//utility func for swapping
void swap(int a, int b)
{	
	int temp;
	temp = a;
	a = b;
	b = temp;

}


//print final decryption
void printList (LL* head)
{
  
  cout<<"\n\nYour messeage has been successfully encoded...\n\n";
	cout<<"Final cipher is :::: "<<endl;
	
	while (head != NULL)
	{
		printf ("%c ",head->data);
		head = head->next;
	}
	return;

}


//print final encryption
void print_decrypt_result(string s)
{
	cout<<"\n\nYour messeage has been successfully decoded...\n\n";

	cout<<"Final message is :::: "<<s<<endl;
	
}



//encrypt / decrypt stored text file
void file_en_de()
{
  string name, target;
  char ch, mod;                         
  
  int num[100], i, option;

  cout <<"\n\nFOR FILE ENCRYPTION / DECRYPTION ";
  cout <<"\n\nEnter Your Option ";
  cout <<"\n1. To Encrypt The File ";
  cout <<"\n2. To Decrypt The File ";

  cout <<"\nOption : ";
  cin >> option;

  //ENCRYPTION OF TEXT FILE

  if (option == 1)
  {

    cout <<"\nEnter The Path Of A File Which Is To Be Encrypted : ";
    cin.ignore();
    getline(cin, name);

    ifstream fin(name);                             
    if (!fin)
    { 
      cout << "\n\nError In Openinig Of A File : ";               
    }

    cout << "Enter The New Encrypted File Name : ";
    cin.ignore();
    getline(cin, target);

    ofstream fout(target); 

    if (!fout)
    {
      cout << "\n\nError In Opening Of Target File : ";            
      
    }

    for (i = 0; i < 9; i++)
    {
      num[i] = i;                                             
    }

    for (i = 14; i < 31; i++)                                  
    {
      num[i - 5] = i;                                         
    }

    for (i = 33; i <= 68; i++)                                 
    { 
      num[i - 7] = i;                                    
    }

    for (i = 97; i <= 122; i++)
    {
      num[i - 35] = i;
    }

    while (fin)
    { 
      fin.get(ch);

      if (ch == EOF)
        break;                                 

      if ((ch >= 97) && (ch <= 122))
      { 
        i = 97;
        mod = num[ch - i];
        fout << mod;
      }

      if ((ch >= 65) && (ch <= 90))
      {
        i = 39;                                               
        mod = num[ch - i];                                    
        fout << mod;
      }

      if ((ch >= 48) && (ch <= 57))
      {
        i = 4;                                              
        mod = num[ch + i];
        fout << mod;
      }

      if ((ch == 10) || (ch == 13))
      {
        mod = ch;                                          
        fout << mod;
      }

      if (ch == 32)
        fout << ch;                                          

      if (ch == 9)
        fout << ch; 

      if ((ch >= 33) && (ch <= 47))
      { 
        mod = ch + 64;
        fout << mod;
      }

      if ((ch >= 58) && (ch <= 64))
      { 
        mod = ch + 54;
        fout << mod;
      }

      if ((ch >= 91) && (ch <= 96))
      {
        mod = ch + 28;                                      
        fout << mod;
      }

      if ((ch >= 123) && (ch <= 126))
      {
        mod = ch - 40;                                      
        fout << mod;
      }
    }

    fin.close();                                         
    
    fout.close();                                         
   

    cout << "\n\nYour File Is being Encrypted........... ";

    this_thread::sleep_for(chrono::seconds(1));

    cout << "\n\nYour File Is Encrypted Now........... ";
   
  }


  //DECRYPTION OF TEXT FILE

  if (option == 2)
  {

    string name, target;
    char ch, mod;                          
    int num[100], i, flag;

    cout << "\n\nEnter The Path Of A File Name Which Is To Be Decrypted : ";
    cin.ignore();
    getline(cin, name);

    ifstream fin(name);

    if (!fin)                                                   
    {
    
      cout << "\nError In Opening Of A File : ";
    
    }                                                            

    cout << "\n\nEnter The New Decrypted File Name : ";
    cin.ignore();
    getline(cin, target);

    ofstream fout;
    fout.open(target);  

    if (!fout)
    { 
      cout << "\nError In Opening Of A Target File : ";
      
    }

    for (i = 0; i < 9; i++)
    { 
      num[i] = i;                                               
    }

    for (i = 14; i < 31; i++)
    {
      num[i - 5] = i;                                           
    }

    for (i = 33; i <= 68; i++)                                      
    {
      num[i - 7] = i;
    }

    while (fin)
    { 
      fin.get(ch);
      flag = 0;                                                      
      
      if (ch == EOF)
        break;

      for (i = 26; i < 52; i++)
      {
        if (ch == num[i])                                         
        {
          mod = i + 39;                                            
          fout << mod;                                             
          flag = 1; 
          break ;                                           
        }
      }

      if (flag == 1) 
        continue ;                                      

      for (i = 0; i < 26; i++)
      { 
        if (ch == num[i])
        { 
          mod = i + 97;                                          
          fout << mod;
          flag = 1; break;                                           
        }
      }

      if (flag == 1) 
        continue ;                                     

      for (i = 52; i < 62; i++)
      { 
        if (ch == num[i])
        {
          mod = i - 4;
          fout << mod;
          flag = 1; 
          break ;
        }
      }

      if (flag == 1) 
        continue ;

      if ((ch == 10) || (ch == 13))
      {
        mod = ch;                                           
        fout << mod;
      }

      if (ch == 32)
        fout << ch;                                           

      if (ch == 9)
        fout << ch;                                           

      if ((ch >= 97) && (ch <= 111))
      {
        mod = ch - 64;                                      
        fout << mod;
      }

      if ((ch >= 112) && (ch <= 118))
      {
        mod = ch - 54;                                     
        fout << mod;
      }

      if ((ch >= 119) && (ch <= 124))
      {
        mod = ch - 28;                                     
        fout << mod;
      }

      if ((ch >= 83) && (ch <= 86))
      { 
        mod = ch + 40;
        fout << mod;
      }

    }

    fin.close();                                        
    fout.close();                                       

    cout << "\n\nThe File Is Being Decrypted............ ";
    
    this_thread::sleep_for(chrono::seconds(1));

    cout << "\n\nThe File Is Decrypted............ ";
    
    
 }

}


//encrytion level 1 - using array
string encrypt_1(string value)
{
	head = NULL;
	int i, l = value.size();
	int s[l];


	for(i=0; i<l; i++)
		s[i] = char_to_ASCII(value[i]);

	int p1 = 1;
	int p2 = 2;

	for(i=0; i<l; i=i+2)
	{
		s[i] = s[i] + p2;
		s[i+1] = s[i+1] + p1;
		p1 = p1+2;
		p2 = p2+2;
	}

	for(i=0; i<l; i++)
		value[i] = ASCII_to_char(s[i]);

	return value;

}


//encryption level 2 - using bt
string encrypt_2(string cipher)
{
	int n = cipher.length();

  Node* root = insertLevelOrder(cipher, root, 0, n);
  string traversal =  levelOrder(root);

  reverselevel(root,0);cout<<endl;

  string Encriper = levelOrder(root);
	
	return Encriper;
	
}


//encryption level 3 - run length using queue
void encrypt_3(string s)
{

	int n = s.size();
	int i=0;

	for(;i<n;i++)
	head = insert(head, s[i]);

	runLengthEncode (head);
	
	printList (head);
}


//decryption level 1 - run length using queue
string decrypt_1(LL* head)
{
	
    LL* p = head;
    string res = "";
    int count;
 
    while (p) 
    {
 
        count = 0;
 
        char c = p->data;
        if (p->next) 
        {
            LL* temp = p->next;
 
            if (temp && temp->data >= '0' && temp->data <= '9') 
            {
 
                while (temp && temp->data >= '0' && temp->data <= '9') 
                {
                    count = count * 10 + (temp->data - '0');
                    temp = temp->next;
                }
                p = temp;
            }
            else 
            {
                count = 1;
                p = p->next;
            }
        }
        else 
        {
            count = 1;
            p = p->next;
        }
 
        for (int i = 0; i < count; i++) 
        {
            res += c;
        }
    }
 
    return res;
    
}


//decryption level 2 - using bt
string decrypt_2(string cipher)
{
	 int n = cipher.length();

    Node* root = insertLevelOrder(cipher, root, 0, n);
    string traversal =  levelOrder(root);

    reverselevel(root,0);cout<<endl;

    string decipher = levelOrder(root);
    
    return decipher;
}


//decryption level 3 - using array
void decrypt_3(string value)
{
	
	int i, l = value.size();
	int s[l];


	for(i=0; i<l; i++)
		s[i] = char_to_ASCII(value[i]);

	int p1 = 1;
	int p2 = 2;

	for(i=0; i<l; i=i+2)
	{
		s[i] = s[i] - p2;
		s[i+1] = s[i+1] - p1;
		p1 = p1+2;
		p2 = p2+2;
	}

	for(i=0; i<l; i++)
		value[i] = ASCII_to_char(s[i]);

	print_decrypt_result( value);

}


//about project
void about_project()
{
	cout<<"\n ABOUT THE PROJECT";
	cout<<"\n\n\nThis project is developed as the mini-project for Data Structures Lab";
	cout<<"\n\nIn this digitalized era, the amount of data created and shared using internet has been increasing day by day.\nWe use different applications for data exchange every day."; 
	cout<<"\nThe number of security threats has also increased due to vulnerabilities in the network and software.";
	cout<<"\nIn this project, we have created a data encrypter which can encrypt the data entered. \nThe encrypted data, then can be shared easliy.";
	cout<<"\nThis program also includes a decrypter which can easily extract original message from the cipher.";

	cout<<"\n\nHere, we have used 3 level encryption to ensure maximum security of the data.\nAlso, since this process does not require an key, its hard to crack the idea without any prior knowledge.";

	cout<<"\n\nFor an working example, kindly visit the \"Display Process with Example\" option in the \"Key Encryption\" menu\n\n";
}


//about developers
void about_developers()
{
	cout<<"\n.....ABOUT THE DEVELOPERS.....\n\n";

	cout<<"This project is developed by students of Jaypee Institute of Information Technology";
	cout<<"\n\nBatch: F6, B.Tech 2023";
	cout<<"\n\nThe information about developers is given below (alphabetically): ";
	cout<<endl<<endl;

	cout<<"\n ____________________________________________________________________________";
	cout<<"\n|                 Name                |             Enrollment No.           |";
	cout<<"\n ____________________________________________________________________________";
	cout<<"\n|          ADITI SHARMA               |                9919103162            |";
	cout<<"\n|          BRISTI JANA                |                9919103154            |";
	cout<<"\n|          SHIVIKA SHARMA             |                9919103171            |";
	cout<<"\n|          VISAL AHMED                |                9919103167            |";
	cout<<"\n|____________________________________________________________________________|";

}


//main function for encryption
void encrypt()
{
	string txt;

	cout<<"\n\n\t ...ENCRYPTION...\n";

	cout<<"\n\nPlease Enter the Text :: \n";
	cout<<"\nPress enter to stop...\n\n";
	cin.ignore();
	getline(cin, txt);
	cout<<endl;

	string en_1 = encrypt_1(txt);

	txt = encrypt_2(en_1);

	encrypt_3(txt);

}


//main function for decryption
void decrypt()
{
	string txt;

	cout<<"\n\n\t ...DECRYPTION...\n";

	cout<<"\nPlease Enter the Cipher :: \n";
	cout<<"\nPress enter to stop...\n\n";

	cin.ignore();
	getline(cin, txt);
	cout<<endl;

	LL* list = txt_to_ll(txt);

	string de_1 = decrypt_1(list);

	txt = decrypt_2(de_1);

	decrypt_3(txt);
}


//function to display process step by step
void display()
{
	cout<<"\n\n\t DISPLAY SECTION\n";
	cout<<"\n\nHi, this section is created to give users an idea about working of this project ";

	string txt, s;

	cout<<"\n\nPlease Enter a Message to continue...\n";
	cout<<"\nPress enter to stop...\n\n";
	cin.ignore();
	getline(cin, txt);
	cout<<endl;

	cout<<"\n\nThe text is being encrypted on 1st level...";
	s = encrypt_1(txt);

	this_thread::sleep_for(chrono::seconds(1));

	cout<<"\nThe first level cipher is : ";
	cout<<s;

	cout<<"\n\nThe text is being encrypted on 2nd level...";
	txt = encrypt_2(s);

	this_thread::sleep_for(chrono::seconds(1));

	cout<<"\nThe second level cipher is : ";
	cout<<txt;

	cout<<"\n\nNow, The text is being encrypted on 3rd level...";
	
	this_thread::sleep_for(chrono::seconds(1));

	encrypt_3(txt);

	cout<<"\n\n\nNow we will decrypt the text...";

	cout<<"\n\nThe text is being decrypted on 3rd level...";
	s = decrypt_1(head);

	this_thread::sleep_for(chrono::seconds(1));

	cout<<"\nThe text after decryption is : ";
	cout<<s;

	cout<<"\n\nThe text is being decrypted on 2nd level...";
	txt = decrypt_2(s);

	this_thread::sleep_for(chrono::seconds(1));

	cout<<"\nThe text after decryption is : ";
	cout<<txt;

	cout<<"\n\nThe text is being decrypted on last level...";

	this_thread::sleep_for(chrono::seconds(1));

	decrypt_3(txt);

}


//menu for key encryption
void key_encryption()
{
	int ch, flag = 1;
	char ch2;

  LL* head = NULL;

	cout<<"\n\n\t..........Welcome to Key Encryption..........\n\n";

	do{

	cout<<":: Menu ::\n ";
	cout<<"\n1) ENCRYPT DATA \n2) DECRYPT DATA ";
	cout<<"\n3) DISPLAY PROCESS WITH EXAMPLE \n4) FILE ENCRYPTION(text files only)";
  cout<<"\n5) BACK TO MAIN MENU";

	cout<<"\n\nEnter ypur choice :: ";
	cin>>ch;

	switch(ch)
	{
		case 1: 
            encrypt();
				    break;


		case 2:  
            decrypt();
				    break;

				
		case 3: 
            display();
				    break;


		case 4: file_en_de();
				break;


    case 5: cout<<"\n\nEnter n/N in the next question to visit main menu...";
        break;


		default: cout<<"\n\tInvalid choice!!\n\tPlease try again...";
					break;
	}

	cout<<"\n\nDo you want to revisit the menu?(y/n) :: ";
	cin>>ch2;


	}while(ch2=='y' || ch2=='Y');

}


//function for displaying menu
void menu()
{
  int ch, flag1 = 1;
  char ch2;

  cout<<"\n _________________________________________________________________________________________";
  cout<<"\n|                                                                                         |";
  cout<<"\n|                                       KEY ENCRYPTION                                    |";
  cout<<"\n|                                                                                         |";
  cout<<"\n|_________________________________________________________________________________________|";

  cout<<endl<<endl;


  do
  {
    
  cout<<"\n __________________________________________________________________________________________";
  cout<<"\n|                                                                                          |";
  cout<<"\n|                                       ...MAIN MENU...                                    |";
  cout<<"\n|                                                                                          |";
  cout<<"\n|__________________________________________________________________________________________|";

    cout<<"\n\n\tPLEASE CHOOSE AN OPTION: \n";

    cout<<"\n\t1) About the Project";
    cout<<"\n\t2) About Developers";
    cout<<"\n\t3) Key Encryption";
    cout<<"\n\t4) Quit";

    cout<<"\n\n\tEnter your choice ::  ";
    cin>>ch;


    switch(ch)
    {
      case 1: about_project();
          break;

      case 2: about_developers();
          break;

      case 3: key_encryption();
          break;

      case 4: goto QUIT;
          break;

      default: cout<<"\n\tInvalid choice!!\n\tPlease try again...";
          break;
    }

    cout<<"\n\nDo you want to revisit the main menu?(y/n) :: ";
    cin>>ch2;

  }while(ch2=='y' || ch2=='Y');

  QUIT:;
}


//main function for program
int main()
{
  
  menu();
	
	return 0;
}