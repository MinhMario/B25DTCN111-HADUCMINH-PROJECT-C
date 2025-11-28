#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<stdlib.h>
typedef struct{
	char transId[20];
	char productId[10];
	char type[5];
	char date[15];
}Transaction;
typedef struct{
	char productId[10];
	char name[50];
	char unit[10];
	int qty;//So luong ton kho
	int status;
	Transaction trans;
}Product;
Product products[100] = {
    {"1", "Sua tuoi ", "Hop", 20, 1, {}},
    {"2", "Nuoc uong", "Chai", 50, 1, {}},
    {"3", "Banh keo ", "GOi", 30, 1, {}},
    {"4", "Do dung hoc tap ", "CAi", 40, 1, {}},
    {"5", "Ly thuy tinh", "CAi", 25, 1, {}}
};
int length = 5; 
Transaction allTrans[100];
int totalTransactions=0;

void mainMenu() {
    system("cls");
    printf("\n");
    printf("   -------------------------------------\n");
    printf("        MENU CHINH-QUAN LY BAN HANG     \n");
    printf("   -------------------------------------\n");
    printf("\n");
    printf("     1. Quan ly hang hoa \n");
    printf("     2. Quan ly giao dich\n");
    printf("     3. Xem danh sach hoa don\n");

    printf("   -------------------------------------\n");
    printf("   Nhap lua chon: ");
}
void transmenu(){
	printf("    1. Giao dich xuat / nhap hang hoa\n");
    printf("    2. Lich su xuat / nhap hang\n");
    printf("     3.Thoat                    \n");
}
void productmenu(){
    printf("============================================================\n");
    printf("         CHUONG TRINH QUAN LY KHO HANG HOA\n");
    printf("============================================================\n\n");
    
    printf("    1. Them ma hang moi\n");
    printf("    2. Cap nhat thong tin san pham\n");
    printf("    3. Quan ly trang thai (Khoa / Xoa)\n");
    printf("    4. Tra cuu - Tim kiem san pham\n");
    printf("    5. Danh sach san pham (Phan trang)\n");
    printf("    6. Sap xep danh sach\n");
    printf("    0. Thoat chuong trinh\n");
    printf("============================================================\n");
    printf("   Vui long chon chuc nang (1 - 0): ");
}
int getNumber(int min, int max){
	int num;
	char buffer[100];
	while (1) {
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strcspn(buffer, "\n")] = '\0';
		if(strlen(buffer) == 0) {
			printf("Khong duoc de trong! Vui long nhap!\n");
			continue;
		}
		int isValid = 1;
		for(int i = 0; i < strlen(buffer); i++){
			if(!isdigit(buffer[i])){
				isValid = 0;
				break;
			}
		}
		if(!isValid){
			printf("Yeu cau phai nhap lai mot so nguyen!\n");
			continue;
		}
		num = atoi(buffer);
		if (num < min || num > max) {
			printf("Gia tri phai trong khoang %d -> %d\n", min, max);
			continue;
		}
		return num;
	}
}
void getString(char* string,int size){
	do{
		fgets(string,size,stdin);
		string[strcspn(string,"\n")]=0;
		if(strlen(string)==0) {
		printf("Khong duoc de trong! Vui long nhap!\n");
	}
	} while (strlen(string)==0);
}

void add(){
    int n;
    do {
        printf("Nhap so luong san pham: ");  
        n=getNumber(0,1000);
    } while (n <= 0);
    for(int i = 0; i < n; i++){
        printf("\n--- San pham thu %d ---\n", i + 1);
        int isDuplicate;
        do{
            isDuplicate = 0;
            printf("Nhap ma san pham: ");
            getString(products[length].productId,sizeof(products[length].productId));

            for(int j = 0; j < length; j++){
                if(strcmp(products[j].productId, products[length].productId) == 0){
                    isDuplicate = 1;
                    printf("Ma san pham da ton tai!\n");
                    break;
                }
            }
        } while(isDuplicate);
        
            printf("Nhap ten san pham: ");
            getString(products[length].name,sizeof(products[length].name));

            printf("Nhap don vi san pham: ");
            getString(products[length].unit,sizeof(products[length].unit));
        

        do{
            printf("Nhap so luong ton kho: ");
            products[length].qty=getNumber(0,100);
        } while(products[length].qty < 0);
        
        products[length].status = 1;
        length++;
        printf("Them san pham thanh cong!\n");
    }
}
void update(){
    if(length == 0){
        printf("\nDanh sach san pham trong!\n");
        return;
    }
    char searchId[10];
    printf("Nhap ma san pham can cap nhat: ");
    fgets(searchId, sizeof(searchId), stdin);
    searchId[strcspn(searchId, "\n")] = '\0';
    

    int found = -1;  
    for(int i = 0; i < length; i++){
        if(strcmp(products[i].productId, searchId) == 0){
            found = i;
            break;
        }
    }
    

    if(found == -1){
        printf("Khong tim thay san pham voi ma: %s\n", searchId);
        return;
    }
   system("cls");

    printf("+----------------------------------------------------------------------------+\n");
    printf("                       THONG TIN SAN PHAM HIEN TAI                       \n");
    printf("-------------------------------------------------------------------------\n");
    printf(" Ma san pham  Ten san pham   Don vi tinh   So luong     Trang thai    \n");
    printf("------------+---------------+--------------+--------------+--------------\n");
    

    printf(" %-10s  %-13s  %-12s  %-12d  %-12s \n",
           products[found].productId,
           products[found].name,
           products[found].unit,
           products[found].qty,
           products[found].status == 1 ? "Con su dung" : "Het han");

    printf("+-------------------------------------------------------------------------+\n");
    printf("         NHAP THONG TIN MOI DE CAP NHAT                  \n");
    printf("|------------------------------------------------------------------------\n\n");
    
    
        printf("Nhap ten san pham: ");
        getString(products[found].name,sizeof(products[found].name));
   
        printf("Nhap don vi san pham: ");
        getString(products[found].unit,sizeof(products[found].unit));
    do{
        printf("Nhap so luong ton kho: ");
        
       products[found].qty=getNumber(0,100);
        
    } while(products[found].qty < 0);
    
    printf("\nCap nhat san pham thanh cong!\n");
}
void lock(){
	if(length == 0){
        printf("\nDanh sach san pham trong!\n");
        return;
    }
    printf("Nhap ma san pham can khoa \n");
	char searchid[10];
	fgets(searchid,sizeof(searchid),stdin);
	searchid[strcspn(searchid,"\n")]='\0';
	int found=0;
	for(int i=0;i<length;i++){
		if(strcmp(searchid,products[i].productId)==0){
			found=1;
			products[i].status=0;
			break;
		}
	}
		if(!found){
		printf("Khong tim thay san pham\n");
		return;
	}
	printf("Da khoa san pham !\n");
}

void search(){
	if(length == 0){
        printf("\nDanh sach san pham trong!\n");
        return;
    }
	int choice;
    int found=-1;
	printf("1.Tim kiem theo ma\n");
    printf("2.Tim kiem theo ten\n");
    printf("Lua chon cua ban:");
    
    choice=getNumber(1,2);
   
    switch(choice){
    	case 1:
    printf("Nhap ma san pham de tim kiem");
	char searchid[10];
	do{
		fgets(searchid,sizeof(searchid),stdin);
		searchid[strcspn(searchid,"\n")]='\0';
		if(strlen(searchid)==0){
			printf("Ma san pham khong duoc de trong ");
		}
	}while(strlen(searchid)==0);
	for(int i=0;i<length;i++){
		if(strcmp(searchid,products[i].productId)==0){
			found=i;
 printf("+----------------------------------------------------------------------------+\n");
    printf("                       THONG TIN SAN PHAM HIEN TAI                       \n");
    printf("-------------------------------------------------------------------------\n");
    printf(" Ma san pham   Ten san pham   Don vi tinh   So luong     Trang thai    \n");
    printf("------------+---------------+--------------+--------------+--------------\n");
    

    printf(" %-10s  %-13s  %-12s  %-12d  %-12s \n",
           products[found].productId,
           products[found].name,
           products[found].unit,
           products[found].qty,
           products[found].status == 1 ? "Con su dung" : "Het han");
        break;
		}
	}
	if(found==-1){
		printf("Khong tim thay san pham\n");
	}
	break;
	case 2:
		printf("Nhap vao ten cua san pham\n");
		char name[100];
		getString(name,sizeof(name));
		for(int i=0;i<length;i++){
			if(strcmp(name,products[i].name)==0||strstr(products[i].name,name)!=NULL){
					found=i;
 printf("+----------------------------------------------------------------------------+\n");
    printf("                       THONG TIN SAN PHAM HIEN TAI                       \n");
    printf("-------------------------------------------------------------------------\n");
    printf(" Ma san pham   Ten san pham   Don vi tính   So luong     Trang thai    \n");
    printf("------------+---------------+--------------+--------------+--------------\n");
    

    printf(" %-10s  %-13s  %-12s  %-12d  %-12s \n",
           products[found].productId,
           products[found].name,
           products[found].unit,
           products[found].qty,
           products[found].status == 1 ? "Con su dung" : "Het han");
		}
	}
	if(found==-1){
		printf("Khong tim thay san pham\n");
		}
		break;
			
			default:
				printf("Lua chon khong hop le\n");
		}
}
void sort(){
	if(length == 0){
        printf("\nDanh sach san pham trong!\n");
        return;
    }
    int choice;
    do{
    	printf("1.Sap xep theo so luong\n");
    	printf("2.Sap xep theo ten\n");
    	printf("3.Thoat\n");
		choice=getNumber(1,3);
    switch(choice){
    	case 1:
	for(int i=0;i<length;i++){
		for(int j=i+1;j<length;j++){
			if(products[i].qty>products[j].qty){
				Product temp=products[i];
				products[i]=products[j];
				products[j]=temp;
			}
		}
	}
	printf("Da sap xep theo so luong thanh cong\n");
	break;
	case 2:
		for(int i=0;i<length;i++){
		for(int j=i+1;j<length;j++){
			if(strcmp(products[i].name,products[j].name)>0){
				Product temp=products[i];
				products[i]=products[j];
				products[j]=temp;
			}
		}
	}
	case 3:
		printf("Thoat\n");
	printf("Da sap xep theo ten thanh cong\n!");
	break;
	default:
		printf("Lua chon khong hop le\n");
}
}while(choice!=3);
}
void phanSotrang(){
		if(length == 0){
        printf("\nDanh sach san pham trong!\n");
        return;
    }
	int productsPerPage=5;
	int currentPage=1;
	int choice;
	do{
  	int totalPage = (length + productsPerPage - 1) / productsPerPage;
	int start=(currentPage-1)*productsPerPage;
	int end=start+productsPerPage;
    system("cls");
	printf("Trang %d/%d",currentPage,totalPage);
    printf("+----------------------------------------------------------------------------+\n");
    printf("                       THONG TIN SAN PHAM HIEN TAI                       \n");
    printf("-------------------------------------------------------------------------\n");
    printf(" Ma san pham Ten san pham  Don vi tinh   So luong     Trang thai   \n");
    printf("------------+---------------+--------------+--------------+--------------\n");
    
	for(int i = start; i < end; i++){
    printf(" %-10s  %-13s  %-12s  %-12d  %-12s \n",
           products[i].productId,
           products[i].name,
           products[i].unit,
           products[i].qty,
           products[i].status == 1 ? "Con su dung" : "Het han");
	}
    printf("+-------------------------------------------------------------------------+\n");

   printf("   +------------------------------------------------------------------+\n");
    printf("                 1. Trang truoc     2. Thoat     3. Trang sau          \n");
    printf("   +------------------------------------------------------------------+\n");

    printf("\n   Nhap lua chon: ");
		
		choice=getNumber(1,3);
		switch(choice){
			case 1:
				if(currentPage>1){
				currentPage-=1;
			}
				if(currentPage<1){
					printf("Khong co trang truoc\n");
					continue;
				}
				break;
				case 2:
					printf("Thoat chuong trinh\n");
					break;
				case 3:
					if(currentPage<totalPage){
					currentPage+=1;
				}
					if(currentPage>totalPage){
						printf("Kich thuoc trang da dat toi da\n");
						continue;
					}
					break;
				default:
					printf("Lua chon khong hop le\n");
					}
		}while(choice!=2);
	}

void currenttime(char *date){
    time_t currentTime = time(NULL);
    strcpy(date, ctime(&currentTime));
    date[strcspn(date, "\n")] = '\0';  
}

void transaction(){
	if(length == 0){
        printf("\nDanh sach san pham trong!\n");
        return;
    }
    char newTransId[20];
    int qtyBefore;
    int found=-1;
    char searchId[10];
    printf("Nhap id san pham can giao dich");
	getString(searchId,sizeof(searchId));
    for(int i=0;i<length;i++){
    if(strcmp(searchId,products[i].productId)==0){
    found=i;	
	printf("\nSan pham: %s - %s\n", products[found].productId, products[found].name);
	printf("So luong ton kho hien tai: %d %s\n", products[found].qty, products[found].unit);
	break;
	}
	}
	if(found==-1){
		printf("Khong tim thay san pham!\n");
		return;
	}
	
	if(products[found].status==0){
		printf("San pham khong the giao dich\n");
		return;
	}
	int choice;
	printf("\nChon loai giao dich:\n");
	printf("1. Nhap hang\n");
	printf("2. Xuat hang\n");
	printf("Lua chon: ");
	choice = getNumber(1, 2);
	int amount;
	printf("Chon so luong ban can \n");
	amount=getNumber(0,10000);
		qtyBefore=products[found].qty;
	switch(choice){
		case 1:
			products[found].qty+=amount;
			if(totalTransactions<1000){
				sprintf(newTransId, "TRANS%04d", totalTransactions+1);
				strcpy(allTrans[totalTransactions].transId,newTransId);
				strcpy(allTrans[totalTransactions].productId, products[found].productId);
				strcpy(allTrans[totalTransactions].type, "NHAP");
				currenttime(allTrans[totalTransactions].date);
				totalTransactions++;
			}
				printf("\n=== NHAP HANG THANH CONG ===\n");
			printf("Ma giao dich: %s\n", newTransId);
			printf("So luong truoc: %d\n", qtyBefore);
			printf("So luong nhap: %d\n", amount);
			printf("So luong sau: %d\n", products[found].qty);
			break;
		case 2:
			if(amount>products[found].qty){
				printf("Khong hop le!\n");
				return;
			}
		products[found].qty-=amount;
		
		if(totalTransactions<1000){
			sprintf(newTransId, "TRANS%04d", totalTransactions+1);
				strcpy(allTrans[totalTransactions].transId,newTransId);
				strcpy(allTrans[totalTransactions].productId, products[found].productId);
				strcpy(allTrans[totalTransactions].type, "XUAT");
				currenttime(allTrans[totalTransactions].date);
				totalTransactions++;
			}

				printf("\n=== XUAT HANG THANH CONG ===\n");
			printf("Ma giao dich: %s\n", newTransId);
			printf("So luong truoc: %d\n", qtyBefore);
			printf("So luong nhap: %d\n", amount);
			printf("So luong sau: %d\n", products[found].qty);
			break;
	
		}
	
		}
		

void history(){
	if(length == 0){
        printf("\nDanh sach san pham trong!\n");
        return;
    }
	char productid[10];
    printf("           LICH SU XUAT/NHAP HANG HOA\n");
    printf("============================================================\n\n");
    printf("Nhap ma can xem lich su\n");
    getString(productid,sizeof(productid));
     int productIndex = -1;
     if(totalTransactions==0){
     	printf("Chua co giao dich");
     	return;
	 }
	    for(int i = 0; i < length; i++){
        if(strcmp(products[i].productId, productid) == 0){
            productIndex = i;
            break;
        }
    }
    if(productIndex == -1){
        printf("\n[!] Khong tim thay san pham voi ma: %s\n", productid);
        printf("\nNhan phim bat ky de quay lai...");
        getchar();
        return;
    }

printf("\n%-15s %-15s %-15s %-20s\n", "Ma GD", "Ma SP", "Loai GD", "Thoi gian");
printf("------------------------------------------------------------------------\n");

for(int i = 0; i < totalTransactions; i++){
    if(strcmp(allTrans[i].productId, productid) == 0){
        printf("%-15s %-15s %-15s %-20s\n",
            allTrans[i].transId,
            allTrans[i].productId,
            allTrans[i].type,
            allTrans[i].date);
    }
}
}
    

int main(){
	int choice;
	do{
		mainMenu();
		choice=getNumber(1,3);
		switch(choice){
			case 1:	
			int subchoice;
				do{
				productmenu();
				subchoice=getNumber(0,6);
					switch(subchoice){
				case 1:
				add();
				break;
				case 2:
				update();
				break;	
				case 3:
				lock();
				break;
				case 4:
				search();
				break;
				case 5:
				phanSotrang();
				break;
				case 6:
				sort();
				break;
				case 0:
				printf("Quay lai menu chinh!\n");
				break;
				default:
					printf("Nhap khong hop le!\n");
				}
			}while(subchoice!=0);
		
				break;
			case 2:
				int subchoice_1;
				do{
				transmenu();
            	subchoice_1=getNumber(1,3);
				switch(subchoice_1){
				case 1:
					transaction();
				break;
				case 2:
				history();
				break;
				case 3:
					printf("Quay ve menu chinh!\n");
					break;
				default:
					printf("Lua chon khong hop le!\n");
		}
		}while(subchoice_1!=3);
			break;
			case 3:
				printf("Ket thuc chuong trinh!\n");
				break;
				default:
					printf("Lua chon khong hop le!\n");
	}
	}while(choice!=3);
	return 0;
}
