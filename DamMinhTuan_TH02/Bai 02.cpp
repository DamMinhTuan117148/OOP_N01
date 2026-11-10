#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);

    int lay_ma_xe() const;
    string lay_loai_xe() const;
    double tinh_phi() const;
    void hien_thi() const;
};

phuong_tien::phuong_tien() : ma_xe(0), loai_xe(""), gio_vao(0), tg_do(0) {}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg)
    : ma_xe(ma), loai_xe(loai), gio_vao(gio), tg_do(tg) {}

int phuong_tien::lay_ma_xe() const { return ma_xe; }
string phuong_tien::lay_loai_xe() const { return loai_xe; }

double phuong_tien::tinh_phi() const {
    double gia = (loai_xe == "Car") ? 6.0 : (loai_xe == "Motorcycle") ? 4.0 : 2.0;
    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
    double tong = 0;
    for (int h = 0; h < tg_do; ++h) {
        if (h < 2) tong += gia * (cao_diem ? 1.30 : 0.95);
        else       tong += gia * 0.90;
    }
    return tong;
}

void phuong_tien::hien_thi() const {
    cout << "  ID: " << ma_xe << " | " << loai_xe
         << " | " << gio_vao << "h | " << tg_do << "h"
         << " | Phi: $" << fixed << setprecision(2) << tinh_phi() << "\n";
}

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    phuong_tien pt1, pt2, pt3;   // sau này dùng mảng
    bool co1, co2, co3;
    
    static const int pt_lonhat = 3;// suc chua toi da va them mang tinh tuc la arr
    phuong_tien pt[3];
    int so_pt_ht = 0;

public:
    bai_xe();
    bai_xe(int ma, char kt);
    int getpt_lonhat(){
    	return pt_lonhat;
	}
	bool da_day() const;
	phuong_tien get_pt_thu(int index) const{
		return pt[index];
	}
    int lay_ma() const;
    bool them(phuong_tien v);
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;
    void hien_thi() const;
    bool co_loai(string loai, int& dem, double& tong) const;
};

bai_xe::bai_xe() : ma_bai(0), kich_thuoc('S'), co1(false), co2(false), co3(false) {}

bai_xe::bai_xe(int ma, char kt) : ma_bai(ma), kich_thuoc(kt), co1(false), co2(false), co3(false) {}

int bai_xe::lay_ma() const { return ma_bai; }

bool bai_xe::da_day ()const{
	int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
	if(so_pt_ht == cap){
		return true;
	}
	else{
		return false;
	}
}


bool bai_xe::them(phuong_tien v) {
    int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
    // Kiem tra tung dieu kien nhung ma mang chi can kiem tra ro do la 1 xe
    bool flag = false;
    if (cap >= 1 && !co1) { pt1 = v; co1 = true;pt[so_pt_ht] = v;flag = true ; return true; }
    if (cap >= 2 && !co2) { pt2 = v; co2 = true;pt[so_pt_ht] = v ;flag = true ;return true; }
    if (cap >= 3 && !co3) { pt3 = v; co3 = true;pt[so_pt_ht] = v;flag = true ; return true; }
    
    if(flag == true){
    	so_pt_ht ++;
	}
    
    return false;
}

bool bai_xe::xoa(int ma_xe) {
	bool flag = false;
    if (co1 && pt1.lay_ma_xe() == ma_xe) {
        if (co2) {
            pt[0] = pt2; pt[1] = phuong_tien();flag = true;
            if (co3){
            	pt[1] = pt3;pt[2] = phuong_tien() ; co3 = false;flag = true; // 0,1,2   set phan tu thu 3 thanh rong
			}
            else {
            	co2 = false; 	
			}
        } else co1 = false;flag = true;// khong co de don
        if(flag == true){
        	so_pt_ht --;
		}
        return true;
    }
    if (co2 && pt2.lay_ma_xe() == ma_xe) {
        if (co3){
        	 pt[1] = pt3;pt[2]= phuong_tien();co3 = false; flag = true;
		}
        else{
        	co2 = false;
        	flag = true;
		} 
		if(flag == true){
        	so_pt_ht --;
		}
        return true;
    }
    if (co3 && pt3.lay_ma_xe() == ma_xe) {
        co3 = false;
        flag = true;
        if(flag == true){
        	so_pt_ht --;
		}
        return true;
    }
    return false;
}

bool bai_xe::chua(int ma_xe) const {
    if (co1 && pt1.lay_ma_xe() == ma_xe) {
    	cout<< "Index of xe" << 0;
		return true;
	}
    if (co2 && pt2.lay_ma_xe() == ma_xe){
    	cout<< "Index of xe" << 1;
    	return true;
	} 
    if (co3 && pt3.lay_ma_xe() == ma_xe) {
    	cout<< "Index of xe" << 2;
    	return true;
	}
	cout<< "Index of xe" << -1;
    return false;
}

void bai_xe::hien_thi() const {
    int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "<< so_pt_ht << "/" << cap << " xe\n";
    for(int i = 0 ; i < so_pt_ht;i++){
		pt[i].hien_thi();
	}
}

bool bai_xe::co_loai(string loai, int& dem, double& tong) const {
    dem = 0; tong = 0;
    if (co1 && pt1.lay_loai_xe() == loai) { ++dem; tong += pt1.tinh_phi(); }
    if (co2 && pt2.lay_loai_xe() == loai) { ++dem; tong += pt2.tinh_phi(); }
    if (co3 && pt3.lay_loai_xe() == loai) { ++dem; tong += pt3.tinh_phi(); }
    return dem > 0;
}

class SystemInterface {
private:
    bai_xe bai1, bai2, bai3;   // sau này dùng mảng
    bool co1, co2, co3;
    static const int bai_lonhat = 10;
    bai_xe bai[bai_lonhat];
    int soBai = 0;

public:
	bool coTonTaiIDBai(int pID) const{
		for(int i = 0 ;i < bai_lonhat;i++){
			if(bai[i].lay_ma() == pID){
				return true;
			}
		}
		
	}
	bool coTonTaiIDXe(int vID) const{
		bool flag =false;
		for(int i = 0 ; i < bai_lonhat;i++){
			if(bai[i].chua(vID)){
				return true;
			}
		}
	}
	int taoIDNgauNhien(){
		int newID = rand() % 9999 + 1000;
		return newID;
	}
    SystemInterface();
    void runMenu();
};

SystemInterface::SystemInterface() : co1(false), co2(false), co3(false) {}

void SystemInterface::runMenu() {
    int chon;
    while (true) {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        cout << "Chon: ";
        cin >> chon;
//các e chuyển sang lệnh switch cho thầy
        if (chon == 1) {
            int ma; char kt;
            if(bai_lonhat >= 10){
            	cout<< " Bai da day ";
			}
			else{
			cout << "Ma bai: "; cin >> ma;
            cout << "Kich thuoc (S/M/L): "; cin >> kt;
            if(coTonTaiIDBai(ma)){
            	int newID;
            	do{
            		newID = taoIDNgauNhien();
				}while(coTonTaiIDBai(newID));// neu == false thi no se huy
			}
			if (!co1)      { bai1 = bai_xe(ma, kt); co1 = true; }
            else if (!co2) { bai2 = bai_xe(ma, kt); co2 = true; }
            else           { bai3 = bai_xe(ma, kt); co3 = true; }
            cout << "Da tao bai " << ma << "\n";		
			}
        }
        else if (chon == 2) {
            int ma, gio, tg; string loai;
            cout << "Ma xe: "; cin >> ma;
            cout << "Loai (Car/Motorcycle/Bicycle): "; cin >> loai;
            cout << "Gio vao (0-23): "; cin >> gio;
            cout << "Thoi luong (1-23): "; cin >> tg;
            if(coTonTaiIDXe(ma)){
            	int newID;
            	do{
            		newID = taoIDNgauNhien();
				}while(coTonTaiIDXe(newID));// neu == false thi no se huy
			}
            if(bai_lonhat >= 10){
            	cout<< " Bai da day ";
			}
			else{
			phuong_tien v(ma, loai, gio, tg);
            bool ok = false;
            if (co1 && !ok){ok = bai1.them(v);}
            if (co2 && !ok) ok = bai2.them(v);
            if (co3 && !ok) ok = bai3.them(v);
            if (ok) cout << "Da them xe " << ma << " | Phi: $" << fixed << setprecision(2) << v.tinh_phi() << "\n";
			}	
		} 
		//Dam Minh Tuan 117148
        else if (chon == 3) {
            int ma;
            cout << "Ma bai can xoa: "; cin >> ma;
            int idSearch = -1;
            for(int i = 0 ; i < bai_lonhat;i++){
            	if(bai[i].lay_ma() == ma){
            		idSearch = i;
            		break;
				}
			}
			for(int i = idSearch; i < bai_lonhat;i++){
				bai[i] = bai[i+ 1]; // mat mot xe thi chung se don tu trai sang phai tu cai xe do 
			}
        }
        else if (chon == 4) {
            int ma;
            cout << "Ma xe can lay ra: "; cin >> ma;
            int idSearch = -1;
            for(int i = 0 ; i < bai_lonhat;i++){
            	if(bai[i].chua(ma)){
            		idSearch = i;
            		bai[i].xoa(ma);
            		break;
				}
			}
			for(int i = idSearch; i < bai_lonhat;i++){
				bai[i] = bai[i+ 1]; // mat mot xe thi chung se don tu trai sang phai tu cai xe do 
			}
        }
        else if (chon == 5) {
            for(int i = 0; i < bai_lonhat;i++){
            	bai[i].hien_thi();
			}
        }
        else if (chon == 6) {
            int ma;
            cout << "Ma bai: "; cin >> ma;
            for(int i = 0 ; i < bai_lonhat;i++){
            		if(bai[i].lay_ma() == ma ){
            			bai[i].hien_thi();
					}
				}
			}
        
        else if (chon == 7) {
            string loai;
            cout << "Loai xe: "; cin >> loai;
            for(int i = 0 ; i < bai_lonhat;i++){
            		for(int j = 0 ; j < bai[i].getpt_lonhat();j++){
            			if(bai[i].get_pt_thu(j).lay_loai_xe() == loai ){
            			bai[i].get_pt_thu(j).hien_thi();
					}
				}
			}
        }
        else if (chon == 8) {
		string loai_arr[3] = {"Car", "Motorcycle", "Bicycle"};
    	for(int t = 0; t < 3; t++) {
        int count = 0; 
        double sum = 0;
        for(int i = 0; i < soBai; i++) {
            int d = 0; double s = 0;
            if (bai[i].co_loai(loai_arr[t], d, s)) {
                count += d;
                sum += s;
            }
        }   
        if (count == 0) cout << "khong co xe\n";
        else cout << dem << " xe | TB: $" << fixed << setprecision(2) << tong / dem << "\n";
    }
        
        else if (chon == 9) break;
}
}

int main() {
    SystemInterface sys;
    sys.runMenu();
    return 0;
}

