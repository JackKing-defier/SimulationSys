
//user.h -- User class interface
//version 00
#ifndef USER_H_
#define USER_H_

#include <string>
using namespace std;

class User
{
private:
	int sno;
	string id;
	float lon;
	float lat;
	string isEnabled;
	string isOnDuty;
	string name;
	string mid;
	//discription;
	//capability;
public:
	int get_sno() const { return sno; };
	string get_id() const { return id; };
	float get_lon() const { return lon; };
	float get_lat() const { return lat; };
	string get_isEnabled() const { return isEnabled; };
	string get_isOnDuty() const { return isOnDuty; };
	string get_name() const { return name; };
	string get_mid() const { return mid; };

	void set_sno(int s) { sno = s; };
	void set_id(string i) { id = i; };
	void set_lon(float lo) { lon = lo; };
	void set_lat(float la) { lat = la; };
	void set_isEnabled(string e) { isEnabled = e; };
	void set_isOnDuty(string o) { isOnDuty = o; };
	void set_name(string n) { name = n; };
	void set_mid(string m) { mid = m; };

	void show();

	User();
	User(int s, const string & i, float lo, float la,
		const string & e, const string & o, const string & n,
		const string & m);
	~User();
};
#endif // !USER_H_

