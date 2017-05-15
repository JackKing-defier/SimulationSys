
//uav.h -- Uav class interface
//version 00
#ifndef UAV_H_
#define UAV_H_

#include <string>
using namespace std;

class Uav //
{
private:
	int sno;
	string id;
	string model;
	string brand;
	string max_height;
	string max_minute;
	string max_distance;
	string memory;
	string resolution;
	string min_focus;
	string max_focus;
	float lon;
	float lat;
public:
	int get_sno() const { return sno; };
	string get_id() const { return id; };
	string get_model() const { return model; };
	string get_brand() const { return brand; };
	string get_max_height() const { return max_height; };
	string get_max_minute() const { return max_minute; };
	string get_max_distance() const { return max_distance; };
	string get_memory() const { return memory; };
	string get_resolution() const { return resolution; };
	string get_min_focus() const { return min_focus; };
	string get_max_focus() const { return max_focus; };
	float get_lon() const { return lon; };
	float get_lat() const { return lat; };

	void set_sno(int s) { sno = s; };
	void set_id(string i) { id = i; };
	void set_model(string lo) { model = lo; };
	void set_brand(string la) { brand = la; };
	void set_max_height(string e) { max_height = e; };
	void set_max_minute(string o) { max_minute = o; };
	void set_max_distance(string n) { max_distance = n; };
	void set_memory(string m) { memory = m; };
	void set_resolution(string r) { resolution = r; };
	void set_min_focus(string mf) { min_focus = mf; };
	void set_max_focus(string maxf) { max_focus = maxf; };
	void set_lon(float lo) { lon = lo; };
	void set_lat(float la) { lat = la; };

	void show();

	Uav();
	Uav(int sno, const string & i, const string & lo, const string & la,
		const string & e, const string & o, const string & n,
		const string & m, const string & r, const string & mf,
		const string & maxf);
	~Uav();
};
#endif // !UAV_H_

