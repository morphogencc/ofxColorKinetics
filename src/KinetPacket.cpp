#include "KinetPacket.h"

using namespace ofxColorKinetics;

const unsigned char KinetPacket::mMagicNumber[] = { '0x04', '0x01', '0xDC', '0x4A' };
const unsigned char KinetPacket::mSequenceNumber[] = { '0x00', '0x00', '0x00', '0x00' };
const unsigned char KinetPacket::mPad = '0x00';
const unsigned char KinetPacket::mFlags[] = { '0x00', '0x00' };
const unsigned char KinetPacket::mPacketType[] = { '0x01', '0x08' };

KinetPacket::KinetPacket(uint16_t version) {
	setVersionNumber(version);
	setUniverse(0xFFFFFFFF);
	setPort(0x00);
	setStartCode(0x0000);
	resetPacket();
}

void KinetPacket::setVersionNumber(uint16_t version) {
	mVersionNumber[0] = ((version >> 8) & 0xFF);
	mVersionNumber[1] = (version & 0xFF);
	if (mPacket.size() > 0) {
		mPacket[4] = mVersionNumber[0];
		mPacket[5] = mVersionNumber[1];
	}
}

void KinetPacket::setUniverse(uint32_t universe) {
	mUniverse[0] = ((universe >> 8) & 0xFF);
	mUniverse[1] = ((universe >> 8) & 0xFF);
	mUniverse[2] = ((universe >> 8) & 0xFF);
	mUniverse[3] = (universe & 0xFF);
	if (mPacket.size() > 0) {
		mPacket[12] = mUniverse[0];
		mPacket[13] = mUniverse[1];
		mPacket[14] = mUniverse[2];
		mPacket[15] = mUniverse[3];
	}
}

void KinetPacket::setPort(unsigned char port) {
	mPort = port;
	if (mPacket.size() > 0) {
		mPacket[16] = mPort;
	}
}

void KinetPacket::setStartCode(uint16_t start_code) {
	//should be 0x0000 or 0x0FFF for ChromASIC-based lights
	mStartCode[0] = ((start_code >> 8) & 0xFF);
	mStartCode[1] = (start_code & 0xFF);
	if (mPacket.size() > 0) {
		mPacket[22] = mStartCode[0];
		mPacket[23] = mStartCode[1];
	}
}

void KinetPacket::resetPacket() {
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
	mPacket.push_back(mUniverse[0]);
	mPacket.push_back(mUniverse[1]);
	mPacket.push_back(mUniverse[2]);
	mPacket.push_back(mUniverse[3]);
	mPacket.push_back(mPort);
	mPacket.push_back(mPad);
	mPacket.push_back(mFlags[0]);
	mPacket.push_back(mFlags[1]);
	mPacket.push_back(0xAA); //length of packet -- 170 lights
	mPacket.push_back(0x00); //length of packet -- 170 lights
	mPacket.push_back(mStartCode[0]);
	mPacket.push_back(mStartCode[1]);
	
	//set the starting in the packet.  Now, mPacket[mDmxStart] is DMX Address 0; mPacket[mDmxStart + 1] is DMX Address 1, etc.
	mDmxStart = mPacket.size();

	//pad out the rest of the packet so we can just assign values to DMX Addresses as above.
	for (int i = 0; i < 512; i++) {
		mPacket.push_back(0x00);
	}
}

void KinetPacket::setDmxData(int address, unsigned char value) {
	if (mPacket.size() > 0) {
		if (address < 512) {
			mPacket[mDmxStart + address] = value;
		}
		else {
			std::printf("KinetPacket::setDmxData -- DMX512 Protocol only supports DMX Address less than 512!  Address %d is too large.", address);
		}
	}
}

unsigned char* KinetPacket::getPacketData() {
	return mPacket.data();
}

int KinetPacket::getPacketLength() {
	return mPacket.size();
}