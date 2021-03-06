#pragma once

#include "Fixture.h"
#include "PowerSupply.h"

namespace ofxColorKinetics {
	class LightingController {
	public:
		static std::shared_ptr<LightingController> getInstance();
		static std::shared_ptr<LightingController> getInstance(std::string filename);
		void addPowerSupply(std::string ip_address, int port=6038);
		void addFixture(std::string ip_address, int starting_address, int number_of_pixels);
		void addFixture(std::string ip_address, int starting_address, int number_of_pixels, std::string name);
		void addFixture(std::string ip_address, std::shared_ptr<Fixture> fixture);
		void addFixture(std::string ip_address, std::shared_ptr<Fixture> fixture, std::string name);
		std::shared_ptr<PowerSupply> getPowerSupply(std::string ip_address);
		std::vector<std::shared_ptr<PowerSupply> > getAllPowerSupplies();
		std::shared_ptr<Fixture> getFixture(std::string ip_address, int starting_address);
		std::vector<std::shared_ptr<Fixture> > getFixtures(std::string ip_address);
		std::vector<std::shared_ptr<Fixture> > getAllFixtures();
		int getNumberOfFixtures();
		void tick(unsigned char port = 0x00);
		void setKinetVersion(int version);
	protected:
		LightingController();
		LightingController(std::string filename);
		void loadFromFile(std::string filename);
		static std::shared_ptr<LightingController> mLightingController;
		std::map<std::string, std::shared_ptr<PowerSupply> > mPowerSupplies;
		std::map<std::string, std::shared_ptr<Fixture> > mFixtures;
	};
}