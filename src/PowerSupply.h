#pragma once

#include <string>
#include <memory>
#include <map>
#include "Fixture.h"
#include "KinetPacket.h"
#include "ofxUDPManager.h"

namespace ofxColorKinetics {
	class PowerSupply {
	public:
		static std::shared_ptr<PowerSupply> make(std::string ip_address, int port);
		~PowerSupply();
		bool connect();
		std::string getIpAddress();
		int getPort();
		void setKinetVersion(uint16_t version);
		void addFixture(std::shared_ptr<Fixture> fixture);
		int getNumberOfFixtures();
		std::vector<std::shared_ptr<Fixture> > getFixtures();
		std::shared_ptr<Fixture> getFixture(int starting_address);
		void clearFixtures();
		void tick(unsigned char port = 0x00);
	protected:
		PowerSupply(std::string ip_address, int port);
		std::string mIpAddress;
		int mPort;
		std::vector<std::shared_ptr<Fixture> > mFixtures;
		std::unique_ptr<KinetPacket> mKinet;
		ofxUDPManager mUdpSocket;
	};
}
