#include "PowerSupply.h"

using namespace ofxColorKinetics;

std::shared_ptr<PowerSupply> PowerSupply::make(std::string ip_address, int port) {
	std::shared_ptr<PowerSupply> psu(new PowerSupply(ip_address, port));
	return psu;
}

PowerSupply::PowerSupply(std::string ip_address, int port) {
	mIpAddress = ip_address;
	mPort = port;
	mKinet = std::unique_ptr<KinetPacket>(new KinetPacket(0x0001));
	connect();
}

PowerSupply::~PowerSupply() {

}

bool PowerSupply::connect() {
	//bool result = connect();
	//return result;
	return false;
}

std::string PowerSupply::getIpAddress() {
	return mIpAddress;
}

int PowerSupply::getPort() {
	return mPort;
}

void PowerSupply::setKinetVersion(uint16_t version) {
	mKinet->setVersionNumber(version);
}

void PowerSupply::addFixture(std::shared_ptr<Fixture> fixture) {
	mFixtures.push_back(fixture);
}

int PowerSupply::getNumberOfFixtures() {
	return mFixtures.size();
}

std::vector<std::shared_ptr<Fixture> > PowerSupply::getFixtures() {
	return mFixtures;
}

std::shared_ptr<Fixture> PowerSupply::getFixture(int starting_address) {
	for (auto fixture : mFixtures) {
		if (fixture->getStartingAddress() == starting_address) {
			return fixture;
		}
	}
	std::printf("PowerSupply::getFixture() -- could not find a fixture with designated starting DMX address.");
	return nullptr;
}

void PowerSupply::clearFixtures() {
	mFixtures.clear();
}

void PowerSupply::tick(unsigned char port) {
	for (auto fixture : mFixtures) {
		for (auto pixel : fixture->getPixels()) {
			mKinet->setDmxData(pixel.mDmxAddress, pixel.mRed);
			mKinet->setDmxData(pixel.mDmxAddress + 1, pixel.mBlue);
			mKinet->setDmxData(pixel.mDmxAddress + 2, pixel.mGreen);
		}
	}

	//send packet
	mKinet->setPort(port);
}
