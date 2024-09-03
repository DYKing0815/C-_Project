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
	int saCost[6] = {0}; // 판매 단가
	int saQty[6] = {0}; // 아이템 수량 선택
	int saItemTotalCost[6] = {0};
	int saManageStock[6] = { 0}; // 재고 수량
	int totalCost = 0;
	int money = 0; // 받은 금액
	int totalMoney = 0; // 받은 금액 누적
	string passWord="";
	int storageQty[6] = { 0 };
	int salesCost[6] = { 0 }; // 거래 단가
	int inputQty[6] = { 0 };  // 입고 수량만 누적
};

ProductManage::ProductManage()
{
	ifstream fin;
	// 상품명
	fin.open("itemName.txt");

	for (int i = 1; i < 6; i++)
	{
		fin >> saMenu[i];
	}
	fin.close();

	//수량
	fin.open("itemQty.txt");

	for (int i = 1; i < 6; i++)
	{
		fin >> saManageStock[i];
	}
	fin.close();

	// 판매 단가
	fin.open("itemCost.txt");
	for (int i = 1; i < 6; i++)
	{
		fin >> saCost[i];
	}
	fin.close();

	//거래 단가
	fin.open("salesCost.txt");
	for (int i = 1; i < 6; i++)
	{
		fin >> salesCost[i];
	}
	fin.close();

	//관리자 암호
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
		cout << "========== 메인 메뉴 ==========" << endl;
		cout << "1. 상품판매" << endl;
		cout << "2. 재고관리" << endl;
		cout << "3. 종료" << endl;
		cout << "4. 관리자 모드" << endl;
		cout << "===============================" << endl;
		cout << endl;
		cout << "어떤 메뉴를 선택하시겠습니까?" << endl;
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
				cout << "관리자모드 암호를 입력하세요." << endl;
				cout << "암호 : ";
				cin >> CheckPassWord;
				if (passWord != CheckPassWord)
				{
					cout << "잘못된 암호입니다." << endl;
				}
				else break;
			}
			ManageMode();

			break;
		default:
			cout << "메뉴를 다시 선택해주세요" << endl;
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
		cout << "더 구매하시겠습니까? (예: 1/Y, 아니오: 0/N)";
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
	cout << "품목" << "	" << "수량" << "	" << "금액" << endl;
	for (int i = 1; i < 6; i++)
	{
		if (saQty[i] > 0)
			cout << saMenu[i] << "	" << saQty[i] << "	" << saItemTotalCost[i] << "원" << endl;
	}
	while (1)
	{
		cout << "취소 하시겠습니까? (예: 1/Y, 아니오: 0/N)" << endl;
		cin >> selectChoose;
		if (selectChoose == '0' || selectChoose == 'N' || selectChoose == 'n')
			break;
		cout << "취소하실 상품 번호를 입력해주세요." << endl;
		cin >> selectProduct;
		cout << "차감 수량을 입력해주세요." << endl;
		cin >> count;
		//수량에서 빼고
		saQty[selectProduct] -= count;
		//재고에서 더하고
		saManageStock[selectProduct] += count;
		//누적재고 
		storageQty[selectProduct] -= count;
		//금액 변경
		saItemTotalCost[selectProduct] = saQty[selectProduct] * saCost[selectProduct];



		cout << "더 변경 하시겠습니까? (예: 1/Y, 아니오: 0/N)" << endl;
		cin >> selectChoose;
		if (selectChoose == '0' || selectChoose == 'N' || selectChoose == 'n')
			break;
	}

	


}

void ProductManage::DisplayMenu()
{
	system("cls");
	cout << "========== 상품 메뉴 ==========" << endl;
	for (int i = 1; i < 6; i++)
	{
		cout << i << ". " << saMenu[i] << "	" << saCost[i] << "원	" << saManageStock[i] <<"개" << endl;
	}
	cout << "===============================" << endl;
	system("pause");
}

void ProductManage::CalProduct() 
{
	int count;
	int selectProduct;
	cout << "어떤 상품을 구매하시겠습니까?";
	cin >> selectProduct;
	cout << endl;
	cout << saMenu[selectProduct] << "를 선택하셨습니다." << endl;
	cout << "단가는" << saCost[selectProduct] << "입니다.";
	cout << endl;


	do {
		cout << "몇개를 구매하시겠습니까?";
		cin >> count;
		if (saManageStock[selectProduct] < count)
		{
			cout << "재고 수량 초과";
		}

	} while (saManageStock[selectProduct] < count);

	// 아임템별 구매 수량 누적
	saQty[selectProduct]+= count;
	// 상품별 누적 판매 수량
	storageQty[selectProduct] += count;

	saManageStock[selectProduct] -= count;

	saItemTotalCost[selectProduct] = saCost[selectProduct] * saQty[selectProduct];
	cout << "구매하신 금액은"<< saItemTotalCost[selectProduct] <<"원 입니다." << endl;


}

void ProductManage::CalMoney() //결제 금액 계산
{

	for (int i = 1; i < 6; i++)
	{
		totalCost += saItemTotalCost[i];
	}

	
	cout << "구매하신 총 금액은" << totalCost << "원 입니다." << endl; // 10

	while(1)
	{
		// 적게 낸 결제 금액 반영 안됨
		cout << "결제금액을 입금해주시기 바랍니다." << endl;
		cout << "결제금액 : ";
		cin >> money; // 5+1
		cout << endl;
		totalMoney += money; // 받은 돈 업데이트


		if (totalMoney < totalCost)
		{
			cout << "결제금액에서 " << totalCost - totalMoney << " 원이 부족합니다." << endl; // 5 만 다시 내면 됨
		}

		else break;
	}

}

void ProductManage::Displaybill() // 영수증 display
{
	system("cls");
	cout << "========== 영수증 ==========" << endl;
	cout << "품목" << "	" << "수량" << "	" << "금액" << endl;
	for (int i = 1; i < 6; i++)
	{
		if (saQty[i] > 0)
			cout <<  saMenu[i]<< "	"<< saQty[i] << "	" << saItemTotalCost[i]<<"원" << endl;
	}
	cout << "============================" << endl;
	cout << "총구매금액		" << totalCost << "원" << endl;
	cout << "받은금액	" << totalMoney << "원" << endl;
	cout << "거스름돈	" << totalMoney- totalCost << "원" << endl;
	
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
		cout << "========== 재고관리 ==========" << endl;
		cout << "1. 재고조회" << endl;
		cout << "2. 상품입고" << endl;
		cout << "3. 상품반품" << endl;
		cout << "4. 이전메뉴" << endl;
		cout << "===============================" << endl;
		cout << endl;
		cout << "어떤 업무를 선택하시겠습니까?" << endl;
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
			cout << "업무를 다시 선택해주세요" << endl;
			break;
		}
	} while (selectNum!=4);
	
}

void ProductManage::End()
{
	// 상품명
	ofstream fout;
	fout.open("itemName.txt");

	for (int i = 1; i < 6; i++)
	{
		fout << saMenu[i] << endl;
	}
	fout.close();

	// 수량
	fout.open("itemQty.txt");

	for (int i = 1; i < 6; i++)
	{
		fout << saManageStock[i] << endl;
	}
	fout.close();

	//판매단가
	fout.open("itemCost.txt");
	for (int i = 1; i < 6; i++)
	{
		fout << saCost[i] << endl;
	}
	fout.close();

	//거래단가
	fout.open("salesCost.txt");
	for (int i = 1; i < 6; i++)
	{
		fout << salesCost[i] << endl;
	}
	fout.close();

	//관리자 암호
	fout.open("password.txt");
	fout << passWord << endl;
	fout.close();

	cout << "========== 종료 ==========" << endl;

}

void ProductManage::ManageMode()
{
	// 메뉴 받는 변수
	int selectNum;
	do {
		system("cls");
		cout << "========== 관리자모드 ==========" << endl;
		cout << "1. 상품조회" << endl;
		cout << "2. 상품변경" << endl;
		cout << "3. 단가변경" << endl;
		cout << "4. 매출실적현황" << endl;
		cout << "5. 이전메뉴" << endl;
		cout << "6. 암호변경" << endl;
		cout << "===============================" << endl;
		cout << endl;
		cout << "어떤 모드를 선택하시겠습니까?" << endl;
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
			cout << "선택을 다시 해주세요." << endl;
			break;
		}
	} while (selectNum != 5);
}

void ProductManage::searchStock() // 재고 출력
{
	system("cls");
	cout << "========== 재고조회 ==========" << endl;
	for (int i = 1; i < 6; i++)
	{
		cout << i << ". " << saMenu[i] << "	" << saManageStock[i] << "개" << endl;
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
		cout << "========== 상품입고 ==========" << endl;
		while (1) {
			// 어떤 상품 입고 할지
			cout << "입고하실 상품 번호를 선택하세요. " << endl;
			cin >> selectProduct;
			// 상품 개수 증가
			cout << "수량을 입력하세요." << endl;
			cin >> count;
			saManageStock[selectProduct] += count;
			// 입고 수량만 누적
			inputQty[selectProduct] += count;

			// 더 할 것인지
			cout << "더 입고하시겠습니까? (예: 1/Y, 아니오: 0/N)";
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
	cout << "========== 상품반품 ==========" << endl;

	while (1) {
		cout << "반품하실 상품 번호를 선택하세요." << endl;
		cin >> selectProduct;

		while (1) {
			cout << "수량을 입력하세요." << endl;
			cin >> count;
			if (count > saManageStock[selectProduct])
			{
				cout << "재고수량보다 반품 수량이 더 많습니다." << endl;
			}
			else break;
		}

		saManageStock[selectProduct] -= count;
		cout << "더 반품하시겠습니까? (예: 1/Y, 아니오: 0/N)";
		cin >> selectChoose;
		if (selectChoose == '0' || selectChoose == 'N' || selectChoose == 'n')
			break;
	}
}

// 상품 조회
void ProductManage::searchItem()
{
	system("cls");
	cout << "========== 상품조회 ==========" << endl;
	for (int i = 1; i < 6; i++)
		cout << i << "." << saMenu[i] << " " << saCost[i] << "원" << endl;
	cout << "==============================" << endl;
	system("pause");
}

void ProductManage::changeItem()
{
	int selectProduct;
	string newItemName;
	char selectChoose;
	system("cls");
	cout << "========== 상품변경 ==========" << endl;
	cout << "변경하실 상품의 번호를 입력하세요." << endl;
	cin >> selectProduct;
	
	while (1) {
		cout << "변경할 상품명을 입력하세요." << endl;
		cin >> newItemName;
		// 다시 보여줌 
		cout << "변경할 상품명 확인 : (예: 1/Y, 아니오: 0/N) " << newItemName << endl;
		cin >> selectChoose;
		if (selectChoose == '1' || selectChoose == 'Y' || selectChoose == 'y')
			break;
	}

	saMenu[selectProduct] = newItemName;
	cout << "상품명이 변경되었습니다." << endl;

}

void ProductManage::changeCost()
{
	int selectProduct;
	int changeMoney;
	char selectChoose;
	system("cls");
	cout << "========== 단가변경 ==========" << endl;
	cout << "변경하실 상품의 번호를 입력하세요." << endl;
	cin >> selectProduct;

	while (1) {
		cout << "변경할 단가를 입력하세요." << endl;
		cin >> changeMoney;
		cout << "변경할 단가 확인 : (예: 1/Y, 아니오: 0/N) " << changeMoney << "원" << endl;
		cin >> selectChoose;
		if (selectChoose == '1' || selectChoose == 'Y' || selectChoose == 'y')
			break;
	}

	saCost[selectProduct] = changeMoney;
	cout << "상품 단가가 변경되었습니다." << endl;
}

void ProductManage::CheckSales()
{
	int selectNum;
	do {
		system("cls");
		cout << "========== 매출실적현황 ==========" << endl;
		cout << "1. 매출현황조회" << endl;
		cout << "2. 주문상품조회" << endl;
		cout << "3. 거래처현황" << endl;
		cout << "4. 이전메뉴" << endl;
		cout << "==================================" << endl;
		cout << endl;
		cout << "어떤 항목을 선택하시겠습니까?" << endl;
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
			cout << "선택을 다시 해주세요." << endl;
			break;
		}
	} while (selectNum != 4);
}

void ProductManage::changePW()
{
	string CheckPassWord;
	char selectChoose;
	system("cls");
	cout << "========== 암호변경 ==========" << endl;
	cout << "기존 암호를 입력하세요." << endl;
	while (1) {

		cin >> CheckPassWord;

		if (passWord != CheckPassWord)
		{
			cout << "다시 암호를 입력하세요." << endl;
		}
		else break;
	}

	while (1) {
		cout << "변경하실 암호를 입력하세요." << endl;
		cin >> CheckPassWord;
		cout << "변경 암호 확인 : (예: 1/Y, 아니오: 0/N) " << CheckPassWord << endl;
		cin >> selectChoose;
		if (selectChoose == '1' || selectChoose == 'Y' || selectChoose == 'y')
			break;
	}
	passWord = CheckPassWord;
	cout << "암호가 변경되었습니다." << endl;
	system("pause");
}

void ProductManage::searchSales()
{
	int totalSales=0;
	system("cls");
	cout << "========== 매출현황조회 ==========" << endl;
	for (int i = 1; i < 6; i++)
	{
		if (storageQty[i]>0)
			cout << i << "." << saMenu[i] << storageQty[i] << "개" << "\t" << storageQty[i]*saCost[i] << endl;
		totalSales += storageQty[i] * saCost[i];
	}
	cout << "전체매출      " << totalSales << endl;
	system("pause");
}

void ProductManage::searchOrderItem()
{
	system("cls");
	int check = 0;
	cout << "========== 주문상품조회 ==========" << endl;
	for (int i = 1; i < 6; i++)
	{
		if (saManageStock[i] < 5)
		{
			cout << i << "." << saMenu[i] << "	" << saManageStock[i] << "개" << endl;
			check = 1;
		}
	}
	// 위에 출력 안한 경우
	if (check==0)
		cout << "미리 주문할 상품이 없습니다." << endl;
	system("pause");
}

void ProductManage::searchMarket()
{
	int selectNum;
	do {
		system("cls");
		cout << "========== 거래처현황 ==========" << endl;
		cout << "1. 거래품목 현황조회" << endl;
		cout << "2. 거래품목 입고 현황조회" << endl;
		cout << "3. 거래 단가 변경" << endl;
		cout << "4. 이전메뉴" << endl;
		cout << "================================" << endl;
		cout << "원하시는 항목을 선택해주세요" << endl;
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
			cout << "다시 항목을 선택해주세요." << endl;
			break;
		}

	} while (selectNum != 4);
}

void ProductManage::searchSalesItems()
{
	system("cls");
	cout << "========== 거래품목 현황조회 ==========" << endl;
	for (int i = 1; i < 6; i++)
	{
		cout << i << "." << saMenu[i] << "	" << " 판매단가 : " << saCost[i] << "원	" << "거래단가 : " << salesCost[i] << "원" <<endl;
	}
	cout << "=======================================" << endl;
	system("pause");
}

void ProductManage::salesItemsInput()
{
	int check = 0;
	int totalPayCost=0;
	system("cls");
	cout << "========== 거래품목 입고 현황조회 ==========" << endl;
	for (int i = 1; i < 6; i++)
	{
		if (inputQty[i] > 0) 
		{
			cout << i << "." << saMenu[i] << "	" << inputQty[i] << "개	" << "결제 금액 : " << inputQty[i] * salesCost[i] << "원" << endl;
			totalPayCost += inputQty[i] * salesCost[i];
			check = 1;
		}
		
	}
	if (check == 0) cout << "입고된 품목이 없습니다." << endl;
	if (check == 1) cout << "총 금액 : " << totalPayCost << "원" << endl;
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
	cout << "========== 거래단가 변경 ==========" << endl;
	cout << "거래 단가를 변경할 상품 번호를 선택하세요." << endl;
	cin >> selectProcut;

	while (1) {
		cout << "변경할 거래단가를 입력하세요." << endl;
		cin >> changeMoney;
		cout << "변경할 판매단가를 입력하세요." << endl;
		cin >> changeMoney1;
		cout << "변경할 거래 / 판매 단가 확인 : (예: 1/Y, 아니오: 0/N) " << changeMoney << "원	" << changeMoney1 << "원" << endl;;
		cin >> selectChoose;
		if (selectChoose == '1' || selectChoose == 'Y' || selectChoose == 'y')
			break;
	}
	salesCost[selectProcut] = changeMoney;
	saCost[selectProcut] = changeMoney1;
	cout << "거래 / 판매 단가가 변경되었습니다." << endl;

}



int main() {
	ProductManage pm;
	pm.mainMenu();
	return 0;
}