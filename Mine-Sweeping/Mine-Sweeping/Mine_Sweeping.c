#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ROW 9
#define COL 9
#define MINE_COUNT 10

int Menu()
{
	printf("=======================\n");
	printf("1.��ʼ��Ϸ\n");
	printf("0.������Ϸ\n");
	printf("=======================\n");
	int choice = 0;
	printf("����������ѡ��!\n");
	scanf("%d", &choice);
	return choice;
}

void Init(char mine_map[ROW + 2][COL + 2],
	char show_map[ROW + 2][COL + 2])
{
	//1.show_map����ʼ���� * ����ʾû�з�����λ�ã�
	for (int row = 0; row < ROW + 2; ++row)
	{
		for (int col = 0; col < COL + 2; ++col)
		{
			show_map[row][col] = '*';
		}
	}
	//2.mine_map����ʼ��Ϊ'0'
	for (int row = 0; row < ROW + 2; ++row)
	{
		for (int col = 0; col < COL + 2; ++col)
		{
			mine_map[row][col] = '0';
		}
	}
	//��������ķ��������ԣ�����memset��һ���������ڴ�ռ���и�ֵ
	//��ά����Ҳ����һ���������ڴ�ռ���
	//memset(mine_map, '0', (ROW + 2)*(COL + 2));
	//memset(show_map, '*', (ROW + 2)*(COL + 2));

	//3.��mine_map��������Ĳ���
	int mine_count = MINE_COUNT;
	while (mine_count > 0)
	{
		//���ѭ�����Խ��в��ף�ÿ�β��óɹ�һ����mine_count--
		//magice number
		int row = rand() % 9 + 1;
		int col = rand() % 9 + 1;
		if (mine_map[ROW][COL] == '1')
		{
			continue;
		}
		//��ǰλ�ÿ����������õ���
		mine_map[row][col] = '1';
		--mine_count;
	}
	return;
}

void DisplayMap(char map[ROW + 2][COL + 2])
{
	//�ȴ�ӡ�ĸ��ո�
	printf("    ");
	//��ӡ�е�����
	for (int i = 1; i <= COL; ++i)
	{
		printf("%d ", i);
	}
	printf("\n");
	//��һ�д�ӡ���
	//�����ӡ�ϱ߿�
	for (int i = 1; i <= COL; ++i)
	{
		printf("---");
	}
	printf("\n");
	//��ӡ���̵�ÿһ�У�ע�⣬ÿһ����ǰ���Ҫ�����к�
	for (int row = 1; row <= ROW; ++row)
	{
		printf("  %d|", row);
		for (int col = 1; col <= COL; ++col)
		{
			printf("%c ", map[row][col]);
		}
		printf("\n");
	}
}

void UpdateShowMap(char mine_map[ROW + 2][COL + 2],
	char show_map[ROW + 2][COL + 2], int row, int col)
{
	//ÿ�η���һ�����ӵ�ʱ�����������Ӳ����ף�����Ҫ����show_map
	//�ѵ�ǰλ���滻��һ������(���־ͱ�ʾ�˵�ǰλ����Χ8���������м�������)
	int mine_count =
		(mine_map[row - 1][col - 1] - '0')
		+ (mine_map[row - 1][col] - '0')
		+ (mine_map[row - 1][col + 1] - '0')
		+ (mine_map[row][col - 1] - '0')
		+ (mine_map[row][col + 1] - '0')
		+ (mine_map[row + 1][col - 1] - '0')
		+ (mine_map[row + 1][col] - '0')
		+ (mine_map[row + 1][col + 1] - '0');
	//����show_map�ж����ַ�����Ҫ���������ת��Ϊ�ַ�
	show_map[row][col] = mine_count + '0';
	//��������ifһ��һ�������ж��ķ�����
	//if (mine_map[row - 1][col - 1] == '1')//�߿����Ϊ�����ﲻ��Խ��
	//{
	//	++mine_count;
	//}
	//if (mine_map[row - 1][col - 1] == '1')
	//{

	//}
}

void Game()
{
	printf("'0'��ʾû�е��ף�'1'��ʾ�е���\n");
	//1.�趨һ����ά���飬��Ϊ��ʾ���׵ĵ�ͼ��'0'��ʾû�е��ף�'1'��ʾ�е���
	//  �趨һ����ά���飬��Ϊ����ҿ��ĵ�ͼ��ÿ��λ���Ƿ񱻷������������
	//�ڴ˴�����2��ʾ����һȦ�߿�
	char mine_map[ROW + 2][COL + 2];
	char show_map[ROW + 2][COL + 2];
	//2.�Ե�ͼ���г�ʼ�����������õ��׵Ĺ��̣�
	Init(mine_map, show_map);
	int blank_not_mine_count = 0;//�����׵ĸ���
	//3.�ȴ�ӡһ�³�ʼ��ͼ
	DisplayMap(show_map);
	while (1)
	{
		//4.��ʾ�������һ�����꣬���Ҷ����������кϷ��Լ��
		printf("������һ�����꣨row col����");
		int row = 0;
		int col = 0;
		scanf("%d %d", &row, &col);
		//row,col����Ч��Χ[1,row][1,col]��ͼ���б߿�
		if (row<1 || row>ROW || col<1 || col>COL)
		{
			printf("�����������Ƿ������������룺\n");
			continue;
		}
		//5.��ʾ��ҷ�����λ���Ƿ��ǵ��ף�����ǵ�ͼ����Ϸ����
		if (mine_map[row][col] == '1')
		{
			printf("�������ˣ���Ϸ������\n");
			//��Ҳ��׺���Ҫ������ҵ�ǰ��ͼ�϶�����Щλ���ǵ���
			DisplayMap(mine_map);
			break;
		}
		//6.�����ǰλ���Ѿ������һ�������׵�λ�÷����ˣ���Ϸ���������ʤ��
		++blank_not_mine_count;
		if (blank_not_mine_count == ROW * COL - MINE_COUNT)
		{
			printf("ɨ�׳ɹ���\n");
			DisplayMap(mine_map);
			break;
		}
		//7.�����λ�÷����������㵱ǰλ����Χ8�������а���������
		UpdateShowMap(mine_map, show_map, row, col);
		DisplayMap(show_map);
		//�ص�3ѭ��ִ��

	}

}

int main()
{
	while (1)
	{
		int choice = Menu();
		if (choice == 1)
		{
			Game();
		}
		else
		{
			printf("Goodbye!\n");
			break;
		}
	}



	return 0;
}
