#pragma once

#include <vector>
#include <memory>

namespace ofxColorKinetics {

	struct Pixel {
		Pixel(int dmx_address) {
			mDmxAddress = dmx_address;
			mRed = 0;
			mGreen = 0;
			mBlue = 0;
		};

		int mDmxAddress;
		unsigned char mRed;
		unsigned char mGreen;
		unsigned char mBlue;
	};

	class Fixture {
	public:
		static std::shared_ptr<Fixture> Fixture::make(int starting_address, int number_of_pixels) {
			std::shared_ptr<Fixture> fixture(new Fixture(starting_address, number_of_pixels));
			return fixture;
		}

		~Fixture() {};
		
		std::vector<std::shared_ptr<Pixel> > getPixels() {
			return mPixels;
		}

		int getStartingAddress() {
			return mDmxStart;
		};

		int getNumberOfPixels() {
			return mPixels.size();
		}
		
		void setColor(unsigned char red, unsigned char green, unsigned char blue) {
			for (auto pixel : mPixels) {
				pixel->mRed = red;
				pixel->mGreen = green;
				pixel->mBlue = blue;
			}
		};
		
		void setColor(int pixel, unsigned char red, unsigned char green, unsigned char blue) {
			if (pixel < mPixels.size()) {
				mPixels[pixel]->mRed = red;
				mPixels[pixel]->mGreen = green;
				mPixels[pixel]->mBlue = blue;
			}
			else {
				std::printf("Fixture::setColor -- Pixel %d doesn't exist! This fixture only has %d pixels.", pixel, mPixels.size());
			}
		};

	protected:
		Fixture(int starting_address, int number_of_pixels) {
			mDmxStart = starting_address;
			for (int i = 0; i < number_of_pixels; i++) {
				mPixels.push_back(std::shared_ptr<Pixel>(new Pixel(mDmxStart + 3*i)));
			}
		};
		std::vector<std::shared_ptr<Pixel> > mPixels;
		int mDmxStart;
	};

	class ColorBlast : public Fixture {
	public:
		std::shared_ptr<ColorBlast> make(int starting_address) {
			std::shared_ptr<ColorBlast> fixture(new ColorBlast(starting_address));
			return fixture;
		};

	protected:
		ColorBlast(int starting_address) : Fixture(starting_address, 1) {
		};
	};

	class FlexString : public Fixture {
	public:
		std::shared_ptr<FlexString> make(int starting_address) {
			std::shared_ptr<FlexString> fixture(new FlexString(starting_address));
			return fixture;
		};

	protected:
		FlexString(int starting_address) : Fixture(starting_address, 50) {
		};
	};

	class ColorBlaze48 : public Fixture {
	public:
		std::shared_ptr<ColorBlaze48> make(int starting_address) {
			std::shared_ptr<ColorBlaze48> fixture(new ColorBlaze48(starting_address));
			return fixture;
		};

	protected:		
		ColorBlaze48(int starting_address) : Fixture(starting_address, 8) {
		};
	};

	class ColorBlaze72 : public Fixture {
	public:
		std::shared_ptr<ColorBlaze72> make(int starting_address) {
			std::shared_ptr<ColorBlaze72> fixture(new ColorBlaze72(starting_address));
			return fixture;
		};

	protected:
		ColorBlaze72(int starting_address) : Fixture(starting_address, 12) {
		};
	};

}
