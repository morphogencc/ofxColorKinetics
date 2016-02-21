#include "LightingController.h"

using namespace ofxColorKinetics;

std::shared_ptr<LightingController> LightingController::mLightingController = nullptr;

std::shared_ptr<LightingController> LightingController::getInstance() {
	if (!mLightingController) {
		mLightingController = std::shared_ptr<LightingController>(new LightingController());
	}
	return mLightingController;
}

std::shared_ptr<LightingController> LightingController::getInstance(std::string filename) {
	if (!mLightingController) {
		mLightingController = std::shared_ptr<LightingController>(new LightingController(filename));
	}
	return mLightingController;
}

LightingController::LightingController() {

}

LightingController::LightingController(std::string filename) {

}

void LightingController::addPowerSupply(std::string ip_address, int port) {
	mPowerSupplies.insert(std::make_pair(ip_address, PowerSupply::make(ip_address, port)));
}

void LightingController::addFixture(std::string ip_address, int starting_address, int number_of_pixels) {
	std::shared_ptr<Fixture> fixture = Fixture::make(starting_address, number_of_pixels);
	mFixtures.insert(std::make_pair(std::to_string(starting_address), fixture));
	mPowerSupplies[ip_address]->addFixture(fixture);
}

void LightingController::addFixture(std::string ip_address, int starting_address, int number_of_pixels, std::string name) {
	std::shared_ptr<Fixture> fixture = Fixture::make(starting_address, number_of_pixels);
	mFixtures.insert(std::make_pair(name, fixture));
	mPowerSupplies[ip_address]->addFixture(fixture);
}

void LightingController::addFixture(std::string ip_address, std::shared_ptr<Fixture> fixture) {
	mFixtures.insert(std::make_pair(std::to_string(fixture->getStartingAddress()) , fixture));
	mPowerSupplies[ip_address]->addFixture(fixture);
}

void LightingController::addFixture(std::string ip_address, std::shared_ptr<Fixture> fixture, std::string name) {
	mFixtures.insert(std::make_pair(name, fixture));
	mPowerSupplies[ip_address]->addFixture(fixture);
}

std::shared_ptr<PowerSupply> LightingController::getPowerSupply(std::string ip_address) {
	return mPowerSupplies[ip_address];
}

std::vector<std::shared_ptr<PowerSupply> > LightingController::getAllPowerSupplies() {
	std::vector<std::shared_ptr<PowerSupply> > supplies;
	for (std::map<std::string, std::shared_ptr<PowerSupply> >::iterator it = mPowerSupplies.begin(); it != mPowerSupplies.end(); ++it) {
		supplies.push_back(it->second);
	}
	return supplies;
}

std::shared_ptr<Fixture> LightingController::getFixture(std::string ip_address, int starting_address) {
	return mPowerSupplies[ip_address]->getFixture(starting_address);
}

std::vector<std::shared_ptr<Fixture> > LightingController::getFixtures(std::string ip_address) {
	return mPowerSupplies[ip_address]->getFixtures();
}

std::vector<std::shared_ptr<Fixture> > LightingController::getAllFixtures() {
	std::vector<std::shared_ptr<Fixture> > fixtures;
	for (std::map<std::string, std::shared_ptr<Fixture> >::iterator it = mFixtures.begin(); it != mFixtures.end(); ++it) {
		fixtures.push_back(it->second);
	}
	return fixtures;
}

void LightingController::tick(unsigned char port) {
	for (auto psu : mPowerSupplies) {
		psu.second->tick(port);
	}
}

void LightingController::setKinetVersion(int version) {
	for (auto psu : mPowerSupplies) {
		psu.second->setKinetVersion(version);
	}
}