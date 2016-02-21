# ofxColorKinetics

## Requirements
This library requires `ofxNetwork` for networking.

Also, make sure that your computer is configured to be on the same subnet as your power supply!

## Usage
`LightingController` is the entry point for this addon -- create an instance of `std::shared_ptr<LightingController>` to get going.

Once you've created a `LightingController`, you can add power supplies via `addPowerSupply()`.  You'll need the IP Address and receiving port, which you can detect with ColorKinetic's (free!) QuickPlay Pro software.

Once you've added power supplies, you can use `addFixture()` to add lighting fixtures.  You'll need the number of pixels (1 for a ColorBlast, since it only has 1 addressable RGB triplet, or 50 for a ColorFlex, which has 50 pixels, for example) and the *first* DMX address of the string.

There are several ways to add fixtures:

* `addFixture("192.168.0.17", 0, 1)` would add a ColorBlast-type unit that uses DMX Addresses 0, 1, and 2 for red, green, and blue.
* `addFixture("192.168.0.17", ColorBlast::make(0))` would do the same thing, but uses a shorthand.

Classes have been added for `ColorBlast`, 50 pixel `ColorFlex`, and 48- and 72-inch ColorBlaze (`ColorBlaze48`/`ColorBlaze72`) fixtures.

## Examples
* `example-singleColor` creates a single power supply and sends a fading color to all 512 DMX channels.  This is a good first test to see if your network is configured properly.

## Contributions

## More Information
For more information on how to address your lights and power supply, see the official Philips documentation for their QuickPlay Pro software: [KiNET Addressing](http://www.colorkinetics.com/support/addressing/)
