/*!
\file
\brief Refsol header file
\author Rybin Aleksandr 1 course 2 half
\date 30.03.2017
\version 2.0
*/

#include "Generator.h"

#define Sizeof_Commands 10

/*!
\brief Read data from tables
\param[in] stream_1 pointer to first table
\param[in] stream_2 pointer to second table
\return first_element Pointer to begin of readed list
\ingroup Refsol
*/
Table* Read_Data(FILE* stream_1, FILE* stream_2)
{	
	int buf;

	/* Skip headers of tables */
	while ((buf = fgetc(stream_1)) != '\n')
		if (feof(stream_1))
		{
			printf("Fail with input_file_1");
			return NULL;
		}
	while ((buf = fgetc(stream_2)) != '\n')
		if (feof(stream_2))
		{
			printf("Fail with input_file_2");
			return NULL;
		}

	/* Number of line in table */
	int number = 1;
	/* Create first element that will be return */
	Table* first_element = create_input_element();
	Table* input_head = first_element;

	/* Reading fields */
	do
	{
		int i = 0;

		while ((buf = fgetc(stream_1)) != ',')
		{
			if (feof(stream_1))
				return first_element;
			input_head->name[i++] = buf;
		}
		input_head->name[i] = '\0';
		i = 0;

		while ((buf = fgetc(stream_1)) != ',')
		{
			if (feof(stream_1))
				return first_element;
			input_head->surname[i++] = buf;
		}
		input_head->surname[i] = '\0';
		i = 0;
		
		while ((buf = fgetc(stream_1)) != ',')
		{
			if (feof(stream_1))
				return first_element;
			input_head->patronymic[i++] = buf;
		}
		input_head->patronymic[i] = '\0';

		i = 0;

		while ((buf = fgetc(stream_1)) != ',')
		{
			if (feof(stream_1))
				return first_element;
			input_head->GitHub_account[i++] = buf;
		}
		input_head->GitHub_account[i] = '\0';

		i = 0;

		while ((buf = fgetc(stream_1)) != ',')
		{
			if (feof(stream_1))
				return first_element;
			input_head->Email[i++] = buf;
		}
		input_head->Email[i] = '\0';

		i = 0;

		fscanf(stream_1, "%d", &input_head->group);
		if (feof(stream_1))
			return first_element;

		/* Skip to fields in second table */
		while ((buf = fgetc(stream_2)) != ',')
			if (feof(stream_2))
				return first_element;;
		while ((buf = fgetc(stream_2)) != ',')
			if (feof(stream_2))
				return first_element;;

		fscanf(stream_2, "%d", &input_head->exam_result);
		if (feof(stream_2))
			return first_element;

		input_head->number = ++number;

		/* Create in end new object */
		push(input_head, create_input_element());
		input_head = input_head->next;

		/* Go to new line */
		while ((buf = fgetc(stream_1)) != '\n');
		if (feof(stream_1))
			return first_element;
		while ((buf = fgetc(stream_2)) != '\n')
			if (feof(stream_2))
				return first_element;
	} while (true);
}

/*!
\brief Read commands from file
\param[in] commands Pointer to file with commands
\param[in]\[out] commands_vector Pointer to vector to write commands
\return -1 if any error, or lenth of commands_vector if read correctly
\ingroup Refsol
*/
int Read_Commands(FILE* commands,int** commands_vector)
{
	*commands_vector = (int*)malloc(sizeof(int) * Sizeof_Commands);
	int size_commands = Sizeof_Commands;
	int buf = 0;
	int counter_commands = 0;

	while (fscanf(commands,"%d",&buf) != EOF)
	{	
		/* If commands exists yet */
		if ((buf < 1) || (buf > 5))
		{
			printf("Fail with command %d", counter_commands + 1);
			return -1;
		}
		else if(counter_commands > size_commands - 1)
		{
			size_commands *= 2;
			*commands_vector = (int*)realloc(commands_vector,size_commands);
		}
		else
		{
			*(*commands_vector + counter_commands++) = buf;
		}
	}
	/* Check when file ends */
		if (counter_commands < 1)
		{
			printf("Too few commands");
			return -1;
		}
		else if (*(*commands_vector + counter_commands - 1) != 5)
		{
			printf("Fail with last command");
			return -1;
		}
		else
			return counter_commands;
}

/*!
\brief Removes same fields
\param[in] input_head Pointer to begin of list
\return void
\ingroup Refsol
*/
void Remove_Repeats(Table* input_head)
{
	while (input_head->next)
	{
		Table* obj = input_head->next;
		while (obj->next)
		{
			if ((strcmp(input_head->name, obj->name) == 0) &&
				(strcmp(input_head->surname, obj->surname) == 0) &&
				(strcmp(input_head->Email, obj->Email) == 0) &&
				(strcmp(input_head->GitHub_account, obj->GitHub_account) == 0) &&
				(strcmp(input_head->patronymic, obj->patronymic) == 0) &&
				(input_head->exam_result == obj->exam_result) &&
				(input_head->group == obj->group))
			{
				Table* tmp_obj = obj;
				obj = obj->next;
				Remove_element(tmp_obj);
			}
			else
				obj = obj->next;
		}
		input_head = input_head->next;
	}
}

