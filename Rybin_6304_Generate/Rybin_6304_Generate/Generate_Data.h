/*!
\file
\brief Data functions to generate

This file contains struct and functions for save and work with generated data.

\author Rybin Aleksandr 1 course 2 half
\date 15.03.2017
\version 1.0

*/

#include "Generate.h"

/*!
\struct
\brief Struct Table for generating temporary data for tables
*/
typedef struct Table
{
	char* name;				//!< Name of student
	char* surname;			//!< Surame of student
	char* patronymic;		//!< Patronymic of student
	char* GitHub_account;	//!< GitHub account of student
	char* Email;			//!< Student's email
	int group;				//!< Student's group
	int exam_result;		//!< Mark for exam
	int number;				//!< Number of element in list

	Table* next;			//!< Pointer to next element
	Table* prev;			//!< Pointer to previous element
} Table;

/*!
\brief Generates table field
\param[in] number Number of creating element
\return Table_obj Pointer to new object
\ingroup Generate_Random_Data
*/
Table* generate_field(int number)
{
	Table* Table_obj = (Table*)malloc(sizeof(Table));

	Table_obj->Email = generate_token(1);
	Table_obj->GitHub_account = generate_token(2);
	Table_obj->name = generate_token(0);
	Table_obj->surname = generate_token(0);
	Table_obj->patronymic = generate_token(0);
	Table_obj->group = 1 + rand() % 1000;
	Table_obj->exam_result = 1 + rand() % 6;
	Table_obj->number = number;

	Table_obj->next = NULL;
	Table_obj->prev = NULL;

	return Table_obj;
}

/*!
\brief Push new object to end of list
\param[in] head Pointer to begin of list
\param[in] new_element Pointer to object to push
\return void
\ingroup Generate_Random_Data
*/
void push(Table* head, Table* new_element)
{
	while (head->next)
	{
		head = head->next;
	}

	head->next = new_element;
	new_element->prev = head;
}

/*!
\brief Crate list of random fields
\param[in] head Pointer to begin of list
\param[in] count number of elements that wiil be generate
\return void
\ingroup Generate_Random_Data
*/
void create_random_list(Table* head,int count)
{
	for (int i = 0; i < count; i++)
	{
		push(head, generate_field(i));
	}
}

void print_field(Table* head, int number,FILE* table1,FILE*table2)
{
	while (head->next)
	{
		if (head->number == number)
		{
			fprintf(table1, "%s,%s,%s,%s,%s,%d\n",
				head->name,
				head->surname,
				head->patronymic,
				head->Email,
				head->GitHub_account,
				head->group);
			fprintf(table2, "%s,%s,%d\n",
				head->name,
				head->surname,
				head->exam_result);

			return;
		}
		else
			head = head->next;
	}
}

/*!
\brief Free list
\param[in] head Pointer to begin of list
\return void
\ingroup Generate_Random_Data
*/
void free_list(Table* head)
{
	while (head)
	{
		if (head->next = NULL)
		{
			free(head->Email);
			free(head->surname);
			free(head->name);
			free(head->patronymic);
			free(head->GitHub_account);
			free(head);
			return;
		}

		head = head->next;
		free(head->prev->Email);
		free(head->prev->surname);
		free(head->prev->name);
		free(head->prev->patronymic);
		free(head->prev->GitHub_account);
		free(head->prev);


	}
}