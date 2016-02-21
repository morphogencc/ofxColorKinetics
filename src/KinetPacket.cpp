#include "KinetPacket.h"

using namespace ofxColorKinetics;

// Don't forget -- Kinet uses little-endian byte ordering!
const unsigned char KinetPacket::mMagicNumber[] = { 0x04, 0x01, 0xDC, 0x4A };
const unsigned char KinetPacket::mSequenceNumber[] = { 0x00, 0x00, 0x00, 0x00 };
const unsigned char KinetPacket::mPad = 0x00;
const unsigned char KinetPacket::mFlags[] = { 0x00, 0x00 };

KinetPacket::KinetPacket(uint16_t version) {
	setVersionNumber(version);
	setUniverse(0xFFFFFFFF);
	setPort(0x00);
	setStartCode(0x0FFF);
	resetPacket();
	std::printf("KiNETPacket::KiNETPacket -- Successfully initialized a KiNET v%d packet.\n", version);
}

void KinetPacket::setVersionNumber(uint16_t version) {
	// Don't forget -- Kinet uses little-endian byte ordering!
	if (version == 0x01) {
		mPacketType[0] = 0x08;
		mPacketType[1] = 0x01;
	}
	else if (version == 0x02) {
		mPacketType[0] = 0x01;
		mPacketType[1] = 0x01;
	}
	else {
		std::printf("KiNETPacket::setVersionNumber -- unsupported version number %d!  This library only supports KiNET v1 and KiNET v2.\n", version);
	}

	mVersion = version;
	mVersionNumber[1] = 0x00;
	mVersionNumber[0] = 0x01;

	resetPacket();
}

void KinetPacket::setUniverse(uint32_t universe) {
	// Don't forget -- Kinet uses little-endian byte ordering!
	mUniverse[3] = ((universe >> 24) & 0xFF);
	mUniverse[2] = ((universe >> 16) & 0xFF);
	mUniverse[1] = ((universe >> 8) & 0xFF);
	mUniverse[0] = (universe & 0xFF);
	resetPacket();
}

void KinetPacket::setPort(unsigned char port) {
	mPort = port;
	resetPacket();
}

void KinetPacket::setStartCode(uint16_t start_code) {
	// Don't forget -- Kinet uses little-endian byte ordering!
	// should be 0x0000 or 0x0FFF for ChromASIC-based lights
	mStartCode[1] = ((start_code >> 8) & 0xFF);
	mStartCode[0] = (start_code & 0xFF);
	resetPacket();
}

void KinetPacket::resetPacket() {
	// Don't forget -- Kinet uses little-endian byte ordering!

	mPacket.clear();
	mPacket.push_back(mMagicNumber[0]);
	mPacket.push_back(mMagicNumber[1]);
	mPacket.push_back(mMagicNumber[2]);
	mPacket.push_back(mMagicNumber[3]);
	mPacket.push_back(mVersionNumber[0]);
	mPacket.push_back(mVersionNumber[1]);
	mPacket.push_back(mPacketType[0]);
	mPacket.push_back(mPacketType[1]);
	mPacket.push_back(mSequenceNumber[0]);
	mPacket.push_back(mSequenceNumber[1]);
	mPacket.push_back(mSequenceNumber[2]);
	mPacket.push_back(mSequenceNumber[3]);
	//
	if (mVersion == 1) {
		mPacket.push_back(mPort);
		mPacket.push_back(mPad);
		mPacket.push_back(mPad);
		mPacket.push_back(mPad);
		mPacket.push_back(mUniverse[0]);
		mPacket.push_back(mUniverse[1]);
		mPacket.push_back(mUniverse[2]);
		mPacket.push_back(mUniverse[3]);
	}
	else if (mVersion == 2) {
		mPacket.push_back(mUniverse[0]);
		mPacket.push_back(mUniverse[1]);
		mPacket.push_back(mUniverse[2]);
		mPacket.push_back(mUniverse[3]);
		mPacket.push_back(mPort);
		mPacket.push_back(mPad);
		mPacket.push_back(mFlags[0]);
		mPacket.push_back(mFlags[1]);
		mPacket.push_back(0x00);
		mPacket.push_back(0x02);
		mPacket.push_back(mStartCode[0]);
		mPacket.push_back(mStartCode[1]);
	}
	
	// set the starting in the packet.  Now, mPacket[mDmxStart] is DMX Address 0; mPacket[mDmxStart + 1] is DMX Address 1, etc.
	mDmxStart = mPacket.size();

	// pad out the rest of the packet so we can just assign values to DMX Addresses as above.
	for (int i = 0; i < 512; i++) {
		mPacket.push_back(0x00);
	}
}

void KinetPacket::setDmxData(int address, unsigned char value) {
	if (mPacket.size() > 0) {
		if (address <= 512 && address > 0) {
			// some odd index juggling because DMX is 1-indexed
			mPacket[mDmxStart + address - 1] = value;
		}
		else {
			std::printf("KiNETPacket::setDmxData -- KiNET only supports DMX Address less than 512!  Address %d is out of range.", address);
		}
	}
}

unsigned char* KinetPacket::getPacketData() {
	return mPacket.data();
}

int KinetPacket::getPacketLength() {
	return mPacket.size();
}