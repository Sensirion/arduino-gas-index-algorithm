# Sensirion Gas Index Algorithm Arduino Library

SGP4x VOC/NOx Engine Algorithm applies a gain-offset normalization algorithm to a SGP tick signal. The algorithm 
assumes a humidity compensated raw tick signal, applies state estimation, tick-to-GasIndex conversion and an 
adaptive lowpass filter.

The main goal of the VOC/NOX Engine algorithm is to calculate a VOC/NOx Index signal that enables robust detection of ambient
VOC/NOx changes, with minimal sensor-to-sensor variations. The Algorithm Engine calculates the VOC/NOx Index signal 
recursively from a single raw tick value Sout that is measured by the SGP sensor at each time step, as well as internal 
states that are updated at each time step. These internal states are most importantly the recursively estimated mean and 
variance of the Sout signal, as well as some additional internal states such as uptime and other counters.

# Installation

To install, download the latest release as .zip file and add it to your
[Arduino IDE](http://www.arduino.cc/en/main/software) via

	Sketch => Include Library => Add .ZIP Library...

# Dependencies

The dependency to the Sensirion I2C drivers are only needed to run the example, which uses a SGP41 and a SHT4x sensor.

* [Sensirion I2C SGP41](https://github.com/Sensirion/arduino-i2c-sgp41)
* [Sensirion I2C SHT4x](https://github.com/Sensirion/arduino-i2c-sht4x)


## Quick Start to run the example

The example measures VOC and NOx ticks with a SGP41 sensor using a SHT4x to compensate temperature and humidity.
The raw VOC and NOx measurement signals are then processed with the gas index algorithm to get VOC Index and NOx Index values.

For more details about the sensors and breakout boards check out http://sensirion.com/my-sgp-ek/.

1. **Install the driver dependencies** listed above the same way as you installed this library (via `Add .ZIP Library`)


2. Connect a SGP41 and SHT4x Sensor over I2C to your Arduino


3. Open the `exampleUsage` sample project within the Arduino IDE

        File => Examples => Sensirion Gas Index Algorithm => exampleUsage

4. Click the `Upload` button in the Arduino IDE or

        Sketch => Upload

5. When the upload process has finished, open the `Serial Monitor` or `Serial
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
