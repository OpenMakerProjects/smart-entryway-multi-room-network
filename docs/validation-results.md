# Actual cloud validation results

On 2026-10-10 IST, [Completion run 37999322489](https://github.com/OpenMakerProjects/smart-entryway-multi-room-network/actions/runs/37999322489) and [Validate run 37999322546](https://github.com/OpenMakerProjects/smart-entryway-multi-room-network/actions/runs/37999322546) succeeded on repaired source/image commit `284133a84aae78e88c16d10a5b6e26da60183990`.

Passed: C++ microphone window host tests (count, peaks, quiet, clipping, NaN and recovery), three image transport tests, PNG SHA256/CRC/dimension checks, SVG parsing, README links, full MIT and credential scans, Home Assistant automation YAML syntax, and actual ESPHome 2026.9.1 configuration and ESP-IDF compilation for both node-a and node-b.

Earlier runs failed on the reserved all-zero example API key and custom-global header order. The public CI key is now non-zero and example-only; device microphone state uses equivalent primitive globals. No coverage or window behavior was removed. Final push and PR workflows rerun the complete gates on this documentation commit; durable state records their exact head and run IDs before merge.

Physical microphones, relay/servo operation, flashing, live Home Assistant/API, and Wi-Fi coordination were not tested.
