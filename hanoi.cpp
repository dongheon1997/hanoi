#include <iostream>
#include <Windows.h>
#include <math.h>
using namespace std;

enum { FROM, TEMP, TO };//locations

class Tower {
	friend class UI;
private:
	int num;
	int *block;

public:
	Tower(int n) {
		num = n;
		block = new int[num];
		for (int i = 0; i < num; i += 1) block[i] = FROM;
	}
	~Tower() {
		delete[] block;
	}

	int getMin(int location) const {
		int min = INT_MAX;
		for (int i = 0; i < num; i += 1) {
			if (block[i] == location) {
				if (i < min) min = i;
			}
		}
		return min;
	}
	bool move(int origin, int destination) {
		int min = getMin(origin);
		if (min == INT_MAX || getMin(destination) <= min) {
			return false;
		}
		else {
			block[min] = destination;
			return true;
		}
	}
};

class UI {
private:
	Tower *tower;
	int attempt;
	int input, input2;

public:
	UI() {
		do {
			initialization();
			display();
			do {
				moveBlock();
				display();
			} while (!isFinish());
			celebration();
		} while (isOneMore());
	}

	void initialization() {
		do {
			cout << "������ �� ������ �Է��ϼ���. (1 ~ 10) �� ";
			cin >> input;
		} while (input < 1 || input > 10);
		tower = new Tower(input);
		attempt = 0;
	}
	void gotoxy(int x, int y) {
		COORD CursorPosition;
		CursorPosition.X = x;
		CursorPosition.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
	}
	void display() {
		system("cls");
		int temp = tower->num;
		cout << "��������������������������" << endl;
		for (int i = 0; i < temp; i += 1) cout << "��   ��   ��   ��" << endl;
		cout << "��������������������������" << endl;
		cout << "�� 1 �� 2 �� 3 ��" << endl;
		cout << "��������������������������" << endl;
		int layer[3] = { temp, temp, temp };
		temp = tower->num - 1;
		for (int i = temp; i >= 0; i -= 1) {
			temp = tower->block[i];
			gotoxy(temp * 4 + 2, layer[temp]--);
			cout << i;
		}
		gotoxy(0, tower->num + 5);
	}
	void moveBlock() {
		cout << attempt + 1 << "��° �õ�, ";
		while (true) {
			do {
				cout << "��� ���� �ű�ڽ��ϱ�? (1 ~ 3) �� ";
				cin >> input;
			} while (input < 1 || input > 3 || tower->getMin(input - 1) == INT_MAX);
			do {
				cout << "��� ������ �ű�ڽ��ϱ�? (1 ~ 3) �� ";
				cin >> input2;
			} while (input2 < 1 || input2 > 3);
			if (tower->move(input - 1, input2 - 1)) break;
			else cout << "�׷��� ���մϴ�. ";
		}
		attempt += 1;
	}
	bool isFinish() const {
		for (int i = 0; i < tower->num; i += 1) {
			if (tower->block[i] < TO) return false;
		}
		return true;
	}
	void celebration() {
		if (attempt == pow(2, tower->num) - 1) cout << "�Ϻ��ϰ� �س��̱���! ���ϵ帳�ϴ�." << endl;
		else cout << "��°��° �س��̱���. ���ϵ帳�ϴ�." << endl;
		delete tower;
	}
	int isOneMore() {
		cout << "�����Ͻ÷��� 0, ����Ͻ÷��� 1�� �Է��ϼ��� �� ";
		cin >> input;
		return input;
	}
};

int main() {
	UI();
	return 0;
}
