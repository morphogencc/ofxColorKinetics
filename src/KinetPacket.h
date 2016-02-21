#pragma once

#include <vector>

namespace ofxColorKinetics {

	class KinetPacket {
	public:
		KinetPacket(uint16_t version);
		void setVersionNumber(uint16_t version);
		void setUniverse(uint32_t universe);
		void setPort(unsigned char port);
		void setStartCode(uint16_t start_code);
		void resetPacket();
		void setDmxData(int address, unsigned char value);
		unsigned char* getPacketData();
		int getPacketLength();
	protected:
		static const unsigned char mMagicNumber[4];
		static const unsigned char mSequenceNumber[4];
		static const unsigned char mPad;
		static const unsigned char mFlags[2];
		unsigned char mPacketType[2];
		unsigned char mStartCode[2];
		unsigned char mVersionNumber[2];
		int mVersion;
		int mPortIndex;
		unsigned char mUniverse[4];
		unsigned char mPort;
		unsigned char mLength[2];
		std::vector<unsigned char> mPacket;
		int mDmxStart;
	};

}
