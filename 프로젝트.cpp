#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;

class ProductManage {
public:
	ProductManage();
	void mainMenu();
	void SellProcut();
	void DisplayMenu();
	void CalProduct();
	void CalMoney();
	void Displaybill();
	void stockManage();
	void End();
	void ManageMode();
	void searchStock();
	void inputStock();
	void returnStock();
	void searchItem();
	void changeItem();
	void changeCost();
	void CheckSales();
	void changePW();
	void searchSales();
	void searchOrderItem();
	void searchMarket();
	void searchSalesItems();
	void salesItemsInput();
	void changeSalesCost();
	void cancleCal();

private:
	string saMenu[6] = { "" };
	int saCost[6] = {0}; // �Ǹ� �ܰ�
	int saQty[6] = {0}; // ������ ���� ����
	int saItemTotalCost[6] = {0};
	int saManageStock[6] = { 0}; // ��� ����
	int totalCost = 0;
	int money = 0; // ���� �ݾ�
	int totalMoney = 0; // ���� �ݾ� ����
	string passWord="";
	int storageQty[6] = { 0 };
	int salesCost[6] = { 0 }; // �ŷ� �ܰ�
	int inputQty[6] = { 0 };  // �԰� ������ ����
};

ProductManage::ProductManage()
{
	ifstream fin;
	// ��ǰ��
	fin.open("itemName.txt");

	for (int i = 1; i < 6; i++)
	{
		fin >> saMenu[i];
	}
	fin.close();

	//����
	fin.open("itemQty.txt");

	for (int i = 1; i < 6; i++)
	{
		fin >> saManageStock[i];
	}
	fin.close();

	// �Ǹ� �ܰ�
	fin.open("itemCost.txt");
	for (int i = 1; i < 6; i++)
	{
		fin >> saCost[i];
	}
	fin.close();

	//�ŷ� �ܰ�
	fin.open("salesCost.txt");
	for (int i = 1; i < 6; i++)
	{
		fin >> salesCost[i];
	}
	fin.close();

	//������ ��ȣ
	fin.open("password.txt");
	fin >> passWord;
	fin.close();
}


void ProductManage::mainMenu()
{
	int selectNum;
	string CheckPassWord = "";
	do {
		system("cls");
		cout << "========== ���� �޴� ==========" << endl;
		cout << "1. ��ǰ�Ǹ�" << endl;
		cout << "2. ������" << endl;
		cout << "3. ����" << endl;
		cout << "4. ������ ���" << endl;
		cout << "===============================" << endl;
		cout << endl;
		cout << "� �޴��� �����Ͻðڽ��ϱ�?" << endl;
		cin >> selectNum;

		switch (selectNum)
		{
		case 1:
			SellProcut();
			break;
		case 2:
			stockManage();
			break;
		case 3:
			End();
			break;
		case 4:

			while (1) {
				cout << "�����ڸ�� ��ȣ�� �Է��ϼ���." << endl;
				cout << "��ȣ : ";
				cin >> CheckPassWord;
				if (passWord != CheckPassWord)
				{
					cout << "�߸��� ��ȣ�Դϴ�." << endl;
				}
				else break;
			}
			ManageMode();

			break;
		default:
			cout << "�޴��� �ٽ� �������ּ���" << endl;
			break;
		}
	} while (selectNum != 3);


}

void ProductManage::SellProcut()
{
	char selectPurchase;
	do {
		DisplayMenu();
		CalProduct();
		cout << "�� �����Ͻðڽ��ϱ�? (��: 1/Y, �ƴϿ�: 0/N)";
		cin >> selectPurchase;
	} while (selectPurchase == '1' || selectPurchase == 'Y' || selectPurchase == 'y');

	cancleCal();

	CalMoney();
	Displaybill();
}

void ProductManage::cancleCal()
{
	int selectProduct;
	int count;
	char selectChoose;
	system("cls");
	cout << "ǰ��" << "	" << "����" << "	" << "�ݾ�" << endl;
	for (int i = 1; i < 6; i++)
	{
		if (saQty[i] > 0)
			cout << saMenu[i] << "	" << saQty[i] << "	" << saItemTotalCost[i] << "��" << endl;
	}
	while (1)
	{
		cout << "��� �Ͻðڽ��ϱ�? (��: 1/Y, �ƴϿ�: 0/N)" << endl;
		cin >> selectChoose;
		if (selectChoose == '0' || selectChoose == 'N' || selectChoose == 'n')
			break;
		cout << "����Ͻ� ��ǰ ��ȣ�� �Է����ּ���." << endl;
		cin >> selectProduct;
		cout << "���� ������ �Է����ּ���." << endl;
		cin >> count;
		//�������� ����
		saQty[selectProduct] -= count;
		//����� ���ϰ�
		saManageStock[selectProduct] += count;
		//������� 
		storageQty[selectProduct] -= count;
		//�ݾ� ����
		saItemTotalCost[selectProduct] = saQty[selectProduct] * saCost[selectProduct];



		cout << "�� ���� �Ͻðڽ��ϱ�? (��: 1/Y, �ƴϿ�: 0/N)" << endl;
		cin >> selectChoose;
		if (selectChoose == '0' || selectChoose == 'N' || selectChoose == 'n')
			break;
	}

	


}

void ProductManage::DisplayMenu()
{
	system("cls");
	cout << "========== ��ǰ �޴� ==========" << endl;
	for (int i = 1; i < 6; i++)
	{
		cout << i << ". " << saMenu[i] << "	" << saCost[i] << "��	" << saManageStock[i] <<"��" << endl;
	}
	cout << "===============================" << endl;
	system("pause");
}

void ProductManage::CalProduct() 
{
	int count;
	int selectProduct;
	cout << "� ��ǰ�� �����Ͻðڽ��ϱ�?";
	cin >> selectProduct;
	cout << endl;
	cout << saMenu[selectProduct] << "�� �����ϼ̽��ϴ�." << endl;
	cout << "�ܰ���" << saCost[selectProduct] << "�Դϴ�.";
	cout << endl;


	do {
		cout << "��� �����Ͻðڽ��ϱ�?";
		cin >> count;
		if (saManageStock[selectProduct] < count)
		{
			cout << "��� ���� �ʰ�";
		}

	} while (saManageStock[selectProduct] < count);

	// �����ۺ� ���� ���� ����
	saQty[selectProduct]+= count;
	// ��ǰ�� ���� �Ǹ� ����
	storageQty[selectProduct] += count;

	saManageStock[selectProduct] -= count;

	saItemTotalCost[selectProduct] = saCost[selectProduct] * saQty[selectProduct];
	cout << "�����Ͻ� �ݾ���"<< saItemTotalCost[selectProduct] <<"�� �Դϴ�." << endl;


}

void ProductManage::CalMoney() //���� �ݾ� ���
{

	for (int i = 1; i < 6; i++)
	{
		totalCost += saItemTotalCost[i];
	}

	
	cout << "�����Ͻ� �� �ݾ���" << totalCost << "�� �Դϴ�." << endl; // 10

	while(1)
	{
		// ���� �� ���� �ݾ� �ݿ� �ȵ�
		cout << "�����ݾ��� �Ա����ֽñ� �ٶ��ϴ�." << endl;
		cout << "�����ݾ� : ";
		cin >> money; // 5+1
		cout << endl;
		totalMoney += money; // ���� �� ������Ʈ


		if (totalMoney < totalCost)
		{
			cout << "�����ݾ׿��� " << totalCost - totalMoney << " ���� �����մϴ�." << endl; // 5 �� �ٽ� ���� ��
		}

		else break;
	}

}

void ProductManage::Displaybill() // ������ display
{
	system("cls");
	cout << "========== ������ ==========" << endl;
	cout << "ǰ��" << "	" << "����" << "	" << "�ݾ�" << endl;
	for (int i = 1; i < 6; i++)
	{
		if (saQty[i] > 0)
			cout <<  saMenu[i]<< "	"<< saQty[i] << "	" << saItemTotalCost[i]<<"��" << endl;
	}
	cout << "============================" << endl;
	cout << "�ѱ��űݾ�		" << totalCost << "��" << endl;
	cout << "�����ݾ�	" << totalMoney << "��" << endl;
	cout << "�Ž�����	" << totalMoney- totalCost << "��" << endl;
	
	for (int i = 1; i < 6; i++)
	{
		saQty[i] = 0;
		saItemTotalCost[i] = 0;
	}
	system("pause");

}

void ProductManage::stockManage()
{
	int selectNum;
	do {
		system("cls");
		cout << "========== ������ ==========" << endl;
		cout << "1. �����ȸ" << endl;
		cout << "2. ��ǰ�԰�" << endl;
		cout << "3. ��ǰ��ǰ" << endl;
		cout << "4. �����޴�" << endl;
		cout << "===============================" << endl;
		cout << endl;
		cout << "� ������ �����Ͻðڽ��ϱ�?" << endl;
		cin >> selectNum;


		switch (selectNum)
		{
		case 1:
			searchStock();
			break;
		case 2:
			inputStock();
			break;
		case 3:
			returnStock();
			break;
		case 4:
			return;

		default:
			cout << "������ �ٽ� �������ּ���" << endl;
			break;
		}
	} while (selectNum!=4);
	
}

void ProductManage::End()
{
	// ��ǰ��
	ofstream fout;
	fout.open("itemName.txt");

	for (int i = 1; i < 6; i++)
	{
		fout << saMenu[i] << endl;
	}
	fout.close();

	// ����
	fout.open("itemQty.txt");

	for (int i = 1; i < 6; i++)
	{
		fout << saManageStock[i] << endl;
	}
	fout.close();

	//�ǸŴܰ�
	fout.open("itemCost.txt");
	for (int i = 1; i < 6; i++)
	{
		fout << saCost[i] << endl;
	}
	fout.close();

	//�ŷ��ܰ�
	fout.open("salesCost.txt");
	for (int i = 1; i < 6; i++)
	{
		fout << salesCost[i] << endl;
	}
	fout.close();

	//������ ��ȣ
	fout.open("password.txt");
	fout << passWord << endl;
	fout.close();

	cout << "========== ���� ==========" << endl;

}

void ProductManage::ManageMode()
{
	// �޴� �޴� ����
	int selectNum;
	do {
		system("cls");
		cout << "========== �����ڸ�� ==========" << endl;
		cout << "1. ��ǰ��ȸ" << endl;
		cout << "2. ��ǰ����" << endl;
		cout << "3. �ܰ�����" << endl;
		cout << "4. ���������Ȳ" << endl;
		cout << "5. �����޴�" << endl;
		cout << "6. ��ȣ����" << endl;
		cout << "===============================" << endl;
		cout << endl;
		cout << "� ��带 �����Ͻðڽ��ϱ�?" << endl;
		cin >> selectNum;

		switch (selectNum)
		{
		case 1:
			searchItem();
			break;
		case 2:
			changeItem();
			break;
		case 3:
			changeCost();
			break;
		case 4:
			CheckSales();
			break;
		case 5:
			return;
		case 6:
			changePW();
			break;
		default:
			cout << "������ �ٽ� ���ּ���." << endl;
			break;
		}
	} while (selectNum != 5);
}

void ProductManage::searchStock() // ��� ���
{
	system("cls");
	cout << "========== �����ȸ ==========" << endl;
	for (int i = 1; i < 6; i++)
	{
		cout << i << ". " << saMenu[i] << "	" << saManageStock[i] << "��" << endl;
	}
	cout << "===============================" << endl;
	system("pause");
}

void ProductManage::inputStock()
{
		int count;
		int selectProduct;
		char selectPurchase;
		system("cls");
		cout << "========== ��ǰ�԰� ==========" << endl;
		while (1) {
			// � ��ǰ �԰� ����
			cout << "�԰��Ͻ� ��ǰ ��ȣ�� �����ϼ���. " << endl;
			cin >> selectProduct;
			// ��ǰ ���� ����
			cout << "������ �Է��ϼ���." << endl;
			cin >> count;
			saManageStock[selectProduct] += count;
			// �԰� ������ ����
			inputQty[selectProduct] += count;

			// �� �� ������
			cout << "�� �԰��Ͻðڽ��ϱ�? (��: 1/Y, �ƴϿ�: 0/N)";
			cin >> selectPurchase;
			if (selectPurchase == '0' || selectPurchase == 'N' || selectPurchase == 'n')
				break;
		}
}

void ProductManage::returnStock()
{
	int selectProduct=0;
	int count;
	char selectChoose;
	system("cls");
	cout << "========== ��ǰ��ǰ ==========" << endl;

	while (1) {
		cout << "��ǰ�Ͻ� ��ǰ ��ȣ�� �����ϼ���." << endl;
		cin >> selectProduct;

		while (1) {
			cout << "������ �Է��ϼ���." << endl;
			cin >> count;
			if (count > saManageStock[selectProduct])
			{
				cout << "���������� ��ǰ ������ �� �����ϴ�." << endl;
			}
			else break;
		}

		saManageStock[selectProduct] -= count;
		cout << "�� ��ǰ�Ͻðڽ��ϱ�? (��: 1/Y, �ƴϿ�: 0/N)";
		cin >> selectChoose;
		if (selectChoose == '0' || selectChoose == 'N' || selectChoose == 'n')
			break;
	}
}

// ��ǰ ��ȸ
void ProductManage::searchItem()
{
	system("cls");
	cout << "========== ��ǰ��ȸ ==========" << endl;
	for (int i = 1; i < 6; i++)
		cout << i << "." << saMenu[i] << " " << saCost[i] << "��" << endl;
	cout << "==============================" << endl;
	system("pause");
}

void ProductManage::changeItem()
{
	int selectProduct;
	string newItemName;
	char selectChoose;
	system("cls");
	cout << "========== ��ǰ���� ==========" << endl;
	cout << "�����Ͻ� ��ǰ�� ��ȣ�� �Է��ϼ���." << endl;
	cin >> selectProduct;
	
	while (1) {
		cout << "������ ��ǰ���� �Է��ϼ���." << endl;
		cin >> newItemName;
		// �ٽ� ������ 
		cout << "������ ��ǰ�� Ȯ�� : (��: 1/Y, �ƴϿ�: 0/N) " << newItemName << endl;
		cin >> selectChoose;
		if (selectChoose == '1' || selectChoose == 'Y' || selectChoose == 'y')
			break;
	}

	saMenu[selectProduct] = newItemName;
	cout << "��ǰ���� ����Ǿ����ϴ�." << endl;

}

void ProductManage::changeCost()
{
	int selectProduct;
	int changeMoney;
	char selectChoose;
	system("cls");
	cout << "========== �ܰ����� ==========" << endl;
	cout << "�����Ͻ� ��ǰ�� ��ȣ�� �Է��ϼ���." << endl;
	cin >> selectProduct;

	while (1) {
		cout << "������ �ܰ��� �Է��ϼ���." << endl;
		cin >> changeMoney;
		cout << "������ �ܰ� Ȯ�� : (��: 1/Y, �ƴϿ�: 0/N) " << changeMoney << "��" << endl;
		cin >> selectChoose;
		if (selectChoose == '1' || selectChoose == 'Y' || selectChoose == 'y')
			break;
	}

	saCost[selectProduct] = changeMoney;
	cout << "��ǰ �ܰ��� ����Ǿ����ϴ�." << endl;
}

void ProductManage::CheckSales()
{
	int selectNum;
	do {
		system("cls");
		cout << "========== ���������Ȳ ==========" << endl;
		cout << "1. ������Ȳ��ȸ" << endl;
		cout << "2. �ֹ���ǰ��ȸ" << endl;
		cout << "3. �ŷ�ó��Ȳ" << endl;
		cout << "4. �����޴�" << endl;
		cout << "==================================" << endl;
		cout << endl;
		cout << "� �׸��� �����Ͻðڽ��ϱ�?" << endl;
		cin >> selectNum;

		switch (selectNum)
		{
		case 1:
			searchSales();
			break;
		case 2:
			searchOrderItem();
			break;
		case 3:
			searchMarket();
			break;
		case 4:
			return;
		default:
			cout << "������ �ٽ� ���ּ���." << endl;
			break;
		}
	} while (selectNum != 4);
}

void ProductManage::changePW()
{
	string CheckPassWord;
	char selectChoose;
	system("cls");
	cout << "========== ��ȣ���� ==========" << endl;
	cout << "���� ��ȣ�� �Է��ϼ���." << endl;
	while (1) {

		cin >> CheckPassWord;

		if (passWord != CheckPassWord)
		{
			cout << "�ٽ� ��ȣ�� �Է��ϼ���." << endl;
		}
		else break;
	}

	while (1) {
		cout << "�����Ͻ� ��ȣ�� �Է��ϼ���." << endl;
		cin >> CheckPassWord;
		cout << "���� ��ȣ Ȯ�� : (��: 1/Y, �ƴϿ�: 0/N) " << CheckPassWord << endl;
		cin >> selectChoose;
		if (selectChoose == '1' || selectChoose == 'Y' || selectChoose == 'y')
			break;
	}
	passWord = CheckPassWord;
	cout << "��ȣ�� ����Ǿ����ϴ�." << endl;
	system("pause");
}

void ProductManage::searchSales()
{
	int totalSales=0;
	system("cls");
	cout << "========== ������Ȳ��ȸ ==========" << endl;
	for (int i = 1; i < 6; i++)
	{
		if (storageQty[i]>0)
			cout << i << "." << saMenu[i] << storageQty[i] << "��" << "\t" << storageQty[i]*saCost[i] << endl;
		totalSales += storageQty[i] * saCost[i];
	}
	cout << "��ü����      " << totalSales << endl;
	system("pause");
}

void ProductManage::searchOrderItem()
{
	system("cls");
	int check = 0;
	cout << "========== �ֹ���ǰ��ȸ ==========" << endl;
	for (int i = 1; i < 6; i++)
	{
		if (saManageStock[i] < 5)
		{
			cout << i << "." << saMenu[i] << "	" << saManageStock[i] << "��" << endl;
			check = 1;
		}
	}
	// ���� ��� ���� ���
	if (check==0)
		cout << "�̸� �ֹ��� ��ǰ�� �����ϴ�." << endl;
	system("pause");
}

void ProductManage::searchMarket()
{
	int selectNum;
	do {
		system("cls");
		cout << "========== �ŷ�ó��Ȳ ==========" << endl;
		cout << "1. �ŷ�ǰ�� ��Ȳ��ȸ" << endl;
		cout << "2. �ŷ�ǰ�� �԰� ��Ȳ��ȸ" << endl;
		cout << "3. �ŷ� �ܰ� ����" << endl;
		cout << "4. �����޴�" << endl;
		cout << "================================" << endl;
		cout << "���Ͻô� �׸��� �������ּ���" << endl;
		cin >> selectNum;

		switch (selectNum)
		{
		case 1:
			searchSalesItems();
			break;
		case 2:
			salesItemsInput();
			break;
		case 3:
			changeSalesCost();
			break;
		case 4:
			return;
		default:
			cout << "�ٽ� �׸��� �������ּ���." << endl;
			break;
		}

	} while (selectNum != 4);
}

void ProductManage::searchSalesItems()
{
	system("cls");
	cout << "========== �ŷ�ǰ�� ��Ȳ��ȸ ==========" << endl;
	for (int i = 1; i < 6; i++)
	{
		cout << i << "." << saMenu[i] << "	" << " �ǸŴܰ� : " << saCost[i] << "��	" << "�ŷ��ܰ� : " << salesCost[i] << "��" <<endl;
	}
	cout << "=======================================" << endl;
	system("pause");
}

void ProductManage::salesItemsInput()
{
	int check = 0;
	int totalPayCost=0;
	system("cls");
	cout << "========== �ŷ�ǰ�� �԰� ��Ȳ��ȸ ==========" << endl;
	for (int i = 1; i < 6; i++)
	{
		if (inputQty[i] > 0) 
		{
			cout << i << "." << saMenu[i] << "	" << inputQty[i] << "��	" << "���� �ݾ� : " << inputQty[i] * salesCost[i] << "��" << endl;
			totalPayCost += inputQty[i] * salesCost[i];
			check = 1;
		}
		
	}
	if (check == 0) cout << "�԰�� ǰ���� �����ϴ�." << endl;
	if (check == 1) cout << "�� �ݾ� : " << totalPayCost << "��" << endl;
	cout << "===========================================" << endl;
	system("pause");
}

void ProductManage::changeSalesCost()
{
	int selectProcut;
	int changeMoney;
	int changeMoney1;
	char selectChoose;
	system("cls");
	cout << "========== �ŷ��ܰ� ���� ==========" << endl;
	cout << "�ŷ� �ܰ��� ������ ��ǰ ��ȣ�� �����ϼ���." << endl;
	cin >> selectProcut;

	while (1) {
		cout << "������ �ŷ��ܰ��� �Է��ϼ���." << endl;
		cin >> changeMoney;
		cout << "������ �ǸŴܰ��� �Է��ϼ���." << endl;
		cin >> changeMoney1;
		cout << "������ �ŷ� / �Ǹ� �ܰ� Ȯ�� : (��: 1/Y, �ƴϿ�: 0/N) " << changeMoney << "��	" << changeMoney1 << "��" << endl;;
		cin >> selectChoose;
		if (selectChoose == '1' || selectChoose == 'Y' || selectChoose == 'y')
			break;
	}
	salesCost[selectProcut] = changeMoney;
	saCost[selectProcut] = changeMoney1;
	cout << "�ŷ� / �Ǹ� �ܰ��� ����Ǿ����ϴ�." << endl;

}



int main() {
	ProductManage pm;
	pm.mainMenu();
	return 0;
}