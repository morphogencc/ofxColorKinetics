
namespace ofxColorKinetics {
	struct Pixel {
		Pixel(int dmx_address) {
			mDmxAddress = dmx_address;
			mRed = 0;
			mBlue = 0;
			mGreen = 0;
		};

		int mDmxAddress;
		unsigned char mRed;
		unsigned char mBlue;
		unsigned char mGreen;
	};

	class Fixture {
	public:
		static std::shared_ptr<Fixture> make(int starting_address, int number_of_pixels) {
			std::shared_ptr<Fixture> fixture(new Fixture(starting_address, number_of_pixels));
			return fixture;
		}

		~Fixture() {};
		
		std::vector<Pixel> getPixels() {
			return mPixels;
		};

		int getStartingAddress() {
			return mDmxStart;
		};
		
		void setColor(unsigned char red, unsigned char blue, unsigned char green) {
			for (auto pixel : mPixels) {
				pixel.mRed = red;
				pixel.mBlue = blue;
				pixel.mGreen = green;
			}
		};
		
		void setColor(int pixel, unsigned char red, unsigned char blue, unsigned char green) {
			if (pixel < mPixels.size()) {
				mPixels[pixel].mRed = red;
				mPixels[pixel].mBlue = blue;
				mPixels[pixel].mGreen = green;
			}
			else {
				std::printf("Fixture::setColor -- Pixel %d doesn't exist! This fixture only has %d pixels.", pixel, mPixels.size());
			}
		};

	protected:
		Fixture(int starting_address, int number_of_pixels) {
			mDmxStart = starting_address;
			for (int i = 0; i < number_of_pixels; i++) {
				mPixels.push_back(Pixel(mDmxStart + 3*i));
			}
		};
		std::vector<Pixel> mPixels;
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
