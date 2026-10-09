# Smart Entryway Multi-Room Network
Two ESP32/ESPHome nodes coordinate low-voltage demonstration lamps and loose servo pointers through Home Assistant over Wi-Fi. Analog microphones detect sound activity; no audio or speech is stored.

![Two conceptual low-voltage sound-triggered ESP32 nodes coordinated through a home server](docs/images/project-overview.png)

## Overview, objectives and features
Learn per-node sensing, encrypted native API, HA coordination and independent bounded outputs. Either healthy node’s sound event requests both indicators. Each node independently enforces5s maximum pulse, boot-off and sensor/network fail-off. This is an educational multi-room prototype, not an access-control system.

## Architecture and platform
Two ESP32 DevKit esp32dev boards, ESPHome2026.9.1/ESP-IDF, HA nativeAPI and Wi-Fi. [Shared firmware](firmware/device.yaml) is instantiated by [nodeA](firmware/node-a.yaml) and [nodeB](firmware/node-b.yaml). [Architecture](docs/architecture.md), [HA automation](config/home-assistant-automation.yaml), and [circuit](docs/circuit-diagram.svg).

## BOM quantities (two nodes)
| Qty | Item |
|---:|---|
| 2 each | ESP32 DevKit, USB data/power cable |
| 2 | Analog microphone module3.3V biased output |
| 2 | Active-high3.3V-compatible relay module5V coil |
| 2 | Micro servo accepting3.3V signal and loose pointer |
| 2 each | Small5VLED lamp, external5V≥1A supply,1A fuse |
| 2 | 10kΩ relay-input pulldown |
| 2 each | Breadboard and jumper set |
| 1 each | Wi-Fi access point and HA host |

## Prerequisites and exact pin map
Python3.12, ESPHome2026.9.1, HA with ESPHome integration, USB drivers. Verify part polarity and microphone DC bias. Bothnodes use identicalpins:
| ESP32 | Connection |
|---|---|
| GPIO34 ADC1 | MicOUT≤3.3V |
| GPIO25 | RelayIN;10kΩtoGND |
| GPIO26 | ServoSignal50Hz |
| 3V3 | MicVCC |
| GND | Mic/relay/servo/lamp/externalnegative return |
| Externalfused5V | RelayVCC/COM andservoV+ |
| RelayNO | Lamppositive;NCunused |

## Circuit/wiring and assembly
Disconnectpower, follow [SVG](docs/circuit-diagram.svg) and [wiring](docs/wiring.md). Join negatives, keepexternalpositiveoff3V3. ControllerusesUSBpower. Use small5Vlamps only. Fit no door linkage; calibrate servopulses withloosearm removed. Each boardneeds aunique node name toavoidentity/APIcollisions.

## Setup, flashing and configuration
```sh
python -m pip install esphome==2026.9.1
cp firmware/secrets.example.yaml firmware/secrets.yaml
# Replace dummy Wi-Fi values and all-zero CI key privately.
esphome config firmware/node-a.yaml
esphome compile firmware/node-a.yaml
esphome run firmware/node-a.yaml
esphome run firmware/node-b.yaml
```
Choose each board’s USBport when prompted. Generate aprivate32byte APIkey with `openssl rand -base64 32`, store it only in ignoredsecrets.yaml and enter it when adding both ESPHome devices toHA. The publishedall-zero key is a**CI dummy**, never deploy it. Foruniqueper-nodekeys, maintain separateprivateconfigurationdirectories. InitialflashUSB; subsequentOTA throughESPHome requiresauthorizednetworkaccess. Defaults: sample10ms, window1s, ≥20validsamples, soundthreshold0.25V peak-to-peak, clipped≤0.03V/≥3.25Vinvalid, pulse5s. These are uncalibrated demo thresholds.

## Usage and multi-room coordination
Add both devices inHA and verify actualentityIDs. Merge [automation](config/home-assistant-automation.yaml) intoHA automations; adjustentityIDs todiscoverednames and reload. It triggers on eithersoundactivity OFF→ON only when bothsensorOKstates areON. A sustainedONsound does not continuouslyretrigger; quietthenloud producesanotheredge. ToggleanIndicator manually to test a5spulse. ON isacceptedonlywithvalidsensorandnativeAPIconnection; OFFcancels the pulse. Firmware independentlyrests onfault/disconnection, evenifHAautomation isunavailable. Coordinationlatency/packetorderingarenotguaranteed.

## Telemetry/data formats and expected output
NativeAPIexposes SoundPeak inV, SoundActivityboolean, SensorOKboolean and Indicatorstate. [SampleJSONL](sample-data/telemetry.jsonl) isillustrative, notanactualwireformat; ESPHomeusesprotobufnativeAPI. Invalidpeaks becomeunavailable/NaN, soundfalse andoutputsrest. OLED isnotpartofthisproject. Onshortloudsoundafterbothnodeshealthy, HAswitchesbothindicatorsON; eachrestsat5s. Pointerrest=-100%(1ms),active=0%(1.5ms),configuredrange1–2ms at50Hz. Anglesdependonactualservo.

## Actual run tests
[Run results](docs/validation-results.md) records C++windowtests,3imagetransporttests, PNG/SVG/links/MIT/credentialchecks, HAYAMLsyntax andactualESPHomeconfig+ESP32ESP-IDFbuildsfor**bothnodes**. [Testplan](docs/test-plan.md). Physicalsensors, relay/servobehavior, encryptedliveAPI, HAandWi-Ficoordinationhave**not**beentested.

## Troubleshooting
UnavailableAPI: privatekey/SSID,nodeuniquenessandnetworkaccess. Noevent: micbias,thresholdandSensorOK; railclippingfailsvalidity. Oneindicatoronly: actualHAentityIDs, bothsensorOK, APIconnection; checklocal5stimeout. Servo jitter: currentsupply/ground/calibration. Relayopposite: onlythe specifiedactive-highmoduleissupported.

## Limitations and domain safety
Soundactivitydoesnotidentifypeopleorunderstandspeech. Analogaudioisnotrecorded. Falseeventsandnetworkdelaysarepossible; thereisnosynchronizeddistributedclockorcertifiedsafetyguarantee. Relaydriveslow-voltageLEDonly,servoaloosepointer; no mains, locks or egress equipment. GPIO is3.3V; servo/coilpowerexternal. Keepfusedsuppliesandwiresawayfrompinchpoints.

## Future work
Measurelatencyandfalsepositive rates, addhardware-in-loopnetworkfaulttests andqualifiedauthenticatedcontrolpolicies.

## Contributing and license
Maintainwindowfaultcoverage,per-nodeboundsandpin-mapconsistency. Full [MITlicense](LICENSE). Primaryconfigurationdocs: [nativeAPI](https://esphome.io/components/api/) and [servo](https://esphome.io/components/servo/).
