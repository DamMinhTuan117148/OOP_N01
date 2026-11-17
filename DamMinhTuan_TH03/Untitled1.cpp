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
    int suc_chua; // Khoi tao s m l
    int so_xe_hien_tai;
    phuong_tien** mang_pt;
    
    

public:
    bai_xe();
    bai_xe(int ma, char kt){
    	mang_pt = new phuong_tien * [suc_chua]();
    	for(int i = 0 ;  i < suc_chua;i++){
    		mang_pt[i] = nullptr;
		}
    	this->ma_bai=ma;
    	this->kich_thuoc=kt;
	}
	~bai_xe(){
		for(int i = 0 ; i < suc_chua;i++){
			delete mang_pt[i];
		}
		delete[] mang_pt;
	}
	bai_xe(const bai_xe& other){
		this->mang_pt = new phuong_tien * [other.suc_chua]();
		for(int i = 0 ; i < suc_chua ;i++){
			this->mang_pt[i] = other.mang_pt[i];
		}
	}
	bai_xe operator = (const bai_xe& other){
		this->ma_bai = other.ma_bai;
		this->kich_thuoc = other.kich_thuoc;
		this->suc_chua = other.suc_chua;
		this->so_xe_hien_tai = other.so_xe_hien_tai;
		return *this;
	}
	void td_succhua(int nsucchua){	
		phuong_tien** mang_moi = new phuong_tien *[nsucchua]();
		for(int i = 0 ; i < this->suc_chua ;i++){
			mang_moi[i] = this->mang_pt[i];
		}
		
		delete[] this->mang_pt;
		this->mang_pt = mang_moi;
		this->suc_chua = nsucchua;
	}
    int lay_ma() const;
    bool them(const phuong_tien& v);
    bool xoa(int ma_xe);
};



int bai_xe::lay_ma() const { return ma_bai; }

bool bai_xe::them(const phuong_tien& v) {
	if(this->so_xe_hien_tai == this->suc_chua){
		this->td_succhua(2 * this->suc_chua);
	}
	for(int i = 0 ; i < this->suc_chua;i++){
		if( mang_pt[i] == nullptr){
			mang_pt[i] = new phuong_tien(v);
			this->so_xe_hien_tai++;
			return true;
		}
	}
	return false;
}

bool bai_xe::xoa(int ma_xe) {
	bool flag = false;
	int count = -1;
	for(int i = 0 ; i < this->suc_chua;i++){
		if( this->mang_pt[i]->lay_ma_xe() == ma_xe){
			delete mang_pt[i];
			flag= true;
			count = i;
			this->so_xe_hien_tai--;
		}
	}
	if(count != -1){
		for(int i = count ; i < this->suc_chua ;i ++){
			if((i+1) < this->suc_chua){
				this->mang_pt[i] = this->mang_pt[i+1];
			}
		}
		this->mang_pt[this->suc_chua - 1] = nullptr;
	}
	return flag;
}


class SystemInterface {
private:
    int succhua_baido = 5;
    int sobai_hientai = 0;
    bai_xe** mang_bx;

public:
	SystemInterface(){
		mang_bx = new bai_xe * [this->sobai_hientai];
		for(int i = 0 ; i < this->succhua_baido;i++){
			this->mang_bx[i] = nullptr;
		}
	}
	~SystemInterface(){
		for(int i = 0 ; i < this->succhua_baido;i++){
			delete this->mang_bx[i];
		}
		delete[] mang_bx;
	}
	void td_System(int nsucchua){
		bai_xe mang_moi = new bai_xe * [nsucchua];
		for(int i = 0 ; i < this->succhua_baido;i++){
			mang_moi[i] = this->mang_bx[i];
		}
		delete this->mang_bx;
		this->mang_bx = mang_moi;
		this->succhua_baido = nsucchua;
	}
    void runMenu();
};



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
//các e chuy?n sang l?nh switch cho th?y
        if (chon == 1) {
            int ma; char kt;
            if(this->sobai_hientai == succhua_baido){
            	
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

