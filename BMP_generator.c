#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#pragma pack(push)
#pragma pack(2) // ������������ �������� �� ��� �����

typedef struct BITMAPFILEHEADER // �������� �������� ��� ���������� �������������� ����� BMP �����
{
	unsigned char   bfType[2];
	unsigned long	bfSize;
	unsigned short	bfReserved1;
	unsigned short	bfReserved2;
	unsigned long	bfOffBits;
} BITMAPFILEHEADER;

typedef struct BITMAPINFOHEADER
{
	unsigned int    biSize;
	int             biWidth;
	int             biHeight;
	unsigned short  biPlanes;
	unsigned short  biBitCount;
	unsigned int    biCompression;
	unsigned int    biSizeImage;
	int             biXPelsPerMeter;
	int             biYPelsPerMeter;
	unsigned int    biClrUsed;
	unsigned int    biClrImportant;
} BITMAPINFOHEADER;

#pragma pack(pop)

void create_BMP(int nx, int ny);

void create_TXT(int nx, int ny, int number_of_commands);

int main()
{
	srand(time(NULL));								// ��������� ����� ���������

	int nx, ny, number_of_commands;
	scanf("%d%d%d", &nx, &ny, &number_of_commands); // ���������� (�����������, ����� �������� ����������� ���������� ��� ����������)

	create_BMP(nx, ny);								// �������� ���������� BMP ����� � ��������� ���������
	create_TXT(nx, ny, number_of_commands);			// �������� ���������� txt ����� ����������� ������� ��� �������� bmp �����

	return 0;
}

void create_BMP(int nx, int ny)
{
	BITMAPFILEHEADER header_BMP;					// ���������� �������� ��� ���������� �������������� �����
	BITMAPINFOHEADER info_BMP;

	int staff_for_filling = 4 - ((nx * 3) % 4);		// ���������� ������������ ���������� ��� ��� ������������
	if (staff_for_filling == 4)
	{
		staff_for_filling = 0;
	}

	int size_of_image = ((nx * 3) + staff_for_filling) * ny; // ���������� ������� ����������� (��� ���. �����)

	header_BMP.bfType[0] = 'B';						// ���������� �������������� ����� BMP ����� � ������������ � �������������
	header_BMP.bfType[1] = 'M';
	header_BMP.bfSize = 54 + size_of_image;			// ������ �������������� �������� ����� 54 �����
	header_BMP.bfReserved1 = 0;
	header_BMP.bfReserved2 = 0;
	header_BMP.bfOffBits = 54;						// ���������� ��� ������� ����� ������� ������� �����������

	info_BMP.biSize = 40;							// ������ ��������� info_BMP � �����
	info_BMP.biWidth = nx;							// ���������� �������� �� �����������
	info_BMP.biHeight = ny;							// ���������� �������� �� ���������
	info_BMP.biPlanes = 1;							// ������ ���� ����������� �� 1
	info_BMP.biBitCount = 24;						// ���������� ��� � ����� ������� (� ������ ������ 3 ����� �� �������)
	info_BMP.biCompression = 0;						// ��� ������
	info_BMP.biSizeImage = size_of_image;			// ������ ����������� � �����
	info_BMP.biXPelsPerMeter = 0;					// � ������ ������ ��������� ���� �� ������������ � ����� �� ��������� ����
	info_BMP.biYPelsPerMeter = 0;
	info_BMP.biClrUsed = 0;
	info_BMP.biClrImportant = 0;

	FILE * pFile = fopen("input_file_test.bmp", "wb");		// �������� ����� � �����

	fwrite(&header_BMP, sizeof(BITMAPFILEHEADER), 1, pFile); // ������ ������������ �������� � ������ �����
	fwrite(&info_BMP, sizeof(BITMAPINFOHEADER), 1, pFile);

	int rand_colour = 0;

	for (int i = 0; i < ny; i++)		// ���� ����������� ������ � ��������� ���������� ������ ����������� ���������� ������� (���������� �������)
	{
		for (int j = 0; j < (nx * 3) + staff_for_filling; j++)
		{
			if (j > (nx * 3))					// ���� ��� ������� ������ �������� � ��������� �������� ���� ��� ������������ ��� ������������
			{
				fprintf(pFile, "%c", 0);
				continue;
			}
			rand_colour = rand() % 256;			// ��������� ���������� ����� ���������������� ����� �� ������������ ������� (RGB)
			fwrite(&rand_colour, 1, 1, pFile);	// ������ ���������� ����� � ������ �����������
		}
	}
	fclose(pFile);								// �������� ��������� ������
}

void create_TXT(int nx, int ny, int number_of_commands)
{
	FILE* pFile = fopen("input.txt", "w");					// �������� ���������� ����� ��� ������

	fprintf(pFile, "%d\n%d\n%d\n%d\n",						// ������ � ���� ������ ��������� � ������
		(rand() % ((nx + (nx / 4))) - rand() % (nx / 2)),	// ��� ������������ �������������� ��������� ���������
		(rand() % ((ny + (ny / 4))) - rand() % (ny / 2)),	// � ������������
		rand() % (nx + (nx / 8)),							// ������ ������������� �������� � ��������� ��������� �� �������������
		rand() % (ny + (ny / 8)));							// ������ ��������� ��������� (����� � ������ �����)

	for (int i = 0; i < number_of_commands; i++)
	{
		fprintf(pFile, "%d\n", ((rand() % 3)+1));			// ������ � ���� ������ ��� ��������� ����� � ����������
	}
	fprintf(pFile, "%d", 4);								// ������ � ����� ������� ���������� ����� �����������

	fclose(pFile);											// �������� ��������� ������
}
