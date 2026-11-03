#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;
class Vehicle{
	private:
		int vehicleID;
		string vehicleType;
		int entryTime;
		int parkingDuration;
		double parkingFee;
		bool isOccupied;
		
	public:
		Vehicle(){
			this->vehicleID = 0;
			this->vehicleType = "";
			this->entryTime = 0;
			this->parkingDuration = 0;
			this->parkingFee = 0 ;
			this->isOccupied = false;
		}
		Vehicle(int ID,string Type, int Entry , int Duration , double Fee, bool Occu ){
			this->vehicleID = ID;
			SetVehicleType(Type);
			SetEntryTime(Entry);
			SetParkingDuration(Duration);
			this->parkingFee = Fee;
			this->isOccupied = Occu;
		}
		int GetVehicleID() const{
			return vehicleID;
		}
		void SetVehicleID(int ID){
			this->vehicleID = ID;
		}
		string GetVehicleType() const{
			return vehicleType;
		}
		void SetVehicleType(string Type){
			transform(Type.begin(),Type.end(),Type.begin(),::tolower);
			if(Type == "car" || Type == "motorcycle" || Type == "bicycle" ){
				this->vehicleType = Type;
			}
			else{
				cout<<"Loai xe khong khong hop le ";
			}
		}
		int GetEntryTime() const{
			return entryTime;
		}
		void SetEntryTime(int Time){
			if(Time >=0 && Time <= 23){
				this->entryTime = Time;
			}
			else{
				cout<<"Thoi gian vao khong hop le";
				this->entryTime = 0;
			}
		}
		int GetParkingDuration() const{
			return parkingDuration;
		}
		void SetParkingDuration(int Duration){
			if(Duration >= 0 && Duration <= 23){
				this->parkingDuration = Duration;
			}
			else{
				cout<<"Thoi gian do khong hop le ";
			}
		}
		void GetParkingFee(){
			CaculatingFee();
		}
		void SetParkingFee(double Fee){
			this->parkingFee = 0;
		}
		void CaculatingFee(){
			double money = 0;
			double base = 0,peak = 0;
			if(vehicleType == "car"){
				base = 6;
			}
			else if(vehicleType == "motorcycle"){
				base = 4;
			}
			else if (vehicleType == "bicycle"){
				base = 2;
			}
			
			if((entryTime >= 6 && entryTime <= 9) || (entryTime >= 15 && entryTime <= 18)){
				peak = 1.3;
			}
			else{
				peak = 0.95;
			}
			if(parkingDuration <= 2){
				money = base * parkingDuration * peak;
			}
			else{
				money = (base * 2 * peak) + (base * (parkingDuration - 2) * 0.90);
			}
			cout << "Phi do xe la " << money;
		}
		bool GetIsOccupied() const{return isOccupied;}
		void SetIsOccupied(bool Occu){
			this->isOccupied = Occu;
		}
		void display()const{
			cout<<"Thong tin xe\n";
			cout<<"ID xe"<<vehicleID<<"\n";
			cout<<"Type xe"<<vehicleType<<"\n";
			cout<<"Entry Time xe"<<entryTime<<"\n";
			cout<<"Parking Duration xe"<<parkingDuration<<"\n";
			cout<<"Parking Fee xe"<<parkingFee<<"\n";
			cout<<"IsOccupied xe"<<isOccupied<<"\n";
		}
};
class ParkingLot{
	private:
		int parkID;
		char size;
		Vehicle vehicle1;
		Vehicle vehicle2;
		Vehicle vehicle3;
		bool hasVehicle1,hasVehicle2,hasVehicle3;
	public:
		ParkingLot(){
			this->parkID = 0;
			this->size = ' ';
			this->hasVehicle1 = false;
			this->hasVehicle2 = false;
			this->hasVehicle3 = false;
		}
		ParkingLot(int id, char s){
			parkID = id;
			size = s;
			hasVehicle1 = false;
			hasVehicle2 = false;
			hasVehicle3 = false;
		}
		
		
		int GetParkId() const{ return parkID;}
		char GetSize() const { return size;}
		Vehicle GetVehicle1() const{return vehicle1;}
		Vehicle GetVehicle2() const{return vehicle2;}
		Vehicle GetVehicle3() const{return vehicle3;}
		bool GetHasVehicle1() const{return hasVehicle1;}
		bool GetHasVehicle2() const{return hasVehicle2;}
		bool GetHasVehicle3() const{return hasVehicle3;}
		
		
		
		bool addVehicle(const Vehicle v){
			if(size == 'S'){
				vehicle1 = v;
				hasVehicle1 = true;
				return true;
			}
			else if ( size == 'M'){
				vehicle1 = v ; vehicle2 = v;
				hasVehicle1 = true;hasVehicle2 = true;
				return true;
			}
			else if ( size == 'L'){
				vehicle1 = v;vehicle2 = v;vehicle3 = v;
				hasVehicle1 = true;hasVehicle2 = true;hasVehicle3 = true;
				return true;
			}
			else{
				return false;
			}
		}
		bool removeVehicle(int vID){
			if(hasVehicle1 == true && vehicle1.GetVehicleID() == vID ){
				hasVehicle1 = false;
				vehicle1.SetIsOccupied(false);
				return true;
			}
			if(hasVehicle2 == true && vehicle2.GetVehicleID() == vID ){
				hasVehicle2 = false;
				vehicle2.SetIsOccupied(false);
				return true;
			}
			if(hasVehicle3 == true && vehicle3.GetVehicleID() == vID ){
				hasVehicle3 = false;
				vehicle3.SetIsOccupied(false);
				return true;
			}
		}
		
		void displayLotInfo(){
			cout<<parkID<<size<<"\n";
			if(hasVehicle1 == true){
				vehicle1.display();
			}
			if(hasVehicle2 == true){
				vehicle2.display();
			}
			if(hasVehicle3 == true){
				vehicle3.display();
			}
		}
			
};
class SystemInterface{
		private:
			ParkingLot parkingLot1;
			ParkingLot parkingLot2;
			ParkingLot parkingLot3;
			bool hasLot1,hasLot2,hasLot3;
		public:
			SystemInterface(){
				hasLot1 = false;hasLot2 = false;hasLot3 = false;
			}
			void runMenu(){
				int select = 0;
				while (select != 9 ){
				cout << "1. Tao bai do xe moi - parkID , size: \n";
				cout << "2. Them xe vao bai do - vehicleID , vehicleType , entryTime:\n";
				cout << "3. Xoa mot bai do xe - parkID:\n";
				cout << "4. Lay xe ra khoi bao di - vehicleID:\n";
				cout << "5.Hien thi danh sach tat ca cac bai do xe :\n";
				cout << "6. hien thi danh sach xe theo bai cu the - parkID:\n";
				cout << "7.Liet ke xe theo loai phuong tien - (Car,MotorCycle,Bicycle) : \n";
				cout << "8. Xem bao cao tom tat chi phi do xe trung binh : \n";
				cout << "9. Thoat\n";
				cin >> select;
				switch (select){
					case 1 : createParkingLot();break;
					case 2 : addVehicleParking();break;
					case 3 : removeParkingLot();break;
					case 4 : getVehicleOut();break;
					case 5 : displayListParkingLot();break;
					case 6 : displayVehicleParkingID();break;
					case 7 : listVehicleType();break;
					case 8 : displayReport();break;
					case 9 : break; 
					default : cout << "Lua chon khong hop le hay chon lai so  theo dung quy tac";
				}
				}
			}
			 
			void createParkingLot(){ 
				if(hasLot1 == true && hasLot2 == true && hasLot3 == true){
					cout<< "FUll";
				}
				else{
					int id;
					char size;
					cin >> id >> size;
					if (size == 's') size = 'S';
        			if (size == 'm') size = 'M';
        			if (size == 'l') size = 'L';
        			
        			if(hasLot1 == false){
        				parkingLot1 = ParkingLot(id,size);
        				hasLot1 = true;
					}
					else if(hasLot2 == false){
        				parkingLot2 = ParkingLot(id,size);
        				hasLot2 = true;
					}
					else if(hasLot3 == false){
        				parkingLot3 = ParkingLot(id,size);
        				hasLot3 = true;
					}			
				}
			}
			void addVehicleParking(){
				int vehicleID ; string vehicleType ; int entryTime;
				cout << "Nhap lan luot ID , vType, eTime";
				cin >> vehicleID >> vehicleType >> entryTime;
				if(hasLot1 == true && hasLot2 == true && hasLot3 == true){
					cout << "FULL";
				}
				else{
					Vehicle newVehicle(vehicleID,vehicleType,entryTime,0,0,true);
					bool count = false;
					if(hasLot1 == false && parkingLot1.addVehicle(newVehicle)){
						cout<< "Success";
					}
					else if (hasLot2 == false && parkingLot2.addVehicle(newVehicle)){
						cout<< "Success";
					}
					else if (hasLot3 == false && parkingLot3.addVehicle(newVehicle)){
						cout<< "Success";
					}
			
				}
			}
			void removeParkingLot(){
				cout << "Nhap id bai do xe";
				int id ;
				cin >> id;
				bool flag = false;
				if(hasLot1 == true && parkingLot1.GetParkId() == id){
					hasLot1 = false;
					flag = true;
				}
				else if ( hasLot2 == true && parkingLot2.GetParkId() == id){
					hasLot2 = false;
					flag = true;
				}
				else if( hasLot3 == true && parkingLot3.GetParkId() == id){
					hasLot3 = false;
					flag = true;
				}
				if(flag == true){
					cout << "Xoa thanh cong";
				}
				else{
					cout << "Khong tim thay id da nhap";
				}
			}
			void getVehicleOut(){
				cout << " Nhap vao vehicleID cua ban";
				int id;
				cin >> id;
				bool flag = false;
				if(hasLot1 == true && parkingLot1.removeVehicle(id) == true ){
					flag = true;
				}
				else if (hasLot2 == true && parkingLot2.removeVehicle(id) == true ){
					flag = true;
				}
				else if(hasLot3 == true && parkingLot3.removeVehicle(id) == true ){
					flag = true;
				}
				if(flag == true){
					cout << "Xoa thanh cong";
				}
				else{
					cout << "Khong tim thay id da nhap";
				}
			}
			void displayListParkingLot(){
				if(hasLot1 == true){
					parkingLot1.displayLotInfo();
				}
				if(hasLot2 == true){
					parkingLot2.displayLotInfo();
				}
				if(hasLot3 == true){
					parkingLot3.displayLotInfo();
				}
			}
			void displayVehicleParkingID(){
				int id ;
				cin >> id;
				bool flag = false;
				if(hasLot1 == true && parkingLot1.GetParkId() == id ){
					parkingLot1.GetVehicle1().display(); // lay thong tin tu lop parkinglot -> lop xe  roi den ham hien thi chi tiet
					parkingLot1.GetVehicle2().display();
					parkingLot1.GetVehicle3().display();
				}
				else if (hasLot2 == true && parkingLot2.GetParkId() == id ){
					parkingLot2.GetVehicle1().display(); 
					parkingLot2.GetVehicle2().display();
					parkingLot2.GetVehicle3().display();
				}
				else if (hasLot3 == true && parkingLot3.GetParkId() == id){
					parkingLot3.GetVehicle1().display(); 
					parkingLot3.GetVehicle2().display();
					parkingLot3.GetVehicle3().display();
				}
			}
			void listVehicleType(){
				string temp;
				cin >> temp;
				transform(temp.begin(),temp.end(),temp.begin(), ::tolower);
				if(hasLot1 == true){
					bool flag = false;
					if(parkingLot1.GetVehicle1().GetVehicleType() == temp){
						parkingLot1.GetVehicle1().display();
						flag = true;
					}
					if(parkingLot1.GetVehicle2().GetVehicleType() == temp){
						parkingLot1.GetVehicle1().display();
						flag = true;
					}
					if(parkingLot1.GetVehicle3().GetVehicleType() == temp){
						parkingLot1.GetVehicle1().display();
						flag = true;
					}
					if(flag == true){
						parkingLot1.displayLotInfo();
					}
				}
				if(hasLot2 == true){
					bool flag = false;
					if(parkingLot2.GetVehicle1().GetVehicleType() == temp){
						parkingLot2.GetVehicle1().display();
						flag = true;
					}
					if(parkingLot2.GetVehicle2().GetVehicleType() == temp){
						parkingLot2.GetVehicle1().display();
						flag = true;
					}
					if(parkingLot2.GetVehicle3().GetVehicleType() == temp){
						parkingLot2.GetVehicle1().display();
						flag = true;
					}
					if(flag == true){
						parkingLot2.displayLotInfo();
					}
				}
				if(hasLot3 == true){
					bool flag = false;
					if(parkingLot3.GetVehicle1().GetVehicleType() == temp){
						parkingLot3.GetVehicle1().display();
						flag = true;
					}
					if(parkingLot3.GetVehicle2().GetVehicleType() == temp){
						parkingLot3.GetVehicle1().display();
						flag = true;
					}
					if(parkingLot3.GetVehicle3().GetVehicleType() == temp){
						parkingLot3.GetVehicle1().display();
						flag = true;
					}
					if(flag == true){
						parkingLot3.displayLotInfo();
					}
				}		
			}
			void displayReport(){
				// ......
			}
			
			
	};
			int main(){
			SystemInterface st;			
			st.runMenu();		
				
				
					
}
	
	
