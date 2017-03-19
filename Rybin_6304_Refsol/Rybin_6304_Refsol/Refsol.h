#include "Refsol_Data.h"

/*!
\brief Read data from tables
\param[in] stream_1 pointer to first table
\param[in] stream_2 pointer to second table
\param[in] input1_head pointer to begin of list input1
\param[in] input2_head pinter to begin of lust input2
\return void
\ingroup Refsol_Data
*/
void Read_Data(FILE* stream_1, FILE* stream_2, input2* input2_head, input1* input1_head)
{
	int buf;
	while ((buf = fgetc(stream_1)) != '\n');
	while ((buf = fgetc(stream_2)) != '\n');

	do
	{
		int i = 0;

		while ((buf = fgetc(stream_1)) != ',')
		{
			input1_head->name[i++] = buf;
		}
		input1_head->name[i] = '\0';

		i = 0;

		while ((buf = fgetc(stream_1)) != ',')
		{
			input1_head->surname[i++] = buf;
		}
		input1_head->surname[i] = '\0';
		i = 0;
		
		while ((buf = fgetc(stream_1)) != ',')
		{
			input1_head->patronymic[i++] = buf;
		}
		input1_head->patronymic[i] = '\0';

		i = 0;

		while ((buf = fgetc(stream_1)) != ',')
		{
			input1_head->GitHub_account[i++] = buf;
		}
		input1_head->GitHub_account[i] = '\0';

		i = 0;

		while ((buf = fgetc(stream_1)) != ',')
		{
			input1_head->Email[i++] = buf;
		}
		input1_head->Email[i] = '\0';

		i = 0;

		fscanf(stream_1, "%d", &input1_head->group);

		push_input1(input1_head, create_input1_element());
		input1_head = input1_head->next;

		while ((buf = fgetc(stream_2)) != ',')
		{
			input2_head->name[i++] = buf;
		}
		input2_head->name[i] = '\0';

		i = 0;
		
		while ((buf = fgetc(stream_2)) != ',')
		{
			input2_head->surname[i++] = buf;
		}
		input1_head->surname[i] = '\0';

		i = 0;

		fscanf(stream_2, "%d", &input2_head->exam_result);

		push_input2(input2_head, create_input2_element());
		input2_head = input2_head->next;

		while ((buf = fgetc(stream_1)) != '\n');
		while ((buf = fgetc(stream_2)) != '\n');

	} while (!feof(stream_1));


}