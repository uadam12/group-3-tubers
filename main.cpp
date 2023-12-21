#include "utils.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct FarmingDetails {
	string name_of_crop;
	double length_per_seed;
	double breadth_per_seed;
	int seed_per_hole;
	double unit_price;

	FarmingDetails(string name_of_crop, double length_per_seed, double breadth_per_seed, int seed_per_hole, double unit_price)
		: name_of_crop(name_of_crop),
		  length_per_seed(length_per_seed),
		  breadth_per_seed(breadth_per_seed),
		  seed_per_hole(seed_per_hole),
		  unit_price(unit_price) {}

	string toString() const {
		stringstream ss;
		ss << "Name of crop: " << name_of_crop << "\n";
		ss << "Length per Seed: " << length_per_seed << "\n";
		ss << "Breadth per Seed: " << breadth_per_seed << "\n";
		ss << "Seed per Hole: " << seed_per_hole << "\n";
		ss << "Unit earnings per Plant: N" << unit_price << "\n";
		return ss.str();
	}
};

struct LandDetails {
	string name;
	double size_in_m2;
	int number_of_workers;
	double price_per_worker;
	double liters_of_pesticide;
	double unit_price_of_pesticide;
	double price_of_sqm;

	LandDetails(string name, double size_in_m2, int number_of_workers, int price_per_worker, double liters_of_pesticide, double unit_price_of_pesticide, double price_of_sqm)
		: name(name),
		  size_in_m2(size_in_m2),
		  number_of_workers(number_of_workers),
		  price_per_worker(price_per_worker),
		  liters_of_pesticide(liters_of_pesticide),
		  unit_price_of_pesticide(unit_price_of_pesticide),
		  price_of_sqm(price_of_sqm) {}

	string toString() const {
		stringstream ss;
		ss << "Land: " << name << "\n";
		ss << "Size in square meter: " << size_in_m2 << "\n";
		ss << "Number of Workers: " << number_of_workers << "\n";
		ss << "Price per Worker: N" << price_per_worker << "\n";
		ss << "Liters of Pesticide required: " << liters_of_pesticide << "\n";
		ss << "Unit price per liter: N" << unit_price_of_pesticide << "\n";
		ss << "Price per Square Meter: N" << price_of_sqm << "\n";

		return ss.str();
	}
};

long plantsPerLandArea(const FarmingDetails &farming_details, double land_area) {
	double plantArea = farming_details.length_per_seed * farming_details.breadth_per_seed;
	return land_area / plantArea;
}

long seedsPerLandArea(const FarmingDetails &farming_details, double land_area) {
	return plantsPerLandArea(farming_details, land_area) * farming_details.seed_per_hole;
}

long approximateEarnings(const FarmingDetails &farming_details, double land_area) {
	return farming_details.unit_price * plantsPerLandArea(farming_details, land_area);
}

long approxCostOfLabor(int number_of_labor, double unit_cost_of_labor) {
	return number_of_labor * unit_cost_of_labor;
}

long approxCostOfPesticide(double unit_cost, double liters) {
	return unit_cost * liters;
}

long approxCostOfLand(double land_area, double price_per_sqm) {
	return land_area * price_per_sqm;
}

bool validateId(int value, int max_value) {
	return value <= max_value && value >= 1;
}

bool validateLandArea(int value) {
	return value >= 100;
}

void printFarmingDetails(const vector<FarmingDetails> &farming_details) {
	cout << "Select Type of Crop" << endl;
	for (size_t i = 0; i < farming_details.size(); i++) {
		const FarmingDetails& detail = farming_details[i];
		cout << i+1 << ". " << detail.name_of_crop << endl;
	}
	cout << endl;
}

void printLandDetails(const vector<LandDetails> &land_details) {
	cout << "Select Farm Allocation" << endl;

	for (size_t i = 0; i < land_details.size(); i++) {
		const LandDetails& detail = land_details[i];
		cout << i + 1 << ". " << detail.name << endl;
	}
	cout << endl;
}

void promptUserToCalculateFarmDetails(const vector<FarmingDetails> &farming_details, const LandDetails &land_details) {
	int input;
	bool valid = true;
	do {
		cout << "Enter the number of the crop you want to know more about: ";
		cin >> input;
		if (!validateId(input, farming_details.size())) {
			cout << "Please enter a number between 1 and " << farming_details.size() << ".\n";
			valid = false;
			continue;
		}
		valid = validateId(input, farming_details.size());
		cout << endl;
	} while (!valid);

	const FarmingDetails& selectedFarmingDetail = farming_details[input - 1];

	cout << land_details.toString() << endl;
	cout << selectedFarmingDetail.toString() << endl;

	cout << "Approx. cost of laborers: N" << approxCostOfLabor(land_details.number_of_workers, land_details.price_per_worker) << endl;
	cout << "Approx. cost of pesticide: N" << approxCostOfPesticide(land_details.unit_price_of_pesticide, land_details.liters_of_pesticide) << endl;
	cout << "Approx. cost of land: N" << approxCostOfLand(land_details.size_in_m2, land_details.price_of_sqm) << endl << endl;

	cout << "Approx. seeds per land area: " << seedsPerLandArea(selectedFarmingDetail, land_details.size_in_m2) << endl;
	cout << "Approx. plants per land area: " << plantsPerLandArea(selectedFarmingDetail, land_details.size_in_m2) << endl;
	cout << "Approx. earnings per land area: N" << approximateEarnings(selectedFarmingDetail, land_details.size_in_m2) << endl << endl;

	const long totalCost = approxCostOfLabor(land_details.number_of_workers, land_details.price_per_worker) + approxCostOfPesticide(land_details.unit_price_of_pesticide, land_details.liters_of_pesticide) + approxCostOfLand(land_details.size_in_m2, land_details.price_of_sqm);
	const long approxProfit = approximateEarnings(selectedFarmingDetail, land_details.size_in_m2) - totalCost;

	cout << "Approx. profit: N" << approxProfit << endl;
}

void promptUserToSelectLandDetails(const vector<LandDetails> &land_details, const vector<FarmingDetails> &farming_details) {
	int input;
	bool valid = true;
	do {
		cout << "Enter the number of the land allocation: ";
		cin >> input;
		if (!validateId(input, land_details.size())) {
			cout << "Please enter a number between 1 and " << land_details.size() << ".\n";
			valid = false;
			continue;
		}
		valid = validateId(input, land_details.size());
		cout << endl;
	} while (!valid);

	const LandDetails& selectedLandDetail = land_details[input - 1];

	printFarmingDetails(farming_details);
	promptUserToCalculateFarmDetails(farming_details, selectedLandDetail);
}

auto createFarmDetailsFromLine (const string &line) -> FarmingDetails {
	vector<string> tokens = FileOperations::splitString(line, ',');
	return FarmingDetails(tokens[0], stod(tokens[1]), stod(tokens[2]), stoi(tokens[3]), stod(tokens[4]));
};

auto createLandDetailsFromLine (const string &line) -> LandDetails {
	vector<string> tokens = FileOperations::splitString(line, ',');
	return LandDetails(tokens[0], stod(tokens[1]), stoi(tokens[2]), stod(tokens[3]), stod(tokens[4]), stod(tokens[5]), stod(tokens[6]));
};

int main() {
	const char *FILE_NAME = {"info.txt"};
	fstream *file = FileOperations::openFile(FILE_NAME);

	vector<std::string> lines = FileOperations::readFileIntoStringArray(file);
	vector<FarmingDetails> details; details.reserve(lines.size());

	const char *LAND_FILE_NAME = {"land.txt"};
	fstream *land_file = FileOperations::openFile(LAND_FILE_NAME);

	vector<std::string> land_lines = FileOperations::readFileIntoStringArray(land_file);
	vector<LandDetails> land_details; land_details.reserve(land_lines.size());

	transform(lines.begin() + 1, lines.end(), back_inserter(details), createFarmDetailsFromLine);
	transform(land_lines.begin() + 1, land_lines.end(), back_inserter(land_details), createLandDetailsFromLine);

	printLandDetails(land_details);
	promptUserToSelectLandDetails(land_details, details);

	return 0;
}
