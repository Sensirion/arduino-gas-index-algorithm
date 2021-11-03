# Sensirion Gas Index Algorithm Arduino Library

This is the Sensirion Gas Index Algorithm library for Arduino.


# Installation

To install, download the latest release as .zip file and add it to your
[Arduino IDE](http://www.arduino.cc/en/main/software) via

	Sketch => Include Library => Add .ZIP Library...

Don't forget to **install the dependencies** listed below (if you want to run the example) the same way via `Add .ZIP Library`

Note: Installation via the Arduino Library Manager is coming soon.

# Dependencies

The dependency to the Sensirion I2C drivers are only needed to run the example, which runs with a SGP41 and a SHT4x sensor.

* [Sensirion I2C SGP41](https://github.com/Sensirion/arduino-i2c-sgp41)
* [Sensirion I2C SHT4x](https://github.com/Sensirion/arduino-i2c-sht4x)

# Quick Start to run the example

1. Connect a SGP41 and SHT4x Sensor over I2C to your Arduino


2. Open the `exampleUsage` sample project within the Arduino IDE

        File => Examples => Sensirion Gas Index Algorithm => exampleUsage

3. Click the `Upload` button in the Arduino IDE or

        Sketch => Upload

4. When the upload process has finished, open the `Serial Monitor` or `Serial
   Plotter` via the `Tools` menu to observe the measurement values and calculated 
   Gas Index value. Note that the `Baud Rate` in the corresponding window has to be set to `115200 baud`.

# Contributing

**Contributions are welcome!**

We develop and test this algorithm using our company internal tools (version
control, continuous integration, code review etc.) and automatically
synchronize the master branch with GitHub. But this doesn't mean that we don't
respond to issues or don't accept pull requests on GitHub. In fact, you're very
welcome to open issues or create pull requests :)

This Sensirion library uses
[`clang-format`](https://releases.llvm.org/download.html) to standardize the
formatting of all our `.cpp` and `.h` files. Make sure your contributions are
formatted accordingly:

The `-i` flag will apply the format changes to the files listed.

```bash
clang-format -i src/*.cpp src/*.h
```

Note that differences from this formatting will result in a failed build until
they are fixed.

# License

See [LICENSE](LICENSE).
