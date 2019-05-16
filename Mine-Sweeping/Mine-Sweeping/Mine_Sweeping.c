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
	printf("1.开始游戏\n");
	printf("0.结束游戏\n");
	printf("=======================\n");
	int choice = 0;
	printf("请输入您的选择!\n");
	scanf("%d", &choice);
	return choice;
}

void Init(char mine_map[ROW + 2][COL + 2],
	char show_map[ROW + 2][COL + 2])
{
	//1.show_map都初始化成 * （表示没有翻开的位置）
	for (int row = 0; row < ROW + 2; ++row)
	{
		for (int col = 0; col < COL + 2; ++col)
		{
			show_map[row][col] = '*';
		}
	}
	//2.mine_map都初始化为'0'
	for (int row = 0; row < ROW + 2; ++row)
	{
		for (int col = 0; col < COL + 2; ++col)
		{
			mine_map[row][col] = '0';
		}
	}
	//除了上面的方法还可以：利用memset对一段连续的内存空间进行赋值
	//二维数组也是在一个连续的内存空间上
	//memset(mine_map, '0', (ROW + 2)*(COL + 2));
	//memset(show_map, '*', (ROW + 2)*(COL + 2));

	//3.对mine_map进行雷阵的布置
	int mine_count = MINE_COUNT;
	while (mine_count > 0)
	{
		//这个循环尝试进行布雷，每次布置成功一个则mine_count--
		//magice number
		int row = rand() % 9 + 1;
		int col = rand() % 9 + 1;
		if (mine_map[ROW][COL] == '1')
		{
			continue;
		}
		//当前位置可以用来设置地雷
		mine_map[row][col] = '1';
		--mine_count;
	}
	return;
}

void DisplayMap(char map[ROW + 2][COL + 2])
{
	//先打印四个空格
	printf("    ");
	//打印列的坐标
	for (int i = 1; i <= COL; ++i)
	{
		printf("%d ", i);
	}
	printf("\n");
	//第一行打印完成
	//这里打印上边框
	for (int i = 1; i <= COL; ++i)
	{
		printf("---");
	}
	printf("\n");
	//打印棋盘的每一行，注意，每一行最前面的要带上行号
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
	//每次翻开一个格子的时候，如果这个格子不是雷，就需要跟新show_map
	//把当前位置替换成一个数字(数字就表示了当前位置周围8个格子中有几个地雷)
	int mine_count =
		(mine_map[row - 1][col - 1] - '0')
		+ (mine_map[row - 1][col] - '0')
		+ (mine_map[row - 1][col + 1] - '0')
		+ (mine_map[row][col - 1] - '0')
		+ (mine_map[row][col + 1] - '0')
		+ (mine_map[row + 1][col - 1] - '0')
		+ (mine_map[row + 1][col] - '0')
		+ (mine_map[row + 1][col + 1] - '0');
	//由于show_map中都是字符，需要把这个数字转换为字符
	show_map[row][col] = mine_count + '0';
	//这是利用if一个一个进行判定的方法：
	//if (mine_map[row - 1][col - 1] == '1')//边框就是为了这里不会越界
	//{
	//	++mine_count;
	//}
	//if (mine_map[row - 1][col - 1] == '1')
	//{

	//}
}

void Game()
{
	printf("'0'表示没有地雷，'1'表示有地雷\n");
	//1.设定一个二维数组，作为表示地雷的地图，'0'表示没有地雷，'1'表示有地雷
	//  设定一个二维数组，作为给玩家看的地图，每个位置是否被翻开，如果翻开
	//在此处加了2表示加了一圈边框：
	char mine_map[ROW + 2][COL + 2];
	char show_map[ROW + 2][COL + 2];
	//2.对地图进行初始化（包含布置地雷的过程）
	Init(mine_map, show_map);
	int blank_not_mine_count = 0;//不是雷的个数
	//3.先打印一下初始地图
	DisplayMap(show_map);
	while (1)
	{
		//4.提示玩家输入一组坐标，并且对玩家输入进行合法性检查
		printf("请输入一组坐标（row col）：");
		int row = 0;
		int col = 0;
		scanf("%d %d", &row, &col);
		//row,col的有效范围[1,row][1,col]地图上有边框
		if (row<1 || row>ROW || col<1 || col>COL)
		{
			printf("您输入的坐标非法，请重新输入：\n");
			continue;
		}
		//5.提示玩家翻开的位置是否是地雷，如果是地图就游戏结束
		if (mine_map[row][col] == '1')
		{
			printf("您踩雷了，游戏结束！\n");
			//玩家踩雷后，需要告诉玩家当前地图上都有哪些位置是地雷
			DisplayMap(mine_map);
			break;
		}
		//6.如果当前位置已经把最后一个不是雷的位置翻开了，游戏结束，玩家胜利
		++blank_not_mine_count;
		if (blank_not_mine_count == ROW * COL - MINE_COUNT)
		{
			printf("扫雷成功！\n");
			DisplayMap(mine_map);
			break;
		}
		//7.把这个位置翻开，并计算当前位置周围8个格子中包含几个雷
		UpdateShowMap(mine_map, show_map, row, col);
		DisplayMap(show_map);
		//回到3循环执行

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
